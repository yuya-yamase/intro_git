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
#define RIMID_U1_VDF_HCS_ASCEXT                  (0x0001U)
#define RIMID_U1_VDF_DEST_BDB                    (0x0002U)
#define RIMID_U1_VDF_STRG_WHL                    (0x0003U)
#define RIMID_U1_VDF_DST_IDX                     (0x0004U)
#define RIMID_U1_VDF_LANG_DST_IDX                (0x0005U)
#define RIMID_U1_NVMC_DA_DTF_WRI_011             (0x0006U)
#define RIMID_U1_NVMC_ST_DTF_000                 (0x0007U)
#define RIMID_U1_NVMC_ST_DTF_001                 (0x0008U)
#define RIMID_U1_NVMC_ST_DTF_002                 (0x0009U)
#define RIMID_U1_NVMC_ST_DTF_003                 (0x000AU)
#define RIMID_U1_NVMC_ST_DTF_004                 (0x000BU)
#define RIMID_U1_NVMC_ST_DTF_005                 (0x000CU)
#define RIMID_U1_NVMC_ST_DTF_006                 (0x000DU)
#define RIMID_U1_NVMC_ST_DTF_007                 (0x000EU)
#define RIMID_U1_NVMC_ST_DTF_008                 (0x000FU)
#define RIMID_U1_NVMC_ST_DTF_009                 (0x0010U)
#define RIMID_U1_NVMC_ST_DTF_010                 (0x0011U)
#define RIMID_U1_NVMC_ST_DTF_011                 (0x0012U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_U2## */
#define RIMID_U2_SAMPLE_BBB_2                    (0x4000U)
#define RIMID_U2_VDF_C_CODE                      (0x4001U)
#define RIMID_U2_NVMC_DA_DTF_WRI_009             (0x4002U)
#define RIMID_U2_NVMC_DA_DTF_WRI_010             (0x4003U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_U4## */
#define RIMID_U4_SAMPLE_BBB_4                    (0x8000U)
#define RIMID_U4_VDF_ESO_W0                      (0x8001U)
#define RIMID_U4_VDF_ESO_W1                      (0x8002U)
#define RIMID_U4_VDF_ESO_W2                      (0x8003U)
#define RIMID_U4_VDF_ESO_W3                      (0x8004U)
#define RIMID_U4_VDF_ESO_W4                      (0x8005U)
#define RIMID_U4_VDF_ESO_W5                      (0x8006U)
#define RIMID_U4_VDF_ESO_W6                      (0x8007U)
#define RIMID_U4_VDF_ESO_W7                      (0x8008U)
#define RIMID_U4_VDF_ESO_W8                      (0x8009U)
#define RIMID_U4_NVMC_DA_DTF_WRI_000             (0x800AU)
#define RIMID_U4_NVMC_DA_DTF_WRI_001             (0x800BU)
#define RIMID_U4_NVMC_DA_DTF_WRI_002             (0x800CU)
#define RIMID_U4_NVMC_DA_DTF_WRI_003             (0x800DU)
#define RIMID_U4_NVMC_DA_DTF_WRI_004             (0x800EU)
#define RIMID_U4_NVMC_DA_DTF_WRI_005             (0x800FU)
#define RIMID_U4_NVMC_DA_DTF_WRI_006             (0x8010U)
#define RIMID_U4_NVMC_DA_DTF_WRI_007             (0x8011U)
#define RIMID_U4_NVMC_DA_DTF_WRI_008             (0x8012U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_U4## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_OTR## */
#define RIMID_OTR_SAMPLE_BBB_OTH                 (0xC000U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_OTR## */

/* START : ##TOOL_OUT#RIM_ID_MOD_1B2C_U1## */
#define RIMID_U1_SAMPLE_BCC_1                    (0x0200U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B2C_U2## */
#define RIMID_U2_SAMPLE_BCC_2                    (0x4200U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B2C_U4## */
#define RIMID_U4_SAMPLE_BCC_4                    (0x8200U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U4## */

/* START : ##TOOL_OUT#RIM_ID_MOD_1B_U1## */
#define RIMID_U1_SAMPLE_B_1                      (0x0400U)
#define RIMID_U1_DREC_TX                         (0x0030U)
#define RIMID_U1_ILLUMI_LOUNGE                   (0x0401U)
#define RIMID_U1_MCST_USRNUM_D                   (0x0402U)
#define RIMID_U1_NVMC_ST_DTF_012                 (0x0403U)
#define RIMID_U1_NVMC_ST_DTF_013                 (0x0404U)
#define RIMID_U1_NVMC_ST_DTF_014                 (0x0405U)
#define RIMID_U1_NVMC_ST_DTF_015                 (0x0406U)
#define RIMID_U1_NVMC_ST_DTF_016                 (0x0407U)
#define RIMID_U1_NVMC_ST_DTF_017                 (0x0408U)
#define RIMID_U1_NVMC_ST_DTF_018                 (0x0409U)
#define RIMID_U1_NVMC_ST_DTF_019                 (0x040AU)
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
#define RIMID_OTR_NVMC_DA_DTF_WRI_012            (0xC401U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_013            (0xC402U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_014            (0xC403U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_015            (0xC404U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_016            (0xC405U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_017            (0xC406U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_018            (0xC407U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_019            (0xC408U)
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
