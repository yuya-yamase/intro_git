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
#define NVMCID_U1_SAMPLE_U1                      (0x0000U)
#define NVMCID_U2_SAMPLE_U2                      (0x0001U)
#define NVMCID_U4_SAMPLE_U4                      (0x0002U)
#define NVMCID_OTR_SAMPLE_OTR32                  (0x0003U)
#define NVMCID_OTR_SAMPLE_OTR32CS                (0x0004U)
#define NVMCID_U4_BSW_SECOC_TRIP_CNT             (0x0005U)
#define NVMCID_OTR_OXDC_TMSTP                    (0x0006U)
#define NVMCID_OTR_OXDC_ROE_A005                 (0x0007U)
#define NVMCID_OTR_OXDC_DTC_EVENT001             (0x0008U)
#define NVMCID_OTR_OXDC_DTC_EVENT002             (0x0009U)
#define NVMCID_OTR_OXDC_DTC_EVENT003             (0x000AU)
#define NVMCID_OTR_OXDC_DTC_EVENT004             (0x000BU)
#define NVMCID_OTR_OXDC_DTC_EVENT005             (0x000CU)
#define NVMCID_OTR_OXDC_DTC_EVENT006             (0x000DU)
#define NVMCID_OTR_OXDC_DTC_EVENT007             (0x000EU)
#define NVMCID_OTR_OXDC_DTC_EVENT008             (0x000FU)
#define NVMCID_OTR_OXDC_DTC_EVENT009             (0x0010U)
#define NVMCID_OTR_OXDC_DTC_EVENT010             (0x0011U)
#define NVMCID_OTR_OXDC_DTC_EVENT011             (0x0012U)
#define NVMCID_OTR_OXDC_DTC_EVENT012             (0x0013U)
#define NVMCID_OTR_OXDC_DTC_EVENT013             (0x0014U)
#define NVMCID_OTR_OXDC_DTC_EVENT014             (0x0015U)
#define NVMCID_OTR_OXDC_DTC_EVENT015             (0x0016U)
#define NVMCID_OTR_OXDC_DTC_EVENT016             (0x0017U)
#define NVMCID_OTR_OXDC_DTC_EVENT017             (0x0018U)
#define NVMCID_OTR_OXDC_DTC_EVENT018             (0x0019U)
#define NVMCID_OTR_OXDC_DTC_EVENT019             (0x001AU)
#define NVMCID_OTR_OXDC_DTC_EVENT020             (0x001BU)
#define NVMCID_OTR_OXDC_DTC_EVENT021             (0x001CU)
#define NVMCID_OTR_OXDC_DTC_FAULT001             (0x001DU)
#define NVMCID_OTR_OXDC_DTC_FAULT002             (0x001EU)
#define NVMCID_OTR_OXDC_DTC_FAULT003             (0x001FU)
#define NVMCID_OTR_OXDC_DTC_FAULT004             (0x0020U)
#define NVMCID_OTR_OXDC_DTC_FAULT005             (0x0021U)
#define NVMCID_OTR_OXDC_DTC_FAULT006             (0x0022U)
#define NVMCID_OTR_OXDC_DTC_FAULT007             (0x0023U)
#define NVMCID_OTR_OXDC_DTC_FAULT008             (0x0024U)
#define NVMCID_OTR_OXDC_DTC_FAULT009             (0x0025U)
#define NVMCID_OTR_OXDC_DTC_FAULT010             (0x0026U)
#define NVMCID_OTR_OXDC_DTC_FAULT011             (0x0027U)
#define NVMCID_OTR_OXDC_DTC_FAULT012             (0x0028U)
#define NVMCID_OTR_OXDC_DTC_FAULT013             (0x0029U)
#define NVMCID_OTR_OXDC_DTC_FAULT014             (0x002AU)
#define NVMCID_OTR_OXDC_DTC_FAULT015             (0x002BU)
#define NVMCID_OTR_OXDC_DTC_FAULT016             (0x002CU)
#define NVMCID_OTR_OXDC_DTC_FAULT017             (0x002DU)
#define NVMCID_OTR_OXDC_DTC_FAULT018             (0x002EU)
#define NVMCID_OTR_OXDC_DTC_FAULT019             (0x002FU)
#define NVMCID_OTR_OXDC_DTC_FAULT020             (0x0030U)
#define NVMCID_OTR_OXDC_DTC_FAULT021             (0x0031U)
#define NVMCID_OTR_OXDC_DTC_FFD001               (0x0032U)
#define NVMCID_OTR_OXDC_DTC_FFD002               (0x0033U)
#define NVMCID_OTR_OXDC_DTC_FFD003               (0x0034U)
#define NVMCID_OTR_OXDC_DTC_FFD004               (0x0035U)
#define NVMCID_OTR_OXDC_DTC_FFD005               (0x0036U)
#define NVMCID_OTR_OXDC_DTC_FFD006               (0x0037U)
#define NVMCID_OTR_OXDC_DTC_FFD007               (0x0038U)
#define NVMCID_OTR_OXDC_DTC_FFD008               (0x0039U)
#define NVMCID_OTR_OXDC_DTC_FFD009               (0x003AU)
#define NVMCID_OTR_OXDC_DTC_FFD010               (0x003BU)
#define NVMCID_OTR_OXDC_DTC_FFD011               (0x003CU)
#define NVMCID_OTR_OXDC_DTC_FFD012               (0x003DU)
#define NVMCID_OTR_OXDC_DTC_FFD013               (0x003EU)
#define NVMCID_OTR_OXDC_DTC_FFD014               (0x003FU)
#define NVMCID_OTR_OXDC_DTC_FFD015               (0x0040U)
#define NVMCID_OTR_OXDC_DTC_FFD016               (0x0041U)
#define NVMCID_OTR_OXDC_DTC_FFD017               (0x0042U)
#define NVMCID_OTR_OXDC_DTC_FFD018               (0x0043U)
#define NVMCID_OTR_OXDC_DTC_FFD019               (0x0044U)
#define NVMCID_OTR_OXDC_DTC_FFD020               (0x0045U)
#define NVMCID_OTR_OXDC_DTC_FFD021               (0x0046U)
#define NVMCID_OTR_OXDC_DTC_CLEARINFO            (0x0047U)
#define NVMCID_U4_OXDC_DTC_LOGRX1                (0x0048U)
/* END : ##TOOL_OUT#NVMC_NVMCID## */

/* START : ##TOOL_OUT#NVMC_BLOCKID## */
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
