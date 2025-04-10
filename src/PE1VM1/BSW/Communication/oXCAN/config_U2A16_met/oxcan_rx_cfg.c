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
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [25] MSG_ABG1D50_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [26] MSG_ABG1D51_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [27] MSG_ABG1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [28] MSG_ABG1S09_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [29] MSG_ACN1D50_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [30] MSG_ACN1S03_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [31] MSG_ACN1S04_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [32] MSG_ACN1S07_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [33] MSG_ACN1S15_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [34] MSG_ACN1S25_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [35] MSG_ACN1S29_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [36] MSG_ADC1S08_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [37] MSG_ADC1S10_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [38] MSG_ADC1S11_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [39] MSG_ADC1S12_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [40] MSG_ADC1S13_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [41] MSG_ADC1S14_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [42] MSG_ADC1S15_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [43] MSG_ADC1S16_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [44] MSG_ADC1S17_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [45] MSG_ADC1S27_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [46] MSG_ADC1S31_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [47] MSG_ADU1S03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [48] MSG_ADU1S05_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [49] MSG_ADU1S06_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [50] MSG_ADU1S07_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [51] MSG_ARS1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [52] MSG_ARS1S90_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [53] MSG_BAT1E45_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [54] MSG_BAT1ED1_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [55] MSG_BAT1ED4_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [56] MSG_BAT1ED5_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [57] MSG_BAT1EDA_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [58] MSG_BAT1EDB_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [59] MSG_BAT1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [60] MSG_BAT1S08_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [61] MSG_BAT1S11_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [62] MSG_BAT2ED2_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [63] MSG_BCC1S06_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [64] MSG_BDB1F01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [65] MSG_BDB1F02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [66] MSG_BDB1F03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [67] MSG_BDB1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [68] MSG_BDB1S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [69] MSG_BDB1S03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [70] MSG_BDB1S04_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [71] MSG_BDB1S05_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [72] MSG_BDB1S08_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [73] MSG_BDB1S10_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [74] MSG_BDB1S13_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [75] MSG_BDB1S27_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [76] MSG_BDB1S28_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [77] MSG_BDB1S29_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [78] MSG_BDB1S36_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [79] MSG_BDC1S13_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [80] MSG_BDC1S23_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [81] MSG_BDC1S33_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [82] MSG_BDC1S41_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [83] MSG_BDC1S45_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [84] MSG_BDC1S46_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [85] MSG_BDC1S48_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [86] MSG_BDC1S52_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [87] MSG_BDC1S60_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [88] MSG_BDC1S74_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [89] MSG_BDC1S81_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [90] MSG_BDC1SH8_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [91] MSG_BDF3S01_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [92] MSG_BDF3S02_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [93] MSG_BDR3S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [94] MSG_BKD1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [95] MSG_BKD1S02_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [96] MSG_BSR1S01_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [97] MSG_BSR1S02_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [98] MSG_BSR1S03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [99] MSG_CMB1S03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [100] MSG_CMB1S04_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [101] MSG_CSR1G10_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [102] MSG_CSR1S04_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [103] MSG_CSR1S07_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [104] MSG_CSR1S08_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [105] MSG_DDM1S00_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [106] MSG_DDM1S09_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [107] MSG_DDM1S12_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [108] MSG_DDM1S16_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [109] MSG_DDM1S17_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [110] MSG_DDM1S32_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [111] MSG_DDM1S35_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [112] MSG_DDM1SFG_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [113] MSG_DDM1SFH_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [114] MSG_DKY1S26_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [115] MSG_DMC1S08_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [116] MSG_DRL1S03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [117] MSG_DRR1S03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [118] MSG_DS11S27_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [119] MSG_DS11S37_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [120] MSG_DS11S40_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [121] MSG_DS12F02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [122] MSG_DS12F03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [123] MSG_DST1S02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [124] MSG_EBU1D01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [125] MSG_ECT1G01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [126] MSG_ECT1G92_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [127] MSG_ECT1S80_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [128] MSG_ECT1S93_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [129] MSG_EHV1E96_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [130] MSG_EHV1F02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [131] MSG_EHV1F04_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [132] MSG_EHV1G30_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [133] MSG_EHV1S23_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [134] MSG_EHV1S26_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [135] MSG_EHV1S31_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [136] MSG_EHV1S90_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [137] MSG_EHV1S94_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [138] MSG_EHV1S95_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [139] MSG_EHV1S96_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [140] MSG_EHV1S97_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [141] MSG_EHV1S99_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [142] MSG_EHV2G02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [143] MSG_EHV2G10_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [144] MSG_EHV2G20_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [145] MSG_EHV2G70_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [146] MSG_EIM1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [147] MSG_ENG1C01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [148] MSG_ENG1C02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [149] MSG_ENG1D51_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [150] MSG_ENG1D52_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [151] MSG_ENG1D53_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [152] MSG_ENG1D55_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [153] MSG_ENG1D56_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [154] MSG_ENG1D59_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [155] MSG_ENG1D60_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [156] MSG_ENG1G03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [157] MSG_ENG1G13_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [158] MSG_ENG1G17_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [159] MSG_ENG1G90_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [160] MSG_ENG1G92_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [161] MSG_ENG1S60_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [162] MSG_ENG1S99_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [163] MSG_EPS1D50_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [164] MSG_EPS1S11_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [165] MSG_EPS1S90_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [166] MSG_FCM1C01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [167] MSG_FCM1S10_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [168] MSG_FCM1S12_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [169] MSG_FCM1S39_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [170] MSG_FCM1S40_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [171] MSG_FCM1S41_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [172] MSG_FCM1S49_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [173] MSG_FCM1S51_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [174] MSG_FCM1S52_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [175] MSG_FCM1S58_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [176] MSG_FCM1S70_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [177] MSG_FCM1S76_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [178] MSG_FCM1S78_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [179] MSG_FCM1S79_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [180] MSG_FCM1S90_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [181] MSG_FCM1S92_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [182] MSG_FCM1S95_RXCH0 */
    (U1)(( OXCAN_SYS_IGP )),                                                                /* [183] MSG_FWD1S10_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [184] MSG_IDT1S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [185] MSG_IDT1S07_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [186] MSG_IDT1S15_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [187] MSG_IPA1S05_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [188] MSG_ITS1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [189] MSG_ITS1S04_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [190] MSG_ITS1S05_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [191] MSG_LVN1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [192] MSG_MGC1F13_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [193] MSG_PCN1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [194] MSG_PDC1G01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [195] MSG_PDC1G02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [196] MSG_PDS1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [197] MSG_PLG1G15_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [198] MSG_PLG1G16_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [199] MSG_PLG1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [200] MSG_PLG1S06_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [201] MSG_PLG1S20_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [202] MSG_PLG1S21_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [203] MSG_PMN1G03_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [204] MSG_PST1S01_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [205] MSG_PWC1S41_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [206] MSG_RCP1S02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [207] MSG_RCP1S03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [208] MSG_RSE1G20_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [209] MSG_RSE1G24_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [210] MSG_RSE1G25_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [211] MSG_RSE1G26_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [212] MSG_RSE1G29_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [213] MSG_RSE1S02_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [214] MSG_SBW1G02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [215] MSG_SCN1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [216] MSG_SCN1S02_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [217] MSG_SCS1S10_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [218] MSG_SCS1S11_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [219] MSG_SCS1S14_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [220] MSG_SOL1S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [221] MSG_SOL1S06_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [222] MSG_TPM1S02_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [223] MSG_TPM1S03_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [224] MSG_TPM1S04_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [225] MSG_TPM1S05_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [226] MSG_TPM1S07_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [227] MSG_TRA1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [228] MSG_UCB1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [229] MSG_VAS1S01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [230] MSG_VGR1D50_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [231] MSG_VSC1D51_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [232] MSG_VSC1F01_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [233] MSG_VSC1G12_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [234] MSG_VSC1G13_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [235] MSG_VSC1G14_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [236] MSG_VSC1G96_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [237] MSG_VUM1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [238] MSG_WIP1S01_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [239] MSG_ZN11S02_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [240] MSG_ZN11S03_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [241] MSG_ZN11S08_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [242] MSG_ZN11S17_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [243] MSG_ZN11S19_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [244] MSG_ZN11S26_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [245] MSG_ZN11S32_RXCH0 */
    (U1)(( OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                                  /* [246] MSG_ZN11S38_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [247] MSG_ZN11S60_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [248] MSG_ZN11S63_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [249] MSG_ZN11S64_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [250] MSG_ZN11S65_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [251] MSG_ZN11S66_RXCH0 */
    (U1)(( OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_IGR )),                                    /* [252] MSG_ZN11S67_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [253] MSG_ZN11SF6_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [254] MSG_ZN11SF7_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [255] MSG_ZN21S05_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR )),        /* [256] MSG_ZN21S13_RXCH0 */
    (U1)(( OXCAN_SYS_BAT|OXCAN_SYS_ACC|OXCAN_SYS_IGP|OXCAN_SYS_PBA|OXCAN_SYS_IGR ))         /* [257] MSG_ZN21S72_RXCH0 */
};
const U2                    u2_g_OXCAN_RX_NUM_RX       = (U2)OXCAN_PDU_NUM_RX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2             u2_sp_OXCAN_RX_BY_RX_0[] = {
    (U2)OXCAN_PDU_RX_CAN_ABG1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S31_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ARS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ARS1S90_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_BDB1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S28_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S36_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S33_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S45_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S46_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S48_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S52_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S74_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S81_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDR3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BKD1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BKD1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1G10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S00_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S32_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S35_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFG_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFH_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DKY1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DMC1S08_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_ECT1S80_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ECT1S93_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1E96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1F02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1F04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1G30_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S31_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S94_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S95_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S97_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S99_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G70_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_ENG1G17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1G90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1G92_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1C01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S39_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S40_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S49_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S58_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S70_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S76_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S78_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S79_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S92_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S95_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FWD1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IPA1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_LVN1S01_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_PWC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G24_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SBW1G02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCN1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCN1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TRA1S01_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_ZN11S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_ZN21S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN21S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN21S72_RXCH0
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2             u2_sp_OXCAN_RX_BY_CH_0[] = {
    (U2)OXCAN_PDU_RX_CAN_ABG1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1D51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ABG1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ACN1S29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADC1S31_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ADU1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ARS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ARS1S90_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_BDB1S27_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S28_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDB1S36_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S13_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S33_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S45_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S46_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S48_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S52_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S74_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1S81_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDC1SH8_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDF3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BDR3S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BKD1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BKD1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_BSR1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CMB1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1G10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_CSR1S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S00_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S09_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S16_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S32_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1S35_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFG_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DDM1SFH_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DKY1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_DMC1S08_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_ECT1S80_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ECT1S93_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1E96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1F02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1F04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1G30_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S23_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S31_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S94_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S95_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S96_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S97_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV1S99_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EHV2G70_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_ENG1G17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1G90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1G92_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S60_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1D50_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_EPS1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1C01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S12_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S39_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S40_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S49_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S51_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S58_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S70_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S76_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S78_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S79_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S90_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S92_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FCM1S95_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_FWD1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IDT1S15_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_IPA1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ITS1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_LVN1S01_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_PWC1S41_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RCP1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G20_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G24_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G25_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G26_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1G29_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_RSE1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SBW1G02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCN1S01_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCN1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S10_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S11_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SCS1S14_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_SOL1S06_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S04_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TPM1S07_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_TRA1S01_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_ZN11S02_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S03_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S08_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S17_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,
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
    (U2)OXCAN_PDU_RX_CAN_ZN21S05_RXCH0,
    (U2)OXCAN_PDU_RX_CAN_ZN21S13_RXCH0,
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
