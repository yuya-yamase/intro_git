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
#if (OXCAN_LIB_CFG_EN_RXD == 1U)
#else
#error "oxcan_rxd_cfg.c : OXCAN_LIB_CFG_EN_RXD is NOT equal to 1U."
#endif /* #if (OXCAN_LIB_CFG_EN_RXD == 1U) */

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
const U2                    u2_g_OXCAN_RXD_POM_TOUT = (U2)3000U / (U2)OXCAN_MAIN_TICK;    /* 3000 msec    */

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
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [102]    MSG_ABG1D50_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [103]    MSG_ABG1D51_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [104]    MSG_ABG1S01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [105]    MSG_ABG1S04_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [106]    MSG_ABG1S09_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [107]    MSG_ACN1D50_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [108]    MSG_ACN1S03_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [109]    MSG_ACN1S04_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [110]    MSG_ACN1S05_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [111]    MSG_ACN1S07_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [112]    MSG_ACN1S15_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [113]    MSG_ACN1S16_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [114]    MSG_ACN1S22_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [115]    MSG_ACN1S25_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [116]    MSG_ACN1S29_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [117]    MSG_ADC1S06_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [118]    MSG_ADC1S13_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [119]    MSG_ADC1S14_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [120]    MSG_ADC1S15_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [121]    MSG_ADC1S17_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [122]    MSG_ADC1S19_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [123]    MSG_ADC1S20_RXCH0  */
    (U4)0x00050016U,  /* IGR, IGP, ACC, PNC_16,         PNC_43,        */    /* [124]    MSG_ADC1S23_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [125]    MSG_ADC1S27_RXCH0  */
    (U4)0x00050016U,  /* IGR, IGP, ACC, PNC_16,         PNC_43,        */    /* [126]    MSG_ADC1S30_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [127]    MSG_ADC1S31_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [128]    MSG_ADU1S02_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [129]    MSG_ADU1S03_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [130]    MSG_ADU1S05_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [131]    MSG_ADU1S06_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [132]    MSG_ADU1S07_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [133]    MSG_ADU1S18_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [134]    MSG_ADU1S19_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [135]    MSG_ADU1S20_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [136]    MSG_ADU1S21_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [137]    MSG_ADU1S22_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [138]    MSG_ADU1S23_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [139]    MSG_ADU1S24_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [140]    MSG_ADU1S25_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [141]    MSG_ADU1S26_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [142]    MSG_ADU1S27_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [143]    MSG_ADU1S28_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [144]    MSG_ARS1S01_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC,    PNC_16, PNC_40,             */    /* [145]    MSG_ARS1S90_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC,    PNC_16, PNC_40,             */    /* [146]    MSG_BAT1E41_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [147]    MSG_BAT1E45_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [148]    MSG_BAT1ED1_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [149]    MSG_BAT1ED5_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [150]    MSG_BAT1EDA_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [151]    MSG_BAT1EDB_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC,    PNC_16, PNC_40,             */    /* [152]    MSG_BAT1S01_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [153]    MSG_BAT1S08_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [154]    MSG_BAT1S11_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [155]    MSG_BAT2ED2_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [156]    MSG_BCC1S05_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [157]    MSG_BCC1S06_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [158]    MSG_BDB1F01_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [159]    MSG_BDB1F02_RXCH0  */
    (U4)0x00010016U,  /* IGR, IGP, ACC, PNC_16,                        */    /* [160]    MSG_BDB1F03_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [161]    MSG_BDB1S01_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [162]    MSG_BDB1S02_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [163]    MSG_BDB1S03_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [164]    MSG_BDB1S04_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [165]    MSG_BDB1S05_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [166]    MSG_BDB1S08_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [167]    MSG_BDB1S10_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [168]    MSG_BDB1S13_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [169]    MSG_BDB1S19_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [170]    MSG_BDB1S25_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [171]    MSG_BDB1S26_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [172]    MSG_BDB1S27_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [173]    MSG_BDB1S28_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [174]    MSG_BDB1S29_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [175]    MSG_BDB1S35_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [176]    MSG_BDB1S36_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [177]    MSG_BDC1D00_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [178]    MSG_BDC1D01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [179]    MSG_BDC1S13_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [180]    MSG_BDC1S14_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [181]    MSG_BDC1S16_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [182]    MSG_BDC1S30_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [183]    MSG_BDC1S33_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [184]    MSG_BDC1S40_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [185]    MSG_BDC1S41_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [186]    MSG_BDC1S46_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [187]    MSG_BDC1S48_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [188]    MSG_BDC1S52_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [189]    MSG_BDC1S60_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [190]    MSG_BDC1S81_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [191]    MSG_BDC1S82_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [192]    MSG_BDC1S83_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [193]    MSG_BDC1S87_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [194]    MSG_BDC1S89_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [195]    MSG_BDC1S91_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [196]    MSG_BDC1S97_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [197]    MSG_BDC1S98_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [198]    MSG_BDC1S99_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [199]    MSG_BDC1SA0_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [200]    MSG_BDC1SA1_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [201]    MSG_BDC1SC1_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [202]    MSG_BDC1SC2_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [203]    MSG_BDC1SC3_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [204]    MSG_BDC1SC4_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [205]    MSG_BDC1SC5_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [206]    MSG_BDC1SC6_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [207]    MSG_BDC1SC7_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [208]    MSG_BDC1SC8_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [209]    MSG_BDC1SC9_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [210]    MSG_BDC1SD1_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [211]    MSG_BDC1SD2_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [212]    MSG_BDC1SD3_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [213]    MSG_BDC1SD4_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [214]    MSG_BDC1SD5_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [215]    MSG_BDC1SD6_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [216]    MSG_BDC1SD7_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [217]    MSG_BDC1SD8_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [218]    MSG_BDC1SD9_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [219]    MSG_BDC1SE1_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [220]    MSG_BDC1SE2_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [221]    MSG_BDC1SE3_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [222]    MSG_BDC1SE4_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [223]    MSG_BDC1SE5_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [224]    MSG_BDC1SE6_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [225]    MSG_BDC1SE7_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [226]    MSG_BDC1SE8_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [227]    MSG_BDC1SE9_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [228]    MSG_BDC1SF1_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [229]    MSG_BDC1SF2_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [230]    MSG_BDC1SF3_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [231]    MSG_BDC1SF4_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [232]    MSG_BDC1SF5_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [233]    MSG_BDC1SF6_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [234]    MSG_BDC1SG4_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [235]    MSG_BDC1SG6_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [236]    MSG_BDC1SG7_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [237]    MSG_BDC1SG8_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [238]    MSG_BDC1SG9_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [239]    MSG_BDC1SH3_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [240]    MSG_BDC1SH4_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [241]    MSG_BDC1SH5_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [242]    MSG_BDC1SH6_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [243]    MSG_BDC1SH8_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [244]    MSG_BDC1SI0_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [245]    MSG_BDC1SI1_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [246]    MSG_BDC1SI2_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [247]    MSG_BDC1SI3_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [248]    MSG_BDC1SI4_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [249]    MSG_BDC1SI5_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [250]    MSG_BDC1SI6_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [251]    MSG_BDC1SI7_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [252]    MSG_BDC1SI8_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [253]    MSG_BDC1SI9_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [254]    MSG_BDC1SJ0_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [255]    MSG_BDC1SJ1_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [256]    MSG_BDC1SJ2_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [257]    MSG_BDC1SJ3_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [258]    MSG_BDC1SJ4_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [259]    MSG_BDC1SJ5_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [260]    MSG_BDC1SJ6_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [261]    MSG_BDC1SJ7_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [262]    MSG_BDC1SJ8_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [263]    MSG_BDC1SV1_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [264]    MSG_BDC1SV2_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [265]    MSG_BDC1SV3_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [266]    MSG_BDF3S01_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [267]    MSG_BDF3S02_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [268]    MSG_BDR3S02_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [269]    MSG_BKD1S01_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [270]    MSG_BKD1S02_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [271]    MSG_BSR1S01_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [272]    MSG_BSR1S02_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [273]    MSG_BSR1S03_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [274]    MSG_CDC1S01_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [275]    MSG_CMB1S03_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [276]    MSG_CMB1S04_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [277]    MSG_CSR1G10_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [278]    MSG_CSR1S04_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [279]    MSG_CSR1S07_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [280]    MSG_CSR1S08_RXCH0  */
    (U4)0x00010016U,  /* IGR, IGP, ACC, PNC_16,                        */    /* [281]    MSG_DCM1S01_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [282]    MSG_DCM1S03_RXCH0  */
    (U4)0x00010016U,  /* IGR, IGP, ACC, PNC_16,                        */    /* [283]    MSG_DCM1S04_RXCH0  */
    (U4)0x00010016U,  /* IGR, IGP, ACC, PNC_16,                        */    /* [284]    MSG_DCM1S08_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [285]    MSG_DDM1S00_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [286]    MSG_DDM1S09_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [287]    MSG_DDM1S12_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [288]    MSG_DDM1S16_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [289]    MSG_DDM1S17_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [290]    MSG_DDM1S20_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [291]    MSG_DDM1S32_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [292]    MSG_DDM1S35_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [293]    MSG_DDM1S77_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [294]    MSG_DDM1SFH_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [295]    MSG_DKY1S26_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [296]    MSG_DRL1S03_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [297]    MSG_DRR1S03_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [298]    MSG_DS11S27_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [299]    MSG_DS11S37_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [300]    MSG_DS11S40_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [301]    MSG_DS12F02_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [302]    MSG_DS12F03_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [303]    MSG_DST1S02_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [304]    MSG_EBU1D01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [305]    MSG_ECT1G01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [306]    MSG_ECT1G92_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [307]    MSG_ECT1S93_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [308]    MSG_EHV1E96_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [309]    MSG_EHV1F02_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [310]    MSG_EHV1F04_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [311]    MSG_EHV1G30_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [312]    MSG_EHV1G70_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [313]    MSG_EHV1G71_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [314]    MSG_EHV1S23_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [315]    MSG_EHV1S26_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [316]    MSG_EHV1S31_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [317]    MSG_EHV1S90_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [318]    MSG_EHV1S94_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [319]    MSG_EHV1S95_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [320]    MSG_EHV1S96_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [321]    MSG_EHV1S97_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [322]    MSG_EHV1S99_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [323]    MSG_EHV1SL2_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [324]    MSG_EHV2G02_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [325]    MSG_EHV2G10_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [326]    MSG_EHV2G20_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [327]    MSG_EIM1S01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [328]    MSG_ENG1C01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [329]    MSG_ENG1C02_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [330]    MSG_ENG1D51_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [331]    MSG_ENG1D52_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [332]    MSG_ENG1D53_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [333]    MSG_ENG1D55_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [334]    MSG_ENG1D56_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [335]    MSG_ENG1D59_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [336]    MSG_ENG1D60_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [337]    MSG_ENG1G03_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [338]    MSG_ENG1G13_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [339]    MSG_ENG1G90_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [340]    MSG_ENG1G92_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [341]    MSG_ENG1S51_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [342]    MSG_ENG1S60_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [343]    MSG_ENG1S99_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [344]    MSG_EPS1D50_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [345]    MSG_EPS1S11_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [346]    MSG_EPS1S90_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [347]    MSG_FCM1C01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [348]    MSG_FCM1C03_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [349]    MSG_FCM1S10_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [350]    MSG_FCM1S12_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [351]    MSG_FCM1S39_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [352]    MSG_FCM1S40_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [353]    MSG_FCM1S41_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [354]    MSG_FCM1S49_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [355]    MSG_FCM1S51_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [356]    MSG_FCM1S52_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [357]    MSG_FCM1S58_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [358]    MSG_FCM1S66_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [359]    MSG_FCM1S70_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [360]    MSG_FCM1S76_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [361]    MSG_FCM1S78_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [362]    MSG_FCM1S79_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [363]    MSG_FCM1S88_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [364]    MSG_FCM1S90_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [365]    MSG_FCM1S92_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [366]    MSG_FCM1S95_RXCH0  */
    (U4)0x00000004U,  /*      IGP,                                     */    /* [367]    MSG_FWD1S10_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [368]    MSG_IDT1S02_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [369]    MSG_IDT1S07_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [370]    MSG_IDT1S08_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [371]    MSG_IDT1S15_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [372]    MSG_IMS1S01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [373]    MSG_IPA1S05_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [374]    MSG_ITS1S01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [375]    MSG_ITS1S04_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [376]    MSG_ITS1S05_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [377]    MSG_ITS1S08_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [378]    MSG_LVN1S01_RXCH0  */
    (U4)0x000F0016U,  /* IGR, IGP, ACC, PNC_16, PNC_40, PNC_43, PNC_44 */    /* [379]    MSG_MET1S02_RXCH0  */
    (U4)0x000F0016U,  /* IGR, IGP, ACC, PNC_16, PNC_40, PNC_43, PNC_44 */    /* [380]    MSG_MET1S38_RXCH0  */
    (U4)0x000F0016U,  /* IGR, IGP, ACC, PNC_16, PNC_40, PNC_43, PNC_44 */    /* [381]    MSG_MET1S47_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [382]    MSG_MET1S55_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [383]    MSG_MGC1F13_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [384]    MSG_PDC1G01_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [385]    MSG_PDC1G02_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [386]    MSG_PDS1S01_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [387]    MSG_PLG1G15_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [388]    MSG_PLG1G16_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [389]    MSG_PLG1S01_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [390]    MSG_PLG1S06_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [391]    MSG_PLG1S20_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [392]    MSG_PLG1S21_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [393]    MSG_PMN1G03_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [394]    MSG_PST1S01_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [395]    MSG_PST1S02_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [396]    MSG_RCP1S01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [397]    MSG_RCP1S02_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [398]    MSG_RCP1S03_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [399]    MSG_RCP1S04_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [400]    MSG_RCP1S05_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [401]    MSG_RCP1S06_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [402]    MSG_RSE1G20_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [403]    MSG_RSE1G24_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [404]    MSG_RSE1G25_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [405]    MSG_RSE1G26_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [406]    MSG_RSE1S02_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [407]    MSG_RST1S03_RXCH0  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Attention :                                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Although PNC_## is not assigned to IG/ACC system messages as a rule, SBW1G02 received on the CAN-FD Bus/G5M,                      */
