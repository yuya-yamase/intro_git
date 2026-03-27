/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* FW Update State Handler - Main (Init / MainTask / Request I/O / Abort / NVM utilities)                                            */
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
#include "fwush_internal.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1 u1_g_fwush_state_main;
U1 u1_g_fwush_state_sub;

U1 u1_g_fwupx_req_seqcnt_pre;
U1 u1_g_fwupx_res_seqcnt;

U1 u1_g_fwush_abort;
U1 u1_g_fwush_error_log;

U1 u1_g_fwush_seq_progress;
U4 u4_g_fwush_fswa_stat;
U2 u2_g_fwush_veri_stat;
U1 u1_g_fwush_veri_target;

/* PREP state data */
U4 u4_g_fwush_prep_data_crc;

/* RUN state data */
U2 u2_g_fwush_run_ofst;

/* Request header buffer */
U1 u1_gp_fwush_header[FWUSH_REQ_H_SIZE];
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
    u1_g_fwush_state_main       = (U1)FWUSH_MAIN_STATE_PREP;
    u1_g_fwush_state_sub        = (U1)FWUSH_SUB_STATE_WAITING;
    u1_g_fwupx_req_seqcnt_pre   = (U1)0x00U;
    u1_g_fwupx_res_seqcnt       = (U1)0x00U;
    u1_g_fwush_abort            = (U1)FALSE;
    u1_g_fwush_error_log        = (U1)FWUSH_ACK_OK;
    u4_g_fwush_prep_data_crc    = (U4)0U;
    u2_g_fwush_run_ofst         = (U2)0xFFFFU;
    u1_g_fwush_veri_target      = (U1)FWUSH_VERI_LB_NONE;
    u1_t_nvm_chk = u1_g_Nvmc_ReadU1withSts((U2)NVMCID_U1_FWUSH_SEQ_PROGRESS, &u1_g_fwush_seq_progress);
    if(u1_t_nvm_chk != (U1)NVMC_STATUS_COMP) {
        /* If read error, reset progress */
        u1_g_fwush_seq_progress = (U1)FWUSH_PROGRESS_INIT;
    }
    u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts((U2)NVMCID_U4_FWUSH_FSWASTAT_0_INFO, &u4_g_fwush_fswa_stat);
    if(u1_t_nvm_chk != (U1)NVMC_STATUS_COMP) {
        /* If read error, reset progress */
        u4_g_fwush_fswa_stat = (U4)FWUSH_FSWA_STS_INIT;
    }
    u1_t_nvm_chk = u1_g_Nvmc_ReadU2withSts((U2)NVMCID_U2_FWUSH_VERIFY_LBN_COMP, &u2_g_fwush_veri_stat);
    if(u1_t_nvm_chk != (U1)NVMC_STATUS_COMP) {
        /* If read error, reset progress */
        u2_g_fwush_veri_stat = (U2)FWUSH_VERI_LB_STAT_INIT;
    }

    /* Clear header buffer */
    vd_g_MemfillU1(&u1_gp_fwush_header[0], (U1)0U, (U4)FWUSH_REQ_H_SIZE);
    
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

    u1_t_state_main_crnt = u1_g_fwush_state_main;
    u1_t_state_sub_crnt  = u1_g_fwush_state_sub;

    /* 1. Event detection (reads header internally) */
    u1_t_event = u1_g_FwushDetectEvent();
    
    /* 2. Consult state transition table */
    stp_t_TRANSITION = &stp_gp3_FWUSH_STM[u1_t_state_main_crnt]
                                         [u1_t_state_sub_crnt ]
                                         [u1_t_event          ];

    /* 3. Execute Transition Event Handler */
    if(stp_t_TRANSITION->fp_handler_func != vdp_PTR_NA){
        stp_t_TRANSITION->fp_handler_func();
    }

    /* 4. Update state */
    u1_g_fwush_state_main = stp_t_TRANSITION->u1_next_main_state;
    u1_g_fwush_state_sub  = stp_t_TRANSITION->u1_next_sub_state;

    /* 5. Execute MemAcc task */
    vd_g_FwuMemAccMainTask();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Request Processing                                                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* U1 u1_g_FwushReadHeader(U1 * u1_ap_ptr)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 * u1_ap_ptr : Pointer to header buffer                                                                        */
