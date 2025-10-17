/* 1.2.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota Diag on CAN XID / Message Authentication                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_XID_MA_C_MAJOR                   (1U)
#define TYDOCAN_XID_MA_C_MINOR                   (2U)
#define TYDOCAN_XID_MA_C_PATCH                   (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "tydocan_xid_ma_cfg_private.h"
#include "oxdocan_aubif.h"

#include "Csm.h"

#include "oxdocan_aubif_ma.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_XID_MA_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_xid_ma.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (TYDOCAN_XID_MA_C_MAJOR != OXDOCAN_AUBIF_MA_H_MAJOR)
#error "tydocan_xid_ma.c and oxdocan_aubif_ma.h : source and header files are inconsistent!"
#endif

#ifdef TYDOCAN_XID_MA_CFG_H
#if ((TYDOCAN_XID_MA_C_MAJOR != TYDOCAN_XID_MA_CFG_H_MAJOR) || \
     (TYDOCAN_XID_MA_C_MINOR != TYDOCAN_XID_MA_CFG_H_MINOR) || \
     (TYDOCAN_XID_MA_C_PATCH != TYDOCAN_XID_MA_CFG_H_PATCH))
#error "tydocan_xid_ma.c and tydocan_xid_ma_cfg_private.h : source and header files are inconsistent!"
#endif
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*      1234567890123456789012345678901 */
#define TYDC_MAK_UV_EAS_CHK_SES                  (0x01U)  /* Session Transition Event */
#define TYDC_MAK_UV_EAS_CHK_TOUT                 (0x02U)

#define TYDC_MAK_UV_ACK_INA                      (0x00U)
#define TYDC_MAK_UV_ACK_SUC                      (0x04U)
#define TYDC_MAK_UV_ACK_FAI                      (0x08U)

#define TYDC_MAK_UV_NUM_CTRL                     (4U)
#define TYDC_MAK_UV_CTRL_STA                     (0U)
#define TYDC_MAK_UV_CTRL_RUN                     (1U)
#define TYDC_MAK_UV_CTRL_FIN                     (2U)
#define TYDC_MAK_UV_CTRL_INA                     (3U)

#define TYDC_MAK_UV_ACT_TO_ACT                   (0U)
#define TYDC_MAK_UV_ACT_TO_FIN                   (1U)
#define TYDC_MAK_UV_ACT_TO_SUC                   (2U)
#define TYDC_MAK_UV_ACT_TO_FAI                   (3U)
#define TYDC_MAK_UV_ACT_STA                      (4U)
#define TYDC_MAK_UV_ACT_RUN                      (5U)
#define TYDC_MAK_UV_ACT_FIN                      (6U)

#define TYDC_MAK_UV_NUM_STM                      (48U)  /* TYDC_MAK_UV_NUM_CTRL(4U) *         */
                                                        /* TYDC_MAK_UV_EAS_CHK_MAX(12) = 48U  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_MAK_SU_FAC_MAX                      (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_MAK_UV_RID_D904                     (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_RID_D904_ANS_INA                    (0x00U)
#define TYDC_RID_D904_ANS_RUN                    (0x01U)
#define TYDC_RID_D904_ANS_SUC                    (0x02U)
#define TYDC_RID_D904_ANS_FAI                    (0x03U)
     
#define TYDC_RID_D904_ANS_RINFO                  (0x03U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_M1_KEY_ID_POS                       (15U)    /* The position of the KEYID(SHE-ID and Auth-ID) in the M1 data */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_CSM_REQ_NWORD                       (32U)    /* 64 byte x 2                     */
#define TYDC_CSM_REQ_0                           (0U)
#define TYDC_CSM_REQ_1                           (16U)
#define TYDC_CSM_RSL_NWORD                       (12U)    /* 48 byte                         */

#define TYDC_CSM_UP_REQ_NBYTE                    (64U)
#define TYDC_CSM_UP_RSL_NBYTE                    (48U)
#define TYDC_CSM_UP_KEYSET_ELEID                 (1U)
#define TYDC_CSM_UP_KEYGET_ELEID                 (2U)

