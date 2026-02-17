/* NvM_Cfg.h                                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/CFG/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef NVM_CFG_H
#define NVM_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <NvM_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define NVM_API_CONFIG_CLASS            (NVM_API_CONFIG_CLASS_3)
#define NVM_SET_RAM_BLOCK_STATUS_API    (STD_OFF)
#define NVM_VERSION_INFO_API            (STD_ON)

#define NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION (STD_OFF)
#define NVM_DEV_ERROR_DETECT                        (STD_OFF)
#define NVM_DRV_MODE_SWITCH                         (STD_OFF)
#define NVM_DYNAMIC_CONFIGURATION                   (STD_OFF)
#define NVM_JOB_PRIORITIZATION                      (STD_OFF)
#define NVM_POLLING_MODE                            (STD_OFF)

#define NVM_COMPILED_CONFIG_ID          (0U)
#define NVM_CRC_NUM_OF_BYTES            (1U)
#define NVM_DATASET_SELECTION_BITS      (1U)
#define NVM_MAIN_FUNCTION_PERIOD        (5U)
#define NVM_REPEAT_MIRROR_OPERATIONS    (1U)
#define NVM_SIZE_IMMEDIATE_JOB_QUEUE    (1U)
#define NVM_SIZE_STANDARD_JOB_QUEUE     (1U)

#define NVM_WRITE_ALL_API               (STD_OFF)
#define NVM_USE_PRAM_BLOCK_API          (STD_ON)

#define NVM_USE_CRC                     (STD_OFF)
#define NVM_USE_ROM_BLOCK               (STD_OFF)
#define NVM_USE_DATASET_BLOCK           (STD_OFF)
#define NVM_USE_SYNC_MECHANISM          (STD_ON)
#define NVM_USE_PROTECTION              (STD_ON)
#define NVM_USE_CANCEL_NOTIFICATION     (STD_OFF)
#define NVM_USE_REDUNDANT_BLOCK         (STD_OFF)

#define NVM_MAX_OF_BLOCK_JOB_PRIORITY               (1U)

#define NVM_USE_COMMON_SINGLE_BLOCK_CALLBACK        (STD_ON)
#define NVM_USE_COMMON_RAM_MIRROR_CALLBACK          (STD_ON)
#define NVM_USE_COMMON_INIT_BLOCK_CALLBACK          (STD_ON)

#define NVM_USE_COMMON_CRC_TYPE                     (STD_ON)
#define NVM_COMMON_CRC_TYPE                         (NVM_CRC16)

#define NVM_USE_COMMON_MAX_NUM_OF_READ_RETRIES      (STD_ON)
#define NVM_COMMON_MAX_NUM_OF_READ_RETRIES          (0U)

#define NVM_USE_COMMON_MAX_NUM_OF_WRITE_RETRIES     (STD_ON)
#define NVM_COMMON_MAX_NUM_OF_WRITE_RETRIES         (0U)

#define NVM_USE_COMMON_WRITE_VERIFICATION_DATA_SIZE (STD_ON)
#define NVM_COMMON_WRITE_VERIFICATION_DATA_SIZE     (1U)

#define NVM_NUM_OF_NVRAMBLOCKS          (116U)
#define NVM_MAX_NV_BLOCK_LENGTH         (32U)
#define NVM_MAX_RAM_MIRROR_LENGTH       (1U)
#define NVM_MAX_REDUNDANCY_NUM          (1U)
#define NVM_MAX_REDUNDANT_BLOCK_LENGTH  (1U)

#define NVM_E_HARDWARE                  ( DemConf_DemEventParameter_NVM_E_HARDWARE )
#define NVM_E_INTEGRITY_FAILED          ( DemConf_DemEventParameter_NVM_E_INTEGRITY_FAILED )
#define NVM_E_LOSS_OF_REDUNDANCY        ( DemConf_DemEventParameter_NVM_E_LOSS_OF_REDUNDANCY )
#define NVM_E_REQ_FAILED                ( DemConf_DemEventParameter_NVM_E_REQ_FAILED )
#define NVM_E_VERIFY_FAILED             ( DemConf_DemEventParameter_NVM_E_VERIFY_FAILED )
#define NVM_E_WRONG_BLOCK_ID            ( DemConf_DemEventParameter_NVM_E_WRONG_BLOCK_ID )

#define Configuration_ID_Block (1U)
#define DTF_BID_ODO_00 (2U)
#define DTF_BID_ODO_01 (3U)
#define DTF_BID_ODO_02 (4U)
#define DTF_BID_TRIP_0_0 (5U)
#define DTF_BID_TRIP_0_1 (6U)
#define DTF_BID_TRIP_1_0 (7U)
#define DTF_BID_TRIP_1_1 (8U)
#define DTF_BID_TRIP_2_0 (9U)
#define DTF_BID_TRIP_2_1 (10U)
#define DTF_BID_VDF_ESO_W0_0 (11U)
#define DTF_BID_VDF_ESO_W0_1 (12U)
#define DTF_BID_VDF_ESO_W0_2 (13U)
#define DTF_BID_VDF_ESO_W1_0 (14U)
#define DTF_BID_VDF_ESO_W1_1 (15U)
#define DTF_BID_VDF_ESO_W1_2 (16U)
#define DTF_BID_VDF_ESO_W2_0 (17U)
#define DTF_BID_VDF_ESO_W2_1 (18U)
#define DTF_BID_VDF_ESO_W2_2 (19U)
#define DTF_BID_VDF_ESO_W3_0 (20U)
#define DTF_BID_VDF_ESO_W3_1 (21U)
#define DTF_BID_VDF_ESO_W3_2 (22U)
#define DTF_BID_VDF_ESO_W4_0 (23U)
#define DTF_BID_VDF_ESO_W4_1 (24U)
#define DTF_BID_VDF_ESO_W4_2 (25U)
#define DTF_BID_VDF_ESO_W5_0 (26U)
#define DTF_BID_VDF_ESO_W5_1 (27U)
#define DTF_BID_VDF_ESO_W5_2 (28U)
#define DTF_BID_VDF_ESO_W6_0 (29U)
#define DTF_BID_VDF_ESO_W6_1 (30U)
#define DTF_BID_VDF_ESO_W6_2 (31U)
#define DTF_BID_VDF_ESO_W7_0 (32U)
#define DTF_BID_VDF_ESO_W7_1 (33U)
#define DTF_BID_VDF_ESO_W7_2 (34U)
#define DTF_BID_VDF_ESO_W8_0 (35U)
#define DTF_BID_VDF_ESO_W8_1 (36U)
#define DTF_BID_VDF_ESO_W8_2 (37U)
#define DTF_BID_DATESI_CALENDAR_0 (38U)
#define DTF_BID_DATESI_CALENDAR_1 (39U)
#define DTF_BID_DATESI_CALENDAR_2 (40U)
#define DTF_BID_DATESI_OFFSET_0 (41U)
#define DTF_BID_DATESI_OFFSET_1 (42U)
#define DTF_BID_DATESI_OFFSET_2 (43U)
#define DTF_BID_ODO_INHERIT_FLG_0 (44U)
#define DTF_BID_ODO_INHERIT_FLG_1 (45U)
#define DTF_BID_ODO_INHERIT_FLG_2 (46U)
#define DTF_BID_MCST_IDX_USER1_1_0 (47U)
#define DTF_BID_MCST_IDX_USER1_1_1 (48U)
#define DTF_BID_MCST_IDX_USER1_1_2 (49U)
#define DTF_BID_MCST_IDX_USER1_2_0 (50U)
#define DTF_BID_MCST_IDX_USER1_2_1 (51U)
#define DTF_BID_MCST_IDX_USER1_2_2 (52U)
#define DTF_BID_MCST_IDX_USER2_1_0 (53U)
#define DTF_BID_MCST_IDX_USER2_1_1 (54U)
#define DTF_BID_MCST_IDX_USER2_1_2 (55U)
#define DTF_BID_MCST_IDX_USER2_2_0 (56U)
#define DTF_BID_MCST_IDX_USER2_2_1 (57U)
#define DTF_BID_MCST_IDX_USER2_2_2 (58U)
#define DTF_BID_MCST_IDX_USER3_1_0 (59U)
#define DTF_BID_MCST_IDX_USER3_1_1 (60U)
#define DTF_BID_MCST_IDX_USER3_1_2 (61U)
#define DTF_BID_MCST_IDX_USER3_2_0 (62U)
#define DTF_BID_MCST_IDX_USER3_2_1 (63U)
#define DTF_BID_MCST_IDX_USER3_2_2 (64U)
#define DTF_BID_MCST_IDX_GUEST_1_0 (65U)
#define DTF_BID_MCST_IDX_GUEST_1_1 (66U)
#define DTF_BID_MCST_IDX_GUEST_1_2 (67U)
#define DTF_BID_MCST_IDX_GUEST_2_0 (68U)
#define DTF_BID_MCST_IDX_GUEST_2_1 (69U)
#define DTF_BID_MCST_IDX_GUEST_2_2 (70U)
#define DTF_BID_DRVPS_MRRPOS01_0 (71U)
#define DTF_BID_DRVPS_MRRPOS01_1 (72U)
#define DTF_BID_DRVPS_MRRPOS01_2 (73U)
#define DTF_BID_DRVPS_MRRPOS02_0 (74U)
#define DTF_BID_DRVPS_MRRPOS02_1 (75U)
#define DTF_BID_DRVPS_MRRPOS02_2 (76U)
#define DTF_BID_DRVPS_MRRPOS03_0 (77U)
#define DTF_BID_DRVPS_MRRPOS03_1 (78U)
#define DTF_BID_DRVPS_MRRPOS03_2 (79U)
#define DTF_BID_DRVPS_MRRPOS04_0 (80U)
#define DTF_BID_DRVPS_MRRPOS04_1 (81U)
#define DTF_BID_DRVPS_MRRPOS04_2 (82U)
#define DTF_BID_DRVPS_MRRPOS05_0 (83U)
#define DTF_BID_DRVPS_MRRPOS05_1 (84U)
#define DTF_BID_DRVPS_MRRPOS05_2 (85U)
#define DTF_BID_DRVPS_MRRPOS06_0 (86U)
#define DTF_BID_DRVPS_MRRPOS06_1 (87U)
#define DTF_BID_DRVPS_MRRPOS06_2 (88U)
#define DTF_BID_DRVPS_MRRPOS07_0 (89U)
#define DTF_BID_DRVPS_MRRPOS07_1 (90U)
#define DTF_BID_DRVPS_MRRPOS07_2 (91U)
#define DTF_BID_DRVPS_MRRPOS08_0 (92U)
#define DTF_BID_DRVPS_MRRPOS08_1 (93U)
#define DTF_BID_DRVPS_MRRPOS08_2 (94U)
#define DTF_BID_DRVPS_MRRPOS09_0 (95U)
#define DTF_BID_DRVPS_MRRPOS09_1 (96U)
#define DTF_BID_DRVPS_MRRPOS09_2 (97U)
#define DTF_BID_DRVPS_MRRPOS10_0 (98U)
#define DTF_BID_DRVPS_MRRPOS10_1 (99U)
#define DTF_BID_DRVPS_MRRPOS10_2 (100U)
#define DTF_BID_DRVPS_MRRPOS11_0 (101U)
#define DTF_BID_DRVPS_MRRPOS11_1 (102U)
#define DTF_BID_DRVPS_MRRPOS11_2 (103U)
#define DTF_BID_DRVPS_MRRPOS12_0 (104U)
#define DTF_BID_DRVPS_MRRPOS12_1 (105U)
#define DTF_BID_DRVPS_MRRPOS12_2 (106U)
#define DTF_BID_DRVPS_MRRPOS13_0 (107U)
#define DTF_BID_DRVPS_MRRPOS13_1 (108U)
#define DTF_BID_DRVPS_MRRPOS13_2 (109U)
#define DTF_BID_DRVPS_MRRPOS14_0 (110U)
#define DTF_BID_DRVPS_MRRPOS14_1 (111U)
#define DTF_BID_DRVPS_MRRPOS14_2 (112U)
#define DTF_BID_DRVPS_MRRPOS15_0 (113U)
#define DTF_BID_DRVPS_MRRPOS15_1 (114U)
#define DTF_BID_DRVPS_MRRPOS15_2 (115U)

#endif /* NVM_CFG_H */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
