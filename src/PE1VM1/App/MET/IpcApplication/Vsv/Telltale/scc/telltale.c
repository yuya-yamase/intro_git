/* 5.5.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Telltale                                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TELLTALE_C_MAJOR                         (5)
#define TELLTALE_C_MINOR                         (5)
#define TELLTALE_C_PATCH                         (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "telltale_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TELLTALE_C_MAJOR != TELLTALE_H_MAJOR) || \
     (TELLTALE_C_MINOR != TELLTALE_H_MINOR) || \
     (TELLTALE_C_PATCH != TELLTALE_H_PATCH))
#error "telltale.c and telltale.h : source and header files are inconsistent!"
#endif

#if ((TELLTALE_C_MAJOR != TELLTALE_CFG_H_MAJOR) || \
     (TELLTALE_C_MINOR != TELLTALE_CFG_H_MINOR) || \
     (TELLTALE_C_PATCH != TELLTALE_CFG_H_PATCH))
#error "telltale.c and telltale_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TT_PACK_BITPOS_MASK                     (0x001FU)
#define TT_PACK_BUFIDX_SHIFT                    (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TT_MSKOR(u4_now, u4_req, u4_msk)    (((u4_now) & (((U4)U4_MAX) ^ (u4_msk))) | ((u4_req) & (u4_msk)))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1       u1_s_tt_slpok;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_TtStsClr(ST_TT_CTLSTS * stp_a_sts);
static void vd_s_TtOwChk(void);
static void vd_s_TtCntup(ST_TT_CTLSTS * stp_a_sts);
static U1   u1_s_TtSelBlink(const ST_TT_CTLSTS * stp_a_STS, const U1 u1_a_REQ);
static U1   u1_s_TtBlinkMinChk(const ST_TT_CTLSTS * stp_a_STS);
static U1   u1_s_TtBlinkPrdChk(const ST_TT_CTLSTS * stp_a_STS);
static U1   u1_s_TtBlinkSelEdge(const U1 u1_a_NOW , const U1 u1_a_NEXT);
static void vd_s_TtBlinkRun(ST_TT_CTLSTS * stp_a_sts, const U1 u1_a_RTRG);
static void vd_s_TtDsAllchk(void);
static U1   u1_s_TtBlinkRngChk(const U1 u1_a_BLINK);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TelltaleInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TelltaleInit(void)
{
    U4  u4_t_loop;
    U1  u1_t_sup;
    U1  u1_t_did;
    U4  u4_t_bitpos;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_TT_NUM_DID ; u4_t_loop++){
        st_gp_tt[u4_t_loop].u4_light  = (U4)0U;
        st_gp_tt[u4_t_loop].u4_sup    = (U4)0U;
        st_gp_tt[u4_t_loop].u4_unlock = (U4)0U;
        st_gp_tt[u4_t_loop].u4_ow_act = (U4)0U;
        st_gp_tt[u4_t_loop].u4_ow_ch  = (U4)0U;
        st_gp_tt[u4_t_loop].u2_tout   = (U2)TT_OW_TOC_MAX;
    }

    u1_s_tt_slpok = (U1)TRUE;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_TT_NUM_SYM ; u4_t_loop++){
        vd_s_TtStsClr(&st_gp_tt_ctlsts[u4_t_loop]);
        u1_t_did    = u1_TT_ID2DID(st_gp_TT_REQ[u4_t_loop].u2_ior);
        u4_t_bitpos = u4_TT_ID2BIT(st_gp_TT_REQ[u4_t_loop].u2_ior);
        u1_t_sup    = (U1)TRUE;
        if(st_gp_TT_REQ[u4_t_loop].fp_u1_SUP != vdp_PTR_NA){
            u1_t_sup = (st_gp_TT_REQ[u4_t_loop].fp_u1_SUP)();
        }
        if(u1_t_sup == (U1)TRUE){
            st_gp_tt[u1_t_did].u4_sup   |= u4_t_bitpos;
        }
    }

    vd_g_TelltaleCfgInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_TelltaleMainTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TelltaleMainTask(void)
{
    U4              u4_t_loop;
    U1              u1_t_req_blink;
    U1              u1_t_sel_blink;
    U1              u1_t_rtrg;
    U1              u1_t_sup;
    ST_TT_CTLSTS *  stp_t_ctlsts;
    U1              u1_t_did;
    U4              u4_t_bitpos;

    vd_g_TelltaleCfgMainStart();

    vd_s_TtOwChk();
    u1_s_tt_slpok = (U1)TRUE;
    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_TT_NUM_SYM ; u4_t_loop++){
        stp_t_ctlsts = &st_gp_tt_ctlsts[u4_t_loop];
        u1_t_did     = u1_TT_ID2DID(st_gp_TT_REQ[u4_t_loop].u2_ior);
        u4_t_bitpos  = u4_TT_ID2BIT(st_gp_TT_REQ[u4_t_loop].u2_ior);
        if(u1_t_did < u1_g_TT_NUM_DID){
            u1_t_sup    = (U1)TRUE;
            if(st_gp_TT_REQ[u4_t_loop].fp_u1_SUP != vdp_PTR_NA){
                u1_t_sup = (st_gp_TT_REQ[u4_t_loop].fp_u1_SUP)();
            }
            if(u1_t_sup == (U1)FALSE){
                vd_s_TtStsClr(stp_t_ctlsts);
                st_gp_tt[u1_t_did].u4_light &= ((U4)U4_MAX ^ u4_t_bitpos);
                st_gp_tt[u1_t_did].u4_sup   &= ((U4)U4_MAX ^ u4_t_bitpos);
            }
            else{
                st_gp_tt[u1_t_did].u4_sup   |= u4_t_bitpos;
                u1_t_req_blink               = (U1)TT_BL_CO_OFF____100P;
                u1_t_rtrg                    = (U1)FALSE;
                if(st_gp_TT_REQ[u4_t_loop].fp_u1_REQ != vdp_PTR_NA){
                    u1_t_req_blink = (st_gp_TT_REQ[u4_t_loop].fp_u1_REQ)(stp_t_ctlsts->u1_blink, &u1_t_rtrg);
                    u1_t_req_blink = u1_s_TtBlinkRngChk(u1_t_req_blink);
                }
                vd_s_TtCntup(stp_t_ctlsts);
                u1_t_sel_blink          = u1_s_TtSelBlink(stp_t_ctlsts, u1_t_req_blink);
                u1_t_rtrg              |= u1_s_TtBlinkSelEdge(stp_t_ctlsts->u1_blink , u1_t_sel_blink);
                stp_t_ctlsts->u1_blink  = u1_t_sel_blink;
                vd_s_TtBlinkRun(stp_t_ctlsts, u1_t_rtrg);
                if(stp_t_ctlsts->u1_act == (U1)TRUE){
                    st_gp_tt[u1_t_did].u4_light |= u4_t_bitpos;
                }else{
                    st_gp_tt[u1_t_did].u4_light &= ((U4)U4_MAX ^ u4_t_bitpos);
                }
                if(stp_t_ctlsts->u1_blink != (U1)TT_BL_CO_OFF____100P){
                    u1_s_tt_slpok = (U1)FALSE;
                }
            }
        }
    }

    vd_g_TelltaleCfgMainFinish();

}
/*===================================================================================================================================*/
/*  U1      u1_g_TelltaleShtdwnOk(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TelltaleShtdwnOk(void)
{
    return(u1_s_tt_slpok);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TelltaleBySym(const U1 u1_a_SYM, const U1 u1_a_OW_EN, U1 * u1p_t_owch)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TelltaleBySym(const U1 u1_a_SYM, const U1 u1_a_OW_EN, U1 * u1p_t_owch)
{
    U4  u4_t_sts;
    U4  u4_t_bit;
    U1  u1_t_did;
    U1  u1_t_ret;
    U4  u4_t_ow_ch;

    u1_t_ret = (U1)FALSE;
    if(u1_a_SYM < u1_g_TT_NUM_SYM){
        u1_t_did = u1_TT_ID2DID(st_gp_TT_REQ[u1_a_SYM].u2_ior);
        if(u1_t_did < u1_g_TT_NUM_DID){
            u4_t_bit  = u4_TT_ID2BIT(st_gp_TT_REQ[u1_a_SYM].u2_ior);
            u4_t_sts  = st_gp_tt[u1_t_did].u4_light;
            u4_t_sts &= st_gp_tt[u1_t_did].u4_sup;

            if((u1_a_OW_EN                  == (U1)TRUE             ) &&
               ((st_gp_tt[u1_t_did].u2_tout <  u2_g_TT_OW_TOUT ) ||
                (st_gp_tt[u1_t_did].u2_tout >= (U2)U2_MAX      )    )    ){
                u4_t_sts = TT_MSKOR(u4_t_sts, st_gp_tt[u1_t_did].u4_ow_act, st_gp_tt[u1_t_did].u4_ow_ch);
            }
            if((u4_t_sts & u4_t_bit) != (U4)0U){
                u1_t_ret = (U1)TRUE;
            }
            if(u1p_t_owch != vdp_PTR_NA){
                u4_t_ow_ch  = st_gp_tt[u1_t_did].u4_ow_ch & st_gp_tt[u1_t_did].u4_sup;
                *u1p_t_owch = (U1)FALSE;
                if((u4_t_ow_ch & u4_t_bit) != (U4)0U){
                    *u1p_t_owch = (U1)TRUE;
                }
            }
        }
    }
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U4      u4_g_TelltaleByDID(const U1 u1_a_DID, const U1 u1_a_OW_EN)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_TelltaleByDID(const U1 u1_a_DID, const U1 u1_a_OW_EN)
{
    U4  u4_t_ret;

    u4_t_ret = (U4)0U;
    if(u1_a_DID < u1_g_TT_NUM_DID){
        u4_t_ret  = st_gp_tt[u1_a_DID].u4_light;
        u4_t_ret &= st_gp_tt[u1_a_DID].u4_sup;

        if((u1_a_OW_EN                  == (U1)TRUE             ) &&
           ((st_gp_tt[u1_a_DID].u2_tout <  u2_g_TT_OW_TOUT ) ||
            (st_gp_tt[u1_a_DID].u2_tout >= (U2)U2_MAX      )    )    ){
            u4_t_ret = TT_MSKOR(u4_t_ret, st_gp_tt[u1_a_DID].u4_ow_act, st_gp_tt[u1_a_DID].u4_ow_ch);
        }
    }

    return(u4_t_ret);
}
/*===================================================================================================================================*/
/*  void    vd_g_TelltaleBitPack(const ST_TT_BITPACK * st_ap_PACK, U4 * u4_ap_buf, const U1 u1_a_NWORD, const U1 u1_a_OW_EN)         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TelltaleBitPack(const ST_TT_BITPACK * st_ap_PACK, U4 * u4_ap_buf, const U1 u1_a_NWORD, const U1 u1_a_OW_EN)
{
    U4                          u4_t_loop;
    U1                          u1_t_srcid;
    U2                          u2_t_dstpos;
    U2                          u2_t_storeidx;
    U4                          u4_t_act;
    U4                          u4_t_dstbit;
    U1                          u1_t_srcdid;
    U4                          u4_t_srcbit;
    
    if((st_ap_PACK != (ST_TT_BITPACK *)vdp_PTR_NA) && (u4_ap_buf != vdp_PTR_NA)){
        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)st_ap_PACK->u1_NUM ; u4_t_loop++){
            u1_t_srcid    = (st_ap_PACK->stp_SRC2DST[u4_t_loop]).u1_srcid;
            u2_t_dstpos   = (st_ap_PACK->stp_SRC2DST[u4_t_loop]).u2_dstpos;
            u2_t_storeidx = (U2)(u2_t_dstpos >> TT_PACK_BUFIDX_SHIFT);
            if((u1_t_srcid    < u1_g_TT_NUM_SYM) &&
               (u2_t_storeidx < (U2)u1_a_NWORD )    ){
                u1_t_srcdid   = u1_TT_ID2DID(st_gp_TT_REQ[u1_t_srcid].u2_ior);
                u4_t_srcbit   = u4_TT_ID2BIT(st_gp_TT_REQ[u1_t_srcid].u2_ior);
                u4_t_act      = st_gp_tt[u1_t_srcdid].u4_light;
                u4_t_act     &= st_gp_tt[u1_t_srcdid].u4_sup;
                u4_t_act     &= u4_t_srcbit;
                if((u1_a_OW_EN                    == (U1)TRUE              ) &&
                   ((st_gp_tt[u1_t_srcdid].u2_tout <  u2_g_TT_OW_TOUT ) ||
                    (st_gp_tt[u1_t_srcdid].u2_tout >= (U2)U2_MAX      )    )     ){
                    u4_t_act  = TT_MSKOR(u4_t_act, st_gp_tt[u1_t_srcdid].u4_ow_act, st_gp_tt[u1_t_srcdid].u4_ow_ch);
                    u4_t_act &= u4_t_srcbit;
                }
                u4_t_dstbit   = (U4)TRUE << (u2_t_dstpos & (U2)TT_PACK_BITPOS_MASK);
                if(u4_t_act != (U4)0U){
                    u4_ap_buf[u2_t_storeidx] |= u4_t_dstbit;
                }else{
                    u4_ap_buf[u2_t_storeidx] &= ((U4)U4_MAX ^ u4_t_dstbit);
                }
            }
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TelltaleOwUnlock(const U1 u1_a_DID, const U4 u4_a_KEY)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TelltaleOwUnlock(const U1 u1_a_DID, const U4 u4_a_KEY)
{
    if(u1_a_DID < u1_g_TT_NUM_DID){
        st_gp_tt[u1_a_DID].u4_unlock = u4_a_KEY;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TelltaleOwAct(const U1 u1_a_DID, const U4 u4_a_OW_CH , const U4 u4_a_OW_ACT)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TelltaleOwAct(const U1 u1_a_DID, const U4 u4_a_OW_CH , const U4 u4_a_OW_ACT)
{
    U1  u1_t_did_d2981;

    if(u1_a_DID  <  u1_g_TT_NUM_DID ){
        if(st_gp_tt[u1_a_DID].u4_unlock == (U4)TT_OW_UNLOCK ){
            st_gp_tt[u1_a_DID].u2_tout    = (U2)U2_MAX;
            st_gp_tt[u1_a_DID].u4_ow_ch   = u4_a_OW_CH  & st_gp_tt[u1_a_DID].u4_sup;
            st_gp_tt[u1_a_DID].u4_ow_act  = u4_a_OW_ACT & st_gp_tt[u1_a_DID].u4_sup;

            u1_t_did_d2981 = u1_TT_ID2DID(u2_g_TT_IOR_D2981_B06_7_ALLON);
            if(u1_a_DID == u1_t_did_d2981){
                vd_s_TtDsAllchk();
            }
        }
        st_gp_tt[u1_a_DID].u4_unlock = (U4)0U;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TelltaleOwDeAct(const U1 u1_a_DID)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TelltaleOwDeAct(const U1 u1_a_DID)
{
    if(u1_a_DID < u1_g_TT_NUM_DID){

        st_gp_tt[u1_a_DID].u2_tout   = (U2)TT_OW_TOC_MAX;
        st_gp_tt[u1_a_DID].u4_ow_act = (U4)0U;
        st_gp_tt[u1_a_DID].u4_ow_ch  = (U4)0U;

        st_gp_tt[u1_a_DID].u4_unlock = (U4)0U;
    }
}
/*===================================================================================================================================*/
/*  U4      u4_g_TelltaleSupByDID(const U1 u1_a_DID)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_TelltaleSupByDID(const U1 u1_a_DID)
{
    U4  u4_t_sup;

    u4_t_sup = (U4)0U;
    if(u1_a_DID < u1_g_TT_NUM_DID){
        u4_t_sup = st_gp_tt[u1_a_DID].u4_sup;
    }
    return(u4_t_sup);
}

/*===================================================================================================================================*/
/*  static void         vd_s_TtStsClr(ST_TT_CTLSTS * stp_a_sts)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_TtStsClr(ST_TT_CTLSTS * stp_a_sts)
{
    stp_a_sts->u1_blink    = (U1)TT_BL_CO_OFF____100P;
    stp_a_sts->u1_act      = (U1)FALSE;
    stp_a_sts->u1_step_cnt = (U1)0U;
    stp_a_sts->u1_cycl_cnt = (U1)0U;
    stp_a_sts->u2_elapstim = (U2)0U;
}
/*===================================================================================================================================*/
/*  static void           vd_s_TtOwChk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void           vd_s_TtOwChk(void)
{
    U4  u4_t_loop;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_TT_NUM_DID ; u4_t_loop++){
        st_gp_tt[u4_t_loop].u4_unlock = (U4)0U;
        if(st_gp_tt[u4_t_loop].u2_tout >= (U2)U2_MAX){
            st_gp_tt[u4_t_loop].u2_tout = (U2)0U;
        }
        else if(st_gp_tt[u4_t_loop].u2_tout >= (U2)TT_OW_TOC_MAX){
            st_gp_tt[u4_t_loop].u2_tout = (U2)TT_OW_TOC_MAX;
        }
        else{
            st_gp_tt[u4_t_loop].u2_tout++; /* QAC over-detection */
        }
        if(st_gp_tt[u4_t_loop].u2_tout >= u2_g_TT_OW_TOUT){
            st_gp_tt[u4_t_loop].u4_ow_act = (U4)0U;
            st_gp_tt[u4_t_loop].u4_ow_ch  = (U4)0U;
        }
    }

}

