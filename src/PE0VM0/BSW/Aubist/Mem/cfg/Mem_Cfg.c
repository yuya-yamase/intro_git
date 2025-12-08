/* Mem_Cfg_c                                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/Mem/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mem.h>
#include "../inc/Mem_Internal.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_CONFIG_32
#include <Mem_MemMap.h>

/* [Device Individuality Config] MEM Control Setting Configuration Table */
static CONST (AB_83_ConstV Mem_DevControlSettingType, MEM_CONFIG_DATA) MEM_DEVCFG_CONTROL_DATA =
{
    2U,
    2U
};

/* [Device Individuality Config] MEM Device Individuality Configuration Table */
CONST (AB_83_ConstV Mem_DevConfigType, MEM_CONFIG_DATA) MEM_DEVCFG_DATA =
{
    &MEM_DEVCFG_CONTROL_DATA
};

/**********************************************************************************************/
/* Described from the configuration information of the AUTOSAR_SWS_MemoryDriver specification */
/**********************************************************************************************/
/* Instance Information Container */
CONST(AB_83_ConstV Mem_InstanceType, MEM_CONFIG_DATA) MemInstance =
{
    MEM_BANK_MAX_NUM,                               /* Mem Bank Max Number                          */
    MEM_INSTANCEID_0,                               /* MemInstance ID                               */
    {
        {
            /* [Bank]Sector Batch Configuration Information Container */
            MEM_READ_PAGE_SIZE_0_000,               /* Memory Read Page Size                        */
            MEM_WRITE_PAGE_SIZE_0_000,              /* Memory Write Page Size                       */
            MEM_ERASESECTOR_SIZE_0_000,             /* Memory Erase Sector Size                     */
            MEM_NERASE_CYCLES_0_000,                /* Number of memory erase cycles                */
            MEM_START_ADDRESS_0_000,                /* Sector physical start address                */
            MEM_NUMBER_OF_SECTORS_0_000,            /* Number of consecutive sectors                */
            {    /* Burst Transfer Information Container */
                MEM_READ_BURST_SIZE_0_000,          /* Memory Read Burst Size                       */
                MEM_WRITE_BURST_SIZE_0_000,         /* Memory Write Burst Size                      */
                MEM_ERASE_BURST_SIZE_0_000          /* Memory Erase Burst Size                      */
            }
        },
        {
            /* [Bank]Sector Batch Configuration Information Container */
            MEM_READ_PAGE_SIZE_0_001,               /* Memory Read Page Size                        */
            MEM_WRITE_PAGE_SIZE_0_001,              /* Memory Write Page Size                       */
            MEM_ERASESECTOR_SIZE_0_001,             /* Memory Erase Sector Size                     */
            MEM_NERASE_CYCLES_0_001,                /* Number of memory erase cycles                */
            MEM_START_ADDRESS_0_001,                /* Sector physical start address                */
            MEM_NUMBER_OF_SECTORS_0_001,            /* Number of consecutive sectors                */
            {    /* Burst Transfer Information Container */
                MEM_READ_BURST_SIZE_0_001,          /* Memory Read Burst Size                       */
                MEM_WRITE_BURST_SIZE_0_001,         /* Memory Write Burst Size                      */
                MEM_ERASE_BURST_SIZE_0_001          /* Memory Erase Burst Size                      */
            }
        }
    }
};

/* Public Information Container */
CONST(AB_83_ConstV Mem_PublishedInformationType, MEM_CONFIG_DATA) MemPublishedInformation =
{
    0xFFFFFFFFUL                                    /* Memory Erase Settings                        */
};

#define MEM_STOP_SEC_CONST_CONFIG_32
#include <Mem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/*  v1.01          :2025/04/14                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

