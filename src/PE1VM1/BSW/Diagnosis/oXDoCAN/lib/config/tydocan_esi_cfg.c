/* 1.1.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  SID 0xBA ECU Shipping Inspection                                                                                                 */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_ESI_CFG_C_MAJOR                  (1U)
#define TYDOCAN_ESI_CFG_C_MINOR                  (1U)
#define TYDOCAN_ESI_CFG_C_PATCH                  (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"

#include "mtrxsrch.h"

#ifdef ES_INSPECT_H
#include "es_inspect.h"
#endif /* #ifdef ES_INSPECT_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_ESI_CFG_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_esi_cfg.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_ESI_REQ_CID_MIN                     (2U)
#define TYDC_ESI_REQ_CID_MAX                     (4U)

#define TYDC_ESI_REQ_LSB_RX_0                    (24U)
#define TYDC_ESI_REQ_LSB_RX                      (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1  ( * const     fp_u1_TRX)(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
                                                                                                /* Return : OXDC_SAL_PROC_RUN or Not */
    U2                u2_req_nbyte;
    U2                u2_ans_nbyte;
}ST_TYDC_ESI;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2       u2_s_tydc_esi_cid;
static U1       u1_s_tydc_esi_eom_chk;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_TydcEsiReqchk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_TydcEsiSecuritychk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_TydcEsiCidchk(const ST_OXDC_REQ * st_ap_REQ);