typedef struct{
    U4        u4p_req[TYDC_CSM_REQ_NWORD];
    U4        u4p_rsl[TYDC_CSM_RSL_NWORD];
    U4        u4_rsl_nbyte;

    U1        u1_req_sel;
}ST_TYDC_CSM_IO;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_XID_MA_CFG_H
static ST_TYDC_CSM_IO        st_s_tydc_csm_io; 

static U2                    u2_s_tydc_mak_uv_tm_elpsd;                     /* Key Update/Verify Elapsed       */
static U1                    u1_s_tydc_mak_uv_ctrl;                         /* Key Update/Verify Control       */
static U1                    u1_s_tydc_mak_uv_rid;

static U1                    u1_s_tydc_mak_uv_ack;                          /* Key Update/Verify Ack           */
static U1                    u1_s_tydc_mak_su_ack;                          /* Key Single Update Result        */
static U1                    u1_s_tydc_mak_su_facnt;                        /* Key Single Update Failure Count */
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_XID_MA_CFG_H
static void    vd_s_TydcMakUvAct_ToAct(void);
static void    vd_s_TydcMakUvAct_ToFin(void);
static void    vd_s_TydcMakUvAct_ToSuc(void);
static void    vd_s_TydcMakUvAct_ToFai(void);
static void    vd_s_TydcMakUvAct_Sta(void);

static void    vd_s_TydcXidMaUpdtStart(void);

