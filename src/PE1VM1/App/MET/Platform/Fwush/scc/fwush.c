/* 1.0.0 */
/*===================================================================================================================================*/
/*  FW Update State Handler                                                                                                          */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "fwush.h"

#include "ivdsh.h"

#include "aip_common.h"
#include "memfill_u4.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* Action Definitions for 8-State Machine */
#define FWUSH_ACT_TO_RUN      (0U)  /* RUN状態への遷移 */
#define FWUSH_ACT_TO_RUN_FIN  (1U)  /* RUN状態からの遷移 */
#define FWUSH_ACT_TO_ACT      (2U)  /* ACT状態への遷移 */
#define FWUSH_ACT_TO_ACT_FIN  (3U)  /* ACT状態からの遷移 */
#define FWUSH_ACT_PREP        (4U)  /* PREP状態での処理継続 */
#define FWUSH_ACT_RUN         (5U)  /* RUN状態での処理継続 */
#define FWUSH_ACT_VERI        (6U)  /* VERI状態での処理継続 */
#define FWUSH_ACT_ACT         (7U)  /* ACT状態での処理継続 */

/* Event Definitions */
#define FWUSH_EAS_CHK_PREP_FIN      (0x01U)  /* PREP処理完了 */
#define FWUSH_EAS_CHK_RUN_FIN       (0x02U)  /* RUN処理完了 */
#define FWUSH_EAS_CHK_VERI_FIN      (0x04U)  /* VERI処理完了 */
#define FWUSH_EAS_CHK_ACT_FIN       (0x08U)  /* ACT処理完了 */

/* Log types for debugging */
#define FWUSH_LOG_NORMAL_TRANSITION (0x00U)
#define FWUSH_LOG_ABORT_TRANSITION  (0x01U)

/* System status bit masks */
#define SYSTEM_STATUS_CRITICAL_ERROR (0x80000000UL)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                u1_sp_fwush_header[FWUSH_REQ_H_SIZE];
static U1                u1_s_fwush_subtype_prev;
static U1                u1_s_fwush_stm_ctl;
static U1                u1_s_fwush_stm_act;
static U1                u1_s_fwush_memacc_job_active;
static U1                u1_s_fwush_abort_active;

static U2                u2_s_fwush_run_offset_prev;
static U1                u1_s_fwush_act_fin_flg;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1       u1_s_FwushReadHeader(U1 * u1_ap_ptr);
static U1        u1_s_FwushReadData(U2 u2_a_length, U4* u4_ap_reqadr);
static U2       u2_s_FwushEasChk(void);

static void     vd_s_FwushStmEvPrep(void);
static void     vd_s_FwushStmEvRun(void);
static void     vd_s_FwushStmEvVeri(void);
static void     vd_s_FwushStmEvAct(void);
static void     vd_s_FwushStmEvToRun(void);
static void     vd_s_FwushStmEvToRunFin(void);
static void     vd_s_FwushStmEvToAct(void);
static void     vd_s_FwushStmEvToActFin(void);

static U1       u1_s_FwushReqChk(void);
static void     vd_s_FwushPrepMemAccChk(void);
static void     vd_s_FwushRunMemAccChk(void);
static void     vd_s_FwushVeriMemAccChk(void);
static void     vd_s_FwushActMemAccChk(void);
static void     vd_s_FwushMakeAckData(U1 u1_a_subtype);
static void     vd_s_FwushMakeNackData(U1 u1_a_subtype);
static U1       u1_s_FwushMakePrepData(U4 * u4_ap_adr, U4 * u4_ap_length, U4 * u4_ap_crc);
static U1       u1_s_FwushMakeRunData(U4 * u4_ap_adr, U2 * u2_ap_ofst);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_FwushInit(void)
{
    u1_s_fwush_subtype_prev = (U1)FWUSH_REQ_SUBTYPE_NA;
    u1_s_fwush_stm_ctl = (U1)FWUSH_STS_PREP;  /* Initialize to PREP_受信中 */
    u1_s_fwush_stm_act = (U1)0U;
    u1_s_fwush_abort_active = (U1)FALSE;
    u1_s_fwush_memacc_job_active = (U1)FALSE;
    u2_s_fwush_run_offset_prev = (U2)0xFFFFU;

    u1_s_fwush_act_fin_flg = (U1)FALSE;

    vd_g_FwuMemAccInit();
}


