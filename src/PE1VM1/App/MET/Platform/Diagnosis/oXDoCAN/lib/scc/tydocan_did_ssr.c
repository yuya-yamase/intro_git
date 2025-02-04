/* 1.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  Snapshot Recorder for SID 0x22                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DID_SSR_C_MAJOR                  (1U)
#define TYDOCAN_DID_SSR_C_MINOR                  (0U)
#define TYDOCAN_DID_SSR_C_PATCH                  (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "tydocan_did_ssr_cfg_private.h"
#include "tydocan_tmstp_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_DID_SSR_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_did_ssr.c and tydocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (TYDOCAN_DID_SSR_C_MAJOR != OXDOCAN_SAL_H_MAJOR)
#error "tydocan_did_ssr.c and tydocan_sal.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DID_SSR_C_MAJOR != TYDOCAN_DID_SSR_CFG_H_MAJOR) || \
     (TYDOCAN_DID_SSR_C_MINOR != TYDOCAN_DID_SSR_CFG_H_MINOR) || \
     (TYDOCAN_DID_SSR_C_PATCH != TYDOCAN_DID_SSR_CFG_H_PATCH))
#error "tydocan_did_ssr.c and tydocan_did_ssr_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DIDSSR_MEM_TYPE_NVM            (0U)
#define OXDC_DIDSSR_MEM_TYPE_RIM            (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4                    u4_s_oxdc_did_ssr_key_unlock;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_oXdcDidSsrRecUpdt(const ST_OXDC_DID_SSR * st_ap_SSR, const U2 u2_a_TSLOT);

static void    vd_s_oXdcDidSsrIfSyn(const U1 u1_a_SSR_CH, const U1 u1_a_BON_INIT, const U1 u1_a_MEM_TYPE);
static U1      u1_s_oXdcDidSsrIfRea(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr, const U1 u1_a_MEM_TYPE);
static U1      u1_s_oXdcDidSsrIfRun(const U1 u1_a_SSR_CH, const ST_OXDC_DID_SSR * st_ap_SSR, const U1 u1_a_MEM_TYPE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDidSsrInit(const U1 u1_a_BR_INIT)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANDidSsrInit(const U1 u1_a_BR_INIT)
{
    U4                        u4_t_lpcnt;

    u4_s_oxdc_did_ssr_key_unlock = (U4)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXDC_DID_SSR_NUM_CH; u4_t_lpcnt++){

        st_gp_oxdc_did_ssr_ctrl[u4_t_lpcnt].u4_odo_last  = (U4)OXDC_TMSTP_ODO_UNK;
        st_gp_oxdc_did_ssr_ctrl[u4_t_lpcnt].u2_num_last  = (U2)0U;
        st_gp_oxdc_did_ssr_ctrl[u4_t_lpcnt].u2_pau_elpsd = (U2)U2_MAX;
        st_gp_oxdc_did_ssr_ctrl[u4_t_lpcnt].u1_rec_run   = (U1)FALSE;
        st_gp_oxdc_did_ssr_ctrl[u4_t_lpcnt].u1_rec_cnt   = (U1)0U;
        st_gp_oxdc_did_ssr_ctrl[u4_t_lpcnt].u1_rec_last  = (U1)0U;
        st_gp_oxdc_did_ssr_ctrl[u4_t_lpcnt].u1_del_cnt   = (U1)U1_MAX;

        (*(stp_gp_OXDC_DID_SSR_IF_BY_CH[u4_t_lpcnt]->fp_vd_SYN))((U1)u4_t_lpcnt, u1_a_BR_INIT);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSsrMainTask(const U2 u2_a_TSLOT, const U1 u1_a_EOM)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSsrMainTask(const U2 u2_a_TSLOT, const U1 u1_a_EOM)
{
    ST_OXDC_DID_SSR           st_t_ssr;
    U4                        u4_t_lpcnt;
    U1                        u1_t_num_rec;
    U1                        u1_t_rec_run;

    u4_s_oxdc_did_ssr_key_unlock = (U4)0U;

    st_t_ssr.u2_rec_num                  = (U2)0U;
    st_t_ssr.u2_tri_cnt                  = u2_g_oXDoCANTmstpTripcnt();
    st_t_ssr.u4_tim_cnt                  = u4_g_oXDoCANTmstpTimecnt();
    st_t_ssr.u4_odo_0p1km                = u4_g_oXDoCANTmstpOdo();
    vd_g_oXDoCANTmstpGmt(&st_t_ssr.u1p_gmt[0], (U4)OXDC_TMSTP_GMT_NUM);
    st_t_ssr.u1_tri_sync                 = u1_g_oXDoCANTmstpTripSync();
    st_t_ssr.u1_spare                    = (U1)0;
    st_t_ssr.u4p_ss[OXDC_DID_SSR_SS_DW0] = (U4)0U;
    st_t_ssr.u4p_ss[OXDC_DID_SSR_SS_DW1] = (U4)0U;
    st_t_ssr.u4p_ss[OXDC_DID_SSR_SS_DW2] = (U4)0U;

    if(u1_a_EOM < (U1)OXDC_EOM_SI_ACT){

        u1_t_rec_run = u1_s_oXdcDidSsrRecUpdt(&st_t_ssr, u2_a_TSLOT);
    }
    else{

        u1_t_rec_run = (U1)FALSE;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXDC_DID_SSR_NUM_CH; u4_t_lpcnt++){

            st_gp_oxdc_did_ssr_ctrl[u4_t_lpcnt].u2_pau_elpsd = (U2)U2_MAX;

            u1_t_num_rec = st_gp_OXDC_DID_SSR_CH_CFG[u4_t_lpcnt].u1_num_rec;
            if(st_gp_oxdc_did_ssr_ctrl[u4_t_lpcnt].u1_del_cnt < u1_t_num_rec){

                u1_t_rec_run |= (*(stp_gp_OXDC_DID_SSR_IF_BY_CH[u4_t_lpcnt]->fp_u1_DEL))((U1)u4_t_lpcnt);
            }
        }
    }

    return(u1_t_rec_run);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSsrNumRecord(const U1 u1_a_SSR_CH, const U1 u1_a_REQ_MAX)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSsrNumRecord(const U1 u1_a_SSR_CH, const U1 u1_a_REQ_MAX)
{
    U1                        u1_t_num_rec;

    if(u1_a_SSR_CH >= u1_g_OXDC_DID_SSR_NUM_CH){
        u1_t_num_rec = (U1)0U;
    }
    else if(u1_a_REQ_MAX == (U1)TRUE){
        u1_t_num_rec = st_gp_OXDC_DID_SSR_CH_CFG[u1_a_SSR_CH].u1_num_rec;
    }
    else{
        u1_t_num_rec = st_gp_oxdc_did_ssr_ctrl[u1_a_SSR_CH].u1_rec_cnt;
    }

    return(u1_t_num_rec);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSsrRead(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSsrRead(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr)
{
    U1                        u1_t_ok;

    if((u1_a_SSR_CH <  u1_g_OXDC_DID_SSR_NUM_CH) &&
       (st_ap_ssr   != vdp_PTR_NA          )){

        u1_t_ok = (*(stp_gp_OXDC_DID_SSR_IF_BY_CH[u1_a_SSR_CH]->fp_u1_REA))(u1_a_SSR_CH, u1_a_REC_IDX, st_ap_ssr);
    }
    else{
        u1_t_ok = (U1)FALSE;
    }

    return(u1_t_ok);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDidSsrUnlock(const U4 u4_a_KEY)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANDidSsrUnlock(const U4 u4_a_KEY)
{
    u4_s_oxdc_did_ssr_key_unlock = u4_a_KEY;
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDidSsrDelete(const U1 u1_a_SSR_CH)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANDidSsrDelete(const U1 u1_a_SSR_CH)
{
    if((u1_a_SSR_CH              <  u1_g_OXDC_DID_SSR_NUM_CH   ) &&
       (u4_s_oxdc_did_ssr_key_unlock == (U4)OXDC_DID_SSR_KEY_UNLOCK)){

        st_gp_oxdc_did_ssr_ctrl[u1_a_SSR_CH].u1_rec_cnt = (U1)0U;
        st_gp_oxdc_did_ssr_ctrl[u1_a_SSR_CH].u1_del_cnt = (U1)0U;
    }
    u4_s_oxdc_did_ssr_key_unlock = (U4)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDidSsrPause(const U1 u1_a_SSR_CH)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANDidSsrPause(const U1 u1_a_SSR_CH)
{
    if((u1_a_SSR_CH                  <  OXDC_DID_SSR_NUM_CH        ) &&
       (u4_s_oxdc_did_ssr_key_unlock == (U4)OXDC_DID_SSR_KEY_UNLOCK)){

        st_gp_oxdc_did_ssr_ctrl[u1_a_SSR_CH].u2_pau_elpsd = (U2)0U;
    }
    u4_s_oxdc_did_ssr_key_unlock = (U4)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDidSsrIfSynNvmbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_BON_INIT)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANDidSsrIfSynNvmbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_BON_INIT)
{
    vd_s_oXdcDidSsrIfSyn(u1_a_SSR_CH, u1_a_BON_INIT, (U1)OXDC_DIDSSR_MEM_TYPE_NVM);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSsrIfReaNvmbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSsrIfReaNvmbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr)
{
    return(u1_s_oXdcDidSsrIfRea(u1_a_SSR_CH, u1_a_REC_IDX, st_ap_ssr, (U1)OXDC_DIDSSR_MEM_TYPE_NVM));
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSsrIfRunNvmbyCh(const U1 u1_a_SSR_CH, const ST_OXDC_DID_SSR * st_ap_SSR)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSsrIfRunNvmbyCh(const U1 u1_a_SSR_CH, const ST_OXDC_DID_SSR * st_ap_SSR)
{
    return(u1_s_oXdcDidSsrIfRun(u1_a_SSR_CH, st_ap_SSR, (U1)OXDC_DIDSSR_MEM_TYPE_NVM));
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSsrIfDelNvmbyCh(const U1 u1_a_SSR_CH)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSsrIfDelNvmbyCh(const U1 u1_a_SSR_CH)
{
    static const ST_OXDC_DID_SSR  st_s_TYDC_DID_SSR_MEM_INIT = {
        (U2)0U,                                /* u2_rec_num   */
        (U2)0U,                                /* u2_tri_cnt   */
        (U4)0U,                                /* u4_tim_cnt   */
        (U4)0U,                                /* u4_odo_0p1km */
        {                                      /* u1p_gmt[6]   */
            (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U
        },
        (U1)0U,                                /* u1_tri_sync  */
        (U1)0U,                                /* u1_spare     */
        {                                      /* u4p_ss[3]    */
            (U4)0U, (U4)0U, (U4)0U
        }
    };

    const ST_OXDC_DID_SSR_CH *  st_tp_CH;
    ST_OXDC_DID_SSR_CTRL *      st_tp_ctrl;

    U2                          u2_t_mem_id;
    U2                          u2_t_rec_next;
    U2                          u2_t_del_next;

    U1                          u1_t_num_rec;

    st_tp_CH   = &st_gp_OXDC_DID_SSR_CH_CFG[u1_a_SSR_CH];
    st_tp_ctrl = &st_gp_oxdc_did_ssr_ctrl[u1_a_SSR_CH];

    u1_t_num_rec  = st_tp_CH->u1_num_rec;
    u2_t_rec_next = (U2)st_tp_ctrl->u1_rec_last + (U2)1U;
    if(u2_t_rec_next >= (U2)u1_t_num_rec){
        u2_t_rec_next = (U2)0U;
    }
    st_tp_ctrl->u1_rec_last = (U1)u2_t_rec_next;

    u2_t_mem_id = st_tp_CH->u2p_MEM_ID[u2_t_rec_next];
    vd_g_Nvmc_WriteOthr(u2_t_mem_id,
                        (U2)st_tp_CH->u1_mem_nbyte,
                        (const U1 *)&st_s_TYDC_DID_SSR_MEM_INIT);

    u2_t_del_next = (U2)st_tp_ctrl->u1_del_cnt + (U2)1U;
    if(u2_t_del_next >= (U2)u1_t_num_rec){

        st_tp_ctrl->u4_odo_last  = (U4)OXDC_TMSTP_ODO_UNK;
        st_tp_ctrl->u2_num_last  = (U2)0U;
     /* st_tp_ctrl->u2_pau_elpsd = (U2)U2_MAX; */
        st_tp_ctrl->u1_rec_run   = (U1)FALSE;
        st_tp_ctrl->u1_rec_last  = u1_t_num_rec - (U1)1U;
        st_tp_ctrl->u1_rec_cnt   = (U1)0U;
        st_tp_ctrl->u1_del_cnt   = (U1)U1_MAX;
    }
    else{
        st_tp_ctrl->u1_del_cnt   = (U1)u2_t_del_next;
    }

    return((U1)TRUE);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDidSsrIfSynRimbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_BON_INIT)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANDidSsrIfSynRimbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_BON_INIT)
{
    vd_s_oXdcDidSsrIfSyn(u1_a_SSR_CH, u1_a_BON_INIT, (U1)OXDC_DIDSSR_MEM_TYPE_RIM);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSsrIfReaRimbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSsrIfReaRimbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr)
{
    return(u1_s_oXdcDidSsrIfRea(u1_a_SSR_CH, u1_a_REC_IDX, st_ap_ssr, (U1)OXDC_DIDSSR_MEM_TYPE_RIM));
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSsrIfRunRimbyCh(const U1 u1_a_SSR_CH, const ST_OXDC_DID_SSR * st_ap_SSR)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSsrIfRunRimbyCh(const U1 u1_a_SSR_CH, const ST_OXDC_DID_SSR * st_ap_SSR)
{
    (void)u1_s_oXdcDidSsrIfRun(u1_a_SSR_CH, st_ap_SSR, (U1)OXDC_DIDSSR_MEM_TYPE_RIM);
    /* Returns FALSE because Nvmc has not been requested to update. */
    return((U1)FALSE);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSsrIfDelRimbyCh(const U1 u1_a_SSR_CH)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSsrIfDelRimbyCh(const U1 u1_a_SSR_CH)
{
    static const ST_OXDC_DID_SSR  st_s_TYDC_DID_SSR_MEM_INIT = {
        (U2)0U,                                /* u2_rec_num   */
        (U2)0U,                                /* u2_tri_cnt   */
        (U4)0U,                                /* u4_tim_cnt   */
        (U4)0U,                                /* u4_odo_0p1km */
        {                                      /* u1p_gmt[6]   */
            (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U
        },
        (U1)0U,                                /* u1_tri_sync  */
        (U1)0U,                                /* u1_spare     */
        {                                      /* u4p_ss[3]    */
            (U4)0U, (U4)0U, (U4)0U
        }
    };

    const ST_OXDC_DID_SSR_CH *  st_tp_CH;
    ST_OXDC_DID_SSR_CTRL *      st_tp_ctrl;

    U2                          u2_t_mem_id;
    U1                          u1_t_rec_cnt;
    U2                          u2_t_rec_next;
    U1                          u1_t_num_rec;

    st_tp_CH   = &st_gp_OXDC_DID_SSR_CH_CFG[u1_a_SSR_CH];
    st_tp_ctrl = &st_gp_oxdc_did_ssr_ctrl[u1_a_SSR_CH];

    u1_t_num_rec  = st_tp_CH->u1_num_rec;

    for(u1_t_rec_cnt = (U1)0; u1_t_rec_cnt < u1_t_num_rec; u1_t_rec_cnt++){
        
        u2_t_rec_next = (U2)st_tp_ctrl->u1_rec_last + (U2)1U;
        if(u2_t_rec_next >= (U2)u1_t_num_rec){
            u2_t_rec_next = (U2)0U;
        }
        st_tp_ctrl->u1_rec_last = (U1)u2_t_rec_next;
        
        u2_t_mem_id = st_tp_CH->u2p_MEM_ID[u2_t_rec_next];
        vd_g_Rim_WriteOther(u2_t_mem_id,
                            (U2)st_tp_CH->u1_mem_nbyte,
                            (const U1 *)&st_s_TYDC_DID_SSR_MEM_INIT);
    }

    st_tp_ctrl->u4_odo_last  = (U4)OXDC_TMSTP_ODO_UNK;
    st_tp_ctrl->u2_num_last  = (U2)0U;
 /* st_tp_ctrl->u2_pau_elpsd = (U2)U2_MAX; */
    st_tp_ctrl->u1_rec_run   = (U1)FALSE;
    st_tp_ctrl->u1_rec_last  = u1_t_num_rec - (U1)1U;
    st_tp_ctrl->u1_rec_cnt   = (U1)0U;
    st_tp_ctrl->u1_del_cnt   = (U1)U1_MAX;

    /* Returns FALSE because Nvmc has not been requested to update. */
    return((U1)FALSE);
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcDidSsrIfSyn(const U1 u1_a_SSR_CH, const U1 u1_a_BON_INIT, const U1 u1_a_MEM_TYPE)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcDidSsrIfSyn(const U1 u1_a_SSR_CH, const U1 u1_a_BON_INIT, const U1 u1_a_MEM_TYPE)
{
    const ST_OXDC_DID_SSR_CH *  st_tp_CH;
    ST_OXDC_DID_SSR_CTRL *      st_tp_ctrl;

    const U2 *                  u2_tp_MEM_ID;

    ST_OXDC_DID_SSR             st_t_mem;

    U4                          u4_t_lpcnt;
    U4                          u4_t_num_rec;
    U4                          u4_t_rec_cnt;
    U4                          u4_t_rec_last;
    U4                          u4_t_odo_last;

    U2                          u2_t_mem_nbyte;
    U2                          u2_t_num_last;

    U1                          u1_t_mem_chk;
    U1                          u1_t_mem_ok;

    st_tp_CH       = &st_gp_OXDC_DID_SSR_CH_CFG[u1_a_SSR_CH];
    st_tp_ctrl     = &st_gp_oxdc_did_ssr_ctrl[u1_a_SSR_CH];

    u2_tp_MEM_ID  = st_tp_CH->u2p_MEM_ID;
    u2_t_mem_nbyte = (U2)st_tp_CH->u1_mem_nbyte;
    u4_t_num_rec   = (U4)st_tp_CH->u1_num_rec; 

    u4_t_rec_cnt   = (U4)0U;
    u4_t_rec_last  = u4_t_num_rec - (U4)1U;
    u4_t_odo_last  = (U4)OXDC_TMSTP_ODO_UNK;

    u2_t_num_last  = (U2)0U;

    st_t_mem.u2_rec_num   = (U2)0U;                   /* Codesonar Red Warning "Uninitialized Variable" was fixed */
    st_t_mem.u4_odo_0p1km = (U4)OXDC_TMSTP_ODO_UNK;   /* Codesonar Red Warning "Uninitialized Variable" was fixed */

    if((u1_a_MEM_TYPE == (U1)OXDC_DIDSSR_MEM_TYPE_NVM) ||
       (u1_a_BON_INIT != (U1)TRUE                    )){
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_num_rec; u4_t_lpcnt++){

            u1_t_mem_ok = (U1)TRUE;
            if(u1_a_MEM_TYPE == (U1)OXDC_DIDSSR_MEM_TYPE_RIM){
                u1_t_mem_chk = u1_g_Rim_ReadOtherwithStatus(u2_tp_MEM_ID[u4_t_lpcnt], u2_t_mem_nbyte, (U1 *)&st_t_mem);
                if((u1_t_mem_chk & (U1)RIM_RESULT_KIND_MASK) != RIM_RESULT_KIND_OK){
                    u1_t_mem_ok = (U1)FALSE;
                }
            }
            else{
                u1_t_mem_chk = u1_g_Nvmc_ReadOthrwithSts(u2_tp_MEM_ID[u4_t_lpcnt], u2_t_mem_nbyte, (U1 *)&st_t_mem);
                if((u1_t_mem_chk >= (U1)NVMC_STATUS_NG      ) ||
                   (u1_t_mem_chk == (U1)NVMC_STATUS_ERRCOMP ) ||
                   (u1_t_mem_chk == (U1)NVMC_STATUS_CACHE_NG)){
                    u1_t_mem_ok = (U1)FALSE;
                }
            }

            if(u1_t_mem_ok == (U1)FALSE){
                /* Do Nothing */
            }
            else if(st_t_mem.u2_rec_num > u2_t_num_last){
                u2_t_num_last = st_t_mem.u2_rec_num;
                u4_t_odo_last = st_t_mem.u4_odo_0p1km;
                u4_t_rec_last = u4_t_lpcnt;
                u4_t_rec_cnt++;
            }
            else if(st_t_mem.u2_rec_num > (U2)0U){
                u4_t_rec_cnt++;
            }
            else{
                /* Do Nothing */
            }
        }
    }

    st_tp_ctrl->u4_odo_last = u4_t_odo_last;
    st_tp_ctrl->u2_num_last = u2_t_num_last;
    st_tp_ctrl->u1_rec_last = (U1)u4_t_rec_last;
    st_tp_ctrl->u1_rec_cnt  = (U1)u4_t_rec_cnt;
}
/*===================================================================================================================================*/
/*  static U1 u1_s_oXdcDidSsrIfRea(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr, const U1 u1_a_MEM_TYPE) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcDidSsrIfRea(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr, const U1 u1_a_MEM_TYPE)
{
    const ST_OXDC_DID_SSR_CH *  st_tp_CH;
    ST_OXDC_DID_SSR_CTRL *      st_tp_ctrl;

    ST_OXDC_DID_SSR             st_t_mem;

    U2                          u2_t_idx;
    U2                          u2_t_mem_id;

    U1                          u1_t_num_rec;
    U1                          u1_t_rec_last;
    U1                          u1_t_rec_cnt;

    U1                          u1_t_mem_chk;
    U1                          u1_t_mem_ok;
    U1                          u1_t_ok;

    st_tp_CH      = &st_gp_OXDC_DID_SSR_CH_CFG[u1_a_SSR_CH];
    st_tp_ctrl    = &st_gp_oxdc_did_ssr_ctrl[u1_a_SSR_CH];

    u1_t_num_rec  = st_tp_CH->u1_num_rec;
    u1_t_rec_last = st_tp_ctrl->u1_rec_last;
    u1_t_rec_cnt  = st_tp_ctrl->u1_rec_cnt;
    if((u1_t_rec_last >= u1_t_num_rec) ||
       (u1_t_rec_cnt  >  u1_t_num_rec) ||
       (u1_a_REC_IDX  >= u1_t_rec_cnt)){
        u2_t_idx = (U2)U2_MAX;
    }
    else if(u1_a_REC_IDX <= u1_t_rec_last){
        u2_t_idx = (U2)u1_t_rec_last - (U2)u1_a_REC_IDX;
    }
    else{
        u2_t_idx = ((U2)u1_t_num_rec + (U2)u1_t_rec_last) - (U2)u1_a_REC_IDX;
    }

    u1_t_ok = (U1)FALSE;
    if(u2_t_idx < (U2)u1_t_num_rec){

     /* st_t_mem.u2_rec_num                  = (U2)0U;                       */
     /* st_t_mem.u2_tri_cnt                  = (U2)0U;                       */
     /* st_t_mem.u4_tim_cnt                  = (U4)0U;                       */
     /* st_t_mem.u4_odo_0p1km                = (U4)TYDC_TMSTP_ODO_UNK;       */
     /* vd_g_MemfillU1(&st_t_mem.u1p_gmt[0], (U1)OXDC_TMSTP_GMT_UNK, (U4)OXDC_TMSTP_GMT_NUM); */
     /* st_t_mem.u1_tri_sync                 = (U1)0U;                       */
     /* st_t_mem.u1_spare                    = (U1)0U;                       */
        st_t_mem.u4p_ss[OXDC_DID_SSR_SS_DW0] = (U4)0U;
        st_t_mem.u4p_ss[OXDC_DID_SSR_SS_DW1] = (U4)0U;
        st_t_mem.u4p_ss[OXDC_DID_SSR_SS_DW2] = (U4)0U;

        u2_t_mem_id = st_tp_CH->u2p_MEM_ID[u2_t_idx];

        u1_t_mem_ok = (U1)TRUE;
        if(u1_a_MEM_TYPE == (U1)OXDC_DIDSSR_MEM_TYPE_RIM){
            u1_t_mem_chk = u1_g_Rim_ReadOtherwithStatus(u2_t_mem_id, (U2)st_tp_CH->u1_mem_nbyte, (U1 *)&st_t_mem);
            if((u1_t_mem_chk & (U1)RIM_RESULT_KIND_MASK) != RIM_RESULT_KIND_OK){
                u1_t_mem_ok = (U1)FALSE;
            }
        }
        else{
            u1_t_mem_chk = u1_g_Nvmc_ReadOthrwithSts(u2_t_mem_id, (U2)st_tp_CH->u1_mem_nbyte, (U1 *)&st_t_mem);
            if((u1_t_mem_chk >= (U1)NVMC_STATUS_NG      ) ||
               (u1_t_mem_chk == (U1)NVMC_STATUS_ERRCOMP ) ||
               (u1_t_mem_chk == (U1)NVMC_STATUS_CACHE_NG)){
                u1_t_mem_ok = (U1)FALSE;
            }
        }

        if(u1_t_mem_ok == (U1)FALSE){
            /* Do Nothing */
        }
        else{

            st_ap_ssr->u2_rec_num                  = st_t_mem.u2_rec_num;
            st_ap_ssr->u2_tri_cnt                  = st_t_mem.u2_tri_cnt;
            st_ap_ssr->u4_tim_cnt                  = st_t_mem.u4_tim_cnt;
            st_ap_ssr->u4_odo_0p1km                = st_t_mem.u4_odo_0p1km;
            vd_g_MemcpyU1(&st_ap_ssr->u1p_gmt[0], &st_t_mem.u1p_gmt[0], (U4)OXDC_TMSTP_GMT_NUM);
            st_ap_ssr->u1_tri_sync                 = st_t_mem.u1_tri_sync;
            st_ap_ssr->u1_spare                    = st_t_mem.u1_spare;
            st_ap_ssr->u4p_ss[OXDC_DID_SSR_SS_DW0] = st_t_mem.u4p_ss[OXDC_DID_SSR_SS_DW0];
            st_ap_ssr->u4p_ss[OXDC_DID_SSR_SS_DW1] = st_t_mem.u4p_ss[OXDC_DID_SSR_SS_DW1];
            st_ap_ssr->u4p_ss[OXDC_DID_SSR_SS_DW2] = st_t_mem.u4p_ss[OXDC_DID_SSR_SS_DW2];

            u1_t_ok = (U1)TRUE;
        }
    }

    return(u1_t_ok);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDidSsrIfRunbyCh(const U1 u1_a_SSR_CH, const ST_OXDC_DID_SSR * st_ap_SSR)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcDidSsrIfRun(const U1 u1_a_SSR_CH, const ST_OXDC_DID_SSR * st_ap_SSR, const U1 u1_a_MEM_TYPE)
{
    const ST_OXDC_DID_SSR_CH *  st_tp_CH;
    ST_OXDC_DID_SSR_CTRL *      st_tp_ctrl;

    ST_OXDC_DID_SSR             st_t_mem;

    U2                          u2_t_rec_next;
    U2                          u2_t_mem_nbyte;
    U2                          u2_t_mem_id;

    U1                          u1_t_odo_updt;
    U1                          u1_t_num_rec;
    U1                          u1_t_rec_chk;
    U1                          u1_t_rec_run;

    st_tp_CH   = &st_gp_OXDC_DID_SSR_CH_CFG[u1_a_SSR_CH];
    st_tp_ctrl = &st_gp_oxdc_did_ssr_ctrl[u1_a_SSR_CH];

    if((st_tp_CH->fp_u1_EV_CAPT != vdp_PTR_NA) &&
       (st_tp_ctrl->u2_num_last <  (U2)U2_MAX)){

        st_t_mem.u4p_ss[OXDC_DID_SSR_SS_DW0] = (U4)0U;
        st_t_mem.u4p_ss[OXDC_DID_SSR_SS_DW1] = (U4)0U;
        st_t_mem.u4p_ss[OXDC_DID_SSR_SS_DW2] = (U4)0U;

        if(st_tp_ctrl->u4_odo_last != st_ap_SSR->u4_odo_0p1km){
            u1_t_odo_updt = (U1)TRUE;
        }
        else{
            u1_t_odo_updt = (U1)FALSE;
        }

        u1_t_rec_chk = (*st_tp_CH->fp_u1_EV_CAPT)(u1_t_odo_updt, &st_t_mem.u4p_ss[0]) & (U1)TRUE;
        u1_t_rec_run = (st_tp_ctrl->u1_rec_run ^ u1_t_rec_chk) & u1_t_rec_chk;
        st_tp_ctrl->u1_rec_run = u1_t_rec_chk;
    }
    else{
        u1_t_rec_run = (U1)FALSE;
        st_tp_ctrl->u1_rec_run = (U1)FALSE;
    }

    if(u1_t_rec_run == (U1)TRUE){

        st_tp_ctrl->u4_odo_last = st_ap_SSR->u4_odo_0p1km;
        st_tp_ctrl->u2_num_last++;

        u1_t_num_rec  = st_tp_CH->u1_num_rec;
        u2_t_rec_next = (U2)st_tp_ctrl->u1_rec_last + (U2)1U;
        if(u2_t_rec_next >= (U2)u1_t_num_rec){
            u2_t_rec_next = (U2)0U;
        }
        st_tp_ctrl->u1_rec_last = (U1)u2_t_rec_next;

        if(st_tp_ctrl->u1_rec_cnt < u1_t_num_rec){
            st_tp_ctrl->u1_rec_cnt++;
        }
        else{
            st_tp_ctrl->u1_rec_cnt = u1_t_num_rec;
        }

        st_t_mem.u2_rec_num                  = st_tp_ctrl->u2_num_last;
        st_t_mem.u2_tri_cnt                  = st_ap_SSR->u2_tri_cnt;
        st_t_mem.u4_tim_cnt                  = st_ap_SSR->u4_tim_cnt;
        st_t_mem.u4_odo_0p1km                = st_ap_SSR->u4_odo_0p1km;
        vd_g_MemcpyU1(&st_t_mem.u1p_gmt[0], &st_ap_SSR->u1p_gmt[0], (U4)OXDC_TMSTP_GMT_NUM);
        st_t_mem.u1_tri_sync                 = st_ap_SSR->u1_tri_sync;
        st_t_mem.u1_spare                    = st_ap_SSR->u1_spare;

        u2_t_mem_id    = st_tp_CH->u2p_MEM_ID[u2_t_rec_next];
        u2_t_mem_nbyte = (U2)st_tp_CH->u1_mem_nbyte;

        if(u1_a_MEM_TYPE == (U1)OXDC_DIDSSR_MEM_TYPE_RIM){
            vd_g_Rim_WriteOther(u2_t_mem_id, u2_t_mem_nbyte, (const U1 *)&st_t_mem);
        }
        else{
            vd_g_Nvmc_WriteOthr(u2_t_mem_id, u2_t_mem_nbyte, (const U1 *)&st_t_mem);
        }
    }

    return(u1_t_rec_run);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcDidSsrRecUpdt(const ST_OXDC_DID_SSR * st_ap_SSR, const U2 u2_a_TSLOT)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcDidSsrRecUpdt(const ST_OXDC_DID_SSR * st_ap_SSR, const U2 u2_a_TSLOT)
{
    static const U2           u2_s_TYDC_SSR_PAU_TOUT = ((U2)200U / (U2)OXDC_MAIN_TICK) - (U2)1U;

    const ST_OXDC_DID_SSR_CH *  st_tp_CH;
    ST_OXDC_DID_SSR_CTRL *      st_tp_ctrl;
    U4                          u4_t_lpcnt;
    U2                          u2_t_smpl_chk;
    U1                          u1_t_num_rec;
    U1                          u1_t_rec_run;

    u1_t_rec_run = (U1)FALSE;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXDC_DID_SSR_NUM_CH; u4_t_lpcnt++){

        st_tp_CH   = &st_gp_OXDC_DID_SSR_CH_CFG[u4_t_lpcnt];
        st_tp_ctrl = &st_gp_oxdc_did_ssr_ctrl[u4_t_lpcnt];

        if(st_tp_ctrl->u2_pau_elpsd < u2_s_TYDC_SSR_PAU_TOUT){
            st_tp_ctrl->u2_pau_elpsd++;
            u2_t_smpl_chk = (U2)0U;
        }
        else{
            u2_t_smpl_chk = u2_a_TSLOT & st_tp_CH->u2_smpl_tslot;
        }

        u1_t_num_rec = st_tp_CH->u1_num_rec;
        if(st_tp_ctrl->u1_del_cnt < u1_t_num_rec){
            u1_t_rec_run |= (*(stp_gp_OXDC_DID_SSR_IF_BY_CH[u4_t_lpcnt]->fp_u1_DEL))((U1)u4_t_lpcnt);
        }
        else if(u2_t_smpl_chk == (U2)0U){
            /* Do Nothing */
        }
        else if((st_tp_ctrl->u1_rec_last >= u1_t_num_rec) ||
                (st_tp_ctrl->u1_rec_cnt  >  u1_t_num_rec)){
            (*(stp_gp_OXDC_DID_SSR_IF_BY_CH[u4_t_lpcnt]->fp_vd_SYN))((U1)u4_t_lpcnt, (U1)FALSE);
        }
        else{
            u1_t_rec_run |= (*(stp_gp_OXDC_DID_SSR_IF_BY_CH[u4_t_lpcnt]->fp_u1_RUN))((U1)u4_t_lpcnt, st_ap_SSR);
        }
    }

    return(u1_t_rec_run);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    11/23/2023  TI       The functions of oxdocan_ssr are divided into oxdocan_tmstp and oxdocan_did_ssr.                   */
/*                                Removed Nvmc writing function and added Rim writing function.                                      */
/*  1.0.1     2/21/2024  TI       Added Nvmc writing function.                                                                       */
/*  1.0.2     4/15/2024  TI       Changed Odo information format.                                                                    */
/*                                                                                                                                   */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
