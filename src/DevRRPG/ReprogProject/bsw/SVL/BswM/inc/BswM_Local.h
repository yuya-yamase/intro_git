/* BswM_Local_h_Revision(v4.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/Local/HEADER                                           */
/******************************************************************************/
#ifndef BSWM_LOCAL_H
#define BSWM_LOCAL_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <EcuM.h>
#include <CanSM.h>
#include <CanSM_BswM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* API ID */
#define BSWM_API_ID_INIT                (0x01U)
#define BSWM_API_ID_REQMODE             (0x02U)
#define BSWM_API_ID_CANSMCURRENTSTATE   (0x03U)
#define BSWM_API_ID_ECUMCURRENTSTATE    (0x04U)
#define BSWM_API_ID_REQMODE_REWRITE     (0x05U)
#define BSWM_API_ID_REQMODE_SESSION     (0x06U)
#define BSWM_API_ID_REQMODE_SECURITY    (0x07U)
#define BSWM_API_ID_REQMODE_FLSPRG      (0x08U)
#define BSWM_API_ID_REQMODE_ECURESET    (0x09U)
#define BSWM_API_ID_REQMODE_FINISH      (0x0AU)
#define BSWM_API_ID_REQMODE_USRRESET    (0x0BU)
#define BSWM_API_ID_REQMODE_USRSLEEP    (0x0CU)
#define BSWM_API_ID_REQMODE_ACC         (0x0DU)
#define BSWM_API_ID_REQMODE_IG          (0x0EU)
#define BSWM_API_ID_COMSTART            (0x0FU)
#define BSWM_API_ID_DCMDUMMYRECEPTION   (0x10U)
#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
 #define BSWM_API_ID_REQMODE_MAINERR     (0x13U)
#else
 #define BSWM_API_ID_REQ_MMICON_SESSION  (0x11U)
 #define BSWM_API_ID_REQ_MMICON_SECURITY (0x12U)
 #define BSWM_API_ID_REQ_MMICON_MAINERR  (0x14U)
#endif
#define BSWM_API_ID_CHECKDUMMYRECEPTION (0x19U)
#define BSWM_API_ID_INITUNIT_CSM        (0x1AU)
#if (REPROG_CFG_ETH_USE == STD_ON)
#define BSWM_API_ID_ETH_SENDRCV_START       (0x15U)
#define BSWM_API_ID_ETHDCMDUMMYRECEPTION    (0x16U)
#define BSWM_API_ID_REQMODE_ETHSENDRCV      (0x17U)
#endif
#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
#define BSWM_API_ID_SUBMICONEVENT_TXCONFIRMATION    (0x18U)
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
#define BSWM_API_ID_CXPISMCURRENTSTATE    (0x81U)
#define BSWM_API_ID_CXPICOMSTART          (0x82U)
#define BSWM_API_ID_CXPIDCMDUMMYRECEPTION (0x83U)
#endif
/* ERROR CODE */
#define BSWM_E_NO_INIT                  (0x01U)
#define BSWM_E_NULL_POINTER             (0x02U)
#define BSWM_E_PARAM_INVALID            (0x03U)
#define BSWM_E_REQ_USER_OUT_OF_RANGE    (0x04U)
#define BSWM_E_REQ_MODE_OUT_OF_RANGE    (0x05U)
#define BSWM_E_PDUIDSEARCH_ERR          (0x81U)
#define BSWM_E_APENTRYCHECK_ERR         (0x82U)
#define BSWM_E_PARAM_MICON_INVALID      (0x83U)
#define BSWM_E_STARTOFRECEPTION_ERR     (0x84U)
#define BSWM_E_COPYRXDATA_ERR           (0x85U)
#define BSWM_E_UIDSET_ERR               (0x86U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef P2FUNC(void, BSWM_CALLOUT_CODE, BswM_ReqModeFuncType)
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);

typedef struct {
    BswM_ReqModeFuncType    Func;
    BswM_UserType           User;
} BswM_ReqUserType;

