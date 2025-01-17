/* DiagLib_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagLib/HEADER                                              */
/******************************************************************************/
#ifndef DIAGLIB_H
#define DIAGLIB_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <ComStack_Types.h>
#include <DiagCmn.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_Init (void);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_Time (void);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SendPosRsp
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_DATA) Msg
);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SendNegRsp
(
    VAR(uint8, AUTOMATIC) Nrc,
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_DATA) Msg
);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetSuppressResponseBySid
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_DATA) Msg
);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetFuncAddressSuppressByNrc
(
    P2VAR(Gdn_Dcm_NegativeResponseInfoType, AUTOMATIC, DIAGLIB_APPL_DATA) NegRsp
);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_CancelProcessingFinished
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_CONST) Msg
);
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_GetComStatus (void);
FUNC(Std_ReturnType, DIAGLIB_CODE_SLOW) DiagLib_GetPendingRspInfo
(
    P2VAR(uint8, AUTOMATIC, DIAGLIB_APPL_DATA) Status,
    P2VAR(uint32, AUTOMATIC, DIAGLIB_APPL_DATA) ElapsedTime
);
FUNC(Std_ReturnType, DIAGLIB_CODE_SLOW) DiagLib_GetCurrentPduId
(
    P2VAR(PduIdType, AUTOMATIC, DIAGLIB_APPL_DATA) PduId
);
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_CheckSidSupport
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_CONST) Msg
);
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_CheckSubfunctionSupport
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_CONST) Msg,
    P2CONST(Diag_SubfuncConfigType, AUTOMATIC, DIAGLIB_APPL_CONST) SubfuncConfig,
    P2VAR(uint8, AUTOMATIC, DIAGLIB_APPL_DATA) Index
);
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_CheckDidSupport
(
    VAR(uint16, AUTOMATIC) Did,
    P2CONST(Diag_DidConfigType, AUTOMATIC, DIAGLIB_APPL_CONST) DidConfig,
    P2VAR(uint8, AUTOMATIC, DIAGLIB_APPL_DATA) Index
);
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_CheckRidSupport
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_CONST) Msg,
    P2CONST(Diag_RidConfigType, AUTOMATIC, DIAGLIB_APPL_CONST) RidConfig,
    P2VAR(uint8, AUTOMATIC, DIAGLIB_APPL_DATA) Index
);
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_GetSession (void);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetSession
(
    VAR(uint8, AUTOMATIC) Session,
    VAR(uint8, AUTOMATIC) Factor
);
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_GetSecurityLockStatus (void);
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_GetSecurityLockStatusLevel
(
    VAR(uint8, AUTOMATIC) Level
);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetSecurityLockAll (void);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetSecurityUnlockAll (void);
FUNC(Std_ReturnType, DIAGLIB_CODE_SLOW) DiagLib_SetSecurityUnlockLevel
(
    VAR(uint8, AUTOMATIC) Level
);
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_GetTransferMode (void);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetTransferMode
(
    VAR(uint8, AUTOMATIC) Mode
);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_EcuReset (void);
FUNC(uint32, DIAGLIB_CODE_SLOW) DiagLib_GetMNOBL (void);
FUNC(uint32, DIAGLIB_CODE_SLOW) DiagLib_GetULMNOBL (void);
#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_PendingRspSentHook (void);
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_PendingRspStopHook (void);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGLIB_START_SEC_VAR
#include <DiagLib_MemMap.h>


#define DIAGLIB_STOP_SEC_VAR
#include <DiagLib_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGLIB_START_SEC_CST
#include <DiagLib_MemMap.h>


#define DIAGLIB_STOP_SEC_CST
#include <DiagLib_MemMap.h>


#endif /* DIAGLIB_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/03/01 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

