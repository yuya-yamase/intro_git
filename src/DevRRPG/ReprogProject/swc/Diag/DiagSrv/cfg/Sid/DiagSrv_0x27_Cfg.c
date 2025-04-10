/* DiagSrv_0x27_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x27/Cfg/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagSrv.h>
#include "DiagSrv_0x27_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_0X27_SUBFUNCINFO_NUM        (sizeof(DiagSrv_0x27_SubfuncInfoConfig) / sizeof(DiagSrv_0x27_SubfuncInfoConfig[0]))

#define DIAGSRV_CFG_0X27_LV1_SEEDSIZE           (16U)
#define DIAGSRV_CFG_0X27_LV1_KEYSIZE            (16U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR_SEED
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x27_Lv1_Seed[DIAGSRV_CFG_0X27_LV1_SEEDSIZE];

#define DIAGSRV_STOP_SEC_VAR_SEED
#include <DiagSrv_MemMap.h>

#define DIAGSRV_START_SEC_VAR_KEY
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x27_Lv1_Key[DIAGSRV_CFG_0X27_LV1_KEYSIZE];

#define DIAGSRV_STOP_SEC_VAR_KEY
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(Diag_SubfuncInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x27_SubfuncInfoConfig[] = {
     { 0x01U, 0x0000U, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
    ,{ 0x02U, 0x0010U, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
};

CONST(Diag_SubfuncConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x27_SubfuncConfig = {
    &DiagSrv_0x27_SubfuncInfoConfig[0],
    DIAGSRV_CFG_0X27_SUBFUNCINFO_NUM
};

static CONST(DiagSrv_0x27_SecLevelInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x27_SecLevelInfoConfig[DIAGSRV_CFG_0X27_SUPPORT_SECLEVEL_NUM] = {
     { 0x01U, 0U,   DIAG_NOT_SUPPORT, 0U,     DIAGSRV_CFG_0X27_LV1_SEEDSIZE, &DiagSrv_0x27_Lv1_Seed[0], DIAGSRV_CFG_0X27_LV1_KEYSIZE, &DiagSrv_0x27_Lv1_Key[0] }
};

CONST(DiagSrv_0x27_SecLevelConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x27_SecLevelConfig = {
    &DiagSrv_0x27_SecLevelInfoConfig[0],
    DIAGSRV_CFG_0X27_SUPPORT_SECLEVEL_NUM
};

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

