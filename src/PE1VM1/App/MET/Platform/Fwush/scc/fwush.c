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

/* State transition entry */
typedef struct {
    U1 u1_next_main_state;     /* Next main state */
    U1 u1_next_sub_state;      /* Next sub state */
    void (*fp_handler_func)(void);             /* Handler function */
} ST_FWUSH_TRANSITION_ENTRY;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* Current main and sub states */
static U1 u1_s_main_state;           /* Current main state */
static U1 u1_s_sub_state;            /* Current sub state */

/* Request information */
static U1 u1_s_previous_subtype;                    /* Previous request subtype */

/* Error management */
static U1 u1_s_abort_active;                        /* Abort-in-progress flag (alternative to ERROR state) */

/* PREP state data */
static U1 u1_s_prep_data_ready;                     /* Data ready flag */
static U4 u4_s_prep_data_crc;                       /* Data CRC */

/* RUN state data */
static U2 u2_s_run_offset_prev;                     /* Previous offset */

/* Request header buffer */
static U1 u1_sp_fwush_header[FWUSH_REQ_H_SIZE];

/* Rollback management (planned to externalize in Phase3) */
static U1 u1_s_rollback_trigger_flag;   /* Rollback trigger flag */
static U1 u1_s_rollback_in_progress;    /* Rollback in-progress flag */

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
static void vd_s_FwushStartJob(void);
static void vd_s_FwushMonitorJob(void);
static void vd_s_FwushHandleJobSuccess(void);
static void vd_s_FwushHandleJobProgress(void);
static void vd_s_FwushHandleError(void);

/* CANCEL handlers */
static void vd_s_FwushHandleCancel(void);
static void vd_s_FwushHandleCancelDuringJob(void);
static void vd_s_FwushHandleCancelRollback(void);

/* Data generation */
static void vd_s_FwushMakeResData(U1 u1_a_subtype, U1 u1_a_response);
static U1 u1_s_FwushMakePrepData(U4 * u4_ap_adr, U4 * u4_ap_length, U4 * u4_ap_crc);
static U1 u1_s_FwushMakeRunData(U4 * u4_ap_adr, U2 * u2_ap_ofst);

