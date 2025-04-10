/* 1.7.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr                                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef NVMC_MGR_H
#define NVMC_MGR_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MGR_H_MAJOR                         (1U)
#define NVMC_MGR_H_MINOR                         (7U)
#define NVMC_MGR_H_PATCH                         (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "nvmc_mgr_cfg.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* NvmcSts */
#define NVMC_STATUS_COMP                         (0x00U)      /* STS:Complete                 */
#define NVMC_STATUS_ERRCOMP                      (0x01U)      /* STS:Err Complete             */
#define NVMC_STATUS_CACHE_NG                     (0x02U)      /* STS:Cache NG                 */
#define NVMC_STATUS_READING                      (0x03U)      /* STS:Reading                  */
#define NVMC_STATUS_WRITING                      (0x04U)      /* STS:Writing                  */
#define NVMC_STATUS_NG                           (0x10U)      /* NG                           */
#define NVMC_STATUS_NG_PRM_ID                    (0x21U)      /* PRM:ID Error                 */
#define NVMC_STATUS_NG_PRM_SIZE                  (0x22U)      /* PRM:Size Error               */
#define NVMC_STATUS_NG_PRM_DATA_P                (0x23U)      /* PRM:Data Pointer Error       */
#define NVMC_STATUS_NG_PRM_DEVICE                (0x24U)      /* PRM:Device Error             */
#define NVMC_STATUS_NG_PRM_ADDR                  (0x25U)      /* PRM:Address Error            */
#define NVMC_STATUS_NG_PRM_DATA                  (0x26U)      /* PRM:Data Error               */

#define NVMC_STATUS_MAX                          (NVMC_STATUS_WRITING)

#define NVMC_STATUS_KIND_MASK                    (0xF0U)
#define NVMC_STATUS_KIND_OK                      (0x00U)
#define NVMC_STATUS_KIND_NG                      (0x10U)
#define NVMC_STATUS_KIND_NG_PRM                  (0x20U)

/* NvmcId */
#define NVMC_ID_DEVICE_SHIFT                     (14U)
#define NVMC_ID_DATA_ID_SHIFT                    (0U)

#define NVMC_ID_DEVICE_MASK                      (0xC000U)
#define NVMC_ID_DATAID_MASK                      (0x0FFFU)

/* NvmcRequestType */
#define NVMC_REQUEST_TYPE_READ                   (0U)
#define NVMC_REQUEST_TYPE_WRITE                  (1U)
#define NVMC_REQUEST_TYPE_ERASE                  (2U)
#define NVMC_REQUEST_TYPE_NUM                    (3U)

#define NVMC_REQUEST_TYPE_ERROR                  (0xFFU)

/* NvmcHookResult */
#define NVMC_RESULT_OK                           (0x00U)
#define NVMC_RESULT_NG                           (0x01U)
#define NVMC_RESULT_NODATA                       (0x02U)
#define NVMC_RESULT_NON                          (0x03U)

/* BlockId To MvmcId Max */
#define NVMC_BLOCKID_TO_NVMCID_MAX               (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_Nvmc_BonInit(void);
void    vd_g_Nvmc_WkupInit(void);
void    vd_g_Nvmc_DeInit(void);

U1      u1_g_Nvmc_BonRead(void);
U1      u1_g_Nvmc_WkupRead(void);

void    vd_g_Nvmc_Task(void);
void    vd_g_Nvmc_PeriodicTask(void);

U1      u1_g_Nvmc_IsShtdwnOk(void);
void    vd_g_Nvmc_ClearShtdwnTimer(void);

void    vd_g_Nvmc_SetAcsReq(const U2 u2_a_NVMCID, const U1 u1_a_MODE);
U1      u1_g_Nvmc_GetAcsReq(const U2 u2_a_NVMCID);
U1      u1_g_Nvmc_GetAllAcsReq(const U1 u1_a_DEVICE);

U1      u1_g_Nvmc_GetDataSts(const U2 u2_a_NVMCID);

void    vd_g_Nvmc_WriteU1(const U2 u2_a_NVMCID, const U1 u1_a_DATA);
void    vd_g_Nvmc_WriteU2(const U2 u2_a_NVMCID, const U2 u2_a_DATA);
void    vd_g_Nvmc_WriteU4(const U2 u2_a_NVMCID, const U4 u4_a_DATA);
void    vd_g_Nvmc_WriteOthr(const U2 u2_a_NVMCID, const U2 u2_a_SIZE, const U1 * const u1_ap_DATA);

U1      u1_g_Nvmc_ReadU1withSts(const U2 u2_a_NVMCID, U1 *u1_ap_data);
U1      u1_g_Nvmc_ReadU2withSts(const U2 u2_a_NVMCID, U2 *u2_ap_data);
U1      u1_g_Nvmc_ReadU4withSts(const U2 u2_a_NVMCID, U4 *u4_ap_data);
U1      u1_g_Nvmc_ReadOthrwithSts(const U2 u2_a_NVMCID, const U2 u2_a_SIZE, U1 *u1_ap_data);

U1      u1_g_Nvmc_ReadStrValU1withSts(const U2 u2_a_NVMCID, U1 *u1_ap_data);
U1      u1_g_Nvmc_ReadStrValU2withSts(const U2 u2_a_NVMCID, U2 *u2_ap_data);
U1      u1_g_Nvmc_ReadStrValU4withSts(const U2 u2_a_NVMCID, U4 *u4_ap_data);
U1      u1_g_Nvmc_ReadStrValOthrwithSts(const U2 u2_a_NVMCID, const U2 u2_a_SIZE, U1 *u1_ap_data);

U1      u1_g_Nvmc_SyncData(const U2 u2_a_NVMCID);

U1      u1_g_Nvmc_ReadBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID);
U1      u1_g_Nvmc_WriteBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, const U1 * const u1_ap_DATA, const U2 u2_a_SIZE);
U1      u1_g_Nvmc_EraseBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID);
U1      u1_g_Nvmc_ReadDrctBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, U1 * u1_ap_data, const U2 u2_a_SIZE);

U1      u1_g_Nvmc_SuspendAcs(const U1 u1_a_DEVICE);
U1      u1_g_Nvmc_IsSuspendAcs(const U1 u1_a_DEVICE);
U1      u1_g_Nvmc_ConvBlockIdToNvmcId(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, U2 *u2_ap_nvmcid);

/* Following function is called from vd_g_Nvmc_DTF_Hook. */
void    vd_g_Nvmc_JobFinishHook(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, const U1 u1_a_REQUEST_TYPE, const U1 u1_a_RESULT, const U1 * const u1_ap_DATA, const U2 u2_a_NUM_BYTE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* NVMC_MGR_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see nvmc_mgr.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
