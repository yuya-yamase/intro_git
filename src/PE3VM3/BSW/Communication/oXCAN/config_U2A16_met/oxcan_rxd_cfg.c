/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of CAN : Rx Detection                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_RXD_CFG_C_MAJOR                    (2U)
#define OXCAN_RXD_CFG_C_MINOR                    (0U)
#define OXCAN_RXD_CFG_C_PATCH                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_rxd_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_RXD_CFG_C_MAJOR != OXCAN_RXD_CFG_H_MAJOR) || \
     (OXCAN_RXD_CFG_C_MINOR != OXCAN_RXD_CFG_H_MINOR) || \
     (OXCAN_RXD_CFG_C_PATCH != OXCAN_RXD_CFG_H_PATCH))
#error "oxcan_rxd_cfg.c and oxcan_rxd_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_RXD_NUM_POM                        (9U)
/* #define OXCAN_RX_POM_BAT                           */
/* #define OXCAN_RX_POM_ACC                      (0U) */
/* #define OXCAN_RX_POM_IGP                      (1U) */
/* #define OXCAN_RX_POM_PBA                           */
/* #define OXCAN_RX_POM_IGR                      (2U) */
/* #define OXCAN_RX_POM_VDC                      (3U) */
/* #define OXCAN_RX_POM_PTC                      (4U) */

