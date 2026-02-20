/* 1.7.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr                                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef NVMC_MGR_CFG_H
#define NVMC_MGR_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MGR_CFG_H_MAJOR                     (1U)
#define NVMC_MGR_CFG_H_MINOR                     (7U)
#define NVMC_MGR_CFG_H_PATCH                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Device definition */
/* START : ##TOOL_OUT#NVMC_DEVICE_TYPE_NUM## */
#define NVMC_DEVICE_TYPE_NUM                     (1U)
/* END : ##TOOL_OUT#NVMC_DEVICE_TYPE_NUM## */

#define NVMC_DEVICE_TYPE_DTF                     (0U)
#define NVMC_DEVICE_TYPE_EEPROM                  (1U)
#define NVMC_DEVICE_TYPE_ALL                     (0xFFU)

/* NvmcId:DEVICE */
#define NVMC_ID_DEVICE_DTF                       (0x0000U) /* NVMC_DEVICE_TYPE_DTF    (0U) << NVMC_ID_DEVICE_SHIFT (14U) */
#define NVMC_ID_DEVICE_EEPROM                    (0x4000U) /* NVMC_DEVICE_TYPE_EEPROM (1U) << NVMC_ID_DEVICE_SHIFT (14U) */

/* NvmcId */
/* SAMPLE */
/* START : ##TOOL_OUT#NVMC_NVMCID## */
#define NVMCID_APP_ODO                           (0x0000U)
#define NVMCID_APP_ODO_TRIP                      (0x0001U)
#define NVMCID_U4_VDF_ESO_W0                     (0x0002U)
#define NVMCID_U4_VDF_ESO_W1                     (0x0003U)
#define NVMCID_U4_VDF_ESO_W2                     (0x0004U)
#define NVMCID_U4_VDF_ESO_W3                     (0x0005U)
#define NVMCID_U4_VDF_ESO_W4                     (0x0006U)
#define NVMCID_U4_VDF_ESO_W5                     (0x0007U)
#define NVMCID_U4_VDF_ESO_W6                     (0x0008U)
#define NVMCID_U4_VDF_ESO_W7                     (0x0009U)
#define NVMCID_U4_VDF_ESO_W8                     (0x000AU)
#define NVMCID_U2_DATESI_CALENDAR                (0x000BU)
#define NVMCID_U2_DATESI_OFFSET                  (0x000CU)
#define NVMCID_U1_ODO_INHERIT_FLG                (0x000DU)
#define NVMCID_OTR_MCST_IDX_USER1_1              (0x000EU)
#define NVMCID_OTR_MCST_IDX_USER1_2              (0x000FU)
#define NVMCID_OTR_MCST_IDX_USER2_1              (0x0010U)
#define NVMCID_OTR_MCST_IDX_USER2_2              (0x0011U)
#define NVMCID_OTR_MCST_IDX_USER3_1              (0x0012U)
#define NVMCID_OTR_MCST_IDX_USER3_2              (0x0013U)
#define NVMCID_OTR_MCST_IDX_GUEST_1              (0x0014U)
#define NVMCID_OTR_MCST_IDX_GUEST_2              (0x0015U)
#define NVMCID_U2_DRVPS_MRRPOS01                 (0x0016U)
#define NVMCID_U2_DRVPS_MRRPOS02                 (0x0017U)
#define NVMCID_U2_DRVPS_MRRPOS03                 (0x0018U)
#define NVMCID_U2_DRVPS_MRRPOS04                 (0x0019U)
#define NVMCID_U2_DRVPS_MRRPOS05                 (0x001AU)
#define NVMCID_U2_DRVPS_MRRPOS06                 (0x001BU)
#define NVMCID_U2_DRVPS_MRRPOS07                 (0x001CU)
#define NVMCID_U2_DRVPS_MRRPOS08                 (0x001DU)
#define NVMCID_U2_DRVPS_MRRPOS09                 (0x001EU)
#define NVMCID_U2_DRVPS_MRRPOS10                 (0x001FU)
#define NVMCID_U2_DRVPS_MRRPOS11                 (0x0020U)
#define NVMCID_U2_DRVPS_MRRPOS12                 (0x0021U)
#define NVMCID_U2_DRVPS_MRRPOS13                 (0x0022U)
#define NVMCID_U2_DRVPS_MRRPOS14                 (0x0023U)
#define NVMCID_U2_DRVPS_MRRPOS15                 (0x0024U)
#define NVMCID_U4_TOEC_OC                        (0x0025U)
#define NVMCID_U4_TOEC_EU                        (0x0026U)
#define NVMCID_U4_TOSP_OC                        (0x0027U)
#define NVMCID_U4_TOSP_ET                        (0x0028U)
#define NVMCID_U4_TOTM_ET                        (0x0029U)
#define NVMCID_U4_TODT_OC                        (0x002AU)
#define NVMCID_U4_TR_A_SP_OC                     (0x002BU)
#define NVMCID_U4_TR_A_SP_ET                     (0x002CU)
#define NVMCID_U4_TR_B_SP_OC                     (0x002DU)
#define NVMCID_U4_TR_B_SP_ET                     (0x002EU)
#define NVMCID_U4_TR_A_TM_ET                     (0x002FU)
#define NVMCID_U4_TR_B_TM_ET                     (0x0030U)
#define NVMCID_U4_TR_A_DT_OC                     (0x0031U)
#define NVMCID_U4_TR_B_DT_OC                     (0x0032U)
#define NVMCID_OTR_GRPH_TAEE_ECON                (0x0033U)
#define NVMCID_OTR_GRPH_TAEE_DATE                (0x0034U)
/* END : ##TOOL_OUT#NVMC_NVMCID## */

/* START : ##TOOL_OUT#NVMC_BLOCKID## */
#define NVMC_BLOCKID_DTF_ODO_00                  (2U)
#define NVMC_BLOCKID_DTF_ODO_01                  (3U)
#define NVMC_BLOCKID_DTF_ODO_02                  (4U)
#define NVMC_BLOCKID_DTF_TRIP_0_0                (5U)
#define NVMC_BLOCKID_DTF_TRIP_0_1                (6U)
#define NVMC_BLOCKID_DTF_TRIP_1_0                (7U)
#define NVMC_BLOCKID_DTF_TRIP_1_1                (8U)
#define NVMC_BLOCKID_DTF_TRIP_2_0                (9U)
#define NVMC_BLOCKID_DTF_TRIP_2_1                (10U)
/* END : ##TOOL_OUT#NVMC_BLOCKID## */

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

#endif /* NVMC_MGR_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see nvmc_mgr.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
