/* CanSM_Cfg_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CanSM/Cfg/CODE                                              */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <CanSM.h>
#include "CanSM_Ucfg.h"
#include "CanSM_Cfg.h"


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
#define CANSM_START_SEC_VAR
#include <CanSM_MemMap.h>


#define CANSM_STOP_SEC_VAR
#include <CanSM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define CANSM_START_SEC_CST
#include <CanSM_MemMap.h>

static CONST(CanSM_NetworkConfigType, CANSM_CONFIG_DATA) CanSM_Cfg_Network_Data = {
    CANSM_CFG_MODEREQ_REPETITION_TIME,
    CANSM_CFG_MODEREQ_REPETITION_MAX,
    CANSM_UCFG_NETWORK_NUM,
    &CanSM_Ucfg_NetworkSetting_Data[0]
};

static CONST(CanSM_PduIdConfigType, CANSM_CONFIG_DATA) CanSM_Cfg_PduId_Data = {
    &CanSM_Ucfg_PduIdSetting_Data[0],
    CANSM_UCFG_PDUID_NUM
};

static CONST(CanSM_BaudrateConfigType, CANSM_CONFIG_DATA) CanSM_Cfg_BaudrateConfig = {
    &CanSM_Ucfg_BaudrateSettingConfig[0],
    CANSM_UCFG_BAUDRATE_NUM
};

CONST(CanSM_ConfigType, CANSM_CONFIG_DATA) CanSM_Cfg_Data = {
    &CanSM_Cfg_Network_Data,
    &CanSM_Cfg_PduId_Data,
    &CanSM_Cfg_BaudrateConfig
};

#define CANSM_STOP_SEC_CST
#include <CanSM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define CANSM_START_SEC_CODE
#include <CanSM_MemMap.h>


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/


#define CANSM_STOP_SEC_CODE
#include <CanSM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