void    vd_g_FwushMainTask(void)
{
    /* State transition matrix: [Event][Current_State] -> Action */
    /* Current State: PREP(0), RUN(1), VERI(2), ACT(3) */
    /* Event Index: bit pattern from u2_t_eas_chk */
    static const U1 u1_sp_FWUSH_STM[] = {
        /* EAS=0: Normal operation (no events) */
        /* PREP               RUN                       VERI                  ACT                    */
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        /* EAS=1    : PREP_FIN */
        (U1)FWUSH_ACT_TO_RUN, (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        /* EAS=2    : RUN_FIN */
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_TO_RUN_FIN, (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        /* EAS=3    : RUN_FIN + PREP_FIN (irregular) */
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        /* EAS=4    : VERI_FIN */
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_TO_ACT, (U1)FWUSH_ACT_ACT,
        /* EAS=5-7  : VERI_FIN + other (irregular) */
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        /* EAS=8    : ACT_FIN */
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_TO_ACT_FIN,
        /* EAS=9-15 : ACT_FIN + other (irregular) */
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT,
        (U1)FWUSH_ACT_PREP,   (U1)FWUSH_ACT_RUN,        (U1)FWUSH_ACT_VERI,   (U1)FWUSH_ACT_ACT
        /* PREP               RUN                       VERI                  ACT                    */
    };

    /* Action function pointer table */
    static void (* const  fp_sp_FWUSH_ACT[])(void) = {
        &vd_s_FwushStmEvToRun,            /* FWUSH_ACT_TO_RUN      (0U) */
        &vd_s_FwushStmEvToRunFin,         /* FWUSH_ACT_TO_RUN_FIN  (1U) */
        &vd_s_FwushStmEvToAct,            /* FWUSH_ACT_TO_ACT      (2U) */
        &vd_s_FwushStmEvToActFin,         /* FWUSH_ACT_TO_ACT_FIN  (3U) */
        &vd_s_FwushStmEvPrep,             /* FWUSH_ACT_PREP        (4U) */
        &vd_s_FwushStmEvRun,              /* FWUSH_ACT_RUN         (5U) */
        &vd_s_FwushStmEvVeri,             /* FWUSH_ACT_VERI        (6U) */
        &vd_s_FwushStmEvAct               /* FWUSH_ACT_ACT         (7U) */
    };
    static const U2  u2_s_FWUSH_ACT_SIZE = sizeof(fp_sp_FWUSH_ACT) / sizeof(fp_sp_FWUSH_ACT[0]);

    U1  u1_t_head_ok;
    U2  u2_t_eas_chk;
    U2  u2_t_act;

    /* Check for external request changes */
    u1_t_head_ok = u1_s_FwushReqChk();
    if(u1_t_head_ok == (U1)TRUE){
    
        /* Determine event/action status */
        u2_t_eas_chk = u2_s_FwushEasChk();
    
        /* Calculate table index: (Event_Index * State_Count) + Current_State */
        u2_t_act = (u2_t_eas_chk * (U2)FWUSH_NUM_STS) + (U2)u1_s_fwush_stm_ctl;

        /* Bounds check for state machine table */
        if(u2_t_act < (U2)(sizeof(u1_sp_FWUSH_STM) / sizeof(u1_sp_FWUSH_STM[0]))){
            u2_t_act = (U2)u1_sp_FWUSH_STM[u2_t_act];
            
            /* Bounds check for function pointer table */
            if(u2_t_act < u2_s_FWUSH_ACT_SIZE){
                /* Null check */
                if(fp_sp_FWUSH_ACT[u2_t_act] != vdp_PTR_NA){
                    /* Execute selected action */
                    fp_sp_FWUSH_ACT[u2_t_act]();
                }
            }
        }
        /* Store previous subtype for change detection */
        u1_s_fwush_subtype_prev = u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET];

        /* 関数化 */
        if(u1_s_fwush_abort_active != (U1)FALSE){
            /* Handle error state */
            vd_s_FwushMakeNackData(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET]);
            vd_g_FwushInit();
        }
    }

    vd_g_FwuMemAccMainTask();
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1    u1_s_FwushReqChk(void)
{
    U1  u1_t_read_ok;
    
    /* FWUPXREQ_H analysis */
    u1_t_read_ok = u1_s_FwushReadHeader(&u1_sp_fwush_header[0]);

    return(u1_t_read_ok);
}

static U2       u2_s_FwushEasChk(void)
{
    U2  u2_t_eas_pattern;
    
    /* Clear previous EAS check result */
    u2_t_eas_pattern = (U2)0U;
    
    /* Build event pattern from current request status */
    if((u1_s_fwush_stm_act & (U1)FWUSH_EAS_CHK_PREP_FIN) != (U1)0U){
        u2_t_eas_pattern |= (U2)FWUSH_EAS_CHK_PREP_FIN;
    }

    if((u1_s_fwush_stm_act & (U1)FWUSH_EAS_CHK_RUN_FIN) != (U1)0U){
        u2_t_eas_pattern |= (U2)FWUSH_EAS_CHK_RUN_FIN;
    }
    
    if((u1_s_fwush_stm_act & (U1)FWUSH_EAS_CHK_VERI_FIN) != (U1)0U){
        u2_t_eas_pattern |= (U2)FWUSH_EAS_CHK_VERI_FIN;
    }

    if((u1_s_fwush_stm_act & (U1)FWUSH_EAS_CHK_ACT_FIN) != (U1)0U){
        u2_t_eas_pattern |= (U2)FWUSH_EAS_CHK_ACT_FIN;
    }

    /* 異常中断要求はEvent Action Statusで管理しない*/

    /* Clear processed flags */
    u1_s_fwush_stm_act = (U1)0U;
    
    return(u2_t_eas_pattern);
}

static void     vd_s_FwushPrepMemAccChk(void)
{
    U1  u1_t_prep_sts;
    u1_t_prep_sts = u1_g_FwuMemAccEraseSts();
    switch (u1_t_prep_sts)
    {
    case FWUSH_MEMACC_STATUS_PREP_IDLE:
        break;
    case FWUSH_MEMACC_STATUS_PREP_RUNNING:
        break;
    case FWUSH_MEMACC_STATUS_PREP_SUCCESS:
        /* Job completed successfully */
        u1_s_fwush_memacc_job_active = (U1)FALSE;
        u1_s_fwush_stm_act |= (U1)FWUSH_EAS_CHK_PREP_FIN;
        break;
    case FWUSH_MEMACC_STATUS_PREP_ERROR:
        /* Job failed */
        u1_s_fwush_memacc_job_active = (U1)FALSE;
        u1_s_fwush_stm_act |= (U1)FWUSH_EAS_CHK_PREP_FIN;
        break;
    default:
        break;  /* Invalid status */
    }
}

static void     vd_s_FwushRunMemAccChk(void)
{
    U1  u1_t_run_sts;

    u1_t_run_sts = u1_g_FwuMemAccUpdateSts();
    switch (u1_t_run_sts)
    {
    case (U1)FWUSH_MEMACC_STATUS_RUN_IDLE:
        break;
    case (U1)FWUSH_MEMACC_STATUS_RUN_RUNNING:
        break;
    case (U1)FWUSH_MEMACC_STATUS_RUN_CRC_CHECK:
        break;
    case (U1)FWUSH_MEMACC_STATUS_RUN_SUCCESS_MIDWAY:
        /* Job completed successfully (MIDWAY) */
        u1_s_fwush_memacc_job_active = (U1)FALSE;
        u1_s_fwush_stm_act |= (U1)FWUSH_EAS_CHK_RUN_FIN;
        break;
    case (U1)FWUSH_MEMACC_STATUS_RUN_SUCCESS_FINAL:
        /* Job completed successfully (FINAL)*/
        u1_s_fwush_memacc_job_active = (U1)FALSE;
        u1_s_fwush_stm_act |= (U1)FWUSH_EAS_CHK_RUN_FIN;
        break;
    case (U1)FWUSH_MEMACC_STATUS_RUN_ERROR:
        /* Job failed */
        u1_s_fwush_memacc_job_active = (U1)FALSE;
        u1_s_fwush_stm_act |= (U1)FWUSH_EAS_CHK_RUN_FIN;
        break;
    default:
        break;  /* Invalid status */
    }
}

static void     vd_s_FwushVeriMemAccChk(void)
{
        /* u1_s_fwush_veri_sts = u1_g_MemAcc_GetVeriJobStatus(); */  /* Step1では不要 */
        u1_s_fwush_stm_act |= (U1)FWUSH_EAS_CHK_VERI_FIN;
}

static void     vd_s_FwushActMemAccChk(void)
{
    U1  u1_t_act_sts;
    u1_t_act_sts = u1_g_FwuMemAccSwitchSts();
    switch (u1_t_act_sts)
    {
    case FWUSH_MEMACC_STATUS_ACT_IDLE:
        /* Job is idle */
        break;
    case FWUSH_MEMACC_STATUS_ACT_RUNNING:
        /* Job is running */
    break;
    case FWUSH_MEMACC_STATUS_ACT_SUCCESS:
        /* Job completed successfully */
        u1_s_fwush_memacc_job_active = (U1)FALSE;
        u1_s_fwush_stm_act |= (U1)FWUSH_EAS_CHK_ACT_FIN;
        break;
    case FWUSH_MEMACC_STATUS_ACT_ERROR:
        /* Job failed */
        u1_s_fwush_memacc_job_active = (U1)FALSE;
        u1_s_fwush_stm_act |= (U1)FWUSH_EAS_CHK_ACT_FIN;
        break;
    default:
        break;  /* Invalid status */
    }
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/


/* 定常処理 */
static void   vd_s_FwushStmEvPrep(void)
{
    U1    u1_t_read_ok;
    U4    u4_t_adr;
    U4    u4_t_length;
    U4    u4_t_crc;

    switch (u1_s_fwush_subtype_prev)  /* Check previous subtype */
    {
        case FWUSH_REQ_SUBTYPE_NA:    /* RECV */  /* 関数化 */
            if(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] == (U1)FWUSH_REQ_SUBTYPE_PREP)
            {
                /* make memacc data for Prep */
                u1_t_read_ok = u1_s_FwushMakePrepData(&u4_t_adr, &u4_t_length, &u4_t_crc);
                /* Start MemAcc job for preparation */
                if(u1_t_read_ok == (U1)TRUE){
                    u1_s_fwush_memacc_job_active = (U1)TRUE;
                    vd_g_FwuMemAccEraseReqTrg(u4_t_adr, u4_t_length, u4_t_crc);
                } else {
                    u1_s_fwush_abort_active = (U1)TRUE;  /* Set abort flag */
                }
            }
            else
            {
                /* u1_s_fwush_stm_ctl = (U1)FWUSH_STS_PREP; */  /* No need to action. */
            }
            break;
        case FWUSH_REQ_SUBTYPE_PREP:    /* PROC */  /* 関数化 */
            if(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] == (U1)FWUSH_REQ_SUBTYPE_PREP)
            {
                /* Already in PREP state, continue processing */
                vd_s_FwushPrepMemAccChk();
            }
            else
            {
                u1_s_fwush_abort_active = (U1)TRUE;  /* Set abort flag */
            }
        default:
            break;
    }
}

