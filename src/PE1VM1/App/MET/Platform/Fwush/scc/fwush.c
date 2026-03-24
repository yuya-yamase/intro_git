/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* FW Update State Handler                                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUSH_C_MAJOR                   (2U)
#define FWUSH_C_MINOR                   (0U)
#define FWUSH_C_PATCH                   (0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "fwush.h"

#include "ivdsh.h"
#include "memfill_u1.h"
#include "memfill_u4.h"
#include "nvmc_mgr.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

typedef struct {
    U1 u1_next_main_state;
    U1 u1_next_sub_state;
    void (*fp_handler_func)(void);
} ST_FWUSH_TRANSITION_ENTRY;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_fwush_state_main;
static U1 u1_s_fwush_state_sub;

static U1 u1_s_fwupx_req_seqcnt_pre;
static U1 u1_s_fwupx_res_seqcnt;

static U1 u1_s_fwush_abort;
static U1 u1_s_fwush_error_log;

static U1 u1_s_fwush_seq_progress;
static U4 u4_s_fwush_fswa_stat;
static U2 u2_s_fwush_veri_stat;
static U1 u1_s_fwush_veri_target;

/* PREP state data */
static U4 u4_s_fwush_prep_data_crc;

/* RUN state data */
static U2 u2_s_fwush_run_ofst;

/* Request header buffer */
static U1 u1_sp_fwush_header[FWUSH_REQ_H_SIZE];
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* Request processing */
static U1 u1_s_FwushReadHeader(U1 * u1_ap_ptr);
static U1 u1_s_FwushReadData(U4* u4_ap_adr);

/* Event detection */
static U1 u1_s_FwushDetectEvent(void);
static U1 u1_s_FwushDetectResumeEvent(void);
static U1 u1_s_FwushDetectEventForWaiting(void);
static U1 u1_s_FwushDetectEventForProcessing(void);
static U1 u1_s_FwushCheckMemAccJobEvent(void);
/* State-to-event mapping helper */
static U1 u1_s_FwushMapMainStatusToEvent(U1 u1_a_main_status);
/* MemAcc error-to-ACK mapping helper */
static U1 u1_s_FwushMapMemAccErrorToAck(void);
static U1 u1_s_FwushMapMemAccErrorToAckForRollback(void);
static U1 u1_s_FwushMapMemAccErrorToAckForOth(void);
/* Request-to-response subtype mapping helper */
static U1 u1_s_FwushMapReqToResSubtype(U1 u1_a_req_subtype);
/* Resume event detection */
static U1 u1_s_FwushDetectresponseEvent(U1 u1_a_req_subtype);

/* State handlers */
static void vd_s_FwushHandleEraseReq(void);
static void vd_s_FwushHandleRunReq(void);
static void vd_s_FwushHandleVerifyReq(void);
static void vd_s_FwushHandleActivateReq(void);
static void vd_s_FwushHandleValidateReq(void);
static void vd_s_FwushHandleFinalizeReq(void);
static void vd_s_FwushHandleRollbackReq(void);

static void vd_s_FwushHandleMonitorJob(void);

static void vd_s_FwushHandleEraseSuccess(void);
static void vd_s_FwushHandleRunSuccess(void);
static void vd_s_FwushHandleVerifySuccess(void);
static void vd_s_FwushHandleActivateSuccess(void);
static void vd_s_FwushHandleValidateSuccess(void);
static void vd_s_FwushHandleFinalizeSuccess(void);
static void vd_s_FwushHandleRollbackSuccess(void);

static void vd_s_FwushHandleJobProgress(void);
static void vd_s_FwushHandleProcessing(void);
static void vd_s_FwushHandleEraseAbort(void);
static void vd_s_FwushHandleRunAbort(void);
static void vd_s_FwushHandleVerifyAbort(void);
static void vd_s_FwushHandleActivateAbort(void);
static void vd_s_FwushHandleValidateAbort(void);
static void vd_s_FwushHandleFinalizeAbort(void);
static void vd_s_FwushHandleRollbackAbort(void);
static void vd_s_FwushHandleInvalidReq(void);

static U1 u1_s_FwushCheckValidArea(void);
static U1 u1_s_FwushCheckPrepTarget(U4 *u4_ap_adr);

/* CANCEL handlers */
static void vd_s_FwushHandleCancel(void);
/* Data generation */
static void vd_s_FwushMakeResData(U1 u1_a_subtype_res, U1 u1_a_response);
static U1   u1_s_FwushMakeRunData(U4 * u4_ap_adr, U2 * u2_ap_ofst);

/* Abort handling */
static void vd_s_FwushAbort(void);

/* for FWUSH_SEQ_PROGRESS */
static void vd_s_FwushUpdateSeqProgress(U1 u1_a_progress_bit);
static void vd_s_FwushResetSeqProgress(void);

static U1   u1_s_FwushGetFswaStat(void);
static void vd_s_FwushUpdateFswaStat(void);
static void vd_s_FwushResetFswaStat(void);

