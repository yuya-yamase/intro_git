/* DiagSrv_0x2E_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x2E/Cfg/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagSrv.h>
#include "DiagSrv_0x2E_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_0X2E_DIDINFO_NUM    (sizeof(DiagSrv_0x2E_DidInfoConfig) / sizeof(DiagSrv_0x2E_DidInfoConfig[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(Diag_DidInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x2E_DidInfoConfig[] = {
     { 0xF050U, 0x0010U, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_NOT_SUPPORT } }
    ,{ 0xF120U, 0x0018U, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_NOT_SUPPORT } }
};

CONST(Diag_DidConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x2E_DidConfig = {
    &DiagSrv_0x2E_DidInfoConfig[0],
    DIAGSRV_CFG_0X2E_DIDINFO_NUM
};

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


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

