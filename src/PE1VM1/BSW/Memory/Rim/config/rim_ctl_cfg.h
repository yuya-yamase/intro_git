/* 1.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : CTL                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef RIM_CTL_CFG_H
#define RIM_CTL_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_CTL_CFG_H_MAJOR                      (1U)
#define RIM_CTL_CFG_H_MINOR                      (3U)
#define RIM_CTL_CFG_H_PATCH                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* RimId */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_U1## */
#define RIMID_U1_SAMPLE_BBB_1                    (0x0000U)
#define RIMID_U1_NVMC_DA_DTF_WRI_000             (0x0001U)
#define RIMID_U1_NVMC_DA_DTF_REA_000             (0x0002U)
#define RIMID_U1_NVMC_ST_DTF_000                 (0x0003U)
#define RIMID_U1_NVMC_ST_DTF_001                 (0x0004U)
#define RIMID_U1_NVMC_ST_DTF_002                 (0x0005U)
#define RIMID_U1_NVMC_ST_DTF_003                 (0x0006U)
#define RIMID_U1_NVMC_ST_DTF_004                 (0x0007U)
#define RIMID_U1_NVMC_ST_DTF_005                 (0x0008U)
#define RIMID_U1_VDF_DEST_BDB                    (0x0009U)
#define RIMID_U1_VDF_STRG_WHL                    (0x000AU)
#define RIMID_U1_OXDC_UDTC_EV_CNT                (0x000BU)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_U2## */
#define RIMID_U2_SAMPLE_BBB_2                    (0x4000U)
#define RIMID_U2_NVMC_DA_DTF_WRI_001             (0x4001U)
#define RIMID_U2_NVMC_DA_DTF_REA_001             (0x4002U)
#define RIMID_U2_OXDC_UDTC_LAST_EV_ID            (0x4003U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_U4## */
#define RIMID_U4_SAMPLE_BBB_4                    (0x8000U)
#define RIMID_U4_NVMC_DA_DTF_WRI_002             (0x8001U)
#define RIMID_U4_NVMC_DA_DTF_REA_002             (0x8002U)
#define RIMID_U4_NVMC_DA_DTF_WRI_005             (0x8003U)
#define RIMID_U4_BSW_SECOC_TRIP_CNT              (0x8004U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_U4## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_OTR## */
#define RIMID_OTR_SAMPLE_BBB_OTH                 (0xC000U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_003            (0xC001U)
#define RIMID_OTR_NVMC_DA_DTF_REA_003            (0xC002U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_004            (0xC003U)
#define RIMID_OTR_NVMC_DA_DTF_REA_004            (0xC004U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_OTR## */

/* START : ##TOOL_OUT#RIM_ID_MOD_1B2C_U1## */
#define RIMID_U1_SAMPLE_BCC_1                    (0x0200U)
#define RIMID_U1_NVMC_ST_DTF_072                 (0x0201U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B2C_U2## */
#define RIMID_U2_SAMPLE_BCC_2                    (0x4200U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B2C_U4## */
#define RIMID_U4_SAMPLE_BCC_4                    (0x8200U)
#define RIMID_U4_NVMC_DA_DTF_WRI_072             (0x8201U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U4## */

