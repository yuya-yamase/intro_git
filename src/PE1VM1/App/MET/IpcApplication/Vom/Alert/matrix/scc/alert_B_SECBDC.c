/* 5.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_SECBDC                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_SECBDC_C_MAJOR                   (5)
#define ALERT_B_SECBDC_C_MINOR                   (0)
#define ALERT_B_SECBDC_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_B_SECBDC_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_SECBDC.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_SECBDC_NUM_DST                   (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_b_secbdc_bdc1s97_msgsts;
static U1      u1_s_alert_b_secbdc_bdc1s98_msgsts;
static U1      u1_s_alert_b_secbdc_bdc1s99_msgsts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertB_secbdcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_B_SECBDC_CRIT[ALERT_B_SECBDC_NUM_DST] = {
    (U4)0x02000010U,                                                           /* 00 UNREGISTERED                                    */
    (U4)0x02000004U,                                                           /* 01 UNREGISTERED                                    */
    (U4)0x02000001U                                                            /* 02 UNREGISTERED                                    */
};

static const U4  u4_sp_ALERT_B_SECBDC_MASK[ALERT_B_SECBDC_NUM_DST] = {
    (U4)0x02000030U,                                                           /* 00 UNREGISTERED                                    */
    (U4)0x0200000CU,                                                           /* 01 UNREGISTERED                                    */
    (U4)0x02000003U                                                            /* 02 UNREGISTERED                                    */
};

static const U1  u1_sp_ALERT_B_SECBDC_DST[ALERT_B_SECBDC_NUM_DST] = {
    (U1)ALERT_REQ_B_SECBDC_UNREGISTERED,                                       /* 00 UNREGISTERED                                    */
    (U1)ALERT_REQ_B_SECBDC_UNREGISTERED,                                       /* 01 UNREGISTERED                                    */
    (U1)ALERT_REQ_B_SECBDC_UNREGISTERED                                        /* 02 UNREGISTERED                                    */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_B_SECBDC_MTRX[1] = {
    {
        &u4_s_AlertB_secbdcSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_B_SECBDC_MASK[0],                                         /* u4p_MASK                                           */
        &u4_sp_ALERT_B_SECBDC_CRIT[0],                                         /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SECBDC_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_B_SECBDC_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_pbdksInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_secbdcInit(void)
{
    u1_s_alert_b_secbdc_bdc1s97_msgsts = (U1)COM_NO_RX;
    u1_s_alert_b_secbdc_bdc1s98_msgsts = (U1)COM_NO_RX;
    u1_s_alert_b_secbdc_bdc1s99_msgsts = (U1)COM_NO_RX;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_secddcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_secbdcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_SECBDC_BDC1S97_TO_THRESH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U2 u2_s_ALERT_B_SECBDC_BDC1S98_TO_THRESH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U2 u2_s_ALERT_B_SECBDC_BDC1S99_TO_THRESH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SECBDC_BDC1S97_MSG       = (U1)1U;
    static const U1 u1_s_ALERT_B_SECBDC_BDRMCUNR_SGNL     = (U1)2U;
    static const U1 u1_s_ALERT_B_SECBDC_BDC1S98_MSG       = (U1)3U;
    static const U1 u1_s_ALERT_B_SECBDC_BDLMCUNR_SGNL     = (U1)4U;
    static const U1 u1_s_ALERT_B_SECBDC_BDC1S99_MSG       = (U1)5U;

    U1              u1_t_trns_fact;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_trns_fact   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_BDC1S97_CH0,
                                         (U4)ALERT_CAN_SYS_ALL,
                                         u2_s_ALERT_B_SECBDC_BDC1S97_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_secbdc_bdc1s97_msgsts, u1_t_trns_fact);

    u1_t_sgnl        = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BDFMCUNR, &u1_t_sgnl);

    u4_t_src_chk     = (U4)u1_t_sgnl;
    u4_t_src_chk    |= (((U4)u1_s_alert_b_secbdc_bdc1s97_msgsts & (U4)COM_NO_RX) << u1_s_ALERT_B_SECBDC_BDC1S97_MSG);


    u1_t_trns_fact   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_BDC1S98_CH0,
                                         (U4)ALERT_CAN_SYS_ALL,
                                         u2_s_ALERT_B_SECBDC_BDC1S98_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_secbdc_bdc1s98_msgsts, u1_t_trns_fact);

    u1_t_sgnl        = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BDRMCUNR, &u1_t_sgnl);

    u4_t_src_chk    |= ((U4)u1_t_sgnl << u1_s_ALERT_B_SECBDC_BDRMCUNR_SGNL);
    u4_t_src_chk    |= (((U4)u1_s_alert_b_secbdc_bdc1s98_msgsts & (U4)COM_NO_RX) << u1_s_ALERT_B_SECBDC_BDC1S98_MSG);


    u1_t_trns_fact   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_BDC1S99_CH0,
                                         (U4)ALERT_CAN_SYS_ALL,
                                         u2_s_ALERT_B_SECBDC_BDC1S99_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_secbdc_bdc1s99_msgsts, u1_t_trns_fact);

    u1_t_sgnl        = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BDLMCUNR, &u1_t_sgnl);

    u4_t_src_chk    |= ((U4)u1_t_sgnl << u1_s_ALERT_B_SECBDC_BDLMCUNR_SGNL);
    u4_t_src_chk    |= (((U4)u1_s_alert_b_secbdc_bdc1s99_msgsts & (U4)COM_NO_RX) << u1_s_ALERT_B_SECBDC_BDC1S99_MSG);

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
/*  5.0.0    02/06/2026  YH       New(BEV Full_Function_2).                                                                          */
/*                                MET-B_SECBDC-CSTD-0-00-A-C0                                                                        */
/*                                Created due to specification change from feature to legacy.                                        */
/*                                                                                                                                   */
/*  * YH   = Yuki Hatakeyama, KSE                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
