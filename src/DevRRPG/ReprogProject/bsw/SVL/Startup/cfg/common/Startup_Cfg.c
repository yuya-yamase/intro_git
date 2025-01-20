/* Startup_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Startup/Cfg/CODE                                            */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "Startup_Cfg.h"
#include "Startup_Ucfg.h"
#include "Startup_Local.h"


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
#define STARTUP_START_SEC_VAR
#include <Startup_MemMap.h>

#define STARTUP_STOP_SEC_VAR
#include <Startup_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define STARTUP_START_SEC_CST
#include <Startup_MemMap.h>

static CONST(Startup_ApCheckSpConfigType, STARTUP_CONFIG_DATA) Startup_Cfg_ApCheckSpData = {
    STARTUP_UCFG_APCHECK_SP_ADDR,
    STARTUP_UCFG_APCHECK_SP_SIZE
};

static CONST(Startup_ApCheckConfigType, STARTUP_CONFIG_DATA) Startup_Cfg_ApCheckData = {
    STARTUP_UCFG_APCHECK_NUM,
    &Startup_Ucfg_ApCheckInfo[0]
};

static CONST(Startup_ApAreaConfigType, STARTUP_CONFIG_DATA) Startup_Cfg_ApAreaData = {
    STARTUP_UCFG_APAREA_NUM,
    &Startup_Ucfg_ApAreaInfo[0]
};

static CONST(Startup_InitCfgConfigType, STARTUP_CONFIG_DATA) Startup_Cfg_InitCfgData = {
    &GPT_CFG_DATA,
    &WDG_CFG_DATA,
    &MCU_CFG_DATA,
    &WdgM_Cfg_Data
};

CONST(Startup_ConfigType, STARTUP_CONFIG_DATA) Startup_Cfg_Data = {
    &Startup_Cfg_ApCheckSpData,
    &Startup_Cfg_ApCheckData,
    &Startup_Cfg_ApAreaData,
    &Startup_Cfg_InitCfgData,
    STARTUP_UCFG_APJUMPADDR_SAVE_ADDR,
    STARTUP_CFG_PLLCHECK_NUM,
    STARTUP_CFG_CLEAR_RAM_BLOCK_SIZE
};

#define STARTUP_STOP_SEC_CST
#include <Startup_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define STARTUP_START_SEC_CODE
#include <Startup_MemMap.h>


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define STARTUP_STOP_SEC_CODE
#include <Startup_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

