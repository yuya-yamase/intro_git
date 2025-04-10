/* DiagSrv_0x3E_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x3E/Cfg/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagSrv.h>
#include "DiagSrv_0x3E_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_0X3E_SUBFUNCINFO_NUM    (sizeof(DiagSrv_0x3E_SubfuncInfoConfig) / sizeof(DiagSrv_0x3E_SubfuncInfoConfig[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(Diag_SubfuncInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x3E_SubfuncInfoConfig[] = {
     { 0x00U, 0x0000U, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
};

CONST(Diag_SubfuncConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x3E_SubfuncConfig = {
    &DiagSrv_0x3E_SubfuncInfoConfig[0],
    DIAGSRV_CFG_0X3E_SUBFUNCINFO_NUM
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
/**** End of File *************************************************************/