/*===================================================================================================================================*/
/*  static void     vd_s_TtCntup(ST_TT_CTLSTS * stp_a_sts)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_TtCntup(ST_TT_CTLSTS * stp_a_sts)
{
    U1                  u1_t_seq_end; 
    U2                  u2_t_elps_end;

    if(stp_a_sts->u2_elapstim < (U2)TT_BLINK_ELAPS_MAX){
        stp_a_sts->u2_elapstim = stp_a_sts->u2_elapstim + (U2)1U;
    }else{
        stp_a_sts->u2_elapstim = (U2)TT_BLINK_ELAPS_MAX;
    }
    if(stp_a_sts->u1_blink >= u1_g_TT_NUM_BLINK){
        stp_a_sts->u1_blink = (U1)TT_BL_CO_OFF____100P;
    }
    u1_t_seq_end  = st_gp_TT_BLINK[stp_a_sts->u1_blink].u1_num_opd - (U1)1U;
    u2_t_elps_end = st_gp_TT_BLINK[stp_a_sts->u1_blink].stp_OPD[u1_t_seq_end].u2_dur;
    if(stp_a_sts->u2_elapstim >= u2_t_elps_end){
        if(stp_a_sts->u1_cycl_cnt < (U1)U1_MAX){
            stp_a_sts->u1_cycl_cnt = stp_a_sts->u1_cycl_cnt + (U1)1U;
        }
    }
}

/*===================================================================================================================================*/
/*  static U1    u1_s_TtSelBlink(const ST_TT_CTLSTS * stp_a_STS , const U1 u1_a_REQ)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_TtSelBlink(const ST_TT_CTLSTS * stp_a_STS , const U1 u1_a_REQ)
{
    U1  u1_t_cmpchk;
    U1  u1_t_selblink;

    u1_t_cmpchk  = u1_s_TtBlinkMinChk(stp_a_STS);
    u1_t_cmpchk &= u1_s_TtBlinkPrdChk(stp_a_STS);

    if(u1_t_cmpchk == (U1)TRUE){
        u1_t_selblink = u1_a_REQ;
    }
    else{
        u1_t_selblink = stp_a_STS->u1_blink;
    }

    return(u1_t_selblink);

}
/*===================================================================================================================================*/
/*  static U1 u1_s_TtBlinkMinChk(const ST_TT_CTLSTS * stp_a_STS)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_TtBlinkMinChk(const ST_TT_CTLSTS * stp_a_STS)
{
    U1  u1_t_chk;
    U1  u1_t_min; 

    u1_t_min = st_gp_TT_BLINK[stp_a_STS->u1_blink].u1_min_cycl;
    u1_t_chk = (U1)FALSE;
    if(u1_t_min <= stp_a_STS->u1_cycl_cnt){
        u1_t_chk = (U1)TRUE;
    }
    return(u1_t_chk);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_TtBlinkPrdChk(const ST_TT_CTLSTS * stp_a_STS)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_TtBlinkPrdChk(const ST_TT_CTLSTS * stp_a_STS)
{
    U1                  u1_t_chk;
    U1                  u1_t_num;
    U2                  u2_t_dur;

    u1_t_num  = st_gp_TT_BLINK[stp_a_STS->u1_blink].u1_num_opd - (U1)1U;
    u2_t_dur  = st_gp_TT_BLINK[stp_a_STS->u1_blink].stp_OPD[u1_t_num].u2_dur;
    u1_t_chk  = (U1)FALSE;
    if(st_gp_TT_BLINK[stp_a_STS->u1_blink].u1_swc_cycl == (U1)TRUE){
        if(stp_a_STS->u2_elapstim <= (U2)1U){
            u1_t_chk = (U1)TRUE;
        }
        if(u2_t_dur != (U2)0U){
            if((stp_a_STS->u2_elapstim % u2_t_dur) == (U2)0U ){
                u1_t_chk = (U1)TRUE;
            }
        }
    }
    else{
        u1_t_chk = (U1)TRUE;
    }

    return(u1_t_chk);
}

/*===================================================================================================================================*/
/*  static void vd_s_TtBlinkRun(ST_TT_CTLSTS * stp_a_sts, const U1 u1_a_RTRG)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_TtBlinkRun(ST_TT_CTLSTS * stp_a_sts, const U1 u1_a_RTRG)
{
    U1                  u1_t_num;
    U2                  u2_t_dur;
    const ST_TT_OPD *   stp_t_OPD;

    stp_t_OPD = st_gp_TT_BLINK[stp_a_sts->u1_blink].stp_OPD;
    u1_t_num  = st_gp_TT_BLINK[stp_a_sts->u1_blink].u1_num_opd;
    if((u1_a_RTRG              == (U1)TRUE ) ||
       (stp_a_sts->u1_step_cnt >= u1_t_num )    ){
        stp_a_sts->u1_step_cnt = (U1)0U;
        stp_a_sts->u1_cycl_cnt = (U1)0U;
        stp_a_sts->u2_elapstim = (U2)0U;
        stp_a_sts->u1_act      = stp_t_OPD[0].u1_act;
    }
    else{
        u2_t_dur  = stp_t_OPD[stp_a_sts->u1_step_cnt].u2_dur;
        if( stp_a_sts->u2_elapstim < u2_t_dur){
            stp_a_sts->u1_act = stp_t_OPD[stp_a_sts->u1_step_cnt].u1_act;
        }
        else{
            stp_a_sts->u1_step_cnt = stp_a_sts->u1_step_cnt + (U1)1U;
            if(stp_a_sts->u1_step_cnt >= u1_t_num){
                stp_a_sts->u1_step_cnt  = (U1)0U;
                stp_a_sts->u2_elapstim  = (U2)0U;
            }
            stp_a_sts->u1_act = stp_t_OPD[stp_a_sts->u1_step_cnt].u1_act;
        }
    }
}
/*===================================================================================================================================*/
/*  static U1 u1_s_TtBlinkSelEdge(const U1 u1_a_NOW , const U1 u1_a_NEXT)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_TtBlinkSelEdge(const U1 u1_a_NOW , const U1 u1_a_NEXT)
{
    U1  u1_t_chk;

    u1_t_chk = (U1)FALSE;
    if(u1_a_NEXT  != u1_a_NOW){
        u1_t_chk = (U1)TRUE;
    }
    return(u1_t_chk);
}
/*===================================================================================================================================*/
/*  static void vd_s_TtDsAllchk(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_TtDsAllchk(void)
{

    U4  u4_t_allon_bit;
    U1  u1_t_pos;
    U4  u4_t_allon_act;
    U4  u4_t_loop;

    u4_t_allon_bit = (U4)TRUE << (u2_g_TT_IOR_D2981_B06_7_ALLON & (U2)TT_IOR_BITMASK);
    u1_t_pos       = u1_TT_ID2DID(u2_g_TT_IOR_D2981_B06_7_ALLON);
    u4_t_allon_act = st_gp_tt[u1_t_pos].u4_ow_act & u4_t_allon_bit;

    if(u4_t_allon_act != (U4)0U){
        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_TT_NUM_DID ; u4_t_loop++){
            st_gp_tt[u4_t_loop].u2_tout    = (U2)U2_MAX;
            st_gp_tt[u4_t_loop].u4_ow_ch   = st_gp_tt[u4_t_loop].u4_sup;
            st_gp_tt[u4_t_loop].u4_ow_act  = st_gp_tt[u4_t_loop].u4_sup;
        }
    }
}
/*===================================================================================================================================*/
/*  static U1   u1_s_TtBlinkRngChk(const U1 u1_a_BLINK)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_TtBlinkRngChk(const U1 u1_a_BLINK)
{
    U1  u1_t_blink;

    if(u1_a_BLINK >= u1_g_TT_NUM_BLINK){
        u1_t_blink = (U1)TT_BL_CO_OFF____100P;
    }
    else{
        u1_t_blink = u1_a_BLINK;
    }
    return(u1_t_blink);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  3.0.0    01/25/2018  TA       New.                                                                                               */
