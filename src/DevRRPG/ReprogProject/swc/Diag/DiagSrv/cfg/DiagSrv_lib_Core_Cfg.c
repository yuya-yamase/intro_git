/* DiagSrv_lib_Core_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/lib/Core/Cfg/CODE                                   */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "DiagSrv_lib_Core_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_REWRITEAREA_NUM     (sizeof(DiagSrv_RewriteAreaInfoConfig) / sizeof(DiagSrv_RewriteAreaInfoConfig[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(DiagSrv_RewriteAreaInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_RewriteAreaInfoConfig[] = {
     { 0x00U, { 0x00020000UL, 0x007DFE00UL } }
};

CONST(DiagSrv_RewriteAreaConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_RewriteAreaConfig = {
    &DiagSrv_RewriteAreaInfoConfig[0],
    DIAGSRV_CFG_REWRITEAREA_NUM
};

CONST(DiagSrv_SblAreaConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SblAreaConfig = {
    0xFE000000UL, 0x00001000UL
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