static void   vd_s_FwushStmEvRun(void)
{
    U1    u1_t_read_ok;
    U4    u4_t_adr;
    U2    u2_t_ofst;

    switch (u1_s_fwush_subtype_prev)  /* Check previous subtype */
    {
        case FWUSH_REQ_SUBTYPE_NA:    /* RECV */  /* 関数化 */
            if(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] == (U1)FWUSH_REQ_SUBTYPE_RUN)
            {
                /* make memacc data for Run */
                u1_t_read_ok = u1_s_FwushMakeRunData(&u4_t_adr, &u2_t_ofst);
                if (u2_t_ofst != u2_s_fwush_run_offset_prev)
                {
                    /* Start MemAcc job for Run */
                    if(u1_t_read_ok == (U1)TRUE){
                        u1_s_fwush_memacc_job_active = (U1)TRUE;
                        vd_g_FwuMemAccUpdateReqTrg(u2_t_ofst, (U4 *)u4_t_adr);
                    } else {
                        u1_s_fwush_abort_active = (U1)TRUE;  /* Set abort flag */
                    }
                }
                else
                {
                    /* Offset has not changed, no need to start MemAcc job */
                    u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = FWUSH_REQ_SUBTYPE_NA;  /* Wait new request */
                }
                /* Update previous offset */
                u2_s_fwush_run_offset_prev = u2_t_ofst;
            }
            else
            {
                /* u1_s_fwush_stm_ctl = (U1)FWUSH_STS_RUN; */  /* No need to action. */
            }
            break;
        case FWUSH_REQ_SUBTYPE_RUN:    /* PROC */  /* 関数化 */
            if(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] == (U1)FWUSH_REQ_SUBTYPE_RUN)
            {
                /* Already in RUN state, continue processing */
                vd_s_FwushRunMemAccChk();
            }
            else
            {
                u1_s_fwush_abort_active = (U1)TRUE;  /* Set abort flag */
            }
        default:
            break;
    }
}

