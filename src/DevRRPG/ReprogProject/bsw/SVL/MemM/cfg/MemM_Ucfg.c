/* MemM_Ucfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MemM/Ucfg/CODE                                              */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <MemM.h>
#include "MemM_Local.h"
#include "MemM_Cfg.h"
#include "MemM_Ucfg.h"


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
#define MEMM_START_SEC_VAR
#include <MemM_MemMap.h>

#define MEMM_STOP_SEC_VAR
#include <MemM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define MEMM_START_SEC_CST
#include <MemM_MemMap.h>

CONST(MemM_MemoryAreaConfigType, MEMM_CONFIG_DATA) MemM_Ucfg_MemoryAreaData[MEMM_UCFG_MEMORY_AREA_NUM] = {
    {
        MEMM_UCFG_MEMORY_ID_0,
        MEMM_UCFG_VIRTUAL_ADDR_0,
        MEMM_UCFG_PHYSICAL_ADDR_0,
        MEMM_UCFG_MEMORY_AREA_SIZE_0,
        { MEMM_UCFG_GRNT_AREA_1ST_ADDR_0, MEMM_UCFG_GRNT_AREA_2ND_ADDR_0 },
        MEMM_UCFG_DEVICE_TYPE_0
    },
    {
        MEMM_UCFG_MEMORY_ID_1,
        MEMM_UCFG_VIRTUAL_ADDR_1,
        MEMM_UCFG_PHYSICAL_ADDR_1,
        MEMM_UCFG_MEMORY_AREA_SIZE_1,
        { MEMM_UCFG_GRNT_AREA_1ST_ADDR_1, MEMM_UCFG_GRNT_AREA_2ND_ADDR_1 },
        MEMM_UCFG_DEVICE_TYPE_1
    },
    {
        MEMM_UCFG_MEMORY_ID_2,
        MEMM_UCFG_VIRTUAL_ADDR_2,
        MEMM_UCFG_PHYSICAL_ADDR_2,
        MEMM_UCFG_MEMORY_AREA_SIZE_2,
        { MEMM_UCFG_GRNT_AREA_1ST_ADDR_2, MEMM_UCFG_GRNT_AREA_2ND_ADDR_2 },
        MEMM_UCFG_DEVICE_TYPE_2
    },
    {
        MEMM_UCFG_MEMORY_ID_3,
        MEMM_UCFG_VIRTUAL_ADDR_3,
        MEMM_UCFG_PHYSICAL_ADDR_3,
        MEMM_UCFG_MEMORY_AREA_SIZE_3,
        { MEMM_UCFG_GRNT_AREA_1ST_ADDR_3, MEMM_UCFG_GRNT_AREA_2ND_ADDR_3 },
        MEMM_UCFG_DEVICE_TYPE_3
    }
};

#define MEMM_STOP_SEC_CST
#include <MemM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define MEMM_START_SEC_CODE
#include <MemM_MemMap.h>


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
#define MEMM_STOP_SEC_CODE
#include <MemM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

