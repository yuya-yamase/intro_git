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

/* PREP state data */
static U1 u1_s_fwush_prep_data_ready;
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
static U1 u1_s_FwushReadData(U2 u2_a_length, U4* u4_ap_reqadr);

/* Event detection */
static U1 u1_s_FwushDetectEvent(void);
static U1 u1_s_FwushDetectEventForWaiting(void);
static U1 u1_s_FwushDetectEventForProcessing(void);
static U1 u1_s_FwushCheckMemAccJobEvent(void);
/* State-to-event mapping helper (Phase2 unified) */
static U1 u1_s_MapMainStatusToEvent(U1 u1_a_main_status);
static void vd_s_FwushExecuteStateSpecificAction(U1 event);

/* State handlers */
static void vd_s_FwushHandleEraseReq(void);
static void vd_s_FwushHandleRunReq(void);
static void vd_s_FwushHandleVerifyReq(void);
static void vd_s_FwushHandleActivateReq(void);
static void vd_s_FwushHandleMonitorJob(void);
static void vd_s_FwushHandleEraseSuccess(void);
static void vd_s_FwushHandleRunSuccess(void);
static void vd_s_FwushHandleVerifySuccess(void);
static void vd_s_FwushHandleActivateSuccess(void);
static void vd_s_FwushHandleJobProgress(void);
static void vd_s_FwushHandleAbort(void);

/* CANCEL handlers */
static void vd_s_FwushHandleCancel(void);
static void vd_s_FwushHandleCancelDuringJob(void);
static void vd_s_FwushHandleCancelRollback(void);

/* Data generation */
static void vd_s_FwushMakeResData(U1 u1_a_subtype_res, U1 u1_a_response);
static U1   u1_s_FwushMakePrepData(U4 * u4_ap_adr, U4 * u4_ap_length, U4 * u4_ap_crc);
static U1   u1_s_FwushMakeRunData(U4 * u4_ap_adr, U2 * u2_ap_ofst);

