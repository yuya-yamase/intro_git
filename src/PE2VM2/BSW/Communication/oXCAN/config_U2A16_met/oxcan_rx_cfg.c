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
#include "veh_opemd.h"

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
static U1      u1_s_oXCANRxeByCh(const U1 u1_a_CH);
#ifdef CXPICDD_H
static U1      u1_s_oXCANCxpRxeByCh(const U1 u1_a_CH);
#endif /* #ifdef CXPICDD_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                    u2_g_OXCAN_RX_POM_TOUT     = (U2)3000U / (U2)OXCAN_MAIN_TICK;    /* 3000 msec    */
const U2                    u2_gp_OXCAN_RX_POM_CHK[OXCAN_RX_NUM_POM] = {
    (U2)OXCAN_RX_SYS_TOE_ACC,                   /* OXCAN_RX_POM_ACC (0U) */
    (U2)OXCAN_RX_SYS_TOE_IGP,                   /* OXCAN_RX_POM_IGP (1U) */
    (U2)OXCAN_RX_SYS_TOE_PBA,                   /* OXCAN_RX_POM_PBA (2U) */
    (U2)OXCAN_RX_SYS_TOE_IGR,                   /* OXCAN_RX_POM_IGR (3U) */
    (U2)OXCAN_RX_SYS_TOE_VDC,                   /* OXCAN_RX_POM_VDC (4U) */
    (U2)OXCAN_RX_SYS_TOE_PTC                    /* OXCAN_RX_POM_PTC (5U) */
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1                    u1_gp_OXCAN_RX_SYS_BY_RX[OXCAN_PDU_NUM_RX] = {

    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [106] MSG_ABG1D50_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [107] MSG_ABG1D51_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [108] MSG_ABG1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [109] MSG_ABG1S04_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [110] MSG_ABG1S09_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [111] MSG_ACN1D50_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [112] MSG_ACN1S03_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [113] MSG_ACN1S04_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [114] MSG_ACN1S05_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [115] MSG_ACN1S07_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [116] MSG_ACN1S15_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [117] MSG_ACN1S16_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [118] MSG_ACN1S22_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [119] MSG_ACN1S25_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [120] MSG_ACN1S29_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [121] MSG_ADC1S06_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [122] MSG_ADC1S13_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [123] MSG_ADC1S14_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [124] MSG_ADC1S17_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [125] MSG_ADC1S19_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [126] MSG_ADC1S20_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [127] MSG_ADC1S23_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [128] MSG_ADC1S27_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [129] MSG_ADC1S30_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [130] MSG_ADC1S31_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [131] MSG_ADU1S02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [132] MSG_ADU1S03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [133] MSG_ADU1S05_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [134] MSG_ADU1S06_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [135] MSG_ADU1S07_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [136] MSG_ADU1S18_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [137] MSG_ADU1S19_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [138] MSG_ADU1S20_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [139] MSG_ADU1S21_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [140] MSG_ADU1S22_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [141] MSG_ADU1S23_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [142] MSG_ADU1S24_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [143] MSG_ADU1S25_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [144] MSG_ADU1S26_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [145] MSG_ADU1S27_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [146] MSG_ADU1S28_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [147] MSG_ARS1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [148] MSG_ARS1S90_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [149] MSG_BAT1E41_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [150] MSG_BAT1E45_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [151] MSG_BAT1ED1_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [152] MSG_BAT1ED4_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [153] MSG_BAT1ED5_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [154] MSG_BAT1EDA_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [155] MSG_BAT1EDB_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [156] MSG_BAT1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [157] MSG_BAT1S08_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [158] MSG_BAT1S11_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [159] MSG_BAT2ED2_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [160] MSG_BCC1S05_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [161] MSG_BCC1S06_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [162] MSG_BDB1F01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [163] MSG_BDB1F02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [164] MSG_BDB1F03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [165] MSG_BDB1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [166] MSG_BDB1S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [167] MSG_BDB1S03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [168] MSG_BDB1S04_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [169] MSG_BDB1S05_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [170] MSG_BDB1S08_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [171] MSG_BDB1S10_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [172] MSG_BDB1S13_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [173] MSG_BDB1S19_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [174] MSG_BDB1S25_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [175] MSG_BDB1S26_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [176] MSG_BDB1S27_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [177] MSG_BDB1S28_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [178] MSG_BDB1S29_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [179] MSG_BDB1S35_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [180] MSG_BDB1S36_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [181] MSG_BDC1S13_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [182] MSG_BDC1S14_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [183] MSG_BDC1S16_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [184] MSG_BDC1S30_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [185] MSG_BDC1S33_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [186] MSG_BDC1S41_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [187] MSG_BDC1S46_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [188] MSG_BDC1S48_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [189] MSG_BDC1S52_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [190] MSG_BDC1S60_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [191] MSG_BDC1S81_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [192] MSG_BDC1S82_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [193] MSG_BDC1S83_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [194] MSG_BDC1S97_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [195] MSG_BDC1S98_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [196] MSG_BDC1S99_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [197] MSG_BDC1SA0_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [198] MSG_BDC1SA1_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [199] MSG_BDC1SC1_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [200] MSG_BDC1SC2_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [201] MSG_BDC1SC3_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [202] MSG_BDC1SC4_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [203] MSG_BDC1SC5_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [204] MSG_BDC1SC6_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [205] MSG_BDC1SC7_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [206] MSG_BDC1SC8_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [207] MSG_BDC1SC9_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [208] MSG_BDC1SD1_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [209] MSG_BDC1SD2_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [210] MSG_BDC1SD3_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [211] MSG_BDC1SD4_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [212] MSG_BDC1SD5_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [213] MSG_BDC1SD6_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [214] MSG_BDC1SD7_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [215] MSG_BDC1SD8_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [216] MSG_BDC1SD9_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [217] MSG_BDC1SE1_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [218] MSG_BDC1SE2_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [219] MSG_BDC1SE3_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [220] MSG_BDC1SE4_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [221] MSG_BDC1SE5_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [222] MSG_BDC1SE6_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [223] MSG_BDC1SE7_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [224] MSG_BDC1SE8_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [225] MSG_BDC1SE9_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [226] MSG_BDC1SF1_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [227] MSG_BDC1SF2_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [228] MSG_BDC1SF3_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [229] MSG_BDC1SF4_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [230] MSG_BDC1SF6_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [231] MSG_BDC1SG4_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [232] MSG_BDC1SG6_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [233] MSG_BDC1SG7_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [234] MSG_BDC1SG8_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [235] MSG_BDC1SG9_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [236] MSG_BDC1SH3_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [237] MSG_BDC1SH4_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [238] MSG_BDC1SH5_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [239] MSG_BDC1SH6_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [240] MSG_BDC1SH8_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [241] MSG_BDC1SV1_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [242] MSG_BDC1SV2_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [243] MSG_BDC1SV3_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [244] MSG_BDF3S01_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [245] MSG_BDF3S02_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [246] MSG_BDR3S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [247] MSG_BKD1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [248] MSG_BKD1S02_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [249] MSG_BSR1S01_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [250] MSG_BSR1S02_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [251] MSG_BSR1S03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [252] MSG_CDC1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [253] MSG_CMB1S03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [254] MSG_CMB1S04_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [255] MSG_CSR1G10_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [256] MSG_CSR1S04_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [257] MSG_CSR1S07_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [258] MSG_CSR1S08_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [259] MSG_DCM1S01_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [260] MSG_DCM1S03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [261] MSG_DCM1S04_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [262] MSG_DCM1S08_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [263] MSG_DDM1S00_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [264] MSG_DDM1S09_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [265] MSG_DDM1S12_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [266] MSG_DDM1S16_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [267] MSG_DDM1S17_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [268] MSG_DDM1S20_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [269] MSG_DDM1S32_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [270] MSG_DDM1S35_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [271] MSG_DDM1SFG_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [272] MSG_DDM1SFH_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [273] MSG_DKY1S26_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [274] MSG_DRL1S03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [275] MSG_DRR1S03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [276] MSG_DS11S27_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [277] MSG_DS11S37_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [278] MSG_DS11S40_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [279] MSG_DS12F02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [280] MSG_DS12F03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [281] MSG_DST1S02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [282] MSG_EBU1D01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [283] MSG_ECT1G01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [284] MSG_ECT1G92_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [285] MSG_ECT1S93_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [286] MSG_EHV1E96_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [287] MSG_EHV1F02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [288] MSG_EHV1F04_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [289] MSG_EHV1G30_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [290] MSG_EHV1G70_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [291] MSG_EHV1G71_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [292] MSG_EHV1S23_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [293] MSG_EHV1S26_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [294] MSG_EHV1S31_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [295] MSG_EHV1S90_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [296] MSG_EHV1S94_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [297] MSG_EHV1S95_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [298] MSG_EHV1S96_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [299] MSG_EHV1S97_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [300] MSG_EHV1S99_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [301] MSG_EHV1SL2_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [302] MSG_EHV2G02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [303] MSG_EHV2G10_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [304] MSG_EHV2G20_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [305] MSG_EIM1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [306] MSG_ENG1C01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [307] MSG_ENG1C02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [308] MSG_ENG1D51_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [309] MSG_ENG1D52_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [310] MSG_ENG1D53_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [311] MSG_ENG1D55_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [312] MSG_ENG1D56_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [313] MSG_ENG1D59_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [314] MSG_ENG1D60_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [315] MSG_ENG1G03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [316] MSG_ENG1G13_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [317] MSG_ENG1G90_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [318] MSG_ENG1G92_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [319] MSG_ENG1S51_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [320] MSG_ENG1S60_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [321] MSG_ENG1S99_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [322] MSG_EPS1D50_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [323] MSG_EPS1S11_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [324] MSG_EPS1S90_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [325] MSG_FCM1C01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [326] MSG_FCM1C03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [327] MSG_FCM1S10_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [328] MSG_FCM1S12_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [329] MSG_FCM1S39_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [330] MSG_FCM1S40_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [331] MSG_FCM1S41_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [332] MSG_FCM1S49_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [333] MSG_FCM1S51_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [334] MSG_FCM1S52_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [335] MSG_FCM1S58_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [336] MSG_FCM1S66_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [337] MSG_FCM1S70_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [338] MSG_FCM1S76_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [339] MSG_FCM1S78_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [340] MSG_FCM1S79_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [341] MSG_FCM1S88_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [342] MSG_FCM1S90_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [343] MSG_FCM1S92_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [344] MSG_FCM1S95_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                        /* [345] MSG_FWD1S10_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [346] MSG_IDT1S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [347] MSG_IDT1S07_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [348] MSG_IDT1S08_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [349] MSG_IDT1S15_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [350] MSG_IPA1S05_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [351] MSG_ITS1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [352] MSG_ITS1S04_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [353] MSG_ITS1S05_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [354] MSG_ITS1S08_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [355] MSG_LVN1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [356] MSG_MET1S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [357] MSG_MET1S33_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [358] MSG_MET1S38_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [359] MSG_MET1S47_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [360] MSG_MET1S55_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [361] MSG_MGC1F13_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [362] MSG_PCN1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [363] MSG_PDC1G01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [364] MSG_PDC1G02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [365] MSG_PDS1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [366] MSG_PLG1G15_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [367] MSG_PLG1G16_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [368] MSG_PLG1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [369] MSG_PLG1S06_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [370] MSG_PLG1S20_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [371] MSG_PLG1S21_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [372] MSG_PMN1G03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [373] MSG_PST1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [374] MSG_PST1S02_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [375] MSG_PWC1S41_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [376] MSG_RCP1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [377] MSG_RCP1S02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [378] MSG_RCP1S03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [379] MSG_RSE1G20_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [380] MSG_RSE1G24_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [381] MSG_RSE1G25_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [382] MSG_RSE1G26_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [383] MSG_RSE1G29_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [384] MSG_RSE1S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [385] MSG_RST1S03_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [386] MSG_SBW1G02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [387] MSG_SCN1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [388] MSG_SCN1S02_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [389] MSG_SCS1S10_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [390] MSG_SCS1S11_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [391] MSG_SCS1S14_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [392] MSG_SOL1S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [393] MSG_SOL1S03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [394] MSG_SOL1S04_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [395] MSG_SOL1S05_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [396] MSG_SOL1S06_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [397] MSG_TPM1S02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [398] MSG_TPM1S03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [399] MSG_TPM1S04_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [400] MSG_TPM1S05_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [401] MSG_TPM1S06_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [402] MSG_TPM1S07_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [403] MSG_TPM1S08_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [404] MSG_TPM1S09_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [405] MSG_TPM1S10_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [406] MSG_TPM1S11_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [407] MSG_TPM1S12_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [408] MSG_TRA1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [409] MSG_TRA1S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [410] MSG_UCB1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [411] MSG_VAS1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [412] MSG_VGR1D50_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [413] MSG_VSC1D51_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [414] MSG_VSC1F01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [415] MSG_VSC1G12_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [416] MSG_VSC1G13_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [417] MSG_VSC1G14_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [418] MSG_VSC1G96_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [419] MSG_VUM1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [420] MSG_WIP1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [421] MSG_YGW1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [422] MSG_ZN11S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [423] MSG_ZN11S03_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [424] MSG_ZN11S08_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [425] MSG_ZN11S14_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [426] MSG_ZN11S17_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [427] MSG_ZN11S19_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [428] MSG_ZN11S25_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [429] MSG_ZN11S26_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [430] MSG_ZN11S32_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                                           /* [431] MSG_ZN11S38_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [432] MSG_ZN11S60_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [433] MSG_ZN11S63_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [434] MSG_ZN11S64_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [435] MSG_ZN11S65_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [436] MSG_ZN11S66_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [437] MSG_ZN11S67_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [438] MSG_ZN11SF6_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [439] MSG_ZN11SF7_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [440] MSG_ZN11SF8_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR)),                             /* [441] MSG_ZN11SF9_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [442] MSG_ZN21S05_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [443] MSG_ZN21S13_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR)), /* [444] MSG_ZN21S28_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR))  /* [445] MSG_ZN21S72_RXCH0 */
};
const U2                    u2_g_OXCAN_RX_NUM_RX       = (U2)OXCAN_PDU_NUM_RX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2             u2_sp_OXCAN_RX_BY_RX_0[] = {
    (U2)OXCAN_PDU_RX_CAN_ABG1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S22_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S19_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S30_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S31_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S18_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S19_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S21_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S22_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S24_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S28_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ARS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ARS1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1E41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1E45_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1EDA_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1EDB_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT2ED2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BCC1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BCC1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1F01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1F02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1F03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S19_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S28_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S35_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S36_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S30_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S33_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S46_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S48_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S52_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S81_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S82_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S83_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S97_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S98_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S99_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SA0_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SA1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC7_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC9_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD7_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD9_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE7_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE9_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SF1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SF2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SF3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SF4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SF6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SG4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SG6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SG7_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SG8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SG9_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SV1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SV2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SV3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDR3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BKD1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BKD1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CDC1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1G10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DCM1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DCM1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DCM1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DCM1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S00_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S32_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S35_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFG_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFH_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DKY1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DRL1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DRR1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS11S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS11S37_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS11S40_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS12F02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DST1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EBU1D01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ECT1G01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ECT1G92_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ECT1S93_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1E96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1F02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1F04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1G30_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1G70_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1G71_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S31_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S94_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S95_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S97_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S99_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1SL2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G02_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_ENG1G03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1G13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1G90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1G92_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1C01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1C03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S39_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S40_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S49_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S58_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S66_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S70_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S76_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S78_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S79_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S88_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S92_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S95_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FWD1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IPA1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_LVN1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MET1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MET1S33_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MET1S38_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MET1S47_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MET1S55_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MGC1F13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PDC1G01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PDC1G02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PDS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1G15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1G16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1S20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1S21_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PMN1G03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PST1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PST1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PWC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G24_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RST1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SBW1G02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCN1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCN1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TRA1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TRA1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_UCB1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VAS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VGR1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1F01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1G12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1G13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1G14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1G96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VUM1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_WIP1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_YGW1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S32_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S38_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S63_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S64_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S65_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S66_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S67_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF7_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF9_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN21S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN21S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN21S28_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN21S72_RXCH0
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2             u2_sp_OXCAN_RX_BY_CH_0[] = {
    (U2)OXCAN_PDU_RX_CAN_ABG1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S22_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S19_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S30_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S31_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S18_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S19_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S21_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S22_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S24_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S28_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ARS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ARS1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1E41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1E45_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1ED5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1EDA_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1EDB_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BAT2ED2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BCC1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BCC1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1F01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1F02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1F03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S19_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S28_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S35_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S36_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S30_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S33_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S46_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S48_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S52_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S81_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S82_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S83_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S97_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S98_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S99_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SA0_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SA1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC7_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SC9_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD7_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SD9_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE7_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SE9_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SF1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SF2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SF3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SF4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SF6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SG4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SG6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SG7_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SG8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SG9_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH4_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH5_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SV1_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SV2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SV3_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDR3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BKD1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BKD1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CDC1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1G10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DCM1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DCM1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DCM1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DCM1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S00_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S32_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S35_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFG_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFH_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DKY1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DRL1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DRR1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS11S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS11S37_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS11S40_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS12F02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DST1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EBU1D01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ECT1G01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ECT1G92_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ECT1S93_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1E96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1F02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1F04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1G30_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1G70_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1G71_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S31_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S94_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S95_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S97_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S99_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1SL2_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G02_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_ENG1G03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1G13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1G90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1G92_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1C01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1C03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S39_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S40_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S49_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S58_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S66_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S70_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S76_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S78_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S79_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S88_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S92_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S95_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FWD1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IPA1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_LVN1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MET1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MET1S33_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MET1S38_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MET1S47_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MET1S55_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_MGC1F13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PDC1G01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PDC1G02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PDS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1G15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1G16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1S20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PLG1S21_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PMN1G03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PST1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PST1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_PWC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G24_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RST1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SBW1G02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCN1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCN1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TRA1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TRA1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_UCB1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VAS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VGR1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1F01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1G12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1G13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1G14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VSC1G96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_VUM1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_WIP1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_YGW1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S32_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S38_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S63_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S64_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S65_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S66_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S67_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF6_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF7_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11SF9_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN21S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN21S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN21S28_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN21S72_RXCH0
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/

const ST_OXCAN_RX_CH        st_gp_OXCAN_RX_BY_CH[OXCAN_NUM_CH] = {
    {
        &u1_s_oXCANRxeByCh,                                  /* fp_u1_RX_EN   */

        &u2_sp_OXCAN_RX_BY_RX_0[0],                          /* u2p_PDU_BY_RX */
        &u2_sp_OXCAN_RX_BY_CH_0[0],                          /* u2p_PDU_BY_CH */

        (U2)MSG_ABG1D50_RXCH0,                               /* u2_msg_min    */
        (U2)MSG_ZN21S72_RXCH0,                               /* u2_msg_max    */
        (U2)(sizeof(u2_sp_OXCAN_RX_BY_CH_0) >> 1U),          /* u2_num_rx     */
        (U2)OXCAN_SYS_BAT                                    /* u2_sys_en     */
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
    return((U2)0U);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXCANRxeByCh(const U1 u1_a_CH)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXCANRxeByCh(const U1 u1_a_CH)
{
    return(u1_g_VehopemdNmAwk());
}
/*===================================================================================================================================*/

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
