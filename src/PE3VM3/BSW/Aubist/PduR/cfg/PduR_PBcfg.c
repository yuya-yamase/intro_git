/* pdur_pbcfg_c_v3-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PDUR/PBCFG/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_pdur_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#if ( BSW_BSWM_CS_FUNC_PDUR == BSW_USE )

#include <pdur/bsw_pdur.h>

#include "../inc/bsw_pdur_rt.h"
#include "PduR_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/******************************************/
/*                                        */
/* Upper Component I-PDU Table            */
/*                                        */
/******************************************/
/* I-PDU Table */
#if ( BSW_PDUR_CFG_ZEROCOSTOPERATION == BSW_NOUSE )

#if ( (BSW_BSWM_CS_FUNC_COM == BSW_USE) && (BSW_PDUR_CFG_MSGCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2ComRoutingTbl[BSW_PDUR_CFG_MSGCOM_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
    ((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0000U)  /* [0] up:ABG1D50_Rx_CDC_VCAN_BUS, low:ABG1D50_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0001U)  /* [1] up:ABG1D51_Rx_CDC_VCAN_BUS, low:ABG1D51_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0002U)  /* [2] up:ABG1S09_Rx_CDC_VCAN_BUS, low:ABG1S09_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0003U)  /* [3] up:ACN1D50_Rx_CDC_VCAN_BUS, low:ACN1D50_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0004U)  /* [4] up:ACN1S03_Rx_CDC_VCAN_BUS, low:ACN1S03_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0005U)  /* [5] up:ACN1S15_Rx_CDC_VCAN_BUS, low:ACN1S15_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0006U)  /* [6] up:ACN1S25_Rx_CDC_VCAN_BUS, low:ACN1S25_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0007U)  /* [7] up:ACN1S29_Rx_CDC_VCAN_BUS, low:ACN1S29_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0008U)  /* [8] up:ADC1S27_Rx_CDC_VCAN_BUS, low:ADC1S27_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0009U)  /* [9] up:ADC1S30_Rx_CDC_VCAN_BUS, low:ADC1S30_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x000AU)  /* [10] up:ADC1S31_Rx_CDC_VCAN_BUS, low:ADC1S31_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x000BU)  /* [11] up:ADU1S03_Rx_CDC_VCAN_BUS, low:ADU1S03_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x000CU)  /* [12] up:ADU1S05_Rx_CDC_VCAN_BUS, low:ADU1S05_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x000DU)  /* [13] up:ADU1S06_Rx_CDC_VCAN_BUS, low:ADU1S06_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x000EU)  /* [14] up:AVN1S95_Rx_CDC_VCAN_BUS, low:AVN1S95_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x000FU)  /* [15] up:BAT1E45_Rx_CDC_VCAN_BUS, low:BAT1E45_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0010U)  /* [16] up:BAT1ED1_Rx_CDC_VCAN_BUS, low:BAT1ED1_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0011U)  /* [17] up:BAT1ED5_Rx_CDC_VCAN_BUS, low:BAT1ED5_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0012U)  /* [18] up:BAT1EDA_Rx_CDC_VCAN_BUS, low:BAT1EDA_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0013U)  /* [19] up:BAT1EDB_Rx_CDC_VCAN_BUS, low:BAT1EDB_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0014U)  /* [20] up:BAT1S08_Rx_CDC_VCAN_BUS, low:BAT1S08_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0015U)  /* [21] up:BAT2ED2_Rx_CDC_VCAN_BUS, low:BAT2ED2_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0016U)  /* [22] up:BDB1F03_Rx_CDC_VCAN_BUS, low:BDB1F03_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0017U)  /* [23] up:BDB1S10_Rx_CDC_VCAN_BUS, low:BDB1S10_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0018U)  /* [24] up:BDC1S41_Rx_CDC_VCAN_BUS, low:BDC1S41_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0019U)  /* [25] up:BDC1S81_Rx_CDC_VCAN_BUS, low:BDC1S81_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x001AU)  /* [26] up:BDC1S82_Rx_CDC_VCAN_BUS, low:BDC1S82_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x001BU)  /* [27] up:BDC1S91_Rx_CDC_VCAN_BUS, low:BDC1S91_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x001CU)  /* [28] up:BDC1SH8_Rx_CDC_VCAN_BUS, low:BDC1SH8_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x001DU)  /* [29] up:BDC1SI1_Rx_CDC_VCAN_BUS, low:BDC1SI1_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x001EU)  /* [30] up:BDC1SI2_Rx_CDC_VCAN_BUS, low:BDC1SI2_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x001FU)  /* [31] up:BDC1SI3_Rx_CDC_VCAN_BUS, low:BDC1SI3_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0020U)  /* [32] up:BDC1SI4_Rx_CDC_VCAN_BUS, low:BDC1SI4_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0021U)  /* [33] up:BDC1SI5_Rx_CDC_VCAN_BUS, low:BDC1SI5_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0022U)  /* [34] up:BDC1SI6_Rx_CDC_VCAN_BUS, low:BDC1SI6_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0023U)  /* [35] up:BDC1SI7_Rx_CDC_VCAN_BUS, low:BDC1SI7_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0024U)  /* [36] up:BDC1SI8_Rx_CDC_VCAN_BUS, low:BDC1SI8_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0025U)  /* [37] up:BDC1SI9_Rx_CDC_VCAN_BUS, low:BDC1SI9_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0026U)  /* [38] up:BDC1SJ0_Rx_CDC_VCAN_BUS, low:BDC1SJ0_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0027U)  /* [39] up:BDC1SJ1_Rx_CDC_VCAN_BUS, low:BDC1SJ1_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0028U)  /* [40] up:BDC1SJ2_Rx_CDC_VCAN_BUS, low:BDC1SJ2_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0029U)  /* [41] up:BDF3S01_Rx_CDC_VCAN_BUS, low:BDF3S01_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x002AU)  /* [42] up:BDF3S02_Rx_CDC_VCAN_BUS, low:BDF3S02_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x002BU)  /* [43] up:BDR3S02_Rx_CDC_VCAN_BUS, low:BDR3S02_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x002CU)  /* [44] up:CDC1S04_Rx_CDC_VCAN_BUS, low:CDC1S04_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x002DU)  /* [45] up:CMB1S03_Rx_CDC_VCAN_BUS, low:CMB1S03_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x002EU)  /* [46] up:CMB1S04_Rx_CDC_VCAN_BUS, low:CMB1S04_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x002FU)  /* [47] up:DCM1S08_Rx_CDC_VCAN_BUS, low:DCM1S08_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0030U)  /* [48] up:DDM1S00_Rx_CDC_VCAN_BUS, low:DDM1S00_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0031U)  /* [49] up:DDM1S09_Rx_CDC_VCAN_BUS, low:DDM1S09_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0032U)  /* [50] up:DDM1S16_Rx_CDC_VCAN_BUS, low:DDM1S16_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0033U)  /* [51] up:DDM1S35_Rx_CDC_VCAN_BUS, low:DDM1S35_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0034U)  /* [52] up:DDM1SFH_Rx_CDC_VCAN_BUS, low:DDM1SFH_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0035U)  /* [53] up:DKY1S26_Rx_CDC_VCAN_BUS, low:DKY1S26_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0036U)  /* [54] up:DS11S27_Rx_CDC_VCAN_BUS, low:DS11S27_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0037U)  /* [55] up:EBU1D01_Rx_CDC_VCAN_BUS, low:EBU1D01_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0038U)  /* [56] up:ECT1S93_Rx_CDC_VCAN_BUS, low:ECT1S93_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0039U)  /* [57] up:EHV1E96_Rx_CDC_VCAN_BUS, low:EHV1E96_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x003AU)  /* [58] up:EHV1F02_Rx_CDC_VCAN_BUS, low:EHV1F02_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x003BU)  /* [59] up:EHV1S23_Rx_CDC_VCAN_BUS, low:EHV1S23_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x003CU)  /* [60] up:EHV2G10_Rx_CDC_VCAN_BUS, low:EHV2G10_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x003DU)  /* [61] up:EHV2G20_Rx_CDC_VCAN_BUS, low:EHV2G20_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x003EU)  /* [62] up:EIM1S01_Rx_CDC_VCAN_BUS, low:EIM1S01_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x003FU)  /* [63] up:ENG1C01_Rx_CDC_VCAN_BUS, low:ENG1C01_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0040U)  /* [64] up:ENG1C02_Rx_CDC_VCAN_BUS, low:ENG1C02_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0041U)  /* [65] up:ENG1D51_Rx_CDC_VCAN_BUS, low:ENG1D51_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0042U)  /* [66] up:ENG1D52_Rx_CDC_VCAN_BUS, low:ENG1D52_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0043U)  /* [67] up:ENG1D53_Rx_CDC_VCAN_BUS, low:ENG1D53_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0044U)  /* [68] up:ENG1D55_Rx_CDC_VCAN_BUS, low:ENG1D55_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0045U)  /* [69] up:ENG1D56_Rx_CDC_VCAN_BUS, low:ENG1D56_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0046U)  /* [70] up:ENG1D59_Rx_CDC_VCAN_BUS, low:ENG1D59_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0047U)  /* [71] up:ENG1D60_Rx_CDC_VCAN_BUS, low:ENG1D60_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0048U)  /* [72] up:ENG1S51_Rx_CDC_VCAN_BUS, low:ENG1S51_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0049U)  /* [73] up:EPS1D50_Rx_CDC_VCAN_BUS, low:EPS1D50_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x004AU)  /* [74] up:FCM1C01_Rx_CDC_VCAN_BUS, low:FCM1C01_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x004BU)  /* [75] up:FCM1S49_Rx_CDC_VCAN_BUS, low:FCM1S49_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x004CU)  /* [76] up:FCM1S76_Rx_CDC_VCAN_BUS, low:FCM1S76_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x004DU)  /* [77] up:FCM1S79_Rx_CDC_VCAN_BUS, low:FCM1S79_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x004EU)  /* [78] up:FCM1S90_Rx_CDC_VCAN_BUS, low:FCM1S90_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x004FU)  /* [79] up:FCM1S95_Rx_CDC_VCAN_BUS, low:FCM1S95_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0050U)  /* [80] up:IDT1S07_Rx_CDC_VCAN_BUS, low:IDT1S07_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0051U)  /* [81] up:IDT1S15_Rx_CDC_VCAN_BUS, low:IDT1S15_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0052U)  /* [82] up:MET1S02_Rx_CDC_VCAN_BUS, low:MET1S02_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0053U)  /* [83] up:MGC1F13_Rx_CDC_VCAN_BUS, low:MGC1F13_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0054U)  /* [84] up:PDC1G01_Rx_CDC_VCAN_BUS, low:PDC1G01_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0055U)  /* [85] up:RCP1S03_Rx_CDC_VCAN_BUS, low:RCP1S03_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0056U)  /* [86] up:RCP1S04_Rx_CDC_VCAN_BUS, low:RCP1S04_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0057U)  /* [87] up:RCP1S05_Rx_CDC_VCAN_BUS, low:RCP1S05_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0058U)  /* [88] up:RCP1S06_Rx_CDC_VCAN_BUS, low:RCP1S06_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0059U)  /* [89] up:RSE1G20_Rx_CDC_VCAN_BUS, low:RSE1G20_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x005AU)  /* [90] up:RSE1G24_Rx_CDC_VCAN_BUS, low:RSE1G24_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x005BU)  /* [91] up:RSE1G25_Rx_CDC_VCAN_BUS, low:RSE1G25_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x005CU)  /* [92] up:RSE1G26_Rx_CDC_VCAN_BUS, low:RSE1G26_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x005DU)  /* [93] up:RSE1S02_Rx_CDC_VCAN_BUS, low:RSE1S02_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x005EU)  /* [94] up:SCS1S10_Rx_CDC_VCAN_BUS, low:SCS1S10_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x005FU)  /* [95] up:VGR1D50_Rx_CDC_VCAN_BUS, low:VGR1D50_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0060U)  /* [96] up:VSC1D51_Rx_CDC_VCAN_BUS, low:VSC1D51_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0061U)  /* [97] up:VSC1G13_Rx_CDC_VCAN_BUS, low:VSC1G13_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0062U)  /* [98] up:WIP1S01_Rx_CDC_VCAN_BUS, low:WIP1S01_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0063U)  /* [99] up:ZN11S08_Rx_CDC_VCAN_BUS, low:ZN11S08_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0064U)  /* [100] up:ZN11S32_Rx_CDC_VCAN_BUS, low:ZN11S32_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0065U)  /* [101] up:ZN11S63_Rx_CDC_VCAN_BUS, low:ZN11S63_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0066U)  /* [102] up:ZN11S64_Rx_CDC_VCAN_BUS, low:ZN11S64_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0067U)  /* [103] up:ZN11S65_Rx_CDC_VCAN_BUS, low:ZN11S65_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0068U)  /* [104] up:ZN11S66_Rx_CDC_VCAN_BUS, low:ZN11S66_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0069U)  /* [105] up:ZN11S67_Rx_CDC_VCAN_BUS, low:ZN11S67_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x006AU)  /* [106] up:ZN11SF6_Rx_CDC_VCAN_BUS, low:ZN11SF6_Rx_CDC_VCAN_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x006BU)  /* [107] up:ZN11SF7_Rx_CDC_VCAN_BUS, low:ZN11SF7_Rx_CDC_VCAN_BUS */
};
#endif