/*  3.1.0    02/14/2018  TA       Add To synchronize the blinking start timing                                                       */
/*  3.2.0    06/05/2018  TA       Change it so that a result of the individual indicator processing is reflected                     */
/*                                at the time of blinking async.                                                                     */
/*  3.2.1    12/06/2018  TA       add clear path u1p_t_enbl                                                                          */
/*  3.3.0    01/10/2019  TA       Refactoring                                                                                        */
/*  5.0.0    07/11/2019  TA       Refactoring                                                                                        */
/*  5.1.0    04/23/2020  TA       Refactoring                                                                                        */
/*  5.2.0    04/29/2020  TA       Add supprort bit generation                                                                        */
/*  5.3.0    05/21/2020  TA       Add TT_IOR_D2981_B06_7_ALLON judgement                                                             */
/*  5.4.0    07/15/2020  ST       Add CANDI(ESI) supprort bit generation                                                             */
/*  5.5.0    07/12/2021  TA       Delete CANDI(ESI) supprort bit generation. Add TT_IOR_D2912_B08_6_YEL_RSCAOFF                      */
/*  5.5.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*                                                                                                                                   */
/*  * TA  = Teruyuki Anjima, Denso                                                                                                   */
/*  * ST  = Syo Toyoda, KSE                                                                                                          */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

