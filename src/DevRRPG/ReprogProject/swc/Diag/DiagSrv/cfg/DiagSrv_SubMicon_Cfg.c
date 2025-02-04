/* DiagSrv_SubMicon_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/SubMicon/Cfg/CODE                                   */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#include <DiagSrv.h>
#include "DiagSrv_SubMicon_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_SUBM_SID_GW_NUM         (sizeof(DiagSrv_SubMSidGwInfoConfig) / sizeof(DiagSrv_SubMSidGwInfoConfig[0]))
#define DIAGSRV_CFG_SUBM_GW_CHECK_FUNC_NUM  (sizeof(DiagSrv_SubM_GwCheckFuncInfoTbl) / sizeof(DiagSrv_SubM_GwCheckFuncInfoTbl[0]))

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(DiagSrv_SubMGatewayInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SubMSidGwInfoConfig[] = {
     { DIAG_SID_WDBI, DIAGSRV_SUBM_GW_DEPEND_MSG }
    ,{ DIAG_SID_RC,   DIAGSRV_SUBM_GW_DEPEND_MSG }
    ,{ DIAG_SID_RD,   DIAGSRV_SUBM_GW_DEPEND_SEQ }
    ,{ DIAG_SID_TD,   DIAGSRV_SUBM_GW_DEPEND_SEQ }
    ,{ DIAG_SID_RTE,  DIAGSRV_SUBM_GW_DEPEND_SEQ }
};

CONST(DiagSrv_SubMGatewayConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SubMGatewayConfig = {
    DIAGSRV_CFG_SUBM_SID_GW_NUM,
    &DiagSrv_SubMSidGwInfoConfig[0]
};

static CONST(DiagSrv_SubM_GwCheckFuncInfoType, DIAGSRV_CONFIG_DATA) DiagSrv_SubM_GwCheckFuncInfoTbl[] = {
     { DIAG_SID_WDBI, &DiagSrv_SubM_GwCheck_0x2E }
    ,{ DIAG_SID_RC,   &DiagSrv_SubM_GwCheck_0x31 }
};

CONST(DiagSrv_SubM_GwCheckFuncConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SubM_GwCheckConfig = {
    DIAGSRV_CFG_SUBM_GW_CHECK_FUNC_NUM,
    &DiagSrv_SubM_GwCheckFuncInfoTbl[0]
};

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>

#endif /* (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2019/12/03 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