/* Abort handling */
static void vd_g_FwushAbort(void);
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
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleEraseReq},        /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleAbort},           /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleAbort},           /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA}                        /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleMonitorJob},      /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleEraseSuccess},    /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleAbort},           /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleCancelDuringJob}, /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA}                        /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        }
    },
    
    /*************************************************************************************************************/
    /* FWUSH_MAIN_STATE_RUN                                                                                      */
    /*************************************************************************************************************/
    {
        /* FWUSH_SUB_STATE_WAITING                                                                               */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleRunReq},         /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleAbort},          /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleAbort},          /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleCancel},         /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                     /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                     /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA}                      /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleMonitorJob},      /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleAbort},           /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancelDuringJob}, /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleRunSuccess},      /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleRunSuccess},      /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA}                        /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
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
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleAbort},           /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleAbort},           /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancel},          /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA}                        /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        }, 
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleMonitorJob},      /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleVerifySuccess},   /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleAbort},           /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancelDuringJob}, /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA}                        /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
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
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleAbort},           /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleAbort},           /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancel},          /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA}                        /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleMonitorJob},      /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleActivateSuccess}, /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleAbort},           /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP,      (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancelDuringJob}, /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA}                        /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        }
    },
    
    /*************************************************************************************************************/
    /* FWUSH_MAIN_STATE_ROLLBACK                                                                                 */
    /*************************************************************************************************************/
    {
        /* FWUSH_SUB_STATE_WAITING                                                                               */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA}                     /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA}                     /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
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
    /* Initialize state variables */
    u1_s_fwush_state_main       = (U1)FWUSH_MAIN_STATE_PREP;
    u1_s_fwush_state_sub        = (U1)FWUSH_SUB_STATE_WAITING;
    u1_s_fwupx_req_seqcnt_pre   = (U1)0x00U;
    u1_s_fwupx_res_seqcnt       = (U1)0x00U;
    u1_s_fwush_abort            = (U1)FALSE;
    u1_s_fwush_prep_data_ready  = (U1)FALSE;
    u4_s_fwush_prep_data_crc    = (U4)0U;
    u2_s_fwush_run_ofst     = (U2)0xFFFFU;
    
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
    U1                                  u1_t_main_crnt;
    U1                                  u1_t_sub_crnt;
    U1                                  u1_t_event;

    u1_t_main_crnt = u1_s_fwush_state_main;
    u1_t_sub_crnt  = u1_s_fwush_state_sub;

    /* 1. Event detection (reads header internally) */
    u1_t_event = u1_s_FwushDetectEvent();
    
    /* 2. Consult state transition table */
    stp_t_TRANSITION = &stp_sp3_FWUSH_STM[u1_t_main_crnt]
                                         [u1_t_sub_crnt ]
                                         [u1_t_event    ];

    /* 3. Execute Transition Event Handler */
    if(stp_t_TRANSITION->fp_handler_func != vdp_PTR_NA){
        stp_t_TRANSITION->fp_handler_func();
    }

    /* 4. Update state */
    u1_s_fwush_state_main = stp_t_TRANSITION->u1_next_main_state;
    u1_s_fwush_state_sub  = stp_t_TRANSITION->u1_next_sub_state;

    /* 5. Error handling */
    if(u1_s_fwush_abort != (U1)FALSE){
        vd_s_FwushMakeResData(u1_t_main_crnt, (U1)FWUSH_ACK_NG);
        vd_g_FwushAbort();
    }
    
    /* 6. Execute MemAcc task */
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

    if(u1_s_fwush_state_sub == (U1)FWUSH_SUB_STATE_WAITING){
        u1_t_head_ok = u1_s_FwushReadHeader(&u1_sp_fwush_header[0]);
        if(u1_t_head_ok == (U1)FALSE){
            u1_t_event = (U1)FWUSH_EVENT_NONE;
        }
        else{
            u1_t_event = u1_s_FwushDetectEventForWaiting();
            vd_s_FwushExecuteStateSpecificAction(u1_t_event);
        }
    }
    else if(u1_s_fwush_state_sub == (U1)FWUSH_SUB_STATE_PROCESSING){
        u1_t_event = u1_s_FwushDetectEventForProcessing();
    }
    else{
        /* Unexpected substate */
        u1_t_event = (U1)FWUSH_EVENT_NONE;
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
        (U1)FWUSH_REQ_SUBTYPE_NA                         /* FWUSH_MAIN_STATE_ROLLBACK (4U) */
    };
    U1 u1_t_event;
    U1 u1_t_current_req_subtype;
    U1 u1_t_expected_subtype;
    U1 u1_t_seqcnt;
    
    /* Expected subtype for main state */
    u1_t_current_req_subtype = u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET];
    u1_t_seqcnt              = u1_sp_fwush_header[FWUSH_REQ_SEQCNT_OFFSET];
    u1_t_event               = (U1)FWUSH_EVENT_NONE;
    u1_t_expected_subtype    = (U1)u1_sp_FWUSH_EXPCT_SUBTYPE_WA[u1_s_fwush_state_main];
    
    /* Detect request change */
    if(u1_t_seqcnt != u1_s_fwupx_req_seqcnt_pre){
        if(u1_t_current_req_subtype == u1_t_expected_subtype){
            u1_t_event = (U1)FWUSH_EVENT_NEW_REQUEST;
        }
        else if(u1_t_current_req_subtype == (U1)FWUSH_REQ_SUBTYPE_CANCEL){
            u1_t_event = (U1)FWUSH_EVENT_CANCEL;
        }
        else if(u1_t_current_req_subtype != (U1)FWUSH_REQ_SUBTYPE_NA){
            u1_t_event = (U1)FWUSH_EVENT_INVALID_REQUEST;
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
        (U1)FWUSH_REQ_SUBTYPE_NA                         /* FWUSH_MAIN_STATE_ROLLBACK (4U) */
    };
    U1 u1_t_event;
    U1 u1_t_current_req_subtype;
    U1 u1_t_expected_subtype;

    u1_t_event                  = (U1)FWUSH_EVENT_NONE;
    u1_t_current_req_subtype    = u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET];
    u1_t_expected_subtype       = (U1)u1_sp_FWUSH_EXPCT_SUBTYPE_PR[u1_s_fwush_state_main];
    
    /* Check whether current subtype is valid (expected, NA, or CANCEL) */
    if(u1_t_current_req_subtype == (U1)FWUSH_REQ_SUBTYPE_CANCEL){

        u1_t_event = (U1)FWUSH_EVENT_CANCEL;
    }
    else if (u1_t_current_req_subtype == u1_t_expected_subtype) {
        u1_t_event = u1_s_FwushCheckMemAccJobEvent();
    }
    else if (u1_t_current_req_subtype != (U1)FWUSH_REQ_SUBTYPE_NA) {
        u1_t_event = (U1)FWUSH_EVENT_INVALID_REQUEST;
    } else {
        /* u1_t_event = (U1)FWUSH_EVENT_NONE; */
    }

    return(u1_t_event);
}

