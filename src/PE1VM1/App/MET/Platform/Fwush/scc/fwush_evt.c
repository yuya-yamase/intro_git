/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* FW Update State Handler - Event Detection                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUSH_EVT_C_MAJOR                   (2U)
#define FWUSH_EVT_C_MINOR                   (0U)
#define FWUSH_EVT_C_PATCH                   (0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "fwush_internal.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_FwushDetectResumeEvent(void);
static U1 u1_g_FwushDetectEventForWaiting(void);
static U1 u1_g_FwushDetectEventForProcessing(void);
static U1 u1_s_FwushCheckMemAccJobEvent(void);
static U1 u1_s_FwushMapMainStatusToEvent(U1 u1_a_main_status);
static U1 u1_g_FwushMapMemAccErrorToAckForRollback(void);
static U1 u1_g_FwushMapMemAccErrorToAckForOth(void);
static U1 u1_s_FwushDetectresponseEvent(U1 u1_a_req_subtype);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* U1 u1_g_FwushDetectEvent(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Detected event                                                                                              */
/*===================================================================================================================================*/
U1 u1_g_FwushDetectEvent(void)
{
    U1 u1_t_event;
    U1 u1_t_head_ok;

    u1_t_event = u1_s_FwushDetectResumeEvent();
    if(u1_t_event != (U1)FWUSH_EVENT_NONE){
        /* Keep Resume Event */
    }
    else if(u1_g_fwush_state_sub == (U1)FWUSH_SUB_STATE_WAITING){
        u1_t_head_ok = u1_g_FwushReadHeader(&u1_gp_fwush_header[0]);
        if(u1_t_head_ok == (U1)FALSE){
            u1_t_event = (U1)FWUSH_EVENT_NONE;
        }
        else{
            u1_t_event = u1_g_FwushDetectEventForWaiting();
        }
    }
    else if(u1_g_fwush_state_sub == (U1)FWUSH_SUB_STATE_PROCESSING){
        u1_t_head_ok = u1_g_FwushReadHeader(&u1_gp_fwush_header[0]);
        if(u1_t_head_ok == (U1)FALSE){
            u1_t_event = (U1)FWUSH_EVENT_NONE;
        }
        else{
            u1_t_event = u1_g_FwushDetectEventForProcessing();
        }

        if(u1_g_fwush_abort != (U1)FALSE){
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
    if(u1_g_fwush_state_main == (U1)FWUSH_MAIN_STATE_PREP){
        u1_t_veri_target = (U1)((u2_g_fwush_veri_stat >> (U2)8U) & (U2)0xFFU);
        u1_t_veri_comp = (U1)(u2_g_fwush_veri_stat & (U2)0xFFU);
        if((u1_g_fwush_seq_progress & u1_s_FWUSH_PROG_MASK) == u1_s_FWUSH_PROG_ACT_CRIT){
            /* Change state to Validate */
            u1_t_event = (U1)FWUSH_EVENT_SWITCH_DETECT;
        }
        else if((u1_t_veri_target == u1_t_veri_comp) &&
                (u2_g_fwush_veri_stat != (U2)FWUSH_VERI_LB_STAT_INIT)){
                u1_t_event = (U1)FWUSH_EVENT_RESUME_ACT;
        }
        else if((u1_g_fwush_seq_progress & u1_s_FWUSH_PROG_MASK) == u1_s_FWUSH_PROG_VALID_CRIT){
                u1_t_event = (U1)FWUSH_EVENT_RESUME_FIN;
        }
        else{
            /* Do Nothing */
        }
    }

    return(u1_t_event);
}

/*===================================================================================================================================*/
/* static U1 u1_g_FwushDetectEventForWaiting(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Detected event                                                                                              */
/*===================================================================================================================================*/
static U1 u1_g_FwushDetectEventForWaiting(void)
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
    u1_t_current_req_subtype = u1_gp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET];
    u1_t_seqcnt              = u1_gp_fwush_header[FWUSH_REQ_SEQCNT_OFFSET];
    u1_t_event               = (U1)FWUSH_EVENT_NONE;
    u1_t_expected_subtype    = (U1)u1_sp_FWUSH_EXPCT_SUBTYPE_WA[u1_g_fwush_state_main];
    
    /* Detect request change */
    if(u1_t_seqcnt != u1_g_fwupx_req_seqcnt_pre){
        /* Check resume event first */
        u1_t_resume_event = u1_s_FwushDetectresponseEvent(u1_t_current_req_subtype);
        if(u1_t_resume_event != (U1)FWUSH_EVENT_NONE){
            u1_t_event = u1_t_resume_event;
        }
        else if(u1_t_current_req_subtype == u1_t_expected_subtype){
            u1_t_event = (U1)FWUSH_EVENT_NEW_REQUEST;
        }
        else if(u1_t_current_req_subtype == (U1)FWUSH_REQ_SUBTYPE_CANCEL){
            if((u1_g_fwush_seq_progress & u1_s_FWUSH_PROG_MASK_WAITING) == u1_s_FWUSH_PROG_ACT_CRIT_WAITING){
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
            u1_g_fwush_error_log = (U1)FWUSH_ACK_SEQ_ERR;
        }
        else{
            /* Do Nothing */
        }
        u1_g_fwupx_req_seqcnt_pre = u1_t_seqcnt;
    }
    else{
        u1_t_event = (U1)FWUSH_EVENT_NONE;
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

    switch(u1_g_fwush_state_main){
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
                    (u1_g_fwush_seq_progress & (U1)FWUSH_PROGRESS_ACT_DONE) != (U1)0U){
                /* ACT + ACT_DONE bit set -> RES_OK (priority over NEW_REQUEST) */
                u1_t_event = (U1)FWUSH_EVENT_RES_OK;
            }
            else{
                /* Do Nothing */
            }
            break;
        case (U1)FWUSH_MAIN_STATE_VALID:
            /* VALID + ACT -> RES_OK */
            if(u1_a_req_subtype == (U1)FWUSH_REQ_SUBTYPE_ACT){
                u1_t_event = (U1)FWUSH_EVENT_RES_OK;
            }
            break;
        case (U1)FWUSH_MAIN_STATE_FIN:
            /* FIN + VALID -> depends on ROLLBACK_DONE bit */
            if(u1_a_req_subtype == (U1)FWUSH_REQ_SUBTYPE_VALID){
                if((u1_g_fwush_seq_progress & (U1)FWUSH_PROGRESS_ROLLBACK_DONE) == (U1)0U){
                    /* ROLLBACK_DONE bit is 0 -> RES_OK */
                    u1_t_event = (U1)FWUSH_EVENT_RES_OK;
                }
                else{
                    /* ROLLBACK_DONE bit is 1 -> INVALID_REQUEST */
                    u1_t_event = (U1)FWUSH_EVENT_INVALID_REQUEST;
                    u1_g_fwush_error_log = (U1)FWUSH_ACK_SEQ_ERR;
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
/* static U1 u1_g_FwushDetectEventForProcessing(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Detected event                                                                                              */
/*===================================================================================================================================*/
static U1 u1_g_FwushDetectEventForProcessing(void)
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

    u1_t_current_req_subtype = u1_gp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET];
    u1_t_seqcnt              = u1_gp_fwush_header[FWUSH_REQ_SEQCNT_OFFSET];
    
    /* Detect request change */
    if(u1_t_seqcnt != u1_g_fwupx_req_seqcnt_pre){
        if(u1_t_current_req_subtype != (U1)FWUSH_REQ_SUBTYPE_NA){
            u1_t_event = (U1)FWUSH_EVENT_INVALID_REQUEST;
        }
        else{
            u1_t_event = u1_s_FwushCheckMemAccJobEvent();
        }
        u1_g_fwupx_req_seqcnt_pre = u1_t_seqcnt;
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
        u1_g_fwush_error_log = u1_g_FwushMapMemAccErrorToAck();
    }

    switch (u1_g_fwush_state_main){
        case (U1)FWUSH_MAIN_STATE_RUN:
            if(u1_t_main_status == (U1)FWUMEMACC_MAIN_STATUS_COMPLETED){
                u1_t_update_status = u1_g_FwuMemAccGetUpdateStatus();
                if(u1_t_update_status == (U1)FWUMEMACC_UPDT_STS_ALL_COMP){
                    u1_t_event = (U1)FWUSH_EVENT_MEMACC_SUCCESS;
                }
                else if(u1_t_update_status == (U1)FWUMEMACC_UPDT_STS_IN_PROGRESS){
                    u1_t_event = (U1)FWUSH_EVENT_MEMACC_RUN_PARTIAL;
                }
                else{
                    /* IDLE: keep FWUSH_EVENT_MEMACC_SUCCESS from mapping */
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
        (U1)FWUSH_EVENT_NONE,            /* FWUMEMACC_MAIN_STATUS_REQUESTED (1U) */
        (U1)FWUSH_EVENT_NONE,            /* FWUMEMACC_MAIN_STATUS_ACTIVE    (2U) */
        (U1)FWUSH_EVENT_MEMACC_SUCCESS,  /* FWUMEMACC_MAIN_STATUS_COMPLETED (3U) */
        (U1)FWUSH_EVENT_MEMACC_ERROR     /* FWUMEMACC_MAIN_STATUS_ERROR     (4U) */
    };

    return(u1_sp_FWUMEMACC_STATUS_TO_EVENT[u1_a_main_status]);
}
/*===================================================================================================================================*/
/* U1 u1_g_FwushMapMemAccErrorToAck(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Mapped fwush ACK error code                                                                                 */
/*===================================================================================================================================*/
U1 u1_g_FwushMapMemAccErrorToAck(void)
{
    U1 u1_t_ack;

    if((u1_g_fwush_state_main == (U1)FWUSH_MAIN_STATE_FIN) &&
       (u1_g_fwush_state_sub  == (U1)FWUSH_SUB_STATE_PROCESSING)){
        u1_t_ack = u1_g_FwushMapMemAccErrorToAckForRollback();
    }
    else{
        u1_t_ack = u1_g_FwushMapMemAccErrorToAckForOth();
    }

    return(u1_t_ack);
}
/*===================================================================================================================================*/
/* static U1 u1_g_FwushMapMemAccErrorToAckForRollback(void)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Mapped fwush ACK error code (for Rollback)                                                                  */
/*===================================================================================================================================*/
static U1 u1_g_FwushMapMemAccErrorToAckForRollback(void)
{
    static const U1 u1_sp_FWUMEMACC_ERROR_TO_ACK_RB[FWUMEMACC_ERROR_MAX] =
    {
        (U1)FWUSH_ACK_ROLLBACK_NG,            /* FWUMEMACC_ERROR_NONE             (0U) */
        (U1)FWUSH_ACK_ROLLBACK_PRECOND_ERR,   /* FWUMEMACC_ERROR_PRECONDITION_ERR (1U) */
        (U1)FWUSH_ACK_OFFSET_JUMP,            /* FWUMEMACC_ERROR_OFFSET_JUMP      (2U) */
        (U1)FWUSH_ACK_OFFSET_UNCHANGED,       /* FWUMEMACC_ERROR_OFFSET_UNCHANGED (3U) */
        (U1)FWUSH_ACK_OFFSET_SUBTRACT,        /* FWUMEMACC_ERROR_OFFSET_SUBTRACT  (4U) */
        (U1)FWUSH_ACK_ROLLBACK_NG,            /* FWUMEMACC_ERROR_MEMACC_FAILED    (5U) */
        (U1)FWUSH_ACK_ROLLBACK_START_ERR,     /* FWUMEMACC_ERROR_START_ERR        (6U) */
        (U1)FWUSH_ACK_LB_ERR                  /* FWUMEMACC_ERROR_LB_INFO_ERR      (7U) */
    };
    U1 u1_t_error;
    u1_t_error = u1_g_FwuMemAccGetError();
    return(u1_sp_FWUMEMACC_ERROR_TO_ACK_RB[u1_t_error]);
}
/*===================================================================================================================================*/
/* static U1 u1_g_FwushMapMemAccErrorToAckForOth(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Mapped fwush ACK error code (for Other states)                                                              */
/*===================================================================================================================================*/
static U1 u1_g_FwushMapMemAccErrorToAckForOth(void)
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
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0    03/27/2026  KI       Split from fwush.c - Event detection functions                                                     */
/*                                                                                                                                   */
/* * KI   = Kanji Ito, Denso Techno                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