static void     vd_s_FwushStmEvVeri(void)
{
    switch (u1_s_fwush_subtype_prev)  /* Check previous subtype */
    {
        case FWUSH_REQ_SUBTYPE_NA:    /* RECV */  /* 関数化 */
            if(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] == (U1)FWUSH_REQ_SUBTYPE_VERI)
            {
                /* Start MemAcc job for verification */
                u1_s_fwush_memacc_job_active = (U1)TRUE;
            }
            else
            {
                /* u1_s_fwush_stm_ctl = (U1)FWUSH_STS_VERI; */  /* No need to action. */
            }
            break;
        case FWUSH_REQ_SUBTYPE_VERI:    /* PROC */  /* 関数化 */
            if(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] == (U1)FWUSH_REQ_SUBTYPE_VERI)
            {
                /* Already in VERI state, continue processing */
                vd_s_FwushVeriMemAccChk();
            }
            else
            {
                u1_s_fwush_abort_active = (U1)TRUE;  /* Set abort flag */
            }
        default:
            break;
    }
}

static void     vd_s_FwushStmEvAct(void)
{
    if(u1_s_fwush_act_fin_flg == (U1)FALSE)
    {
        switch (u1_s_fwush_subtype_prev)  /* Check previous subtype */
        {
            case FWUSH_REQ_SUBTYPE_NA:    /* RECV */  /* 関数化 */
                if(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] == (U1)FWUSH_REQ_SUBTYPE_ACT)
                {
                    /* Start MemAcc job for activation */
                    vd_g_FwuMemAccSwitchReqTrg();
                    u1_s_fwush_memacc_job_active = (U1)TRUE;
                }
                else
                {
                    /* u1_s_fwush_stm_ctl = (U1)FWUSH_STS_ACT; */  /* No need to action. */
                }
                break;
            case FWUSH_REQ_SUBTYPE_ACT:    /* PROC */  /* 関数化 */
                if(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] == (U1)FWUSH_REQ_SUBTYPE_ACT)
                {
                    /* Already in ACT state, continue processing */
                    vd_s_FwushActMemAccChk();
                }
                else
                {
                    u1_s_fwush_abort_active = (U1)TRUE;  /* Set abort flag */
                }
            default:
                break;
        }
    }
}

