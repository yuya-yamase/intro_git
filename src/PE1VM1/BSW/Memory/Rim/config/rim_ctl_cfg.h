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
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_U2## */
#define RIMID_U2_SAMPLE_BBB_2                    (0x4000U)
#define RIMID_U2_NVMC_DA_DTF_WRI_001             (0x4001U)
#define RIMID_U2_NVMC_DA_DTF_REA_001             (0x4002U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_U4## */
#define RIMID_U4_SAMPLE_BBB_4                    (0x8000U)
#define RIMID_U4_NVMC_DA_DTF_WRI_002             (0x8001U)
#define RIMID_U4_NVMC_DA_DTF_REA_002             (0x8002U)
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
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B2C_U2## */
#define RIMID_U2_SAMPLE_BCC_2                    (0x4200U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B2C_U4## */
#define RIMID_U4_SAMPLE_BCC_4                    (0x8200U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U4## */

/* START : ##TOOL_OUT#RIM_ID_MOD_1B_U1## */
#define RIMID_U1_SAMPLE_B_1                      (0x0400U)
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
