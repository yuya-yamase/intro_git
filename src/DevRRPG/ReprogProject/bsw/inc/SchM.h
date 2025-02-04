/* SchM_h_Revision(v4.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | SchM/HEADER                                                 */
/******************************************************************************/
#ifndef SCHM_H
#define SCHM_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
#define SCHM_STATE_BOOT_ENTRY           ((uint8)0x00U)
#define SCHM_STATE_AP_ENTRY             ((uint8)0x01U)
#define SCHM_STATE_STAYINBOOT_WAIT      ((uint8)0x02U)
#define SCHM_STATE_STAYINBOOT_TMO       ((uint8)0x03U)
#define SCHM_STATE_STAYINBOOT_PRGRCV    ((uint8)0x04U)
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef P2FUNC(void, SCHM_CALLOUT_CODE, SchM_MainFuncType) (void);
typedef P2FUNC(void, SCHM_CALLOUT_CODE, SchM_TimeFuncType) (void);

typedef struct {
    SchM_MainFuncType   Func;
    uint8               FlsNotReady;
    uint8               FlsCtrl;
} SchM_MainFuncInfoConfigType;

typedef struct {
    uint32  FuncNum;
    P2CONST(SchM_MainFuncInfoConfigType, TYPEDEF, SCHM_APPL_CONST) FuncInfoPtr;
} SchM_MainFuncConfigType;

typedef struct {
    SchM_TimeFuncType   Func;
    uint8               FlsNotReady;
} SchM_TimeFuncInfoConfigType;

typedef struct {
    uint32  FuncNum;
    P2CONST(SchM_TimeFuncInfoConfigType, TYPEDEF, SCHM_APPL_CONST) FuncInfoPtr;
} SchM_TimeFuncConfigType;

typedef struct {
    P2CONST(SchM_MainFuncConfigType, TYPEDEF, SCHM_APPL_CONST) MainFuncDataPtr;
    P2CONST(SchM_TimeFuncConfigType, TYPEDEF, SCHM_APPL_CONST) TimeFunc0DataPtr;
    P2CONST(SchM_TimeFuncConfigType, TYPEDEF, SCHM_APPL_CONST) TimeFunc1DataPtr;
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
    uint32  StayInBootTime;
#endif
#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
    uint32  SubMiconFinEvtTxTimeOut;
#endif
} SchM_ConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, SCHM_CODE_SLOW) SchM_Init
(
    P2CONST(SchM_ConfigType, AUTOMATIC, SCHM_APPL_CONST) ConfigPtr
);
FUNC(void, SCHM_CODE_SLOW) SchM_Deinit (void);
FUNC(void, SCHM_CODE_SLOW) SchM_MainFunction (void);
FUNC(void, SCHM_CODE_SLOW) SchM_Notification_Channel0 (void);
FUNC(void, SCHM_CODE_SLOW) SchM_Notification_Channel1 (void);
FUNC(void, SCHM_CODE_SLOW) SchM_StartFlsCtrl (void);
FUNC(void, SCHM_CODE_SLOW) SchM_FinishFlsCtrl (void);
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
FUNC(uint8, SCHM_CODE_SLOW) SchM_GetStayInBootState (void);
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_SetStayInBootState
(
    VAR(uint8, AUTOMATIC) State
);
FUNC(uint8, SCHM_CODE_SLOW) SchM_GetRewriteCompFlg (void);
FUNC(void, SCHM_CODE_SLOW) SchM_SetRewriteCompFlg
(
    VAR(uint8, AUTOMATIC) RewriteCompFlg
);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SCHM_RPRG_START_SEC_CST
#include <SchM_Rprg_MemMap.h>

extern CONST(SchM_ConfigType, SCHM_CONFIG_DATA) SchM_Cfg_Data;

#define SCHM_RPRG_STOP_SEC_CST
#include <SchM_Rprg_MemMap.h>


#endif /* SCHM_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2019/07/16 :Update                                rel.AUBASS */
/*  v4.00       :2022/10/04 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

