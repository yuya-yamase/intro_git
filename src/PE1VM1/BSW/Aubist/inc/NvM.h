/* NvM.h v2-1-0                                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/HEADER                                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_H
#define     NVM_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM_Types.h>
#include "../NvM/cfg/NvM_Cfg.h"
#include "../NvM/cfg/NvM_Lcfg.h"
#include "../NvM/cfg/NvM_Wcfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_VENDOR_ID                   (0x0053U)
#define NVM_MODULE_ID                   (0x0014U)
#define NVM_AR_RELEASE_MAJOR_VERSION    (0x04U)
#define NVM_AR_RELEASE_MINOR_VERSION    (0x05U)
#define NVM_AR_RELEASE_REVISION_VERSION (0x00U)
#define NVM_SW_MAJOR_VERSION            (0x02U)
#define NVM_SW_MINOR_VERSION            (0x01U)
#define NVM_SW_PATCH_VERSION            (0x00U)

/* NvM_SetDataIndex */
#if ( ( NVM_USE_DATASET_BLOCK == STD_ON ) && ( ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_2 ) || ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 ) ) )
#define NVM_VALID_SET_DATA_INDEX_API (STD_ON)
#else
#define NVM_VALID_SET_DATA_INDEX_API (STD_OFF)
#endif

/* NvM_GetDataIndex */
#if ( ( NVM_USE_DATASET_BLOCK == STD_ON )  && ( ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_2 ) || ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 ) ) )
#define NVM_VALID_GET_DATA_INDEX_API (STD_ON)
#else
#define NVM_VALID_GET_DATA_INDEX_API (STD_OFF)
#endif

/* NvM_SetBlockProtection */
#if ( ( NVM_USE_PROTECTION == STD_ON ) && ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 ) )
#define NVM_VALID_SET_BLOCK_PROTECTION_API (STD_ON)
#else
#define NVM_VALID_SET_BLOCK_PROTECTION_API (STD_OFF)
#endif

/* NvM_GetErrorStatus */
#define NVM_VALID_GET_ERROR_STATUS_API (STD_ON)

/* NvM_SetRamBlockStatus */
#if ( NVM_SET_RAM_BLOCK_STATUS_API == STD_ON )
#define NVM_VALID_SET_RAM_BLOCK_STATUS_API (STD_ON)
#else
#define NVM_VALID_SET_RAM_BLOCK_STATUS_API (STD_OFF)
#endif

/* NvM_SetBlockLockStatus  */
#define NVM_VALID_SET_BLOCK_LOCK_STATUS_API (STD_ON)

/* NvM_ReadBlock */
#if ( ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_2 ) || ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 ) )
#define NVM_VALID_READ_BLOCK_API (STD_ON)
#else
#define NVM_VALID_READ_BLOCK_API (STD_OFF)
#endif

/* NvM_WriteBlock */
#if ( ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_2 ) || ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 ) )
#define NVM_VALID_WRITE_BLOCK_API (STD_ON)
#else
#define NVM_VALID_WRITE_BLOCK_API (STD_OFF)
#endif

/* NvM_RestoreBlockDefaults */
#if ( ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_2 ) || ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 ) )
#define NVM_VALID_RESTORE_BLOCK_DEFAULTS_API (STD_ON)
#else
#define NVM_VALID_RESTORE_BLOCK_DEFAULTS_API (STD_OFF)
#endif

/* NvM_EraseNvBlock */
#if ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 )
#define NVM_VALID_ERASE_NV_BLOCK_API (STD_ON)
#else
#define NVM_VALID_ERASE_NV_BLOCK_API (STD_OFF)
#endif

/* NvM_InvalidateNvBlock */
#if ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 )
#define NVM_VALID_INVALIDATE_NV_BLOCK_API (STD_ON)
#else
#define NVM_VALID_INVALIDATE_NV_BLOCK_API (STD_OFF)
#endif

/* NvM_CancelJobs */
#if ( ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_2 ) || ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 ) )
#define NVM_VALID_CANCEL_JOBS_API (STD_ON)
#else
#define NVM_VALID_CANCEL_JOBS_API (STD_OFF)
#endif

/* NvM_ReadPRAMBlock */
#if ( ( NVM_USE_PRAM_BLOCK_API == STD_ON ) && ( ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_2 ) || ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 ) ) )
#define NVM_VALID_READ_PRAM_BLOCK_API (STD_ON)
#else
#define NVM_VALID_READ_PRAM_BLOCK_API (STD_OFF)
#endif

