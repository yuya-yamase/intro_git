/* DiagSrv_SubMicon_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/SubMicon/HEADER                                     */
/******************************************************************************/
#ifndef DIAGSRV_SUBMICON_H
#define DIAGSRV_SUBMICON_H

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Rte.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Sub-microcontroller Gateway Status */
#define DIAGSRV_SUBM_GW_STAT_IDLE           ((uint8)0U)
#define DIAGSRV_SUBM_GW_STAT_EXEC           ((uint8)1U)
#define DIAGSRV_SUBM_GW_STAT_FINISH         ((uint8)2U)

/* Kind of Gateway Check */
#define DIAGSRV_SUBM_GW_DEPEND_SEQ          ((uint8)0U)    /* Decide whether to gateway by sequence */
#define DIAGSRV_SUBM_GW_DEPEND_MSG          ((uint8)1U)    /* Decide whether to gateway by message */

/* Microcontroller identifier */
#define DIAGSRV_SUBM_ID_MAIN                (RTE_SUBMICONIF_ID_MAIN)
#define DIAGSRV_SUBM_ID_SUB_1               (RTE_SUBMICONIF_ID_SUB_1)
#define DIAGSRV_SUBM_ID_SUB_2               (RTE_SUBMICONIF_ID_SUB_2)
#define DIAGSRV_SUBM_ID_SUB_3               (RTE_SUBMICONIF_ID_SUB_3)
#define DIAGSRV_SUBM_ID_SUB_4               (RTE_SUBMICONIF_ID_SUB_4)
#define DIAGSRV_SUBM_ID_SUB_5               (RTE_SUBMICONIF_ID_SUB_5)
#define DIAGSRV_SUBM_ID_SUB_6               (RTE_SUBMICONIF_ID_SUB_6)
#define DIAGSRV_SUBM_ID_SUB_7               (RTE_SUBMICONIF_ID_SUB_7)
#define DIAGSRV_SUBM_ID_SUB_8               (RTE_SUBMICONIF_ID_SUB_8)
#define DIAGSRV_SUBM_ID_SUB_9               (RTE_SUBMICONIF_ID_SUB_9)
#define DIAGSRV_SUBM_ID_SUB_10              (RTE_SUBMICONIF_ID_SUB_10)
#define DIAGSRV_SUBM_ID_SUB_11              (RTE_SUBMICONIF_ID_SUB_11)
#define DIAGSRV_SUBM_ID_SUB_12              (RTE_SUBMICONIF_ID_SUB_12)
#define DIAGSRV_SUBM_ID_SUB_13              (RTE_SUBMICONIF_ID_SUB_13)
#define DIAGSRV_SUBM_ID_SUB_14              (RTE_SUBMICONIF_ID_SUB_14)
#define DIAGSRV_SUBM_ID_SUB_15              (RTE_SUBMICONIF_ID_SUB_15)
#define DIAGSRV_SUBM_ID_SUB_16              (RTE_SUBMICONIF_ID_SUB_16)
#define DIAGSRV_SUBM_ID_SUB_17              (RTE_SUBMICONIF_ID_SUB_17)
#define DIAGSRV_SUBM_ID_SUB_18              (RTE_SUBMICONIF_ID_SUB_18)
#define DIAGSRV_SUBM_ID_SUB_19              (RTE_SUBMICONIF_ID_SUB_19)
#define DIAGSRV_SUBM_ID_SUB_20              (RTE_SUBMICONIF_ID_SUB_20)
#define DIAGSRV_SUBM_ID_SUB_21              (RTE_SUBMICONIF_ID_SUB_21)
#define DIAGSRV_SUBM_ID_SUB_22              (RTE_SUBMICONIF_ID_SUB_22)
#define DIAGSRV_SUBM_ID_SUB_23              (RTE_SUBMICONIF_ID_SUB_23)
#define DIAGSRV_SUBM_ID_SUB_24              (RTE_SUBMICONIF_ID_SUB_24)
#define DIAGSRV_SUBM_ID_SUB_25              (RTE_SUBMICONIF_ID_SUB_25)
#define DIAGSRV_SUBM_ID_SUB_26              (RTE_SUBMICONIF_ID_SUB_26)
#define DIAGSRV_SUBM_ID_SUB_27              (RTE_SUBMICONIF_ID_SUB_27)
#define DIAGSRV_SUBM_ID_SUB_28              (RTE_SUBMICONIF_ID_SUB_28)
#define DIAGSRV_SUBM_ID_SUB_29              (RTE_SUBMICONIF_ID_SUB_29)
#define DIAGSRV_SUBM_ID_SUB_30              (RTE_SUBMICONIF_ID_SUB_30)
#define DIAGSRV_SUBM_ID_SUB_31              (RTE_SUBMICONIF_ID_SUB_31)

/* Result of Gateway Check */
#define DIAGSRV_SUBM_GWTGT_OFF              ((uint8)0x00U)
#define DIAGSRV_SUBM_GWTGT_OFF_SEQ_START    ((uint8)0x01U)
#define DIAGSRV_SUBM_GWTGT_OFF_SEQ_END      ((uint8)0x02U)
#define DIAGSRV_SUBM_GWTGT_ON               ((uint8)0x80U)
#define DIAGSRV_SUBM_GWTGT_ON_SEQ_START     ((uint8)0x81U)
#define DIAGSRV_SUBM_GWTGT_ON_SEQ_END       ((uint8)0x82U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(uint8, DIAGSRV_CODE_SLOW) DiagSrv_SubM_JudgeGw
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) MiconId
);
FUNC(uint8, DIAGSRV_CODE_SLOW) DiagSrv_SubM_ConvertRewriteArea2MiconId
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum
);
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_SubM_ClearSequence (void);
FUNC(uint8, DIAGSRV_CODE_SLOW) DiagSrv_SubM_GetSequenceMiconId (void);
FUNC(uint8, DIAGSRV_CODE_SLOW) DiagSrv_SubM_GetGwStatus (void);
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_SubM_SetGwStatus
(
    VAR(uint8, AUTOMATIC) Status
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


#endif /* (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) */
#endif /* DIAGSRV_SUBMICON_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

