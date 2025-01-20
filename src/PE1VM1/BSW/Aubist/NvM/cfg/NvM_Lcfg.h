/* NvM_Lcfg.h v1-2-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/LCFG/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_LCFG_H
#define     NVM_LCFG_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* NvMMultiBlockCallback */
#if ( NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION != STD_ON )
#define NVM_VALID_MULTI_BLOCK_CALLBACK (STD_ON)
#else
#define NVM_VALID_MULTI_BLOCK_CALLBACK (STD_OFF)
#endif

/* NvMBlockJobPriority */
#if ( NVM_JOB_PRIORITIZATION == STD_ON )
#define NVM_VALID_BLOCK_JOB_PRIORITY  (STD_ON)
#else
#define NVM_VALID_BLOCK_JOB_PRIORITY  (STD_OFF)
#endif

/* NvMRomBlockNum */
#if ( NVM_USE_ROM_BLOCK == STD_ON )
#define NVM_VALID_BLOCK_ROM_BLOCK_NUM (STD_ON)
#else
#define NVM_VALID_BLOCK_ROM_BLOCK_NUM (STD_OFF)
#endif

/* NvMMaxNumOfReadRetries */
#if ( NVM_USE_COMMON_MAX_NUM_OF_READ_RETRIES == STD_OFF )
#define NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES   (STD_ON)
#else
#define NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES   (STD_OFF)
#endif

/* NvMMaxNumOfWriteRetries */
#if ( NVM_USE_COMMON_MAX_NUM_OF_WRITE_RETRIES == STD_OFF )
#define NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES  (STD_ON)
#else
#define NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES  (STD_OFF)
#endif

/* NvMBlockCrcType */
#if ( ( NVM_USE_CRC == STD_ON ) && ( NVM_USE_COMMON_CRC_TYPE == STD_OFF ) )
#define NVM_VALID_BLOCK_CRC_TYPE  (STD_ON)
#else
#define NVM_VALID_BLOCK_CRC_TYPE  (STD_OFF)
#endif

/* NvMWriteVerificationDataSize */
#if ( NVM_USE_COMMON_WRITE_VERIFICATION_DATA_SIZE == STD_OFF )
#define NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE  (STD_ON)
#else
#define NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE  (STD_OFF)
#endif

/* NvMRomBlockDataAddress */
#if ( NVM_USE_ROM_BLOCK == STD_ON )
#define NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS    (STD_ON)
#else
#define NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS    (STD_OFF)
#endif

/* NvMSingleBlockCallback */
#if ( NVM_USE_COMMON_SINGLE_BLOCK_CALLBACK == STD_OFF )
#define NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK (STD_ON)
#else
#define NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK (STD_OFF)
#endif

/* NvMReadRamBlockFromNvCallback */
#if ( ( NVM_USE_SYNC_MECHANISM == STD_ON ) && ( NVM_USE_COMMON_RAM_MIRROR_CALLBACK == STD_OFF ) )
#define NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK   (STD_ON)
#else
#define NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK   (STD_OFF)
#endif

/* NvMWriteRamBlockToNvCallback */
#if ( ( NVM_USE_SYNC_MECHANISM == STD_ON ) && ( NVM_USE_COMMON_RAM_MIRROR_CALLBACK == STD_OFF ) )
#define NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK    (STD_ON)
#else
#define NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK    (STD_OFF)
#endif

/* NvMInitBlockCallback */
#if ( ( NVM_USE_ROM_BLOCK == STD_ON ) && ( NVM_USE_COMMON_INIT_BLOCK_CALLBACK == STD_OFF ) )
#define NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK   (STD_ON)
#else
#define NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK   (STD_OFF)
#endif

/* NvMCommonSingleBlockCallback */
#if ( NVM_USE_COMMON_SINGLE_BLOCK_CALLBACK == STD_ON )
#define NVM_VALID_COMMON_SINGLE_BLOCK_CALLBACK  (STD_ON)
#else
#define NVM_VALID_COMMON_SINGLE_BLOCK_CALLBACK  (STD_OFF)
#endif

/* NvMCommonReadRamBlockFromNvCallback */
#if ( ( NVM_USE_SYNC_MECHANISM == STD_ON ) && ( NVM_USE_COMMON_RAM_MIRROR_CALLBACK == STD_ON ) )
#define NVM_VALID_COMMON_READ_RAM_BLOCK_FROM_NV_CALLBACK    (STD_ON)
#else
#define NVM_VALID_COMMON_READ_RAM_BLOCK_FROM_NV_CALLBACK    (STD_OFF)
#endif

/* NvMCommonWriteRamBlockToNvCallback */
#if ( ( NVM_USE_SYNC_MECHANISM == STD_ON ) && ( NVM_USE_COMMON_RAM_MIRROR_CALLBACK == STD_ON ) )
#define NVM_VALID_COMMON_WRITE_RAM_BLOCK_TO_NV_CALLBACK (STD_ON)
#else
#define NVM_VALID_COMMON_WRITE_RAM_BLOCK_TO_NV_CALLBACK (STD_OFF)
#endif

