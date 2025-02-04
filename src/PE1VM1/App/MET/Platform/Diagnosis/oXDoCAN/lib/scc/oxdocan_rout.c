/* 1.0.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  SID 0x31 Routine Control                                                                                                         */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_ROUT_C_MAJOR                     (1U)
#define OXDOCAN_ROUT_C_MINOR                     (0U)
#define OXDOCAN_ROUT_C_PATCH                     (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "oxdocan_xid_cfg_private.h"

#include "Dcm.h"
#include "Dcm_Dsp_SID10_Cfg.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXDOCAN_ROUT_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "oxdocan_rout.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (OXDOCAN_ROUT_C_MAJOR != OXDOCAN_SAL_H_MAJOR)
#error "oxdocan_rout.c and oxdocan_sal.h : source and header files are inconsistent!"
#endif

#if (OXDOCAN_ROUT_C_MAJOR != OXDOCAN_XID_CFG_H_MAJOR)
#error "oxdocan_rout.c and oxdocan_xid_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_ROUT_SUBF                           (0U)
#define OXDC_ROUT_RID_HI                         (1U)
#define OXDC_ROUT_RID_LO                         (2U)
#define OXDC_ROUT_COR                            (3U)              /* Control Option Record */

#define OXDC_ROUT_LSB_RID_HI                     (8U)

#define OXDC_ROUT_SUBF_CHK                       (0x7fU)
#define OXDC_ROUT_SUBF_NO_ANS                    (0x80U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U2             u2_g_oxdc_rout_xid;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_oXdcRoutReqchk(const ST_OXDC_REQ * st_ap_REQ);

static U1      u1_s_oXdcRoutXidchk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcRoutSessionchk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcRoutSecuritychk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcRoutSubfchk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcRoutCorchk(const ST_OXDC_REQ * st_ap_REQ);

static void    vd_s_oXdcRoutProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans);