/*  Return:         U1 : TRUE if header read successfully, FALSE otherwise                                                           */
/*===================================================================================================================================*/
U1 u1_g_FwushReadHeader(U1 * u1_ap_ptr)
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
/* U1 u1_g_FwushReadData(U4* u4_ap_adr)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U4* u4_ap_adr : Pointer to store read address                                                                    */
/*  Return:         U1 : TRUE if data read successfully, FALSE otherwise                                                             */
/*===================================================================================================================================*/
U1 u1_g_FwushReadData(U4* u4_ap_adr)
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
/* void vd_g_FwushMakeResData(U1 u1_a_subtype, U1 u1_a_response)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_subtype : Response subtype                                                                               */
/*                  U1 u1_a_response : Response code                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwushMakeResData(U1 u1_a_subtype, U1 u1_a_response)
{
    U4  u4_tp_res_data[FWUSH_RES_WORDS];

    if(u1_g_fwupx_res_seqcnt < (U1)0xFFU){
        u1_g_fwupx_res_seqcnt++;
    }
    else{
        u1_g_fwupx_res_seqcnt = (U1)0U;
    }
    vd_g_MemfillU4(&u4_tp_res_data[0], (U4)0U, (U4)FWUSH_RES_WORDS);

    u4_tp_res_data[0] = (U4)(u1_a_subtype | ((U4)u1_a_response << (U1)8U) | ((U4)0x01U << (U1)16U)
                      | (U4)((u2_g_fwush_run_ofst & (U2)0xFF00U) << (U1)16U));
    u4_tp_res_data[1] = (U4)((u2_g_fwush_run_ofst & (U2)0x00FFU)) | ((U4)0x04U << (U1)8U) | ((U4)0x00U << (U1)16U)
                      | ((U4)u1_g_fwupx_res_seqcnt << (U1)24U);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_FWUPXRES, &u4_tp_res_data[0], (U2)FWUSH_RES_WORDS);
}

/*===================================================================================================================================*/
/* U1 u1_g_FwushMakeRunData(U4 * u4_ap_adr, U2 * u2_ap_ofst)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U4 * u4_ap_adr    : Pointer to store address                                                                     */
/*                  U2 * u2_ap_ofst   : Pointer to store block offset                                                                */
/*  Return:         U1 : TRUE if data created successfully, FALSE otherwise                                                          */
/*===================================================================================================================================*/
U1 u1_g_FwushMakeRunData(U4 * u4_ap_adr, U2 * u2_ap_ofst)
{
    U1   u1_t_ret;

    u1_t_ret = u1_g_FwushReadData(u4_ap_adr);
    *u2_ap_ofst = ((U2)u1_gp_fwush_header[FWUSH_REQ_RUN_BLKOFS_OFFSET + 1]) | 
                  ((U2)u1_gp_fwush_header[FWUSH_REQ_RUN_BLKOFS_OFFSET] << (U2)8U);
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/* void vd_g_FwushAbort(void)                                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwushAbort(void)
{
    /* Initialize state variables */
    u1_g_fwush_state_main       = (U1)FWUSH_MAIN_STATE_PREP;
    u1_g_fwush_state_sub        = (U1)FWUSH_SUB_STATE_WAITING;
    u1_g_fwush_abort            = (U1)FALSE;
    u1_g_fwush_error_log        = (U1)0x00U;
    u4_g_fwush_prep_data_crc    = (U4)0U;
    u2_g_fwush_run_ofst         = (U2)0xFFFFU;

    vd_g_FwushResetVeriStat();
    
    /* Clear header buffer */
    vd_g_MemfillU1(&u1_gp_fwush_header[0], (U1)0U, (U4)FWUSH_REQ_H_SIZE);
    
    /* Initialize FwuMemAcc */
    vd_g_FwuMemAccInit();
}