/* NvMCommonInitBlockCallback */
#if ( ( NVM_USE_ROM_BLOCK == STD_ON ) && ( NVM_USE_COMMON_INIT_BLOCK_CALLBACK == STD_ON ) )
#define NVM_VALID_COMMON_INIT_BLOCK_CALLBACK    (STD_ON)
#else
#define NVM_VALID_COMMON_INIT_BLOCK_CALLBACK    (STD_OFF)
#endif

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef struct{
    NvM_BlockManagementTypeType NvMBlockManagementType;
#if ( NVM_VALID_BLOCK_JOB_PRIORITY == STD_ON )
    uint8 NvMBlockJobPriority;
#endif
    uint8 NvMNvramDeviceId;
    uint8 NvMNvBlockNum;
#if ( NVM_VALID_BLOCK_ROM_BLOCK_NUM == STD_ON )
    uint8 NvMRomBlockNum;
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_READ_RETRIES == STD_ON )
    uint8 NvMMaxNumOfReadRetries;
#endif
#if ( NVM_VALID_BLOCK_MAX_NUM_OF_WRITE_RETRIES == STD_ON )
    uint8 NvMMaxNumOfWriteRetries;
#endif
#if ( NVM_VALID_BLOCK_CRC_TYPE == STD_ON )
    NvM_BlockCrcTypeType NvMBlockCrcType;
#endif
    NvM_RamBlockTypeType RamBlockType;
    uint16 NvMNvBlockLength;
    uint16 NvMNvBlockBaseNumber;
#if ( NVM_VALID_BLOCK_WRITE_VERIFICATION_DATA_SIZE == STD_ON )
    uint16 NvMWriteVerificationDataSize;
#endif
    NvM_BlockFlagsType NvMBlockFlags;
    P2VAR( uint8, NVM_CONST, NVM_APPL_DATA ) NvMRamBlockDataAddress;
#if ( NVM_VALID_BLOCK_ROM_BLOCK_DATA_ADDRESS == STD_ON )
    P2CONST( uint8, NVM_CONST, NVM_APPL_CONST ) NvMRomBlockDataAddress;
#endif
#if ( NVM_VALID_BLOCK_SINGLE_BLOCK_CALLBACK == STD_ON )
    NvM_SingleBlockCallbackType NvMSingleBlockCallback;
#endif
#if ( NVM_VALID_BLOCK_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
    NvM_ReadRamBlockFromNvCallbackType NvMReadRamBlockFromNvCallback;
#endif
#if ( NVM_VALID_BLOCK_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
    NvM_WriteRamBlockToNvCallbackType NvMWriteRamBlockToNvCallback;
#endif
#if ( NVM_VALID_BLOCK_INIT_BLOCK_CALLBACK == STD_ON )
    NvM_InitBlockCallbackType NvMInitBlockCallback;
#endif
}NvM_BlockDescriptorType;

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CONST_CONFIG_32
#include <NvM_MemMap.h>

#if ( NVM_VALID_MULTI_BLOCK_CALLBACK == STD_ON )
extern CONST(AB_83_ConstV NvM_MultiBlockCallbackType, NVM_CONFIG_DATA) NvMMultiBlockCallback;
#endif

#if ( NVM_VALID_COMMON_SINGLE_BLOCK_CALLBACK == STD_ON )
extern CONST(AB_83_ConstV NvM_CommonSingleBlockCallbackType, NVM_CONFIG_DATA) NvMCommonSingleBlockCallback;
#endif

#if ( NVM_VALID_COMMON_READ_RAM_BLOCK_FROM_NV_CALLBACK == STD_ON )
extern CONST(AB_83_ConstV NvM_CommonReadRamBlockFromNvCallbackType, NVM_CONFIG_DATA) NvMCommonReadRamBlockFromNvCallback;
#endif

#if ( NVM_VALID_COMMON_WRITE_RAM_BLOCK_TO_NV_CALLBACK == STD_ON )
extern CONST(AB_83_ConstV NvM_CommonWriteRamBlockToNvCallbackType, NVM_CONFIG_DATA) NvMCommonWriteRamBlockToNvCallback;
#endif

#if ( NVM_VALID_COMMON_INIT_BLOCK_CALLBACK == STD_ON )
extern CONST(AB_83_ConstV NvM_CommonInitBlockCallbackType, NVM_CONFIG_DATA) NvMCommonInitBlockCallback;
#endif

extern CONST(AB_83_ConstV NvM_BlockDescriptorType, NVM_CONFIG_DATA) NvMBlockDescriptors[];
extern CONST(AB_83_ConstV uint16, NVM_CONFIG_DATA) NvMBlockDescriptorsSize;

extern CONST(AB_83_ConstV uint8, NVM_CONST) NvMRepeatMirrorOperations;
extern CONST(AB_83_ConstV uint8, NVM_CONST) NvMDatasetSelectionBits;

#define NVM_STOP_SEC_CONST_CONFIG_32
#include <NvM_MemMap.h>

#endif  /* NVM_LCFG_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2018/10/24                                              */
/*  1-2-0          :2019/08/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