static void vd_s_FwushUpdateVeriStat(U1 u1_t_veri_target, U1 u1_t_veri_comp);
static void vd_s_FwushResetVeriStat(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* State transition table: [main state][sub state][event] Size: [5 main states][2 sub states][8 events] = 80 entries (38% reduction from old 128 entries) */
static const ST_FWUSH_TRANSITION_ENTRY stp_sp3_FWUSH_STM[FWUSH_MAIN_STATE_MAX]
                                                        [FWUSH_SUB_STATE_MAX ]
                                                        [FWUSH_EVENT_MAX     ] = {
    /*************************************************************************************************************/
    /* FWUSH_MAIN_STATE_PREP                                                                                     */
    /*************************************************************************************************************/
    {
        /* FWUSH_SUB_STATE_WAITING                                                                               */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleEraseReq},       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleInvalidReq},     /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleCancel},         /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_ACT,   (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_FIN,   (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleFinalizeReq}     /* FWUSH_EVENT_FIN_ACCEPT      */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleMonitorJob},      /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleEraseSuccess},    /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleEraseAbort},      /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleProcessing},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA}                        /* FWUSH_EVENT_FIN_ACCEPT      */
        }
    },
    
    /*************************************************************************************************************/
    /* FWUSH_MAIN_STATE_RUN                                                                                      */
    /*************************************************************************************************************/
    {
        /* FWUSH_SUB_STATE_WAITING                                                                               */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleRunReq},          /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleInvalidReq},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancel},          /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleEraseReq},        /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleFinalizeReq}      /* FWUSH_EVENT_FIN_ACCEPT      */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleMonitorJob},      /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleRunAbort},        /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleProcessing},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleRunSuccess},      /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleRunSuccess},      /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA}                        /* FWUSH_EVENT_FIN_ACCEPT      */
        }
    },
    
    /*************************************************************************************************************/
    /* FWUSH_MAIN_STATE_VERI                                                                                     */
    /*************************************************************************************************************/
    {
        /* FWUSH_SUB_STATE_WAITING                                                                               */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleVerifyReq},       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleInvalidReq},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancel},          /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleEraseReq},        /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleFinalizeReq}      /* FWUSH_EVENT_FIN_ACCEPT      */
        }, 
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleMonitorJob},      /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleVerifySuccess},   /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleVerifyAbort},     /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleProcessing},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA}                        /* FWUSH_EVENT_FIN_ACCEPT      */
        }
    },
    
    /*************************************************************************************************************/
    /* FWUSH_MAIN_STATE_ACT                                                                                      */
    /*************************************************************************************************************/
    {
        /* FWUSH_SUB_STATE_WAITING                                                                               */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleActivateReq},     /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleInvalidReq},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancel},          /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleRollbackReq},     /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleEraseReq},        /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleActivateSuccess}, /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleFinalizeReq}      /* FWUSH_EVENT_FIN_ACCEPT      */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleMonitorJob},      /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleActivateSuccess}, /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleActivateAbort},   /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleProcessing},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA}                        /* FWUSH_EVENT_FIN_ACCEPT      */
        }
    },
    
    /*************************************************************************************************************/
    /* FWUSH_MAIN_STATE_VALID                                                                                    */
    /*************************************************************************************************************/
    {
        /* FWUSH_SUB_STATE_WAITING                                                                               */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleValidateReq},     /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleInvalidReq},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_FIN,   (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleRollbackReq},     /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleActivateSuccess}, /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleFinalizeReq}      /* FWUSH_EVENT_FIN_ACCEPT      */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_FIN,   (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleValidateSuccess}, /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleValidateAbort},   /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA}                        /* FWUSH_EVENT_FIN_ACCEPT      */
        }
    },
    /*************************************************************************************************************/
    /* FWUSH_MAIN_STATE_FIN                                                                                      */
    /*************************************************************************************************************/
    {
        /* FWUSH_SUB_STATE_WAITING                                                                               */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,   &vd_s_FwushHandleFinalizeReq},       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleInvalidReq},       /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleRollbackReq},      /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleValidateSuccess},  /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,   &vd_s_FwushHandleFinalizeReq}        /* FWUSH_EVENT_FIN_ACCEPT      */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleMonitorJob},        /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleRollbackSuccess},   /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleJobProgress},       /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_WAITING   , &vd_s_FwushHandleRollbackAbort},     /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleProcessing},        /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleProcessing},        /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_ACT_ACCEPT      */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_VALID_ACCEPT    */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA}                          /* FWUSH_EVENT_FIN_ACCEPT      */
        }
    }
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void vd_g_FwushInit(void)                                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwushInit(void)
{
    U1 u1_t_nvm_chk;
    /* Initialize state variables */
    u1_s_fwush_state_main       = (U1)FWUSH_MAIN_STATE_PREP;
    u1_s_fwush_state_sub        = (U1)FWUSH_SUB_STATE_WAITING;
    u1_s_fwupx_req_seqcnt_pre   = (U1)0x00U;
    u1_s_fwupx_res_seqcnt       = (U1)0x00U;
    u1_s_fwush_abort            = (U1)FALSE;
    u1_s_fwush_error_log        = (U1)FWUSH_ACK_OK;
    u4_s_fwush_prep_data_crc    = (U4)0U;
    u2_s_fwush_run_ofst         = (U2)0xFFFFU;
    u1_s_fwush_veri_target      = (U1)FWUSH_VERI_LB_NONE;
    u1_t_nvm_chk = u1_g_Nvmc_ReadU1withSts((U2)NVMCID_U1_FWUSH_SEQ_PROGRESS, &u1_s_fwush_seq_progress);
    if(u1_t_nvm_chk != (U1)NVMC_STATUS_COMP) {
        /* If read error, reset progress */
        u1_s_fwush_seq_progress = (U1)FWUSH_PROGRESS_INIT;
    }
    u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts((U2)NVMCID_U4_FWUSH_FSWASTAT_0_INFO, &u4_s_fwush_fswa_stat);
    if(u1_t_nvm_chk != (U1)NVMC_STATUS_COMP) {
        /* If read error, reset progress */
        u4_s_fwush_fswa_stat = (U4)FWUSH_FSWA_STS_INIT;
    }
    u1_t_nvm_chk = u1_g_Nvmc_ReadU2withSts((U2)NVMCID_U2_FWUSH_VERIFY_LBN_COMP, &u2_s_fwush_veri_stat);
    if(u1_t_nvm_chk != (U1)NVMC_STATUS_COMP) {
        /* If read error, reset progress */
        u2_s_fwush_veri_stat = (U2)FWUSH_VERI_LB_STAT_INIT;
    }

    /* Clear header buffer */
    vd_g_MemfillU1(&u1_sp_fwush_header[0], (U1)0U, (U4)FWUSH_REQ_H_SIZE);
    
    /* Initialize FwuMemAcc */
    vd_g_FwuMemAccInit();
}

