/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* FW Update State Handler - State Machine (Handlers & Transition Table)                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUSH_STM_C_MAJOR                   (2U)
#define FWUSH_STM_C_MINOR                   (0U)
#define FWUSH_STM_C_PATCH                   (0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "fwush_internal.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* State handlers */
static void vd_s_FwushHandleEraseReq(void);
static void vd_s_FwushHandleRunReq(void);
static void vd_s_FwushHandleVerifyReq(void);
static void vd_s_FwushHandleActivateReq(void);
static void vd_s_FwushHandleValidateReq(void);
static void vd_s_FwushHandleFinalizeReq(void);
static void vd_s_FwushHandleRollbackReq(void);

static void vd_s_FwushHandleEraseSuccess(void);
static void vd_s_FwushHandleRunSuccess(void);
static void vd_s_FwushHandleVerifySuccess(void);
static void vd_s_FwushHandleActivateSuccess(void);
static void vd_s_FwushHandleValidateSuccess(void);
static void vd_s_FwushHandleFinalizeSuccess(void);
static void vd_s_FwushHandleRollbackSuccess(void);

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

/* Request-to-response subtype mapping helper */
static U1 u1_s_FwushMapReqToResSubtype(U1 u1_a_req_subtype);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* State transition table: [main state][sub state][event] Size: [6 main states][2 sub states][14 events] = 168 entries */
const ST_FWUSH_TRANSITION_ENTRY stp_gp3_FWUSH_STM[FWUSH_MAIN_STATE_MAX]
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
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleInvalidReq},     /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleCancel},         /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_ACT,   (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_FIN,   (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                      /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleFinalizeReq}     /* FWUSH_EVENT_FIN_ACCEPT      */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleEraseSuccess},    /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleEraseAbort},      /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleProcessing},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
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
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleInvalidReq},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancel},          /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleEraseReq},        /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleFinalizeReq}      /* FWUSH_EVENT_FIN_ACCEPT      */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleRunSuccess},      /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleRunAbort},        /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleProcessing},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleRunSuccess},      /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_RUN,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
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
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleInvalidReq},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancel},          /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleEraseReq},        /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleFinalizeReq}      /* FWUSH_EVENT_FIN_ACCEPT      */
        }, 
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleVerifySuccess},   /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleVerifyAbort},     /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleProcessing},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_VERI, (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
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
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleInvalidReq},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleCancel},          /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleRollbackReq},     /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleEraseReq},        /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleActivateSuccess}, /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleFinalizeReq}      /* FWUSH_EVENT_FIN_ACCEPT      */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleActivateSuccess}, /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleActivateAbort},   /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  &vd_s_FwushHandleProcessing},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_ACT,  (U1)FWUSH_SUB_STATE_PROCESSING,  vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
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
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleInvalidReq},      /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_FIN,   (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleRollbackReq},     /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleActivateSuccess}, /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,     &vd_s_FwushHandleFinalizeReq}      /* FWUSH_EVENT_FIN_ACCEPT      */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_FIN,   (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleValidateSuccess}, /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_PREP,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleValidateAbort},   /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_VALID, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                       /* FWUSH_EVENT_RESUME_ACT      */
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
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleInvalidReq},       /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleRollbackReq},      /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleValidateSuccess},  /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_FIN,  (U1)FWUSH_SUB_STATE_WAITING,    vdp_PTR_NA},                        /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_PREP, (U1)FWUSH_SUB_STATE_WAITING,   &vd_s_FwushHandleFinalizeReq}        /* FWUSH_EVENT_FIN_ACCEPT      */
        },
        /* FWUSH_SUB_STATE_PROCESSING                                                                            */
        {
            /* u1_next_main_state             u1_next_sub_state               fp_handler_func                     */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_NONE            */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_NEW_REQUEST     */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_WAITING,    &vd_s_FwushHandleRollbackSuccess},   /* FWUSH_EVENT_MEMACC_SUCCESS  */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_WAITING   , &vd_s_FwushHandleRollbackAbort},     /* FWUSH_EVENT_MEMACC_ERROR    */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleProcessing},        /* FWUSH_EVENT_INVALID_REQUEST */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, &vd_s_FwushHandleProcessing},        /* FWUSH_EVENT_CANCEL          */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_MEMACC_RUN_PARTIAL */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_ROLLBACK        */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_SWITCH_DETECT   */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_PREP_ACCEPT     */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_RES_OK          */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_RESUME_ACT      */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA},                         /* FWUSH_EVENT_RESUME_FIN      */
            {(U1)FWUSH_MAIN_STATE_FIN, (U1)FWUSH_SUB_STATE_PROCESSING, vdp_PTR_NA}                          /* FWUSH_EVENT_FIN_ACCEPT      */
        }
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions - State Handlers                                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* static void vd_s_FwushHandleEraseReq(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      void                                                                                                             */
/*  Return:         void                                                                                                             */
/*===================================================================================================================================*/
static void vd_s_FwushHandleEraseReq(void)
{
    U1 u1_t_ack;
    U1 *u1_tp_adr;
    U4 u4_t_adr;

    U1 u1_t_result;

    /* read data & store CRC in context */
    u1_t_ack = u1_s_FwushCheckPrepTarget(&u4_t_adr);
    if(u1_t_ack == (U1)FWUSH_ACK_OK){
        u1_tp_adr = (U1 *)u4_t_adr;
        u4_g_fwush_prep_data_crc =    (U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET]
                                    | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 1] << (U4)8U)
                                    | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 2] << (U4)16U)
                                    | ((U4)u1_tp_adr[FWUSH_REQ_PREP_DATA_CRC_OFFSET + 3] << (U4)24U);
        vd_g_FwushResetSeqProgress();
        vd_g_FwushUpdateFswaStat();

        u1_t_result = u1_g_FwuMemAccEraseReq(u1_gp_fwush_header[FWUSH_REQ_PREP_CUR_TARGET_OFFSET], u4_g_fwush_prep_data_crc);
        if(u1_t_result != (U1)FWUMEMACC_RET_OK){
            u1_g_fwush_abort     = (U1)TRUE;
            u1_g_fwush_error_log = u1_g_FwushMapMemAccErrorToAck();
        }
        else if(u2_g_fwush_veri_stat == (U2)FWUSH_VERI_LB_STAT_INIT){
            u1_g_fwush_veri_target = u1_gp_fwush_header[FWUSH_REQ_PREP_CUR_TARGET_OFFSET];
            vd_g_FwushUpdateVeriStat(u1_gp_fwush_header[FWUSH_REQ_PREP_ALL_TARGET_OFFSET], (U1)FWUSH_VERI_LB_NONE);
        }else{
            u1_g_fwush_veri_target = u1_gp_fwush_header[FWUSH_REQ_PREP_CUR_TARGET_OFFSET];
        }
    }
    else{
        u1_g_fwush_abort     = (U1)TRUE;
        u1_g_fwush_error_log = (U1)u1_t_ack;
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

    u1_t_read_ok = u1_g_FwushMakeRunData(&u4_t_adr, &u2_g_fwush_run_ofst);
    if(u1_t_read_ok == (U1)TRUE){
        u1_t_result = u1_g_FwuMemAccUpdateReq(u2_g_fwush_run_ofst, (const U4 *)u4_t_adr);
        if(u1_t_result != (U1)FWUMEMACC_RET_OK){
            u1_g_fwush_abort     = (U1)TRUE;
            u1_g_fwush_error_log = u1_g_FwushMapMemAccErrorToAck();
        }
    }
    else{
        u1_g_fwush_abort     = (U1)TRUE;
        u1_g_fwush_error_log = (U1)FWUSH_ACK_PRECONDITION_ERR;
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
        u1_g_fwush_abort     = (U1)TRUE;
        u1_g_fwush_error_log = u1_g_FwushMapMemAccErrorToAck();
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
        u1_g_fwush_abort = (U1)FALSE;
    }
    else{
        /* Validate NG */
        u1_g_fwush_abort     = (U1)TRUE;
        u1_g_fwush_error_log = (U1)FWUSH_ACK_PROC_NG;
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
        u1_g_fwush_abort     = (U1)TRUE;
        u1_g_fwush_error_log = (U1)FWUSH_ACK_ROLLBACK_START_ERR;
        break;
    case (U1)FWUSH_CHECK_VA_UNMATCH:
        u1_t_result = u1_g_FwuMemAccSwitchReq();
        if(u1_t_result != (U1)FWUMEMACC_RET_OK){
            u1_g_fwush_abort     = (U1)TRUE;
            u1_g_fwush_error_log = (U1)u1_g_FwushMapMemAccErrorToAck();
        }
        break;
    default:
        vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_CANCEL, (U1)FWUSH_ACK_ROLLBACK_DONE);
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

    u1_t_swva_curr = u1_s_FWUSH_SWVA_MASK & u1_g_FwushGetFswaStat();
    u1_t_swas_curr = u1_s_FWUSH_SWAS_MASK & u1_g_FwushGetFswaStat();
    u1_t_swva_prev = u1_s_FWUSH_SWVA_MASK & u4_g_fwush_fswa_stat;
    u1_t_swas_prev = u1_s_FWUSH_SWAS_MASK & u4_g_fwush_fswa_stat;

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
    U1 u1_t_ack;

    u1_t_read_ok = u1_g_FwushReadData(u4_ap_adr);
    if(u1_t_read_ok == (U1)FALSE){
        u1_t_ack = (U1)FWUSH_ACK_PRECONDITION_ERR;
    }
    else{
        u1_t_cur_target = u1_gp_fwush_header[FWUSH_REQ_PREP_CUR_TARGET_OFFSET];
        u1_t_all_target = u1_gp_fwush_header[FWUSH_REQ_PREP_ALL_TARGET_OFFSET];

        if(u1_t_all_target == (U1)FWUSH_VERI_LB_NONE){
            u1_t_ack = (U1)FWUSH_ACK_NO_REPRO_TARGET;
        }
        else if(((u1_t_cur_target & u1_t_all_target) != u1_t_cur_target) ||
                ((u1_t_cur_target & u1_s_FWUSH_LB_VALID_MASK) != u1_t_cur_target) ||
                ((u1_t_all_target & u1_s_FWUSH_LB_VALID_MASK) != u1_t_all_target)){
            u1_t_ack = (U1)FWUSH_ACK_LB_ERR;
        }
        else{
            u1_t_ack = (U1)FWUSH_ACK_OK;
        }
    }

    return(u1_t_ack);
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
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_PREP, (U1)FWUSH_ACK_OK);
    
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
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_RUN, (U1)FWUSH_ACK_OK);
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
    vd_g_FwushUpdateVeriStat((U1)FWUSH_VERI_LB_NONE, u1_g_fwush_veri_target);
    /* Send ACK */
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_VERI, (U1)FWUSH_ACK_OK);
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
    vd_g_FwushResetVeriStat();
    vd_g_FwushUpdateSeqProgress((U1)FWUSH_PROGRESS_ACT_DONE);
    /* Send ACK */
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_ACT, (U1)FWUSH_ACK_OK);
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
    vd_g_FwushUpdateSeqProgress((U1)FWUSH_PROGRESS_VALIDATE_DONE);
    /* Send ACK */
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_VALID, (U1)FWUSH_ACK_OK);
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
    vd_g_FwushUpdateSeqProgress((U1)FWUSH_PROGRESS_FINALIZE_DONE);
    /* Send ACK */
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_FIN, (U1)FWUSH_ACK_OK);

    vd_g_FwushAbort();
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
    vd_g_FwushUpdateSeqProgress((U1)FWUSH_PROGRESS_ROLLBACK_DONE);
    /* Send ACK */
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_CANCEL, (U1)FWUSH_ACK_ROLLBACK_DONE);

    vd_g_FwushAbort();
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

    u1_t_res_subtype = u1_s_FwushMapReqToResSubtype(u1_gp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET]);
    vd_g_FwushMakeResData(u1_t_res_subtype, (U1)FWUSH_ACK_PROCESSING);
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleEraseAbort(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleEraseAbort(void)
{
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_PREP, u1_g_fwush_error_log);
    vd_g_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleRunAbort(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleRunAbort(void)
{
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_RUN, u1_g_fwush_error_log);
    vd_g_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleVerifyAbort(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleVerifyAbort(void)
{
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_VERI, u1_g_fwush_error_log);
    vd_g_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleActivateAbort(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleActivateAbort(void)
{
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_ACT, u1_g_fwush_error_log);
    vd_g_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleValidateAbort(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleValidateAbort(void)
{
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_VALID, u1_g_fwush_error_log);
    vd_g_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleFinalizeAbort(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleFinalizeAbort(void)
{
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_FIN, u1_g_fwush_error_log);
    vd_g_FwushAbort();
}

/*===================================================================================================================================*/
/* static void vd_s_FwushHandleRollbackAbort(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwushHandleRollbackAbort(void)
{
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_CANCEL, u1_g_fwush_error_log);
    vd_g_FwushAbort();
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

    u1_t_res_subtype = u1_s_FwushMapReqToResSubtype(u1_gp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET]);
    vd_g_FwushMakeResData(u1_t_res_subtype, u1_g_fwush_error_log);
    vd_g_FwushAbort();
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
    vd_g_FwushResetVeriStat();
    vd_g_FwushUpdateSeqProgress((U1)FWUSH_PROGRESS_CANCEL_DONE);
    vd_g_FwushMakeResData((U1)FWUSH_RESP_SUBTYPE_CANCEL, (U1)FWUSH_ACK_OK);
    vd_g_FwushAbort();
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0    03/27/2026  KI       Split from fwush.c - State transition table & handlers                                             */
/*                                                                                                                                   */
/* * KI   = Kanji Ito, Denso Techno                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
