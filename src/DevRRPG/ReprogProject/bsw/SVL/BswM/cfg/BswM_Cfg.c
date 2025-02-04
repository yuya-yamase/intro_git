/* BswM_Cfg_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/Cfg/CODE                                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Ucfg.h"
#include "BswM_Cfg.h"

#include <CanSM.h>
#include <ComM.h>
#include <CanIf.h>

#if (REPROG_CFG_ETH_USE == STD_ON)
#include <EthSM/EthSM_Local.h>
#include "../../../../Comstack/Ether/EthSM/cfg/EthSM_Cfg.h"
#endif


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
#define BSWM_START_SEC2_VAR
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC2_VAR
#include <BswM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC2_CST
#include <BswM_MemMap.h>

static CONST(BswM_ModeInitValConfigType, BSWM_CONFIG_DATA) BswM_Cfg_ModeInitValData = {
    BSWM_CFG_INITVAL_REWRITE,
    BSWM_CFG_INITVAL_SESSION,
    BSWM_CFG_INITVAL_SECURITY,
    BSWM_CFG_INITVAL_FLS_PRG,
    BSWM_CFG_INITVAL_ECU_RESET,
    BSWM_CFG_INITVAL_FINISH,
    BSWM_CFG_INITVAL_MAIN_ERR,
    BSWM_CFG_INITVAL_USR_RESET,
    BSWM_CFG_INITVAL_USR_SLEEP,
    BSWM_CFG_INITVAL_ACC,
    BSWM_CFG_INITVAL_IG,
    BSWM_CFG_INITVAL_CANSM
#if (REPROG_CFG_ETH_USE == STD_ON)
    ,BSWM_CFG_INITVAL_ETHSM
    ,BSWM_CFG_INITVAL_ETHSENDRCV
#endif
};

static CONST(BswM_FinishPriorityConfigType, BSWM_CONFIG_DATA) BswM_Cfg_FinishPriorityData = {
    {
        BSWM_CFG_FINISHTYPE_1,
        BSWM_CFG_FINISHTYPE_2,
        BSWM_CFG_FINISHTYPE_3,
        BSWM_CFG_FINISHTYPE_4,
        BSWM_CFG_FINISHTYPE_5,
        BSWM_CFG_FINISHTYPE_6,
        BSWM_CFG_FINISHTYPE_7
    }
};

static CONST(BswM_AccIgActionConfigType, BSWM_CONFIG_DATA) BswM_Cfg_AccIgActionData = {
    BSWM_UCFG_ACCOFF_ACTION,
    BSWM_UCFG_IGOFF_ACTION
};

#if (REPROG_CFG_ETH_USE == STD_ON)
static CONST(BswM_EthSM_NetworkConfigType, BSWM_CONFIG_DATA) BswM_EthSM_Cfg_Network_Data = {
    ETHSM_NETWORKNUM,
    &EthSM_stNetworks[0]
};

static CONST(BswM_EthSM_ConfigType, BSWM_CONFIG_DATA) BswM_EthSM_Cfg_Data = {
    &BswM_EthSM_Cfg_Network_Data
};
#endif

#if (REPROG_CFG_CXPI_USE == STD_ON)
static CONST(BswM_CxpiSM_NetworkSettingConfigType, BSWM_CONFIG_DATA) BswM_CxpiSM_Cfg_NetworkSettingData = {
    BSWM_CFG_CXPISM_NETWORKID
};

static CONST(BswM_CxpiSM_PduIdSettingConfigType, BSWM_CONFIG_DATA) BswM_CxpiSM_Cfg_PduIdSettingData[BSWM_CFG_CXPI_PDUID_NUM] = {
    { BSWM_CFG_CXPISM_IPDUID_0, BSWM_CFG_CXPISM_NAD_0, BSWM_CFG_CXPISM_CONTROLLERID },
    { BSWM_CFG_CXPISM_IPDUID_1, BSWM_CFG_CXPISM_NAD_1, BSWM_CFG_CXPISM_CONTROLLERID }
};

static CONST(BswM_CxpiSM_NetworkConfigType, BSWM_CONFIG_DATA) BswM_CxpiSM_Cfg_Network_Data = {
    &BswM_CxpiSM_Cfg_NetworkSettingData
};

static CONST(BswM_CxpiSM_PduIdConfigType, BSWM_CONFIG_DATA) BswM_CxpiSM_Cfg_PduId_Data = {
    &BswM_CxpiSM_Cfg_PduIdSettingData[0],
    BSWM_CFG_CXPI_PDUID_NUM
};

static CONST(BswM_CxpiSM_ConfigType, BSWM_CONFIG_DATA) BswM_CxpiSM_Cfg_Data = {
    &BswM_CxpiSM_Cfg_Network_Data,
    &BswM_CxpiSM_Cfg_PduId_Data
};
#endif

CONST(BswM_ConfigType, BSWM_CONFIG_DATA) BswM_Cfg_Data = {
    &BswM_Cfg_ModeInitValData,
    &BswM_Cfg_FinishPriorityData,
    &BswM_Cfg_AccIgActionData,
    &BswM_Cfg_UidData,
    &CanSM_Cfg_Data,
    &CanIf_Cfg_Data,
    &ComM_Cfg_Data,
#if (REPROG_CFG_ETH_USE == STD_ON)
    ,&BswM_EthSM_Cfg_Data
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
    ,&BswM_CxpiSM_Cfg_Data
#endif
};

#define BSWM_STOP_SEC2_CST
#include <BswM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define BSWM_START_SEC2_CODE
#include <BswM_MemMap.h>


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define BSWM_STOP_SEC2_CODE
#include <BswM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

