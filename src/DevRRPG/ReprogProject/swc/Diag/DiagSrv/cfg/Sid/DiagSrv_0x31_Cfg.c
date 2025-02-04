/* DiagSrv_0x31_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x31/Cfg/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagSrv.h>
#include "DiagSrv_lib_Cfg.h"
#include "DiagSrv_0x31_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_0X31_RIDINFO_NUM        (sizeof(DiagSrv_0x31_RidInfoConfig) / sizeof(DiagSrv_0x31_RidInfoConfig[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

CONST(DiagSrv_0x31_ConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x31_Config = {
    DIAGSRV_CFG_SIGNATURE_SIZE,
    DIAG_NOT_SUPPORT
};

static CONST(Diag_RidInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x31_RidInfoConfig[] = {
     { 0xFF00U, 0x0009U, 0x01U, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_NOT_SUPPORT } }
    ,{ 0xDD00U, 0xFFFFU, 0x01U, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_NOT_SUPPORT } }
    ,{ 0xDD01U, 0xFFFFU, 0x01U, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_NOT_SUPPORT } }
    ,{ 0xDD02U, 0x0000U, 0x01U, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_NOT_SUPPORT } }
};

CONST(Diag_RidConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x31_RidConfig = {
    &DiagSrv_0x31_RidInfoConfig[0],
    DIAGSRV_CFG_0X31_RIDINFO_NUM
};

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/07/05 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