/*===================================================================================================================================*/
/* static void vd_s_FwushExecuteStateSpecificAction(U1 u1_a_event)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_event : Detected event                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushExecuteStateSpecificAction(U1 u1_a_event)
{
    U4 u4_t_adr;
    U1* u1_tp_adr;
    U1 u1_t_read_ok;
    
    /* Execute state-specific handling only on NEW_REQUEST event */
    if(u1_a_event == (U1)FWUSH_EVENT_NEW_REQUEST){
        switch (u1_s_fwush_state_main){
        case (U1)FWUSH_MAIN_STATE_PREP:
            /* PREP: read data & store CRC in context */
            u1_t_read_ok = u1_s_FwushReadData((U2)FWUSH_REQ_D_WORDS, &u4_t_adr);
            if(u1_t_read_ok == (U1)TRUE){
                u1_tp_adr = (U1 *)u4_t_adr;
                u4_s_fwush_prep_data_crc =    (U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET]
                                            | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 1] << (U4)8U)
                                            | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 2] << (U4)16U)
                                            | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 3] << (U4)24U);
                u1_s_fwush_prep_data_ready = (U1)TRUE;
            }
            else{

                u1_s_fwush_prep_data_ready = (U1)FALSE;
            }
            break;
        default:
            break;
        }
    }
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

    u1_t_event = (U1)FWUSH_EVENT_NONE;
    /* Get status from Phase2 unified GetStatus */
    vd_g_FwuMemAccGetStatus(&u1_t_job_type, &u1_t_main_status);
    u1_t_event = u1_s_MapMainStatusToEvent(u1_t_main_status);

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
        case (U1)FWUSH_MAIN_STATE_ROLLBACK:
            /* u1_t_event = u1_s_MapMainStatusToEvent(u1_t_main_status); */
            break;
        default:
            u1_t_event = (U1)FWUSH_EVENT_NONE;
            break;
    }

    return(u1_t_event);
}