/* Forward declarations (used by the table) */
static void vd_s_FwushStartJob(void);
static void vd_s_FwushMonitorJob(void);
static void vd_s_FwushHandleJobSuccess(void);
static void vd_s_FwushHandleJobProgress(void);
static void vd_s_FwushHandleError(void);
static void vd_s_FwushHandleCancel(void);
static void vd_s_FwushHandleCancelDuringJob(void);
static void vd_s_FwushHandleRollback(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* State transition table: [main state][sub state][event] Size: [5 main states][2 sub states][8 events] = 80 entries (38% reduction from old 128 entries) */
static const ST_FWUSH_TRANSITION_ENTRY stp_sp3_ST_TABLE[FWUSH_MAIN_STATE_MAX]
                                                       [FWUSH_SUB_STATE_MAX]
                                                       [FWUSH_EVENT_MAX] = {
    /*************************************************************************************************************/
    /* FWUSH_MAIN_STATE_PREP                                                                                     */
    /*************************************************************************************************************/
    {
        /* FWUSH_SUB_STATE_WAITING                                                                               */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushStartJob},              /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleError},           /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleError},           /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA}                        /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushMonitorJob},            /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleJobSuccess},      /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleError},           /* FWUSH_EVENT_MEMACC_ERROR    */
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
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushStartJob},             /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleError},          /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleError},          /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleCancel},         /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                     /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                     /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA}                      /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushMonitorJob},            /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleError},           /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancelDuringJob}, /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleJobSuccess},      /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleJobSuccess},      /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA}                        /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        }
    },
    
    /*************************************************************************************************************/
    /* FWUSH_MAIN_STATE_VERI                                                                                     */
    /*************************************************************************************************************/
    {
        /* FWUSH_SUB_STATE_WAITING                                                                               */
        {
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushStartJob},              /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleError},           /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleError},           /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancel},          /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA}                        /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        }, 
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushMonitorJob},            /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleJobSuccess},      /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleError},           /* FWUSH_EVENT_MEMACC_ERROR    */
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
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushStartJob},              /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleError},           /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleError},           /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancel},          /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA}                        /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushMonitorJob},            /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleJobSuccess},      /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleJobProgress},     /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_ACT,       (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleError},           /* FWUSH_EVENT_MEMACC_ERROR    */
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
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushStartJob},           /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleError},        /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                    /* FWUSH_EVENT_MEMACC_RUN_COMPLETE */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA}                     /* FWUSH_EVENT_MEMACC_ACT_ROLLBACK */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                    /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushMonitorJob},         /* FWUSH_EVENT_SAME_REQUEST    */
            {(U1)FWUSH_MAIN_STATE_PREP,     (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleJobSuccess},   /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleJobProgress},  /* FWUSH_EVENT_MEMACC_PROGRESS */
            {(U1)FWUSH_MAIN_STATE_ROLLBACK, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleError},        /* FWUSH_EVENT_MEMACC_ERROR    */
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
    u1_s_main_state = (U1)FWUSH_MAIN_STATE_PREP;
    u1_s_sub_state = (U1)FWUSH_SUB_STATE_WAITING;
    u1_s_previous_subtype = (U1)FWUSH_REQ_SUBTYPE_NA;
    u1_s_abort_active = (U1)FALSE;
    u1_s_prep_data_ready = (U1)FALSE;
    u4_s_prep_data_crc = (U4)0U;
    u2_s_run_offset_prev = (U2)0xFFFFU;
    
    /* Initialize rollback management */
    u1_s_rollback_trigger_flag = (U1)FALSE;
    u1_s_rollback_in_progress = (U1)FALSE;
    
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
    U1 u1_t_event;
    const ST_FWUSH_TRANSITION_ENTRY* stp_t_TRANSITION;
    
    /* 1. Event detection (reads header internally) */
    u1_t_event = u1_s_FwushDetectEvent();
    
    /* 2. Consult state transition table */
    stp_t_TRANSITION = &stp_sp3_ST_TABLE[u1_s_main_state]
                                        [u1_s_sub_state]
                                        [u1_t_event];
    
    /* 3. Execute state transition */
    if (stp_t_TRANSITION->fp_handler_func != vdp_PTR_NA) {
        stp_t_TRANSITION->fp_handler_func();
    }
    
    /* 4. Update state */
    u1_s_main_state = stp_t_TRANSITION->u1_next_main_state;
    u1_s_sub_state = stp_t_TRANSITION->u1_next_sub_state;
    
    /* 5. Update request subtype */
    u1_s_previous_subtype = u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET];
    
    /* 6. Send delivery ACK (future extension point) */
    /* TODO Phase3: optionally send ACK at event detection time */
    /* if (u1_t_event == FWUSH_EVENT_NEW_REQUEST) { vd_s_FwushSendRequestAck(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET]); } */

    /* 7. Error handling */
    if (u1_s_abort_active != (U1)FALSE) {
        vd_s_FwushMakeResData(u1_s_previous_subtype, (U1)FWUSH_ACK_NG);
        vd_g_FwushInit();
    }
    
    /* 8. Execute MemAcc task */
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

    /* Branch processing according to substate */
    if (u1_s_sub_state == (U1)FWUSH_SUB_STATE_WAITING) {
        /* WAITING: read header -> determine request -> state-specific handling */
        u1_t_head_ok = u1_s_FwushReadHeader(&u1_sp_fwush_header[0]);
        if (u1_t_head_ok == (U1)FALSE) {
            /* Header read failed -> no event (only run MemAcc task) */
            u1_t_event = (U1)FWUSH_EVENT_NONE;
        } else {
            u1_t_event = u1_s_FwushDetectEventForWaiting();

            /* Execute state-specific actions (PREP: data read, etc.) */
            vd_s_FwushExecuteStateSpecificAction(u1_t_event);
        }

    } else if (u1_s_sub_state == (U1)FWUSH_SUB_STATE_PROCESSING) {
        /* PROCESSING: Monitor MemAcc job status */
        u1_t_event = u1_s_FwushDetectEventForProcessing();

    } else {
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
    U1 u1_t_event;
    U1 u1_t_current_req_subtype;
    U1 u1_t_expected_subtype;
    U1 u1_t_bad_state;
    
    /* Expected subtype for main state */
    u1_t_current_req_subtype = u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET];
    u1_t_event = (U1)FWUSH_EVENT_NONE;
    u1_t_bad_state = (U1)FALSE;
    switch (u1_s_main_state) {
        case (U1)FWUSH_MAIN_STATE_PREP:
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_PREP;
            break;
        case (U1)FWUSH_MAIN_STATE_RUN:
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_RUN;
            break;
        case (U1)FWUSH_MAIN_STATE_VERI:
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_VERI;
            break;
        case (U1)FWUSH_MAIN_STATE_ACT:
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_ACT;
            break;
        case (U1)FWUSH_MAIN_STATE_ROLLBACK:
            /* No requests accepted in ROLLBACK state */
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_NA;
            break;
        default:
            u1_t_bad_state = (U1)TRUE;
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_NA;
            break;
    }

    if (u1_t_bad_state == (U1)TRUE) {
        u1_t_event = (U1)FWUSH_EVENT_INVALID_REQUEST;
    } else {
        /* Detect request change */
        if (u1_t_current_req_subtype != u1_s_previous_subtype) {
            if (u1_t_current_req_subtype == u1_t_expected_subtype) {
                u1_t_event = (U1)FWUSH_EVENT_NEW_REQUEST;
            } else if (u1_t_current_req_subtype == (U1)FWUSH_REQ_SUBTYPE_CANCEL) {
                u1_t_event = (U1)FWUSH_EVENT_CANCEL;
            } else if (u1_t_current_req_subtype != (U1)FWUSH_REQ_SUBTYPE_NA) {
                u1_t_event = (U1)FWUSH_EVENT_INVALID_REQUEST;
            } else {
                /* Do Nothing */
            }
        } else if (u1_t_current_req_subtype == u1_t_expected_subtype) {
            u1_t_event = (U1)FWUSH_EVENT_SAME_REQUEST;
        } else if (u1_t_current_req_subtype == (U1)FWUSH_REQ_SUBTYPE_CANCEL) {
            u1_t_event = (U1)FWUSH_EVENT_CANCEL;
        } else {
            /* Do Nothing */
        }
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
    U1 u1_t_event;
    U1 u1_t_current_req_subtype;
    U1 u1_t_expected_subtype;

    u1_t_event = (U1)FWUSH_EVENT_NONE;
    u1_t_current_req_subtype = u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET];

    /* Expected subtype for current main state */
    switch (u1_s_main_state) {
        case (U1)FWUSH_MAIN_STATE_PREP:
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_PREP;
            break;
        case (U1)FWUSH_MAIN_STATE_RUN:
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_RUN;
            break;
        case (U1)FWUSH_MAIN_STATE_VERI:
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_VERI;
            break;
        case (U1)FWUSH_MAIN_STATE_ACT:
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_ACT;
            break;
        case (U1)FWUSH_MAIN_STATE_ROLLBACK:
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_NA;
            break;
        default:
            u1_t_expected_subtype = (U1)FWUSH_REQ_SUBTYPE_NA;
            break;
    }
    
    /* Check whether current subtype is valid (expected, NA, or CANCEL) */
    if (u1_t_current_req_subtype == (U1)FWUSH_REQ_SUBTYPE_CANCEL) {
        /* CANCEL request */
        u1_t_event = (U1)FWUSH_EVENT_CANCEL;
    } else if (u1_t_current_req_subtype == u1_t_expected_subtype) {
        /* Continue normally or no request -> Monitor MemAcc job status */
        u1_t_event = u1_s_FwushCheckMemAccJobEvent();
    } else if (u1_t_current_req_subtype != (U1)FWUSH_REQ_SUBTYPE_NA) {
        /* Invalid request during processing (different subtype) -> Error */
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
    if (u1_a_event == (U1)FWUSH_EVENT_NEW_REQUEST) {
        switch (u1_s_main_state) {
        case (U1)FWUSH_MAIN_STATE_PREP:
            /* PREP: read data & store CRC in context */
            u1_t_read_ok = u1_s_FwushReadData((U2)FWUSH_REQ_D_WORDS, &u4_t_adr);
            if (u1_t_read_ok == (U1)TRUE) {
                u1_tp_adr = (U1 *)u4_t_adr;
                u4_s_prep_data_crc = 
                    (U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET]
                    | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 1] << (U4)8U)
                    | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 2] << (U4)16U)
                    | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 3] << (U4)24U);
                u1_s_prep_data_ready = (U1)TRUE;
            } else {
                u1_s_prep_data_ready = (U1)FALSE;
            }
            break;
            
        case (U1)FWUSH_MAIN_STATE_RUN:
            /* RUN: no special action (StartJob reads data immediately) */
            break;
            
        case (U1)FWUSH_MAIN_STATE_VERI:
            /* VERI: no special action */
            break;
            
        case (U1)FWUSH_MAIN_STATE_ACT:
            /* ACT: no special action */
            /* TODO Phase3 extension: hardware checks before ACT start */
            break;
            
        case (U1)FWUSH_MAIN_STATE_ROLLBACK:
            /* ROLLBACK: no special action */
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

    /* Flatten: map MainStatus directly to event */
    switch (u1_s_main_state) {
        case (U1)FWUSH_MAIN_STATE_PREP:
            u1_t_event = u1_s_MapMainStatusToEvent(u1_t_main_status);
            break;
        case (U1)FWUSH_MAIN_STATE_RUN:
            u1_t_event = u1_s_MapMainStatusToEvent(u1_t_main_status);
            if (u1_t_event == (U1)FWUSH_EVENT_MEMACC_SUCCESS) {
                u1_t_update_status = u1_g_FwuMemAccGetUpdateStatus();
                if (u1_t_update_status == (U1)FWUMEMACC_UPDT_STS_ALL_COMP) {
                    /* Handle all components updated successfully */
                    u1_t_event = (U1)FWUSH_EVENT_MEMACC_RUN_COMPLETE;
                } else if (u1_t_update_status == (U1)FWUMEMACC_UPDT_STS_IN_PROGRESS) {
                    /* Handle partial update */
                    u1_t_event = (U1)FWUSH_EVENT_MEMACC_RUN_PARTIAL;
                } else {
                    /* FWUMEMACC_UPDT_STS_IDLE (Do Nothing) */
                }
            }
            break;
        case (U1)FWUSH_MAIN_STATE_VERI:
            u1_t_event = (U1)FWUSH_EVENT_MEMACC_SUCCESS; /* treated as immediate success */
            break;
        case (U1)FWUSH_MAIN_STATE_ACT:
            u1_t_event = u1_s_MapMainStatusToEvent(u1_t_main_status);
            if (u1_t_event == (U1)FWUSH_EVENT_MEMACC_SUCCESS) {
                if (u1_s_rollback_trigger_flag == (U1)TRUE) {
                    /* If rollback is triggered, change event to ROLLBACK */
                    u1_t_event = (U1)FWUSH_EVENT_MEMACC_ACT_ROLLBACK;
                }
            }
            break;
        case (U1)FWUSH_MAIN_STATE_ROLLBACK:
            /* Temporary: reuse MainStatus */
            u1_t_event = u1_s_MapMainStatusToEvent(u1_t_main_status);
            break;
        default:
            u1_t_event = (U1)FWUSH_EVENT_NONE;
            break;
    }

    return(u1_t_event);
}

