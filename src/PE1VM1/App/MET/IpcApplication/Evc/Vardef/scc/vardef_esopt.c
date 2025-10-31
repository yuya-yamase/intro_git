/* 2.6.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Vardef Electrical System Option.                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_ESOPT_C_MAJOR                     (2)
#define VARDEF_ESOPT_C_MINOR                     (6)
#define VARDEF_ESOPT_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef_esopt_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_ESOPT_C_MAJOR != VARDEF_ESOPT_H_MAJOR) || \
     (VARDEF_ESOPT_C_MINOR != VARDEF_ESOPT_H_MINOR) || \
     (VARDEF_ESOPT_C_PATCH != VARDEF_ESOPT_H_PATCH))
#error "vardef_esopt.c and vardef_esopt.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_ESOPT_C_MAJOR != VARDEF_ESOPT_CFG_H_MAJOR) || \
     (VARDEF_ESOPT_C_MINOR != VARDEF_ESOPT_CFG_H_MINOR) || \
     (VARDEF_ESOPT_C_PATCH != VARDEF_ESOPT_CFG_H_PATCH))
#error "vardef_esopt.c and vardef_esopt_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_ESO_NVM_SYN_FIN                      (0x00U)
#define VDF_ESO_NVM_SYN_RUN                      (0x01U)
#define VDF_ESO_NVM_SYN_STA                      (0x02U)

#define VDF_ESO_IGROFFEG_OFF                     (0x0000U)
#define VDF_ESO_IGROFFEG_ON                      (0x0001U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2             u2_s_vdf_eso_res_tocnt;
static U2             u2_s_vdf_eso_nvm_tocnt;
static U2             u2_s_vdf_eso_vom_act;

static U1             u1_s_vdf_eso_vom_tocnt;
static U1             u1_s_vdf_eso_res_ctrl;
static U2             u2_s_vdf_eso_igredge;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_VdfEsoInit(void);
static void    vd_s_VdfEsoVomEvTout(const U2 u2_a_VOM);
static U1      u1_s_VdfEsoAvaRx(const ST_VDF_ESO_CH * st_ap_CH, const U1 u1_a_RXEV_CNT, ST_VDF_ESO_RX * st_ap_rx);

static void    vd_s_VdfEsoNvmSynchk(const U2 u2_a_EOM);
static U1      u1_s_VdfEsoNvmInit(const U1 u1_a_NWO_EN);
static U1      u1_s_VdfEsoNvmUpdt(const U1 u1_a_NWO_EN);
static U1      u1_s_VdfEsoNvmNext(const U1 u1_a_NWO_EN, const U2 u2_a_NID, const U4 u4_a_NEXT);
static U1      u1_s_VdfEsoNvmNextUpdt(const U1 u1_a_NWO_EN, const U2 u2_a_NID, const U4 u4_a_NEXT);

static void    vd_s_VdfEsoNvmReschk(const U1 u1_a_SYN_CHK);

static U1      u1_s_VdfEsoGetRxevCnt(const U1 u1_a_INPUT_TYPE, const U2 u2_a_MSG);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VardefEsOptBonInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefEsOptBonInit(void)
{
    U4                        u4_t_lpcnt;
    U4                        u4_t_ch_rx;
    U4                        u4_t_ch_nvm;
    U4                        u4_t_ch_bra;
    U4                        u4_t_log_ava;

    U1                        u1_t_nvm_chk;

    vd_s_VdfEsoInit();

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_VDF_ESO_NOW_AVA; u4_t_lpcnt++){

        u4_t_ch_nvm  = st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_nvm;
        u4_t_ch_rx   = st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_rx;
        u4_t_ch_bra  = ((U4)U4_MAX ^ u4_t_ch_nvm) & u4_t_ch_rx;
        u4_t_ch_nvm &= u4_t_ch_rx;

        u4_t_log_ava = (U4)0U;
        u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts(st_gp_VDF_ESO_AVA[u4_t_lpcnt].u2_nid, &u4_t_log_ava);
        if(u1_t_nvm_chk == (U1)NVMC_STATUS_KIND_OK){
            u4_t_log_ava &= u4_t_ch_nvm;
        }
        else{
            u4_t_log_ava  = st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_unk & u4_t_ch_nvm;
        }
        u4_t_log_ava |= (st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_ini & u4_t_ch_bra);

        u4_gp_vdf_eso_ava[u4_t_lpcnt] = u4_t_log_ava;

        vd_g_Rim_WriteU4(st_gp_VDF_ESO_AVA[u4_t_lpcnt].u2_bid, u4_t_log_ava);
    }

    vd_g_VardefEsOptCfgInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefEsOptRstwkInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefEsOptRstwkInit(void)
{
    U4                        u4_t_lpcnt;
    U4                        u4_t_ch_rx;
    U4                        u4_t_ch_nvm;
    U4                        u4_t_ch_bra;
    U4                        u4_t_log_nvm;
    U4                        u4_t_log_bra;

    U1                        u1_t_log_chk;

    vd_s_VdfEsoInit();

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_VDF_ESO_NOW_AVA; u4_t_lpcnt++){

        u4_t_ch_nvm  = st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_nvm;
        u4_t_ch_rx   = st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_rx;
        u4_t_ch_bra  = ((U4)U4_MAX ^ u4_t_ch_nvm) & u4_t_ch_rx;
        u4_t_ch_nvm &= u4_t_ch_rx;

        u4_t_log_nvm = (U4)0U;
        u1_t_log_chk = u1_g_Nvmc_ReadU4withSts(st_gp_VDF_ESO_AVA[u4_t_lpcnt].u2_nid, &u4_t_log_nvm);
        if(u1_t_log_chk == (U1)NVMC_STATUS_KIND_OK){
            u4_t_log_nvm &= u4_t_ch_nvm;
        }
        else{
            u4_t_log_nvm  = st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_unk & u4_t_ch_nvm;
        }

        u4_t_log_bra = (U4)0U;
        u1_t_log_chk = u1_g_Rim_ReadU4withStatus(st_gp_VDF_ESO_AVA[u4_t_lpcnt].u2_bid, &u4_t_log_bra) & (U1)RIM_RESULT_KIND_MASK;
        if(u1_t_log_chk == (U1)RIM_RESULT_KIND_OK){
            u4_t_log_bra &= u4_t_ch_bra;
        }
        else{
            u4_t_log_bra  = st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_ini & u4_t_ch_bra;
        }

        u4_gp_vdf_eso_ava[u4_t_lpcnt] = u4_t_log_nvm | u4_t_log_bra;
    }

    vd_g_VardefEsOptCfgInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefEsOptOpemdEvhk(const U2 u2_a_EOM)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefEsOptOpemdEvhk(const U2 u2_a_EOM)
{
    u2_s_vdf_eso_vom_act   &= u2_a_EOM;
    u1_s_vdf_eso_vom_tocnt  = (U1)U1_MAX;
}
/*===================================================================================================================================*/
/*  void        vd_g_VardefEsOptMainTask(const U2 u2_a_EOM, const U1 u1_a_TSLOT)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void        vd_g_VardefEsOptMainTask(const U2 u2_a_EOM, const U1 u1_a_TSLOT)
{
    const ST_VDF_ESO_CH *     st_tp_CH;

    ST_VDF_ESO_RX *           st_tp_rx;

    U4                        u4_t_lpcnt;
    U4                        u4_t_lpend;

    U4                        u4_t_idx;
    U4                        u4_t_bit;

    U1                        u1_t_input_type;
    U1                        u1_t_input_type_next;

    U2                        u2_t_msg_rx;
    U2                        u2_t_msg_next;

    U2                        u2_t_vom_act;
    U2                        u2_t_vom_chk;
    U2                        u2_t_rxc_act;

    U2                        u2_t_ch;

    U1                        u1_t_rxev_cnt;
    U1                        u1_t_ava_rx;

    u2_t_vom_act = u2_a_EOM & (U2)VDF_EOM_VOM_ON;
    vd_s_VdfEsoVomEvTout(u2_t_vom_act);

    u4_t_lpcnt  = (U4)u2_g_VDF_ESO_NUM_RX_BY_RUN * (U4)u1_a_TSLOT;
    u4_t_lpend  = u4_t_lpcnt + (U4)u2_g_VDF_ESO_NUM_RX_BY_RUN;
    if(u4_t_lpend > (U4)u2_g_VDF_ESO_NUM_RX){
        u4_t_lpend = (U4)u2_g_VDF_ESO_NUM_RX;
    }

    u1_t_input_type = (U1)U1_MAX;
    u2_t_msg_rx     = (U2)U2_MAX;
    u1_t_rxev_cnt   = u1_g_VDF_ESO_RXC_INT;
    while(u4_t_lpcnt < u4_t_lpend){

        st_tp_CH      = &st_gp_VDF_ESO_CH[u4_t_lpcnt];
        u1_t_input_type_next = st_tp_CH->u1_input_type;
        u2_t_msg_next = st_tp_CH->u2_msg_rx;

        if((u1_t_input_type_next != u1_t_input_type) ||
           (u2_t_msg_next != u2_t_msg_rx)){
            u1_t_rxev_cnt   = u1_s_VdfEsoGetRxevCnt(u1_t_input_type_next, u2_t_msg_next);
            u1_t_input_type = u1_t_input_type_next;
            u2_t_msg_rx     = u2_t_msg_next;
        }

        st_tp_rx     = &st_gp_vdf_eso_rx[u4_t_lpcnt];
        u2_t_rxc_act = st_tp_CH->u2_vom_act;
        u2_t_vom_chk = u2_s_vdf_eso_vom_act & u2_t_rxc_act;
        if(u2_t_vom_chk == (U2)0U){
            st_tp_rx->u2_tim_elpsd = (U2)U2_MAX;
            st_tp_rx->u1_rxc_start = u1_g_VDF_ESO_RXC_INT;
            st_tp_rx->u1_ava_rx    = (U1)VDF_ESO_AVA_RX_UNK;
        }

        u2_t_vom_chk = u2_t_vom_act & u2_t_rxc_act;
        if(u2_t_vom_chk != (U2)0U){

            u1_t_ava_rx = u1_s_VdfEsoAvaRx(st_tp_CH, u1_t_rxev_cnt, st_tp_rx);

            u2_t_ch     = st_tp_CH->u2_eso_ch;
            u4_t_idx    = (U4)u2_t_ch >> VDF_ESO_CH_LSB_AVA_IDX;
            if((u4_t_idx    >= (U4)u1_g_VDF_ESO_NOW_AVA) ||
               (u1_t_ava_rx >= (U1)VDF_ESO_AVA_RX_UNK  )){
            }
            else if(u1_t_ava_rx == (U1)VDF_ESO_AVA_RX_ACT){
                u4_t_bit = (U4)0x00000001U << (u2_t_ch & (U2)VDF_ESO_CH_BIT_AVA_LSB);
                u4_gp_vdf_eso_ava[u4_t_idx] |= u4_t_bit;
            } 
            else{
                u4_t_bit = (U4)0x00000001U << (u2_t_ch & (U2)VDF_ESO_CH_BIT_AVA_LSB);
                u4_gp_vdf_eso_ava[u4_t_idx] &= ((U4)U4_MAX ^ u4_t_bit);
            }
        }

        u4_t_lpcnt++;
    }

    if(u1_a_TSLOT >= (U1)VDF_TSLOT_4){
        vd_s_VdfEsoNvmSynchk(u2_a_EOM);
    }
}
/*===================================================================================================================================*/
/*  U1          u1_g_VardefEsOptAvaByCh(const U2 u2_a_CH)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1          u1_g_VardefEsOptAvaByCh(const U2 u2_a_CH)
{
    U2                        u2_t_idx;
    U2                        u2_t_lsb;
    U1                        u1_t_ava;

    u2_t_idx = u2_VDF_ESO_CH_TO_IDX(u2_a_CH);
    if(u2_t_idx < (U2)u1_g_VDF_ESO_NOW_AVA){
        u2_t_lsb = u2_VDF_ESO_CH_TO_LSB(u2_a_CH);
        u1_t_ava = (U1)(u4_gp_vdf_eso_ava[u2_t_idx] >> u2_t_lsb) & (U1)TRUE;
    }
    else{
        u1_t_ava = (U1)FALSE;
    }

    return(u1_t_ava);
}

/*===================================================================================================================================*/
/*  void        vd_g_VardefEsOptAva(U4 * u4_ap_ava, const U1 u1_a_NWORD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void        vd_g_VardefEsOptAva(U4 * u4_ap_ava, const U1 u1_a_NWORD)
{
    U4                        u4_t_lpcnt;
    U4                        u4_t_nword;

    if(u4_ap_ava != vdp_PTR_NA){

        if(u1_a_NWORD > u1_g_VDF_ESO_NOW_AVA){
            u4_t_nword = (U4)u1_g_VDF_ESO_NOW_AVA;
        }
        else{
            u4_t_nword = (U4)u1_a_NWORD;
        }

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_nword; u4_t_lpcnt++){
            u4_ap_ava[u4_t_lpcnt] = u4_gp_vdf_eso_ava[u4_t_lpcnt];
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefEsOptReset(const U1 u1_a_RUN)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefEsOptReset(const U1 u1_a_RUN)
{
    U4                        u4_t_lpcnt;

    if((u1_a_RUN              == (U1)TRUE           ) &&
       (u1_s_vdf_eso_res_ctrl >  (U1)VDF_ESO_RES_RUN)){

        u2_s_vdf_eso_res_tocnt = (U2)0U;
        u2_s_vdf_eso_vom_act   = (U2)0U;

        u1_s_vdf_eso_vom_tocnt = (U1)U1_MAX;
        u1_s_vdf_eso_res_ctrl  = (U1)VDF_ESO_RES_RUN;

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_VDF_ESO_NOW_AVA; u4_t_lpcnt++){
            u4_gp_vdf_eso_ava[u4_t_lpcnt] = st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_ini;
        }
        vd_g_VardefEsOptCfgInit();
    }

    return(u1_s_vdf_eso_res_ctrl);
}
/*===================================================================================================================================*/
/*  static void        vd_s_VdfEsoInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void        vd_s_VdfEsoInit(void)
{
    U4                        u4_t_lpcnt;

    u2_s_vdf_eso_nvm_tocnt = (U2)U2_MAX;
    u2_s_vdf_eso_res_tocnt = (U2)U2_MAX;
    u2_s_vdf_eso_vom_act   = (U2)0U;

    u1_s_vdf_eso_vom_tocnt = (U1)U1_MAX;
    u1_s_vdf_eso_res_ctrl  = (U1)VDF_ESO_RES_UNK;
    u2_s_vdf_eso_igredge = (U2)VDF_ESO_IGROFFEG_OFF;
    
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_g_VDF_ESO_NUM_RX; u4_t_lpcnt++){
        st_gp_vdf_eso_rx[u4_t_lpcnt].u2_tim_elpsd = (U2)U2_MAX;
        st_gp_vdf_eso_rx[u4_t_lpcnt].u1_rxc_start = u1_g_VDF_ESO_RXC_INT;
        st_gp_vdf_eso_rx[u4_t_lpcnt].u1_ava_rx    = (U1)VDF_ESO_AVA_RX_UNK;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdfEsoVomEvTout(const U2 u2_a_VOM)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdfEsoVomEvTout(const U2 u2_a_VOM)
{
    if(u1_s_vdf_eso_vom_tocnt >= (U1)U1_MAX){
        u1_s_vdf_eso_vom_tocnt = (U1)0U;
    }
    else if(u1_s_vdf_eso_vom_tocnt >= (U1)VDF_NUM_TSLOT){
        u1_s_vdf_eso_vom_tocnt = (U1)VDF_NUM_TSLOT;
    }
    else{
        u1_s_vdf_eso_vom_tocnt++;
    }

    if(u1_s_vdf_eso_vom_tocnt >= (U1)VDF_NUM_TSLOT){
        u2_s_vdf_eso_vom_act = u2_a_VOM;
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_VdfEsoAvaRx(const ST_VDF_ESO_CH * st_ap_CH, const U1 u1_a_RXEV_CNT, ST_VDF_ESO_RX * st_ap_rx)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_VdfEsoAvaRx(const ST_VDF_ESO_CH * st_ap_CH, const U1 u1_a_RXEV_CNT, ST_VDF_ESO_RX * st_ap_rx)
{
    U4                        u4_t_tim_elpsd;

    U2                        u2_t_rxi;
    U2                        u2_t_min;

    U1                        u1_t_ava_rx;

    if(st_ap_CH->fp_u1_AVA_RX != vdp_PTR_NA){
        u1_t_ava_rx = (*st_ap_CH->fp_u1_AVA_RX)();
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }

    if((u1_a_RXEV_CNT          >  u1_g_VDF_ESO_RXC_MAX  ) ||
       (st_ap_rx->u1_rxc_start >  u1_g_VDF_ESO_RXC_MAX  ) ||
       (u1_t_ava_rx            >= (U1)VDF_ESO_AVA_RX_UNK)){

        st_ap_rx->u1_rxc_start = u1_a_RXEV_CNT;
        st_ap_rx->u1_ava_rx    = (U1)VDF_ESO_AVA_RX_UNK;
        u1_t_ava_rx            = (U1)VDF_ESO_AVA_RX_UNK;
    }
    else if(u1_t_ava_rx == st_ap_rx->u1_ava_rx){

        u2_t_rxi               = (U2)u1_a_RXEV_CNT - (U2)st_ap_rx->u1_rxc_start;
        u2_t_rxi               = (u2_t_rxi & (U2)u1_g_VDF_ESO_RXC_MAX) + (U2)1U;
        u2_t_min               = st_ap_CH->u2_rxc_min[u1_t_ava_rx];

        if(u2_t_rxi < u2_t_min){
            u1_t_ava_rx        = (U1)VDF_ESO_AVA_RX_UNK;
        }
    }
    else if(st_ap_CH->u2_rxc_min[u1_t_ava_rx] == (U2)0U){
        st_ap_rx->u1_rxc_start = u1_a_RXEV_CNT;
        st_ap_rx->u1_ava_rx    = u1_t_ava_rx;
    }
    else if(st_ap_rx->u1_rxc_start != u1_a_RXEV_CNT){

        st_ap_rx->u1_rxc_start = u1_a_RXEV_CNT;
        st_ap_rx->u1_ava_rx    = u1_t_ava_rx;

        if(st_ap_CH->u2_rxc_min[u1_t_ava_rx] > (U2)1U){
            u1_t_ava_rx        = (U1)VDF_ESO_AVA_RX_UNK;
        }
    }
    else{
        u1_t_ava_rx            = (U1)VDF_ESO_AVA_RX_UNK;
    }

    u4_t_tim_elpsd = (U4)st_ap_rx->u2_tim_elpsd + (U4)VDF_NUM_TSLOT;
    if(u4_t_tim_elpsd >= (U4)st_ap_CH->u2_rxc_peri){
        st_ap_rx->u1_rxc_start = u1_a_RXEV_CNT;
        st_ap_rx->u1_ava_rx    = (U1)VDF_ESO_AVA_RX_UNK;
        u4_t_tim_elpsd         = (U4)0U;
    }
    st_ap_rx->u2_tim_elpsd = (U2)u4_t_tim_elpsd;

    return(u1_t_ava_rx);
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdfEsoNvmSynchk(const U2 u2_a_EOM)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdfEsoNvmSynchk(const U2 u2_a_EOM)
{
    static const U2           u2_s_VDF_ESO_NVM_SYN_TOUT = (U2)2000U / (U2)VDF_MAIN_TICK;  /* 2 seconds */

    U4                        u4_t_tocnt;

    U1                        u1_t_nwo_en;
    U1                        u1_t_syn_chk;

    u4_t_tocnt = (U4)u2_s_vdf_eso_nvm_tocnt + (U4)VDF_NUM_TSLOT;
    if(u4_t_tocnt > (U4)U2_MAX){
        u4_t_tocnt = (U4)U2_MAX;
    }

    if(u4_t_tocnt >= (U4)u2_s_VDF_ESO_NVM_SYN_TOUT){
        u1_t_nwo_en = (U1)VDF_ESO_NVM_SYN_STA;
    }
    else{
        u1_t_nwo_en = (U1)0U;
    }

    if(u1_s_vdf_eso_res_ctrl == (U1)VDF_ESO_RES_RUN){
        u1_t_syn_chk = u1_s_VdfEsoNvmInit(u1_t_nwo_en);
        u2_s_vdf_eso_igredge = (U2)VDF_ESO_IGROFFEG_OFF;
    }
    else if(u2_a_EOM >= (U2)VDF_EOM_SI_ACT){
        u1_t_syn_chk = (U1)VDF_ESO_NVM_SYN_FIN;
        u2_s_vdf_eso_igredge = (U2)VDF_ESO_IGROFFEG_OFF;
    }
    else{
        u1_t_syn_chk = u1_s_VdfEsoNvmUpdt(u1_t_nwo_en);
    }

    if(u1_t_syn_chk == (U1)VDF_ESO_NVM_SYN_FIN){
        u4_t_tocnt = (U4)U2_MAX;
    }
    else if(u1_t_syn_chk >= (U1)VDF_ESO_NVM_SYN_STA){
        u4_t_tocnt = (U4)0U;
    }
    else{
        /* do nothing */
    }
    u2_s_vdf_eso_nvm_tocnt = (U2)u4_t_tocnt;

    vd_s_VdfEsoNvmReschk(u1_t_syn_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_VdfEsoNvmInit(const U1 u1_a_NWO_EN)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_VdfEsoNvmInit(const U1 u1_a_NWO_EN)
{
    U4                        u4_t_lpcnt;
    U4                        u4_t_ch_ini;

    U1                        u1_t_syn_chk;

    u1_t_syn_chk = (U1)VDF_ESO_NVM_SYN_FIN;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_VDF_ESO_NOW_AVA; u4_t_lpcnt++){

        u4_t_ch_ini   = st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_ini;

        vd_g_Rim_WriteU4(st_gp_VDF_ESO_AVA[u4_t_lpcnt].u2_bid, u4_t_ch_ini);

        u4_t_ch_ini  &= st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_nvm;
        u4_t_ch_ini  &= st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_rx;
        u1_t_syn_chk |= u1_s_VdfEsoNvmNext(u1_a_NWO_EN, st_gp_VDF_ESO_AVA[u4_t_lpcnt].u2_nid, u4_t_ch_ini);
    }

    return(u1_t_syn_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_VdfEsoNvmUpdt(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_VdfEsoNvmUpdt(const U1 u1_a_NWO_EN)
{
    U4                        u4_t_lpcnt;
    U4                        u4_t_log_nvm;

    U1                        u1_t_syn_chk;

    u1_t_syn_chk = (U1)VDF_ESO_NVM_SYN_FIN;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_VDF_ESO_NOW_AVA; u4_t_lpcnt++){

        u4_gp_vdf_eso_ava[u4_t_lpcnt] &= st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_rx;

        vd_g_Rim_WriteU4(st_gp_VDF_ESO_AVA[u4_t_lpcnt].u2_bid, u4_gp_vdf_eso_ava[u4_t_lpcnt]);

        u4_t_log_nvm  = u4_gp_vdf_eso_ava[u4_t_lpcnt] & st_gp_VDF_ESO_AVA[u4_t_lpcnt].u4_nvm;
        u1_t_syn_chk |= u1_s_VdfEsoNvmNextUpdt(u1_a_NWO_EN, st_gp_VDF_ESO_AVA[u4_t_lpcnt].u2_nid, u4_t_log_nvm);
    }
    
    if(((u1_t_syn_chk & (U1)VDF_ESO_NVM_SYN_STA) != (U1)0U) ||
       (u1_t_syn_chk == (U1)VDF_ESO_NVM_SYN_FIN)){
        u2_s_vdf_eso_igredge = (U2)VDF_ESO_IGROFFEG_OFF;
    }

    return(u1_t_syn_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_VdfEsoNvmNext(const U1 u1_a_NWO_EN, const U2 u2_a_NID, const U4 u4_a_NEXT)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_VdfEsoNvmNext(const U1 u1_a_NWO_EN, const U2 u2_a_NID, const U4 u4_a_NEXT)
{
    U4                        u4_t_last;

    U1                        u1_t_nvm_chk;
    U1                        u1_t_syn_chk;
    U1                        u1_t_nwo_chk;

    u4_t_last    = (U4)0U;
    u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts(u2_a_NID, &u4_t_last);
    if((u4_a_NEXT    != u4_t_last               ) ||
       (u1_t_nvm_chk >= (U1)NVMC_STATUS_KIND_NG ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_ERRCOMP ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_CACHE_NG)){

        u1_t_syn_chk = ((U1)VDF_ESO_NVM_SYN_STA | (U1)VDF_ESO_NVM_SYN_RUN);
    }
    else if(u1_t_nvm_chk == (U1)NVMC_STATUS_WRITING){
        u1_t_syn_chk = (U1)VDF_ESO_NVM_SYN_RUN;
    }
    else{
        u1_t_syn_chk = (U1)VDF_ESO_NVM_SYN_FIN;
    }

    u1_t_nwo_chk = u1_t_syn_chk & u1_a_NWO_EN;
    if(u1_t_nwo_chk == (U1)VDF_ESO_NVM_SYN_STA){
        vd_g_Nvmc_WriteU4(u2_a_NID, u4_a_NEXT);
    }
    else{
        u1_t_syn_chk &= (U1)VDF_ESO_NVM_SYN_RUN;
    }

    return(u1_t_syn_chk);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_VdfEsoNvmNextUpdt(const U1 u1_a_NWO_EN, const U2 u2_a_NID, const U4 u4_a_NEXT)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_VdfEsoNvmNextUpdt(const U1 u1_a_NWO_EN, const U2 u2_a_NID, const U4 u4_a_NEXT)
{
    U4                        u4_t_last;

    U1                        u1_t_nvm_chk;
    U1                        u1_t_syn_chk;
    U1                        u1_t_nwo_chk;

    u4_t_last    = (U4)0U;
    u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts(u2_a_NID, &u4_t_last);
    if((u4_a_NEXT    != u4_t_last               ) ||
       (u1_t_nvm_chk >= (U1)NVMC_STATUS_KIND_NG ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_ERRCOMP ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_CACHE_NG)){

        u1_t_syn_chk = ((U1)VDF_ESO_NVM_SYN_STA | (U1)VDF_ESO_NVM_SYN_RUN);
    }
    else if(u1_t_nvm_chk == (U1)NVMC_STATUS_WRITING){
        u1_t_syn_chk = (U1)VDF_ESO_NVM_SYN_RUN;
    }
    else{
        u1_t_syn_chk = (U1)VDF_ESO_NVM_SYN_FIN;
    }

    u1_t_nwo_chk = u1_t_syn_chk & u1_a_NWO_EN;
    if(u1_t_nwo_chk == (U1)VDF_ESO_NVM_SYN_STA){
        if(u2_s_vdf_eso_igredge >= (U2)VDF_ESO_IGROFFEG_ON){
            vd_g_Nvmc_WriteU4(u2_a_NID, u4_a_NEXT);
        }
        else{
            u1_t_syn_chk = (U1)VDF_ESO_NVM_SYN_FIN;
       }
    }
    else{
        u1_t_syn_chk &= (U1)VDF_ESO_NVM_SYN_RUN;
    }

    return(u1_t_syn_chk);
}

/*===================================================================================================================================*/
/*  static U1      vd_s_VdfEsoNvmReschk(const U1 u1_a_SYN_CHK)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdfEsoNvmReschk(const U1 u1_a_SYN_CHK)
{
    U4                        u4_t_tocnt;

    u4_t_tocnt = (U4)u2_s_vdf_eso_res_tocnt + (U4)VDF_NUM_TSLOT;
    if(u4_t_tocnt > (U4)U2_MAX){
        u4_t_tocnt = (U4)U2_MAX;
    }
    u2_s_vdf_eso_res_tocnt = (U2)u4_t_tocnt;

    if(u1_s_vdf_eso_res_ctrl > (U1)VDF_ESO_RES_RUN){
     /* u1_s_vdf_eso_res_ctrl = keep last;           */
    }
    else if(u1_a_SYN_CHK == (U1)VDF_ESO_NVM_SYN_FIN){
        u1_s_vdf_eso_res_ctrl = (U1)VDF_ESO_RES_SUC;
    }
    else if(u4_t_tocnt >= (U4)u2_g_VDF_ESO_RES_TOUT){
        u1_s_vdf_eso_res_ctrl = (U1)VDF_ESO_RES_FAI;
    }
    else{
     /* u1_s_vdf_eso_res_ctrl = (U1)VDF_ESO_RES_RUN; */
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_VdfEsoGetRxevCnt(const U1 u1_a_INPUT_TYPE, const U2 u2_a_MSG)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_VdfEsoGetRxevCnt(const U1 u1_a_INPUT_TYPE, const U2 u2_a_MSG)
{
    U1    u1_t_rxev_cnt;

    switch(u1_a_INPUT_TYPE){
        case (U1)VDF_ESO_INPUT_TYPE_ETH:
            u1_t_rxev_cnt = u1_g_VardefEsOptCfgEthRxEvcnt(u2_a_MSG);
            break;
        case (U1)VDF_ESO_INPUT_TYPE_OTHER:
            u1_t_rxev_cnt = (U1)0U;
            break;
        default:
            u1_t_rxev_cnt = u1_g_VardefEsOptCfgCanRxEvcnt(u2_a_MSG);
            break;
    }

    return(u1_t_rxev_cnt);
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefEsOptIgoffEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVBIT)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefEsOptIgoffEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVBIT)
{
    U4                      u4_t_ign_chk;

    u4_t_ign_chk = u4_a_EVBIT & (U4)VEH_OPEMD_EVBIT_IG_R_TO_OFF;
    if(u4_t_ign_chk == (U4)VEH_OPEMD_EVBIT_IG_R_TO_OFF){
        u2_s_vdf_eso_igredge = (U2)VDF_ESO_IGROFFEG_ON;
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
/*  1.0.0     2/22/2019  YI       NEW!                                                                                               */
/*  1.1.0     4/ 2/2019  YI       Updated judgement logic.                                                                           */
/*  1.2.0     7/ 3/2019  YI       Add force unavailable parameter.                                                                   */
/*  1.3.0    10/18/2019  YI       Factory init was divided into MET and HUD.                                                         */
/*  1.4.0    11/ 7/2019  YI       Add Factory init Status.                                                                           */
/*  1.5.0     1/ 8/2020  YI       NVM fail-safe logic of the reading error was implemented.                                          */
/*  2.0.0     3/ 2/2020  TN       Re-designed.                                                                                       */
/*  2.1.0     9/28/2020  SF       Add CXPI / Ethernet signal judgement.                                                              */
/*  2.2.0     1/25/2021  SF       Bug Fix : Initial value of option availability was incorrect if NvM was unknown.                   */
/*  2.3.0    11/15/2021  RO       Add Other judgement.                                                                               */
/*  2.4.0     3/15/2022  RO       Add AVN judgement.                                                                                 */
/*  2.5.0     8/26/2024  TN       QAC Fix : Delete u1_g_VardefEsOptAvaByAvn func.                                                    */
/*  2.6.0     12/25/2024 KM       Updated write timing of DTF                                                                            */
/*                                                                                                                                   */
/*  * YI   = Yoshiki Iwata, Denso                                                                                                    */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * SF   = Seiya Fukutome, Denso Techno                                                                                            */
/*  * RO   = Reiya Okuda, KSE                                                                                                        */
/*  * TN   = Tetsushi Nakanao, Denso Techno                                                                                          */
/*  * KM   = Kazuma Miyazawa, Denso Techno                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
