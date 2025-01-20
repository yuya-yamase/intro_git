/* IntHndlr_Cfg_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | IntHndlr/Cfg/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "IntHndlr_Local.h"
#include "IntHndlr_Cfg.h"
#include "IntHndlr_Ucfg.h"


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
#define INTHNDLR_START_SEC_VAR
#include <IntHndlr_MemMap.h>

#define INTHNDLR_STOP_SEC_VAR
#include <IntHndlr_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define INTHNDLR_START_SEC_CST
#include <IntHndlr_MemMap.h>

static CONST(IntHndlr_CanConfigType, INTHNDLR_CONFIG_DATA) IntHndlr_Cfg_CanData = {
    INTHNDLR_UCFG_CAN_CH_USE_NUM,
    &IntHndlr_Ucfg_CanInfo[0]
};

static CONST(IntHndlr_GptConfigType, INTHNDLR_CONFIG_DATA) IntHndlr_Cfg_GptData = {
    INTHNDLR_CFG_GPT0_CODE,
    INTHNDLR_CFG_GPT1_CODE
};

#if (REPROG_CFG_CXPI_USE == STD_ON)
static CONST(IntHndlr_CxpiConfigType, INTHNDLR_CONFIG_DATA) IntHndlr_Cfg_CxpiData = {
    &IntHndlr_Ucfg_CxpiInfo
};
#endif

static CONST(IntHndlr_UsrConfigType, INTHNDLR_CONFIG_DATA) IntHndlr_Cfg_UsrData = {
    INTHNDLR_CFG_USR_USE_NUM,
    &IntHndlr_Ucfg_UsrInfo[0]
};

CONST(IntHndlr_ConfigType, INTHNDLR_CONFIG_DATA) IntHndlr_Cfg_Data = {
    &IntHndlr_Cfg_CanData,
    &IntHndlr_Cfg_GptData,
#if (REPROG_CFG_CXPI_USE == STD_ON)
    &IntHndlr_Cfg_CxpiData,
#endif
    &IntHndlr_Cfg_UsrData
};

#define INTHNDLR_STOP_SEC_CST
#include <IntHndlr_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define INTHNDLR_START_SEC_CODE
#include <IntHndlr_MemMap.h>


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define INTHNDLR_STOP_SEC_CODE
#include <IntHndlr_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/02/13 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