/* 遷移処理 */
static void     vd_s_FwushStmEvToRun(void)
{
    U1  u1_t_prep_sts;

    u1_t_prep_sts = u1_g_FwuMemAccEraseSts();
    switch (u1_t_prep_sts)
    {
    case (U1)FWUSH_MEMACC_STATUS_PREP_SUCCESS:
        /* Transition to RUN state */
        u1_s_fwush_stm_ctl = (U1)FWUSH_STS_RUN;
        vd_s_FwushMakeAckData(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET]);
        break;
    case (U1)FWUSH_MEMACC_STATUS_PREP_ERROR:
        /* Transition to PREP state with abort */
        u1_s_fwush_abort_active = (U1)TRUE;  /* Set abort flag */
    default:
        break;
    }
}

static void     vd_s_FwushStmEvToRunFin(void)
{
    U1  u1_t_run_sts;

    u1_t_run_sts = u1_g_FwuMemAccUpdateSts();
    switch (u1_t_run_sts)
    {
    case (U1)FWUSH_MEMACC_STATUS_RUN_SUCCESS_MIDWAY:
        /* Keep Run state */
        u1_s_fwush_stm_ctl = (U1)FWUSH_STS_RUN;
        vd_s_FwushMakeAckData(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET]);
        break;
    case (U1)FWUSH_MEMACC_STATUS_RUN_SUCCESS_FINAL:
        /* Transition to FIN state */
        u1_s_fwush_stm_ctl = (U1)FWUSH_STS_VERI;
        vd_s_FwushMakeAckData(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET]);
        break;
    case (U1)FWUSH_MEMACC_STATUS_RUN_ERROR:
        /* Transition to PREP state with abort */
        u1_s_fwush_abort_active = (U1)TRUE;  /* Set abort flag */
    default:
        break;
    }
}

