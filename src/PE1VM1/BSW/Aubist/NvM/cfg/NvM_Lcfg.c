/* NvM_Lcfg.c                                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/LCFG/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <NvM.h>
#include "nvmc_dtf_ramblk_cfg.h"
#include "nvmc_dtf.h"

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define NVM_START_SEC_CONST_CONFIG_32
#include <NvM_MemMap.h>                 /* SWS_NvM_00554 */

CONST(AB_83_ConstV NvM_BlockDescriptorType, NVM_CONFIG_DATA) NvMBlockDescriptors[NVM_NUM_OF_NVRAMBLOCKS]
= {
    {
        /* ID.0 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        255U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_TEMPORARY,    /* RamBlockType */
        1U,    /* NvMNvBlockLength */
        1U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,   /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        NULL_PTR,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.1 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_TEMPORARY,    /* RamBlockType */
        32U,    /* NvMNvBlockLength */
        65534U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        NULL_PTR,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.2 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        12U,    /* NvMNvBlockLength */
        2U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_odo,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.3 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        12U,    /* NvMNvBlockLength */
        3U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_odo,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.4 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        12U,    /* NvMNvBlockLength */
        4U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_odo,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.5 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        12U,    /* NvMNvBlockLength */
        5U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_odo,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.6 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        12U,    /* NvMNvBlockLength */
        6U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_odo,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.7 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        12U,    /* NvMNvBlockLength */
        7U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_odo,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.8 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        12U,    /* NvMNvBlockLength */
        8U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_odo,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.9 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        12U,    /* NvMNvBlockLength */
        9U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_odo,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.10 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        12U,    /* NvMNvBlockLength */
        10U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_odo,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.11 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        11U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.12 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        12U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.13 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        13U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.14 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        14U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.15 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        15U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.16 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        16U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.17 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        17U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.18 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        18U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.19 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        19U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.20 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        20U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.21 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        21U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.22 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        22U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.23 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        23U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.24 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        24U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.25 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        25U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.26 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        26U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.27 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        27U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.28 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        28U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.29 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        29U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.30 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        30U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.31 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        31U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.32 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        32U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.33 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        33U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.34 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        34U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.35 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        35U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.36 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        36U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.37 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        37U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.38 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        38U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.39 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        39U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.40 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        40U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.41 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        41U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.42 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        42U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.43 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        43U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.44 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        44U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.45 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        45U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.46 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        4U,    /* NvMNvBlockLength */
        46U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.47 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        47U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.48 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        48U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.49 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        49U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.50 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        50U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.51 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        51U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.52 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        52U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.53 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        53U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.54 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        54U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.55 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        55U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.56 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        56U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.57 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        57U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.58 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        58U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.59 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        59U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.60 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        60U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.61 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        61U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
    {
        /* ID.62 */
        NVM_BLOCK_NATIVE,    /* NvMBlockManagementType */
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
        1U,    /* NvMBlockJobPriority */
#endif
        0U,    /* NvMNvramDeviceId */
        1U,    /* NvMNvBlockNum */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
        0U,    /* NvMRomBlockNum */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfReadRetries */
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
        0U,    /* NvMMaxNumOfWriteRetries */
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
        NVM_CRC16,    /* NvMBlockCrcType */
#endif
        NVM_RAM_BLOCK_TYPE_SHARED,    /* RamBlockType */
        20U,    /* NvMNvBlockLength */
        62U,    /* NvMNvBlockBaseNumber */
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
        1U,    /* NvMWriteVerificationDataSize */
#endif
        NVM_BLOCK_FLAGS_ALL_FALSE,    /* NvMBlockFlags */
        u1_gp_nvmc_dtf_default,    /* NvMRamBlockDataAddress */
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
        NULL_PTR,    /* NvMRomBlockDataAddress */
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMSingleBlockCallback */
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMReadRamBlockFromNvCallback */
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
        NULL_PTR,    /* NvMWriteRamBlockToNvCallback */
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
        NULL_PTR    /* NvMInitBlockCallback */
#endif
    },
};
CONST(AB_83_ConstV uint16, NVM_CONFIG_DATA) NvMBlockDescriptorsSize = sizeof(NvMBlockDescriptors) / sizeof(NvMBlockDescriptors[0]);

#if ( NVM_VALID_MULTI_BLOCK_CALLBACK == STD_ON )
CONST(AB_83_ConstV NvM_MultiBlockCallbackType, NVM_CONFIG_DATA) NvMMultiBlockCallback = NULL_PTR;
#endif

#if ( NVM_VALID_COMMON_SINGLE_BLOCK_CALLBACK == STD_ON )
CONST(AB_83_ConstV NvM_CommonSingleBlockCallbackType, NVM_CONFIG_DATA) NvMCommonSingleBlockCallback = &u1_g_Nvmc_DTF_Hook;
#endif

#if ( NVM_VALID_COMMON_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
CONST(AB_83_ConstV NvM_CommonReadRamBlockFromNvCallbackType, NVM_CONFIG_DATA) NvMCommonReadRamBlockFromNvCallback = &u1_g_Nvmc_DTF_CommonReadCallBack;
#endif

#if ( NVM_VALID_COMMON_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
CONST(AB_83_ConstV NvM_CommonWriteRamBlockToNvCallbackType, NVM_CONFIG_DATA) NvMCommonWriteRamBlockToNvCallback = &u1_g_Nvmc_DTF_CommonWriteCallBack;
#endif

#if ( NVM_VALID_COMMON_INIT_BLOCK_CALLBACK == STD_ON )
CONST(AB_83_ConstV NvM_CommonInitBlockCallbackType, NVM_CONFIG_DATA) NvMCommonInitBlockCallback = NULL_PTR;
#endif

#define NVM_STOP_SEC_CONST_CONFIG_32
#include <NvM_MemMap.h>                 /* SWS_NvM_00554 */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