/*===================================================================================================================================*/
/* void vd_g_FwushUpdateSeqProgress(U1 u1_a_progress_bit)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_progress_bit : Progress bit to set                                                                       */
/*                      0x01U : MCU activate complete                                                                                */
/*                      0x02U : MCU validate complete                                                                                */
/*                      0x04U : MCU update complete                                                                                  */
/*                      0x08U : MCU cancel complete                                                                                  */
/*                      0x10U : MCU rollback complete                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwushUpdateSeqProgress(U1 u1_a_progress_bit)
{
    U1 u1_t_updated;

    /* OR the new progress bit with the cached value */
    u1_t_updated = u1_g_fwush_seq_progress | u1_a_progress_bit;

    /* Write only if changed */
    if(u1_t_updated != u1_g_fwush_seq_progress){
        u1_g_fwush_seq_progress = u1_t_updated;
        vd_g_Nvmc_WriteU1((U2)NVMCID_U1_FWUSH_SEQ_PROGRESS, u1_g_fwush_seq_progress);
    }
}

/*===================================================================================================================================*/
/* void vd_g_FwushResetSeqProgress(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwushResetSeqProgress(void)
{
    if(u1_g_fwush_seq_progress != (U1)FWUSH_PROGRESS_INIT){
        u1_g_fwush_seq_progress = (U1)FWUSH_PROGRESS_INIT;
        vd_g_Nvmc_WriteU1((U2)NVMCID_U1_FWUSH_SEQ_PROGRESS, u1_g_fwush_seq_progress);
    }
}

/*===================================================================================================================================*/
/* U1 u1_g_FwushGetFswaStat(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_FwushGetFswaStat(void)
{
    /* Same Address with CODEFLS_U4_REGADD_FSWASTAT_0 in CodeFls_Reg.h */
    return((U1)((*(volatile uint32 *)((uint32)0xFFA10000UL + 0x0A8UL) & (U1)FWUSH_FSWA_READ_POS)));
}

/*===================================================================================================================================*/
/* void vd_g_FwushUpdateFswaStat(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwushUpdateFswaStat(void)
{
    U4 u4_t_updated;

    u4_t_updated = (U4)0xFFFFFF00U | (U4)u1_g_FwushGetFswaStat();

    /* Write only if changed */
    if(u4_t_updated != u4_g_fwush_fswa_stat){
        u4_g_fwush_fswa_stat = u4_t_updated;
        vd_g_Nvmc_WriteU4((U2)NVMCID_U4_FWUSH_FSWASTAT_0_INFO, u4_g_fwush_fswa_stat);
    }
}

/*===================================================================================================================================*/
/* void vd_g_FwushResetFswaStat(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwushResetFswaStat(void)
{
    if(u4_g_fwush_fswa_stat != (U4)FWUSH_FSWA_STS_INIT){
        u4_g_fwush_fswa_stat = (U4)FWUSH_FSWA_STS_INIT;
        vd_g_Nvmc_WriteU4((U2)NVMCID_U4_FWUSH_FSWASTAT_0_INFO, u4_g_fwush_fswa_stat);
    }
}

/*===================================================================================================================================*/
/* void vd_g_FwushUpdateVeriStat(U1 u1_t_veri_target, U1 u1_t_veri_comp)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_t_veri_target : target Logical Block                                                                          */
/*                  u1_t_veri_comp   : verification completion status                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwushUpdateVeriStat(U1 u1_t_veri_target, U1 u1_t_veri_comp)
{
    U2 u2_t_updated;

    u2_t_updated = (U2)(u2_g_fwush_veri_stat | ((u1_t_veri_target << (U1)8U) | u1_t_veri_comp));

    /* Write only if changed */
    if(u2_t_updated != u2_g_fwush_veri_stat){
        u2_g_fwush_veri_stat = u2_t_updated;
        vd_g_Nvmc_WriteU2((U2)NVMCID_U2_FWUSH_VERIFY_LBN_COMP, u2_g_fwush_veri_stat);
    }
}

/*===================================================================================================================================*/
/* void vd_g_FwushResetVeriStat(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwushResetVeriStat(void)
{
    if(u2_g_fwush_veri_stat != (U2)FWUSH_VERI_LB_STAT_INIT){
        u2_g_fwush_veri_stat = (U2)FWUSH_VERI_LB_STAT_INIT;
        vd_g_Nvmc_WriteU2((U2)NVMCID_U2_FWUSH_VERIFY_LBN_COMP, u2_g_fwush_veri_stat);
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
/*  2.0.0    03/27/2026  KI       Split into fwush.c / fwush_evt.c / fwush_stm.c                                                    */
/*                                                                                                                                   */
/* * KI   = Kanji Ito, Denso Techno                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

