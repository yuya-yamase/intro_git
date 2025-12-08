/* MemAcc_Cfg.c v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/

#include <MemAcc.h>
#include "MemAcc_Cfg.h"
#include "nvmc_dtf_cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>

/* RkAddrArea_0001 : Address Area ID=0, Sub Address Area */
CONST ( AB_83_ConstV MemAcc_SubAddressAreaConfiguration, MEMACC_CONFIG_DATA) MemAcc_SubAddrAreaCfg_0[] =
{
    {
        MEMACC_LOGIC_STARTADDR_0_000,
        MEMACC_NUM_OF_SECTORS_0_000,
        MEMACC_SECTOR_OFFSET_0_000,
        MEMACC_NAMEPREFIX_0_000,
        MEMACC_INVOCATION_0_000,
        MEMACC_NUM_OF_ER_RETRY_0_000,
        MEMACC_NUM_OF_WR_RETRY_0_000,
        MEMACC_USE_ER_BURST_0_000,
        MEMACC_USE_RE_BURST_0_000,
        MEMACC_USE_WR_BURST_0_000,
        MEMACC_SECTORBATCH_REF_0_000
    }
};

CONST (AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_SubAddrAreaCfg_0_Size = (uint16)(sizeof(MemAcc_SubAddrAreaCfg_0) / sizeof(MemAcc_SubAddrAreaCfg_0[0]));

/* RkAddrArea_0002 : Address Area ID=1, Sub Address Area */
CONST ( AB_83_ConstV MemAcc_SubAddressAreaConfiguration, MEMACC_CONFIG_DATA) MemAcc_SubAddrAreaCfg_1[] =
{
    {
        MEMACC_LOGIC_STARTADDR_1_000,
        MEMACC_NUM_OF_SECTORS_1_000,
        MEMACC_SECTOR_OFFSET_1_000,
        MEMACC_NAMEPREFIX_1_000,
        MEMACC_INVOCATION_1_000,
        MEMACC_NUM_OF_ER_RETRY_1_000,
        MEMACC_NUM_OF_WR_RETRY_1_000,
        MEMACC_USE_ER_BURST_1_000,
        MEMACC_USE_RE_BURST_1_000,
        MEMACC_USE_WR_BURST_1_000,
        MEMACC_SECTORBATCH_REF_1_000
    }
};

CONST (AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_SubAddrAreaCfg_1_Size = (uint16)(sizeof(MemAcc_SubAddrAreaCfg_1) / sizeof(MemAcc_SubAddrAreaCfg_1[0]));


CONST ( AB_83_ConstV MemAcc_AddressAreaConfiguration, MEMACC_CONFIG_DATA) MemAcc_AddrAreaCfg[MEMACC_ADDRESS_AREA_MAX] =
{
    /* RkAddrArea_0001 : Address Area ID=0 */
    {
        MEMACC_ADDRAREA_0,
        MEMACC_ADDRAREA_PRIORITY_0,
        MEMACC_BUF_ALIGNMENT_VAL_0,
        &vd_g_Nvmc_MemAcc_JobEndHook,
        MemAcc_SubAddrAreaCfg_0

    },
    /* RkAddrArea_0002 : Address Area ID=1 */
    {
        MEMACC_ADDRAREA_1,
        MEMACC_ADDRAREA_PRIORITY_1,
        MEMACC_BUF_ALIGNMENT_VAL_1,
        &vd_g_Nvmc_MemAcc_JobEndHook,
        MemAcc_SubAddrAreaCfg_1
    }
};

CONST (AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_AddrAreaCfgSize = (uint16)(sizeof(MemAcc_AddrAreaCfg) / sizeof(MemAcc_AddrAreaCfg[0]));

/* Mem Sector Batch Container */
CONST ( AB_83_ConstV MemAcc_Mem_SectorBatchType, MEMACC_CONFIG_DATA) MemAcc_MemSectorBatch_0[MEMACC_MEM_BANK_MAX] = 
{
    {
        MEMACC_MEM_READ_PAGE_SIZE_0,
        MEMACC_MEM_WRITEPAGE_SIZE_0,
        MEMACC_MEM_ERASESECTOR_SIZE_0,
        MEMACC_MEM_ERASE_CYCLES_0,
        MEMACC_MEM_START_ADDRESS_0,
        MEMACC_MEM_NUMBER_OF_SECTORS_0,
        MEMACC_MEM_READ_BURST_SIZE_0,
        MEMACC_MEM_WRITE_BURST_SIZE_0,
        MEMACC_MEM_ERASE_BURST_SIZE_0
#if (MEMACC_MEM_BANK_MAX > 1U)
    },
    {
        MEMACC_MEM_READ_PAGE_SIZE_1,
        MEMACC_MEM_WRITEPAGE_SIZE_1,
        MEMACC_MEM_ERASESECTOR_SIZE_1,
        MEMACC_MEM_ERASE_CYCLES_1,
        MEMACC_MEM_START_ADDRESS_1,
        MEMACC_MEM_NUMBER_OF_SECTORS_1,
        MEMACC_MEM_READ_BURST_SIZE_1,
        MEMACC_MEM_WRITE_BURST_SIZE_1,
        MEMACC_MEM_ERASE_BURST_SIZE_1
#endif
#if (MEMACC_MEM_BANK_MAX > 2U)
    },
    {
        MEMACC_MEM_READ_PAGE_SIZE_2,
        MEMACC_MEM_WRITEPAGE_SIZE_2,
        MEMACC_MEM_ERASESECTOR_SIZE_2,
        MEMACC_MEM_ERASE_CYCLES_2,
        MEMACC_MEM_START_ADDRESS_2,
        MEMACC_MEM_NUMBER_OF_SECTORS_2,
        MEMACC_MEM_READ_BURST_SIZE_2,
        MEMACC_MEM_WRITE_BURST_SIZE_2,
        MEMACC_MEM_ERASE_BURST_SIZE_2
#endif
#if (MEMACC_MEM_BANK_MAX > 3U)
    },
    {
        MEMACC_MEM_READ_PAGE_SIZE_3,
        MEMACC_MEM_WRITEPAGE_SIZE_3,
        MEMACC_MEM_ERASESECTOR_SIZE_3,
        MEMACC_MEM_ERASE_CYCLES_3,
        MEMACC_MEM_START_ADDRESS_3,
        MEMACC_MEM_NUMBER_OF_SECTORS_3,
        MEMACC_MEM_READ_BURST_SIZE_3,
        MEMACC_MEM_WRITE_BURST_SIZE_3,
        MEMACC_MEM_ERASE_BURST_SIZE_3
#endif
    }
};

CONST (AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_MemSectorBatch_0_Size = (uint16)(sizeof(MemAcc_MemSectorBatch_0) / sizeof(MemAcc_MemSectorBatch_0[0]));

/* Mem Instance Information Container */
CONST (AB_83_ConstV MemAcc_Mem_InstanceType, MEMACC_CONFIG_DATA) MemAcc_MemInstance = 
{
    MEMACC_MEM_INSTANCEID_0,
    &MemAcc_MemSectorBatch_0[0]
};

#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/