static void     vd_s_FwushStmEvToAct(void)
{
    /* Step1ではVERIの管理不要。必ず成功扱いでACTに遷移する。 */
    u1_s_fwush_stm_ctl = (U1)FWUSH_STS_ACT;
    vd_s_FwushMakeAckData(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET]);
}

static void     vd_s_FwushStmEvToActFin(void)
{
    U1  u1_t_act_sts;

    u1_t_act_sts = u1_g_FwuMemAccSwitchSts();
    switch (u1_t_act_sts)
    {
    case (U1)FWUSH_MEMACC_STATUS_ACT_SUCCESS:
        /* Transition to ACT state */
        u1_s_fwush_stm_ctl = (U1)FWUSH_STS_ACT;  /* Step1では手動リセットがかかるまでACTで固定する。 */
        u1_s_fwush_act_fin_flg = (U1)TRUE;       /* Step1では手動リセットがかかるまでACTで固定する。 */
        vd_s_FwushMakeAckData(u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET]);
        break;
    case (U1)FWUSH_MEMACC_STATUS_ACT_ERROR:
        /* Transition to PREP state with abort */
        u1_s_fwush_abort_active = (U1)TRUE;  /* Set abort flag */
    default:
        break;
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_FwushMakeAckData(U1 u1_a_subtype)
{
    /* ヘッダデータ(グローバル変数) または 現在の遷移状態に従って応答データを変えられるように作る */
    U4  u4_tp_ack_data[FWUSH_RES_WORDS];
    
    /* Clear response data buffer */
    vd_g_MemfillU4(&u4_tp_ack_data[0], (U4)0U, (U4)FWUSH_RES_WORDS);
    
    switch (u1_a_subtype)  /* Check subtype for specific NACK handling */
    {
    case (U1)FWUSH_REQ_SUBTYPE_PREP:
        /* Handle PREP specific ACK */
        /* make write data (Subtype 07h, Ack OK) */
        u4_tp_ack_data[0] = (U4)0x07U | ((U4)FWUSH_ACK_OK << (U1)8U) | ((U4)0x01U << (U1)16U); /* SubType & Ack & LogicalBlock */
        u4_tp_ack_data[1] = (U4)0x00U; /* Reserve */
        /* iVDshWrite */
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_ack_data[0], (U2)FWUSH_RES_WORDS);
        u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = FWUSH_REQ_SUBTYPE_NA;  /* Reset previous subtype */
        break;
    case (U1)FWUSH_REQ_SUBTYPE_RUN:
        /* make write data (Subtype 17h, Ack OK) */
        u4_tp_ack_data[0] = (U4)(0x17U | ((U4)FWUSH_ACK_OK << (U1)8U) | ((U4)0x01U << (U1)16U)
                          | (U4)((u2_s_fwush_run_offset_prev & (U2)0xFF00U) << (U1)16U)); /* SubType & Ack & LogicalBlock & offset(high) */
        u4_tp_ack_data[1] = (U4)((u2_s_fwush_run_offset_prev & (U2)0x00FFU)) | ((U4)0x04U << (U1)8U) | ((U4)0x00U << (U1)16U); /* offset(low) & length(high) & length (low) */
        /* iVDshWrite */
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_ack_data[0], (U2)FWUSH_RES_WORDS);
        u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = FWUSH_REQ_SUBTYPE_NA;  /* Reset previous subtype */
        break;
    case (U1)FWUSH_REQ_SUBTYPE_VERI:
        /* make write data (Subtype 18h, Ack OK) */
        u4_tp_ack_data[0] = (U4)0x19U | ((U4)FWUSH_ACK_OK << (U1)8U) | ((U4)0x01U << (U1)16U); /* SubType & Ack & LogicalBlock */
        u4_tp_ack_data[1] = (U4)0x00U; /* Reserve */
        /* iVDshWrite */
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_ack_data[0], (U2)FWUSH_RES_WORDS);
        u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = FWUSH_REQ_SUBTYPE_NA;  /* Reset previous subtype */
        break;
    case (U1)FWUSH_REQ_SUBTYPE_ACT:
        /* make write data (Subtype 38h, Ack OK) */
        u4_tp_ack_data[0] = (U4)0x38U | ((U4)FWUSH_ACK_OK << (U1)8U); /* SubType & Ack */
        u4_tp_ack_data[1] = (U4)0x00U; /* Reserve */
        /* iVDshWrite */
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_ack_data[0], (U2)FWUSH_RES_WORDS);
        u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = FWUSH_REQ_SUBTYPE_NA;  /* Reset previous subtype */
        break;
    default:
        break;
    }
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_FwushMakeNackData(U1 u1_a_subtype)
{
    /* ヘッダデータ(グローバル変数) または 現在の遷移状態に従って応答データを変えられるように作る */
    U4  u4_tp_nack_data[FWUSH_RES_WORDS];
    
    /* Clear response data buffer */
    vd_g_MemfillU4(&u4_tp_nack_data[0], (U4)0U, (U4)FWUSH_RES_WORDS);
    
    switch (u1_a_subtype)  /* Check subtype for specific NACK handling */
    {
    case (U1)FWUSH_REQ_SUBTYPE_PREP:
        /* Handle PREP specific NACK */
        /* make write data (Subtype 07h, Ack NG) */
        u4_tp_nack_data[0] = (U4)0x07U | ((U4)FWUSH_ACK_NG << (U1)8U) | ((U4)0x01U << (U1)16U); /* SubType & Ack & LogicalBlock */
        u4_tp_nack_data[1] = (U4)0x00U; /* Reserve */
        /* iVDshWrite */
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_nack_data[0], (U2)FWUSH_RES_WORDS);
        u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = FWUSH_REQ_SUBTYPE_NA;  /* Reset previous subtype */
        break;
    case (U1)FWUSH_REQ_SUBTYPE_RUN:
        /* make write data (Subtype 17h, Ack NG) */
        u4_tp_nack_data[0] = (U4)(0x17U | ((U4)FWUSH_ACK_NG << (U1)8U) | ((U4)0x01U << (U1)16U)
                           | (U4)((u2_s_fwush_run_offset_prev & (U2)0xFF00U) << (U1)16U)); /* SubType & Ack & LogicalBlock & offset(high) */
        u4_tp_nack_data[1] = (U4)((u2_s_fwush_run_offset_prev & (U2)0x00FFU)) | ((U4)0x04U << (U1)8U) | ((U4)0x00U << (U1)16U); /* offset(low) & length(high) & length (low) */
        /* iVDshWrite */
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_nack_data[0], (U2)FWUSH_RES_WORDS);
        u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = FWUSH_REQ_SUBTYPE_NA;  /* Reset previous subtype */
        break;
    case (U1)FWUSH_REQ_SUBTYPE_VERI:
        /* make write data (Subtype 18h, Ack NG) */
        u4_tp_nack_data[0] = (U4)0x19U | ((U4)FWUSH_ACK_NG << (U1)8U) | ((U4)0x01U << (U1)16U); /* SubType & Ack & LogicalBlock */
        u4_tp_nack_data[1] = (U4)0x00U; /* Reserve */
        /* iVDshWrite */
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_nack_data[0], (U2)FWUSH_RES_WORDS);
        u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = FWUSH_REQ_SUBTYPE_NA;  /* Reset previous subtype */
        break;
    case (U1)FWUSH_REQ_SUBTYPE_ACT:
        /* make write data (Subtype 38h, Ack NG) */
        u4_tp_nack_data[0] = (U4)0x38U | ((U4)FWUSH_ACK_NG << (U1)8U); /* SubType & Ack */
        u4_tp_nack_data[1] = (U4)0x00U; /* Reserve */
        /* iVDshWrite */
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_nack_data[0], (U2)FWUSH_RES_WORDS);
        u1_sp_fwush_header[FWUSH_REQ_SUBTYPE_OFFSET] = FWUSH_REQ_SUBTYPE_NA;  /* Reset previous subtype */
        break;
    default:
        break;
    }
}

