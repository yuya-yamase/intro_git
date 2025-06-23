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

    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [24]  MSG_ABG1D51_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [25]  MSG_ABG1S01_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [26]  MSG_ABG1S09_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [27]  MSG_ACN1D50_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [28]  MSG_ACN1S03_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [29]  MSG_ACN1S04_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [30]  MSG_ACN1S07_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [31]  MSG_ACN1S15_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [32]  MSG_ACN1S25_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [33]  MSG_ACN1S29_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [34]  MSG_ADC1S08_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [35]  MSG_ADC1S10_RXCH0 */
    (U4)0x00050016U , /* IGR, IGP, ACC, PNC_16,         PNC_43         */       /* [36]  MSG_ADC1S11_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [37]  MSG_ADC1S12_RXCH0 */
    (U4)0x00050016U , /* IGR, IGP, ACC, PNC_16,         PNC_43         */       /* [38]  MSG_ADC1S13_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [39]  MSG_ADC1S14_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [40]  MSG_ADC1S15_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [41]  MSG_ADC1S16_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [42]  MSG_ADC1S17_RXCH0 */
    (U4)0x00010016U , /* IGR, IGP, ACC, PNC_16                         */       /* [43]  MSG_ADC1S27_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [44]  MSG_ADC1S31_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [45]  MSG_ADU1S03_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [46]  MSG_ADU1S05_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [47]  MSG_ADU1S06_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [48]  MSG_ADU1S07_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [49]  MSG_ARS1S01_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [50]  MSG_ARS1S90_RXCH0 */
    (U4)0x00030004U , /*      IGP,      PNC_16, PNC_40                 */       /* [51]  MSG_BAT1E45_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [52]  MSG_BAT1ED1_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [53]  MSG_BAT1ED5_RXCH0 */
    (U4)0x00010016U , /* IGR, IGP, ACC, PNC_16                         */       /* [54]  MSG_BAT1EDA_RXCH0 */
    (U4)0x00010016U , /* IGR, IGP, ACC, PNC_16                         */       /* [55]  MSG_BAT1EDB_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [56]  MSG_BAT1S01_RXCH0 */
    (U4)0x00030004U , /*      IGP,      PNC_16, PNC_40                 */       /* [57]  MSG_BAT1S08_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [58]  MSG_BAT1S11_RXCH0 */
    (U4)0x00010016U , /* IGR, IGP, ACC, PNC_16                         */       /* [59]  MSG_BAT2ED2_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [60]  MSG_BCC1S06_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [61]  MSG_BDB1F01_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [62]  MSG_BDB1F02_RXCH0 */
    (U4)0x00010016U , /* IGR, IGP, ACC, PNC_16                         */       /* [63]  MSG_BDB1F03_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [64]  MSG_BDB1S01_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [65]  MSG_BDB1S02_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [66]  MSG_BDB1S03_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [67]  MSG_BDB1S04_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [68]  MSG_BDB1S05_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [69]  MSG_BDB1S08_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [70]  MSG_BDB1S10_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [71]  MSG_BDB1S13_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [72]  MSG_BDB1S27_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [73]  MSG_BDB1S28_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [74]  MSG_BDB1S29_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [75]  MSG_BDB1S36_RXCH0 */
    (U4)0x00090014U , /* IGR, IGP,      PNC_16,                 PNC_44 */       /* [76]  MSG_BDC1S13_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [77]  MSG_BDC1S23_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [78]  MSG_BDC1S33_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [79]  MSG_BDC1S41_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [80]  MSG_BDC1S45_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [81]  MSG_BDC1S46_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [82]  MSG_BDC1S48_RXCH0 */
    (U4)0x00090014U , /* IGR, IGP,      PNC_16,                 PNC_44 */       /* [83]  MSG_BDC1S52_RXCH0 */
    (U4)0x00090014U , /* IGR, IGP,      PNC_16,                 PNC_44 */       /* [84]  MSG_BDC1S60_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [85]  MSG_BDC1S74_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [86]  MSG_BDC1S81_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [87]  MSG_BDC1S91_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [88]  MSG_BDC1S97_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [89]  MSG_BDC1S98_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [90]  MSG_BDC1S99_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [91]  MSG_BDC1SH8_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [92]  MSG_BDC1SI1_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [93]  MSG_BDC1SI2_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [94]  MSG_BDC1SI3_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [95]  MSG_BDC1SI4_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [96]  MSG_BDC1SI5_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [97]  MSG_BDC1SI6_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [98]  MSG_BDC1SI7_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [99]  MSG_BDC1SI8_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [100]  MSG_BDC1SI9_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [101]  MSG_BDC1SJ0_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [102]  MSG_BDC1SJ1_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [103]  MSG_BDC1SJ2_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [104]  MSG_BDC1SV1_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [105]  MSG_BDC1SV2_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [106]  MSG_BDF3S01_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [107]  MSG_BDF3S02_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [108]  MSG_BDR3S02_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [109]  MSG_BKD1S01_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [110]  MSG_BKD1S02_RXCH0 */
    (U4)0x00050016U , /* IGR, IGP, ACC, PNC_16,         PNC_43         */       /* [111]  MSG_BSR1S01_RXCH0 */
    (U4)0x00050016U , /* IGR, IGP, ACC, PNC_16,         PNC_43         */       /* [112]  MSG_BSR1S02_RXCH0 */
    (U4)0x00050016U , /* IGR, IGP, ACC, PNC_16,         PNC_43         */       /* [113]  MSG_BSR1S03_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [114]  MSG_CMB1S03_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [115]  MSG_CMB1S04_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [116]  MSG_CSR1G10_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [117]  MSG_CSR1S04_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [118]  MSG_CSR1S07_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [119]  MSG_CSR1S08_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [120]  MSG_DDM1S00_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [121]  MSG_DDM1S09_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [122]  MSG_DDM1S12_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [123]  MSG_DDM1S16_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [124]  MSG_DDM1S17_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [125]  MSG_DDM1S32_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [126]  MSG_DDM1S35_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [127]  MSG_DDM1SFH_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [128]  MSG_DKY1S26_RXCH0 */
    (U4)0x00050016U , /* IGR, IGP, ACC, PNC_16,         PNC_43         */       /* [129]  MSG_DMC1S08_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [130]  MSG_DRL1S03_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [131]  MSG_DRR1S03_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [132]  MSG_DS11S27_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [133]  MSG_DS11S37_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [134]  MSG_DS11S40_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [135]  MSG_DS12F02_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [136]  MSG_DS12F03_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [137]  MSG_DST1S02_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [138]  MSG_EBU1D01_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [139]  MSG_ECT1G01_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [140]  MSG_ECT1G92_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [141]  MSG_ECT1S80_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [142]  MSG_ECT1S93_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [143]  MSG_EHV1E96_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [144]  MSG_EHV1F02_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [145]  MSG_EHV1F04_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [146]  MSG_EHV1G30_RXCH0 */
    (U4)0x00030004U , /*      IGP,      PNC_16, PNC_40                 */       /* [147]  MSG_EHV1S23_RXCH0 */
    (U4)0x00030004U , /*      IGP,      PNC_16, PNC_40                 */       /* [148]  MSG_EHV1S26_RXCH0 */
    (U4)0x00030004U , /*      IGP,      PNC_16, PNC_40                 */       /* [149]  MSG_EHV1S31_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [150]  MSG_EHV1S90_RXCH0 */
    (U4)0x00030004U , /*      IGP,      PNC_16, PNC_40                 */       /* [151]  MSG_EHV1S94_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [152]  MSG_EHV1S95_RXCH0 */
    (U4)0x00030004U , /*      IGP,      PNC_16, PNC_40                 */       /* [153]  MSG_EHV1S96_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [154]  MSG_EHV1S97_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [155]  MSG_EHV1S99_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [156]  MSG_EHV2G02_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [157]  MSG_EHV2G10_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [158]  MSG_EHV2G20_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [159]  MSG_EHV2G70_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [160]  MSG_EIM1S01_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [161]  MSG_ENG1C01_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [162]  MSG_ENG1C02_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [163]  MSG_ENG1D51_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [164]  MSG_ENG1D52_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [165]  MSG_ENG1D53_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [166]  MSG_ENG1D55_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [167]  MSG_ENG1D56_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [168]  MSG_ENG1D59_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [169]  MSG_ENG1D60_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [170]  MSG_ENG1G03_RXCH0 */
    (U4)0x00030004U , /*      IGP,      PNC_16, PNC_40                 */       /* [171]  MSG_ENG1G13_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [172]  MSG_ENG1G17_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [173]  MSG_ENG1G90_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [174]  MSG_ENG1G92_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [175]  MSG_ENG1S60_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [176]  MSG_ENG1S99_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [177]  MSG_EPS1D50_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [178]  MSG_EPS1S11_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [179]  MSG_EPS1S90_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [180]  MSG_FCM1C01_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [181]  MSG_FCM1S10_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [182]  MSG_FCM1S12_RXCH0 */
    (U4)0x00050016U , /* IGR, IGP, ACC, PNC_16,         PNC_43         */       /* [183]  MSG_FCM1S39_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [184]  MSG_FCM1S40_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [185]  MSG_FCM1S41_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [186]  MSG_FCM1S49_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [187]  MSG_FCM1S51_RXCH0 */
    (U4)0x00010016U , /* IGR, IGP, ACC, PNC_16                         */       /* [188]  MSG_FCM1S52_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [189]  MSG_FCM1S58_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [190]  MSG_FCM1S70_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [191]  MSG_FCM1S76_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [192]  MSG_FCM1S78_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [193]  MSG_FCM1S79_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [194]  MSG_FCM1S90_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [195]  MSG_FCM1S92_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [196]  MSG_FCM1S95_RXCH0 */
    (U4)0x00010004U , /*      IGP,      PNC_16                         */       /* [197]  MSG_FWD1S10_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [198]  MSG_IDT1S02_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [199]  MSG_IDT1S07_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [200]  MSG_IDT1S15_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [201]  MSG_IPA1S05_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [202]  MSG_ITS1S01_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [203]  MSG_ITS1S04_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [204]  MSG_ITS1S05_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [205]  MSG_LVN1S01_RXCH0 */
    (U4)0x000F0016U , /* IGR, IGP, ACC, PNC_16, PNC_40, PNC_43, PNC_44 */       /* [206]  MSG_MET1S33_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [207]  MSG_MGC1F13_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [208]  MSG_PCN1S01_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [209]  MSG_PDC1G01_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [210]  MSG_PDC1G02_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [211]  MSG_PDS1S01_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [212]  MSG_PLG1G15_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [213]  MSG_PLG1G16_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [214]  MSG_PLG1S01_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [215]  MSG_PLG1S06_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [216]  MSG_PLG1S20_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [217]  MSG_PLG1S21_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [218]  MSG_PMN1G03_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [219]  MSG_PST1S01_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [220]  MSG_RCP1S02_RXCH0 */
    (U4)0x00050014U , /* IGR, IGP,      PNC_16,         PNC_43         */       /* [221]  MSG_RCP1S03_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [222]  MSG_RCP1S04_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [223]  MSG_RCP1S05_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [224]  MSG_RCP1S06_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [225]  MSG_RSE1G20_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [226]  MSG_RSE1G24_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [227]  MSG_RSE1G25_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [228]  MSG_RSE1G26_RXCH0 */
    (U4)0x00010016U , /* IGR, IGP, ACC, PNC_16                         */       /* [229]  MSG_RSE1S02_RXCH0 */
    (U4)0x00010016U , /* IGR, IGP, ACC, PNC_16                         */       /* [230]  MSG_SBW1G02_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [231]  MSG_SCN1S01_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [232]  MSG_SCN1S02_RXCH0 */
    (U4)0x00010016U , /* IGR, IGP, ACC, PNC_16                         */       /* [233]  MSG_SCS1S10_RXCH0 */
    (U4)0x00030016U , /* IGR, IGP, ACC, PNC_16, PNC_40                 */       /* [234]  MSG_SCS1S11_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [235]  MSG_SCS1S14_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [236]  MSG_SOL1S02_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [237]  MSG_SOL1S06_RXCH0 */
    (U4)0x00090014U , /* IGR, IGP,      PNC_16,                 PNC_44 */       /* [238]  MSG_TPM1S02_RXCH0 */
    (U4)0x00090014U , /* IGR, IGP,      PNC_16,                 PNC_44 */       /* [239]  MSG_TPM1S03_RXCH0 */
    (U4)0x00090014U , /* IGR, IGP,      PNC_16,                 PNC_44 */       /* [240]  MSG_TPM1S04_RXCH0 */
    (U4)0x00090014U , /* IGR, IGP,      PNC_16,                 PNC_44 */       /* [241]  MSG_TPM1S05_RXCH0 */
    (U4)0x00090014U , /* IGR, IGP,      PNC_16,                 PNC_44 */       /* [242]  MSG_TPM1S07_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [243]  MSG_TRA1S01_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [244]  MSG_UCB1S01_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [245]  MSG_VAS1S01_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [246]  MSG_VGR1D50_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [247]  MSG_VSC1D51_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [248]  MSG_VSC1F01_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [249]  MSG_VSC1G12_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [250]  MSG_VSC1G13_RXCH0 */
    (U4)0x00030014U , /* IGR, IGP,      PNC_16, PNC_40                 */       /* [251]  MSG_VSC1G14_RXCH0 */
    (U4)0x00010014U , /* IGR, IGP,      PNC_16                         */       /* [252]  MSG_VSC1G96_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [253]  MSG_VUM1S01_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [254]  MSG_WIP1S01_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [255]  MSG_ZN11S02_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [256]  MSG_ZN11S03_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [257]  MSG_ZN11S08_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [258]  MSG_ZN11S14_RXCH0 */
    (U4)0x00090014U , /* IGR, IGP,      PNC_16,                 PNC_44 */       /* [259]  MSG_ZN11S17_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [260]  MSG_ZN11S19_RXCH0 */
    (U4)0x00090014U , /* IGR, IGP,      PNC_16,                 PNC_44 */       /* [261]  MSG_ZN11S26_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [262]  MSG_ZN11S32_RXCH0 */
    (U4)0x00090014U , /* IGR, IGP,      PNC_16,                 PNC_44 */       /* [263]  MSG_ZN11S38_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [264]  MSG_ZN11S60_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [265]  MSG_ZN11S63_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [266]  MSG_ZN11S64_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [267]  MSG_ZN11S65_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [268]  MSG_ZN11S66_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [269]  MSG_ZN11S67_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [270]  MSG_ZN11SF6_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [271]  MSG_ZN11SF7_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [272]  MSG_ZN21S05_RXCH0 */
    (U4)0x00090016U , /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [273]  MSG_ZN21S13_RXCH0 */
    (U4)0x00090016U   /* IGR, IGP, ACC, PNC_16,                 PNC_44 */       /* [274]  MSG_ZN21S72_RXCH0 */
};
const U2                    u2_g_OXCAN_RXD_NUM_PDU = (U2)OXCAN_RXD_NUM_PDU;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2             u2_sp_OXCAN_RXD_BY_ACK[] = {
    (U2)OXCAN_RXD_PDU_CAN_ABG1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ABG1D51_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ABG1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ABG1S09_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S07_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S15_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S25_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ACN1S29_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S11_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S12_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S14_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S15_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S16_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S17_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S27_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADC1S31_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S06_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ADU1S07_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ARS1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ARS1S90_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1E45_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1ED1_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1ED5_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1EDA_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1EDB_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT1S11_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BAT2ED2_CH0,
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
    (U2)OXCAN_RXD_PDU_CAN_BDB1S27_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S28_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S29_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDB1S36_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S23_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S33_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S41_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S45_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S46_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S48_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S52_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S60_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S74_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S81_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S91_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S97_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S98_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1S99_CH0,
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
    (U2)OXCAN_RXD_PDU_CAN_BDC1SV1_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDC1SV2_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDF3S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDF3S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BDR3S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BKD1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BKD1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BSR1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BSR1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_BSR1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CMB1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CMB1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CSR1G10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CSR1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CSR1S07_CH0,
    (U2)OXCAN_RXD_PDU_CAN_CSR1S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S00_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S09_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S12_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S16_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S17_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S32_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1S35_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DDM1SFH_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DKY1S26_CH0,
    (U2)OXCAN_RXD_PDU_CAN_DMC1S08_CH0,
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
    (U2)OXCAN_RXD_PDU_CAN_ECT1S80_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ECT1S93_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1E96_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1F02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1F04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1G30_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S23_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S26_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S31_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S90_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S94_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S95_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S96_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S97_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV1S99_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV2G02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV2G10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV2G20_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EHV2G70_CH0,
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
    (U2)OXCAN_RXD_PDU_CAN_ENG1G17_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1G90_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1G92_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ENG1S99_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EPS1D50_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EPS1S11_CH0,
    (U2)OXCAN_RXD_PDU_CAN_EPS1S90_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1C01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S12_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S39_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S40_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S41_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S49_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S51_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S52_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S58_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S70_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S76_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S78_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S79_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S90_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S92_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FCM1S95_CH0,
    (U2)OXCAN_RXD_PDU_CAN_FWD1S10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IDT1S07_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IDT1S15_CH0,
    (U2)OXCAN_RXD_PDU_CAN_IPA1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ITS1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ITS1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ITS1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_LVN1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_MET1S33_CH0,
    (U2)OXCAN_RXD_PDU_CAN_MGC1F13_CH0,
    (U2)OXCAN_RXD_PDU_CAN_PCN1S01_CH0,
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
    (U2)OXCAN_RXD_PDU_CAN_SBW1G02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SCN1S01_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SCN1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SCS1S10_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SCS1S11_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SCS1S14_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SOL1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_SOL1S06_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S04_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TPM1S07_CH0,
    (U2)OXCAN_RXD_PDU_CAN_TRA1S01_CH0,
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
    (U2)OXCAN_RXD_PDU_CAN_ZN11S02_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S03_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S08_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S14_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S17_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,
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
    (U2)OXCAN_RXD_PDU_CAN_ZN21S05_CH0,
    (U2)OXCAN_RXD_PDU_CAN_ZN21S13_CH0,
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
