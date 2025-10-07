/* MemM_Ucfg_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MemM/Ucfg/HEADER                                            */
/******************************************************************************/
#ifndef MEMM_UCFG_H
#define MEMM_UCFG_H


/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <MemM.h>
#include "MemM_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define MEMM_UCFG_ERASETIME_CODEFLS     (179000000UL) /* Microsecond */
#define MEMM_UCFG_ERASETIME_EXTCODEFLS  (179000000UL) /* Microsecond */

#define MEMM_UCFG_WRITETIME_CODEFLS     (179000000UL) /* Microsecond */
#define MEMM_UCFG_WRITETIME_EXTCODEFLS  (179000000UL) /* Microsecond */
#define MEMM_UCFG_WRITETIME_CODERAM     (179000000UL) /* Microsecond */

#define MEMM_UCFG_READTIME_CODEFLS      (179000000UL) /* Microsecond */
#define MEMM_UCFG_READTIME_EXTCODEFLS   (179000000UL) /* Microsecond */
#define MEMM_UCFG_READTIME_CODERAM      (179000000UL) /* Microsecond */

#define MEMM_UCFG_RPGCMPLTTIME          (179000000UL) /* Microsecond */

/* Select guarantee method. Guarantee means taking measures for the case that a power supply is cut off           */
/* MEMM_GRNT_MODE_KEYWORDSTAMP  No_1 : Keyword stamp method                                                       */
/* MEMM_GRNT_MODE_FLASHSTATUS1  No_2 : Flash status method[Overwrite is impossible, There are two Flash statuses] */
/* MEMM_GRNT_MODE_FLASHSTATUS2  No_3 : Flash status method[Overwrite is possible,   There are two Flash statuses] */
/* MEMM_GRNT_MODE_FLASHSTATUS3  No_4 : Flash status method[Overwrite is possible,   There is one Flash status]    */
/* MEMM_GRNT_MODE_FLASHSTATUS4  No_5 : Flash status method[Overwrite is impossible, There is one Flash status]    */
#define MEMM_UCFG_GRNT_MODE             (MEMM_GRNT_MODE_KEYWORDSTAMP)

#define MEMM_UCFG_KEYWORD_BLOCK_SIZE    (0x00004000UL)

#define MEMM_UCFG_MEMORY_AREA_NUM       (4U)

/* Set information about MemoryArea XX [XX : MemoryID]                                   */
/* MEMM_UCFG_MEMORY_ID_XX          : MemoryId       0x00000000-0xFFFFFFFF                */
/* MEMM_UCFG_PHYSICAL_ADDR_XX      : PhysicalAddr   0x00000000-0xFFFFFFFF                */
/* MEMM_UCFG_VIRTUAL_ADDR_XX       : VirtualAddr    0x00000000-0xFFFFFFFF                */
/* MEMM_UCFG_MEMORY_AREA_SIZE_XX   : AreaSize       0x00000000-0xFFFFFFFF                */
/* MEMM_UCFG_GRNT_AREA_1ST_ADDR_XX : Grnt_Addr1     0x00000000-0xFFFFFFFF                */
/* MEMM_UCFG_GRNT_AREA_2ND_ADDR_XX : Grnt_Addr2     0x00000000-0xFFFFFFFF                */
/* MEMM_UCFG_DEVICE_TYPE_XX        : DeviceId       MEMM_DEVICE_TYPE_CODEFLS    [ROM]    */
/*                                                  MEMM_DEVICE_TYPE_EXTCODEFLS [ExtROM] */
/*                                                  MEMM_DEVICE_TYPE_CODERAM    [RAM]    */
/* MemoryArea 0 */
#define MEMM_UCFG_MEMORY_ID_0               (0x00000000UL)
#define MEMM_UCFG_PHYSICAL_ADDR_0           (0xFE000000UL)
#define MEMM_UCFG_VIRTUAL_ADDR_0            (0xFE000000UL)
#define MEMM_UCFG_MEMORY_AREA_SIZE_0        (0x00001000UL)
#define MEMM_UCFG_GRNT_AREA_1ST_ADDR_0      (MEMM_INVALID_ADDR)
#define MEMM_UCFG_GRNT_AREA_2ND_ADDR_0      (MEMM_INVALID_ADDR)
#define MEMM_UCFG_DEVICE_TYPE_0             (MEMM_DEVICE_TYPE_CODERAM)

/* MemoryArea 1 */
#define MEMM_UCFG_MEMORY_ID_1               (0x00000000UL)
#define MEMM_UCFG_PHYSICAL_ADDR_1           (0x00004000UL)
#define MEMM_UCFG_VIRTUAL_ADDR_1            (0x00004000UL)
#define MEMM_UCFG_MEMORY_AREA_SIZE_1        (0x00004000UL)
#define MEMM_UCFG_GRNT_AREA_1ST_ADDR_1      (0x00004000UL)
#define MEMM_UCFG_GRNT_AREA_2ND_ADDR_1      (MEMM_INVALID_ADDR)
#define MEMM_UCFG_DEVICE_TYPE_1             (MEMM_DEVICE_TYPE_CODEFLS)

/* MemoryArea 2 */
#define MEMM_UCFG_MEMORY_ID_2               (0x00000000UL)
#define MEMM_UCFG_PHYSICAL_ADDR_2           (0x00008000UL)
#define MEMM_UCFG_VIRTUAL_ADDR_2            (0x00008000UL)
#define MEMM_UCFG_MEMORY_AREA_SIZE_2        (0x00004000UL)
#define MEMM_UCFG_GRNT_AREA_1ST_ADDR_2      (MEMM_INVALID_ADDR)
#define MEMM_UCFG_GRNT_AREA_2ND_ADDR_2      (MEMM_INVALID_ADDR)
#define MEMM_UCFG_DEVICE_TYPE_2             (MEMM_DEVICE_TYPE_CODEFLS)

/* MemoryArea 3 */
#define MEMM_UCFG_MEMORY_ID_3               (0x00000000UL)
#define MEMM_UCFG_PHYSICAL_ADDR_3           (0x0001C000UL)
#define MEMM_UCFG_VIRTUAL_ADDR_3            (0x0001C000UL)
#define MEMM_UCFG_MEMORY_AREA_SIZE_3        (0x007A4000UL)
#define MEMM_UCFG_GRNT_AREA_1ST_ADDR_3      (MEMM_INVALID_ADDR)
#define MEMM_UCFG_GRNT_AREA_2ND_ADDR_3      (MEMM_INVALID_ADDR)
#define MEMM_UCFG_DEVICE_TYPE_3             (MEMM_DEVICE_TYPE_CODEFLS)


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
#define MEMM_START_SEC_CST
#include <MemM_MemMap.h>

extern CONST(MemM_MemoryAreaConfigType, MEMM_CONFIG_DATA) MemM_Ucfg_MemoryAreaData[MEMM_UCFG_MEMORY_AREA_NUM];

#define MEMM_STOP_SEC_CST
#include <MemM_MemMap.h>

#endif /* MEMM_UCFG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/10/23 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
/**** End of File *************************************************************/

