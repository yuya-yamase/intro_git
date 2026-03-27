/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* FW Update State Handler - Internal Header                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef FWUSH_INTERNAL_H
#define FWUSH_INTERNAL_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "fwush.h"

#include "ivdsh.h"
#include "memfill_u1.h"
#include "memfill_u4.h"
#include "nvmc_mgr.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

typedef struct {
    U1 u1_next_main_state;
    U1 u1_next_sub_state;
    void (*fp_handler_func)(void);
} ST_FWUSH_TRANSITION_ENTRY;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Shared Variable Declarations (defined in fwush.c)                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U1 u1_g_fwush_state_main;
extern U1 u1_g_fwush_state_sub;

extern U1 u1_g_fwupx_req_seqcnt_pre;
extern U1 u1_g_fwupx_res_seqcnt;

extern U1 u1_g_fwush_abort;
extern U1 u1_g_fwush_error_log;

extern U1 u1_g_fwush_seq_progress;
extern U4 u4_g_fwush_fswa_stat;
extern U2 u2_g_fwush_veri_stat;
extern U1 u1_g_fwush_veri_target;

/* PREP state data */
extern U4 u4_g_fwush_prep_data_crc;

/* RUN state data */
extern U2 u2_g_fwush_run_ofst;

/* Request header buffer */
extern U1 u1_gp_fwush_header[FWUSH_REQ_H_SIZE];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes (fwush_evt.c)                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U1 u1_g_FwushDetectEvent(void);
extern U1 u1_g_FwushMapMemAccErrorToAck(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes (fwush.c)                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U1   u1_g_FwushReadHeader(U1 * u1_ap_ptr);
extern U1   u1_g_FwushReadData(U4* u4_ap_adr);
extern void vd_g_FwushMakeResData(U1 u1_a_subtype_res, U1 u1_a_response);
extern U1   u1_g_FwushMakeRunData(U4 * u4_ap_adr, U2 * u2_ap_ofst);
extern void vd_g_FwushAbort(void);
extern void vd_g_FwushUpdateSeqProgress(U1 u1_a_progress_bit);
extern void vd_g_FwushResetSeqProgress(void);
extern U1   u1_g_FwushGetFswaStat(void);
extern void vd_g_FwushUpdateFswaStat(void);
extern void vd_g_FwushResetFswaStat(void);
extern void vd_g_FwushUpdateVeriStat(U1 u1_t_veri_target, U1 u1_t_veri_comp);
extern void vd_g_FwushResetVeriStat(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  State Transition Table (defined in fwush_stm.c)                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_FWUSH_TRANSITION_ENTRY stp_gp3_FWUSH_STM[FWUSH_MAIN_STATE_MAX]
                                                        [FWUSH_SUB_STATE_MAX ]
                                                        [FWUSH_EVENT_MAX     ];

#endif /* FWUSH_INTERNAL_H */
/*===================================================================================================================================*/