/*===================================================================================================================================*/
/* static U1 u1_s_MapMainStatusToEvent(U1 u1_a_main_status)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_main_status : Main status from MemAcc                                                                    */
/*  Return:         U1 : Mapped event                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_MapMainStatusToEvent(U1 u1_a_main_status)
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
    U4 u4_t_adr;
    U4 u4_t_length;
    U4 u4_t_crc;

    U1 u1_t_result;

    if(u1_s_fwush_prep_data_ready == (U1)TRUE){
        u4_t_adr    = (U4)0x1c000U;
        u4_t_length = (U4)0x7A4000U;
        u4_t_crc    = u4_s_fwush_prep_data_crc;
        
        u1_t_result = u1_g_FwuMemAccEraseReq(u4_t_adr, u4_t_length, u4_t_crc);
        if(u1_t_result != (U1)FWUMEMACC_RET_OK){
            u1_s_fwush_abort = (U1)TRUE;
        }

        u1_s_fwush_prep_data_ready = (U1)FALSE;
    }
    else{

        u1_s_fwush_abort = (U1)TRUE;
    }
}
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleRunReq(void)                                                                                       */
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
            u1_s_fwush_abort = (U1)TRUE;
        }
    }
    else{
        u1_s_fwush_abort = (U1)TRUE;
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
        u1_s_fwush_abort = (U1)TRUE;
    }
}
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleRollbackReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      void                                                                                                             */
/*  Return:         void                                                                                                             */
/*===================================================================================================================================*/
static void vd_s_FwushHandleRollbackReq(void)
{
}
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleValidateReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleValidateReq(void)
{
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
    vd_s_FwushMakeResData((U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_ACK_OK);
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
    vd_s_FwushMakeResData((U1)FWUSH_MAIN_STATE_RUN, (U1)FWUSH_ACK_OK);
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
    /* Send ACK */
    vd_s_FwushMakeResData((U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_ACK_OK);
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
    /* Send ACK */
    vd_s_FwushMakeResData((U1)FWUSH_MAIN_STATE_ACT, (U1)FWUSH_ACK_OK);
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
/* static void vd_s_FwushHandleAbort(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleAbort(void)
{
    /* set error flag */
    u1_s_fwush_abort = (U1)TRUE;
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
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleCancelDuringJob(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleCancelDuringJob(void)
{
    /* Initialize FwuMemAcc (job abort) */
    vd_g_FwuMemAccInit();
    
    /* Return to PREP_WAITING (set in table) */
    u2_s_fwush_run_ofst                      = (U2)0xFFFFU;
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
/* static U1 u1_s_FwushReadData(U2 u2_a_length, U4* u4_ap_reqadr)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2 u2_a_length : Read length (words)                                                                             */
/*                  U4* u4_ap_reqadr : Pointer to store read address                                                                 */
/*  Return:         U1 : TRUE if data read successfully, FALSE otherwise                                                             */
/*===================================================================================================================================*/
static U1 u1_s_FwushReadData(U2 u2_a_length, U4* u4_ap_reqadr)
{
    U1  u1_t_read_ok;
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;

    u1_t_read_ok = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_FWUPXREQ_D, u4_ap_reqadr, (U2)FWUSH_REQ_D_WORDS);

    if((u1_t_read_ok != (U1)IVDSH_NO_REA) &&
       (u4_ap_reqadr != vdp_PTR_NA      )){
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Data Generation                                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* static void vd_s_FwushMakeResData(U1 u1_a_state, U1 u1_a_response)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_state : Response state                                                                                   */
/*                  U1 u1_a_response : Response code (FWUSH_ACK_OK or FWUSH_ACK_NG)                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushMakeResData(U1 u1_a_state, U1 u1_a_response)
{
    static const U1 u1_sp_FWUSH_EXPCT_SUBTYPE[FWUSH_MAIN_STATE_MAX] =
    {
        (U1)FWUSH_RESP_SUBTYPE_PREP,                      /* FWUSH_MAIN_STATE_PREP     (0U) */
        (U1)FWUSH_RESP_SUBTYPE_RUN,                       /* FWUSH_MAIN_STATE_RUN      (1U) */
        (U1)FWUSH_RESP_SUBTYPE_VERI,                      /* FWUSH_MAIN_STATE_VERI     (2U) */
        (U1)FWUSH_RESP_SUBTYPE_ACT,                       /* FWUSH_MAIN_STATE_ACT      (3U) */
        (U1)FWUSH_RESP_SUBTYPE_NA                         /* FWUSH_MAIN_STATE_ROLLBACK (4U) */
    };
    U4  u4_tp_res_data[FWUSH_RES_WORDS];

    vd_g_MemfillU4(&u4_tp_res_data[0], (U4)0U, (U4)FWUSH_RES_WORDS);

    u4_tp_res_data[0] = (U4)(u1_sp_FWUSH_EXPCT_SUBTYPE[u1_a_state] | ((U4)u1_a_response << (U1)8U) | ((U4)0x01U << (U1)16U)
                      | (U4)((u2_s_fwush_run_ofst & (U2)0xFF00U) << (U1)16U));
    u4_tp_res_data[1] = (U4)((u2_s_fwush_run_ofst & (U2)0x00FFU)) | ((U4)0x04U << (U1)8U) | ((U4)0x00U << (U1)16U)
                      | ((U4)u1_s_fwupx_res_seqcnt << (U1)24U);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_res_data[0], (U2)FWUSH_RES_WORDS);

    if(u1_s_fwupx_res_seqcnt < (U1)0xFFU){
        u1_s_fwupx_res_seqcnt++;
    }
    else{
        u1_s_fwupx_res_seqcnt = (U1)0U;
    }
}
/*===================================================================================================================================*/
/* static U1 u1_s_FwushMakePrepData(U4 * u4_ap_adr, U4 * u4_ap_length, U4 * u4_ap_crc)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U4 * u4_ap_adr    : Pointer to store address                                                                     */
/*                  U4 * u4_ap_length  : Pointer to store length                                                                     */
/*                  U4 * u4_ap_crc     : Pointer to store CRC                                                                        */
/*  Return:         U1 : TRUE if data created successfully, FALSE otherwise                                                          */
/*===================================================================================================================================*/
static U1 u1_s_FwushMakePrepData(U4 * u4_ap_adr, U4 * u4_ap_length, U4 * u4_ap_crc)
{
    U4   u4_t_adr;
    U1 * u1_tp_adr;
    U1   u1_t_ret;

    u1_t_ret  = u1_s_FwushReadData((U2)FWUSH_REQ_D_WORDS, &u4_t_adr);
    u1_tp_adr = (U1 *)u4_t_adr;

    if(u1_t_ret == (U1)TRUE){
        *u4_ap_adr    = (U4)0x1c000U;
        *u4_ap_length = (U4)0x7A4000U;
        *u4_ap_crc    = (U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET]
                      | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 1] << (U4)8U)
                      | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 2] << (U4)16U)
                      | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 3] << (U4)24U);
    }

    return(u1_t_ret);
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

    u1_t_ret = u1_s_FwushReadData((U2)FWUSH_REQ_D_WORDS, u4_ap_adr);
    *u2_ap_ofst = ((U2)u1_sp_fwush_header[FWUSH_REQ_RUN_BLKOFS_OFFSET + 1]) | 
                  ((U2)u1_sp_fwush_header[FWUSH_REQ_RUN_BLKOFS_OFFSET] << (U2)8U);
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/* static void vd_g_FwushAbort(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_g_FwushAbort(void)
{
    /* Initialize state variables */
    u1_s_fwush_state_main       = (U1)FWUSH_MAIN_STATE_PREP;
    u1_s_fwush_state_sub        = (U1)FWUSH_SUB_STATE_WAITING;
    u1_s_fwush_abort            = (U1)FALSE;
    u1_s_fwush_prep_data_ready  = (U1)FALSE;
    u4_s_fwush_prep_data_crc    = (U4)0U;
    u2_s_fwush_run_ofst     = (U2)0xFFFFU;
    
    /* Clear header buffer */
    vd_g_MemfillU1(&u1_sp_fwush_header[0], (U1)0U, (U4)FWUSH_REQ_H_SIZE);
    
    /* Initialize FwuMemAcc */
    vd_g_FwuMemAccInit();
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
