/* DiagSrv_0x22_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x22/Cfg/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagSrv.h>
#include "DiagSrv_0x22_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_0X22_DIDINFO_NUM        (sizeof(DiagSrv_0x22_DidInfoConfig) / sizeof(DiagSrv_0x22_DidInfoConfig[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

CONST(DiagSrv_0x22_ConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x22_Config = {
    DIAGSRV_CFG_0X22_MULTIPLE_DID_MAX
};

static CONST(Diag_DidInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x22_DidInfoConfig[] = {
     { 0xF050U, 0x0010U, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
    ,{ 0xF186U, 0x0001U, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
    ,{ 0xF188U, 0x0013U, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
    ,{ 0xF191U, 0x000FU, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
    ,{ 0xF120U, 0x0018U, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
};

CONST(Diag_DidConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x22_DidConfig = {
    &DiagSrv_0x22_DidInfoConfig[0],
    DIAGSRV_CFG_0X22_DIDINFO_NUM
};

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/03/01 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

