/* BswM_h_Revision(v5.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/HEADER                                                 */
/******************************************************************************/
#ifndef BSWM_H
#define BSWM_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <CanSM.h>
#include <CanSM_BswM.h>
#include <ComM.h>
#include <CanIf.h>

#if (REPROG_CFG_ETH_USE == STD_ON)
#include <EthSM/EthSM_Local.h>
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* BswM_UserType */
#define BSWM_USER_SCHM_REWRITE          ((BswM_UserType)0x0001U)
#define BSWM_USER_SCHM_SESSION          ((BswM_UserType)0x0002U)
#define BSWM_USER_SCHM_SECURITY         ((BswM_UserType)0x0003U)
#define BSWM_USER_SCHM_FLS_PRG          ((BswM_UserType)0x0004U)
#define BSWM_USER_SCHM_ECU_RESET        ((BswM_UserType)0x0005U)
#define BSWM_USER_SCHM_FINISH           ((BswM_UserType)0x0006U)
#define BSWM_USER_SCHM_MAIN_ERR         ((BswM_UserType)0x0007U)
#define BSWM_USER_RTE_USR_RESET         ((BswM_UserType)0x8001U)
#define BSWM_USER_RTE_USR_SLEEP         ((BswM_UserType)0x8002U)
#define BSWM_USER_RTE_ACC               ((BswM_UserType)0x8003U)
#define BSWM_USER_RTE_IG                ((BswM_UserType)0x8004U)
#define BSWM_USER_SUBMICONIF_SESSION    ((BswM_UserType)0x1001U)
#define BSWM_USER_SUBMICONIF_SECURITY   ((BswM_UserType)0x1002U)
#define BSWM_USER_SUBMICONIF_ECU_RESET  ((BswM_UserType)0x1003U)
#define BSWM_USER_SUBMICONIF_MAIN_ERR   ((BswM_UserType)0x1004U)
#define BSWM_USER_SUBMICONIF_USR_RESET  ((BswM_UserType)0x1005U)
#define BSWM_USER_SUBMICONIF_USR_SLEEP  ((BswM_UserType)0x1006U)
#define BSWM_USER_SUBMICONIF_ACC        ((BswM_UserType)0x1007U)
#define BSWM_USER_SUBMICONIF_IG         ((BswM_UserType)0x1008U)
#if (REPROG_CFG_ETH_USE == STD_ON)
#define BSWM_USER_COMM_ETH_SENDRCV      ((BswM_UserType)0x2001U)
#endif

#if (REPROG_CFG_ETH_USE == STD_ON)
 #if (REPROG_CFG_SUBMICON_USE_SUB == STD_ON)
  #define BSWM_MAX_USER_NUM              ((uint8)18U)
 #else
  #define BSWM_MAX_USER_NUM              ((uint8)12U)
 #endif
#else
 #if (REPROG_CFG_SUBMICON_USE_SUB == STD_ON)
  #define BSWM_MAX_USER_NUM              ((uint8)17U)
 #else
  #define BSWM_MAX_USER_NUM              ((uint8)11U)
 #endif
#endif

/* BswM_ModeType */
#define BSWM_MODE_REWRITE_NONE          ((BswM_ModeType)0x0000U)
#define BSWM_MODE_REWRITE_START         ((BswM_ModeType)0x0001U)
#define BSWM_MODE_REWRITE_FINISH        ((BswM_ModeType)0x0002U)

#define BSWM_MODE_SESSION_DEF           ((BswM_ModeType)0x0001U)
#define BSWM_MODE_SESSION_EXT           ((BswM_ModeType)0x0003U)
#define BSWM_MODE_SESSION_PRG           ((BswM_ModeType)0x0002U)

#define BSWM_MODE_SECURITY_LOCK         ((BswM_ModeType)0x0000U)
#define BSWM_MODE_SECURITY_UNLOCK_LV1   ((BswM_ModeType)0x0001U)
#define BSWM_MODE_SECURITY_UNLOCK_LV2   ((BswM_ModeType)0x0002U)
#define BSWM_MODE_SECURITY_UNLOCK_LV3   ((BswM_ModeType)0x0004U)
#define BSWM_MODE_SECURITY_UNLOCK_LV4   ((BswM_ModeType)0x0008U)
#define BSWM_MODE_SECURITY_UNLOCK_LV5   ((BswM_ModeType)0x0010U)
#define BSWM_MODE_SECURITY_UNLOCK_LV6   ((BswM_ModeType)0x0020U)
#define BSWM_MODE_SECURITY_UNLOCK_LV7   ((BswM_ModeType)0x0040U)
#define BSWM_MODE_SECURITY_UNLOCK_LV8   ((BswM_ModeType)0x0080U)

#define BSWM_MODE_FLS_PRG_NOTREADY      ((BswM_ModeType)0x0000U)
#define BSWM_MODE_FLS_PRG_READY         ((BswM_ModeType)0x0001U)

