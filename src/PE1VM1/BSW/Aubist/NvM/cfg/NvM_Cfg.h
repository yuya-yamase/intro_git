/* NvM_Cfg.h                                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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

#define NVM_NUM_OF_NVRAMBLOCKS          (47U)
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
#define DTF_BID_DATESI_TIMEFMT_0 (44U)
#define DTF_BID_DATESI_TIMEFMT_1 (45U)
#define DTF_BID_DATESI_TIMEFMT_2 (46U)

#endif /* NVM_CFG_H */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