/* NvM_WritePRAMBlock */
#if ( ( NVM_USE_PRAM_BLOCK_API == STD_ON ) && ( ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_2 ) || ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 ) ) )
#define NVM_VALID_WRITE_PRAM_BLOCK_API (STD_ON)
#else
#define NVM_VALID_WRITE_PRAM_BLOCK_API (STD_OFF)
#endif

/* NvM_RestorePRAMBlockDefaults */
#if ( ( NVM_USE_PRAM_BLOCK_API == STD_ON ) && ( ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_2 ) || ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 ) ) )
#define NVM_VALID_RESTORE_PRAM_BLOCK_DEFAULTS_API (STD_ON)
#else
#define NVM_VALID_RESTORE_PRAM_BLOCK_DEFAULTS_API (STD_OFF)
#endif

/* NvM_ReadAll */
#define NVM_VALID_READ_ALL_API (STD_ON)

/* NvM_WriteAll */
#if ( NVM_WRITE_ALL_API == STD_ON )
#define NVM_VALID_WRITE_ALL_API (STD_ON)
#else
#define NVM_VALID_WRITE_ALL_API (STD_OFF)
#endif

/* NvM_CancelWriteAll */
#if ( NVM_WRITE_ALL_API == STD_ON )
#define NVM_VALID_CANCEL_WRITE_ALL_API (STD_ON)
#else
#define NVM_VALID_CANCEL_WRITE_ALL_API (STD_OFF)
#endif

/* NvM_ValidateAll */
#if ( ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_2 ) || ( NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 ) )
#define NVM_VALID_VALIDATE_ALL_API (STD_ON)
#else
#define NVM_VALID_VALIDATE_ALL_API (STD_OFF)
#endif

/* NvM_GetVersionInfo */
#if ( NVM_VERSION_INFO_API == STD_ON )
#define NVM_VALID_GET_VERSION_INFO_API (STD_ON)
#else
#define NVM_VALID_GET_VERSION_INFO_API (STD_OFF)
#endif

#define NVM_VALID_ABORT_JOBS_API (STD_ON)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    uint32      dummy;
} NvM_ConfigType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE_TRUST
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE_TRUST )
NvM_PreInit( void );

#define NVM_STOP_SEC_CODE_TRUST
#include <NvM_MemMap.h>

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Init(
    P2CONST( NvM_ConfigType, AUTOMATIC, NVM_CONFIG_DATA ) ConfigPtr
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_SetDataIndex(
    NvM_BlockIdType BlockId,
    uint8 DataIndex
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_GetDataIndex(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) DataIndexPtr
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_SetBlockProtection(
    NvM_BlockIdType BlockId,
    boolean ProtectionEnabled
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_GetErrorStatus(
    NvM_BlockIdType BlockId,
    P2VAR( NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA ) RequestResultPtr
);

FUNC( void, NVM_CODE )
NvM_GetVersionInfo(
    P2VAR( Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA ) versioninfo
);

#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_SetRamBlockStatus(
    NvM_BlockIdType BlockId,
    boolean BlockChanged
);
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */

FUNC( void, NVM_CODE )
NvM_SetBlockLockStatus(
    NvM_BlockIdType BlockId,
    boolean BlockLocked
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_CancelJobs(
    NvM_BlockIdType BlockId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_ReadBlock(
    NvM_BlockIdType BlockId,
    P2VAR( void, AUTOMATIC, NVM_APPL_DATA ) NvM_DstPtr
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_WriteBlock(
    NvM_BlockIdType BlockId,
    P2CONST( void, AUTOMATIC, TYPEDEF ) NvM_SrcPtr
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_RestoreBlockDefaults(
    NvM_BlockIdType BlockId,
    P2VAR( void, AUTOMATIC, NVM_APPL_DATA ) NvM_DestPtr
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_EraseNvBlock(
    NvM_BlockIdType BlockId
);

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( void, NVM_CODE )
NvM_CancelWriteAll( void );
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

FUNC( Std_ReturnType, NVM_CODE )
NvM_InvalidateNvBlock(
    NvM_BlockIdType BlockId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_ReadPRAMBlock(
    NvM_BlockIdType BlockId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_WritePRAMBlock(
    NvM_BlockIdType BlockId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_RestorePRAMBlockDefaults(
    NvM_BlockIdType BlockId
);

FUNC( void, NVM_CODE )
NvM_ReadAll( void );

#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( void, NVM_CODE )
NvM_WriteAll( void );
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

FUNC( void, NVM_CODE )
NvM_ValidateAll( void );

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2018/10/24                                              */
/*  1-2-0          :2019/08/29                                              */
/*  2-0-0          :2021/05/11                                              */
/*  2-1-0          :2022/08/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
