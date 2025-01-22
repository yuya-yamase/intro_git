/* 1.0.7 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN Rx                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_RX_CFG_C_MAJOR                     (1U)
#define OXCAN_RX_CFG_C_MINOR                     (0U)
#define OXCAN_RX_CFG_C_PATCH                     (7U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_rx_cfg_private.h"

#include "iohw_diflt.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_RX_CFG_C_MAJOR != OXCAN_RX_CFG_H_MAJOR) || \
     (OXCAN_RX_CFG_C_MINOR != OXCAN_RX_CFG_H_MINOR) || \
     (OXCAN_RX_CFG_C_PATCH != OXCAN_RX_CFG_H_PATCH))
#error "oxcan_rx_cfg.c and oxcan_rx_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
ST_OXCAN_RX_ST              st_gp_oxcan_rx_pdu_st[OXCAN_PDU_NUM_RX];
U2                          u2_gp_oxcan_rx_nwk_elpsd[OXCAN_NUM_CH];
U2                          u2_gp_oxcan_rx_toe_chk[OXCAN_NUM_CH];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef CXPICDD_H
static U1      u1_s_oXCANCxpRxeByCh(const U1 u1_a_CH);
#endif /* #ifdef CXPICDD_H */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                    u2_g_OXCAN_RX_POM_TOUT     = (U2)3000U / (U2)OXCAN_MAIN_TICK;    /* 3000 msec    */
const U2                    u2_sp_OXCAN_RX_POM_CHK[OXCAN_RX_NUM_POM] = {
    (U2)OXCAN_RX_SYS_TOE_ACC,                   /* OXCAN_RX_POM_ACC (0U) */
    (U2)OXCAN_RX_SYS_TOE_IGP,                   /* OXCAN_RX_POM_IGP (1U) */
    (U2)OXCAN_RX_SYS_TOE_PBA,                   /* OXCAN_RX_POM_PBA (2U) */
    (U2)OXCAN_RX_SYS_TOE_IGR,                   /* OXCAN_RX_POM_IGR (3U) */
    (U2)OXCAN_RX_SYS_TOE_VDC,                   /* OXCAN_RX_POM_VDC (4U) */
    (U2)OXCAN_RX_SYS_TOE_PTC                    /* OXCAN_RX_POM_PTC (5U) */
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1                    u1_gp_OXCAN_RX_SYS_BY_RX[OXCAN_PDU_NUM_RX] = {
     ( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_IGP )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
    ,( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )
};
const U2                    u2_g_OXCAN_RX_NUM_RX       = (U2)OXCAN_PDU_NUM_RX;

#define OXCAN_RX_CH_POWSUPPLY  (BSW_COMM_PWSTAT_BAT|BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_PBA|ComMConf_SysStatusName_IGR|ComMConf_SysStatusName_Special)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2             u2_sp_OXCAN_RX_BY_RX_0[] = {
    (U2)OXCAN_PDU_RX_CAN_ABG1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S30_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S31_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1E45_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1EDA_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1EDB_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT2ED2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1F03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S22_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S81_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDR3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DCM1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S00_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S35_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFG_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFH_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DKY1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS11S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EBU1D01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ECT1S93_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1E96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1F02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EIM1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1C01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1C02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D52_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D53_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D55_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D56_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D59_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1C01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S49_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S76_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S79_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S95_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_LRS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_LRS1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_LRS1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MGC1F13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PDC1G01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PWC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RRS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RRS1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RRS1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G24_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VGR1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1G13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_WIP1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S32_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S63_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S64_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S65_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S66_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S67_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF7_RXCH0
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2             u2_sp_OXCAN_RX_BY_CH_0[] = {
    (U2)OXCAN_PDU_RX_CAN_ABG1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S30_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S31_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1E45_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1EDA_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1EDB_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT2ED2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1F03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S22_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S81_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDR3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DCM1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S00_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S35_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFG_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFH_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DKY1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS11S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EBU1D01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ECT1S93_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1E96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1F02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EIM1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1C01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1C02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D52_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D53_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D55_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D56_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D59_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1D60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1C01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S49_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S76_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S79_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S95_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_LRS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_LRS1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_LRS1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MGC1F13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PDC1G01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PWC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RRS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RRS1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RRS1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G24_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VGR1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1G13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_WIP1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S32_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S63_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S64_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S65_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S66_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S67_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF7_RXCH0
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/

const ST_OXCAN_RX_CH        st_gp_OXCAN_RX_BY_CH[OXCAN_NUM_CH] = {
    {
        &u1_g_oXCANNmwkRxeByCh,                              /* fp_u1_RX_EN   */

        &u2_sp_OXCAN_RX_BY_RX_0[0],                          /* u2p_PDU_BY_RX */
        &u2_sp_OXCAN_RX_BY_CH_0[0],                          /* u2p_PDU_BY_CH */

        (U2)MSG_ABG1D50_RXCH0,                               /* u2_msg_min    */
        (U2)MSG_ZN11SF7_RXCH0,                               /* u2_msg_max    */
        (U2)(sizeof(u2_sp_OXCAN_RX_BY_CH_0) >> 1U),          /* u2_num_rx     */
        (U2)OXCAN_RX_CH_POWSUPPLY                            /* u2_sys_en     */
    }
};
const U1                    u1_g_OXCAN_RX_NUM_CH = (U1)OXCAN_NUM_CH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U2      u2_g_oXCANRxCfgSysXgrOn(const U2 u2_a_SYS_CHK)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_oXCANRxCfgSysXgrOn(const U2 u2_a_SYS_CHK)
{
#if (defined(MSG_ENG1G92_RXCH0) && defined(ComConf_ComSignal_B_ST))
    U2                     u2_t_ign_on;
    U2                     u2_t_xgr_on;
    U1                     u1_t_rx_stat;
    U1                     u1_t_b_st;

    /* ------------------------------------------------------------------------------------ */
    /* Attention :                                                                          */
    /* ------------------------------------------------------------------------------------ */
    /* CAN Rx signal "B_ST" is intentionally tested at here in order to keep the consitency */
    /* between telltale and diag trouble code.                                              */
    /* ------------------------------------------------------------------------------------ */
    u1_t_b_st    = (U1)0U;
    u1_t_rx_stat = Com_GetIPDUStatus(MSG_ENG1G92_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_ST, &u1_t_b_st);
    if(u1_t_rx_stat != (U1)0U){
        u1_t_b_st = (U1)0U;
    }

    u2_t_ign_on = u2_a_SYS_CHK & ((U2)OXCAN_SYS_IGR | (U2)OXCAN_SYS_IGP);
/*    u2_t_xgr_on = (U2)u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_IGN_10V);*/
    u2_t_xgr_on = (U2)IOHW_DIFLT_SWITCH_ACT;
    if((u2_t_ign_on <  (U2)OXCAN_SYS_IGR        ) ||
       (u1_t_b_st   != (U1)0U                   ) ||
       (u2_t_xgr_on != (U2)IOHW_DIFLT_SWITCH_ACT)){

        u2_t_xgr_on = (U2)0x0000U;
    }
    else if(u2_t_ign_on == ((U2)OXCAN_SYS_IGR | (U2)OXCAN_SYS_IGP)){
        u2_t_xgr_on = (U2)OXCAN_RX_SYS_NRX_VDC | (U2)OXCAN_RX_SYS_NRX_PTC;
    }
    else{
        u2_t_xgr_on = (U2)OXCAN_RX_SYS_NRX_VDC;
    }

    return(u2_t_xgr_on);
#else /* #if (defined(MSG_ENG1G92_RXCH0) && defined(ComConf_ComSignal_B_ST)) */
    U2                     u2_t_ign_on;
    U2                     u2_t_xgr_on;

    u2_t_ign_on = u2_a_SYS_CHK & ((U2)OXCAN_SYS_IGR | (U2)OXCAN_SYS_IGP);
/*     u2_t_xgr_on = (U2)u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_IGN_10V); */
    u2_t_xgr_on = (U2)IOHW_DIFLT_SWITCH_ACT;
    if((u2_t_ign_on <  (U2)OXCAN_SYS_IGR        ) ||
       (u2_t_xgr_on != (U2)IOHW_DIFLT_SWITCH_ACT)){

        u2_t_xgr_on = (U2)0x0000U;
    }
    else if(u2_t_ign_on == ((U2)OXCAN_SYS_IGR | (U2)OXCAN_SYS_IGP)){
        u2_t_xgr_on = (U2)OXCAN_RX_SYS_NRX_VDC | (U2)OXCAN_RX_SYS_NRX_PTC;
    }
    else{
        u2_t_xgr_on = (U2)OXCAN_RX_SYS_NRX_VDC;
    }

    return(u2_t_xgr_on);
#endif /* #if (defined(MSG_ENG1G92_RXCH0) && defined(ComConf_ComSignal_B_ST)) */
}
#ifdef CXPICDD_H
/*===================================================================================================================================*/
/*  static U1      u1_s_oXCANCxpRxeByCh(const U1 u1_a_CH)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXCANCxpRxeByCh(const U1 u1_a_CH)
{
   U1                     u1_t_rxe;

   if(CxpiCdd_CxpiNmStsIsOpe0()){
       u1_t_rxe = (U1)TRUE;
   }
   else{
       u1_t_rxe = (U1)FALSE;
   }

   return(u1_t_rxe);
}
#endif /* #ifdef CXPICDD_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/22/2022  HU       ty19epf_ren_d1x_v220_r009 -> ox25epf_ren_d1x_v100_r000.                                            */
/*  1.0.1     9/27/2022  TM       Fixed QAC issue.                                                                                   */
/*  1.0.2    11/16/2022  HU       oxcan_rx v1.0.1 -> v1.0.2                                                                          */
/*  1.0.3    12/13/2022  TM       oxcan_rx v1.0.2 -> v1.0.3                                                                          */
/*  1.0.4     1/25/2023  TM       oxcan_rx v1.0.3 -> v1.0.4                                                                          */
/*  1.0.5     5/10/2023  HU       oxcan_rx v1.0.4 -> v1.0.5                                                                          */
/*  1.0.6     1/31/2024  TI       oxcan_rx v1.0.5 -> v1.0.6                                                                          */
/*  1.0.7     2/08/2024  AM       oxcan_rx v1.0.6 -> v1.0.7                                                                          */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * HU   = Hayato Usui, DENSO                                                                                                      */
/*  * TM   = Takanori Maruyama, DENSO                                                                                                */
/*  * TI   = Tomoko Inuzuka, DENSO                                                                                                   */
/*  * AM   = Atsushi Mizutani, DENSO                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
