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

#define NVM_NUM_OF_NVRAMBLOCKS          (90U)
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
#define BlockDescriptor_00002 (2U)
#define BlockDescriptor_00003 (3U)
#define BlockDescriptor_00004 (4U)
#define BlockDescriptor_00005 (5U)
#define BlockDescriptor_00006 (6U)
#define BlockDescriptor_00007 (7U)
#define BlockDescriptor_00008 (8U)
#define BlockDescriptor_00009 (9U)
#define BlockDescriptor_00010 (10U)
#define BlockDescriptor_00011 (11U)
#define BlockDescriptor_00012 (12U)
#define BlockDescriptor_00013 (13U)
#define BlockDescriptor_00014 (14U)
#define BlockDescriptor_00015 (15U)
#define BlockDescriptor_00016 (16U)
#define BlockDescriptor_00017 (17U)
#define DTF_BID_TRIP_CNT001 (18U)
#define DTF_BID_TRIP_CNT002 (19U)
#define DTF_BID_TRIP_CNT003 (20U)
#define DTF_BID_TRIP_TMSTP (21U)
#define DTF_BID_ROE_A005 (22U)
#define DTF_BID_DTC_EVENT001 (23U)
#define DTF_BID_DTC_EVENT002 (24U)
#define DTF_BID_DTC_EVENT003 (25U)
#define DTF_BID_DTC_EVENT004 (26U)
#define DTF_BID_DTC_EVENT005 (27U)
#define DTF_BID_DTC_EVENT006 (28U)
#define DTF_BID_DTC_EVENT007 (29U)
#define DTF_BID_DTC_EVENT008 (30U)
#define DTF_BID_DTC_EVENT009 (31U)
#define DTF_BID_DTC_EVENT010 (32U)
#define DTF_BID_DTC_EVENT011 (33U)
#define DTF_BID_DTC_EVENT012 (34U)
#define DTF_BID_DTC_EVENT013 (35U)
#define DTF_BID_DTC_EVENT014 (36U)
#define DTF_BID_DTC_EVENT015 (37U)
#define DTF_BID_DTC_EVENT016 (38U)
#define DTF_BID_DTC_EVENT017 (39U)
#define DTF_BID_DTC_EVENT018 (40U)
#define DTF_BID_DTC_EVENT019 (41U)
#define DTF_BID_DTC_EVENT020 (42U)
#define DTF_BID_DTC_EVENT021 (43U)
#define DTF_BID_DTC_FAULT001 (44U)
#define DTF_BID_DTC_FAULT002 (45U)
#define DTF_BID_DTC_FAULT003 (46U)
#define DTF_BID_DTC_FAULT004 (47U)
#define DTF_BID_DTC_FAULT005 (48U)
#define DTF_BID_DTC_FAULT006 (49U)
#define DTF_BID_DTC_FAULT007 (50U)
#define DTF_BID_DTC_FAULT008 (51U)
#define DTF_BID_DTC_FAULT009 (52U)
#define DTF_BID_DTC_FAULT010 (53U)
#define DTF_BID_DTC_FAULT011 (54U)
#define DTF_BID_DTC_FAULT012 (55U)
#define DTF_BID_DTC_FAULT013 (56U)
#define DTF_BID_DTC_FAULT014 (57U)
#define DTF_BID_DTC_FAULT015 (58U)
#define DTF_BID_DTC_FAULT016 (59U)
#define DTF_BID_DTC_FAULT017 (60U)
#define DTF_BID_DTC_FAULT018 (61U)
#define DTF_BID_DTC_FAULT019 (62U)
#define DTF_BID_DTC_FAULT020 (63U)
#define DTF_BID_DTC_FAULT021 (64U)
#define DTF_BID_DTC_FFD001 (65U)
#define DTF_BID_DTC_FFD002 (66U)
#define DTF_BID_DTC_FFD003 (67U)
#define DTF_BID_DTC_FFD004 (68U)
#define DTF_BID_DTC_FFD005 (69U)
#define DTF_BID_DTC_FFD006 (70U)
#define DTF_BID_DTC_FFD007 (71U)
#define DTF_BID_DTC_FFD008 (72U)
#define DTF_BID_DTC_FFD009 (73U)
#define DTF_BID_DTC_FFD010 (74U)
#define DTF_BID_DTC_FFD011 (75U)
#define DTF_BID_DTC_FFD012 (76U)
#define DTF_BID_DTC_FFD013 (77U)
#define DTF_BID_DTC_FFD014 (78U)
#define DTF_BID_DTC_FFD015 (79U)
#define DTF_BID_DTC_FFD016 (80U)
#define DTF_BID_DTC_FFD017 (81U)
#define DTF_BID_DTC_FFD018 (82U)
#define DTF_BID_DTC_FFD019 (83U)
#define DTF_BID_DTC_FFD020 (84U)
#define DTF_BID_DTC_FFD021 (85U)
#define DTF_BID_DTC_CLEARINFO (86U)
#define DTF_BID_DTC_LOGRX1_1 (87U)
#define DTF_BID_DTC_LOGRX1_2 (88U)
#define DTF_BID_DTC_LOGRX1_3 (89U)

#endif /* NVM_CFG_H */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
