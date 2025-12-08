/* MemAcc_Cfg.h v2-0-0                                                        */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MemAcc/CFG/HEADER                                           */
/******************************************************************************/
#ifndef MEMACC_CFG_H
#define MEMACC_CFG_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <Mem.h>
#include <Fls.h>
#include "MemAcc_Cfg_Internal.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* MemAccGeneral */
#define MEMACC_64BIT_SUPPORT                    ( STD_OFF )
#define MEMACC_COMPARE_API                      ( STD_OFF )
#define MEMACC_DEV_ERROR_DETECT                 ( STD_OFF )
#define MEMACC_USE_MEMFUNC_PTRTABLE             ( STD_OFF )
#define MEMACC_MAINFUNCTION_PERIOD              ( (uint16)5U )

/* MemAccMemNamePrefix */
#define MEMACC_NAMEPREFIX_CODEFLASH             ( (uint32)1U )

/* MemAccAddressAreaConfiguration */
#define MEMACC_ADDRESS_AREA_MAX                 ( (uint16)2U )

/* RkAddrArea_0001 : Address Area ID=0 */
#define MEMACC_ADDRAREA_0                       ( (uint16)0U )
#define MEMACC_ADDRAREA_PRIORITY_0              ( (uint16)1U )
#define MEMACC_BUF_ALIGNMENT_VAL_0              ( (uint8)0U )

/* RkAddrArea_0002 : Address Area ID=1 */
#define MEMACC_ADDRAREA_1                       ( (uint16)1U )
#define MEMACC_ADDRAREA_PRIORITY_1              ( (uint16)0U )
#define MEMACC_BUF_ALIGNMENT_VAL_1              ( (uint8)0U )

/* RkAddrArea_0001 : Address Area ID=0, Sub Address Area */
#define MEMACC_LOGIC_STARTADDR_0_000            ( (uint32)0x00000000UL )
#define MEMACC_NUM_OF_SECTORS_0_000             ( (uint32)1UL )
#define MEMACC_SECTOR_OFFSET_0_000              ( (uint32)0UL )
#define MEMACC_NAMEPREFIX_0_000                 ( MEMACC_NAMEPREFIX_DATAFLASH )
#define MEMACC_INVOCATION_0_000                 ( MEMACC_INVOKE_DIRECT_STATIC )
#define MEMACC_NUM_OF_ER_RETRY_0_000            ( (uint8)0U )
#define MEMACC_NUM_OF_WR_RETRY_0_000            ( (uint8)0U )
#define MEMACC_USE_ER_BURST_0_000               ( STD_OFF )
#define MEMACC_USE_RE_BURST_0_000               ( STD_OFF )
#define MEMACC_USE_WR_BURST_0_000               ( STD_OFF )
#define MEMACC_SECTORBATCH_REF_0_000            ( NULL_PTR )

/* RkAddrArea_0002 : Address Area ID=1, Sub Address Area */
#define MEMACC_LOGIC_STARTADDR_1_000            ( (uint32)0x00000000UL )
#define MEMACC_NUM_OF_SECTORS_1_000             ( (uint32)1UL )
#define MEMACC_SECTOR_OFFSET_1_000              ( (uint32)0UL )
#define MEMACC_NAMEPREFIX_1_000                 ( MEMACC_NAMEPREFIX_CODEFLASH )
#define MEMACC_INVOCATION_1_000                 ( MEMACC_INVOKE_DIRECT_STATIC )
#define MEMACC_NUM_OF_ER_RETRY_1_000            ( (uint8)0U )
#define MEMACC_NUM_OF_WR_RETRY_1_000            ( (uint8)0U )
#define MEMACC_USE_ER_BURST_1_000               ( STD_OFF )
#define MEMACC_USE_RE_BURST_1_000               ( STD_OFF )
#define MEMACC_USE_WR_BURST_1_000               ( STD_OFF )
#define MEMACC_SECTORBATCH_REF_1_000            ( NULL_PTR )

/* Mem MAX Bank */
#define MEMACC_MEM_BANK_MAX                     ( MEM_BANK_MAX_NUM )

/* Mem Instance Information */
#define MEMACC_MEM_INSTANCEID_0                 ( MEM_INSTANCEID_0 )

/* Sector Batch Configuration Information */
#define MEMACC_MEM_READ_PAGE_SIZE_0      ( MEM_READ_PAGE_SIZE_0_000 )
#define MEMACC_MEM_WRITEPAGE_SIZE_0      ( MEM_WRITE_PAGE_SIZE_0_000 )
#define MEMACC_MEM_ERASESECTOR_SIZE_0    ( MEM_ERASESECTOR_SIZE_0_000 )
#define MEMACC_MEM_ERASE_CYCLES_0        ( MEM_NERASE_CYCLES_0_000 )
#define MEMACC_MEM_START_ADDRESS_0       ( MEM_START_ADDRESS_0_000 )
#define MEMACC_MEM_NUMBER_OF_SECTORS_0   ( MEM_NUMBER_OF_SECTORS_0_000 )
#define MEMACC_MEM_READ_BURST_SIZE_0     ( MEM_READ_BURST_SIZE_0_000 )
#define MEMACC_MEM_WRITE_BURST_SIZE_0    ( MEM_WRITE_BURST_SIZE_0_000 )
#define MEMACC_MEM_ERASE_BURST_SIZE_0    ( MEM_ERASE_BURST_SIZE_0_000 )