/* which is an IG/ACC system bus, is defined as a +B system message in CAN BitAssign v7.30, so PNC_16 is assigned as an exception.   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
    (U4)0x00010016U,  /* IGR, IGP, ACC, PNC_16                         */    /* [408]    MSG_SBW1G02_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [409]    MSG_SCN1S01_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [410]    MSG_SCN1S02_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [411]    MSG_SCS1D50_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [412]    MSG_SCS1S10_RXCH0  */
    (U4)0x00030016U,  /* IGR, IGP, ACC, PNC_16, PNC_40,                */    /* [413]    MSG_SCS1S11_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [414]    MSG_SCS1S14_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [415]    MSG_SOL1S02_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [416]    MSG_SOL1S03_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [417]    MSG_SOL1S04_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [418]    MSG_SOL1S05_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [419]    MSG_SOL1S06_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [420]    MSG_TPM1S02_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [421]    MSG_TPM1S03_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [422]    MSG_TPM1S04_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [423]    MSG_TPM1S05_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [424]    MSG_TPM1S06_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [425]    MSG_TPM1S07_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [426]    MSG_TPM1S08_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [427]    MSG_TPM1S09_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [428]    MSG_TPM1S10_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [429]    MSG_TPM1S11_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [430]    MSG_TPM1S12_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [431]    MSG_TRA1S01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [432]    MSG_TRA1S02_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [433]    MSG_UCB1S01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [434]    MSG_VAS1S01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [435]    MSG_VGR1D50_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [436]    MSG_VSC1D51_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [437]    MSG_VSC1F01_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [438]    MSG_VSC1G12_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [439]    MSG_VSC1G13_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [440]    MSG_VSC1G14_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [441]    MSG_VSC1G96_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [442]    MSG_VUM1S01_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [443]    MSG_WIP1S01_RXCH0  */
    (U4)0x00010016U,  /* IGR, IGP, ACC, PNC_16,                        */    /* [444]    MSG_YGW1S01_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [445]    MSG_ZN11S02_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [446]    MSG_ZN11S03_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [447]    MSG_ZN11S08_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [448]    MSG_ZN11S14_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [449]    MSG_ZN11S17_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [450]    MSG_ZN11S19_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [451]    MSG_ZN11S25_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [452]    MSG_ZN11S26_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [453]    MSG_ZN11S32_RXCH0  */
    (U4)0x00000014U,  /* IGR, IGP,                                     */    /* [454]    MSG_ZN11S38_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [455]    MSG_ZN11S60_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [456]    MSG_ZN11S63_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [457]    MSG_ZN11S64_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [458]    MSG_ZN11S65_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [459]    MSG_ZN11S66_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [460]    MSG_ZN11S67_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [461]    MSG_ZN11SF6_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [462]    MSG_ZN11SF7_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [463]    MSG_ZN11SF8_RXCH0  */
    (U4)0x00000016U,  /* IGR, IGP, ACC,                                */    /* [464]    MSG_ZN11SF9_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [465]    MSG_ZN21S05_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [466]    MSG_ZN21S13_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [467]    MSG_ZN21S28_RXCH0  */
    (U4)0x00090016U,  /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [468]    MSG_ZN21S52_RXCH0  */
    (U4)0x00090016U   /* IGR, IGP, ACC, PNC_16,                 PNC_44 */    /* [469]    MSG_ZN21S72_RXCH0  */
};
const U2                    u2_g_OXCAN_RXD_NUM_PDU = (U2)OXCAN_RXD_NUM_PDU;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2             u2_sp_OXCAN_RXD_BY_ACK[] = {
    (U2)OXCAN_RXD_PDU_CAN_ABG1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ABG1D51_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ABG1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ABG1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ABG1S09_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S07_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S15_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S16_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S22_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S25_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S29_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S06_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S14_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S15_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S17_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S19_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S20_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S23_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S27_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S30_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S31_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S06_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S07_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S18_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S19_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S20_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S21_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S22_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S23_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S24_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S25_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S26_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S27_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S28_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ARS1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ARS1S90_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1E41_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1E45_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1ED1_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1ED5_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1EDA_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1EDB_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1S11_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT2ED2_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BCC1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BCC1S06_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1F01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1F02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1F03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S19_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S25_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S26_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S27_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S28_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S29_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S35_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S36_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1D00_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1D01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S14_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S16_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S30_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S33_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S40_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S41_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S46_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S48_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S52_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S60_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S81_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S82_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S83_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S87_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S89_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S91_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S97_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S98_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S99_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SA0_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SA1_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SC1_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SC2_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SC3_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SC4_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SC5_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SC6_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SC7_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SC8_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SC9_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SD1_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SD2_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SD3_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SD4_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SD5_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SD6_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SD7_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SD8_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SD9_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SE1_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SE2_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SE3_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SE4_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SE5_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SE6_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SE7_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SE8_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SE9_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SF1_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SF2_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SF3_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SF4_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SF5_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SF6_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SG4_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SG6_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SG7_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SG8_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SG9_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SH3_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SH4_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SH5_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SH6_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SH8_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SI0_CH0,
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
    (U2)OXCAN_RXD_PDU_CAN_BDC1SJ3_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SJ4_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SJ5_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SJ6_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SJ7_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SJ8_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SV1_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SV2_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SV3_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDF3S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDF3S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDR3S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BKD1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BKD1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BSR1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BSR1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BSR1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CDC1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CMB1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CMB1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CSR1G10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CSR1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CSR1S07_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CSR1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DCM1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DCM1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DCM1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DCM1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S00_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S09_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S12_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S16_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S17_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S20_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S32_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S35_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S77_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1SFH_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DKY1S26_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DRL1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DRR1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DS11S27_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DS11S37_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DS11S40_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DS12F02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DS12F03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DST1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EBU1D01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ECT1G01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ECT1G92_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ECT1S93_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1E96_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1F02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1F04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1G30_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1G70_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1G71_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S23_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S26_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S31_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S90_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S94_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S95_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S96_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S97_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S99_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1SL2_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV2G02_CH0,
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
    (U2)OXCAN_RXD_PDU_CAN_ENG1G03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1G13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1G90_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1G92_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1S51_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1S99_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EPS1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EPS1S11_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EPS1S90_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1C01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1C03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S12_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S39_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S40_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S41_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S49_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S51_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S52_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S58_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S66_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S70_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S76_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S78_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S79_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S88_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S90_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S92_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S95_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FWD1S10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IDT1S07_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IDT1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IDT1S15_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IMS1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IPA1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ITS1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ITS1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ITS1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ITS1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_LVN1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_MET1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_MET1S38_CH0,
    (U2)OXCAN_RXD_PDU_CAN_MET1S47_CH0,
    (U2)OXCAN_RXD_PDU_CAN_MET1S55_CH0,
    (U2)OXCAN_RXD_PDU_CAN_MGC1F13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PDC1G01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PDC1G02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PDS1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PLG1G15_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PLG1G16_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PLG1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PLG1S06_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PLG1S20_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PLG1S21_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PMN1G03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PST1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PST1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RCP1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RCP1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RCP1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RCP1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RCP1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RCP1S06_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RSE1G20_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RSE1G24_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RSE1G25_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RSE1G26_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RSE1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_RST1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SBW1G02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SCN1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SCN1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SCS1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SCS1S10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SCS1S11_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SCS1S14_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SOL1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SOL1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SOL1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SOL1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SOL1S06_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S06_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S07_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S09_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S11_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S12_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TRA1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TRA1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_UCB1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VAS1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VGR1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VSC1D51_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VSC1F01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VSC1G12_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VSC1G13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VSC1G14_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VSC1G96_CH0,
    (U2)OXCAN_RXD_PDU_CAN_VUM1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_WIP1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_YGW1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S14_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S17_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S25_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S26_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S32_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S38_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S60_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S63_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S64_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S65_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S66_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S67_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11SF6_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11SF7_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11SF8_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11SF9_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN21S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN21S13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN21S28_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN21S52_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN21S72_CH0
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_OXCAN_RXD_ACK      st_gp_OXCAN_RXD_ACK_BY_GR[OXCAN_RXD_NUM_GR] = {
    {
        &u2_sp_OXCAN_RXD_BY_ACK[0],    /* u2p_RXD_BY_ACK */
        (U2)MSG_ABG1D50_RXCH0,         /* u2_ack_min     */
        (U2)MSG_ZN21S72_RXCH0          /* u2_ack_max     */
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
