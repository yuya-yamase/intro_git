/* DiagSrv_0x10_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x10/Cfg/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagSrv.h>
#include "DiagSrv_0x10_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_0X10_SUBFUNCINFO_NUM        (sizeof(DiagSrv_0x10_SubfuncInfoConfig) / sizeof(DiagSrv_0x10_SubfuncInfoConfig[0]))
#define DIAGSRV_CFG_0X10_TIMINGPARAMINFO_NUM    (sizeof(DiagSrv_0x10_TimingParamInfoConfig) / sizeof(DiagSrv_0x10_TimingParamInfoConfig[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(Diag_SubfuncInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x10_SubfuncInfoConfig[] = {
     { 0x01U, 0x0000U, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
    ,{ 0x02U, 0x0000U, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
};

CONST(Diag_SubfuncConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x10_SubfuncConfig = {
    &DiagSrv_0x10_SubfuncInfoConfig[0],
    DIAGSRV_CFG_0X10_SUBFUNCINFO_NUM
};

static CONST(DiagSrv_0x10_TimingParamInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x10_TimingParamInfoConfig[] = {
     { 0x01U, 50U,    500U   }
    ,{ 0x02U, 50U,    500U   }
};

CONST(DiagSrv_0x10_TimingParamConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x10_TimingParamConfig = {
    &DiagSrv_0x10_TimingParamInfoConfig[0],
    DIAGSRV_CFG_0X10_TIMINGPARAMINFO_NUM
};

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/03/09 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
/**** End of File *************************************************************/