#if (MEMACC_MEM_BANK_MAX > 1U)
#define MEMACC_MEM_READ_PAGE_SIZE_1      ( MEM_READ_PAGE_SIZE_0_001 )
#define MEMACC_MEM_WRITEPAGE_SIZE_1      ( MEM_WRITE_PAGE_SIZE_0_001 )
#define MEMACC_MEM_ERASESECTOR_SIZE_1    ( MEM_ERASESECTOR_SIZE_0_001 )
#define MEMACC_MEM_ERASE_CYCLES_1        ( MEM_NERASE_CYCLES_0_001 )
#define MEMACC_MEM_START_ADDRESS_1       ( MEM_START_ADDRESS_0_001 )
#define MEMACC_MEM_NUMBER_OF_SECTORS_1   ( MEM_NUMBER_OF_SECTORS_0_001 )
#define MEMACC_MEM_READ_BURST_SIZE_1     ( MEM_READ_BURST_SIZE_0_001 )
#define MEMACC_MEM_WRITE_BURST_SIZE_1    ( MEM_WRITE_BURST_SIZE_0_001 )
#define MEMACC_MEM_ERASE_BURST_SIZE_1    ( MEM_ERASE_BURST_SIZE_0_001 )
#endif

#if (MEMACC_MEM_BANK_MAX > 2U)
#define MEMACC_MEM_READ_PAGE_SIZE_2      ( MEM_READ_PAGE_SIZE_0_002 )
#define MEMACC_MEM_WRITEPAGE_SIZE_2      ( MEM_WRITE_PAGE_SIZE_0_002 )
#define MEMACC_MEM_ERASESECTOR_SIZE_2    ( MEM_ERASESECTOR_SIZE_0_002 )
#define MEMACC_MEM_ERASE_CYCLES_2        ( MEM_NERASE_CYCLES_0_002 )
#define MEMACC_MEM_START_ADDRESS_2       ( MEM_START_ADDRESS_0_002 )
#define MEMACC_MEM_NUMBER_OF_SECTORS_2   ( MEM_NUMBER_OF_SECTORS_0_002 )
#define MEMACC_MEM_READ_BURST_SIZE_2     ( MEM_READ_BURST_SIZE_0_002 )
#define MEMACC_MEM_WRITE_BURST_SIZE_2    ( MEM_WRITE_BURST_SIZE_0_002 )
#define MEMACC_MEM_ERASE_BURST_SIZE_2    ( MEM_ERASE_BURST_SIZE_0_002 )
#endif

#if (MEMACC_MEM_BANK_MAX > 3U)
#define MEMACC_MEM_READ_PAGE_SIZE_3      ( MEM_READ_PAGE_SIZE_0_003 )
#define MEMACC_MEM_WRITEPAGE_SIZE_3      ( MEM_WRITE_PAGE_SIZE_0_003 )
#define MEMACC_MEM_ERASESECTOR_SIZE_3    ( MEM_ERASESECTOR_SIZE_0_003 )
#define MEMACC_MEM_ERASE_CYCLES_3        ( MEM_NERASE_CYCLES_0_003 )
#define MEMACC_MEM_START_ADDRESS_3       ( MEM_START_ADDRESS_0_003 )
#define MEMACC_MEM_NUMBER_OF_SECTORS_3   ( MEM_NUMBER_OF_SECTORS_0_003 )
#define MEMACC_MEM_READ_BURST_SIZE_3     ( MEM_READ_BURST_SIZE_0_003 )
#define MEMACC_MEM_WRITE_BURST_SIZE_3    ( MEM_WRITE_BURST_SIZE_0_003 )
#define MEMACC_MEM_ERASE_BURST_SIZE_3    ( MEM_ERASE_BURST_SIZE_0_003 )
#endif

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/* Mem Instance Information Container */
typedef struct
{
    uint16                      MemAcc_MemInstanceId;
    P2CONST( AB_83_ConstV MemAcc_Mem_SectorBatchType, AUTOMATIC, TYPEDEF ) MemAcc_MemSectorBatch;
} MemAcc_Mem_InstanceType;

/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>

extern CONST ( AB_83_ConstV MemAcc_SubAddressAreaConfiguration, MEMACC_CONFIG_DATA) MemAcc_SubAddrAreaCfg_0[];
extern CONST ( AB_83_ConstV MemAcc_SubAddressAreaConfiguration, MEMACC_CONFIG_DATA) MemAcc_SubAddrAreaCfg_1[];
extern CONST ( AB_83_ConstV MemAcc_Mem_SectorBatchType, MEMACC_CONFIG_DATA) MemAcc_MemSectorBatch_0[MEMACC_MEM_BANK_MAX];

#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>

extern CONST (AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_SubAddrAreaCfg_0_Size;
extern CONST (AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_SubAddrAreaCfg_1_Size;
extern CONST (AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_AddrAreaCfgSize;
extern CONST (AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_MemSectorBatch_0_Size;
extern CONST (AB_83_ConstV MemAcc_Mem_InstanceType, MEMACC_CONFIG_DATA) MemAcc_MemInstance;

#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>


#endif  /* MEMACC_CFG_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