typedef struct {
    BswM_ModeType   Rewrite;
    BswM_ModeType   Session;
    BswM_ModeType   Security;
    BswM_ModeType   FlsPrg;
    BswM_ModeType   EcuReset;
    BswM_ModeType   Finish;
    BswM_ModeType   MainErr;
    BswM_ModeType   UsrReset;
    BswM_ModeType   UsrSleep;
    BswM_ModeType   Acc;
    BswM_ModeType   Ig;
#if (REPROG_CFG_ETH_USE == STD_ON)
    BswM_ModeType   EthSendRcv;
#endif
} BswM_CtrlReqModeType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, BSWM_CODE_FAST) BswM_InitUnit (void);
FUNC(void, BSWM_CODE_FAST) BswM_DeinitUnit (void);
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Rewrite
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Session
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Security
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_FlsPrg
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_EcuReset
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Finish
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_UsrReset
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_UsrSleep
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Acc
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Ig
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
#if (REPROG_CFG_ETH_USE == STD_ON)
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_EthSendRcv
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
#endif
#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
 FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_MainErr
 (
     VAR(BswM_ModeType, AUTOMATIC) Mode
 );
#else
 FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Mmicon_Session
 (
     VAR(BswM_ModeType, AUTOMATIC) Mode
 );
 FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Mmicon_Security
 (
     VAR(BswM_ModeType, AUTOMATIC) Mode
 );
 FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Mmicon_MainErr
 (
     VAR(BswM_ModeType, AUTOMATIC) Mode
 );
#endif
FUNC(void, BSWM_CODE_FAST) BswM_Act_CanSMNoCom
(
    VAR(NetworkHandleType, AUTOMATIC) NetworkId,
    VAR(uint8, AUTOMATIC) StateIndex
);
FUNC(void, BSWM_CODE_FAST) BswM_Act_CanSMFullCom
(
    VAR(NetworkHandleType, AUTOMATIC) NetworkId,
    VAR(uint8, AUTOMATIC) StateIndex
);
FUNC(void, BSWM_CODE_FAST) BswM_Act_CanSMChangeBaudrate
(
    VAR(uint8, AUTOMATIC) StateIndex
);
#if (REPROG_CFG_ETH_USE == STD_ON)
FUNC(void, BSWM_CODE_FAST) BswM_Act_EthSMFullCom
(
    VAR(NetworkHandleType, AUTOMATIC) NetworkId,
    VAR(uint8, AUTOMATIC) StateIndex
);
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
FUNC(void, BSWM_CODE_FAST) BswM_Act_CxpiSMFullCom (void);
#endif
FUNC(void, BSWM_CODE_FAST) BswM_Act_EcuMStartup (void);
FUNC(void, BSWM_CODE_SLOW) BswM_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_VAR
#include <BswM_MemMap.h>

extern VAR(CanSM_BswMRequestedModeType, BSWM_VAR_CLEARED) BswM_CanSMState[CANSM_MAXNETWORK_NUM];
extern VAR(EcuM_StateType, BSWM_VAR_CLEARED) BswM_EcuMState;
extern VAR(uint8, BSWM_VAR_CLEARED) BswM_ComStartFlg;

#if (REPROG_CFG_ETH_USE == STD_ON)
extern VAR(EthSM_NetworkModeStateType, BSWM_VAR_CLEARED) BswM_EthSMState[BSWM_ETHSM_MAXNETWORK_NUM];
extern VAR(uint8, BSWM_VAR_CLEARED) BswM_ComStartFlg_Eth;
#endif


#define BSWM_STOP_SEC_VAR
#include <BswM_MemMap.h>

#define BSWM_START_SEC2_VAR
#include <BswM_MemMap.h>

extern P2CONST(BswM_ConfigType, BSWM_VAR_CLEARED, BSWM_APPL_CONST) BswM_CfgPtr;
extern VAR(BswM_CtrlReqModeType, BSWM_VAR_CLEARED) BswM_CtrlReqMode;

#define BSWM_STOP_SEC2_VAR
#include <BswM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* BSWM_LOCAL_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/07/16 :Update                                rel.AUBASS */
/*  v3.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v4.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