/* START : ##TOOL_OUT#RIM_ID_MOD_1B_U1## */
#define RIMID_U1_SAMPLE_B_1                      (0x0400U)
#define RIMID_U1_NVMC_ST_DTF_006                 (0x0401U)
#define RIMID_U1_NVMC_ST_DTF_007                 (0x0402U)
#define RIMID_U1_NVMC_ST_DTF_008                 (0x0403U)
#define RIMID_U1_NVMC_ST_DTF_009                 (0x0404U)
#define RIMID_U1_NVMC_ST_DTF_010                 (0x0405U)
#define RIMID_U1_NVMC_ST_DTF_011                 (0x0406U)
#define RIMID_U1_NVMC_ST_DTF_012                 (0x0407U)
#define RIMID_U1_NVMC_ST_DTF_013                 (0x0408U)
#define RIMID_U1_NVMC_ST_DTF_014                 (0x0409U)
#define RIMID_U1_NVMC_ST_DTF_015                 (0x040AU)
#define RIMID_U1_NVMC_ST_DTF_016                 (0x040BU)
#define RIMID_U1_NVMC_ST_DTF_017                 (0x040CU)
#define RIMID_U1_NVMC_ST_DTF_018                 (0x040DU)
#define RIMID_U1_NVMC_ST_DTF_019                 (0x040EU)
#define RIMID_U1_NVMC_ST_DTF_020                 (0x040FU)
#define RIMID_U1_NVMC_ST_DTF_021                 (0x0410U)
#define RIMID_U1_NVMC_ST_DTF_022                 (0x0411U)
#define RIMID_U1_NVMC_ST_DTF_023                 (0x0412U)
#define RIMID_U1_NVMC_ST_DTF_024                 (0x0413U)
#define RIMID_U1_NVMC_ST_DTF_025                 (0x0414U)
#define RIMID_U1_NVMC_ST_DTF_026                 (0x0415U)
#define RIMID_U1_NVMC_ST_DTF_027                 (0x0416U)
#define RIMID_U1_NVMC_ST_DTF_028                 (0x0417U)
#define RIMID_U1_NVMC_ST_DTF_029                 (0x0418U)
#define RIMID_U1_NVMC_ST_DTF_030                 (0x0419U)
#define RIMID_U1_NVMC_ST_DTF_031                 (0x041AU)
#define RIMID_U1_NVMC_ST_DTF_032                 (0x041BU)
#define RIMID_U1_NVMC_ST_DTF_033                 (0x041CU)
#define RIMID_U1_NVMC_ST_DTF_034                 (0x041DU)
#define RIMID_U1_NVMC_ST_DTF_035                 (0x041EU)
#define RIMID_U1_NVMC_ST_DTF_036                 (0x041FU)
#define RIMID_U1_NVMC_ST_DTF_037                 (0x0420U)
#define RIMID_U1_NVMC_ST_DTF_038                 (0x0421U)
#define RIMID_U1_NVMC_ST_DTF_039                 (0x0422U)
#define RIMID_U1_NVMC_ST_DTF_040                 (0x0423U)
#define RIMID_U1_NVMC_ST_DTF_041                 (0x0424U)
#define RIMID_U1_NVMC_ST_DTF_042                 (0x0425U)
#define RIMID_U1_NVMC_ST_DTF_043                 (0x0426U)
#define RIMID_U1_NVMC_ST_DTF_044                 (0x0427U)
#define RIMID_U1_NVMC_ST_DTF_045                 (0x0428U)
#define RIMID_U1_NVMC_ST_DTF_046                 (0x0429U)
#define RIMID_U1_NVMC_ST_DTF_047                 (0x042AU)
#define RIMID_U1_NVMC_ST_DTF_048                 (0x042BU)
#define RIMID_U1_NVMC_ST_DTF_049                 (0x042CU)
#define RIMID_U1_NVMC_ST_DTF_050                 (0x042DU)
#define RIMID_U1_NVMC_ST_DTF_051                 (0x042EU)
#define RIMID_U1_NVMC_ST_DTF_052                 (0x042FU)
#define RIMID_U1_NVMC_ST_DTF_053                 (0x0430U)
#define RIMID_U1_NVMC_ST_DTF_054                 (0x0431U)
#define RIMID_U1_NVMC_ST_DTF_055                 (0x0432U)
#define RIMID_U1_NVMC_ST_DTF_056                 (0x0433U)
#define RIMID_U1_NVMC_ST_DTF_057                 (0x0434U)
#define RIMID_U1_NVMC_ST_DTF_058                 (0x0435U)
#define RIMID_U1_NVMC_ST_DTF_059                 (0x0436U)
#define RIMID_U1_NVMC_ST_DTF_060                 (0x0437U)
#define RIMID_U1_NVMC_ST_DTF_061                 (0x0438U)
#define RIMID_U1_NVMC_ST_DTF_062                 (0x0439U)
#define RIMID_U1_NVMC_ST_DTF_063                 (0x043AU)
#define RIMID_U1_NVMC_ST_DTF_064                 (0x043BU)
#define RIMID_U1_NVMC_ST_DTF_065                 (0x043CU)
#define RIMID_U1_NVMC_ST_DTF_066                 (0x043DU)
#define RIMID_U1_NVMC_ST_DTF_067                 (0x043EU)
#define RIMID_U1_NVMC_ST_DTF_068                 (0x043FU)
#define RIMID_U1_NVMC_ST_DTF_069                 (0x0440U)
#define RIMID_U1_NVMC_ST_DTF_070                 (0x0441U)
#define RIMID_U1_NVMC_ST_DTF_071                 (0x0442U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B_U2## */
#define RIMID_U2_SAMPLE_B_2                      (0x4400U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B_U4## */
#define RIMID_U4_SAMPLE_B_4                      (0x8400U)
#define RIMID_U4_NVMC_ERROR_LOG                  (0x8401U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B_U4## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B_OTR## */
#define RIMID_OTR_SAMPLE_B_OTH                   (0xC400U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_006            (0xC401U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_007            (0xC402U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_008            (0xC403U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_009            (0xC404U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_010            (0xC405U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_011            (0xC406U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_012            (0xC407U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_013            (0xC408U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_014            (0xC409U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_015            (0xC40AU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_016            (0xC40BU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_017            (0xC40CU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_018            (0xC40DU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_019            (0xC40EU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_020            (0xC40FU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_021            (0xC410U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_022            (0xC411U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_023            (0xC412U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_024            (0xC413U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_025            (0xC414U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_026            (0xC415U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_027            (0xC416U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_028            (0xC417U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_029            (0xC418U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_030            (0xC419U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_031            (0xC41AU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_032            (0xC41BU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_033            (0xC41CU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_034            (0xC41DU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_035            (0xC41EU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_036            (0xC41FU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_037            (0xC420U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_038            (0xC421U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_039            (0xC422U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_040            (0xC423U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_041            (0xC424U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_042            (0xC425U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_043            (0xC426U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_044            (0xC427U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_045            (0xC428U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_046            (0xC429U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_047            (0xC42AU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_048            (0xC42BU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_049            (0xC42CU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_050            (0xC42DU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_051            (0xC42EU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_052            (0xC42FU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_053            (0xC430U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_054            (0xC431U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_055            (0xC432U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_056            (0xC433U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_057            (0xC434U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_058            (0xC435U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_059            (0xC436U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_060            (0xC437U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_061            (0xC438U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_062            (0xC439U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_063            (0xC43AU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_064            (0xC43BU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_065            (0xC43CU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_066            (0xC43DU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_067            (0xC43EU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_068            (0xC43FU)
#define RIMID_OTR_NVMC_DA_DTF_WRI_069            (0xC440U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_070            (0xC441U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_071            (0xC442U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B_OTR## */

/* START : ##TOOL_OUT#RIM_ID_MOD_3C_U1## */
#define RIMID_U1_SAMPLE_CCC_1                    (0x0600U)
#define RIMID_U1_NVMC_NEXT_W_RDNNO_DTF           (0x0601U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3C_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3C_U2## */
#define RIMID_U2_SAMPLE_CCC_2                    (0x4600U)
#define RIMID_U2_NVMC_INITID_DTF                 (0x4601U)
#define RIMID_U2_NVMC_RECOVERY_DTF               (0x4602U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3C_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3C_U4## */
#define RIMID_U4_SAMPLE_CCC_4                    (0x8600U)
#define RIMID_U4_NVMC_REQ_DTF0                   (0x8601U)
#define RIMID_U4_NVMC_REQ_DTF1                   (0x8602U)
#define RIMID_U4_NVMC_REQ_DTF2                   (0x8603U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3C_U4## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3C_OTR## */
#define RIMID_OTR_SAMPLE_CCC_OTH                 (0xC600U)
#define RIMID_OTR_SAMPLE_CCC_OTH_2               (0xC601U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3C_OTR## */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* RIM_CTL_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see rim_ctl.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
