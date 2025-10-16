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
/* Application Headers */
#ifdef TYDOCAN_DTC_MA_CFG_H
#include "tydocan_evlog_cfg_private.h"
#include "stub.h"           /* Use stubs instead of odo_km.h */
#endif /* #ifdef TYDOCAN_DTC_MA_CFG_H */
#include "veh_opemd.h"

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
#define TYDC_DTC_NUM_TR_EVT                      (3U)                    /* ((Max. of DEM_DemEventDTC_XXXX) + 1) */
#define TYDC_DTC_NUM_PDU_RX                      (1U)
#define TYDC_DTC_NOW_LOG_RX                      (2U)

#ifdef TYDOCAN_DTC_MM_CFG_H
#define TYDC_DTC_MM_NUM_PDU_RX                   (1U)
#endif /* #ifdef TYDOCAN_DTC_MM_CFG_H */
#ifdef TYDOCAN_DTC_MA_CFG_H
#define TYDC_DTC_MA_SYN_TOUT                     (310U)                  /* 3.1 seconds                           */
#define TYDC_DTC_MA_ODO_MIN                      (1000U)                 /* LSB:0.001km = 1.000km                 */
#define TYDC_DTC_MA_ODO_MAX                      (999999999U)            /* LSB:0.001km = 999999.999km            */
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
U1      u1_s_oXDoCANDtcSup_U0100(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1                    u1_g_TYDC_DTC_NOW_TR_ACT = (U1)TYDC_DTC_NOW_TR_ACT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_PDU_RX    st_gp_TYDC_DTC_PDU_RX[] = {
/*   u2_pdu_idx,                    u2_sys_chk,   u2_rx_tout,                   u2_rxc_cyc,                         u2_rxc_min */
    {(U2)0U,                       (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(3600U),   (U2)89U    / (U2)OXDC_MAIN_TICK,    (U2)2U}
};
const U1                    u1_g_TYDC_DTC_NUM_PDU_RX = (U1)TYDC_DTC_NUM_PDU_RX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                    u2_gp_TYDC_DTC_NVMC_LOG_RX[TYDC_DTC_NOW_LOG_RX] = {
    (U2)0,
    (U2)0
};
const U1                    u1_g_TYDC_DTC_NOW_LOG_RX = (U1)TYDC_DTC_NOW_LOG_RX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_COM_RX    st_gp_TYDC_DTC_COM_RX[] = {
/*   fp_u1_SUP,                     u2_smpl_tslot,  u2_dtc_id,                                   u1_pdu_begin, u1_num_pdu, u1_log_bit, u1_log_idx */
    {&u1_s_oXDoCANDtcSup_U0100,    (U2)0x0001U,     DemConf_DemEventParameter_DemEventDTC_U0100,(U1)0U,       (U1)1U,     (U1)14U,    (U1)0U},
};
const U1                    u1_g_TYDC_DTC_NUM_COM_RX = (U1)(sizeof(st_gp_TYDC_DTC_COM_RX) / sizeof(ST_TYDC_DTC_COM_RX));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DTC_TR_CHK    st_gp_TYDC_DTC_TR_CHK[] = {
/*   fp_u1_CHK,                     u2_smpl_tslot,  u2_dtc_id             */
    {&u1_g_oXDoCANDtcTrchk_B1500,   (U2)0x0004U,    (U2)DemConf_DemEventParameter_DemEventDTC_B1500}
};
const U1                    u1_g_TYDC_DTC_NUM_TR_CHK = (U1)(sizeof(st_gp_TYDC_DTC_TR_CHK) / sizeof(ST_TYDC_DTC_TR_CHK));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
    {(U2)OXCAN_PDU_RX_CAN_AVNMS49,  (U2)0x4040U,  u2_OXCAN_RXTO_THRSH(30000U),  (U2)1009U  / (U2)OXDC_MAIN_TICK,    (U2)3U}
};
#if (TYDC_DTC_MM_NUM_PDU_RX > TYDC_DTC_MM_PDU_MAX)
#error "tydocan_dtc_cfg.c : TYDC_DTC_MM_NUM_PDU_RX shall be equal or less than TYDC_DTC_MM_PDU_MAX."
#endif
const U1                    u1_g_TYDC_DTC_MM_NUM_PDU_RX = (U1)TYDC_DTC_MM_NUM_PDU_RX;

const ST_TYDC_DTC_COM_RX    st_gp_TYDC_DTC_MM_RX[TYDC_DTC_MM_NUM_RX] = {
/*   fp_u1_SUP,                     u2_smpl_tslot,  u2_dtc_id,            u1_pdu_begin, u1_num_pdu, u1_log_bit, u1_log_idx */
    {vdp_PTR_NA,                    (U2)0x0002U,    (U2)U2_MAX,           (U1)0U,       (U1)1U,     (U1)0U,     (U1)0U}     /* B1321 */
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
    U4                      u4_t_odo_0p001km;
    U1                      u1_t_odo_stat;
    U1                      u1_t_odo_chk;

    u4_t_odo_0p001km = (U4)0U;
    u1_t_odo_stat    = u1_g_OdoKm(&u4_t_odo_0p001km);    /* [0.001km] */

    if((u1_t_odo_stat    == (U1)ODO_STSBIT_VALID   ) &&
       (u4_t_odo_0p001km >= (U4)TYDC_DTC_MA_ODO_MIN) &&
       (u4_t_odo_0p001km <= (U4)TYDC_DTC_MA_ODO_MAX)){
        u1_t_odo_chk = (U1)TRUE;
    }
    else{
        u1_t_odo_chk = (U1)FALSE;
    }

    return(u1_t_odo_chk);
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* #ifdef TYDOCAN_DTC_MA_CFG_H */

U1      u1_s_oXDoCANDtcSup_U0100(void){return((U1)FALSE);}

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
