/* 1.9.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  SID 0x14 0x19 0x85                                                                                                               */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DTC_CFG_C_MAJOR                  (1U)
#define TYDOCAN_DTC_CFG_C_MINOR                  (9U)
#define TYDOCAN_DTC_CFG_C_PATCH                  (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "tydocan_dtc_cfg_private.h"

/* #include "nvmc_mgr.h"             nvmc_mgr.h is included in oxdocan_cfg_private.h              */
/* #include "oxcan.h"                oxcan.h is included in oxdocan_cfg_private.h                 */

#include "Dem.h"                  /* DEM_DemEventDTC_XXX are defined in Dem.h                     */
/* #include "Dem_MM_Cfg.h"           DEM_MM_NVM_REC_KIND_XXX are defined in Dem_MM_Cfg.h          */
/*                                   Dem_MM_Cfg.h is included in tydocan_dtc_cfg_private.h        */
/* #include "rim_ctl.h"              rim_ctl.h is included in tydocan_dtc_cfg_private.h           */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "veh_opemd.h"
#include "xspi_met_dsal.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_DTC_CFG_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_dtc_cfg.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_CFG_C_MAJOR != TYDOCAN_DTC_CFG_H_MAJOR) || \
     (TYDOCAN_DTC_CFG_C_MINOR != TYDOCAN_DTC_CFG_H_MINOR) || \
     (TYDOCAN_DTC_CFG_C_PATCH != TYDOCAN_DTC_CFG_H_PATCH))
#error "tydocan_dtc_cfg.c and tydocan_dtc_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_NUM_TR_EVT                      (2U)                    /* ((Max. of DEM_DemEventDTC_XXXX) + 1) */
#define TYDC_DTC_NUM_PDU_RX                      (1U)
#define TYDC_DTC_NOW_LOG_RX                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_NOW_TR_ACT                      ((TYDC_DTC_NUM_TR_EVT + 31U) >> 5U)


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4                      u4_gp_tydc_dtc_tr_act[TYDC_DTC_NOW_TR_ACT];
ST_TYDC_DTC_LOG_RX      st_gp_tydc_dtc_log_rx[TYDC_DTC_NOW_LOG_RX];
U2                      u2_gp_tydc_dtc_rxc_st[TYDC_DTC_NUM_PDU_RX];
U1                      u1_gp_tydc_dtc_rx_cnt[TYDC_DTC_NUM_PDU_RX];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0    /* BEV Diag provisionally */
const U2                    u2_g_TYDC_DTC_RIMID_UDM_EV_CNT = (U2)RIMID_U1_OXDC_UDTC_EV_CNT;
const U2                    u2_g_TYDC_DTC_RIMID_UDM_EV_ID  = (U2)RIMID_U2_OXDC_UDTC_LAST_EV_ID;
#else    /* BEV Diag provisionally */
const U2                    u2_g_TYDC_DTC_RIMID_UDM_EV_CNT = (U2)U2_MAX;
const U2                    u2_g_TYDC_DTC_RIMID_UDM_EV_ID  = (U2)U2_MAX;
#endif    /* BEV Diag provisionally */