#if ( ((BSW_BSWM_CS_FUNC_DCM == BSW_USE)) && (BSW_PDUR_CFG_MSGDCM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2DcmRoutingTbl[BSW_PDUR_CFG_MSGDCM_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) && (BSW_PDUR_CFG_MSGLDCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2LdComRoutingTbl[BSW_PDUR_CFG_MSGLDCOM_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD1_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd1RoutingTbl[BSW_PDUR_CFG_MSGCDD1_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD2_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd2RoutingTbl[BSW_PDUR_CFG_MSGCDD2_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPUP_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2J1939TpUpRoutingTbl[BSW_PDUR_CFG_MSGJ1939TPUP_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
};
#endif

#endif /* (BSW_PDUR_CFG_ZEROCOSTOPERATION == BSW_NOUSE) */


/******************************************/
/*                                        */
/* Lower Component I-PDU Table            */
/*                                        */
/******************************************/
#if ( BSW_PDUR_CFG_ZEROCOSTOPERATION == BSW_NOUSE )

#if ( (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) && (BSW_PDUR_CFG_MSGCANIF_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stCanIfRoutingTbl[BSW_PDUR_CFG_MSGCANIF_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
    { ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0000U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [0] up:ABG1D50_Rx_CDC_VCAN_BUS, low:ABG1D50_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0001U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [1] up:ABG1D51_Rx_CDC_VCAN_BUS, low:ABG1D51_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0002U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [2] up:ABG1S09_Rx_CDC_VCAN_BUS, low:ABG1S09_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0003U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [3] up:ACN1D50_Rx_CDC_VCAN_BUS, low:ACN1D50_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0004U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [4] up:ACN1S03_Rx_CDC_VCAN_BUS, low:ACN1S03_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0005U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [5] up:ACN1S15_Rx_CDC_VCAN_BUS, low:ACN1S15_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0006U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [6] up:ACN1S25_Rx_CDC_VCAN_BUS, low:ACN1S25_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0007U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [7] up:ACN1S29_Rx_CDC_VCAN_BUS, low:ACN1S29_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0008U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [8] up:ADC1S27_Rx_CDC_VCAN_BUS, low:ADC1S27_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0009U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [9] up:ADC1S30_Rx_CDC_VCAN_BUS, low:ADC1S30_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x000AU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [10] up:ADC1S31_Rx_CDC_VCAN_BUS, low:ADC1S31_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x000BU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [11] up:ADU1S03_Rx_CDC_VCAN_BUS, low:ADU1S03_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x000CU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [12] up:ADU1S05_Rx_CDC_VCAN_BUS, low:ADU1S05_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x000DU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [13] up:ADU1S06_Rx_CDC_VCAN_BUS, low:ADU1S06_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x000EU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [14] up:AVN1S95_Rx_CDC_VCAN_BUS, low:AVN1S95_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x000FU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [15] up:BAT1E45_Rx_CDC_VCAN_BUS, low:BAT1E45_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0010U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [16] up:BAT1ED1_Rx_CDC_VCAN_BUS, low:BAT1ED1_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0011U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [17] up:BAT1ED5_Rx_CDC_VCAN_BUS, low:BAT1ED5_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0012U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [18] up:BAT1EDA_Rx_CDC_VCAN_BUS, low:BAT1EDA_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0013U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [19] up:BAT1EDB_Rx_CDC_VCAN_BUS, low:BAT1EDB_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0014U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [20] up:BAT1S08_Rx_CDC_VCAN_BUS, low:BAT1S08_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0015U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [21] up:BAT2ED2_Rx_CDC_VCAN_BUS, low:BAT2ED2_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0016U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [22] up:BDB1F03_Rx_CDC_VCAN_BUS, low:BDB1F03_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0017U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [23] up:BDB1S10_Rx_CDC_VCAN_BUS, low:BDB1S10_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0018U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [24] up:BDC1S41_Rx_CDC_VCAN_BUS, low:BDC1S41_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0019U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [25] up:BDC1S81_Rx_CDC_VCAN_BUS, low:BDC1S81_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x001AU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [26] up:BDC1S82_Rx_CDC_VCAN_BUS, low:BDC1S82_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x001BU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [27] up:BDC1S91_Rx_CDC_VCAN_BUS, low:BDC1S91_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x001CU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [28] up:BDC1SH8_Rx_CDC_VCAN_BUS, low:BDC1SH8_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x001DU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [29] up:BDC1SI1_Rx_CDC_VCAN_BUS, low:BDC1SI1_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x001EU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [30] up:BDC1SI2_Rx_CDC_VCAN_BUS, low:BDC1SI2_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x001FU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [31] up:BDC1SI3_Rx_CDC_VCAN_BUS, low:BDC1SI3_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0020U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [32] up:BDC1SI4_Rx_CDC_VCAN_BUS, low:BDC1SI4_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0021U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [33] up:BDC1SI5_Rx_CDC_VCAN_BUS, low:BDC1SI5_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0022U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [34] up:BDC1SI6_Rx_CDC_VCAN_BUS, low:BDC1SI6_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0023U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [35] up:BDC1SI7_Rx_CDC_VCAN_BUS, low:BDC1SI7_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0024U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [36] up:BDC1SI8_Rx_CDC_VCAN_BUS, low:BDC1SI8_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0025U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [37] up:BDC1SI9_Rx_CDC_VCAN_BUS, low:BDC1SI9_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0026U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [38] up:BDC1SJ0_Rx_CDC_VCAN_BUS, low:BDC1SJ0_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0027U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [39] up:BDC1SJ1_Rx_CDC_VCAN_BUS, low:BDC1SJ1_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0028U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [40] up:BDC1SJ2_Rx_CDC_VCAN_BUS, low:BDC1SJ2_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0029U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [41] up:BDF3S01_Rx_CDC_VCAN_BUS, low:BDF3S01_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x002AU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [42] up:BDF3S02_Rx_CDC_VCAN_BUS, low:BDF3S02_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x002BU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [43] up:BDR3S02_Rx_CDC_VCAN_BUS, low:BDR3S02_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x002CU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [44] up:CDC1S04_Rx_CDC_VCAN_BUS, low:CDC1S04_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x002DU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [45] up:CMB1S03_Rx_CDC_VCAN_BUS, low:CMB1S03_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x002EU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [46] up:CMB1S04_Rx_CDC_VCAN_BUS, low:CMB1S04_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x002FU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [47] up:DCM1S08_Rx_CDC_VCAN_BUS, low:DCM1S08_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0030U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [48] up:DDM1S00_Rx_CDC_VCAN_BUS, low:DDM1S00_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0031U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [49] up:DDM1S09_Rx_CDC_VCAN_BUS, low:DDM1S09_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0032U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [50] up:DDM1S16_Rx_CDC_VCAN_BUS, low:DDM1S16_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0033U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [51] up:DDM1S35_Rx_CDC_VCAN_BUS, low:DDM1S35_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0034U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [52] up:DDM1SFH_Rx_CDC_VCAN_BUS, low:DDM1SFH_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0035U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [53] up:DKY1S26_Rx_CDC_VCAN_BUS, low:DKY1S26_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0036U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [54] up:DS11S27_Rx_CDC_VCAN_BUS, low:DS11S27_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0037U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [55] up:EBU1D01_Rx_CDC_VCAN_BUS, low:EBU1D01_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0038U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [56] up:ECT1S93_Rx_CDC_VCAN_BUS, low:ECT1S93_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0039U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [57] up:EHV1E96_Rx_CDC_VCAN_BUS, low:EHV1E96_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x003AU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [58] up:EHV1F02_Rx_CDC_VCAN_BUS, low:EHV1F02_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x003BU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [59] up:EHV1S23_Rx_CDC_VCAN_BUS, low:EHV1S23_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x003CU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [60] up:EHV2G10_Rx_CDC_VCAN_BUS, low:EHV2G10_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x003DU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [61] up:EHV2G20_Rx_CDC_VCAN_BUS, low:EHV2G20_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x003EU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [62] up:EIM1S01_Rx_CDC_VCAN_BUS, low:EIM1S01_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x003FU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [63] up:ENG1C01_Rx_CDC_VCAN_BUS, low:ENG1C01_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0040U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [64] up:ENG1C02_Rx_CDC_VCAN_BUS, low:ENG1C02_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0041U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [65] up:ENG1D51_Rx_CDC_VCAN_BUS, low:ENG1D51_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0042U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [66] up:ENG1D52_Rx_CDC_VCAN_BUS, low:ENG1D52_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0043U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [67] up:ENG1D53_Rx_CDC_VCAN_BUS, low:ENG1D53_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0044U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [68] up:ENG1D55_Rx_CDC_VCAN_BUS, low:ENG1D55_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0045U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [69] up:ENG1D56_Rx_CDC_VCAN_BUS, low:ENG1D56_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0046U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [70] up:ENG1D59_Rx_CDC_VCAN_BUS, low:ENG1D59_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0047U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [71] up:ENG1D60_Rx_CDC_VCAN_BUS, low:ENG1D60_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0048U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [72] up:ENG1S51_Rx_CDC_VCAN_BUS, low:ENG1S51_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0049U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [73] up:EPS1D50_Rx_CDC_VCAN_BUS, low:EPS1D50_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x004AU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [74] up:FCM1C01_Rx_CDC_VCAN_BUS, low:FCM1C01_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x004BU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [75] up:FCM1S49_Rx_CDC_VCAN_BUS, low:FCM1S49_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x004CU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [76] up:FCM1S76_Rx_CDC_VCAN_BUS, low:FCM1S76_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x004DU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [77] up:FCM1S79_Rx_CDC_VCAN_BUS, low:FCM1S79_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x004EU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [78] up:FCM1S90_Rx_CDC_VCAN_BUS, low:FCM1S90_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x004FU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [79] up:FCM1S95_Rx_CDC_VCAN_BUS, low:FCM1S95_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0050U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [80] up:IDT1S07_Rx_CDC_VCAN_BUS, low:IDT1S07_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0051U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [81] up:IDT1S15_Rx_CDC_VCAN_BUS, low:IDT1S15_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0052U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [82] up:MET1S02_Rx_CDC_VCAN_BUS, low:MET1S02_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0053U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [83] up:MGC1F13_Rx_CDC_VCAN_BUS, low:MGC1F13_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0054U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [84] up:PDC1G01_Rx_CDC_VCAN_BUS, low:PDC1G01_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0055U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [85] up:RCP1S03_Rx_CDC_VCAN_BUS, low:RCP1S03_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0056U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [86] up:RCP1S04_Rx_CDC_VCAN_BUS, low:RCP1S04_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0057U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [87] up:RCP1S05_Rx_CDC_VCAN_BUS, low:RCP1S05_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0058U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [88] up:RCP1S06_Rx_CDC_VCAN_BUS, low:RCP1S06_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0059U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [89] up:RSE1G20_Rx_CDC_VCAN_BUS, low:RSE1G20_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x005AU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [90] up:RSE1G24_Rx_CDC_VCAN_BUS, low:RSE1G24_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x005BU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [91] up:RSE1G25_Rx_CDC_VCAN_BUS, low:RSE1G25_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x005CU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [92] up:RSE1G26_Rx_CDC_VCAN_BUS, low:RSE1G26_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x005DU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [93] up:RSE1S02_Rx_CDC_VCAN_BUS, low:RSE1S02_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x005EU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [94] up:SCS1S10_Rx_CDC_VCAN_BUS, low:SCS1S10_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x005FU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [95] up:VGR1D50_Rx_CDC_VCAN_BUS, low:VGR1D50_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0060U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [96] up:VSC1D51_Rx_CDC_VCAN_BUS, low:VSC1D51_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0061U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [97] up:VSC1G13_Rx_CDC_VCAN_BUS, low:VSC1G13_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0062U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [98] up:WIP1S01_Rx_CDC_VCAN_BUS, low:WIP1S01_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0063U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [99] up:ZN11S08_Rx_CDC_VCAN_BUS, low:ZN11S08_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0064U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [100] up:ZN11S32_Rx_CDC_VCAN_BUS, low:ZN11S32_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0065U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [101] up:ZN11S63_Rx_CDC_VCAN_BUS, low:ZN11S63_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0066U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [102] up:ZN11S64_Rx_CDC_VCAN_BUS, low:ZN11S64_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0067U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [103] up:ZN11S65_Rx_CDC_VCAN_BUS, low:ZN11S65_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0068U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [104] up:ZN11S66_Rx_CDC_VCAN_BUS, low:ZN11S66_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0069U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [105] up:ZN11S67_Rx_CDC_VCAN_BUS, low:ZN11S67_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x006AU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [106] up:ZN11SF6_Rx_CDC_VCAN_BUS, low:ZN11SF6_Rx_CDC_VCAN_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x006BU),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [107] up:ZN11SF7_Rx_CDC_VCAN_BUS, low:ZN11SF7_Rx_CDC_VCAN_BUS */
};
#endif /* ( (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) && (BSW_PDUR_CFG_MSGCANIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) && (BSW_PDUR_CFG_MSGLINIF_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stLinIfRoutingTbl[BSW_PDUR_CFG_MSGLINIF_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) && (BSW_PDUR_CFG_MSGLINIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stSoAdIfRoutingTbl[BSW_PDUR_CFG_MSGSOADIF_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPIF_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stDoIPIfRoutingTbl[BSW_PDUR_CFG_MSGDOIPIF_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_CANTP == BSW_USE) && (BSW_PDUR_CFG_MSGCANTP_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stCanTpRoutingTbl[BSW_PDUR_CFG_MSGCANTP_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_CANTP == BSW_USE) && (BSW_PDUR_CFG_MSGCANTP_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_LINTP == BSW_USE) && (BSW_PDUR_CFG_MSGLINTP_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stLinTpRoutingTbl[BSW_PDUR_CFG_MSGLINTP_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_LINTP == BSW_USE) && (BSW_PDUR_CFG_MSGLINTP_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADTP_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stSoAdTpRoutingTbl[BSW_PDUR_CFG_MSGSOADTP_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADTP_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPTP_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stDoIPTpRoutingTbl[BSW_PDUR_CFG_MSGDOIPTP_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPTP_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPLO_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stJ1939TpLoRoutingTbl[BSW_PDUR_CFG_MSGJ1939TPLO_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPLO_NUM != 0U) ) */

