/* DiagSrv_SubMicon_Core_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/SubMicon/Core/Cfg/CODE                              */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#include <DiagSrv.h>
#include "DiagSrv_SubMicon_Core_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_SUBM_MICON_NUM          ((uint8)1U)
#define DIAGSRV_CFG_SUBM_0_REWRITEAREA_NUM  (sizeof(DiagSrv_SubM_0_RewriteAreaConfig) / sizeof(DiagSrv_SubM_0_RewriteAreaConfig[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(uint8, DIAGSRV_CONFIG_DATA) DiagSrv_SubM_0_RewriteAreaConfig[] = {
     0U
};

static CONST(DiagSrv_SubMRewriteAreaInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SubMRewriteAreaInfoConfig[DIAGSRV_CFG_SUBM_MICON_NUM] = {
     { DIAGSRV_SUBM_ID_MAIN,   DIAGSRV_CFG_SUBM_0_REWRITEAREA_NUM, &DiagSrv_SubM_0_RewriteAreaConfig[0] }
};

CONST(DiagSrv_SubMRewriteConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SubMRewriteConfig = {
    DIAGSRV_CFG_SUBM_MICON_NUM,
    &DiagSrv_SubMRewriteAreaInfoConfig[0]
};

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>

#endif /* (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
/**** End of File *************************************************************/

