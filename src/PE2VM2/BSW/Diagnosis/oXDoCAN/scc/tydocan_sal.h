/* 2.0.0 */
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
#define OXDOCAN_SAL_H_MAJOR                      (2U)
#define OXDOCAN_SAL_H_MINOR                      (0U)
#define OXDOCAN_SAL_H_PATCH                      (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_MAIN_TICK                           (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                          session-rd000-004-b.doc / SESSION-018 */
#define OXDC_SESSION_DEF                         (0x01U)                 /* 0x01  defaultSession                  */
#define OXDC_SESSION_RPG                         (0x02U)                 /* 0x02  programmingSession              */
#define OXDC_SESSION_EXT                         (0x03U)                 /* 0x03  extendedDiagnosticSession       */
#define OXDC_SESSION_OTA                         (0x50U)                 /* 0x50  otaSession                      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_NUM_SID                             (5U)
#define OXDC_SID_14                              (0U)                    /* 0x14 : Read by Identifier             */
#define OXDC_SID_19                              (1U)                    /* 0x19 :                                */
#define OXDC_SID_22                              (2U)                    /* 0x22 : Read by Identifier             */
#define OXDC_SID_2E                              (3U)                    /* 0x2E : Write by Identifier            */
#define OXDC_SID_31                              (4U)                    /* 0x31 : Routine                        */
#define OXDC_SID_INA                             (0xffU)                 /*        Service Inactive               */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_SERV_TIM_MAX                        (0xfffeU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_TASK_NUM_SLOT                       (10U)
#define OXDC_TSLOT_BIT_0                         (0x0001U)               /* 100ms A */
#define OXDC_TSLOT_BIT_1                         (0x0002U)               /* 100ms B */
#define OXDC_TSLOT_BIT_2                         (0x0004U)               /* 100ms C */
#define OXDC_TSLOT_BIT_3                         (0x0008U)               /* 100ms D */
#define OXDC_TSLOT_BIT_4                         (0x0010U)               /* 100ms E */
#define OXDC_TSLOT_BIT_5                         (0x0020U)               /* 100ms F */
#define OXDC_TSLOT_BIT_6                         (0x0040U)               /* 100ms G */
#define OXDC_TSLOT_BIT_7                         (0x0080U)               /* 100ms H */
#define OXDC_TSLOT_BIT_8                         (0x0100U)               /* 100ms I */
#define OXDC_TSLOT_BIT_9                         (0x0200U)               /* 100ms J */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_REQ_TYPE_PHYS                       (0U)
#define OXDC_REQ_TYPE_FUNC                       (1U)

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
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    const U1 *     u1p_RX;
    U4             u4_nbyte;          /* length of u1p_RX                                         */

    U2             u2_tim_elpsd;      /* resoluation = OXDOCAN_MAIN_TICK. Max = OXDC_SERV_TIM_MAX */
    U1             u1_sid;            /* OXDC_SID_XXX                                             */
    U1             u1_req_type;
    U1             u1_ses_bfr;        /* OXDC_SESSION_XX                                          */
    U1             u1_ses_aft;        /* OXDC_SESSION_XX                                          */
}ST_OXDC_REQ;

typedef struct{
    U1 *           u1p_tx;
    U4             u4_nbyte;          /* length of u1p_tx                                         */
}ST_OXDC_ANS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXDoCANAnsTx(const U1 u1_a_NRC, const ST_OXDC_ANS * st_ap_ANS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* OXDOCAN_SAL_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see oxdocan.c, oxdocan_[xxx].c and tydocan_[xxx].c                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