/* #define OXCAN_RX_POM_PNC_16                   (5U) */
/* #define OXCAN_RX_POM_PNC_40                   (6U) */
/* #define OXCAN_RX_POM_PNC_43                   (7U) */
/* #define OXCAN_RX_POM_PNC_44                   (8U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_LIB_CFG_EN_RXD == 1U) || (OXCAN_LIB_CFG_EN_RXD == 2U))
#else
#error "oxcan_rxd_cfg.c : OXCAN_LIB_CFG_EN_RXD shall be equal to 1U or 2U."
#endif /* #if ((OXCAN_LIB_CFG_EN_RXD == 1U) || (OXCAN_LIB_CFG_EN_RXD == 2U)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
ST_OXCAN_RXD_ST             st_gp_oxcan_rxd_pdu_st[OXCAN_RXD_NUM_PDU];
U4                          u4_gp_oxcan_rxd_pom_elpsd[OXCAN_RXD_NUM_POM];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4                    u4_g_OXCAN_RXD_SYS_NET  = (U4)OXCAN_SYS_NET;                 /* OXCAN_SYS_NET defined in oxcan_sys_def.h */
const U2                    u2_g_OXCAN_RXD_POM_TOUT = (U2)3000U / (U2)OXCAN_MAIN_TICK;   /* 3000 msec                                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4                    u4_gp_OXCAN_RXD_SYS_BY_POM[OXCAN_RXD_NUM_POM] = {
 /* (U4)OXCAN_SYS_BAT, */
    (U4)OXCAN_SYS_ACC,
    (U4)OXCAN_SYS_IGP,
 /* (U4)OXCAN_SYS_PBA, */
    (U4)OXCAN_SYS_IGR,
    (U4)OXCAN_SYS_VDC,
    (U4)OXCAN_SYS_PTC, 

    (U4)OXCAN_SYS_PNC_16,
    (U4)OXCAN_SYS_PNC_40,
    (U4)OXCAN_SYS_PNC_43,
    (U4)OXCAN_SYS_PNC_44
};
const U1                    u1_g_OXCAN_RXD_NUM_POM = (U1)OXCAN_RXD_NUM_POM;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4                    u4_gp_OXCAN_RXD_SYS_BY_PDU[] = {
/* #define OXCAN_SYS_ACC                            (0x00000002U) */
/* #define OXCAN_SYS_IGP                            (0x00000004U) */
/* #define OXCAN_SYS_PBA                            (0x00000008U) */
/* #define OXCAN_SYS_IGR                            (0x00000010U) */

/* #define OXCAN_SYS_PNC_16                         (0x00010000U) */
/* #define OXCAN_SYS_PNC_40                         (0x00020000U) */
/* #define OXCAN_SYS_PNC_43                         (0x00040000U) */
/* #define OXCAN_SYS_PNC_44                         (0x00080000U) */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [  0] MSG_ABG1D50_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [  1] MSG_ABG1D51_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [  2] MSG_ABG1S09_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [  3] MSG_ACN1D50_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [  4] MSG_ACN1S03_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [  5] MSG_ACN1S15_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [  6] MSG_ACN1S25_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [  7] MSG_ACN1S29_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [  8] MSG_ADC1S27_RXCH0   */
    (U4)0x00050016U,  /* IGR, IGP, ACC, PNC_16,         PNC_43,         */ /* [  9] MSG_ADC1S30_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 10] MSG_ADC1S31_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 11] MSG_ADU1S03_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 12] MSG_ADU1S05_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 13] MSG_ADU1S06_RXCH0   */
    (U4)0x000F0016U,  /* IGR, IGP, ACC, PNC_16, PNC_40, PNC_43, PNC_44  */ /* [ 14] MSG_AVN1S95_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 15] MSG_BAT1E45_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 16] MSG_BAT1EDA_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 17] MSG_BAT1S08_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 18] MSG_BAT2ED2_RXCH0   */
    (U4)0x00010016U,  /* IGR, IGP, ACC, PNC_16,                         */ /* [ 19] MSG_BDB1F03_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 20] MSG_BDB1S10_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 21] MSG_BDC1S41_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 22] MSG_BDC1S81_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 23] MSG_BDC1S82_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 24] MSG_BDC1S91_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 25] MSG_BDC1SH8_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 26] MSG_BDC1SI1_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 27] MSG_BDC1SI2_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 28] MSG_BDC1SI3_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 29] MSG_BDC1SI4_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 30] MSG_BDC1SI5_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 31] MSG_BDC1SI6_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 32] MSG_BDC1SI7_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 33] MSG_BDC1SI8_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 34] MSG_BDC1SI9_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 35] MSG_BDC1SJ0_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 36] MSG_BDC1SJ1_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 37] MSG_BDC1SJ2_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 38] MSG_BDF3S01_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 39] MSG_BDF3S02_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 40] MSG_BDR3S02_RXCH0   */
    (U4)0x000F0016U,  /* IGR, IGP, ACC, PNC_16, PNC_40, PNC_43, PNC_44  */ /* [ 41] MSG_CDC1S04_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 42] MSG_CMB1S03_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 43] MSG_CMB1S04_RXCH0   */
    (U4)0x00010016U,  /* IGR, IGP, ACC, PNC_16,                         */ /* [ 44] MSG_DCM1S08_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 45] MSG_DDM1S00_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 46] MSG_DDM1S09_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 47] MSG_DDM1S16_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 48] MSG_DDM1S35_RXCH0   */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                 */ /* [ 49] MSG_DDM1SFH_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 50] MSG_DKY1S26_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 51] MSG_DS11S27_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 52] MSG_EBU1D01_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 53] MSG_ECT1S93_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 54] MSG_EHV1E96_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 55] MSG_EHV1F02_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 56] MSG_EHV1S23_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 57] MSG_EHV2G10_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 58] MSG_EHV2G20_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 59] MSG_EIM1S01_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 60] MSG_ENG1C01_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 61] MSG_ENG1C02_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 62] MSG_ENG1D51_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 63] MSG_ENG1D52_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 64] MSG_ENG1D53_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 65] MSG_ENG1D55_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 66] MSG_ENG1D56_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 67] MSG_ENG1D59_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 68] MSG_ENG1D60_RXCH0   */
    (U4)0x00000004U,  /*      IGP,                                      */ /* [ 69] MSG_ENG1S51_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 70] MSG_EPS1D50_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 71] MSG_FCM1C01_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 72] MSG_FCM1S49_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 73] MSG_FCM1S76_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 74] MSG_FCM1S79_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 75] MSG_FCM1S90_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 76] MSG_FCM1S95_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 77] MSG_IDT1S07_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 78] MSG_IDT1S15_RXCH0   */
    (U4)0x000F0016U,  /* IGR, IGP, ACC, PNC_16, PNC_40, PNC_43, PNC_44  */ /* [ 79] MSG_MET1S02_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 80] MSG_MGC1F13_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 81] MSG_PDC1G01_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 82] MSG_RCP1S03_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 83] MSG_RCP1S04_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 84] MSG_RCP1S05_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 85] MSG_RCP1S06_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 86] MSG_RSE1G20_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 87] MSG_RSE1G24_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 88] MSG_RSE1G25_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 89] MSG_RSE1G26_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 90] MSG_RSE1S02_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 91] MSG_VGR1D50_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 92] MSG_VSC1D51_RXCH0   */
    (U4)0x00000014U,  /* IGR, IGP,                                      */ /* [ 93] MSG_VSC1G13_RXCH0   */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44  */ /* [ 94] MSG_WIP1S01_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 95] MSG_ZN11S08_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 96] MSG_ZN11S63_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 97] MSG_ZN11S64_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 98] MSG_ZN11S65_RXCH0   */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                 */ /* [ 99] MSG_ZN11S66_RXCH0   */
    (U4)0x00000016U   /* IGR, IGP, ACC,                                 */ /* [100] MSG_ZN11S67_RXCH0   */
};
const U2                    u2_g_OXCAN_RXD_NUM_PDU = (U2)OXCAN_RXD_NUM_PDU;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2             u2_sp_OXCAN_RXD_BY_ACK[] = {
    (U2)OXCAN_RXD_PDU_CAN_ABG1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ABG1D51_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ABG1S09_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S15_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S25_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S29_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S27_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S30_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S31_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S06_CH0,
    (U2)OXCAN_RXD_PDU_CAN_AVN1S95_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1E45_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1EDA_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT2ED2_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1F03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S41_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S81_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S82_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S91_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SH8_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SI1_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SI2_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SI3_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SI4_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SI5_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SI6_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SI7_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SI8_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SI9_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SJ0_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SJ1_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SJ2_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDF3S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDF3S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDR3S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CDC1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CMB1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CMB1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DCM1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S00_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S09_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S16_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S35_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1SFH_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DKY1S26_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DS11S27_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EBU1D01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ECT1S93_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1E96_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1F02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S23_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV2G10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV2G20_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EIM1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1C01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1C02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1D51_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1D52_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1D53_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1D55_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1D56_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1D59_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1D60_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1S51_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EPS1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1C01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S49_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S76_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S79_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S90_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S95_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IDT1S07_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IDT1S15_CH0,
    (U2)OXCAN_RXD_PDU_CAN_MET1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_MGC1F13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PDC1G01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RCP1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RCP1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RCP1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RCP1S06_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RSE1G20_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RSE1G24_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RSE1G25_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RSE1G26_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RSE1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VGR1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VSC1D51_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VSC1G13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_WIP1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S63_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S64_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S65_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S66_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S67_CH0
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_OXCAN_RXD_ACK      st_gp_OXCAN_RXD_ACK_BY_GR[OXCAN_RXD_NUM_GR] = {
    {
        &u2_sp_OXCAN_RXD_BY_ACK[0],    /* u2p_RXD_BY_ACK */
        (U2)MSG_ABG1D50_RXCH0,         /* u2_ack_min     */
        (U2)MSG_ZN11S67_RXCH0          /* u2_ack_max     */
    }
};
const U1                    u1_g_OXCAN_RXD_NUM_GR = (U1)OXCAN_RXD_NUM_GR;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     2/28/2025  TN       oxcan_rx v1.0.7 -> oxcan_rxd v2.0.0.                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