/******************************************/
/*                                        */
/* IpduM I-PDU Table                      */
/*                                        */
/******************************************/
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )

#if ( (BSW_BSWM_CS_FUNC_COM == BSW_USE) && (BSW_PDUR_CFG_MSGCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2ComIpduMTbl[BSW_PDUR_CFG_MSGCOM_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( ((BSW_BSWM_CS_FUNC_DCM == BSW_USE)) && (BSW_PDUR_CFG_MSGDCM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2DcmIpduMTbl[BSW_PDUR_CFG_MSGDCM_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) && (BSW_PDUR_CFG_MSGLDCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2LdComIpduMTbl[BSW_PDUR_CFG_MSGLDCOM_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD1_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd1IpduMTbl[BSW_PDUR_CFG_MSGCDD1_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD2_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd2IpduMTbl[BSW_PDUR_CFG_MSGCDD2_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPUP_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2J1939TpUpIpduMTbl[BSW_PDUR_CFG_MSGJ1939TPUP_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) && (BSW_PDUR_CFG_MSGCANIF_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2CanIfIpduMTbl[BSW_PDUR_CFG_MSGCANIF_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) && (BSW_PDUR_CFG_MSGCANIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) && (BSW_PDUR_CFG_MSGLINIF_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2LinIfIpduMTbl[BSW_PDUR_CFG_MSGLINIF_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) && (BSW_PDUR_CFG_MSGLINIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2SoAdIfIpduMTbl[BSW_PDUR_CFG_MSGSOADIF_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPIF_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2DoIPIfIpduMTbl[BSW_PDUR_CFG_MSGDOIPIF_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPLO_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2J1939TpLoIpduMTbl[BSW_PDUR_CFG_MSGJ1939TPLO_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPLO_NUM != 0U) ) */