/* Helper: map Phase2 MainStatus to event (unified) */
/*===================================================================================================================================*/
/* static U1 u1_s_MapMainStatusToEvent(U1 u1_a_main_status)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_main_status : Main status from MemAcc                                                                    */
/*  Return:         U1 : Mapped event                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_MapMainStatusToEvent(U1 u1_a_main_status)
{
    U1 u1_t_event = (U1)FWUSH_EVENT_NONE;
    switch (u1_a_main_status) {
        case (U1)FWUMEMACC_MAIN_STATUS_IDLE:
            u1_t_event = (U1)FWUSH_EVENT_NONE;
            break;
        case (U1)FWUMEMACC_MAIN_STATUS_REQUESTED:
        case (U1)FWUMEMACC_MAIN_STATUS_ACTIVE:
            u1_t_event = (U1)FWUSH_EVENT_MEMACC_PROGRESS;
            break;
        case (U1)FWUMEMACC_MAIN_STATUS_COMPLETED:
            u1_t_event = (U1)FWUSH_EVENT_MEMACC_SUCCESS;
            break;
        case (U1)FWUMEMACC_MAIN_STATUS_ERROR:
            u1_t_event = (U1)FWUSH_EVENT_MEMACC_ERROR;
            break;
        default:
            u1_t_event = (U1)FWUSH_EVENT_NONE;
            break;
    }
    return(u1_t_event);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  State Handlers                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* static void vd_s_FwushStartJob(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushStartJob(void)
{
    U1 u1_t_read_ok;
    U4 u4_t_adr;
    U4 u4_t_length;
    U4 u4_t_crc;
    U2 u2_t_ofst;
    U1 u1_t_result;
    
    switch (u1_s_main_state) {
        case (U1)FWUSH_MAIN_STATE_PREP:
            /* PREP: start job using data saved during WAITING */
            if (u1_s_prep_data_ready == (U1)TRUE) {
                u4_t_adr = (U4)0x1c000U;
                u4_t_length = (U4)0x7A4000U;
                u4_t_crc = u4_s_prep_data_crc;
                
                u1_t_result = u1_g_FwuMemAccEraseReq(u4_t_adr, u4_t_length, u4_t_crc);
                if (u1_t_result != (U1)FWUMEMACC_RET_OK) {
                    /* Job start failed */
                    u1_s_abort_active = (U1)TRUE;
                }
                
                /* Clear flag after using data */
                u1_s_prep_data_ready = (U1)FALSE;
            } else {
                /* Data preparation failed */
                u1_s_abort_active = (U1)TRUE;
            }
            break;
            
        case (U1)FWUSH_MAIN_STATE_RUN:
            /* Create RUN data and start job */
            u1_t_read_ok = u1_s_FwushMakeRunData(&u4_t_adr, &u2_t_ofst);
            if (u2_t_ofst != u2_s_run_offset_prev) {
                if (u1_t_read_ok == (U1)TRUE) {
                    u1_t_result = u1_g_FwuMemAccUpdateReq(u2_t_ofst, (const U4 *)u4_t_adr);
                    if (u1_t_result != (U1)FWUMEMACC_RET_OK) {
                        /* job start failed */
                        u1_s_abort_active = (U1)TRUE;
                    }
                } else {
                    u1_s_abort_active = (U1)TRUE;
                }
            } else {
                /* No offset change, mark request as NA */
                u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = (U1)FWUSH_REQ_SUBTYPE_NA;
            }
            u2_s_run_offset_prev = u2_t_ofst;
            break;
            
        case (U1)FWUSH_MAIN_STATE_VERI:
            /* VERI completes immediately (Step1 specification) */
            break;
            
        case (U1)FWUSH_MAIN_STATE_ACT:
            /* Start ACT job */
            {
                u1_t_result = u1_g_FwuMemAccSwitchReq();
                if (u1_t_result != (U1)FWUMEMACC_RET_OK) {
                    /* job start failed */
                    u1_s_abort_active = (U1)TRUE;
                }
            }
            break;
            
        case (U1)FWUSH_MAIN_STATE_ROLLBACK:
            /* Call rollback handler */
            vd_s_FwushHandleRollback();
            break;
            
        default:
            break;
    }
}

