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

#define OXDC_SECURITY_LVL01                      (1U)
#define OXDC_SECURITY_LVL02                      (2U)
#define OXDC_SECURITY_LVL03                      (3U)
#define OXDC_SECURITY_LVL04                      (4U)
#define OXDC_SECURITY_LVL05                      (5U)
#define OXDC_SECURITY_LVL06                      (6U)
#define OXDC_SECURITY_LVL07                      (7U)
#define OXDC_SECURITY_LVL08                      (8U)
#define OXDC_SECURITY_LVL09                      (9U)
#define OXDC_SECURITY_LVL10                      (10U)
#define OXDC_SECURITY_LVL11                      (11U)
#define OXDC_SECURITY_LVL12                      (12U)
#define OXDC_SECURITY_LVL13                      (13U)
#define OXDC_SECURITY_LVL14                      (14U)
#define OXDC_SECURITY_LVL15                      (15U)
#define OXDC_SECURITY_LVL16                      (16U)
#define OXDC_SECURITY_LVL17                      (17U)
#define OXDC_SECURITY_LVL18                      (18U)
#define OXDC_SECURITY_LVL19                      (19U)
#define OXDC_SECURITY_LVL20                      (20U)
#define OXDC_SECURITY_LVL21                      (21U)
#define OXDC_SECURITY_LVL22                      (22U)
#define OXDC_SECURITY_LVL23                      (23U)
#define OXDC_SECURITY_LVL24                      (24U)
#define OXDC_SECURITY_LVL25                      (25U)
#define OXDC_SECURITY_LVL26                      (26U)
#define OXDC_SECURITY_LVL27                      (27U)
#define OXDC_SECURITY_LVL28                      (28U)
#define OXDC_SECURITY_LVL29                      (29U)
#define OXDC_SECURITY_LVL30                      (30U)
#define OXDC_SECURITY_LVL31                      (31U)
#define OXDC_SECURITY_LVL32                      (32U)
#define OXDC_SECURITY_LVL33                      (33U)
#define OXDC_SECURITY_LVL34                      (34U)
#define OXDC_SECURITY_LVL35                      (35U)
#define OXDC_SECURITY_LVL36                      (36U)
#define OXDC_SECURITY_LVL37                      (37U)
#define OXDC_SECURITY_LVL38                      (38U)
#define OXDC_SECURITY_LVL39                      (39U)
#define OXDC_SECURITY_LVL40                      (40U)
#define OXDC_SECURITY_LVL41                      (41U)
#define OXDC_SECURITY_LVL42                      (42U)
#define OXDC_SECURITY_LVL43                      (43U)
#define OXDC_SECURITY_LVL44                      (44U)
#define OXDC_SECURITY_LVL45                      (45U)
#define OXDC_SECURITY_LVL46                      (46U)
#define OXDC_SECURITY_LVL47                      (47U)
#define OXDC_SECURITY_LVL48                      (48U)
#define OXDC_SECURITY_LVL49                      (49U)
#define OXDC_SECURITY_LVL50                      (50U)
#define OXDC_SECURITY_LVL51                      (51U)
#define OXDC_SECURITY_LVL52                      (52U)
#define OXDC_SECURITY_LVL53                      (53U)
#define OXDC_SECURITY_LVL54                      (54U)
#define OXDC_SECURITY_LVL55                      (55U)
#define OXDC_SECURITY_LVL56                      (56U)
#define OXDC_SECURITY_LVL57                      (57U)
#define OXDC_SECURITY_LVL58                      (58U)
#define OXDC_SECURITY_LVL59                      (59U)
#define OXDC_SECURITY_LVL60                      (60U)
#define OXDC_SECURITY_LVL61                      (61U)
#define OXDC_SECURITY_LVL62                      (62U)
#define OXDC_SECURITY_LVL63                      (63U)

#define OXDC_SECURITY_KEY_1                      (0U)
#define OXDC_SECURITY_KEY_2                      (1U)
#define OXDC_SECURITY_KEY_3                      (2U)
#define OXDC_SECURITY_KEY_4                      (3U)
#define OXDC_SECURITY_KEY_5                      (4U)
#define OXDC_SECURITY_KEY_6                      (5U)
#define OXDC_SECURITY_KEY_7                      (6U)
#define OXDC_SECURITY_KEY_8                      (7U)
#define OXDC_SECURITY_KEY_9                      (8U)
#define OXDC_SECURITY_KEY_10                     (9U)

#define OXDC_SEC_KEY_STAT_INIT                   (0U)
#define OXDC_SEC_KEY_STAT_NOTREG                 (1U)
#define OXDC_SEC_KEY_STAT_REGISTERED             (2U)

#define OXDC_DTF_SIZE_USR_TMSP                   (32U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DID_SSR_SS_NDWORD                   (3U)
#define OXDC_DID_SSR_SS_DW0                      (0U)
#define OXDC_DID_SSR_SS_DW1                      (1U)
#define OXDC_DID_SSR_SS_DW2                      (2U)
typedef struct{
    U2         u2_rec_num;
    U2         u2_tri_cnt;
    U4         u4_tim_cnt;
    U4         u4_odo_0p1km;                    /* unit : 0.1km */
    U1         u1p_gmt[OXDC_TMSTP_GMT_NUM];
    U1         u1_tri_sync;
    U1         u1_spare;
    U4         u4p_ss[OXDC_DID_SSR_SS_NDWORD];
}ST_OXDC_DID_SSR;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_TyDoCANDtcUnlock(const U4 u4_a_KEY);
void    vd_g_TyDoCANDtcLogRxReset(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANDidSsrNumRecord(const U1 u1_a_SSR_CH, const U1 u1_a_REQ_MAX);
                                               /* u1_a_REQ_MAX TRUE  : Return = st_gp_OXDC_DID_SSR_CH_CFG[u1_a_SSR_CH].u1_num_rec */
                                               /*              FALSE : Return = st_gp_oxdc_did_ssr_ctrl[u1_a_SSR_CH].u1_rec_cnt   */

U1      u1_g_oXDoCANDidSsrRead(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr);

void    vd_g_oXDoCANDidSsrUnlock(const U4 u4_a_KEY);
void    vd_g_oXDoCANDidSsrDelete(const U1 u1_a_SSR_CH);
void    vd_g_oXDoCANDidSsrPause(const U1 u1_a_SSR_CH);

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