#define BSWM_MODE_ECU_RESET_NONE        ((BswM_ModeType)0x0000U)
#define BSWM_MODE_ECU_RESET_EXECUTE     ((BswM_ModeType)0x0001U)

#define BSWM_MODE_FINISH_NONE           ((BswM_ModeType)0x0000U)
#define BSWM_MODE_FINISH_NORMAL         ((BswM_ModeType)0x0001U)
#define BSWM_MODE_FINISH_ERROR          ((BswM_ModeType)0x0002U)

#define BSWM_MODE_MAIN_ERR_NONE         ((BswM_ModeType)0x0000U)
#define BSWM_MODE_MAIN_ERR_OCCUR        ((BswM_ModeType)0x0001U)

#define BSWM_MODE_USR_RESET_NONE        ((BswM_ModeType)0x0000U)
#define BSWM_MODE_USR_RESET_EXECUTE     ((BswM_ModeType)0x0001U)

#define BSWM_MODE_USR_SLEEP_NONE        ((BswM_ModeType)0x0000U)
#define BSWM_MODE_USR_SLEEP_EXECUTE     ((BswM_ModeType)0x0001U)

#define BSWM_MODE_ACC_NONE              ((BswM_ModeType)0x0000U)
#define BSWM_MODE_ACC_ON                ((BswM_ModeType)0x0001U)
#define BSWM_MODE_ACC_OFF               ((BswM_ModeType)0x0002U)

#define BSWM_MODE_IG_NONE               ((BswM_ModeType)0x0000U)
#define BSWM_MODE_IG_ON                 ((BswM_ModeType)0x0001U)
#define BSWM_MODE_IG_OFF                ((BswM_ModeType)0x0002U)

#if (REPROG_CFG_ETH_USE == STD_ON)
#define BSWM_MODE_ETH_SENDRCV_NONE      ((BswM_ModeType)0x0000U)
#define BSWM_MODE_ETH_SENDRCV_START     ((BswM_ModeType)0x0001U)
#define BSWM_MODE_ETH_SENDRCV_WAITSTOP  ((BswM_ModeType)0x0002U)
#define BSWM_MODE_ETH_SENDRCV_STOP      ((BswM_ModeType)0x0003U)
#endif

/* Finish */
#define BSWM_FINISHTYPE_USR_RESET       ((uint8)0x01U)
#define BSWM_FINISHTYPE_USR_SLEEP       ((uint8)0x02U)
#define BSWM_FINISHTYPE_ECU_RESET       ((uint8)0x03U)
#define BSWM_FINISHTYPE_ERROR           ((uint8)0x04U)
#define BSWM_FINISHTYPE_ACCOFF          ((uint8)0x05U)
#define BSWM_FINISHTYPE_IGOFF           ((uint8)0x06U)
#define BSWM_FINISHTYPE_MAIN_ERR        ((uint8)0x07U)

#define BSWM_FINISHTYPE_NUM             ((uint8)7U)

/* Shutdown */
#define BSWM_SHUTDOWN_NONE              ((uint8)0x00U)
#define BSWM_SHUTDOWN_RESET             ((uint8)0x01U)
#define BSWM_SHUTDOWN_SLEEP             ((uint8)0x02U)

#if (REPROG_CFG_ETH_USE == STD_ON)
#define BSWM_ETHSM_MAXNETWORK_NUM       ((uint8)16U)
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint16  BswM_UserType;
typedef uint16  BswM_ModeType;

typedef struct {
    BswM_ModeType               InitValRewrite;
    BswM_ModeType               InitValSession;
    BswM_ModeType               InitValSecurity;
    BswM_ModeType               InitValFlsPrg;
    BswM_ModeType               InitValEcuReset;
    BswM_ModeType               InitValFinish;
    BswM_ModeType               InitValMainErr;
    BswM_ModeType               InitValUsrReset;
    BswM_ModeType               InitValUsrSleep;
    BswM_ModeType               InitValAcc;
    BswM_ModeType               InitValIg;
    CanSM_BswMRequestedModeType InitValCanSMState;
#if (REPROG_CFG_ETH_USE == STD_ON)
    EthSM_NetworkModeStateType  InitValEthSMState;
    BswM_ModeType               InitValEthSendRcv;
#endif
} BswM_ModeInitValConfigType;

typedef struct {
    uint8   FinPri[BSWM_FINISHTYPE_NUM];
} BswM_FinishPriorityConfigType;

typedef struct {
    uint8   ActAcc;
    uint8   ActIg;
} BswM_AccIgActionConfigType;

typedef struct {
    P2CONST(uint8, TYPEDEF, BSWM_APPL_CONST) UidPtr;
    uint32  UidSize;
    uint32  KeyID;
    uint8   UidSkip;
} BswM_UidConfigType;