static void    vd_s_TydcEsiProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1               u1_g_TYDC_ESI_SEC_LV_CHK = (U1)0x02U;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_ESI      st_gp_TYDC_ESI_CFG[] = {
/*   fp_u1_TRX                      u2_req_nbyte                    u2_ans_nbyte */
    {vdp_PTR_NA,                    (U2)0U,                         (U2)0U                      }         /* Dummy */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4        u4_sp_TYDC_ESI_CID_MASK[] = {
    (U4)0x00000000U         /* Dummy */
};

static const U4        u4_sp_TYDC_ESI_CID_CRIT[] = {
    (U4)0x00000000U         /* Dummy */
};

const ST_MTRX_SRCH     st_g_TYDC_ESI_CID = {
    &u4_sp_TYDC_ESI_CID_MASK[0],    /* u4p_MASK    */
    &u4_sp_TYDC_ESI_CID_CRIT[0],    /* u4p_CRIT    */
    (U2)1U,                         /* u2_len_inst */
    (U2)0U                          /* u2_num_srch */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANEsiCfgRxEvhk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANEsiCfgRxEvhk(void)
{
#ifdef ES_INSPECT_H
    vd_g_ESInspectReqRx((U1)ES_INSPECT_REQ_RUN, (U1)ES_INSPECT_MD_RUN);
#endif /* #ifdef ES_INSPECT_H */
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANEsiInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANEsiInit(void)
{
    u2_s_tydc_esi_cid      = (U2)U2_MAX;
    u1_s_tydc_esi_eom_chk  = (U1)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANEsiMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANEsiMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    u1_s_tydc_esi_eom_chk = st_ap_REQ->u1_eom_aft & (U1)OXDC_EOM_SI_ACT;

    if(st_ap_REQ->u1_sid == (U1)OXDC_SID_BA){

        if(st_ap_REQ->u2_tim_elpsd == (U2)0U){
            vd_s_TydcEsiReqchk(st_ap_REQ);
        }

        if(u2_s_tydc_esi_cid < st_g_TYDC_ESI_CID.u2_num_srch){
            vd_s_TydcEsiProcRun(st_ap_REQ, st_ap_ans);
        }
        else if(st_ap_REQ->u2_tim_elpsd > (U2)0U){
            u2_s_tydc_esi_cid = (U2)U2_MAX;
            vd_g_oXDoCANAnsTx((U1)OXDC_SAL_PROC_FIN, vdp_PTR_NA);
        }
        else{
            /* Do Nothing */
        }
    }
    else{
        u2_s_tydc_esi_cid = (U2)U2_MAX;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcEsiReqchk(const ST_OXDC_REQ * st_ap_REQ)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static void    vd_s_TydcEsiReqchk(const ST_OXDC_REQ * st_ap_REQ)
{
    static U1 ( * const      fp_sp_u1_TYDC_ESI_CHK[])(const ST_OXDC_REQ * st_ap_REQ) = {
        &u1_s_TydcEsiSecuritychk,
        &u1_s_TydcEsiCidchk,
        vdp_PTR_NA
    };

    U4                       u4_t_lpcnt;
    U1                       u1_t_proc;

    if(u1_s_tydc_esi_eom_chk == (U1)OXDC_EOM_SI_ACT){

        u1_t_proc  = (U1)OXDC_SAL_PROC_RUN;
        u4_t_lpcnt = (U4)0U;
        while((u1_t_proc                         == (U1)OXDC_SAL_PROC_RUN) &&
              (fp_sp_u1_TYDC_ESI_CHK[u4_t_lpcnt] != vdp_PTR_NA           )){

            u1_t_proc = (*fp_sp_u1_TYDC_ESI_CHK[u4_t_lpcnt])(st_ap_REQ);
            u4_t_lpcnt++;
        }

        if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
            u2_s_tydc_esi_cid = (U2)U2_MAX;
            vd_g_oXDoCANAnsTx((U1)OXDC_SAL_PROC_FIN, vdp_PTR_NA);
        }
        else{
            vd_g_TyDoCANEsiCfgRxEvhk();
        }
    }
    else{
        u2_s_tydc_esi_cid = (U2)U2_MAX;
        vd_g_oXDoCANAnsTx((U1)OXDC_SAL_PROC_NR_22, vdp_PTR_NA);
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcEsiSecuritychk(const ST_OXDC_REQ * st_ap_REQ)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_TydcEsiSecuritychk(const ST_OXDC_REQ * st_ap_REQ)
{
    return(u1_g_oXDoCANSecurityOk(u1_g_TYDC_ESI_SEC_LV_CHK));
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcEsiCidchk(const ST_OXDC_REQ * st_ap_REQ)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_TydcEsiCidchk(const ST_OXDC_REQ * st_ap_REQ)
{
    U4                       u4_t_lpcnt;
    U4                       u4_t_lpend;
    U4                       u4_t_lsb;

    U4                       u4_t_req_word;
    U4                       u4_tp_req_inst[1U];

    U2                       u2_t_cid;
    U1                       u1_t_proc;

    if((st_ap_REQ->u1p_RX   == vdp_PTR_NA              ) ||
       (st_ap_REQ->u4_nbyte <  (U4)TYDC_ESI_REQ_CID_MIN)){

        u2_t_cid = (U2)U2_MAX;
    }
    else{

        if(st_ap_REQ->u4_nbyte >= (U4)TYDC_ESI_REQ_CID_MAX){
            u4_t_lpend = (U4)TYDC_ESI_REQ_CID_MAX;
        }
        else{
            u4_t_lpend = st_ap_REQ->u4_nbyte;
        }

        u4_t_req_word = (U4)0U;
        u4_t_lpcnt    = (U4)0U;
        u4_t_lsb      = (U4)TYDC_ESI_REQ_LSB_RX_0;
        while(u4_t_lpcnt < u4_t_lpend){
            u4_t_req_word |= ((U4)st_ap_REQ->u1p_RX[u4_t_lpcnt] << u4_t_lsb);
            u4_t_lsb      -= (U4)TYDC_ESI_REQ_LSB_RX;
            u4_t_lpcnt++;
        }
        u4_tp_req_inst[0] = u4_t_req_word;
        u2_t_cid = u2_g_MtrxSrch((U2)0, u4_tp_req_inst, &st_g_TYDC_ESI_CID);
    }

    if((u2_t_cid            <  st_g_TYDC_ESI_CID.u2_num_srch                ) &&
       (st_ap_REQ->u4_nbyte == (U4)st_gp_TYDC_ESI_CFG[u2_t_cid].u2_req_nbyte)){
        u2_s_tydc_esi_cid = u2_t_cid;
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcEsiProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static void    vd_s_TydcEsiProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    U2                       u2_t_req_nbyte;
    U2                       u2_t_ans_nbyte;
    U1                       u1_t_proc;

    u2_t_req_nbyte = st_gp_TYDC_ESI_CFG[u2_s_tydc_esi_cid].u2_req_nbyte;
    u2_t_ans_nbyte = st_gp_TYDC_ESI_CFG[u2_s_tydc_esi_cid].u2_ans_nbyte;
    if((st_ap_REQ->u1p_RX   != vdp_PTR_NA        ) &&
       (st_ap_REQ->u4_nbyte == (U4)u2_t_req_nbyte) &&
       (st_ap_ans->u4_nbyte >= (U4)u2_t_ans_nbyte) &&
       (st_ap_ans->u1p_tx   != vdp_PTR_NA        )){

        u1_t_proc = (*st_gp_TYDC_ESI_CFG[u2_s_tydc_esi_cid].fp_u1_TRX)(st_ap_REQ->u1p_RX,
                                                                       st_ap_ans->u1p_tx,
                                                                       st_ap_REQ->u2_tim_elpsd);
    }
    else{
        u1_t_proc = (U1)U1_MAX;
    }

    if(u1_t_proc == (U1)OXDC_SAL_PROC_FIN){
        u2_s_tydc_esi_cid   = (U2)U2_MAX;
        st_ap_ans->u4_nbyte = (U4)u2_t_ans_nbyte;
        vd_g_oXDoCANAnsTx((U1)OXDC_SAL_PROC_FIN, st_ap_ans);
    }
    else if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
        u2_s_tydc_esi_cid = (U2)U2_MAX;
        vd_g_oXDoCANAnsTx((U1)OXDC_SAL_PROC_FIN, vdp_PTR_NA);
    }
    else{
        /* Do Nothing */
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
/*  1.0.0    10/ 9/2019  TN       New.                                                                                               */
/*  1.1.0     5/27/2020  TN       tydocan_esi.c v1.0.0 -> v1.1.0.                                                                    */
/*  1.1.1     6/16/2020  HK       tydocan_esi.c v1.1.0 -> v1.1.1.                                                                    */
/*  1.1.2     4/ 2/2021  HK       tydocan_esi.c v1.1.1 -> v1.1.2.                                                                    */
/*  1.1.3     9/ 9/2021  TN       tydocan_esi.c v1.1.2 -> v1.1.3.                                                                    */
/*  1.1.4    11/28/2023  TI       tydocan_esi.c v1.1.3 -> v1.1.4.                                                                    */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*  * HK = Hayato Kanamori, DENSO Create                                                                                             */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
