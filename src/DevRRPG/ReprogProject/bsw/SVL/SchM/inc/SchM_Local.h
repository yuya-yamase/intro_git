/* SchM_Local_h_Revision(v4.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | SchM/Local/HEADER                                           */
/******************************************************************************/
#ifndef SCHM_LOCAL_H
#define SCHM_LOCAL_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* API ID */
#define SCHM_API_ID_INIT            (0x01U)
#define SCHM_API_ID_MAINFUNC        (0x02U)
#define SCHM_API_ID_FIN_MAINFUNC    (0x03U)
#define SCHM_API_ID_NOTIFY_CH0      (0x04U)
#define SCHM_API_ID_NOTIFY_CH1      (0x05U)
#define SCHM_API_ID_SW_SESSION      (0x06U)
#define SCHM_API_ID_SW_RESET        (0x07U)
#define SCHM_API_ID_SW_SECURITY     (0x08U)
#define SCHM_API_ID_SW_REWRITE      (0x09U)
#define SCHM_API_ID_SW_FLSPRG       (0x0AU)
#define SCHM_API_ID_NOTIFY_FLSPRG   (0x0BU)
#define SCHM_API_ID_START_FLSCTRL   (0x0CU)
#define SCHM_API_ID_FINISH_FLSCTRL  (0x0DU)
#define SCHM_API_ID_RESET_CSMTIMER  (0x10U)
#define SCHM_API_ID_CHECK_CSMTIMER  (0x11U)
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
#define SCHM_API_ID_STAYINBOOT_CHKTMO   (0xF0U)
#endif

/* ERROR CODE */
#define SCHM_E_UNINIT               (0x81U)
#define SCHM_E_PARAM_POINTER        (0x82U)
#define SCHM_E_PARAM_INVALID        (0x83U)
#define SCHM_E_TM_RESET             (0x84U)
#define SCHM_E_TM_GET               (0x85U)
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
#define SCHM_E_STAYINBOOT_TIMEOUT   (0x86U)
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, SCHM_CODE_FAST) SchM_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define SCHM_RPRG_START_SEC_VAR
#include <SchM_Rprg_MemMap.h>

extern P2CONST(SchM_ConfigType, SCHM_VAR_CLEARED, SCHM_APPL_CONST) SchM_CfgPtr;
extern VAR(uint16, SCHM_VAR_CLEARED) SchM_FlsProgram;
extern VAR(uint8, SCHM_VAR_CLEARED) SchM_FinishFlg;
#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
extern VAR(uint8, SCHM_VAR_CLEARED) SchM_SubMiconFinEvtTxCmplFlg;
#endif

#define SCHM_RPRG_STOP_SEC_VAR
#include <SchM_Rprg_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* SCHM_LOCAL_H */

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

