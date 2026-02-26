/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of CAN                                                                                                             */
/*  acex = AUTOSAR/Aubist Com Extention                                                                                              */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_ACEX_CFG_C_MAJOR                    (2U)
#define OXCAN_ACEX_CFG_C_MINOR                    (0U)
#define OXCAN_ACEX_CFG_C_PATCH                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_aubif_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_ACEX_CFG_C_MAJOR != OXCAN_AUBIF_CFG_H_MAJOR) || \
     (OXCAN_ACEX_CFG_C_MINOR != OXCAN_AUBIF_CFG_H_MINOR) || \
     (OXCAN_ACEX_CFG_C_PATCH != OXCAN_AUBIF_CFG_H_PATCH))
#error "oxcan_acex_cfg.c and oxcan_aubif_cfg_private.h : source and header files are inconsistent!"
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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Transmission */
#if (OXCAN_E2E_NUM_TRA > 0U)
const U2                           u2_gp_OXCAN_E2E_TRA_BY_IPDU[] = {
    (U2)U2_MAX
};
const U1                           u1_gp_OXCAN_E2E_TRA_LEN[OXCAN_E2E_NUM_TRA] = {
    (U1)0U
};
#endif /* #if (OXCAN_E2E_NUM_TRA > 0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Reception   */
#if (OXCAN_E2E_NUM_REC > 0U)
const U2                           u2_gp_OXCAN_E2E_REC_BY_IPDU[] = {
    (U2)0U,                         /* #define MSG_BDC1S81_RXCH0                       (191U) */
    (U2)U2_MAX,                     /* #define MSG_BDC1S82_RXCH0                       (192U) */
    (U2)U2_MAX,                     /* #define MSG_BDC1S83_RXCH0                       (193U) */
    (U2)U2_MAX,                     /* #define MSG_BDC1S87_RXCH0                       (194U) */
    (U2)U2_MAX,                     /* #define MSG_BDC1S89_RXCH0                       (195U) */
    (U2)1U                          /* #define MSG_BDC1S91_RXCH0                       (196U) */
};
const U1                           u1_gp_OXCAN_E2E_REC_LEN[OXCAN_E2E_NUM_REC] = {
    (U1)21U,                        /* 0 BDC1S81 32 - FV/KZK 11 bytes */
    (U1)21U                         /* 1 BDC1S91 32 - FV/KZK 11 bytes */
};
#endif /* #if (OXCAN_E2E_NUM_REC > 0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* OMA = On-Board MAC Authentication */
#if (OXCAN_OMA_NUM_REC > 0U)
const U2                           u2_gp_OXCAN_OMA_REC_BY_IPDU[] = {

    (U2)0U,                             /* #define MSG_BDC1S13_RXCH0                       (180U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S14_RXCH0                       (181U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S16_RXCH0                       (182U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S30_RXCH0                       (183U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S33_RXCH0                       (184U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S40_RXCH0                       (185U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S41_RXCH0                       (186U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S46_RXCH0                       (187U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S48_RXCH0                       (188U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S52_RXCH0                       (189U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S60_RXCH0                       (190U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S81_RXCH0                       (191U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S82_RXCH0                       (192U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S83_RXCH0                       (193U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S87_RXCH0                       (194U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S89_RXCH0                       (195U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S91_RXCH0                       (196U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S97_RXCH0                       (197U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S98_RXCH0                       (198U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S99_RXCH0                       (199U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SA0_RXCH0                       (200U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SA1_RXCH0                       (201U) */
    (U2)1U,                             /* #define MSG_BDC1SC1_RXCH0                       (202U) */
    (U2)2U,                             /* #define MSG_BDC1SC2_RXCH0                       (203U) */
    (U2)3U,                             /* #define MSG_BDC1SC3_RXCH0                       (204U) */
    (U2)4U,                             /* #define MSG_BDC1SC4_RXCH0                       (205U) */
    (U2)5U,                             /* #define MSG_BDC1SC5_RXCH0                       (206U) */
    (U2)6U,                             /* #define MSG_BDC1SC6_RXCH0                       (207U) */
    (U2)7U,                             /* #define MSG_BDC1SC7_RXCH0                       (208U) */
    (U2)8U,                             /* #define MSG_BDC1SC8_RXCH0                       (209U) */
    (U2)9U,                             /* #define MSG_BDC1SC9_RXCH0                       (210U) */
    (U2)10U,                            /* #define MSG_BDC1SD1_RXCH0                       (211U) */
    (U2)11U,                            /* #define MSG_BDC1SD2_RXCH0                       (212U) */
    (U2)12U,                            /* #define MSG_BDC1SD3_RXCH0                       (213U) */
    (U2)13U,                            /* #define MSG_BDC1SD4_RXCH0                       (214U) */
    (U2)14U,                            /* #define MSG_BDC1SD5_RXCH0                       (215U) */
    (U2)15U,                            /* #define MSG_BDC1SD6_RXCH0                       (216U) */
    (U2)16U,                            /* #define MSG_BDC1SD7_RXCH0                       (217U) */
    (U2)17U,                            /* #define MSG_BDC1SD8_RXCH0                       (218U) */
    (U2)18U,                            /* #define MSG_BDC1SD9_RXCH0                       (219U) */
    (U2)19U,                            /* #define MSG_BDC1SE1_RXCH0                       (220U) */
    (U2)20U,                            /* #define MSG_BDC1SE2_RXCH0                       (221U) */
    (U2)21U,                            /* #define MSG_BDC1SE3_RXCH0                       (222U) */
    (U2)22U,                            /* #define MSG_BDC1SE4_RXCH0                       (223U) */
    (U2)23U,                            /* #define MSG_BDC1SE5_RXCH0                       (224U) */
    (U2)24U,                            /* #define MSG_BDC1SE6_RXCH0                       (225U) */
    (U2)25U,                            /* #define MSG_BDC1SE7_RXCH0                       (226U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SE8_RXCH0                       (227U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SE9_RXCH0                       (228U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SF1_RXCH0                       (229U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SF2_RXCH0                       (230U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SF3_RXCH0                       (231U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SF4_RXCH0                       (232U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SF5_RXCH0                       (233U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SF6_RXCH0                       (234U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SG4_RXCH0                       (235U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SG6_RXCH0                       (236U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SG7_RXCH0                       (237U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SG8_RXCH0                       (238U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SG9_RXCH0                       (239U) */
    (U2)26U,                            /* #define MSG_BDC1SH3_RXCH0                       (240U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SH4_RXCH0                       (241U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SH5_RXCH0                       (242U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SH6_RXCH0                       (243U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SH8_RXCH0                       (244U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI0_RXCH0                       (245U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI1_RXCH0                       (246U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI2_RXCH0                       (247U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI3_RXCH0                       (248U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI4_RXCH0                       (249U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI5_RXCH0                       (250U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI6_RXCH0                       (251U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI7_RXCH0                       (252U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI8_RXCH0                       (253U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI9_RXCH0                       (254U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SJ0_RXCH0                       (255U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SJ1_RXCH0                       (256U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SJ2_RXCH0                       (257U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SJ3_RXCH0                       (258U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SJ4_RXCH0                       (259U) */
    (U2)27U                             /* #define MSG_BDC1SJ5_RXCH0                       (260U) */
};
const U1                           u1_gp_OXCAN_OMA_REC_LEN[OXCAN_OMA_NUM_REC] = {
    (U1)32U,                        /* 0 BDC1S13 32             bytes */
    (U1)64U,                        /* 1 BDC1SC1 64             bytes */
    (U1)64U,                        /* 2 BDC1SC2 64             bytes */
    (U1)64U,                        /* 3 BDC1SC3 64             bytes */
    (U1)64U,                        /* 4 BDC1SC4 64             bytes */
    (U1)64U,                        /* 5 BDC1SC5 64             bytes */
    (U1)64U,                        /* 6 BDC1SC6 64             bytes */
    (U1)64U,                        /* 7 BDC1SC7 64             bytes */
    (U1)64U,                        /* 8 BDC1SC8 64             bytes */
    (U1)64U,                        /* 9 BDC1SC9 64             bytes */
    (U1)64U,                        /* 10 BDC1SD1 64            bytes */
    (U1)64U,                        /* 11 BDC1SD2 64            bytes */
    (U1)64U,                        /* 12 BDC1SD3 64            bytes */
    (U1)64U,                        /* 13 BDC1SD4 64            bytes */
    (U1)64U,                        /* 14 BDC1SD5 64            bytes */
    (U1)64U,                        /* 15 BDC1SD6 64            bytes */
    (U1)64U,                        /* 16 BDC1SD7 64            bytes */
    (U1)64U,                        /* 17 BDC1SD8 64            bytes */
    (U1)64U,                        /* 18 BDC1SD9 64            bytes */
    (U1)64U,                        /* 19 BDC1SE1 64            bytes */
    (U1)64U,                        /* 20 BDC1SE2 64            bytes */
    (U1)64U,                        /* 21 BDC1SE3 64            bytes */
    (U1)64U,                        /* 22 BDC1SE4 64            bytes */
    (U1)64U,                        /* 23 BDC1SE5 64            bytes */
    (U1)64U,                        /* 24 BDC1SE6 64            bytes */
    (U1)64U,                        /* 25 BDC1SE7 64            bytes */
    (U1)64U,                        /* 26 BDC1SH3 64            bytes */
    (U1)64U                         /* 27 BDC1SJ5 64            bytes */
};
#endif /* #if (OXCAN_OMA_NUM_REC > 0U) */

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
/*  2.0.0     2/28/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