static U1     u1_s_FwushMakePrepData(U4 * u4_ap_adr, U4 * u4_ap_length, U4 * u4_ap_crc)
{
    U4   u4_t_adr;
    U1 * u1_tp_adr;
    U1   u1_t_ret;

    /* Calculate CRC */
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

static U1     u1_s_FwushMakeRunData(U4 * u4_ap_adr, U2 * u2_ap_ofst)
{
    U1   u1_t_ret;

    u1_t_ret = u1_s_FwushReadData((U2)FWUSH_REQ_D_WORDS, u4_ap_adr);
    *u2_ap_ofst = ((U2)u1_sp_fwush_header[FWUSH_REQ_RUN_BLKOFS_OFFSET + 1]) | 
                  ((U2)u1_sp_fwush_header[FWUSH_REQ_RUN_BLKOFS_OFFSET] << (U2)8U);
    return(u1_t_ret);
}

static U1       u1_s_FwushReadHeader(U1 * u1_ap_ptr)
{
    U4  u4_tp_data[FWUSH_REQ_H_WORDS];
    U1  u1_t_read_ok;
    U1  u1_t_ret;
    U2  u2_t_idx;

    u1_t_ret = (U1)FALSE;
    u1_t_read_ok = u1_g_iVDshReabyDid(IVDSH_DID_REA_FWUPXREQ_H, &u4_tp_data[0], (U2)FWUSH_REQ_H_WORDS);
    if(u1_t_read_ok != (U1)IVDSH_NO_REA){
        for(u2_t_idx = 0U; u2_t_idx < (U2)FWUSH_REQ_H_SIZE; u2_t_idx++){
            u1_ap_ptr[u2_t_idx] = (U1)(u4_tp_data[u2_t_idx / (U1)4U] >> ((U1)8U * (u2_t_idx % (U1)4U)) & (U1)0xFFU);
        }
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

static U1        u1_s_FwushReadData(U2 u2_a_length, U4* u4_ap_reqadr)
{
    U1  u1_t_read_ok;
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    /* get request data */
    u1_t_read_ok = u1_g_iVDshReabyDid(IVDSH_DID_REA_FWUPXREQ_D, u4_ap_reqadr, (U2)FWUSH_REQ_D_WORDS);
    if(u1_t_read_ok != (U1)IVDSH_NO_REA && u4_ap_reqadr != vdp_PTR_NA){
        u1_t_ret = (U1)TRUE;
    }
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
/*                                                                                                                                   */
/*                                                                                                                                   */
/* * KI   = Kanji Ito, Denso Techno                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
