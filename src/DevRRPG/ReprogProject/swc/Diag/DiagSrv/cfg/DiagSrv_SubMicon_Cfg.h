/* DiagSrv_SubMicon_Cfg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/SubMicon/Cfg/HEADER                                 */
/******************************************************************************/
#ifndef DIAGSRV_SUBMICON_CFG_H
#define DIAGSRV_SUBMICON_CFG_H

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 Sid;
    uint8 GwKind;
} DiagSrv_SubMGatewayInfoConfigType;

typedef struct {
    uint8 Num;
    P2CONST(DiagSrv_SubMGatewayInfoConfigType, TYPEDEF, DIAGSRV_APPL_CONST) InfoPtr;
} DiagSrv_SubMGatewayConfigType;

typedef P2FUNC(uint8, DIAGSRV_CALLOUT_CODE, DiagSrv_SubM_GwCheck_SID_FuncType)
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) MiconId,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) CheckResult
);

typedef struct {
    uint8 Sid;
    DiagSrv_SubM_GwCheck_SID_FuncType GwCheckFunc;
} DiagSrv_SubM_GwCheckFuncInfoType;

typedef struct {
    uint8 Num;
    P2CONST(DiagSrv_SubM_GwCheckFuncInfoType, TYPEDEF, DIAGSRV_APPL_CONST) InfoPtr;
} DiagSrv_SubM_GwCheckFuncConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_SubM_GwCheck_0x2E
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) MiconId,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) CheckResult
);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_SubM_GwCheck_0x31
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) MiconId,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) CheckResult
);


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

extern CONST(DiagSrv_SubMGatewayConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SubMGatewayConfig;
extern CONST(DiagSrv_SubM_GwCheckFuncConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SubM_GwCheckConfig;

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>

#endif /* (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) */
#endif /* DIAGSRV_SUBMICON_CFG_H */


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2019/12/03 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

