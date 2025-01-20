/* CanSM_Ucfg_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CanSM/Ucfg/CODE                                             */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <CanSM.h>
#include "CanSM_Ucfg.h"


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

static CONST(CanSM_ControllerSettingConfigType, CANSM_CONFIG_DATA) CanSM_Ucfg_ControllerSetting_Data_0[CANSM_UCFG_CONTROLLER_NUM_0] = {
    { CANSM_UCFG_CONTROLLERID_0 }
};

CONST(CanSM_NetworkSettingConfigType, CANSM_CONFIG_DATA) CanSM_Ucfg_NetworkSetting_Data[CANSM_UCFG_NETWORK_NUM] = {
    { &CanSM_Ucfg_ControllerSetting_Data_0[0], CANSM_UCFG_CONTROLLER_NUM_0, CANSM_UCFG_NETWORKID_0 }
};

CONST(CanSM_PduIdSettingConfigType, CANSM_CONFIG_DATA) CanSM_Ucfg_PduIdSetting_Data[CANSM_UCFG_PDUID_NUM] = {
    { CANSM_UCFG_CANID_0, CANSM_UCFG_IPDUID_0, CANSM_UCFG_CONTROLLERID_0 },
    { CANSM_UCFG_CANID_1, CANSM_UCFG_IPDUID_1, CANSM_UCFG_CONTROLLERID_0 },
    { CANSM_UCFG_CANID_2, CANSM_UCFG_IPDUID_2, CANSM_UCFG_CONTROLLERID_0 },     /* ^^^ */
    { CANSM_UCFG_CANID_3, CANSM_UCFG_IPDUID_3, CANSM_UCFG_CONTROLLERID_0 }      /* ^^^ */
};

CONST(CanSM_BaudrateSettingConfigType, CANSM_CONFIG_DATA) CanSM_Ucfg_BaudrateSettingConfig[CANSM_UCFG_BAUDRATE_NUM] = {
    { 500U }
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

