/* 1.9.3 */
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
#define TYDOCAN_DTC_CFG_C_PATCH                  (3U)

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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)     ) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)  ) && \
     (BSW_BSWM_CS_CFG_FUNC_CS    == BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC == BSW_USE))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_dtc_ma_cfg_private.h"
#include "tydocan_xid_ma_cfg_private.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && ... */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Application Headers */
#include "tydocan_dtc_mm_cfg_private.h" 
#include "tydocan_dtc_nmwk.h"
#include "tydocan_dtc_ecuslp.h"
#include "tydocan_dtc_nmgbl.h"
#ifdef TYDOCAN_DTC_MA_CFG_H
#include "tydocan_evlog_cfg_private.h"
#endif /* #ifdef TYDOCAN_DTC_MA_CFG_H */
#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif

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
#define TYDC_DTC_NUM_TR_EVT                      (38U)                   /* ((Max. of DEM_DemEventDTC_XXXX) + 1) */
#define TYDC_DTC_NUM_PDU_RX                      (22U)
#define TYDC_DTC_NOW_LOG_RX                      (1U)

#ifdef TYDOCAN_DTC_MM_CFG_H
#define TYDC_DTC_MM_NUM_PDU_RX                   (1U)
#endif /* #ifdef TYDOCAN_DTC_MM_CFG_H */
#ifdef TYDOCAN_DTC_MA_CFG_H
#define TYDC_DTC_MA_SYN_TOUT                     (310U)                  /* 3.1 seconds                           */
#define TYDC_DTC_MA_ODO_MIN                      (1U)
#define TYDC_DTC_MA_ODO_MAX                      (999999U)
#endif /* #ifdef TYDOCAN_DTC_MA_CFG_H */

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

