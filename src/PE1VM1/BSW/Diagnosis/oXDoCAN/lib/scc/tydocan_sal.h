/* 1.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef OXDOCAN_SAL_H
#define OXDOCAN_SAL_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_SAL_H_MAJOR                      (1U)
#define OXDOCAN_SAL_H_MINOR                      (0U)
#define OXDOCAN_SAL_H_PATCH                      (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_USE                                 (0x00U)
#define OXDC_NOUSE                               (0xffU)
#define OXDC_MAIN_TICK                           (OXDC_MAIN_TICK_CFG)

#define OXDC_BYTE_SHIFT                          (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  SID 0x22/0x23/0x2E/0x2F/0x31 DataIdentifer and Routine Identifer                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_SAL_PROC_RUN                        (0x00U)          /* Request was accepted / Process is RUNning or can be run */
#define OXDC_SAL_PROC_FIN                        (0x01U)          /* Request was accepted / Process was FINished             */

/* Negative Response Code */
#define OXDC_SAL_PROC_NR_10                      (0x10U)          /* generalReject                                           */
#define OXDC_SAL_PROC_NR_12                      (0x12U)          /* sub-functionNotSupported                                */
#define OXDC_SAL_PROC_NR_13                      (0x13U)          /* incorrectMessageLengthOrInvalidFormat                   */
#define OXDC_SAL_PROC_NR_14                      (0x14U)          /* responseTooLong                                         */
#define OXDC_SAL_PROC_NR_21                      (0x21U)          /* busyRepeatRequest                                       */
#define OXDC_SAL_PROC_NR_22                      (0x22U)          /* conditionsNotCorrect                                    */
#define OXDC_SAL_PROC_NR_24                      (0x24U)          /* requestSequenceError                                    */
#define OXDC_SAL_PROC_NR_31                      (0x31U)          /* requestOutOfRange                                       */
#define OXDC_SAL_PROC_NR_33                      (0x33U)          /* securityAccessDenied                                    */
#define OXDC_SAL_PROC_NR_72                      (0x72U)          /* generalProgrammingFailure                               */
#define OXDC_SAL_PROC_NR_88                      (0x88U)          /* vehicleSpeedTooHigh                                     */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_XID_SUP_PUB                         (0x00U)
#define OXDC_XID_SUP_PRI                         (0x01U)
#define OXDC_XID_SUP_NOT                         (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* SID 0x2F I/O Control InputOutputParameter */
#define OXDC_IOC_PRM_CTE                         (0x00U)          /* returnControlToECU                                      */
#define OXDC_IOC_PRM_RTD                         (0x01U)          /* resetToDefault                                          */
#define OXDC_IOC_PRM_FCS                         (0x02U)          /* freezeCurrentState                                      */
#define OXDC_IOC_PRM_STA                         (0x03U)          /* shortTermAdjustment                                     */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* SID 0x31 Routine Control Subfunction      */
#define OXDC_ROUT_SUBF_START                     (0x01U)          /* startRoutine                                            */
#define OXDC_ROUT_SUBF_STOP                      (0x02U)          /* stopRoutine                                             */
#define OXDC_ROUT_SUBF_RESULT                    (0x03U)          /* requestRoutineResults                                   */

/* SID 0x31 Routine Control InputOutputParameter */
#define OXDC_ROUT_INFO_01                        (0x01U)          /* routineInfo 01 : startRoutine stopRoutine requestRoutineResults */
#define OXDC_ROUT_INFO_02                        (0x02U)          /* routineInfo 02 : startRoutine                                   */
#define OXDC_ROUT_INFO_03                        (0x03U)          /* routineInfo 03 : startRoutine             requestRoutineResults */
#define OXDC_ROUT_RESULT_RUN                     (0x01U)          /* routineStatusRecord 01 : Routine running    */
#define OXDC_ROUT_RESULT_OK                      (0x02U)          /* routineStatusRecord 02 : Normally completed */
#define OXDC_ROUT_RESULT_NG                      (0x03U)          /* routineStatusRecord 03 : Forced termination */

