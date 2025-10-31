/* Mem_Cfg_h                                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/Mem/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MEM_CFG_H
#define MEM_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define MEM_DEV_ERROR_DETECT                (STD_OFF)               /* Development error detection and notification */

#define MEM_BANK_MAX_NUM                    (2U)                    /* Mem Bank Max Number                          */
#define MEM_INSTANCEID_0                    (0x0000U)               /* MemInstance ID                               */

#define MEM_READ_PAGE_SIZE_0_000            (512U)                  /* Memory Read Page Size                        */
#define MEM_WRITE_PAGE_SIZE_0_000           (512U)                  /* Memory Write Page Size                       */
#define MEM_ERASESECTOR_SIZE_0_000          (16384U)                /* Memory Erase Sector Size                     */
#define MEM_NERASE_CYCLES_0_000             (4294967295U)           /* Number of memory erase cycles                */
#define MEM_START_ADDRESS_0_000             (0x00000000UL)          /* Sector physical start address                */
#define MEM_NUMBER_OF_SECTORS_0_000         (512U)                  /* Number of consecutive sectors                */
#define MEM_READ_BURST_SIZE_0_000           (4294967295U)           /* Memory Read Burst Size                       */
#define MEM_WRITE_BURST_SIZE_0_000          (4294967295U)           /* Memory Write Burst Size                      */
#define MEM_ERASE_BURST_SIZE_0_000          (4294967295U)           /* Memory Erase Burst Size                      */

#define MEM_READ_PAGE_SIZE_0_001            (512U)                  /* Memory Read Page Size                        */
#define MEM_WRITE_PAGE_SIZE_0_001           (512U)                  /* Memory Write Page Size                       */
#define MEM_ERASESECTOR_SIZE_0_001          (16384U)                /* Memory Erase Sector Size                     */
#define MEM_NERASE_CYCLES_0_001             (4294967295U)           /* Number of memory erase cycles                */
#define MEM_START_ADDRESS_0_001             (0x02000000UL)          /* Sector physical start address                */
#define MEM_NUMBER_OF_SECTORS_0_001         (512U)                  /* Number of consecutive sectors                */
#define MEM_READ_BURST_SIZE_0_001           (4294967295U)           /* Memory Read Burst Size                       */
#define MEM_WRITE_BURST_SIZE_0_001          (4294967295U)           /* Memory Write Burst Size                      */
#define MEM_ERASE_BURST_SIZE_0_001          (4294967295U)           /* Memory Erase Burst Size                      */


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

#define MEM_STOP_SEC_CONST_CONFIG_32
#include <Mem_MemMap.h>


#endif  /* MEM_CFG_H */

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