/*===================================================================================================================================*/
/* void vd_g_FwushMainTask(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwushMainTask(void)
{
    const ST_FWUSH_TRANSITION_ENTRY*    stp_t_TRANSITION;
    U1                                  u1_t_state_main_crnt;
    U1                                  u1_t_state_sub_crnt;
    U1                                  u1_t_event;

    u1_t_state_main_crnt = u1_s_fwush_state_main;
    u1_t_state_sub_crnt  = u1_s_fwush_state_sub;

    /* 1. Event detection (reads header internally) */
    u1_t_event = u1_s_FwushDetectEvent();
    
    /* 2. Consult state transition table */
    stp_t_TRANSITION = &stp_sp3_FWUSH_STM[u1_t_state_main_crnt]
                                         [u1_t_state_sub_crnt ]
                                         [u1_t_event          ];

    /* 3. Execute Transition Event Handler */
    if(stp_t_TRANSITION->fp_handler_func != vdp_PTR_NA){
        stp_t_TRANSITION->fp_handler_func();
    }

    /* 4. Update state */
    u1_s_fwush_state_main = stp_t_TRANSITION->u1_next_main_state;
    u1_s_fwush_state_sub  = stp_t_TRANSITION->u1_next_sub_state;

    /* 5. Execute MemAcc task */
    vd_g_FwuMemAccMainTask();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Event Detection                                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* static U1 u1_s_FwushDetectEvent(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Detected event                                                                                              */
/*===================================================================================================================================*/
static U1 u1_s_FwushDetectEvent(void)
{
    U1 u1_t_event;
    U1 u1_t_head_ok;

    u1_t_event = u1_s_FwushDetectResumeEvent();
    if(u1_t_event != (U1)FWUSH_EVENT_NONE){
        /* Keep Resume Event */
    }
    else if(u1_s_fwush_state_sub == (U1)FWUSH_SUB_STATE_WAITING){
        u1_t_head_ok = u1_s_FwushReadHeader(&u1_sp_fwush_header[0]);
        if(u1_t_head_ok == (U1)FALSE){
            u1_t_event = (U1)FWUSH_EVENT_NONE;
        }
        else{
            u1_t_event = u1_s_FwushDetectEventForWaiting();
        }
    }
    else if(u1_s_fwush_state_sub == (U1)FWUSH_SUB_STATE_PROCESSING){
        u1_t_head_ok = u1_s_FwushReadHeader(&u1_sp_fwush_header[0]);
        if(u1_t_head_ok == (U1)FALSE){
            u1_t_event = (U1)FWUSH_EVENT_NONE;
        }
        else{
            u1_t_event = u1_s_FwushDetectEventForProcessing();
        }

        if(u1_s_fwush_abort != (U1)FALSE){
            u1_t_event = (U1)FWUSH_EVENT_MEMACC_ERROR;
        }
    }
    else{
        /* Unexpected substate */
        u1_t_event = (U1)FWUSH_EVENT_NONE;
    }

    return(u1_t_event);
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushDetectResumeEvent(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Detected resume event                                                                                       */
/*===================================================================================================================================*/
static U1 u1_s_FwushDetectResumeEvent(void)
{
    static const U1 u1_s_FWUSH_PROG_MASK = (U1)(FWUSH_PROGRESS_ACT_DONE | FWUSH_PROGRESS_VALIDATE_DONE | FWUSH_PROGRESS_ROLLBACK_DONE);
    static const U1 u1_s_FWUSH_PROG_ACT_CRIT = (U1)FWUSH_PROGRESS_ACT_DONE;
    static const U1 u1_s_FWUSH_PROG_VALID_CRIT = (U1)(FWUSH_PROGRESS_ACT_DONE | FWUSH_PROGRESS_VALIDATE_DONE);
    U1 u1_t_event;
    U1 u1_t_veri_target;
    U1 u1_t_veri_comp;

    u1_t_event = (U1)FWUSH_EVENT_NONE;
    if(u1_s_fwush_state_main == (U1)FWUSH_MAIN_STATE_PREP){
        u1_t_veri_target = (U1)((u2_s_fwush_veri_stat >> (U2)8U) & (U2)0xFFU);
        u1_t_veri_comp = (U1)(u2_s_fwush_veri_stat & (U2)0xFFU);
        if((u1_s_fwush_seq_progress & u1_s_FWUSH_PROG_MASK) == u1_s_FWUSH_PROG_ACT_CRIT){
            /* Change state to Validate */
            u1_t_event = (U1)FWUSH_EVENT_SWITCH_DETECT;
        }
        else if((u1_t_veri_target == u1_t_veri_comp) &&
                (u2_s_fwush_veri_stat != (U2)FWUSH_VERI_LB_STAT_INIT)){
                u1_t_event = (U1)FWUSH_EVENT_RESUME_ACT;
        }
        else if((u1_s_fwush_seq_progress & u1_s_FWUSH_PROG_MASK) == u1_s_FWUSH_PROG_VALID_CRIT){
                u1_t_event = (U1)FWUSH_EVENT_RESUME_FIN;
        }
        else{
            /* Do Nothing */
        }
    }

    return(u1_t_event);
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushDetectEventForWaiting(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Detected event                                                                                              */
/*===================================================================================================================================*/
static U1 u1_s_FwushDetectEventForWaiting(void)
{
    static const U1 u1_sp_FWUSH_EXPCT_SUBTYPE_WA[FWUSH_MAIN_STATE_MAX] =
    {
        (U1)FWUSH_REQ_SUBTYPE_PREP,                      /* FWUSH_MAIN_STATE_PREP     (0U) */
        (U1)FWUSH_REQ_SUBTYPE_RUN,                       /* FWUSH_MAIN_STATE_RUN      (1U) */
        (U1)FWUSH_REQ_SUBTYPE_VERI,                      /* FWUSH_MAIN_STATE_VERI     (2U) */
        (U1)FWUSH_REQ_SUBTYPE_ACT,                       /* FWUSH_MAIN_STATE_ACT      (3U) */
        (U1)FWUSH_REQ_SUBTYPE_VALID,                     /* FWUSH_MAIN_STATE_VALID    (4U) */
        (U1)FWUSH_REQ_SUBTYPE_FIN                        /* FWUSH_MAIN_STATE_FIN      (5U) */
    };
    static const U1 u1_s_FWUSH_PROG_MASK_WAITING = (U1)(FWUSH_PROGRESS_ACT_DONE | FWUSH_PROGRESS_FINALIZE_DONE);
    static const U1 u1_s_FWUSH_PROG_ACT_CRIT_WAITING = (U1)FWUSH_PROGRESS_ACT_DONE;
    U1 u1_t_event;
    U1 u1_t_current_req_subtype;
    U1 u1_t_expected_subtype;
    U1 u1_t_seqcnt;
    U1 u1_t_resume_event;
    
    /* Expected subtype for main state */
    u1_t_current_req_subtype = u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET];
    u1_t_seqcnt              = u1_sp_fwush_header[FWUSH_REQ_SEQCNT_OFFSET];
    u1_t_event               = (U1)FWUSH_EVENT_NONE;
    u1_t_expected_subtype    = (U1)u1_sp_FWUSH_EXPCT_SUBTYPE_WA[u1_s_fwush_state_main];
    
    /* Detect request change */
    if(u1_t_seqcnt != u1_s_fwupx_req_seqcnt_pre){
        /* Check resume event first */
        u1_t_resume_event = u1_s_FwushDetectresponseEvent(u1_t_current_req_subtype);
        if(u1_t_resume_event != (U1)FWUSH_EVENT_NONE){
            u1_t_event = u1_t_resume_event;
        }
        else if(u1_t_current_req_subtype == u1_t_expected_subtype){
            u1_t_event = (U1)FWUSH_EVENT_NEW_REQUEST;
        }
        else if(u1_t_current_req_subtype == (U1)FWUSH_REQ_SUBTYPE_CANCEL){
            if((u1_s_fwush_seq_progress & u1_s_FWUSH_PROG_MASK_WAITING) == u1_s_FWUSH_PROG_ACT_CRIT_WAITING){
                u1_t_event = (U1)FWUSH_EVENT_ROLLBACK;
            }
            else{
                u1_t_event = (U1)FWUSH_EVENT_CANCEL;
            }
        }
        else if(u1_t_current_req_subtype == (U1)FWUSH_REQ_SUBTYPE_FIN){
            u1_t_event = (U1)FWUSH_EVENT_FIN_ACCEPT;
        }
        else if(u1_t_current_req_subtype != (U1)FWUSH_REQ_SUBTYPE_NA){
            u1_t_event = (U1)FWUSH_EVENT_INVALID_REQUEST;
            u1_s_fwush_error_log = (U1)FWUSH_ACK_SEQ_ERR;
        }
        else{
            /* Do Nothing */
        }
        u1_s_fwupx_req_seqcnt_pre = u1_t_seqcnt;
    }
    else{
        u1_t_event = (U1)FWUSH_EVENT_SAME_REQUEST;
    }

    return(u1_t_event);
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushDetectresponseEvent(U1 u1_a_req_subtype)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_req_subtype : Request subtype from header                                                                */
/*  Return:         U1 : Detected resume event (FWUSH_EVENT_NONE if no resume event)                                                 */
/*===================================================================================================================================*/
static U1 u1_s_FwushDetectresponseEvent(U1 u1_a_req_subtype)
{
    U1 u1_t_event;

    u1_t_event = (U1)FWUSH_EVENT_NONE;

    switch(u1_s_fwush_state_main){
        case (U1)FWUSH_MAIN_STATE_RUN:
            /* RUN + PREP -> PREP_ACCEPT */
            if(u1_a_req_subtype == (U1)FWUSH_REQ_SUBTYPE_PREP){
                u1_t_event = (U1)FWUSH_EVENT_PREP_ACCEPT;
            }
            break;
        case (U1)FWUSH_MAIN_STATE_VERI:
            /* VERI + PREP -> PREP_ACCEPT */
            if(u1_a_req_subtype == (U1)FWUSH_REQ_SUBTYPE_PREP){
                u1_t_event = (U1)FWUSH_EVENT_PREP_ACCEPT;
            }
            break;
        case (U1)FWUSH_MAIN_STATE_ACT:
            if(u1_a_req_subtype == (U1)FWUSH_REQ_SUBTYPE_PREP){
                /* ACT + PREP -> PREP_ACCEPT */
                u1_t_event = (U1)FWUSH_EVENT_PREP_ACCEPT;
            }
            else if((u1_a_req_subtype == (U1)FWUSH_REQ_SUBTYPE_ACT) &&
                    (u1_s_fwush_seq_progress & (U1)FWUSH_PROGRESS_ACT_DONE) != (U1)0U){
                /* ACT + ACT_DONE bit set -> ACT_ACCEPT (priority over NEW_REQUEST) */
                u1_t_event = (U1)FWUSH_EVENT_ACT_ACCEPT;
            }
            else{
                /* Do Nothing */
            }
            break;
        case (U1)FWUSH_MAIN_STATE_VALID:
            /* VALID + ACT -> ACT_ACCEPT */
            if(u1_a_req_subtype == (U1)FWUSH_REQ_SUBTYPE_ACT){
                u1_t_event = (U1)FWUSH_EVENT_ACT_ACCEPT;
            }
            break;
        case (U1)FWUSH_MAIN_STATE_FIN:
            /* FIN + VALID -> depends on ROLLBACK_DONE bit */
            if(u1_a_req_subtype == (U1)FWUSH_REQ_SUBTYPE_VALID){
                if((u1_s_fwush_seq_progress & (U1)FWUSH_PROGRESS_ROLLBACK_DONE) == (U1)0U){
                    /* ROLLBACK_DONE bit is 0 -> VALID_ACCEPT */
                    u1_t_event = (U1)FWUSH_EVENT_VALID_ACCEPT;
                }
                else{
                    /* ROLLBACK_DONE bit is 1 -> INVALID_REQUEST */
                    u1_t_event = (U1)FWUSH_EVENT_INVALID_REQUEST;
                    u1_s_fwush_error_log = (U1)FWUSH_ACK_SEQ_ERR;
                }
            }
            break;
        default:
            /* FWUSH_MAIN_STATE_PREP: no resume events */
            break;
    }

    return(u1_t_event);
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushDetectEventForProcessing(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Detected event                                                                                              */
/*===================================================================================================================================*/
static U1 u1_s_FwushDetectEventForProcessing(void)
{
    static const U1 u1_sp_FWUSH_EXPCT_SUBTYPE_PR[FWUSH_MAIN_STATE_MAX] =
    {
        (U1)FWUSH_REQ_SUBTYPE_PREP,                      /* FWUSH_MAIN_STATE_PREP     (0U) */
        (U1)FWUSH_REQ_SUBTYPE_RUN,                       /* FWUSH_MAIN_STATE_RUN      (1U) */
        (U1)FWUSH_REQ_SUBTYPE_VERI,                      /* FWUSH_MAIN_STATE_VERI     (2U) */
        (U1)FWUSH_REQ_SUBTYPE_ACT,                       /* FWUSH_MAIN_STATE_ACT      (3U) */
        (U1)FWUSH_REQ_SUBTYPE_VALID,                     /* FWUSH_MAIN_STATE_VALID    (4U) */
        (U1)FWUSH_REQ_SUBTYPE_FIN                        /* FWUSH_MAIN_STATE_FIN      (5U) */
    };
    U1 u1_t_event;
    U1 u1_t_current_req_subtype;
    U1 u1_t_seqcnt;

    u1_t_current_req_subtype = u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET];
    u1_t_seqcnt              = u1_sp_fwush_header[FWUSH_REQ_SEQCNT_OFFSET];
    
    /* Detect request change */
    if(u1_t_seqcnt != u1_s_fwupx_req_seqcnt_pre){
        if(u1_t_current_req_subtype != (U1)FWUSH_REQ_SUBTYPE_NA){
            u1_t_event = (U1)FWUSH_EVENT_INVALID_REQUEST;
        }
        else{
            u1_t_event = u1_s_FwushCheckMemAccJobEvent();
        }
        u1_s_fwupx_req_seqcnt_pre = u1_t_seqcnt;
    }
    else{
        u1_t_event = u1_s_FwushCheckMemAccJobEvent();
    }

    return(u1_t_event);
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushCheckMemAccJobEvent(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Detected event                                                                                              */
/*===================================================================================================================================*/
static U1 u1_s_FwushCheckMemAccJobEvent(void)
{
    U1 u1_t_job_type;
    U1 u1_t_main_status;
    U1 u1_t_event;
    U1 u1_t_update_status;

    vd_g_FwuMemAccGetStatus(&u1_t_job_type, &u1_t_main_status);
    u1_t_event = u1_s_FwushMapMainStatusToEvent(u1_t_main_status);
    if (u1_t_event == (U1)FWUSH_EVENT_MEMACC_ERROR){
        u1_s_fwush_error_log = u1_s_FwushMapMemAccErrorToAck();
    }

    switch (u1_s_fwush_state_main){
        case (U1)FWUSH_MAIN_STATE_RUN:
            if(u1_t_main_status == (U1)FWUMEMACC_MAIN_STATUS_COMPLETED){
                u1_t_update_status = u1_g_FwuMemAccGetUpdateStatus();
                if(u1_t_update_status == (U1)FWUMEMACC_UPDT_STS_ALL_COMP){
                    u1_t_event = (U1)FWUSH_EVENT_MEMACC_RUN_COMPLETE;
                }
                else if(u1_t_update_status == (U1)FWUMEMACC_UPDT_STS_IN_PROGRESS){
                    u1_t_event = (U1)FWUSH_EVENT_MEMACC_RUN_PARTIAL;
                }
                else {
                    /* FWUMEMACC_UPDT_STS_IDLE (Do Nothing) */
                }
            }
            break;
        case (U1)FWUSH_MAIN_STATE_VERI:
            u1_t_event = (U1)FWUSH_EVENT_MEMACC_SUCCESS; /* treated as immediate success */
            break;
        case (U1)FWUSH_MAIN_STATE_PREP:
        case (U1)FWUSH_MAIN_STATE_ACT:
        case (U1)FWUSH_MAIN_STATE_FIN:  /* for Rollback Memacc */
            /* u1_t_event = u1_s_FwushMapMainStatusToEvent(u1_t_main_status); */
            break;
        default:  /* FWUSH_MAIN_STATE_VALID */
            u1_t_event = (U1)FWUSH_EVENT_NONE;
            break;
    }

    return(u1_t_event);
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushMapMainStatusToEvent(U1 u1_a_main_status)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_main_status : Main status from MemAcc                                                                    */
/*  Return:         U1 : Mapped event                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_FwushMapMainStatusToEvent(U1 u1_a_main_status)
{
    static const U1 u1_sp_FWUMEMACC_STATUS_TO_EVENT[FWUMEMACC_MAIN_STATUS_MAX] =
    {
        (U1)FWUSH_EVENT_NONE,            /* FWUMEMACC_MAIN_STATUS_IDLE      (0U) */
        (U1)FWUSH_EVENT_MEMACC_PROGRESS, /* FWUMEMACC_MAIN_STATUS_REQUESTED (1U) */
        (U1)FWUSH_EVENT_MEMACC_PROGRESS, /* FWUMEMACC_MAIN_STATUS_ACTIVE    (2U) */
        (U1)FWUSH_EVENT_MEMACC_SUCCESS,  /* FWUMEMACC_MAIN_STATUS_COMPLETED (3U) */
        (U1)FWUSH_EVENT_MEMACC_ERROR     /* FWUMEMACC_MAIN_STATUS_ERROR     (4U) */
    };

    return(u1_sp_FWUMEMACC_STATUS_TO_EVENT[u1_a_main_status]);
}
/*===================================================================================================================================*/
/* static U1 u1_s_FwushMapMemAccErrorToAck(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Mapped fwush ACK error code                                                                                 */
/*===================================================================================================================================*/
static U1 u1_s_FwushMapMemAccErrorToAck(void)
{
    U1 u1_t_ack;

    if((u1_s_fwush_state_main == (U1)FWUSH_MAIN_STATE_FIN) &&
       (u1_s_fwush_state_sub  == (U1)FWUSH_SUB_STATE_PROCESSING)){
        u1_t_ack = u1_s_FwushMapMemAccErrorToAckForRollback();
    }
    else{
        u1_t_ack = u1_s_FwushMapMemAccErrorToAckForOth();
    }

    return(u1_t_ack);
}
/*===================================================================================================================================*/
/* static U1 u1_s_FwushMapMemAccErrorToAckForRollback(void)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Mapped fwush ACK error code (for Rollback)                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_FwushMapMemAccErrorToAckForRollback(void)
{
    static const U1 u1_sp_FWUMEMACC_ERROR_TO_ACK_RB[FWUMEMACC_ERROR_MAX] =
    {
        (U1)FWUSH_ACK_ROLLBACK_NG,            /* FWUMEMACC_ERROR_NONE             (0U) */
        (U1)FWUSH_ACK_ROLLBACK_PRECOND_ERR,   /* FWUMEMACC_ERROR_PRECONDITION_ERR (1U) */
        (U1)FWUSH_ACK_OFFSET_JUMP,            /* FWUMEMACC_ERROR_OFFSET_JUMP      (2U) */
        (U1)FWUSH_ACK_OFFSET_UNCHANGED,       /* FWUMEMACC_ERROR_OFFSET_UNCHANGED (3U) */
        (U1)FWUSH_ACK_OFFSET_SUBTRACT,        /* FWUMEMACC_ERROR_OFFSET_SUBTRACT  (4U) */
        (U1)FWUSH_ACK_ROLLBACK_NG,            /* FWUMEMACC_ERROR_MEMACC_FAILED    (5U) */
        (U1)FWUSH_ACK_ROLLBACK_START_ERR      /* FWUMEMACC_ERROR_START_ERR        (6U) */
    };
    U1 u1_t_error;
    u1_t_error = u1_g_FwuMemAccGetError();
    return(u1_sp_FWUMEMACC_ERROR_TO_ACK_RB[u1_t_error]);
}
/*===================================================================================================================================*/
/* static U1 u1_s_FwushMapMemAccErrorToAckForOth(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Mapped fwush ACK error code (for Other states)                                                              */
/*===================================================================================================================================*/
static U1 u1_s_FwushMapMemAccErrorToAckForOth(void)
{
    static const U1 u1_sp_FWUMEMACC_ERROR_TO_ACK[FWUMEMACC_ERROR_MAX] =
    {
        (U1)FWUSH_ACK_PROC_NG,            /* FWUMEMACC_ERROR_NONE             (0U) */
        (U1)FWUSH_ACK_PRECONDITION_ERR,   /* FWUMEMACC_ERROR_PRECONDITION_ERR (1U) */
        (U1)FWUSH_ACK_OFFSET_JUMP,        /* FWUMEMACC_ERROR_OFFSET_JUMP      (2U) */
        (U1)FWUSH_ACK_OFFSET_UNCHANGED,   /* FWUMEMACC_ERROR_OFFSET_UNCHANGED (3U) */
        (U1)FWUSH_ACK_OFFSET_SUBTRACT,    /* FWUMEMACC_ERROR_OFFSET_SUBTRACT  (4U) */
        (U1)FWUSH_ACK_PROC_NG,            /* FWUMEMACC_ERROR_MEMACC_FAILED    (5U) */
        (U1)FWUSH_ACK_PROC_START_ERR      /* FWUMEMACC_ERROR_START_ERR        (6U) */
    };
    U1 u1_t_error;
    u1_t_error = u1_g_FwuMemAccGetError();
    return(u1_sp_FWUMEMACC_ERROR_TO_ACK[u1_t_error]);
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  State Handlers                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleEraseReq(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      void                                                                                                             */
/*  Return:         void                                                                                                             */
/*===================================================================================================================================*/
static void vd_s_FwushHandleEraseReq(void)
{
    U1 u1_t_error;
    U1 *u1_tp_adr;
    U4 u4_t_adr;
    U4 u4_t_length;

    U1 u1_t_result;

    /* read data & store CRC in context */
    u1_t_error = u1_s_FwushCheckPrepTarget(&u4_t_adr);
    if(u1_t_error == (U1)FWUSH_ACK_OK){
        u1_tp_adr = (U1 *)u4_t_adr;
        u4_s_fwush_prep_data_crc =    (U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET]
                                    | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 1] << (U4)8U)
                                    | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 2] << (U4)16U)
                                    | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 3] << (U4)24U);
        u4_t_adr    = (U4)0x1c000U;
        u4_t_length = (U4)0x7A4000U;
        vd_s_FwushResetSeqProgress();
        vd_s_FwushUpdateFswaStat();

        u1_t_result = u1_g_FwuMemAccEraseReq(u4_t_adr, u4_t_length, u4_s_fwush_prep_data_crc);
        if(u1_t_result != (U1)FWUMEMACC_RET_OK){
            u1_s_fwush_abort     = (U1)TRUE;
            u1_s_fwush_error_log = u1_s_FwushMapMemAccErrorToAck();
        }
        else if(u2_s_fwush_veri_stat == (U2)FWUSH_VERI_LB_STAT_INIT){
            u1_s_fwush_veri_target = u1_sp_fwush_header[FWUSH_REQ_PREP_CUR_TARGET_OFFSET];
            vd_s_FwushUpdateVeriStat(u1_sp_fwush_header[FWUSH_REQ_PREP_ALL_TARGET_OFFSET], (U1)FWUSH_VERI_LB_NONE);
        }else{
            /* Don nothing */
        }
    }
    else{
        u1_s_fwush_abort     = (U1)TRUE;
        u1_s_fwush_error_log = (U1)u1_t_error;
    }
}
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleRunReq(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      void                                                                                                             */
/*  Return:         void                                                                                                             */
/*===================================================================================================================================*/
static void vd_s_FwushHandleRunReq(void)
{
    U1 u1_t_read_ok;
    U4 u4_t_adr;
    U1 u1_t_result;

    u1_t_read_ok = u1_s_FwushMakeRunData(&u4_t_adr, &u2_s_fwush_run_ofst);
    if(u1_t_read_ok == (U1)TRUE){
        u1_t_result = u1_g_FwuMemAccUpdateReq(u2_s_fwush_run_ofst, (const U4 *)u4_t_adr);
        if(u1_t_result != (U1)FWUMEMACC_RET_OK){
            u1_s_fwush_abort     = (U1)TRUE;
            u1_s_fwush_error_log = u1_s_FwushMapMemAccErrorToAck();
        }
    }
    else{
        u1_s_fwush_abort     = (U1)TRUE;
        u1_s_fwush_error_log = (U1)FWUSH_ACK_PRECONDITION_ERR;
    }
}
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleVerifyReq(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      void                                                                                                             */
/*  Return:         void                                                                                                             */
/*===================================================================================================================================*/
static void vd_s_FwushHandleVerifyReq(void)
{
}
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleActivateReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      void                                                                                                             */
/*  Return:         void                                                                                                             */
/*===================================================================================================================================*/
static void vd_s_FwushHandleActivateReq(void)
{
    U1 u1_t_result;

    u1_t_result = u1_g_FwuMemAccSwitchReq();
    if(u1_t_result != (U1)FWUMEMACC_RET_OK){
        u1_s_fwush_abort     = (U1)TRUE;
        u1_s_fwush_error_log = u1_s_FwushMapMemAccErrorToAck();
    }
}
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleValidateReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      void                                                                                                             */
/*  Return:         void                                                                                                             */
/*===================================================================================================================================*/
static void vd_s_FwushHandleValidateReq(void)
{
    U1 u1_t_chk_result;

    u1_t_chk_result = u1_s_FwushCheckValidArea();
    /* Request rollback */
    if(u1_t_chk_result == (U1)FWUSH_CHECK_VA_UNMATCH){
        /* Validate OK */
        u1_s_fwush_abort = (U1)FALSE;
    }
    else{
        /* Validate NG */
        u1_s_fwush_abort     = (U1)TRUE;
        u1_s_fwush_error_log = (U1)FWUSH_ACK_PROC_NG;
    }
}
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleFinalizeReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      void                                                                                                             */
/*  Return:         void                                                                                                             */
/*===================================================================================================================================*/
static void vd_s_FwushHandleFinalizeReq(void)
{
    vd_s_FwushHandleFinalizeSuccess();
}
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleRollbackReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleRollbackReq(void)
{
    U1 u1_t_result;
    U1 u1_t_chk_result;

    u1_t_chk_result = u1_s_FwushCheckValidArea();
    switch (u1_t_chk_result)
    {
    case (U1)FWUSH_CHECK_VA_ERROR:
        u1_s_fwush_abort     = (U1)TRUE;
        u1_s_fwush_error_log = (U1)FWUSH_ACK_ROLLBACK_START_ERR;
        break;
    case (U1)FWUSH_CHECK_VA_UNMATCH:
        u1_t_result = u1_g_FwuMemAccSwitchReq();
        if(u1_t_result != (U1)FWUMEMACC_RET_OK){
            u1_s_fwush_abort     = (U1)TRUE;
            u1_s_fwush_error_log = (U1)u1_s_FwushMapMemAccErrorToAck();
        }
        break;
    default:
        vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_CANCEL, (U1)FWUSH_ACK_ROLLBACK_DONE);
        break;
    }
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushCheckValidArea(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : 0x00=FWUSH_CHECK_VA_MATCH, 0x01=FWUSH_CHECK_VA_UNMATCH, 0xFF=FWUSH_CHECK_VA_ERROR                           */
/*===================================================================================================================================*/
static U1 u1_s_FwushCheckValidArea(void)
{
    static const U1 u1_s_FWUSH_SWVA_MASK = (U1)0x01U;
    static const U1 u1_s_FWUSH_SWAS_MASK = (U1)0x02U;
    U1 u1_t_swva_curr;
    U1 u1_t_swas_curr;
    U1 u1_t_swva_prev;
    U1 u1_t_swas_prev;
    U1 u1_t_dirty_flag;
    U1 u1_t_ret;

    u1_t_swva_curr = u1_s_FWUSH_SWVA_MASK & u1_s_FwushGetFswaStat();
    u1_t_swas_curr = u1_s_FWUSH_SWAS_MASK & u1_s_FwushGetFswaStat();
    u1_t_swva_prev = u1_s_FWUSH_SWVA_MASK & u4_s_fwush_fswa_stat;
    u1_t_swas_prev = u1_s_FWUSH_SWAS_MASK & u4_s_fwush_fswa_stat;

    u1_t_dirty_flag = u1_t_swas_curr | u1_t_swas_prev;

    if(u1_t_dirty_flag != (U1)FWUSH_SWAS_VALID){
        u1_t_ret = (U1)FWUSH_CHECK_VA_ERROR;
    }
    else if(u1_t_swva_curr != u1_t_swva_prev){
        u1_t_ret = (U1)FWUSH_CHECK_VA_UNMATCH;
    }
    else{
        u1_t_ret = (U1)FWUSH_CHECK_VA_MATCH;
    }
    return (u1_t_ret);
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushCheckPrepTarget(U4 *u4_ap_adr)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U4 *u4_ap_adr : Pointer to receive data address from FwushReadData                                               */
/*  Return:         U1 : FWUSH_ACK_OK / FWUSH_ACK_PRECONDITION_ERR / FWUSH_ACK_NO_REPRO_TARGET / FWUSH_ACK_LB_ERR                    */
/*===================================================================================================================================*/
static U1 u1_s_FwushCheckPrepTarget(U4 *u4_ap_adr)
{
    static const U1 u1_s_FWUSH_LB_VALID_MASK = (U1)(FWUSH_VERI_LB1 | FWUSH_VERI_LB2);
    U1 u1_t_read_ok;
    U1 u1_t_cur_target;
    U1 u1_t_all_target;
    U1 u1_t_result;

    u1_t_read_ok = u1_s_FwushReadData(u4_ap_adr);
    if(u1_t_read_ok == (U1)FALSE){
        u1_t_result = (U1)FWUSH_ACK_PRECONDITION_ERR;
    }
    else{
        u1_t_cur_target = u1_sp_fwush_header[FWUSH_REQ_PREP_CUR_TARGET_OFFSET];
        u1_t_all_target = u1_sp_fwush_header[FWUSH_REQ_PREP_ALL_TARGET_OFFSET];

        if(u1_t_all_target == (U1)FWUSH_VERI_LB_NONE){
            u1_t_result = (U1)FWUSH_ACK_NO_REPRO_TARGET;
        }
        else if(((u1_t_cur_target & u1_t_all_target) != u1_t_cur_target) ||
                ((u1_t_cur_target & u1_s_FWUSH_LB_VALID_MASK) != u1_t_cur_target) ||
                ((u1_t_all_target & u1_s_FWUSH_LB_VALID_MASK) != u1_t_all_target)){
            u1_t_result = (U1)FWUSH_ACK_LB_ERR;
        }
        else{
            u1_t_result = (U1)FWUSH_ACK_OK;
        }
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static void vd_s_FwushMonitorJob(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleMonitorJob(void)
{
    /* No special processing in current implementation */
    /* MemAcc status monitored by event detection */
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleEraseSuccess(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleEraseSuccess(void)
{
    /* State transition already applied by table */
    /* Send ACK */
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_PREP, (U1)FWUSH_ACK_OK);
    
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleRunSuccess(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleRunSuccess(void)
{
    /* State transition already applied by table */
    /* Send ACK */
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_RUN, (U1)FWUSH_ACK_OK);
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleVerifySuccess(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleVerifySuccess(void)
{
    /* State transition already applied by table */
    vd_s_FwushUpdateVeriStat((U1)FWUSH_VERI_LB_NONE, u1_s_fwush_veri_target);
    /* Send ACK */
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_VERI, (U1)FWUSH_ACK_OK);
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleActivateSuccess(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleActivateSuccess(void)
{
    /* State transition already applied by table */
    vd_s_FwushResetVeriStat();
    vd_s_FwushUpdateSeqProgress((U1)FWUSH_PROGRESS_ACT_DONE);
    /* Send ACK */
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_ACT, (U1)FWUSH_ACK_OK);
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleValidateSuccess(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleValidateSuccess(void)
{
    /* State transition already applied by table */
    vd_s_FwushUpdateSeqProgress((U1)FWUSH_PROGRESS_VALIDATE_DONE);
    /* Send ACK */
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_VALID, (U1)FWUSH_ACK_OK);
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleFinalizeSuccess(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleFinalizeSuccess(void)
{
    /* State transition already applied by table */
    vd_s_FwushUpdateSeqProgress((U1)FWUSH_PROGRESS_FINALIZE_DONE);
    /* Send ACK */
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_FIN, (U1)FWUSH_ACK_OK);

    vd_s_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleRollbackSuccess(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleRollbackSuccess(void)
{
    /* State transition already applied by table */
    vd_s_FwushUpdateSeqProgress((U1)FWUSH_PROGRESS_ROLLBACK_DONE);
    /* Send ACK */
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_CANCEL, (U1)FWUSH_ACK_ROLLBACK_DONE);

    vd_s_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleJobProgress(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleJobProgress(void)
{
    /* No special processing required in current implementation */
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleProcessing(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleProcessing(void)
{
    U1 u1_t_res_subtype;

    u1_t_res_subtype = u1_s_FwushMapReqToResSubtype(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET]);
    vd_s_FwushMakeResData(u1_t_res_subtype, (U1)FWUSH_ACK_PROCESSING);
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleEraseAbort(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleEraseAbort(void)
{
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_PREP, u1_s_fwush_error_log);
    vd_s_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleRunAbort(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleRunAbort(void)
{
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_RUN, u1_s_fwush_error_log);
    vd_s_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleVerifyAbort(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleVerifyAbort(void)
{
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_VERI, u1_s_fwush_error_log);
    vd_s_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleActivateAbort(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleActivateAbort(void)
{
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_ACT, u1_s_fwush_error_log);
    vd_s_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleValidateAbort(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleValidateAbort(void)
{
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_VALID, u1_s_fwush_error_log);
    vd_s_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleFinalizeAbort(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleFinalizeAbort(void)
{
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_FIN, u1_s_fwush_error_log);
    vd_s_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleRollbackAbort(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleRollbackAbort(void)
{
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_CANCEL, u1_s_fwush_error_log);
    vd_s_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleInvalidReq(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleInvalidReq(void)
{
    U1 u1_t_res_subtype;

    u1_t_res_subtype = u1_s_FwushMapReqToResSubtype(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET]);
    vd_s_FwushMakeResData(u1_t_res_subtype, u1_s_fwush_error_log);
    vd_s_FwushAbort();
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushMapReqToResSubtype(U1 u1_a_req_subtype)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_req_subtype : Request subtype                                                                            */
/*  Return:         U1 : Corresponding response subtype                                                                              */
/*===================================================================================================================================*/
static U1 u1_s_FwushMapReqToResSubtype(U1 u1_a_req_subtype)
{
    U1 u1_t_res_subtype;

    switch (u1_a_req_subtype)
    {
    case (U1)FWUSH_REQ_SUBTYPE_PREP:
        u1_t_res_subtype = (U1)FWUSH_RESP_SUBTYPE_PREP;
        break;
    case (U1)FWUSH_REQ_SUBTYPE_RUN:
        u1_t_res_subtype = (U1)FWUSH_RESP_SUBTYPE_RUN;
        break;
    case (U1)FWUSH_REQ_SUBTYPE_VERI:
        u1_t_res_subtype = (U1)FWUSH_RESP_SUBTYPE_VERI;
        break;
    case (U1)FWUSH_REQ_SUBTYPE_ACT:
        u1_t_res_subtype = (U1)FWUSH_RESP_SUBTYPE_ACT;
        break;
    case (U1)FWUSH_REQ_SUBTYPE_VALID:
        u1_t_res_subtype = (U1)FWUSH_RESP_SUBTYPE_VALID;
        break;
    case (U1)FWUSH_REQ_SUBTYPE_FIN:
        u1_t_res_subtype = (U1)FWUSH_RESP_SUBTYPE_FIN;
        break;
    case (U1)FWUSH_REQ_SUBTYPE_CANCEL:
        u1_t_res_subtype = (U1)FWUSH_RESP_SUBTYPE_CANCEL;
        break;
    default:
        u1_t_res_subtype = (U1)FWUSH_RESP_SUBTYPE_NA;
        break;
    }

    return(u1_t_res_subtype);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  CANCEL Handlers                                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleCancel(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleCancel(void)
{
    /* Return to PREP_WAITING (set in table) */
    vd_s_FwushResetVeriStat();
    vd_s_FwushUpdateSeqProgress((U1)FWUSH_PROGRESS_CANCEL_DONE);
    vd_s_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_CANCEL, (U1)FWUSH_ACK_OK);
    vd_s_FwushAbort();
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Request Processing                                                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* static U1 u1_s_FwushReadHeader(U1 * u1_ap_ptr)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 * u1_ap_ptr : Pointer to header buffer                                                                        */
/*  Return:         U1 : TRUE if header read successfully, FALSE otherwise                                                           */
/*===================================================================================================================================*/
static U1 u1_s_FwushReadHeader(U1 * u1_ap_ptr)
{
    U4  u4_tp_data[FWUSH_REQ_H_WORDS];
    U1  u1_t_read_ok;
    U1  u1_t_ret;
    U2  u2_t_idx;

    u1_t_ret = (U1)FALSE;
    u1_t_read_ok = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_FWUPXREQ_H, &u4_tp_data[0], (U2)FWUSH_REQ_H_WORDS);
    if(u1_t_read_ok != (U1)IVDSH_NO_REA){
        for(u2_t_idx = 0U; u2_t_idx < (U2)FWUSH_REQ_H_SIZE; u2_t_idx++){
            u1_ap_ptr[u2_t_idx] = (U1)(u4_tp_data[u2_t_idx / (U2)4U] >> ((U2)8U * (u2_t_idx % (U2)4U)) & (U4)0xFFU);
        }
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushReadData(U4* u4_ap_adr)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U4* u4_ap_adr : Pointer to store read address                                                                    */
/*  Return:         U1 : TRUE if data read successfully, FALSE otherwise                                                             */
/*===================================================================================================================================*/
static U1 u1_s_FwushReadData(U4* u4_ap_adr)
{
    U1  u1_t_read_ok;
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;

    u1_t_read_ok = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_FWUPXREQ_D, u4_ap_adr, (U2)FWUSH_REQ_D_WORDS);

    if((u1_t_read_ok != (U1)IVDSH_NO_REA) &&
       (u4_ap_adr != vdp_PTR_NA      )){
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Data Generation                                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* static void vd_s_FwushMakeResData(U1 u1_a_subtype, U1 u1_a_response)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_subtype : Response subtype                                                                               */
/*                  U1 u1_a_response : Response code                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushMakeResData(U1 u1_a_subtype, U1 u1_a_response)
{
    U4  u4_tp_res_data[FWUSH_RES_WORDS];

    if(u1_s_fwupx_res_seqcnt < (U1)0xFFU){
        u1_s_fwupx_res_seqcnt++;
    }
    else{
        u1_s_fwupx_res_seqcnt = (U1)0U;
    }
    vd_g_MemfillU4(&u4_tp_res_data[0], (U4)0U, (U4)FWUSH_RES_WORDS);

    u4_tp_res_data[0] = (U4)(u1_a_subtype | ((U4)u1_a_response << (U1)8U) | ((U4)0x01U << (U1)16U)
                      | (U4)((u2_s_fwush_run_ofst & (U2)0xFF00U) << (U1)16U));
    u4_tp_res_data[1] = (U4)((u2_s_fwush_run_ofst & (U2)0x00FFU)) | ((U4)0x04U << (U1)8U) | ((U4)0x00U << (U1)16U)
                      | ((U4)u1_s_fwupx_res_seqcnt << (U1)24U);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_res_data[0], (U2)FWUSH_RES_WORDS);
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushMakeRunData(U4 * u4_ap_adr, U2 * u2_ap_ofst)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U4 * u4_ap_adr    : Pointer to store address                                                                     */
/*                  U2 * u2_ap_ofst   : Pointer to store block offset                                                                */
/*  Return:         U1 : TRUE if data created successfully, FALSE otherwise                                                          */
/*===================================================================================================================================*/
static U1 u1_s_FwushMakeRunData(U4 * u4_ap_adr, U2 * u2_ap_ofst)
{
    U1   u1_t_ret;

    u1_t_ret = u1_s_FwushReadData(u4_ap_adr);
    *u2_ap_ofst = ((U2)u1_sp_fwush_header[FWUSH_REQ_RUN_BLKOFS_OFFSET + 1]) | 
                  ((U2)u1_sp_fwush_header[FWUSH_REQ_RUN_BLKOFS_OFFSET] << (U2)8U);
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/* static void vd_s_FwushAbort(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushAbort(void)
{
    /* Initialize state variables */
    u1_s_fwush_state_main       = (U1)FWUSH_MAIN_STATE_PREP;
    u1_s_fwush_state_sub        = (U1)FWUSH_SUB_STATE_WAITING;
    u1_s_fwush_abort            = (U1)FALSE;
    u1_s_fwush_error_log        = (U1)0x00U;
    u4_s_fwush_prep_data_crc    = (U4)0U;
    u2_s_fwush_run_ofst         = (U2)0xFFFFU;

    vd_s_FwushResetVeriStat();
    
    /* Clear header buffer */
    vd_g_MemfillU1(&u1_sp_fwush_header[0], (U1)0U, (U4)FWUSH_REQ_H_SIZE);
    
    /* Initialize FwuMemAcc */
    vd_g_FwuMemAccInit();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushUpdateSeqProgress(U1 u1_a_progress_bit)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_progress_bit : Progress bit to set                                                                       */
/*                      0x01U : MCU activate complete                                                                                */
/*                      0x02U : MCU validate complete                                                                                */
/*                      0x04U : MCU update complete                                                                                  */
/*                      0x08U : MCU cancel complete                                                                                  */
/*                      0x10U : MCU rollback complete                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushUpdateSeqProgress(U1 u1_a_progress_bit)
{
    U1 u1_t_updated;

    /* OR the new progress bit with the cached value */
    u1_t_updated = u1_s_fwush_seq_progress | u1_a_progress_bit;

    /* Write only if changed */
    if(u1_t_updated != u1_s_fwush_seq_progress){
        u1_s_fwush_seq_progress = u1_t_updated;
        vd_g_Nvmc_WriteU1((U2)NVMCID_U1_FWUSH_SEQ_PROGRESS, u1_s_fwush_seq_progress);
    }
}

/*===================================================================================================================================*/
/* static void vd_s_FwushResetSeqProgress(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushResetSeqProgress(void)
{
    if(u1_s_fwush_seq_progress != (U1)FWUSH_PROGRESS_INIT){
        u1_s_fwush_seq_progress = (U1)FWUSH_PROGRESS_INIT;
        vd_g_Nvmc_WriteU1((U2)NVMCID_U1_FWUSH_SEQ_PROGRESS, u1_s_fwush_seq_progress);
    }
}

/*===================================================================================================================================*/
/* static U1 u1_s_FwushGetFswaStat(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_FwushGetFswaStat(void)
{
    /* Same Address with CODEFLS_U4_REGADD_FSWASTAT_0 in CodeFls_Reg.h */
    return((U1)((*(volatile uint32 *)((uint32)0xFFA10000UL + 0x0A8UL) & (U1)FWUSH_FSWA_READ_POS)));
}

/*===================================================================================================================================*/
/* static void vd_s_FwushUpdateFswaStat(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushUpdateFswaStat(void)
{
    U4 u4_t_updated;

    u4_t_updated = (U4)0xFFFFFF00U | (U4)u1_s_FwushGetFswaStat();

    /* Write only if changed */
    if(u4_t_updated != u4_s_fwush_fswa_stat){
        u4_s_fwush_fswa_stat = u4_t_updated;
        vd_g_Nvmc_WriteU4((U2)NVMCID_U4_FWUSH_FSWASTAT_0_INFO, u4_s_fwush_fswa_stat);
    }
}

/*===================================================================================================================================*/
/* static void vd_s_FwushResetFswaStat(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushResetFswaStat(void)
{
    if(u4_s_fwush_fswa_stat != (U4)FWUSH_FSWA_STS_INIT){
        u4_s_fwush_fswa_stat = (U4)FWUSH_FSWA_STS_INIT;
        vd_g_Nvmc_WriteU4((U2)NVMCID_U4_FWUSH_FSWASTAT_0_INFO, u4_s_fwush_fswa_stat);
    }
}

/*===================================================================================================================================*/
/* static void vd_s_FwushUpdateVeriStat(U1 u1_t_veri_target, U1 u1_t_veri_comp)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_t_veri_target : target Logical Block                                                                          */
/*                  u1_t_veri_comp   : verification completion status                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushUpdateVeriStat(U1 u1_t_veri_target, U1 u1_t_veri_comp)
{
    U2 u2_t_updated;

    u2_t_updated = (U2)(u2_s_fwush_veri_stat | ((u1_t_veri_target << (U1)8U) | u1_t_veri_comp));

    /* Write only if changed */
    if(u2_t_updated != u2_s_fwush_veri_stat){
        u2_s_fwush_veri_stat = u2_t_updated;
        vd_g_Nvmc_WriteU2((U2)NVMCID_U2_FWUSH_VERIFY_LBN_COMP, u2_s_fwush_veri_stat);
    }
}

/*===================================================================================================================================*/
/* static void vd_s_FwushResetVeriStat(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushResetVeriStat(void)
{
    if(u2_s_fwush_veri_stat != (U2)FWUSH_VERI_LB_STAT_INIT){
        u2_s_fwush_veri_stat = (U2)FWUSH_VERI_LB_STAT_INIT;
        vd_g_Nvmc_WriteU2((U2)NVMCID_U2_FWUSH_VERIFY_LBN_COMP, u2_s_fwush_veri_stat);
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    10/27/2025  KI       New.                                                                                               */
/*  2.0.0    02/16/2026  KI       Refactoring - State machine reconstruction with CANCEL support                                     */
/*                                                                                                                                   */
/* * KI   = Kanji Ito, Denso Techno                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