#ifdef TYDOCAN_DTC_MM_CFG_H
U2                      u2_gp_tydc_dtc_mm_rxc_st[TYDC_DTC_MM_NUM_PDU_RX];
U1                      u1_gp_tydc_dtc_mm_rx_cnt[TYDC_DTC_MM_NUM_PDU_RX];
#endif /* #ifdef TYDOCAN_DTC_MM_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*Phase6Diag Stub*/
U1      u1_s_oXDoCANDtcStubSup(void);
U1      u1_s_oXDoCANDtcStubTrChk(const U2 u2_a_ELPSD);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1                    u1_g_TYDC_DTC_NOW_TR_ACT = (U1)TYDC_DTC_NOW_TR_ACT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_PDU_RX    st_gp_TYDC_DTC_PDU_RX[] = {
/*   u2_pdu_idx,                    u2_sys_chk,   u2_rx_tout,                   u2_rxc_cyc,                         u2_rxc_min */
    {(U2)OXCAN_PDU_RX_CAN_ENG1G97,  (U2)0x8080U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_PCN1S01,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_BAT1S01,  (U2)0x8080U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_FWD1S90,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_STR1S01,  (U2)0x8080U,  u2_OXCAN_RXTO_THRSH(3600U),   (U2)19U    / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_TPM1S04,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_VSC1G13,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(3600U),   (U2)29U    / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_EPS1S90,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(3600U),   (U2)309U   / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_SCS1S90,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(10000U),  (U2)2009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_ARS1S90,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(3600U),   (U2)309U   / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_ABG1S01,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_FCM1S52,  (U2)0x8080U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_AVN1S20,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_ACN1S07,  (U2)0x8080U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_PLG1S01,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_VSC1S97,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(3600U),   (U2)309U   / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_ECT1G01,  (U2)0x8080U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_ECO1S90,  (U2)0x8080U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_CSR1S08,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_SBM1S02,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_BDB1S03,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U},
    {(U2)OXCAN_PDU_RX_CAN_IDT1S02,  (U2)0x8080U,  u2_OXCAN_RXTO_THRSH(5000U),   (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)2U}
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
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0001U,    DemConf_DemEventParameter_DemEventDTC_U0100,  (U1)0U,     (U1)1U,     (U1)2U,     (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0002U,    DemConf_DemEventParameter_DemEventDTC_U0103,  (U1)1U,     (U1)1U,     (U1)3U,     (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0004U,    DemConf_DemEventParameter_DemEventDTC_U0111,  (U1)2U,     (U1)1U,     (U1)4U,     (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0008U,    DemConf_DemEventParameter_DemEventDTC_U0114,  (U1)3U,     (U1)1U,     (U1)5U,     (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0010U,    DemConf_DemEventParameter_DemEventDTC_U0126,  (U1)4U,     (U1)2U,     (U1)0U,     (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0020U,    DemConf_DemEventParameter_DemEventDTC_U0129,  (U1)6U,     (U1)1U,     (U1)6U,     (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0040U,    DemConf_DemEventParameter_DemEventDTC_U0131,  (U1)7U,     (U1)1U,     (U1)7U,     (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0080U,    DemConf_DemEventParameter_DemEventDTC_U0132,  (U1)8U,     (U1)1U,     (U1)8U,     (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0100U,    DemConf_DemEventParameter_DemEventDTC_U0134,  (U1)9U,     (U1)1U,     (U1)9U,     (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0200U,    DemConf_DemEventParameter_DemEventDTC_U0151,  (U1)10U,    (U1)1U,     (U1)10U,    (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0001U,    DemConf_DemEventParameter_DemEventDTC_U015C,  (U1)11U,    (U1)1U,     (U1)11U,    (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0002U,    DemConf_DemEventParameter_DemEventDTC_U015E,  (U1)12U,    (U1)1U,     (U1)12U,    (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0004U,    DemConf_DemEventParameter_DemEventDTC_U0164,  (U1)13U,    (U1)1U,     (U1)13U,    (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0008U,    DemConf_DemEventParameter_DemEventDTC_U019B,  (U1)14U,    (U1)1U,     (U1)14U,    (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0010U,    DemConf_DemEventParameter_DemEventDTC_U025E,  (U1)15U,    (U1)1U,     (U1)15U,    (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0020U,    DemConf_DemEventParameter_DemEventDTC_U0293,  (U1)16U,    (U1)1U,     (U1)16U,    (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0040U,    DemConf_DemEventParameter_DemEventDTC_U1103,  (U1)17U,    (U1)1U,     (U1)17U,    (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0080U,    DemConf_DemEventParameter_DemEventDTC_U1110,  (U1)18U,    (U1)1U,     (U1)18U,    (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0100U,    DemConf_DemEventParameter_DemEventDTC_U114A,  (U1)19U,    (U1)1U,     (U1)19U,    (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0200U,    DemConf_DemEventParameter_DemEventDTC_U1201,  (U1)20U,    (U1)1U,     (U1)20U,    (U1)0U},
    {&u1_s_oXDoCANDtcStubSup,       (U2)0x0001U,    DemConf_DemEventParameter_DemEventDTC_U1202,  (U1)21U,    (U1)1U,     (U1)21U,    (U1)0U}
};
const U1                    u1_g_TYDC_DTC_NUM_COM_RX = (U1)(sizeof(st_gp_TYDC_DTC_COM_RX) / sizeof(ST_TYDC_DTC_COM_RX));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_TR_CHK    st_gp_TYDC_DTC_TR_CHK[] = {
/*   fp_u1_CHK,                     u2_smpl_tslot,  u2_dtc_id             */
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0002U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1321},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0004U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1328},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0008U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1500},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0010U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1501},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0020U,    (U2)DemConf_DemEventParameter_DemEventDTC_B150B},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0040U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1510},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0080U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1511},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0100U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1518},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0200U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1519},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0001U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A16},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0002U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A17},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0004U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A12},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0008U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A13},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0010U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A00},
    {&u1_s_oXDoCANDtcStubTrChk,     (U2)0x0020U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2A01},
    {&u1_g_oXDoCANDtcTrchk_U2303,   (U2)0x0010U,    (U2)DemConf_DemEventParameter_DemEventDTC_U2303}
};
const U1                    u1_g_TYDC_DTC_NUM_TR_CHK = (U1)(sizeof(st_gp_TYDC_DTC_TR_CHK) / sizeof(ST_TYDC_DTC_TR_CHK));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_UDM_DEL   st_gp_TYDC_DTC_UDM_DEL[] = {
/*   u2_mem_slct,                                           fp_u1_UDM_DEL              */
    {(U2)(DEM_DTC_ORIGIN_USERDEFINED_MEMORY | (U2)0x11U),   &u1_g_oXDoCANDtcUdmDelNmwk},
    {(U2)(DEM_DTC_ORIGIN_USERDEFINED_MEMORY | (U2)0x11U),   &u1_g_oXDoCANDtcUdmDelNmGbl},
    {(U2)(DEM_DTC_ORIGIN_USERDEFINED_MEMORY | (U2)0x11U),   &u1_g_oXDoCANDtcUdmDelEcuSlp}
};
const U1                    u1_g_TYDC_DTC_NUM_UDM_DEL = (U1)(sizeof(st_gp_TYDC_DTC_UDM_DEL) / sizeof(ST_TYDC_DTC_UDM_DEL));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
    (U2)NVMCID_OTR_OXDC_DTC_EVENT022,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT023,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT024,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT025,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT026,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT027,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT028,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT029,
    (U2)NVMCID_OTR_OXDC_DTC_EVENT030,
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
    (U2)NVMCID_OTR_OXDC_DTC_FAULT022,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT023,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT024,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT025,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT026,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT027,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT028,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT029,
    (U2)NVMCID_OTR_OXDC_DTC_FAULT030,
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
    (U2)NVMCID_OTR_OXDC_DTC_FFD022,
    (U2)NVMCID_OTR_OXDC_DTC_FFD023,
    (U2)NVMCID_OTR_OXDC_DTC_FFD024,
    (U2)NVMCID_OTR_OXDC_DTC_FFD025,
    (U2)NVMCID_OTR_OXDC_DTC_FFD026,
    (U2)NVMCID_OTR_OXDC_DTC_FFD027,
    (U2)NVMCID_OTR_OXDC_DTC_FFD028,
    (U2)NVMCID_OTR_OXDC_DTC_FFD029,
    (U2)NVMCID_OTR_OXDC_DTC_FFD030,
    (U2)NVMCID_U4_OXDC_DTC_CLEARINFO,
    (U2)NVMCID_U4_OXDC_DTC_UDM_EVENT001,
    (U2)NVMCID_U4_OXDC_DTC_UDM_EVENT002,
    (U2)NVMCID_U4_OXDC_DTC_UDM_EVENT003,
    (U2)NVMCID_U4_OXDC_DTC_UDM_EVENT004,
    (U2)NVMCID_U4_OXDC_DTC_UDM_EVENT005,
    (U2)NVMCID_U4_OXDC_DTC_UDM_EVENT006,
    (U2)NVMCID_U4_OXDC_DTC_UDM_EVENT007,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FAULT001,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FAULT002,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FAULT003,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FAULT004,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FAULT005,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FAULT006,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FAULT007,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD001,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD002,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD003,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD004,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD005,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD006,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD007,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD008,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD009,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD010,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD011,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD012,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD013,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD014,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD015,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD016,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD017,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD018,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD019,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD020,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD021,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD022,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD023,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD024,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD025,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD026,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD027,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD028,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD029,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD030,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD031,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD032,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD033,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD034,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD035,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD036,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD037,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD038,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD039,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD040,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD041,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD042,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD043,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD044,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD045,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD046,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD047,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD048,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD049,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD050,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD051,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD052,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD053,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD054,
    (U2)NVMCID_OTR_OXDC_DTC_UDM_FFD055
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
#ifdef TYDOCAN_DTC_MM_CFG_H
    vd_g_TyDoCANDtcMMInit(u1_a_S14);
#endif /* #ifdef TYDOCAN_DTC_MM_CFG_H */
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcCfgUdmEvCntEnabled(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcCfgUdmEvCntEnabled(void)
{
    return(u1_g_VehopemdIgnOn());
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcCfgNvmKind(const U2 u2_a_rec_id)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcCfgNvmKind(const U2 u2_a_rec_id)
{
    U1      u1_t_rec_kind;

    u1_t_rec_kind = (U1)TYDC_DTC_NVM_REC_KIND_OTHER;

    switch (u2_a_rec_id)
    {
    case DEM_MM_NVM_REC_KIND_EVT:
        u1_t_rec_kind = (U1)TYDC_DTC_NVM_REC_KIND_PRIM_EVT;
        break;
    case DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE2_EVT:
    case DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE3_EVT:
    case DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE7_EVT:
    case DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_MAINTENANCE1_EVT:
        u1_t_rec_kind = (U1)TYDC_DTC_NVM_REC_KIND_UDM_EVT;
        break;
    default:
        /* Do Nothing */
        break;
    }

    return(u1_t_rec_kind);
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#ifdef TYDOCAN_DTC_MM_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_PDU_RX    st_gp_TYDC_DTC_MM_PDU_RX[TYDC_DTC_MM_NUM_PDU_RX] = {
/*                                                                                                  */
/*   Attention :                                                                                    */
/*   u2_sys_chk shall be equal to (OXCAN_RX_SYS_NRX_VDC | OXCAN_RX_SYS_TOE_VDC)                     */
/*                                                                                                  */
/*   u2_pdu_idx,                    u2_sys_chk,   u2_rx_tout,                   u2_rxc_cyc,                         u2_rxc_min */
    {(U2)OXCAN_PDU_RX_CAN_AVNMS49,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(30000U),  (U2)13509U / (U2)OXDC_MAIN_TICK,    (U2)3U}
};
#if (TYDC_DTC_MM_NUM_PDU_RX > TYDC_DTC_MM_PDU_MAX)
#error "tydocan_dtc_cfg.c : TYDC_DTC_MM_NUM_PDU_RX shall be equal or less than TYDC_DTC_MM_PDU_MAX."
#endif
const U1                    u1_g_TYDC_DTC_MM_NUM_PDU_RX = (U1)TYDC_DTC_MM_NUM_PDU_RX;

const ST_TYDC_DTC_COM_RX    st_gp_TYDC_DTC_MM_RX[TYDC_DTC_MM_NUM_RX] = {
/*   fp_u1_SUP,                     u2_smpl_tslot,  u2_dtc_id,            u1_pdu_begin, u1_num_pdu, u1_log_bit, u1_log_idx */
#if 0/*Phase6Diag Stub*/
     {vdp_PTR_NA,                    (U2)0U,        (U2)U2_MAX,           (U1)0U,       (U1)1U,     (U1)0U,     (U1)0U}         /* dummy */
#else
    {&u1_g_oXDoCANDtcSup_B1321,     (U2)0x0200U,    (U2)U2_MAX,           (U1)0U,       (U1)1U,     (U1)0U,     (U1)0U}     /* B1321 */
#endif
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                    u2_gp_TYDC_DTC_MM_AOM_TOUT[TYDC_DTC_MM_NUM_RX] = {
    (U2)10000U / (U2)OXDC_MAIN_TICK          /* B1321 : 10000 milliseconds */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcMMCfgAccOn(const U1 u1_a_EOM)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcMMCfgAccOn(const U1 u1_a_EOM)
{
    /* --------------------------------------------------------------- */
    /* WARNING                                                         */
    /* --------------------------------------------------------------- */
    /* u1_g_VehopemdAccOn() is tentatively implemented because ACC-ON  */
    /* signal is NOT defined in Multi-Media Sys. relevant specs.       */
    /* --------------------------------------------------------------- */
/*#warning "tydocan_dtc_cfg.c : u1_g_VehopemdAccOn() is tentatively implemented. Find how ACC-ON is determined for Multi-Media System."*/
    return(u1_g_VehopemdAccOn());
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* #ifdef TYDOCAN_DTC_MM_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/

#ifdef TYDOCAN_DTC_MA_CFG_H  /* tydocan_dtc_ma_cfg_private.h */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                    u2_g_TYDC_DTC_MA_SYN_TOUT = TYDC_DTC_MA_SYN_TOUT;

const U2                    u2_g_TYDC_DTC_MA_RFC_MAX = (U2)1U;
const U2                    u2_gp_TYDC_DTC_MA_RF_TOUT[TYDC_DTC_MA_RF_NUM_CHK] = {
    (U2)0U,                           /* TYDC_DTC_MA_RF_CHK_INA (0U) */
    (U2)3000U / (U2)OXDC_MAIN_TICK,   /* TYDC_DTC_MA_RF_CHK_STA (1U) */ /* IG-ON Mask    3 seconds */
    (U2)1000U / (U2)OXDC_MAIN_TICK    /* TYDC_DTC_MA_RF_CHK_RUN (2U) */ /* MacFilCntTerm 1 second  */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcMaCfgRfcOdochk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcMaCfgRfcOdochk(void)
{
#ifdef MSG_MET1S02_RXCH0
    U4                      u4_t_odo_dist;
    U1                      u1_t_rx_stat;
    U1                      u1_t_odo_chk;

    u1_t_rx_stat = Com_GetIPDUStatus((U2)MSG_MET1S02_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    (void)Com_ReceiveSignal(ComConf_ComSignal_ODO, &u4_t_odo_dist);
    if((u1_t_rx_stat  == (U1)0U                 ) &&
       (u4_t_odo_dist >= (U4)TYDC_DTC_MA_ODO_MIN) &&
       (u4_t_odo_dist <= (U4)TYDC_DTC_MA_ODO_MAX)){
        u1_t_odo_chk = (U1)TRUE;
    }
    else{
        u1_t_odo_chk = (U1)FALSE;
    }

    return(u1_t_odo_chk);
#else
    U4                      u4_t_odo_dist;
    U1                      u1_t_odo_chk;

    (void)Com_ReceiveSignal(ComConf_ComSignal_ODO, &u4_t_odo_dist);
    if((u4_t_odo_dist >= (U4)TYDC_DTC_MA_ODO_MIN) &&
       (u4_t_odo_dist <= (U4)TYDC_DTC_MA_ODO_MAX)){
        u1_t_odo_chk = (U1)TRUE;
    }
    else{
        u1_t_odo_chk = (U1)FALSE;
    }

    return(u1_t_odo_chk);
#endif /* #ifdef MSG_MET1S02_RXCH0 */
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* #ifdef TYDOCAN_DTC_MA_CFG_H */

/*Phase6Diag Stub*/
U1      u1_s_oXDoCANDtcStubSup(void){
    return((U1)FALSE);
}

U1      u1_s_oXDoCANDtcStubTrChk(const U2 u2_a_ELPSD){
    return((U1)OXDC_DTC_TR_N_A);
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