const U1                    u1_g_TYDC_DTC_NOW_TR_ACT = (U1)TYDC_DTC_NOW_TR_ACT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_PDU_RX    st_gp_TYDC_DTC_PDU_RX[] = {
/*   u2_pdu_idx,                    u2_sys_chk,   u2_rx_tout,                   u2_rxc_cyc,                         u2_rxc_min */
    {(U2)0x0000U,                   (U2)0x0000U,  u2_OXCAN_RXTO_THRSH(10000U),  (U2)10000U / (U2)OXDC_MAIN_TICK,    (U2)2U} /* Dummy */
};
const U1                    u1_g_TYDC_DTC_NUM_PDU_RX = (U1)TYDC_DTC_NUM_PDU_RX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                    u2_gp_TYDC_DTC_NVMC_LOG_RX[TYDC_DTC_NOW_LOG_RX] = {
    (U2)NVMCID_U4_OXDC_DTC_LOGRX1
};
const U1                    u1_g_TYDC_DTC_NOW_LOG_RX = (U1)TYDC_DTC_NOW_LOG_RX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_COM_RX    st_gp_TYDC_DTC_COM_RX[] = {
/*   fp_u1_SUP,                     u2_smpl_tslot,  u2_dtc_id,            u1_pdu_begin, u1_num_pdu, u1_log_bit, u1_log_idx */
    {vdp_PTR_NA,                    (U2)0x0000U,    (U2)0x0000U,            (U1)0U,       (U1)0U,     (U1)0U,     (U1)0U}     /* Dummy */
};
const U1                    u1_g_TYDC_DTC_NUM_COM_RX = (U1)0U;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_TR_CHK    st_gp_TYDC_DTC_TR_CHK[] = {
/*   fp_u1_CHK,                     u2_smpl_tslot,  u2_dtc_id             */
    {&u1_g_oXDoCANDtcTrchk_U2303,   (U2)0x0001U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2303}
};
const U1                    u1_g_TYDC_DTC_NUM_TR_CHK = (U1)(sizeof(st_gp_TYDC_DTC_TR_CHK) / sizeof(ST_TYDC_DTC_TR_CHK));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_UDM_DEL   st_gp_TYDC_DTC_UDM_DEL[] = {
/*   u2_mem_slct,                                           fp_u1_UDM_DEL              */
    {(U2)0x0000U,                                                              vdp_PTR_NA}       /* Dummy */
};
const U1                    u1_g_TYDC_DTC_NUM_UDM_DEL = (U1)0U;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                    u2_gp_TYDC_DTC_NVMC_BLOCK[DEM_NVM_USE_NVBLOCK_NUM] = {
    (U2)NVMCID_OTR_OXDC_DTC_EVENT001,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT001,
    (U2)NVMCID_OTR_OXDC_DTC_FFD001,
    (U2)NVMCID_OTR_OXDC_DTC_CLEARINFO,
    (U2)NVMCID_U4_OXDC_MAT1_EVENT001,
    (U2)NVMCID_OTR_OXDC_MAT1_FAULT001,
    (U2)NVMCID_OTR_OXDC_MAT1_FFD001
};
const U2                    u2_g_TYDC_DTC_S14_TOUT = ((U2)200U / (U2)OXDC_MAIN_TICK) * (U2)DEM_NVM_USE_NVBLOCK_NUM;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcCfgEvmFinish(const U1 u1_a_S14)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcCfgEvmFinish(const U1 u1_a_S14)
{
    if(u1_a_S14 == (U1)TRUE){ /* SID14 */
        vd_g_XSpiDsrUnlock((U4)XSPI_DSR_UNLOCK);
        vd_g_XSpiDsrTx((U1)XSPI_DSR_14_DTC, (U1)XSPI_DTC_CLR_FIN);
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     5/20/2019  TN       New.                                                                                               */
/*  1.1.0    10/15/2019  TN       tydocan_dtc.c v1.0.0 -> v1.1.0                                                                     */
/*  1.2.0    11/ 8/2019  TN       tydocan_dtc.c v1.1.0 -> v1.2.0                                                                     */
/*  1.3.0    11/22/2019  TN       tydocan_dtc.c v1.2.0 -> v1.3.0                                                                     */
/*  1.4.0     2/24/2020  HK       tydocan_dtc.c v1.3.0 -> v1.4.0                                                                     */
/*  1.5.0     3/13/2020  TN       tydocan_dtc.c v1.4.0 -> v1.5.0                                                                     */
/*  1.6.0     7/21/2020  TN       tydocan_dtc.c v1.5.0 -> v1.6.0                                                                     */
/*  1.7.0    12/22/2020  TN       tydocan_dtc.c v1.6.0 -> v1.7.0                                                                     */
/*  1.8.0     2/19/2021  TN       tydocan_dtc.c v1.7.0 -> v1.8.0                                                                     */
/*  1.8.1     4/ 2/2021  HK       tydocan_dtc.c v1.8.0 -> v1.8.1                                                                     */
/*  1.8.2     6/ 9/2021  TN       tydocan_dtc.c v1.8.1 -> v1.8.2                                                                     */
/*  1.8.3     9/ 9/2021  TN       tydocan_dtc.c v1.8.2 -> v1.8.3                                                                     */
/*  1.9.0    10/ 8/2021  TN       tydocan_dtc.c v1.8.3 -> v1.9.0                                                                     */
/*  1.9.1     7/ 7/2023  ST       tydocan_dtc.c v1.9.0 -> v1.9.1                                                                     */
/*  1.9.2    11/08/2023  TI       tydocan_dtc.c v1.9.1 -> v1.9.2                                                                     */
/*  1.9.3     1/23/2024  TI       Moved tydocan_dtc_nmwk config from here to tydocan_dtc_nmslp_cfg.c                                 */
/*  1.9.4    11/18/2024  TI       tydocan_dtc.c v1.9.3 -> v1.9.4                                                                     */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*  * HK = Hayato Kanamori, DENSO Create                                                                                             */
/*  * ST = Shohei Takada, DENSO                                                                                                      */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