#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_XID_MA_CFG_H
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANMakInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANXidMaInit(void)
{
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_req[0]), (U4)0U, (U4)TYDC_CSM_REQ_NWORD);
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)0U, (U4)TYDC_CSM_RSL_NWORD);

    st_s_tydc_csm_io.u4_rsl_nbyte = (U4)0U;
    st_s_tydc_csm_io.u1_req_sel   = (U1)0U;

    u2_s_tydc_mak_uv_tm_elpsd     = (U2)U2_MAX;
    u1_s_tydc_mak_uv_ctrl         = (U1)TYDC_MAK_UV_CTRL_INA;
    u1_s_tydc_mak_uv_rid          = (U1)U1_MAX;

    u1_s_tydc_mak_uv_ack          = (U1)TYDC_MAK_UV_ACK_INA;
    u1_s_tydc_mak_su_ack          = (U1)TYDC_MAK_UV_ACK_INA;
    u1_s_tydc_mak_su_facnt        = (U1)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANXidMaMainTask(const ST_OXDC_REQ * st_ap_REQ)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANXidMaMainTask(const ST_OXDC_REQ * st_ap_REQ)
{
    static const U2               u2_sp_TYDC_MAK_UV_TOUT[] = {
        /* TYDC_MAK_UV_RID_D904 (0U) */
        (U2)600U  / (U2)OXDC_MAIN_TICK,   /* TYDC_MAK_UV_CTRL_STA (0U) */
        (U2)600U  / (U2)OXDC_MAIN_TICK,   /* TYDC_MAK_UV_CTRL_RUN (1U) */
        (U2)0U,                           /* TYDC_MAK_UV_CTRL_FIN (2U) */
        (U2)0U,                           /* TYDC_MAK_UV_CTRL_INA (3U) */
    };

    static const U1               u1_sp_TYDC_MAK_UV_STM[] = {
        /* TYDC_MAK_UV_RID_D904 (0U) */
        (U1)TYDC_MAK_UV_ACT_STA,    (U1)TYDC_MAK_UV_ACT_RUN,    (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
    };

    static void ( * const         fp_sp_vd_TYDC_MAK_UV_ACT[])(void) = {
        &vd_s_TydcMakUvAct_ToAct,     /* TYDC_MAK_UV_ACT_TO_ACT (0U) */
        &vd_s_TydcMakUvAct_ToFin,     /* TYDC_MAK_UV_ACT_TO_FIN (1U) */
        &vd_s_TydcMakUvAct_ToSuc,     /* TYDC_MAK_UV_ACT_TO_SUC (2U) */
        &vd_s_TydcMakUvAct_ToFai,     /* TYDC_MAK_UV_ACT_TO_FAI (3U) */
        &vd_s_TydcMakUvAct_Sta,       /* TYDC_MAK_UV_ACT_STA    (4U) */
                                      /* TYDC_MAK_UV_ACT_RUN    (5U) */
                                      /* TYDC_MAK_UV_ACT_FIN    (6U) */
    };

    U2                            u2_t_tout;
    U2                            u2_t_act;
    U1                            u1_t_ign_on;
    U1                            u1_t_eas_chk;

    u1_t_ign_on = st_ap_REQ->u1_eom_aft & (U1)OXDC_EOM_IGN_ON;
    if((u1_t_ign_on           != (U1)OXDC_EOM_IGN_ON     ) ||
       (u1_s_tydc_mak_uv_ctrl >  (U1)TYDC_MAK_UV_CTRL_INA) ||
       (u1_s_tydc_mak_uv_ack  >  (U1)TYDC_MAK_UV_ACK_FAI )){

        u1_s_tydc_mak_uv_ctrl = (U1)TYDC_MAK_UV_CTRL_INA;
    }
    else{

        if(u2_s_tydc_mak_uv_tm_elpsd < (U2)U2_MAX){
            u2_s_tydc_mak_uv_tm_elpsd++;
        }

        u1_t_eas_chk = u1_s_tydc_mak_uv_ack & ((U1)TYDC_MAK_UV_ACK_SUC | (U1)TYDC_MAK_UV_ACK_FAI);
        if(st_ap_REQ->u1_ses_bfr != st_ap_REQ->u1_ses_aft){
            u1_t_eas_chk |= (U1)TYDC_MAK_UV_EAS_CHK_SES;
        }

        if(u1_s_tydc_mak_uv_rid > (U1)TYDC_MAK_UV_RID_D904){
            u2_t_tout = (U2)u1_s_tydc_mak_uv_ctrl;
            u2_t_act  = (U2)0U;
        }
        else{
            u2_t_tout = ((U2)u1_s_tydc_mak_uv_rid * (U2)TYDC_MAK_UV_NUM_CTRL) + (U2)u1_s_tydc_mak_uv_ctrl;
            u2_t_act  = (U2)u1_s_tydc_mak_uv_rid * (U2)TYDC_MAK_UV_NUM_STM;
        }

        u2_t_tout = u2_sp_TYDC_MAK_UV_TOUT[u2_t_tout];
        if(u2_s_tydc_mak_uv_tm_elpsd >= u2_t_tout){
            u1_t_eas_chk |= (U1)TYDC_MAK_UV_EAS_CHK_TOUT;
        }

        u2_t_act += (((U2)u1_t_eas_chk * (U2)TYDC_MAK_UV_NUM_CTRL) + (U2)u1_s_tydc_mak_uv_ctrl);
        u2_t_act  = (U2)u1_sp_TYDC_MAK_UV_STM[u2_t_act];
        if(u2_t_act < (U2)TYDC_MAK_UV_ACT_RUN){
            (* fp_sp_vd_TYDC_MAK_UV_ACT[u2_t_act])();
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_A901(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_A901(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    U1                            u1_t_ok;
    U1                            u1_t_proc;

    u1_t_ok = u1_g_TyDoCANXidMaCfgSafeKeyNum(u1_ap_ans);
    if(u1_t_ok == (U1)TRUE){
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutCorchk_D904(const U1 u1_a_SUBF, const U1 * u1_ap_COR)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutCorchk_D904(const U1 u1_a_SUBF, const U1 * u1_ap_COR)
{
    U1                            u1_t_proc;

    u1_t_proc = (U1)OXDC_SAL_PROC_RUN;

    if((u1_a_SUBF              == (U1)OXDC_ROUT_SUBF_START) &&
       (u1_s_tydc_mak_uv_ctrl  == (U1)TYDC_MAK_UV_CTRL_FIN) &&
       (u1_s_tydc_mak_su_facnt <  (U1)TYDC_MAK_SU_FAC_MAX )){

        if(u1_ap_COR[TYDC_M1_KEY_ID_POS] == (U1)0x41U){        /* if(M1 == MAC KEY(0x40) / MASTER_KEY(0x01)) */
            vd_g_MemcpyU1((U1 *)&(st_s_tydc_csm_io.u4p_req[0]), &u1_ap_COR[0], (U4)TYDC_CSM_UP_REQ_NBYTE);
        }
        else{
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        }
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutStart_D904(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutStart_D904(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)
{
    U1                            u1_t_proc;

    if((u1_s_tydc_mak_uv_ctrl  == (U1)TYDC_MAK_UV_CTRL_FIN) &&
       (u1_s_tydc_mak_su_facnt <  (U1)TYDC_MAK_SU_FAC_MAX )){

        st_s_tydc_csm_io.u1_req_sel = (U1)0U;

        u2_s_tydc_mak_uv_tm_elpsd   = (U2)0U;
        u1_s_tydc_mak_uv_ctrl       = (U1)TYDC_MAK_UV_CTRL_STA;
        u1_s_tydc_mak_uv_rid        = (U1)TYDC_MAK_UV_RID_D904;

        u1_s_tydc_mak_uv_ack        = (U1)TYDC_MAK_UV_ACK_INA;
        u1_s_tydc_mak_su_ack        = (U1)TYDC_MAK_UV_ACK_INA;

        vd_s_TydcXidMaUpdtStart();

        u1_ap_ans[0] = (U1)TYDC_RID_D904_ANS_RINFO;
        u1_ap_ans[1] = (U1)TYDC_RID_D904_ANS_RUN;
        vd_g_MemfillU1(&u1_ap_ans[2], (U1)0U, (U4)TYDC_CSM_UP_RSL_NBYTE);

        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else if(u1_s_tydc_mak_uv_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_24;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutRslt_D904(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutRslt_D904(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)
{
    U1                            u1_t_proc;

    if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D904){
        u1_ap_ans[0] = (U1)TYDC_RID_D904_ANS_RINFO;
        u1_ap_ans[1] = (U1)TYDC_RID_D904_ANS_RUN;
        vd_g_MemfillU1(&u1_ap_ans[2], (U1)0U, (U4)TYDC_CSM_UP_RSL_NBYTE);
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_21;
    }
    else if(u1_s_tydc_mak_su_ack == (U1)TYDC_MAK_UV_ACK_SUC){
        u1_ap_ans[0] = (U1)TYDC_RID_D904_ANS_RINFO;
        u1_ap_ans[1] = (U1)TYDC_RID_D904_ANS_SUC;
        vd_g_MemcpyU1(&u1_ap_ans[2], (const U1 * )&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)TYDC_CSM_UP_RSL_NBYTE);
        vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)0U, (U4)TYDC_CSM_RSL_NWORD);
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else if(u1_s_tydc_mak_su_ack == (U1)TYDC_MAK_UV_ACK_FAI){
        u1_ap_ans[0] = (U1)TYDC_RID_D904_ANS_RINFO;
        u1_ap_ans[1] = (U1)TYDC_RID_D904_ANS_FAI;
        vd_g_MemfillU1(&u1_ap_ans[2], (U1)0U, (U4)TYDC_CSM_UP_RSL_NBYTE);
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else{
        u1_ap_ans[0] = (U1)TYDC_RID_D904_ANS_RINFO;
        u1_ap_ans[1] = (U1)TYDC_RID_D904_ANS_INA;
        vd_g_MemfillU1(&u1_ap_ans[2], (U1)0U, (U4)TYDC_CSM_UP_RSL_NBYTE);
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_24;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  void   vd_g_TyDoCANAubIfCsmAck(uint32 u4_a_jobId, Crypto_ResultType u1_a_RSLT)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_TyDoCANAubIfCsmAck(uint32 u4_a_jobId, Crypto_ResultType u1_a_RSLT)
{
    if(u1_a_RSLT == (U1)E_OK){
        u1_s_tydc_mak_uv_ack = (U1)TYDC_MAK_UV_ACK_SUC;
    }
    else{
        u1_s_tydc_mak_uv_ack = (U1)TYDC_MAK_UV_ACK_FAI;
    }
}
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */
/*===================================================================================================================================*/
/*  void   vd_g_TyDoCANAubIfCsmKeyAck(uint32 u4_a_jobId, Crypto_ResultType u1_a_RSLT)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_TyDoCANAubIfCsmKeyAck(uint32 u4_a_jobId, Crypto_ResultType u1_a_RSLT)
{
    U1                            u1_t_csm;

    u1_t_csm = (U1)E_NOT_OK;

#ifdef TYDOCAN_XID_MA_CFG_H
    if(u1_a_RSLT == (U1)E_OK){
        u1_t_csm = Csm_KeyElementGet ((U4)CsmConf_CsmKey_CsmKey01_MacKey,
                                      (U4)TYDC_CSM_UP_KEYGET_ELEID,
                                      (U1 *)&(st_s_tydc_csm_io.u4p_rsl[0]),
                                      (U4 *)&(st_s_tydc_csm_io.u4_rsl_nbyte));
    }
    if(u1_t_csm == (U1)E_OK){
        u1_s_tydc_mak_uv_ack = (U1)TYDC_MAK_UV_ACK_SUC;
    }
    else{
        u1_s_tydc_mak_uv_ack = (U1)TYDC_MAK_UV_ACK_FAI;
    }
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */
}
#ifdef TYDOCAN_XID_MA_CFG_H
/*===================================================================================================================================*/
/*  static void    vd_s_TydcMakUvAct_ToAct(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcMakUvAct_ToAct(void)
{
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_req[0]), (U4)0U, (U4)TYDC_CSM_REQ_NWORD);
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)0U, (U4)TYDC_CSM_RSL_NWORD);

    st_s_tydc_csm_io.u1_req_sel = (U1)0U;

    u2_s_tydc_mak_uv_tm_elpsd   = (U2)U2_MAX;
    u1_s_tydc_mak_uv_ctrl       = (U1)TYDC_MAK_UV_CTRL_FIN;
    u1_s_tydc_mak_uv_rid        = (U1)U1_MAX;

    u1_s_tydc_mak_uv_ack        = (U1)TYDC_MAK_UV_ACK_INA;
    u1_s_tydc_mak_su_ack        = (U1)TYDC_MAK_UV_ACK_INA;
    u1_s_tydc_mak_su_facnt      = (U1)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcMakUvAct_ToFin(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcMakUvAct_ToFin(void)
{
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_req[0]), (U4)0U, (U4)TYDC_CSM_REQ_NWORD);
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)0U, (U4)TYDC_CSM_RSL_NWORD);

    st_s_tydc_csm_io.u1_req_sel = (U1)0U;

    u2_s_tydc_mak_uv_tm_elpsd   = (U2)U2_MAX;
    u1_s_tydc_mak_uv_ctrl       = (U1)TYDC_MAK_UV_CTRL_FIN;
    u1_s_tydc_mak_uv_rid        = (U1)U1_MAX;

    u1_s_tydc_mak_uv_ack        = (U1)TYDC_MAK_UV_ACK_INA;
 /* u1_s_tydc_mak_su_ack        = (U1)TYDC_MAK_UV_ACK_INA; */
 /* u1_s_tydc_mak_su_facnt      = (U1)0U; */
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcMakUvAct_ToSuc(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcMakUvAct_ToSuc(void)
{
    if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D904){
        u1_s_tydc_mak_su_ack    = (U1)TYDC_MAK_UV_ACK_SUC;
        vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_req[0]), (U4)0U, (U4)TYDC_CSM_REQ_NWORD);
    }
    else{
        /* Do Nothing */
    }

    st_s_tydc_csm_io.u1_req_sel = (U1)0U;

    u2_s_tydc_mak_uv_tm_elpsd   = (U2)U2_MAX;
    u1_s_tydc_mak_uv_ctrl       = (U1)TYDC_MAK_UV_CTRL_FIN;
    u1_s_tydc_mak_uv_rid        = (U1)U1_MAX;

    u1_s_tydc_mak_uv_ack        = (U1)TYDC_MAK_UV_ACK_INA;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcMakUvAct_ToFai(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcMakUvAct_ToFai(void)
{
    if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D904){

        u1_s_tydc_mak_su_ack    = (U1)TYDC_MAK_UV_ACK_FAI;
        if(u1_s_tydc_mak_su_facnt < (U1)U1_MAX){
            u1_s_tydc_mak_su_facnt++;
        }
    }
    else{
        /* Do Nothing */
    }

    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_req[0]), (U4)0U, (U4)TYDC_CSM_REQ_NWORD);
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)0U, (U4)TYDC_CSM_RSL_NWORD);

    st_s_tydc_csm_io.u1_req_sel = (U1)0U;

    u2_s_tydc_mak_uv_tm_elpsd   = (U2)U2_MAX;
    u1_s_tydc_mak_uv_ctrl       = (U1)TYDC_MAK_UV_CTRL_FIN;
    u1_s_tydc_mak_uv_rid        = (U1)U1_MAX;

    u1_s_tydc_mak_uv_ack        = (U1)TYDC_MAK_UV_ACK_INA;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcMakUvAct_Sta(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcMakUvAct_Sta(void)
{
    if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D904){
        vd_s_TydcXidMaUpdtStart();
    }
    else{
        /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcXidMaUpdtStart(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcXidMaUpdtStart(void)
{
    const U1 *                    u1_tp_MX;

    U4                            u4_t_cpu_md;
    U1                            u1_t_csm;

    u4_t_cpu_md = u4_g_CPUM_PRIV();  /* CPU mode = privilege   */

    if(st_s_tydc_csm_io.u1_req_sel == (U1)0U){
        u1_tp_MX = (const U1 *)&(st_s_tydc_csm_io.u4p_req[TYDC_CSM_REQ_0]);
    }
    else{
        u1_tp_MX = (const U1 *)&(st_s_tydc_csm_io.u4p_req[TYDC_CSM_REQ_1]);
    }

    st_s_tydc_csm_io.u4_rsl_nbyte = (U4)TYDC_CSM_UP_RSL_NBYTE;
    u1_t_csm = Csm_KeyElementSet((U4)CsmConf_CsmKey_CsmKey01_MacKey,
                                 (U4)TYDC_CSM_UP_KEYSET_ELEID,
                                 u1_tp_MX,
                                 (U4)TYDC_CSM_UP_REQ_NBYTE);

    if(u1_t_csm == (U1)E_OK){
        u1_t_csm = Csm_JobKeySetValid(CsmConf_CsmJob_CsmJob18_KeySetValid_MacKey, CsmConf_CsmKey_CsmKey01_MacKey);

        if(u1_t_csm == (U1)E_OK){
            u1_s_tydc_mak_uv_ctrl = (U1)TYDC_MAK_UV_CTRL_RUN;
        }
    }

    vd_g_CPUM_RSTR(u4_t_cpu_md);     /* CPU mode = u4_t_cpu_md */
}
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     7/18/2019  TN       New.                                                                                               */
/*  1.1.0    10/10/2019  TN       tydocan_xid service application interface was optimized.                                           */
/*  1.2.0    11/ 1/2019  TN       Bug Fix : Routine ID 0x100E and 0x100F could be executed during same IG cycle.                     */
/*  1.2.1     8/22/2020  HK       Fix selfcheck and codereview cs issue.                                                             */
/*  1.2.2     4/ 2/2021  HK       QAC warnigs were fixed.                                                                            */
/*  1.2.3     9/ 9/2021  TN       Redundant typecast were delete in Csm_Ab_SymKeyUpdateSc()                                          */
/*                       HK       QAC warnigs were fixed.                                                                            */
/*  1.2.4    12/14/2022  MI       Fix Phase6(XID:A901, D902, D903, D904)                                                             */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * HK   = Hayato Kanamori, DENSO Create                                                                                           */
/*  * MI   = Masahiko Izumi, DENSO                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
