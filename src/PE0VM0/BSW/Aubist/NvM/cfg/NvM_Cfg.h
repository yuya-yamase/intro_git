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

#define NVM_NUM_OF_NVRAMBLOCKS          (18U)
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

#endif /* NVM_CFG_H */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