#if (REPROG_CFG_ETH_USE == STD_ON)
typedef struct {
    uint8  NetworkNum;
    P2CONST(EthSM_NetworkType, TYPEDEF, BSWM_APPL_CONST) NetworkSettingTbl;
} BswM_EthSM_NetworkConfigType;

typedef struct {
    P2CONST(BswM_EthSM_NetworkConfigType, TYPEDEF, BSWM_APPL_CONST) NetworkInfoTbl;
} BswM_EthSM_ConfigType;
#endif

#if (REPROG_CFG_CXPI_USE == STD_ON)
typedef struct {
    PduIdType PduId;
    uint8 Nad;
    uint8 Controller;
} BswM_CxpiSM_PduIdSettingConfigType;

typedef struct {
    P2CONST(BswM_CxpiSM_PduIdSettingConfigType, TYPEDEF, BSWM_APPL_CONST) PduIdSettingTbl;
    uint8 PduIdNum;
} BswM_CxpiSM_PduIdConfigType;

typedef struct {
    NetworkHandleType NetworkId;
} BswM_CxpiSM_NetworkSettingConfigType;

typedef struct {
    P2CONST(BswM_CxpiSM_NetworkSettingConfigType, TYPEDEF, BSWM_APPL_CONST) NetworkSettingTbl;
} BswM_CxpiSM_NetworkConfigType;

typedef struct {
    P2CONST(BswM_CxpiSM_NetworkConfigType, TYPEDEF, BSWM_APPL_CONST) NetworkInfoTbl;
    P2CONST(BswM_CxpiSM_PduIdConfigType, TYPEDEF, BSWM_APPL_CONST) PduIdInfoTbl;
} BswM_CxpiSM_ConfigType;
#endif

typedef struct {
    P2CONST(BswM_ModeInitValConfigType, TYPEDEF, BSWM_APPL_CONST) InitValDataPtr;
    P2CONST(BswM_FinishPriorityConfigType, TYPEDEF, BSWM_APPL_CONST) FinPriDataPtr;
    P2CONST(BswM_AccIgActionConfigType, TYPEDEF, BSWM_APPL_CONST) AccIgActDataPtr;
    P2CONST(BswM_UidConfigType, TYPEDEF, BSWM_APPL_CONST) UidDataPtr;
    P2CONST(CanSM_ConfigType, TYPEDEF, BSWM_APPL_CONST) CanSMCfgDataPtr;
    P2CONST(CanIf_ConfigType, TYPEDEF, BSWM_APPL_CONST) CanIfCfgDataPtr;
    P2CONST(ComM_ConfigType, TYPEDEF, BSWM_APPL_CONST) ComMCfgDataPtr;
#if (REPROG_CFG_ETH_USE == STD_ON)
    P2CONST(BswM_EthSM_ConfigType, TYPEDEF, BSWM_APPL_CONST) EthSMCfgDataPtr;
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
    P2CONST(BswM_CxpiSM_ConfigType, TYPEDEF, BSWM_APPL_CONST) CxpiSMCfgDataPtr;
#endif
} BswM_ConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, BSWM_CODE_SLOW) BswM_Init
(
    P2CONST(BswM_ConfigType, AUTOMATIC, BSWM_APPL_CONST) ConfigPtr
);
FUNC(void, BSWM_CODE_SLOW) BswM_Deinit (void);
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode
(
    VAR(BswM_UserType, AUTOMATIC) requesting_user,
    VAR(BswM_ModeType, AUTOMATIC) requested_mode
);
#if (REPROG_CFG_CXPI_USE == STD_ON)
FUNC(uint8, BSWM_CODE_SLOW) BswM_CxpiCddGetNAD (void);
#endif
#if (REPROG_CFG_POSRES_AFTER_RESET == STD_ON)
FUNC(Std_ReturnType, BSWM_CODE_SLOW) BswM_Get_CommunicationInfo
(
    VAR(PduIdType, AUTOMATIC) PduId,
    P2VAR(uint8, AUTOMATIC, BSWM_APPL_DATA) ReceiveChannel,
    P2VAR(uint32, AUTOMATIC, BSWM_APPL_DATA) ReceiveId
);
#endif
#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
FUNC(void, BSWM_CODE_SLOW) BswM_SubMiconEventTxConfirmation
(
    VAR(uint16, AUTOMATIC) User,
    VAR(uint16, AUTOMATIC) Mode
);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC2_CST
#include <BswM_MemMap.h>

extern CONST(BswM_ConfigType, BSWM_CONFIG_DATA) BswM_Cfg_Data;
extern CONST(BswM_UidConfigType, BSWM_CONFIG_DATA) BswM_Cfg_UidData;

#define BSWM_STOP_SEC2_CST
#include <BswM_MemMap.h>


#endif /* BSWM_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2019/07/16 :Update                                rel.AUBASS */
/*  v4.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v5.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