#define OXDC_ROUT_EXE_STS_IDLE                   (0x00U)
#define OXDC_ROUT_EXE_STS_RUN                    (0x01U)
#define OXDC_ROUT_EXE_STS_FIN                    (0x02U)
#define OXDC_ROUT_EXE_STS_ABORT                  (0x03U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  SID 0x14/0x19/0xBA Diag Trouble Code  Detection/Reset                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DTC_TR_INA                          (0x00U)          /* Trouble = Inactive                                      */
#define OXDC_DTC_TR_ACT                          (0x01U)          /* Trouble = Active                                        */
#define OXDC_DTC_TR_UNK                          (0x02U)          /* Trouble = Unknown                                       */
#define OXDC_DTC_TR_N_A                          (0x03U)          /* Trouble = Not Applicable                                */

#define OXDC_DTC_UDM_DEL_OK                      (0x00U)
#define OXDC_DTC_UDM_DEL_RUN                     (0x01U)
#define OXDC_DTC_UDM_DEL_NG                      (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DTC_KEY_UNLOCK                      (0xa5c38124U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  SID 0x22/0x19/0xBA Snapshot Recorder                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_TMSTP_TRIC_UNK                      (0xffffU)        /* Trip Counter = unknown                                  */

#define OXDC_TMSTP_TIMC_REC_MASK                 (0xffC00000U)    /* = Masks less than 4194304 msec = 69 min                 */

#define OXDC_TMSTP_CNT_LSB_4TH                   (24U)
#define OXDC_TMSTP_CNT_LSB_3RD                   (16U)
#define OXDC_TMSTP_CNT_LSB_2ND                   (8U)
#define OXDC_TMSTP_CNT_LSB_1ST                   (0U)

#define OXDC_TMSTP_TRIC_IDX_2ND                  (0U)
#define OXDC_TMSTP_TRIC_IDX_1ST                  (1U)
#define OXDC_TMSTP_TIMC_IDX_4TH                  (2U)
#define OXDC_TMSTP_TIMC_IDX_3RD                  (3U)
#define OXDC_TMSTP_TIMC_IDX_2ND                  (4U)
#define OXDC_TMSTP_TIMC_IDX_1ST                  (5U)
#define OXDC_TMSTP_SYNC_IDX                      (6U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_TMSTP_ODO_UNK                       (0xffffffffU)

#define OXDC_TMSTP_ODO_IDX_4TH                   (0U)
#define OXDC_TMSTP_ODO_IDX_3RD                   (1U)
#define OXDC_TMSTP_ODO_IDX_2ND                   (2U)
#define OXDC_TMSTP_ODO_IDX_1ST                   (3U)

#define OXDC_TMSTP_ODO_ANS_LSB_4TH               (24U)
#define OXDC_TMSTP_ODO_ANS_LSB_3RD               (16U)
#define OXDC_TMSTP_ODO_ANS_LSB_2ND               (8U)
/* #define OXDC_TMSTP_ODO_ANS_LSB_1ST               (0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_TMSTP_GMT_DWORD_UNK                 (0xffffffffU)
#define OXDC_TMSTP_GMT_NDWORD                    (2U)
#define OXDC_TMSTP_GMT_DW0                       (0U)
#define OXDC_TMSTP_GMT_DW1                       (1U)
#define OXDC_TMSTP_GMT_DW_NBYTE                  (8U)
#define OXDC_TMSTP_GMT_UNK                       (0xffU)
#define OXDC_TMSTP_GMT_NUM                       (6U)
#define OXDC_TMSTP_GMT_IDX_YE                    (0U)
#define OXDC_TMSTP_GMT_IDX_MO                    (1U)
#define OXDC_TMSTP_GMT_IDX_DA                    (2U)
#define OXDC_TMSTP_GMT_IDX_HO                    (3U)
#define OXDC_TMSTP_GMT_IDX_MI                    (4U)
#define OXDC_TMSTP_GMT_IDX_SE                    (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DID_SSR_KEY_UNLOCK                  (0x5a3c1842U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  SID 0x27 SecurityAccess                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_SEC_KIND_SEED                       (0U)
#define OXDC_SEC_KIND_KEY                        (1U)

#define OXDC_SUPPORT_SEC_LVL_NUM                 (1U)

#define OXDC_SECURITY_LVL02                      (2U)

#define OXDC_SEC_ALL_LEVELS_MASK                 (0xFFFFU)

#define OXDC_DTF_SIZE_USR_TMSP                   (32U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_TyDoCANDtcUnlock(const U4 u4_a_KEY);
void    vd_g_TyDoCANDtcLogRxReset(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U1               u1_gp_TYDC_DTF_INIT_TMSP[];

#endif      /* OXDOCAN_SAL_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see oxdocan.c, oxdocan_[xxx].c and tydocan_[xxx].c                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
