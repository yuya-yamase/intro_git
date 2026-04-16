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
#define TYDC_DTC_NUM_TR_EVT                      (53U)                   /* ((Max. of DEM_DemEventDTC_XXXX) + 1) */
#define TYDC_DTC_NUM_PDU_RX                      (15U)
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
const U2                    u2_g_TYDC_DTC_RIMID_UDM_EV_CNT = (U2)RIMID_U1_OXDC_UDTC_EV_CNT;
const U2                    u2_g_TYDC_DTC_RIMID_UDM_EV_ID  = (U2)RIMID_U2_OXDC_UDTC_LAST_EV_ID;

const U1                    u1_g_TYDC_DTC_NOW_TR_ACT = (U1)TYDC_DTC_NOW_TR_ACT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_PDU_RX    st_gp_TYDC_DTC_PDU_RX[] = {
/*   u2_pdu_idx,                    u4_sys_chk,   u2_rx_tout,                   u2_rxc_cyc,                         u2_rxc_min */
    {(U2)OXCAN_RXD_PDU_CAN_BAT1S01_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)3004U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_TPM1S02_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)3004U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_VSC1G13_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(3600U),   (U2)64U    / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_EPS1S90_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(3600U),   (U2)904U   / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_SCS1S11_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(10000U),  (U2)6004U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_ARS1S90_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(3600U),   (U2)904U   / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_PDS1S01_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)3004U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_ITS1S01_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)3004U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_SOL1S02_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)3004U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_BDC1S97_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)3004U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_BDC1S98_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)3004U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_ADU1S07_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)3004U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_FCM1S52_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)3004U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_ENG1G90_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)3004U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_RXD_PDU_CAN_EHV1S99_CH0,  (U4)OXCAN_SYS_DIC,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)3004U  / (U2)OXDC_MAIN_TICK,    (U2)2U}
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
    {vdp_PTR_NA,                    (U2)0x0001U,    DemConf_DemEventParameter_DemEventDTC_P1100,  (U1)0U,     (U1)1U,     (U1)0U,     (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0002U,    DemConf_DemEventParameter_DemEventDTC_U0827,  (U1)1U,     (U1)1U,     (U1)1U,     (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0004U,    DemConf_DemEventParameter_DemEventDTC_C0597,  (U1)2U,     (U1)1U,     (U1)2U,     (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0008U,    DemConf_DemEventParameter_DemEventDTC_C05D6,  (U1)3U,     (U1)1U,     (U1)3U,     (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0010U,    DemConf_DemEventParameter_DemEventDTC_U0832,  (U1)4U,     (U1)1U,     (U1)4U,     (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0020U,    DemConf_DemEventParameter_DemEventDTC_C0559,  (U1)5U,     (U1)1U,     (U1)5U,     (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0040U,    DemConf_DemEventParameter_DemEventDTC_U0851,  (U1)6U,     (U1)1U,     (U1)6U,     (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0080U,    DemConf_DemEventParameter_DemEventDTC_U1809,  (U1)7U,     (U1)1U,     (U1)7U,     (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0100U,    DemConf_DemEventParameter_DemEventDTC_U170D,  (U1)8U,     (U1)1U,     (U1)8U,     (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0001U,    DemConf_DemEventParameter_DemEventDTC_U0843,  (U1)9U,     (U1)1U,     (U1)9U,     (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0002U,    DemConf_DemEventParameter_DemEventDTC_U0845,  (U1)10U,    (U1)1U,     (U1)10U,    (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0004U,    DemConf_DemEventParameter_DemEventDTC_U085C,  (U1)11U,    (U1)1U,     (U1)11U,    (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0008U,    DemConf_DemEventParameter_DemEventDTC_U1802,  (U1)12U,    (U1)1U,     (U1)12U,    (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0010U,    DemConf_DemEventParameter_DemEventDTC_U0822,  (U1)13U,    (U1)1U,     (U1)13U,    (U1)0U},
    {vdp_PTR_NA,                    (U2)0x0020U,    DemConf_DemEventParameter_DemEventDTC_U1706,  (U1)14U,    (U1)1U,     (U1)14U,    (U1)0U}
};
const U1                    u1_g_TYDC_DTC_NUM_COM_RX = (U1)(sizeof(st_gp_TYDC_DTC_COM_RX) / sizeof(ST_TYDC_DTC_COM_RX));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_TR_CHK    st_gp_TYDC_DTC_TR_CHK[] = {
/*   fp_u1_CHK,                     u2_smpl_tslot,  u2_dtc_id             */
    {&u1_g_oXDoCANDtcTrchk_U1807,   (U2)0x0200U,    (U2)DemConf_DemEventParameter_DemEventDTC_U1807},
    {&u1_g_oXDoCANDtcTrchk_B1510,   (U2)0x0040U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1510},
    {&u1_g_oXDoCANDtcTrchk_B1511,   (U2)0x0080U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1511},
    {&u1_g_oXDoCANDtcTrchk_B1518,   (U2)0x0100U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1518},
    {&u1_g_oXDoCANDtcTrchk_B1519,   (U2)0x0200U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1519},
    {&u1_g_oXDoCANDtcTrchk_B151A,   (U2)0x0001U,    (U2)DemConf_DemEventParameter_DemEventDTC_B151A},
    {&u1_g_oXDoCANDtcTrchk_U2A00,   (U2)0x0001U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A00},
    {&u1_g_oXDoCANDtcTrchk_U2A01,   (U2)0x0002U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A01},
    {&u1_g_oXDoCANDtcTrchk_U2A16,   (U2)0x0004U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A16},
    {&u1_g_oXDoCANDtcTrchk_U2A17,   (U2)0x0008U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A17},
    {&u1_g_oXDoCANDtcTrchk_U2A12,   (U2)0x0010U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A12},
    {&u1_g_oXDoCANDtcTrchk_U2A13,   (U2)0x0020U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A13},
    {&u1_g_oXDoCANDtcTrchk_U2303,   (U2)0x0040U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2303},
    {&u1_g_oXDoCANDtcTrchk_U2302,   (U2)0x0080U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2302},
    {&u1_g_oXDoCANDtcTrchk_U13A0,   (U2)0x0100U,    (U2)DemConf_DemEventParameter_DemEventDTC_U13A0},
    {&u1_g_oXDoCANDtcTrchk_U2300,   (U2)0x0200U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2300},
    {&u1_g_oXDoCANDtcTrchk_U2301,   (U2)0x0001U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2301},
    {&u1_g_oXDoCANDtcTrchk_B2E01,   (U2)0x0002U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E01},
    {&u1_g_oXDoCANDtcTrchk_B2E02,   (U2)0x0004U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E02},
    {&u1_g_oXDoCANDtcTrchk_B2E03,   (U2)0x0008U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E03},
    {&u1_g_oXDoCANDtcTrchk_B2E04,   (U2)0x0010U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E04},
    {&u1_g_oXDoCANDtcTrchk_B2E05,   (U2)0x0020U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E05},
    {&u1_g_oXDoCANDtcTrchk_B2E06,   (U2)0x0040U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E06},
    {&u1_g_oXDoCANDtcTrchk_B2E07,   (U2)0x0080U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E07},
    {&u1_g_oXDoCANDtcTrchk_B2E08,   (U2)0x0100U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E08},
    {&u1_g_oXDoCANDtcTrchk_B2E12,   (U2)0x0200U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E12},
    {&u1_g_oXDoCANDtcTrchk_B2E15,   (U2)0x0001U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E15},
    {&u1_g_oXDoCANDtcTrchk_B2E20,   (U2)0x0002U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E20},
    {&u1_g_oXDoCANDtcTrchk_B2E22,   (U2)0x0004U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E22},
    {&u1_g_oXDoCANDtcTrchk_B2E23,   (U2)0x0008U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E23},
    {&u1_g_oXDoCANDtcTrchk_B2E24,   (U2)0x0010U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E24},
    {&u1_g_oXDoCANDtcTrchk_B2E25,   (U2)0x0020U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E25},
    {&u1_g_oXDoCANDtcTrchk_B2E26,   (U2)0x0040U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E26},
    {&u1_g_oXDoCANDtcTrchk_B2E27,   (U2)0x0080U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E27},
    {&u1_g_oXDoCANDtcTrchk_B2E28,   (U2)0x0100U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E28},
    {&u1_g_oXDoCANDtcTrchk_B2E29,   (U2)0x0200U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E29},
    {&u1_g_oXDoCANDtcTrchk_B2E30,   (U2)0x0001U,    (U2)DemConf_DemEventParameter_DemEventDTC_B2E30}
};
const U1                    u1_g_TYDC_DTC_NUM_TR_CHK = (U1)(sizeof(st_gp_TYDC_DTC_TR_CHK) / sizeof(ST_TYDC_DTC_TR_CHK));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_UDM_DEL   st_gp_TYDC_DTC_UDM_DEL[] = {
/*   u2_mem_slct,                                           fp_u1_UDM_DEL              */
    {(U2)0xFFFFU,   vdp_PTR_NA}
};

const U1                    u1_g_TYDC_DTC_NUM_UDM_DEL = (U1)(0U);
const U2                    u2_gp_TYDC_DTC_NVMC_BLOCK[DEM_NVM_USE_NVBLOCK_NUM] = {
    (U2)NVMCID_OTR_OXDC_DTC_EVENT001,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT002,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT003,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT004,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT005,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT006,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT007,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT008,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT009,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT010,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT011,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT012,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT013,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT014,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT015,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT016,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT017,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT018,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT019,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT020,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT021,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT001,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT002,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT003,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT004,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT005,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT006,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT007,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT008,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT009,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT010,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT011,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT012,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT013,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT014,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT015,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT016,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT017,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT018,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT019,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT020,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT021,
    (U2)NVMCID_OTR_OXDC_DTC_FFD001,
    (U2)NVMCID_OTR_OXDC_DTC_FFD002,
    (U2)NVMCID_OTR_OXDC_DTC_FFD003,
    (U2)NVMCID_OTR_OXDC_DTC_FFD004,
    (U2)NVMCID_OTR_OXDC_DTC_FFD005,
    (U2)NVMCID_OTR_OXDC_DTC_FFD006,
    (U2)NVMCID_OTR_OXDC_DTC_FFD007,
    (U2)NVMCID_OTR_OXDC_DTC_FFD008,
    (U2)NVMCID_OTR_OXDC_DTC_FFD009,
    (U2)NVMCID_OTR_OXDC_DTC_FFD010,
    (U2)NVMCID_OTR_OXDC_DTC_FFD011,
    (U2)NVMCID_OTR_OXDC_DTC_FFD012,
    (U2)NVMCID_OTR_OXDC_DTC_FFD013,
    (U2)NVMCID_OTR_OXDC_DTC_FFD014,
    (U2)NVMCID_OTR_OXDC_DTC_FFD015,
    (U2)NVMCID_OTR_OXDC_DTC_FFD016,
    (U2)NVMCID_OTR_OXDC_DTC_FFD017,
    (U2)NVMCID_OTR_OXDC_DTC_FFD018,
    (U2)NVMCID_OTR_OXDC_DTC_FFD019,
    (U2)NVMCID_OTR_OXDC_DTC_FFD020,
    (U2)NVMCID_OTR_OXDC_DTC_FFD021,
    (U2)NVMCID_OTR_OXDC_DTC_CLEARINFO,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT007,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT008,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT009,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT010,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT011,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT012,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT013,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT014,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT015,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT016,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT017,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT018,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT019,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT020,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT021,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT022,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT023,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT024,
    (U2)NVMCID_U4_OXDC_OCC1_EVENT025,
    (U2)NVMCID_U4_OXDC_OCC2_EVENT026,
    (U2)NVMCID_U4_OXDC_OCC2_NM_EVENT001,
    (U2)NVMCID_U4_OXDC_OCC2_NM_EVENT002,
    (U2)NVMCID_U4_OXDC_OCC2_NM_EVENT003,
    (U2)NVMCID_U4_OXDC_OCC2_NM_EVENT004,
    (U2)NVMCID_U4_OXDC_OCC3_NM_EVENT005,
    (U2)NVMCID_U4_OXDC_OCC7_NM_EVENT006,
    (U2)NVMCID_U4_OXDC_MAT1_EVENT001,
    (U2)NVMCID_U4_OXDC_MAT1_EVENT002,
    (U2)NVMCID_U4_OXDC_MAT1_EVENT003,
    (U2)NVMCID_U4_OXDC_SOP2_EVENT001,
    (U2)NVMCID_U4_OXDC_SOP2_EVENT002,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT007,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT008,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT009,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT010,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT011,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT012,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT013,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT014,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT015,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT016,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT017,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT018,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT019,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT020,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT021,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT022,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT023,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT024,
    (U2)NVMCID_OTR_OXDC_OCC1_FAULT025,
    (U2)NVMCID_OTR_OXDC_OCC2_FAULT026,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FAULT001,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FAULT002,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FAULT003,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FAULT004,
    (U2)NVMCID_OTR_OXDC_OCC3_NM_FAULT005,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FAULT006,
    (U2)NVMCID_OTR_OXDC_MAT1_FAULT001,
    (U2)NVMCID_OTR_OXDC_MAT1_FAULT002,
    (U2)NVMCID_OTR_OXDC_MAT1_FAULT003,
    (U2)NVMCID_OTR_OXDC_SOP2_FAULT001,
    (U2)NVMCID_OTR_OXDC_SOP2_FAULT002,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD055,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD056,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD057,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD058,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD059,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD060,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD061,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD062,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD063,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD064,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD065,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD066,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD067,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD068,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD069,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD070,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD071,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD072,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD073,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD074,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD075,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD076,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD077,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD078,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD079,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD080,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD081,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD082,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD083,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD084,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD085,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD086,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD087,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD088,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD089,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD090,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD091,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD092,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD093,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD094,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD095,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD096,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD097,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD098,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD099,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD100,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD101,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD102,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD103,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD104,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD105,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD106,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD107,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD108,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD109,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD110,
    (U2)NVMCID_OTR_OXDC_OCC1_FFD111,
    (U2)NVMCID_OTR_OXDC_OCC2_FFD112,
    (U2)NVMCID_OTR_OXDC_OCC2_FFD113,
    (U2)NVMCID_OTR_OXDC_OCC2_FFD114,
    (U2)NVMCID_OTR_OXDC_OCC2_FFD115,
    (U2)NVMCID_OTR_OXDC_OCC2_FFD116,
    (U2)NVMCID_OTR_OXDC_OCC2_FFD117,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD001,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD002,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD003,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD004,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD005,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD006,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD007,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD008,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD009,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD010,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD011,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD012,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD013,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD014,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD015,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD016,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD017,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD018,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD019,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD020,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD021,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD022,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD023,
    (U2)NVMCID_OTR_OXDC_OCC2_NM_FFD024,
    (U2)NVMCID_OTR_OXDC_OCC3_NM_FFD025,
    (U2)NVMCID_OTR_OXDC_OCC3_NM_FFD026,
    (U2)NVMCID_OTR_OXDC_OCC3_NM_FFD027,
    (U2)NVMCID_OTR_OXDC_OCC3_NM_FFD028,
    (U2)NVMCID_OTR_OXDC_OCC3_NM_FFD029,
    (U2)NVMCID_OTR_OXDC_OCC3_NM_FFD030,
    (U2)NVMCID_OTR_OXDC_OCC3_NM_FFD031,
    (U2)NVMCID_OTR_OXDC_OCC3_NM_FFD032,
    (U2)NVMCID_OTR_OXDC_OCC3_NM_FFD033,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD034,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD035,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD036,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD037,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD038,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD039,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD040,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD041,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD042,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD043,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD044,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD045,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD046,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD047,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD048,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD049,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD050,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD051,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD052,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD053,
    (U2)NVMCID_OTR_OXDC_OCC7_NM_FFD054,
    (U2)NVMCID_OTR_OXDC_MAT1_FFD001,
    (U2)NVMCID_OTR_OXDC_MAT1_FFD002,
    (U2)NVMCID_OTR_OXDC_MAT1_FFD003,
    (U2)NVMCID_OTR_OXDC_SOP2_FFD001,
    (U2)NVMCID_OTR_OXDC_SOP2_FFD002,
    (U2)NVMCID_OTR_OXDC_SOP2_FFD003,
    (U2)NVMCID_OTR_OXDC_SOP2_FFD004
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
