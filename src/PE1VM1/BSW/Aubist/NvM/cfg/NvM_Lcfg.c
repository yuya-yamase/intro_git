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
        4U,    /* NvMNvBlockLength */
        2U,    /* NvMNvBlockBaseNumber */
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
        4U,    /* NvMNvBlockLength */
        3U,    /* NvMNvBlockBaseNumber */
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
        4U,    /* NvMNvBlockLength */
        4U,    /* NvMNvBlockBaseNumber */
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
        4U,    /* NvMNvBlockLength */
        5U,    /* NvMNvBlockBaseNumber */
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
        4U,    /* NvMNvBlockLength */
        6U,    /* NvMNvBlockBaseNumber */
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
        4U,    /* NvMNvBlockLength */
        7U,    /* NvMNvBlockBaseNumber */
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
        4U,    /* NvMNvBlockLength */
        8U,    /* NvMNvBlockBaseNumber */
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
        4U,    /* NvMNvBlockLength */
        9U,    /* NvMNvBlockBaseNumber */
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
        4U,    /* NvMNvBlockLength */
        10U,    /* NvMNvBlockBaseNumber */
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
        32U,    /* NvMNvBlockLength */
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
        32U,    /* NvMNvBlockLength */
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
        32U,    /* NvMNvBlockLength */
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
        32U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        32U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        8U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
        12U,    /* NvMNvBlockLength */
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
    {
        /* ID.63 */
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
        63U,    /* NvMNvBlockBaseNumber */
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
        /* ID.64 */
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
        64U,    /* NvMNvBlockBaseNumber */
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
        /* ID.65 */
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
        32U,    /* NvMNvBlockLength */
        65U,    /* NvMNvBlockBaseNumber */
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
        /* ID.66 */
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
        32U,    /* NvMNvBlockLength */
        66U,    /* NvMNvBlockBaseNumber */
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
        /* ID.67 */
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
        32U,    /* NvMNvBlockLength */
        67U,    /* NvMNvBlockBaseNumber */
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
        /* ID.68 */
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
        32U,    /* NvMNvBlockLength */
        68U,    /* NvMNvBlockBaseNumber */
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
        /* ID.69 */
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
        32U,    /* NvMNvBlockLength */
        69U,    /* NvMNvBlockBaseNumber */
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
        /* ID.70 */
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
        32U,    /* NvMNvBlockLength */
        70U,    /* NvMNvBlockBaseNumber */
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
        /* ID.71 */
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
        32U,    /* NvMNvBlockLength */
        71U,    /* NvMNvBlockBaseNumber */
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
        /* ID.72 */
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
        32U,    /* NvMNvBlockLength */
        72U,    /* NvMNvBlockBaseNumber */
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
        /* ID.73 */
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
        32U,    /* NvMNvBlockLength */
        73U,    /* NvMNvBlockBaseNumber */
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
        /* ID.74 */
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
        32U,    /* NvMNvBlockLength */
        74U,    /* NvMNvBlockBaseNumber */
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
        /* ID.75 */
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
        32U,    /* NvMNvBlockLength */
        75U,    /* NvMNvBlockBaseNumber */
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
        /* ID.76 */
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
        32U,    /* NvMNvBlockLength */
        76U,    /* NvMNvBlockBaseNumber */
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
        /* ID.77 */
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
        32U,    /* NvMNvBlockLength */
        77U,    /* NvMNvBlockBaseNumber */
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
        /* ID.78 */
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
        32U,    /* NvMNvBlockLength */
        78U,    /* NvMNvBlockBaseNumber */
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
        /* ID.79 */
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
        32U,    /* NvMNvBlockLength */
        79U,    /* NvMNvBlockBaseNumber */
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
        /* ID.80 */
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
        32U,    /* NvMNvBlockLength */
        80U,    /* NvMNvBlockBaseNumber */
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
        /* ID.81 */
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
        32U,    /* NvMNvBlockLength */
        81U,    /* NvMNvBlockBaseNumber */
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
        /* ID.82 */
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
        32U,    /* NvMNvBlockLength */
        82U,    /* NvMNvBlockBaseNumber */
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
        /* ID.83 */
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
        32U,    /* NvMNvBlockLength */
        83U,    /* NvMNvBlockBaseNumber */
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
        /* ID.84 */
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
        32U,    /* NvMNvBlockLength */
        84U,    /* NvMNvBlockBaseNumber */
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
        /* ID.85 */
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
        32U,    /* NvMNvBlockLength */
        85U,    /* NvMNvBlockBaseNumber */
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
        /* ID.86 */
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
        8U,    /* NvMNvBlockLength */
        86U,    /* NvMNvBlockBaseNumber */
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
        /* ID.87 */
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
        87U,    /* NvMNvBlockBaseNumber */
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
        /* ID.88 */
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
        88U,    /* NvMNvBlockBaseNumber */
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
        /* ID.89 */
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
        89U,    /* NvMNvBlockBaseNumber */
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
        /* ID.90 */
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
        90U,    /* NvMNvBlockBaseNumber */
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
        /* ID.91 */
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
        91U,    /* NvMNvBlockBaseNumber */
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
        /* ID.92 */
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
        92U,    /* NvMNvBlockBaseNumber */
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
        /* ID.93 */
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
        93U,    /* NvMNvBlockBaseNumber */
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
        /* ID.94 */
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
        94U,    /* NvMNvBlockBaseNumber */
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
        /* ID.95 */
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
        95U,    /* NvMNvBlockBaseNumber */
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
        /* ID.96 */
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
        8U,    /* NvMNvBlockLength */
        96U,    /* NvMNvBlockBaseNumber */
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
        /* ID.97 */
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
        8U,    /* NvMNvBlockLength */
        97U,    /* NvMNvBlockBaseNumber */
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
        /* ID.98 */
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
        8U,    /* NvMNvBlockLength */
        98U,    /* NvMNvBlockBaseNumber */
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
        /* ID.99 */
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
        8U,    /* NvMNvBlockLength */
        99U,    /* NvMNvBlockBaseNumber */
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
        /* ID.100 */
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
        8U,    /* NvMNvBlockLength */
        100U,    /* NvMNvBlockBaseNumber */
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
        /* ID.101 */
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
        8U,    /* NvMNvBlockLength */
        101U,    /* NvMNvBlockBaseNumber */
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
        /* ID.102 */
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
        32U,    /* NvMNvBlockLength */
        102U,    /* NvMNvBlockBaseNumber */
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
        /* ID.103 */
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
        32U,    /* NvMNvBlockLength */
        103U,    /* NvMNvBlockBaseNumber */
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
        /* ID.104 */
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
        32U,    /* NvMNvBlockLength */
        104U,    /* NvMNvBlockBaseNumber */
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
        /* ID.105 */
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
        32U,    /* NvMNvBlockLength */
        105U,    /* NvMNvBlockBaseNumber */
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
        /* ID.106 */
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
        32U,    /* NvMNvBlockLength */
        106U,    /* NvMNvBlockBaseNumber */
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
        /* ID.107 */
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
        32U,    /* NvMNvBlockLength */
        107U,    /* NvMNvBlockBaseNumber */
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
        /* ID.108 */
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
        32U,    /* NvMNvBlockLength */
        108U,    /* NvMNvBlockBaseNumber */
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
        /* ID.109 */
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
        32U,    /* NvMNvBlockLength */
        109U,    /* NvMNvBlockBaseNumber */
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
        /* ID.110 */
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
        32U,    /* NvMNvBlockLength */
        110U,    /* NvMNvBlockBaseNumber */
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
        /* ID.111 */
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
        32U,    /* NvMNvBlockLength */
        111U,    /* NvMNvBlockBaseNumber */
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
        /* ID.112 */
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
        32U,    /* NvMNvBlockLength */
        112U,    /* NvMNvBlockBaseNumber */
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
        /* ID.113 */
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
        32U,    /* NvMNvBlockLength */
        113U,    /* NvMNvBlockBaseNumber */
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
        /* ID.114 */
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
        32U,    /* NvMNvBlockLength */
        114U,    /* NvMNvBlockBaseNumber */
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
        /* ID.115 */
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
        32U,    /* NvMNvBlockLength */
        115U,    /* NvMNvBlockBaseNumber */
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
        /* ID.116 */
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
        32U,    /* NvMNvBlockLength */
        116U,    /* NvMNvBlockBaseNumber */
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
        /* ID.117 */
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
        32U,    /* NvMNvBlockLength */
        117U,    /* NvMNvBlockBaseNumber */
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
        /* ID.118 */
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
        32U,    /* NvMNvBlockLength */
        118U,    /* NvMNvBlockBaseNumber */
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
        /* ID.119 */
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
        32U,    /* NvMNvBlockLength */
        119U,    /* NvMNvBlockBaseNumber */
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
        /* ID.120 */
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
        32U,    /* NvMNvBlockLength */
        120U,    /* NvMNvBlockBaseNumber */
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
        /* ID.121 */
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
        32U,    /* NvMNvBlockLength */
        121U,    /* NvMNvBlockBaseNumber */
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
        /* ID.122 */
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
        32U,    /* NvMNvBlockLength */
        122U,    /* NvMNvBlockBaseNumber */
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
        /* ID.123 */
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
        32U,    /* NvMNvBlockLength */
        123U,    /* NvMNvBlockBaseNumber */
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
        /* ID.124 */
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
        32U,    /* NvMNvBlockLength */
        124U,    /* NvMNvBlockBaseNumber */
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
        /* ID.125 */
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
        32U,    /* NvMNvBlockLength */
        125U,    /* NvMNvBlockBaseNumber */
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
        /* ID.126 */
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
        32U,    /* NvMNvBlockLength */
        126U,    /* NvMNvBlockBaseNumber */
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
        /* ID.127 */
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
        32U,    /* NvMNvBlockLength */
        127U,    /* NvMNvBlockBaseNumber */
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
        /* ID.128 */
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
        32U,    /* NvMNvBlockLength */
        128U,    /* NvMNvBlockBaseNumber */
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
        /* ID.129 */
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
        32U,    /* NvMNvBlockLength */
        129U,    /* NvMNvBlockBaseNumber */
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
        /* ID.130 */
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
        32U,    /* NvMNvBlockLength */
        130U,    /* NvMNvBlockBaseNumber */
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
        /* ID.131 */
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
        32U,    /* NvMNvBlockLength */
        131U,    /* NvMNvBlockBaseNumber */
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
        /* ID.132 */
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
        32U,    /* NvMNvBlockLength */
        132U,    /* NvMNvBlockBaseNumber */
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
        /* ID.133 */
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
        32U,    /* NvMNvBlockLength */
        133U,    /* NvMNvBlockBaseNumber */
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
        /* ID.134 */
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
        32U,    /* NvMNvBlockLength */
        134U,    /* NvMNvBlockBaseNumber */
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
        /* ID.135 */
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
        32U,    /* NvMNvBlockLength */
        135U,    /* NvMNvBlockBaseNumber */
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
        /* ID.136 */
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
        32U,    /* NvMNvBlockLength */
        136U,    /* NvMNvBlockBaseNumber */
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
        /* ID.137 */
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
        32U,    /* NvMNvBlockLength */
        137U,    /* NvMNvBlockBaseNumber */
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
        /* ID.138 */
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
        32U,    /* NvMNvBlockLength */
        138U,    /* NvMNvBlockBaseNumber */
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
        /* ID.139 */
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
        32U,    /* NvMNvBlockLength */
        139U,    /* NvMNvBlockBaseNumber */
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
        /* ID.140 */
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
        32U,    /* NvMNvBlockLength */
        140U,    /* NvMNvBlockBaseNumber */
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
        /* ID.141 */
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
        32U,    /* NvMNvBlockLength */
        141U,    /* NvMNvBlockBaseNumber */
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
        /* ID.142 */
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
        32U,    /* NvMNvBlockLength */
        142U,    /* NvMNvBlockBaseNumber */
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
        /* ID.143 */
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
        32U,    /* NvMNvBlockLength */
        143U,    /* NvMNvBlockBaseNumber */
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
        /* ID.144 */
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
        32U,    /* NvMNvBlockLength */
        144U,    /* NvMNvBlockBaseNumber */
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
        /* ID.145 */
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
        32U,    /* NvMNvBlockLength */
        145U,    /* NvMNvBlockBaseNumber */
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
        /* ID.146 */
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
        32U,    /* NvMNvBlockLength */
        146U,    /* NvMNvBlockBaseNumber */
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
        /* ID.147 */
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
        32U,    /* NvMNvBlockLength */
        147U,    /* NvMNvBlockBaseNumber */
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
        /* ID.148 */
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
        32U,    /* NvMNvBlockLength */
        148U,    /* NvMNvBlockBaseNumber */
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
        /* ID.149 */
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
        32U,    /* NvMNvBlockLength */
        149U,    /* NvMNvBlockBaseNumber */
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
        /* ID.150 */
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
        32U,    /* NvMNvBlockLength */
        150U,    /* NvMNvBlockBaseNumber */
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
        /* ID.151 */
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
        32U,    /* NvMNvBlockLength */
        151U,    /* NvMNvBlockBaseNumber */
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
        /* ID.152 */
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
        32U,    /* NvMNvBlockLength */
        152U,    /* NvMNvBlockBaseNumber */
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
        /* ID.153 */
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
        32U,    /* NvMNvBlockLength */
        153U,    /* NvMNvBlockBaseNumber */
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
        /* ID.154 */
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
        32U,    /* NvMNvBlockLength */
        154U,    /* NvMNvBlockBaseNumber */
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
        /* ID.155 */
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
        32U,    /* NvMNvBlockLength */
        155U,    /* NvMNvBlockBaseNumber */
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
        /* ID.156 */
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
        156U,    /* NvMNvBlockBaseNumber */
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
        /* ID.157 */
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
        157U,    /* NvMNvBlockBaseNumber */
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
        /* ID.158 */
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
        8U,    /* NvMNvBlockLength */
        158U,    /* NvMNvBlockBaseNumber */
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
        /* ID.159 */
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
        8U,    /* NvMNvBlockLength */
        159U,    /* NvMNvBlockBaseNumber */
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
        /* ID.160 */
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
        32U,    /* NvMNvBlockLength */
        160U,    /* NvMNvBlockBaseNumber */
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
        /* ID.161 */
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
        32U,    /* NvMNvBlockLength */
        161U,    /* NvMNvBlockBaseNumber */
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
        /* ID.162 */
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
        162U,    /* NvMNvBlockBaseNumber */
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
        /* ID.163 */
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
        163U,    /* NvMNvBlockBaseNumber */
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
        /* ID.164 */
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
        8U,    /* NvMNvBlockLength */
        164U,    /* NvMNvBlockBaseNumber */
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
        /* ID.165 */
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
        8U,    /* NvMNvBlockLength */
        165U,    /* NvMNvBlockBaseNumber */
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
        /* ID.166 */
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
        32U,    /* NvMNvBlockLength */
        166U,    /* NvMNvBlockBaseNumber */
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
        /* ID.167 */
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
        32U,    /* NvMNvBlockLength */
        167U,    /* NvMNvBlockBaseNumber */
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
        /* ID.168 */
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
        32U,    /* NvMNvBlockLength */
        168U,    /* NvMNvBlockBaseNumber */
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
        /* ID.169 */
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
        32U,    /* NvMNvBlockLength */
        169U,    /* NvMNvBlockBaseNumber */
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
        /* ID.170 */
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
        170U,    /* NvMNvBlockBaseNumber */
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
        /* ID.171 */
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
        171U,    /* NvMNvBlockBaseNumber */
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
        /* ID.172 */
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
        172U,    /* NvMNvBlockBaseNumber */
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
        /* ID.173 */
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
        173U,    /* NvMNvBlockBaseNumber */
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
        /* ID.174 */
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
        174U,    /* NvMNvBlockBaseNumber */
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
        /* ID.175 */
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
        175U,    /* NvMNvBlockBaseNumber */
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
        /* ID.176 */
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
        176U,    /* NvMNvBlockBaseNumber */
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
        /* ID.177 */
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
        177U,    /* NvMNvBlockBaseNumber */
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
        /* ID.178 */
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
        178U,    /* NvMNvBlockBaseNumber */
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
        /* ID.179 */
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
        179U,    /* NvMNvBlockBaseNumber */
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
        /* ID.180 */
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
        180U,    /* NvMNvBlockBaseNumber */
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
        /* ID.181 */
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
        181U,    /* NvMNvBlockBaseNumber */
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
        /* ID.182 */
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
        182U,    /* NvMNvBlockBaseNumber */
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
        /* ID.183 */
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
        183U,    /* NvMNvBlockBaseNumber */
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
        /* ID.184 */
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
        184U,    /* NvMNvBlockBaseNumber */
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
        /* ID.185 */
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
        185U,    /* NvMNvBlockBaseNumber */
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
        /* ID.186 */
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
        186U,    /* NvMNvBlockBaseNumber */
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
        /* ID.187 */
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
        187U,    /* NvMNvBlockBaseNumber */
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
        /* ID.188 */
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
        188U,    /* NvMNvBlockBaseNumber */
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
        /* ID.189 */
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
        189U,    /* NvMNvBlockBaseNumber */
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
        /* ID.190 */
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
        8U,    /* NvMNvBlockLength */
        190U,    /* NvMNvBlockBaseNumber */
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
        /* ID.191 */
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
        8U,    /* NvMNvBlockLength */
        191U,    /* NvMNvBlockBaseNumber */
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
        /* ID.192 */
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
        8U,    /* NvMNvBlockLength */
        192U,    /* NvMNvBlockBaseNumber */
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
        /* ID.193 */
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
        8U,    /* NvMNvBlockLength */
        193U,    /* NvMNvBlockBaseNumber */
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
        /* ID.194 */
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
        8U,    /* NvMNvBlockLength */
        194U,    /* NvMNvBlockBaseNumber */
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
        /* ID.195 */
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
        8U,    /* NvMNvBlockLength */
        195U,    /* NvMNvBlockBaseNumber */
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
        /* ID.196 */
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
        8U,    /* NvMNvBlockLength */
        196U,    /* NvMNvBlockBaseNumber */
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
        /* ID.197 */
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
        8U,    /* NvMNvBlockLength */
        197U,    /* NvMNvBlockBaseNumber */
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
        /* ID.198 */
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
        8U,    /* NvMNvBlockLength */
        198U,    /* NvMNvBlockBaseNumber */
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
        /* ID.199 */
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
        8U,    /* NvMNvBlockLength */
        199U,    /* NvMNvBlockBaseNumber */
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
        /* ID.200 */
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
        8U,    /* NvMNvBlockLength */
        200U,    /* NvMNvBlockBaseNumber */
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
        /* ID.201 */
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
        8U,    /* NvMNvBlockLength */
        201U,    /* NvMNvBlockBaseNumber */
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
        /* ID.202 */
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
        8U,    /* NvMNvBlockLength */
        202U,    /* NvMNvBlockBaseNumber */
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
        /* ID.203 */
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
        8U,    /* NvMNvBlockLength */
        203U,    /* NvMNvBlockBaseNumber */
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
        /* ID.204 */
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
        8U,    /* NvMNvBlockLength */
        204U,    /* NvMNvBlockBaseNumber */
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
        /* ID.205 */
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
        8U,    /* NvMNvBlockLength */
        205U,    /* NvMNvBlockBaseNumber */
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
        /* ID.206 */
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
        8U,    /* NvMNvBlockLength */
        206U,    /* NvMNvBlockBaseNumber */
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
        /* ID.207 */
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
        8U,    /* NvMNvBlockLength */
        207U,    /* NvMNvBlockBaseNumber */
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
        /* ID.208 */
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
        8U,    /* NvMNvBlockLength */
        208U,    /* NvMNvBlockBaseNumber */
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
        /* ID.209 */
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
        8U,    /* NvMNvBlockLength */
        209U,    /* NvMNvBlockBaseNumber */
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
        /* ID.210 */
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
        32U,    /* NvMNvBlockLength */
        210U,    /* NvMNvBlockBaseNumber */
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
        /* ID.211 */
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
        32U,    /* NvMNvBlockLength */
        211U,    /* NvMNvBlockBaseNumber */
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
        /* ID.212 */
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
        32U,    /* NvMNvBlockLength */
        212U,    /* NvMNvBlockBaseNumber */
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
        /* ID.213 */
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
        32U,    /* NvMNvBlockLength */
        213U,    /* NvMNvBlockBaseNumber */
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
        /* ID.214 */
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
        32U,    /* NvMNvBlockLength */
        214U,    /* NvMNvBlockBaseNumber */
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
        /* ID.215 */
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
        32U,    /* NvMNvBlockLength */
        215U,    /* NvMNvBlockBaseNumber */
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
        /* ID.216 */
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
        32U,    /* NvMNvBlockLength */
        216U,    /* NvMNvBlockBaseNumber */
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
        /* ID.217 */
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
        32U,    /* NvMNvBlockLength */
        217U,    /* NvMNvBlockBaseNumber */
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
        /* ID.218 */
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
        32U,    /* NvMNvBlockLength */
        218U,    /* NvMNvBlockBaseNumber */
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
        /* ID.219 */
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
        32U,    /* NvMNvBlockLength */
        219U,    /* NvMNvBlockBaseNumber */
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
        /* ID.220 */
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
        32U,    /* NvMNvBlockLength */
        220U,    /* NvMNvBlockBaseNumber */
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
        /* ID.221 */
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
        32U,    /* NvMNvBlockLength */
        221U,    /* NvMNvBlockBaseNumber */
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
        /* ID.222 */
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
        32U,    /* NvMNvBlockLength */
        222U,    /* NvMNvBlockBaseNumber */
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
        /* ID.223 */
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
        32U,    /* NvMNvBlockLength */
        223U,    /* NvMNvBlockBaseNumber */
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
        /* ID.224 */
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
        32U,    /* NvMNvBlockLength */
        224U,    /* NvMNvBlockBaseNumber */
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
        /* ID.225 */
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
        32U,    /* NvMNvBlockLength */
        225U,    /* NvMNvBlockBaseNumber */
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
        /* ID.226 */
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
        32U,    /* NvMNvBlockLength */
        226U,    /* NvMNvBlockBaseNumber */
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
        /* ID.227 */
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
        32U,    /* NvMNvBlockLength */
        227U,    /* NvMNvBlockBaseNumber */
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
        /* ID.228 */
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
        32U,    /* NvMNvBlockLength */
        228U,    /* NvMNvBlockBaseNumber */
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
        /* ID.229 */
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
        32U,    /* NvMNvBlockLength */
        229U,    /* NvMNvBlockBaseNumber */
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
        /* ID.230 */
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
        32U,    /* NvMNvBlockLength */
        230U,    /* NvMNvBlockBaseNumber */
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
        /* ID.231 */
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
        32U,    /* NvMNvBlockLength */
        231U,    /* NvMNvBlockBaseNumber */
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
        /* ID.232 */
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
        32U,    /* NvMNvBlockLength */
        232U,    /* NvMNvBlockBaseNumber */
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
        /* ID.233 */
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
        32U,    /* NvMNvBlockLength */
        233U,    /* NvMNvBlockBaseNumber */
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
        /* ID.234 */
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
        32U,    /* NvMNvBlockLength */
        234U,    /* NvMNvBlockBaseNumber */
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
        /* ID.235 */
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
        32U,    /* NvMNvBlockLength */
        235U,    /* NvMNvBlockBaseNumber */
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
        /* ID.236 */
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
        32U,    /* NvMNvBlockLength */
        236U,    /* NvMNvBlockBaseNumber */
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
        /* ID.237 */
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
        32U,    /* NvMNvBlockLength */
        237U,    /* NvMNvBlockBaseNumber */
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
        /* ID.238 */
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
        32U,    /* NvMNvBlockLength */
        238U,    /* NvMNvBlockBaseNumber */
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
        /* ID.239 */
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
        32U,    /* NvMNvBlockLength */
        239U,    /* NvMNvBlockBaseNumber */
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
        /* ID.240 */
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
        32U,    /* NvMNvBlockLength */
        240U,    /* NvMNvBlockBaseNumber */
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
        /* ID.241 */
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
        32U,    /* NvMNvBlockLength */
        241U,    /* NvMNvBlockBaseNumber */
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
        /* ID.242 */
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
        32U,    /* NvMNvBlockLength */
        242U,    /* NvMNvBlockBaseNumber */
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
        /* ID.243 */
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
        32U,    /* NvMNvBlockLength */
        243U,    /* NvMNvBlockBaseNumber */
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
        /* ID.244 */
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
        32U,    /* NvMNvBlockLength */
        244U,    /* NvMNvBlockBaseNumber */
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
        /* ID.245 */
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
        32U,    /* NvMNvBlockLength */
        245U,    /* NvMNvBlockBaseNumber */
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
        /* ID.246 */
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
        32U,    /* NvMNvBlockLength */
        246U,    /* NvMNvBlockBaseNumber */
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
        /* ID.247 */
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
        32U,    /* NvMNvBlockLength */
        247U,    /* NvMNvBlockBaseNumber */
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
        /* ID.248 */
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
        32U,    /* NvMNvBlockLength */
        248U,    /* NvMNvBlockBaseNumber */
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
        /* ID.249 */
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
        32U,    /* NvMNvBlockLength */
        249U,    /* NvMNvBlockBaseNumber */
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
        /* ID.250 */
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
        32U,    /* NvMNvBlockLength */
        250U,    /* NvMNvBlockBaseNumber */
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
        /* ID.251 */
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
        32U,    /* NvMNvBlockLength */
        251U,    /* NvMNvBlockBaseNumber */
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
        /* ID.252 */
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
        32U,    /* NvMNvBlockLength */
        252U,    /* NvMNvBlockBaseNumber */
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
        /* ID.253 */
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
        32U,    /* NvMNvBlockLength */
        253U,    /* NvMNvBlockBaseNumber */
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
        /* ID.254 */
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
        32U,    /* NvMNvBlockLength */
        254U,    /* NvMNvBlockBaseNumber */
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
        /* ID.255 */
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
        32U,    /* NvMNvBlockLength */
        255U,    /* NvMNvBlockBaseNumber */
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
        /* ID.256 */
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
        32U,    /* NvMNvBlockLength */
        256U,    /* NvMNvBlockBaseNumber */
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
        /* ID.257 */
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
        32U,    /* NvMNvBlockLength */
        257U,    /* NvMNvBlockBaseNumber */
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
        /* ID.258 */
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
        32U,    /* NvMNvBlockLength */
        258U,    /* NvMNvBlockBaseNumber */
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
        /* ID.259 */
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
        32U,    /* NvMNvBlockLength */
        259U,    /* NvMNvBlockBaseNumber */
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
        /* ID.260 */
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
        32U,    /* NvMNvBlockLength */
        260U,    /* NvMNvBlockBaseNumber */
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
        /* ID.261 */
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
        32U,    /* NvMNvBlockLength */
        261U,    /* NvMNvBlockBaseNumber */
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
        /* ID.262 */
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
        32U,    /* NvMNvBlockLength */
        262U,    /* NvMNvBlockBaseNumber */
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
        /* ID.263 */
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
        32U,    /* NvMNvBlockLength */
        263U,    /* NvMNvBlockBaseNumber */
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
        /* ID.264 */
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
        32U,    /* NvMNvBlockLength */
        264U,    /* NvMNvBlockBaseNumber */
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
        /* ID.265 */
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
        32U,    /* NvMNvBlockLength */
        265U,    /* NvMNvBlockBaseNumber */
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
        /* ID.266 */
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
        32U,    /* NvMNvBlockLength */
        266U,    /* NvMNvBlockBaseNumber */
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
        /* ID.267 */
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
        32U,    /* NvMNvBlockLength */
        267U,    /* NvMNvBlockBaseNumber */
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
        /* ID.268 */
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
        32U,    /* NvMNvBlockLength */
        268U,    /* NvMNvBlockBaseNumber */
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
        /* ID.269 */
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
        32U,    /* NvMNvBlockLength */
        269U,    /* NvMNvBlockBaseNumber */
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
        /* ID.270 */
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
        32U,    /* NvMNvBlockLength */
        270U,    /* NvMNvBlockBaseNumber */
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
        /* ID.271 */
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
        32U,    /* NvMNvBlockLength */
        271U,    /* NvMNvBlockBaseNumber */
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
        /* ID.272 */
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
        32U,    /* NvMNvBlockLength */
        272U,    /* NvMNvBlockBaseNumber */
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
        /* ID.273 */
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
        273U,    /* NvMNvBlockBaseNumber */
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
        /* ID.274 */
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
        8U,    /* NvMNvBlockLength */
        274U,    /* NvMNvBlockBaseNumber */
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
        /* ID.275 */
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
        32U,    /* NvMNvBlockLength */
        275U,    /* NvMNvBlockBaseNumber */
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