#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_USE) */

/******************************************/
/*                                        */
/* SomeIpTp I-PDU Table                   */
/*                                        */
/******************************************/
#if ( BSW_BSWM_CS_FUNC_SOMEIPTP == BSW_USE )

#if ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2SoAdIfSomeIpTpTbl[BSW_PDUR_CFG_MSGSOADIF_NUM] =
{
    /* SomeIpTp I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) ) */

#endif /* (BSW_BSWM_CS_FUNC_SOMEIPTP == BSW_USE) */

/******************************************/
/*                                        */
/* SecOC I-PDU Table                      */
/*                                        */
/******************************************/
#if ( (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) && (BSW_PDUR_CFG_IPDU_MA == BSW_USE) )

#if ( (BSW_BSWM_CS_FUNC_COM == BSW_USE) && (BSW_PDUR_CFG_MSGCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2ComSecOCTbl[BSW_PDUR_CFG_MSGCOM_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif

#if ( ((BSW_BSWM_CS_FUNC_DCM == BSW_USE)) && (BSW_PDUR_CFG_MSGDCM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2DcmSecOCTbl[BSW_PDUR_CFG_MSGDCM_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) && (BSW_PDUR_CFG_MSGLDCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2LdComSecOCTbl[BSW_PDUR_CFG_MSGLDCOM_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD1_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd1SecOCTbl[BSW_PDUR_CFG_MSGCDD1_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD2_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd2SecOCTbl[BSW_PDUR_CFG_MSGCDD2_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPUP_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2J1939TpUpSecOCTbl[BSW_PDUR_CFG_MSGJ1939TPUP_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) && (BSW_PDUR_CFG_IPDU_MA == BSW_USE) */

#endif /* (BSW_PDUR_CFG_ZEROCOSTOPERATION == BSW_NOUSE) */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (BSW_BSWM_CS_FUNC_PDUR == BSW_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/22                                             */
/*  v1-0-1          :2018/01/30                                             */
/*  v1-1-0          :2019/01/15                                             */
/*  v1-2-0          :2019/11/05                                             */
/*  v2-0-0          :2021/02/12                                             */
/*  v3-0-0          :2025/01/23                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
