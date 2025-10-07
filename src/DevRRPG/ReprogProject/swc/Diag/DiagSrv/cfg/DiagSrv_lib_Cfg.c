/* DiagSrv_lib_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/lib/Cfg/CODE                                        */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "DiagSrv_lib_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_LBSTS_INFO_NUM              ((uint8)1U)
#define DIAGSRV_CFG_RPRGDATAAREA_NUM            (sizeof(DiagSrv_RprgDataAreaInfoConfig) / sizeof(DiagSrv_RprgDataAreaInfoConfig[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(DiagSrv_RewriteAreaBootInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_RewriteAreaBootInfo;
static VAR(DiagSrv_RewriteAreaStatusInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_RewriteAreaStatusInfo[DIAGSRV_CFG_LBSTS_INFO_NUM];

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(DiagSrv_RprgDataAreaInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_RprgDataAreaInfoConfig[] = {
     { 0x00U, 0x007BFE00UL, DIAGSRV_CFG_RPRGDATA_SIZE }
};

CONST(DiagSrv_RprgDataAreaConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_RprgDataAreaConfig = {
    &DiagSrv_RprgDataAreaInfoConfig[0],
    DIAGSRV_CFG_RPRGDATAAREA_NUM
};

CONST(DiagSrv_VersionInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_VersionInfoConfig = {
    0x00004200UL,
    0x00008000UL,
    24U
};

CONST(DiagSrv_RewriteAreaStatusType, DIAGSRV_CONFIG_DATA) DiagSrv_RewriteAreaStatus = {
    &DiagSrv_RewriteAreaBootInfo,
    &DiagSrv_RewriteAreaStatusInfo[0],
    DIAGSRV_CFG_LBSTS_INFO_NUM
};

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>

#define DIAGSRV_START_SEC_CST_ENCRYPTION_FLAG
#include <DiagSrv_MemMap.h>

CONST(uint8, DIAGSRV_CONFIG_DATA) DiagSrv_EncryptionFlagConfig = DIAGSRV_ENCRYPTIONFLAG_OFF;

#define DIAGSRV_STOP_SEC_CST_ENCRYPTION_FLAG
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/07/05 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
/**** End of File *************************************************************/

