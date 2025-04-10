/* DiagSrv_Cfg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/Cfg/HEADER                                          */
/******************************************************************************/
#ifndef DIAGSRV_CFG_H
#define DIAGSRV_CFG_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <DiagCmn.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef Diag_SessionSupportType     DiagSrv_SidSessionSupportType;
typedef Diag_SecuritySupportType    DiagSrv_SidSecuritySupportType;

typedef struct {
    uint8 SupportFunc;
    uint8 SupportPhys;
} DiagSrv_SidAddressingSupportType;

typedef struct {
    uint8 Sid;
    DiagSrv_SidAddressingSupportType Addressing;
    DiagSrv_SidSessionSupportType Session;
    DiagSrv_SidSecuritySupportType Security;
} DiagSrv_SidInfoConfigType;

typedef struct {
    P2CONST(DiagSrv_SidInfoConfigType, TYPEDEF, DIAGSRV_APPL_CONST) InfoPtr;
    uint8 SidNum;
} DiagSrv_SidConfigType;

typedef P2FUNC(void, DIAGSRV_CALLOUT_CODE, DiagSrv_SID_Init_FuncType) (void);
typedef P2FUNC(void, DIAGSRV_CALLOUT_CODE, DiagSrv_SID_Time_FuncType) (void);
typedef P2FUNC(void, DIAGSRV_CALLOUT_CODE, DiagSrv_SID_Processing_FuncType)
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
);
typedef P2FUNC(void, DIAGSRV_CALLOUT_CODE, DiagSrv_SID_Confirmation_FuncType)
(
    VAR(uint8, AUTOMATIC) Status
);
typedef P2FUNC(void, DIAGSRV_CALLOUT_CODE, DiagSrv_SID_ChangeSession_FuncType)
(
    VAR(uint8, AUTOMATIC) OldSession,
    VAR(uint8, AUTOMATIC) NewSession,
    VAR(uint8, AUTOMATIC) Factor
);

typedef struct {
    uint8 Sid;
    DiagSrv_SID_Init_FuncType InitFunc;
    DiagSrv_SID_Time_FuncType TimeFunc;
    DiagSrv_SID_Processing_FuncType ProcessingFunc;
    DiagSrv_SID_Confirmation_FuncType ConfirmationFunc;
    DiagSrv_SID_ChangeSession_FuncType ChangeSessionFunc;
} DiagSrv_SidFuncInfoConfigType;

typedef struct {
    P2CONST(DiagSrv_SidFuncInfoConfigType, TYPEDEF, DIAGSRV_APPL_CONST) InfoPtr;
    uint8 SidNum;
} DiagSrv_SidFuncConfigType;

typedef struct {
    uint8 Session;
    uint8 Security;
} DiagSrv_ApEntryConfigType;


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

extern CONST(DiagSrv_SidConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SidConfig;
extern CONST(DiagSrv_SidFuncConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SidFuncConfig;
extern CONST(DiagSrv_ApEntryConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_ApEntryConfig;

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


#endif /* DIAGSRV_CFG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/03/09 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