/*===================================================================================================================================*/
/* static void vd_s_FwushMonitorJob(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushMonitorJob(void)
{
    /* No special processing in current implementation */
    /* MemAcc status monitored by event detection */
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleJobSuccess(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleJobSuccess(void)
{
    U1 u1_t_update_status;
    
    /* State transition already applied by table */
    /* Send ACK */
    vd_s_FwushMakeResData(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET], (U1)FWUSH_ACK_OK);
    
    /* When ROLLBACK completes: system reset -> PREP_WAITING */
    if (u1_s_main_state == (U1)FWUSH_MAIN_STATE_PREP &&
        u1_s_rollback_in_progress != (U1)FALSE) {
        /* Initialization after rollback completion */
        vd_g_FwushInit();
    }
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
/* static void vd_s_FwushHandleError(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleError(void)
{
    /* set error flag */
    u1_s_abort_active = (U1)TRUE;
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
    u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = (U1)FWUSH_REQ_SUBTYPE_NA;
    u1_s_previous_subtype = (U1)FWUSH_REQ_SUBTYPE_NA;
    u2_s_run_offset_prev = (U2)0xFFFFU;
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleRollback(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleRollback(void)
{
    /* TODO: Implement in Phase 3 and later. Planned behavior: 1. Request area switch for rollback via MemAcc_HwSpecificService() - Service ID: MEMACC_SRV_ID_SWITCHVALIDAREA or a dedicated rollback ID, 2. Start rollback as an asynchronous job (e.g. vd_g_FwuMemAccRollbackReqTrg()), 3. Set memacc_job_active flag, 4. Set rollback_in_progress flag. On completion: ROLLBACK_PROCESSING -> (MEMACC_SUCCESS) -> PREP_WAITING. System reset handled in HandleJobSuccess. Notes: Rollback may run asynchronously; state management must be careful. Error handling is required on rollback failure. */
    
    /* Temporary implementation: set rollback in-progress flag */
    u1_s_rollback_in_progress = (U1)TRUE;

    /* Initialize FwuMemAcc (Phase3 will call a rollback-specific trigger) */
    vd_g_FwuMemAccInit();

    /* Reset internal state */
    u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = (U1)FWUSH_REQ_SUBTYPE_NA;
    u1_s_previous_subtype = (U1)FWUSH_REQ_SUBTYPE_NA;
    u2_s_run_offset_prev = (U2)0xFFFFU;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Request Processing                                                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* u1_s_FwushReqChk removed callers now invoke u1_s_FwushReadHeader directly */
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
    /* get request data */
    u1_t_read_ok = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_FWUPXREQ_D, u4_ap_reqadr, (U2)FWUSH_REQ_D_WORDS);
    if((u1_t_read_ok != (U1)IVDSH_NO_REA) && (u4_ap_reqadr != vdp_PTR_NA)){
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
/*  Arguments:      U1 u1_a_subtype : Request subtype                                                                                */
/*                  U1 u1_a_response : Response code (FWUSH_ACK_OK or FWUSH_ACK_NG)                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushMakeResData(U1 u1_a_subtype, U1 u1_a_response)
{
    U4  u4_tp_res_data[FWUSH_RES_WORDS];

    vd_g_MemfillU4(&u4_tp_res_data[0], (U4)0U, (U4)FWUSH_RES_WORDS);

    switch (u1_a_subtype)
    {
    case (U1)FWUSH_REQ_SUBTYPE_PREP:
        u4_tp_res_data[0] = (U4)0x07U | ((U4)u1_a_response << (U1)8U) | ((U4)0x01U << (U1)16U);
        u4_tp_res_data[1] = (U4)0x00U;
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_res_data[0], (U2)FWUSH_RES_WORDS);
        break;
        
    case (U1)FWUSH_REQ_SUBTYPE_RUN:
        u4_tp_res_data[0] = (U4)(0x17U | ((U4)u1_a_response << (U1)8U) | ((U4)0x01U << (U1)16U)
                          | (U4)((u2_s_run_offset_prev & (U2)0xFF00U) << (U1)16U));
        u4_tp_res_data[1] = (U4)((u2_s_run_offset_prev & (U2)0x00FFU)) | ((U4)0x04U << (U1)8U) | ((U4)0x00U << (U1)16U);
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_res_data[0], (U2)FWUSH_RES_WORDS);
        break;
        
    case (U1)FWUSH_REQ_SUBTYPE_VERI:
        u4_tp_res_data[0] = (U4)0x19U | ((U4)u1_a_response << (U1)8U) | ((U4)0x01U << (U1)16U);
        u4_tp_res_data[1] = (U4)0x00U;
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_res_data[0], (U2)FWUSH_RES_WORDS);
        break;
        
    case (U1)FWUSH_REQ_SUBTYPE_ACT:
        u4_tp_res_data[0] = (U4)0x38U | ((U4)u1_a_response << (U1)8U);
        u4_tp_res_data[1] = (U4)0x00U;
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_res_data[0], (U2)FWUSH_RES_WORDS);
        break;
        
    default:
        break;
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

    u1_t_ret = u1_s_FwushReadData((U2)FWUSH_REQ_D_WORDS, &u4_t_adr);
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