static U1      u1_s_oXdcRoutNoAnschk(const ST_OXDC_REQ * st_ap_REQ);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRoutInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRoutInit(void)
{
    u2_g_oxdc_rout_xid = (U2)U2_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRoutMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRoutMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    if(st_ap_REQ->u1_sid == (U1)OXDC_SID_31){

        if(st_ap_REQ->u2_tim_elpsd == (U2)0U){
            vd_s_oXdcRoutReqchk(st_ap_REQ);
        }

        if(u2_g_oxdc_rout_xid < u2_g_OXDC_ROUT_NUM_XID){
            vd_s_oXdcRoutProcRun(st_ap_REQ, st_ap_ans);
        }
        else if(st_ap_REQ->u2_tim_elpsd > (U2)0U){
            vd_g_oXDoCANAnsTx((U1)OXDC_SAL_PROC_NR_10, vdp_PTR_NA);
        }
        else{
            /* Do Nothing */
        }
    }
    else{
        u2_g_oxdc_rout_xid = (U2)U2_MAX;
    }
}
#ifdef OXDC_FUNC_ROUT_STOP
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRoutStop(const U1 u1_a_NEW)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRoutStop(const U1 u1_a_NEW)
{
    U1 ( *                   fp_t_u1_func)(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
    U2                       u2_t_lpcnt;
    U2                       u2_t_conf_ses;
    U2                       u2_t_ans_nbyte;
    U1                       u1_t_proc;

    for(u2_t_lpcnt = (U2)0U; u2_t_lpcnt < u2_g_OXDC_ROUT_NUM_XID; u2_t_lpcnt++){
        fp_t_u1_func  = st_gp_OXDC_ROUT_CFG[u2_t_lpcnt].fp_u1_STOP;
        u2_t_conf_ses = st_gp_OXDC_ROUT_XID[u2_t_lpcnt].u2_ses;
        u1_t_proc     = u1_g_oXDoCANCfgDidSessionBitChk(u1_a_NEW, u2_t_conf_ses);

        if((fp_t_u1_func != vdp_PTR_NA) &&
            (u1_t_proc   != (U1)E_OK  )){
            u2_t_ans_nbyte = (U2)0U;
            (void)(*fp_t_u1_func)((U1 *)vdp_PTR_NA, (U2)0U, &u2_t_ans_nbyte);
        }
    }
}
#endif
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcRoutReqchk(const ST_OXDC_REQ * st_ap_REQ)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static void    vd_s_oXdcRoutReqchk(const ST_OXDC_REQ * st_ap_REQ)
{
    static U1 ( * const      fp_sp_u1_OXDC_ROUT_CHK[])(const ST_OXDC_REQ * st_ap_REQ) = {
        &u1_s_oXdcRoutXidchk,
        &u1_s_oXdcRoutSessionchk,
        &u1_s_oXdcRoutSecuritychk,
        &u1_s_oXdcRoutSubfchk,
        &u1_s_oXdcRoutCorchk,
        vdp_PTR_NA
    };

    U4                       u4_t_lpcnt;
    U1                       u1_t_proc;

    u1_t_proc  = (U1)OXDC_SAL_PROC_RUN;
    u4_t_lpcnt = (U4)0U;
    while((u1_t_proc                          == (U1)OXDC_SAL_PROC_RUN) &&
          (fp_sp_u1_OXDC_ROUT_CHK[u4_t_lpcnt] != vdp_PTR_NA           )){

        u1_t_proc = (*fp_sp_u1_OXDC_ROUT_CHK[u4_t_lpcnt])(st_ap_REQ);
        u4_t_lpcnt++;
    }

    if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
        u2_g_oxdc_rout_xid = (U2)U2_MAX;
        vd_g_oXDoCANAnsTx(u1_t_proc, vdp_PTR_NA);
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRoutXidchk(const ST_OXDC_REQ * st_ap_REQ)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRoutXidchk(const ST_OXDC_REQ * st_ap_REQ)
{
    U2                       u2_t_xid;
    U1                       u1_t_proc;
    U1                       u1_t_sup;

    if((st_ap_REQ->u1p_RX   != vdp_PTR_NA       ) &&
       (st_ap_REQ->u4_nbyte >= (U4)OXDC_ROUT_COR)){

        u2_t_xid  = (U2)st_ap_REQ->u1p_RX[OXDC_ROUT_RID_HI] << OXDC_ROUT_LSB_RID_HI;
        u2_t_xid |= (U2)st_ap_REQ->u1p_RX[OXDC_ROUT_RID_LO];
        u2_t_xid  = u2_g_oXDoCANXidSearchRid(u2_t_xid, &st_gp_OXDC_ROUT_XID[0], u2_g_OXDC_ROUT_NUM_XID);

        u2_g_oxdc_rout_xid = u2_t_xid;

        if(u2_t_xid >= u2_g_OXDC_ROUT_NUM_XID){
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        }
        else if(st_gp_OXDC_ROUT_XID[u2_t_xid].fp_u1_SUP == vdp_PTR_NA){
            u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
        }
        else{

            u1_t_sup = (*st_gp_OXDC_ROUT_XID[u2_t_xid].fp_u1_SUP)();
            if(u1_t_sup < (U1)OXDC_XID_SUP_NOT){
                u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
            }
            else{
                u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
            }
        }
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_13;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRoutSessionchk(const ST_OXDC_REQ * st_ap_REQ)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRoutSessionchk(const ST_OXDC_REQ * st_ap_REQ)
{
    U2                       u2_t_conf_ses;
    U1                       u1_t_proc;

    u2_t_conf_ses = st_gp_OXDC_ROUT_XID[u2_g_oxdc_rout_xid].u2_ses;
    u1_t_proc = u1_g_oXDoCANCfgDidSessionBitChk(st_ap_REQ->u1_ses_aft, u2_t_conf_ses);

    if(u1_t_proc == (U1)E_OK){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRoutSecuritychk(const ST_OXDC_REQ * st_ap_REQ)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRoutSecuritychk(const ST_OXDC_REQ * st_ap_REQ)
{
    U1                       u1_t_proc;
    U1                       u1_t_sec;

    if(st_gp_OXDC_ROUT_XID[u2_g_oxdc_rout_xid].fp_u1_SEC_CHK == vdp_PTR_NA){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_sec = DCM_SEC_LEV_LOCKED;
        (void)Dcm_GetSecurityLevel(&u1_t_sec);
        u1_t_proc = (*st_gp_OXDC_ROUT_XID[u2_g_oxdc_rout_xid].fp_u1_SEC_CHK)(u1_t_sec);
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRoutSubfchk(const ST_OXDC_REQ * st_ap_REQ)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRoutSubfchk(const ST_OXDC_REQ * st_ap_REQ)
{
    U1 ( *                   fp_t_u1_stop)(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
    U1 ( *                   fp_t_u1_rslt)(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
    U1                       u1_t_subf;
    U1                       u1_t_proc;

    fp_t_u1_stop = st_gp_OXDC_ROUT_CFG[u2_g_oxdc_rout_xid].fp_u1_STOP;
    fp_t_u1_rslt = st_gp_OXDC_ROUT_CFG[u2_g_oxdc_rout_xid].fp_u1_RESULT;
    u1_t_subf    = st_ap_REQ->u1p_RX[OXDC_ROUT_SUBF] & (U1)OXDC_ROUT_SUBF_CHK;
    if(u1_t_subf == (U1)OXDC_ROUT_SUBF_START){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else if((u1_t_subf    == (U1)OXDC_ROUT_SUBF_STOP) &&
            (fp_t_u1_stop != vdp_PTR_NA             )){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else if((u1_t_subf    == (U1)OXDC_ROUT_SUBF_RESULT) &&
            (fp_t_u1_rslt != vdp_PTR_NA               )){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_12;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRoutCorchk(const ST_OXDC_REQ * st_ap_REQ)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRoutCorchk(const ST_OXDC_REQ * st_ap_REQ)
{
    U1   ( *                 fp_t_u1_cor_chk)(const U1 u1_a_SUBF, const U1 * u1_ap_COR);

    U4                       u4_t_rx_nbyte;
    U2                       u2_t_req_nbyte;
    U1                       u1_t_subf;
    U1                       u1_t_proc;
#if(OXDC_SID31_NR_22_USE == OXDC_USE)
    U1                       u1_t_cod_chk;

    u1_t_cod_chk = u1_g_oXDoCANCRoutineChk();
#endif

    u1_t_subf = st_ap_REQ->u1p_RX[OXDC_ROUT_SUBF] & (U1)OXDC_ROUT_SUBF_CHK;
    if(u1_t_subf == (U1)OXDC_ROUT_SUBF_START){
        u2_t_req_nbyte = st_gp_OXDC_ROUT_XID_ML_SF_01[u2_g_oxdc_rout_xid].u2_req_nbyte;
    }
    else if(u1_t_subf == (U1)OXDC_ROUT_SUBF_STOP){
        u2_t_req_nbyte = st_gp_OXDC_ROUT_XID_ML_SF_02[u2_g_oxdc_rout_xid].u2_req_nbyte;
    }
    else{ /* u1_t_suf is OXDC_ROUT_SUBF_RESULT */
        u2_t_req_nbyte = st_gp_OXDC_ROUT_XID_ML_SF_03[u2_g_oxdc_rout_xid].u2_req_nbyte;
    }

    u4_t_rx_nbyte   = (U4)u2_t_req_nbyte + (U4)OXDC_ROUT_COR;
    fp_t_u1_cor_chk = st_gp_OXDC_ROUT_CFG[u2_g_oxdc_rout_xid].fp_u1_COR_CHK;
    if(st_ap_REQ->u4_nbyte != u4_t_rx_nbyte){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_13;
    }
#if(OXDC_SID31_NR_22_USE == OXDC_USE)
    else if(u1_t_cod_chk != (U1)E_OK){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
    }
#endif
    else if(fp_t_u1_cor_chk == vdp_PTR_NA){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_proc = (*fp_t_u1_cor_chk)(u1_t_subf, &(st_ap_REQ->u1p_RX[OXDC_ROUT_COR]));
        if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        }
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcRoutProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcRoutProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    U1 ( *                   fp_t_u1_func)(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);

    U4                       u4_t_tx_nbyte;
    U2                       u2_t_ans_nbyte;
    U2                       u2_t_ans_nbyte_max;
    U1                       u1_t_subf;
    U1                       u1_t_no_ans;
    U1                       u1_t_proc;

    if((st_ap_REQ->u1p_RX   != vdp_PTR_NA       ) &&
       (st_ap_REQ->u4_nbyte >= (U4)OXDC_ROUT_COR)){

        u1_t_subf   = st_ap_REQ->u1p_RX[OXDC_ROUT_SUBF] & (U1)OXDC_ROUT_SUBF_CHK;
        u1_t_no_ans = st_ap_REQ->u1p_RX[OXDC_ROUT_SUBF] & (U1)OXDC_ROUT_SUBF_NO_ANS;

        if(u1_t_subf == (U1)OXDC_ROUT_SUBF_START){
            u2_t_ans_nbyte_max = st_gp_OXDC_ROUT_XID_ML_SF_01[u2_g_oxdc_rout_xid].u2_ans_nbyte;
            fp_t_u1_func       = st_gp_OXDC_ROUT_CFG[u2_g_oxdc_rout_xid].fp_u1_START;
        }
        else if(u1_t_subf == (U1)OXDC_ROUT_SUBF_STOP){
            u2_t_ans_nbyte_max = st_gp_OXDC_ROUT_XID_ML_SF_02[u2_g_oxdc_rout_xid].u2_ans_nbyte;
            fp_t_u1_func       = st_gp_OXDC_ROUT_CFG[u2_g_oxdc_rout_xid].fp_u1_STOP;
        }
        else{ /* u1_t_suf is OXDC_ROUT_SUBF_RESULT */
            u2_t_ans_nbyte_max = st_gp_OXDC_ROUT_XID_ML_SF_03[u2_g_oxdc_rout_xid].u2_ans_nbyte;
            fp_t_u1_func       = st_gp_OXDC_ROUT_CFG[u2_g_oxdc_rout_xid].fp_u1_RESULT;
        }

        u4_t_tx_nbyte = (U4)u2_t_ans_nbyte_max + (U4)OXDC_ROUT_COR;
        if((st_ap_ans->u1p_tx   != vdp_PTR_NA   ) &&
           (st_ap_ans->u4_nbyte >= u4_t_tx_nbyte) &&
           (fp_t_u1_func        != vdp_PTR_NA   )){

            u2_t_ans_nbyte = u2_t_ans_nbyte_max;
            u1_t_proc = (*fp_t_u1_func)(&(st_ap_ans->u1p_tx[OXDC_ROUT_COR]), st_ap_REQ->u2_tim_elpsd, &u2_t_ans_nbyte);
            if(u2_t_ans_nbyte < u2_t_ans_nbyte_max){
                u4_t_tx_nbyte = (U4)u2_t_ans_nbyte + (U4)OXDC_ROUT_COR;
            }
        }
        else{
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_10;
        }
    }
    else{
        u1_t_proc   = (U1)OXDC_SAL_PROC_NR_10;
    }

    if(u1_t_proc == (U1)OXDC_SAL_PROC_FIN){

        u2_g_oxdc_rout_xid  = (U2)U2_MAX;
        u1_t_no_ans        &= u1_s_oXdcRoutNoAnschk(st_ap_REQ);
        if(u1_t_no_ans == (U1)0U){

            st_ap_ans->u1p_tx[OXDC_ROUT_SUBF]   = u1_t_subf;
            st_ap_ans->u1p_tx[OXDC_ROUT_RID_HI] = st_ap_REQ->u1p_RX[OXDC_ROUT_RID_HI];
            st_ap_ans->u1p_tx[OXDC_ROUT_RID_LO] = st_ap_REQ->u1p_RX[OXDC_ROUT_RID_LO];
            st_ap_ans->u4_nbyte                 = u4_t_tx_nbyte;

            vd_g_oXDoCANAnsTx(u1_t_proc, st_ap_ans);
        }
        else{
            vd_g_oXDoCANAnsTx(u1_t_proc, vdp_PTR_NA);
        }
    }
    else if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){

        u2_g_oxdc_rout_xid = (U2)U2_MAX;

        vd_g_oXDoCANAnsTx(u1_t_proc, vdp_PTR_NA);
    }
    else{
        /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRoutNoAnschk(const ST_OXDC_REQ * st_ap_REQ)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRoutNoAnschk(const ST_OXDC_REQ * st_ap_REQ)
{
    U4                       u4_t_lpcnt;
    U4                       u4_t_p2svmax;
    U4                       u4_t_elpsd;
    U1                       u1_t_ses;
    U1                       u1_t_no_ans;

    u4_t_p2svmax = (U4)0U;
    u1_t_ses     = st_ap_REQ->u1_ses_aft;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DCM_P_SESSIONROW_N; u4_t_lpcnt++){
        if(u1_t_ses == Dcm_P_SID10_stSessionRow_Tbl[u4_t_lpcnt].u1Level){
            u4_t_p2svmax = (U4)Dcm_P_SID10_stSessionRow_Tbl[u4_t_lpcnt].u2P2ServerMax;
            break;
        }
    }

    u4_t_elpsd = (U4)st_ap_REQ->u2_tim_elpsd * (U4)OXDC_MAIN_TICK;
    if(u4_t_elpsd >= u4_t_p2svmax){
        u1_t_no_ans = (U1)0U;
    }
    else{
        u1_t_no_ans = (U1)OXDC_ROUT_SUBF_NO_ANS;
    }

    return(u1_t_no_ans);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/16/2022  HU       ty19epf_ren_d1x_v220_r009 -> x25epf_ren_d1x_v100_r000, Function Name tydocan_rout -> oxdocan_rout. */
/*  1.0.1     7/ 7/2023  ST       Update for OEM standardization.                                                                    */
/*  1.0.2     8/24/2023  TI       Maximum security level support.                                                                    */
/*  1.0.3     6/19/2024  ToI      Variable length support for responses.                                                             */
/*                                                                                                                                   */
/*  * HU = Hayato Usui, DENSO                                                                                                        */
/*  * ST   = Shohei Takada, DENSO                                                                                                    */
/*  * TI = Takaehisa Inoue, DENSO                                                                                                    */
/*  * ToI= Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
