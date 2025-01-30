/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN Service Application Layer / Digital Input Logger                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DIL_C_MAJOR                      (1)
#define TYDOCAN_DIL_C_MINOR                      (0)
#define TYDOCAN_DIL_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_dil_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TYDOCAN_DIL_C_MAJOR != TYDOCAN_DIL_H_MAJOR) || \
     (TYDOCAN_DIL_C_MINOR != TYDOCAN_DIL_H_MINOR) || \
     (TYDOCAN_DIL_C_PATCH != TYDOCAN_DIL_H_PATCH))
#error "tydocan_dil.c and tydocan_dil.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DIL_C_MAJOR != TYDOCAN_DIL_CFG_H_MAJOR) || \
     (TYDOCAN_DIL_C_MINOR != TYDOCAN_DIL_CFG_H_MINOR) || \
     (TYDOCAN_DIL_C_PATCH != TYDOCAN_DIL_CFG_H_PATCH))
#error "tydocan_dil.c and tydocan_dil_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DIL_CH_TO_GR                        (5U)
#define TYDC_DIL_CH_TO_BI                        (0x001fU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DIL_LOG_NVM_UNK                     (0x80000000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DIL_NVM_SYN_FIN                     (0x00U)
#define TYDC_DIL_NVM_SYN_RUN                     (0x01U)
#define TYDC_DIL_NVM_SYN_STA                     (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2                u2_s_tydc_dil_nvm_tocnt;
static U2                u2_s_tydc_dil_res_tocnt;

static U1                u1_s_tydc_dil_res_ctrl;
static U1                u1_s_tydc_dil_tslot_cnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_TydcDilLogNext(const U1 u1_a_EOM);

static void    vd_s_TydcDilMemSynchk(const U1 u1_a_EOM);
static U1      u1_s_TydcDilMemInit(const U1 u1_a_NWO_EN);
static U1      u1_s_TydcDilMemUpdt(const U1 u1_a_NWO_EN);
static U1      u1_s_TydcDilNvmNext(const U2 u2_a_NID, const U1 u1_a_NWO_EN, U4 * u4_ap_next);
static void    vd_s_TydcDilNvmReschk(const U1 u1_a_SYN_CHK);

static void    vd_s_TydcDilLogReset(const U1 u1_a_MEM);
static U1      u1_s_TydcDilChAct(const U2 u2_a_DIL_CH, const U4 u4_a_CHB);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDilBonInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDilBonInit(void)
{
    U4 *                       u4_tp_chb;

    U4                         u4_t_lpcnt;

    U4                         u4_t_log;
    U4                         u4_t_mem_last;
    U4                         u4_t_wof;

    U2                         u2_t_mem;
    U2                         u2_t_mid;

    U1                         u1_t_mem_chk;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DIL_NUM_GR; u4_t_lpcnt++){

        u4_t_log = (U4)0U;
        u2_t_mem = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u2_mem;
        u2_t_mid = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u2_mid;
        if(u2_t_mem == (U1)TYDC_DIL_MEM_NVM){

            u4_t_mem_last = (U4)0U;
            u1_t_mem_chk  = u1_g_Nvmc_ReadU4withSts(u2_t_mid, &u4_t_mem_last);
            if(u1_t_mem_chk == (U1)NVMC_STATUS_KIND_OK){
                u4_t_log = u4_t_mem_last; 
            }
            else{
                u4_t_log = (U4)TYDC_DIL_LOG_NVM_UNK; 
            }
        }
        else if(u2_t_mem == (U1)TYDC_DIL_MEM_BRA){
            vd_g_Rim_WriteU4(u2_t_mid, (U4)0U);
        }
        else{
            /* Do nothing */
        }

        u4_t_wof  = u4_t_lpcnt * (U4)TYDC_DIL_NUM_CHB;
        u4_tp_chb = &u4_gp_tydc_dil_chb[u4_t_wof];

        u4_tp_chb[TYDC_DIL_CHB_LOG] = u4_t_log; 
        u4_tp_chb[TYDC_DIL_CHB_LAS] = (U4)0U;
        u4_tp_chb[TYDC_DIL_CHB_NEX] = (U4)0U;
    }

    u2_s_tydc_dil_nvm_tocnt = (U2)U2_MAX;
    u2_s_tydc_dil_res_tocnt = (U2)U2_MAX;

    u1_s_tydc_dil_res_ctrl  = (U1)TYDC_DIL_RES_UNK;
    u1_s_tydc_dil_tslot_cnt = (U1)U1_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDilRstwkInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDilRstwkInit(void)
{
    U4 *                       u4_tp_chb;

    U4                         u4_t_lpcnt;

    U4                         u4_t_log;
    U4                         u4_t_mem_last;
    U4                         u4_t_wof;

    U2                         u2_t_mem;
    U2                         u2_t_mid;

    U1                         u1_t_mem_chk;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DIL_NUM_GR; u4_t_lpcnt++){

        u4_t_log      = (U4)0U;
        u4_t_mem_last = (U4)0U;
        u2_t_mem      = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u2_mem;
        u2_t_mid      = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u2_mid;
        if(u2_t_mem == (U1)TYDC_DIL_MEM_NVM){

            u1_t_mem_chk  = u1_g_Nvmc_ReadU4withSts(u2_t_mid, &u4_t_mem_last);
            if(u1_t_mem_chk == (U1)NVMC_STATUS_KIND_OK){
                u4_t_log = u4_t_mem_last; 
            }
            else{
                u4_t_log = (U4)TYDC_DIL_LOG_NVM_UNK; 
            }
        }
        else if(u2_t_mem == (U1)TYDC_DIL_MEM_BRA){

            u1_t_mem_chk = u1_g_Rim_ReadU4withStatus(u2_t_mid, &u4_t_mem_last) & (U1)RIM_RESULT_KIND_MASK;
            if(u1_t_mem_chk == (U1)RIM_RESULT_KIND_OK){
                u4_t_log = u4_t_mem_last;
            }
        }
        else{
            /* Do nothing */
        }

        u4_t_wof  = u4_t_lpcnt * (U4)TYDC_DIL_NUM_CHB;
        u4_tp_chb = &u4_gp_tydc_dil_chb[u4_t_wof];

        u4_tp_chb[TYDC_DIL_CHB_LOG] = u4_t_log; 
        u4_tp_chb[TYDC_DIL_CHB_LAS] = (U4)0U;
        u4_tp_chb[TYDC_DIL_CHB_NEX] = (U4)0U;
    }

    u2_s_tydc_dil_nvm_tocnt = (U2)U2_MAX;
    u2_s_tydc_dil_res_tocnt = (U2)U2_MAX;

    u1_s_tydc_dil_res_ctrl  = (U1)TYDC_DIL_RES_UNK;
    u1_s_tydc_dil_tslot_cnt = (U1)U1_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDilMainTask(const U1 u1_a_EOM)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDilMainTask(const U1 u1_a_EOM)
{
    U4                         u4_t_swi_cnt;
    U4                         u4_t_swi_end;

    U4                         u4_t_ch;
    U4                         u4_t_wof;
    U4                         u4_t_bit;

    U1                         u1_t_swi_act;

    if(u1_s_tydc_dil_tslot_cnt >= (U1)TYDC_DIL_NUM_TSLOT){
        u1_s_tydc_dil_tslot_cnt = (U1)0U;
    }

    u4_t_swi_cnt = (U4)u2_g_TYDC_DIL_NUM_SWI_BY_RUN * (U4)u1_s_tydc_dil_tslot_cnt;
    u4_t_swi_end = u4_t_swi_cnt + (U4)u2_g_TYDC_DIL_NUM_SWI_BY_RUN;
    if(u4_t_swi_end > (U4)u2_g_TYDC_DIL_NUM_SWI){
        u4_t_swi_end = (U4)u2_g_TYDC_DIL_NUM_SWI;
    }

    while(u4_t_swi_cnt < u4_t_swi_end){

        u1_t_swi_act = u1_g_IoHwDifltSwitch(st_gp_TYDC_DIL_SWI[u4_t_swi_cnt].u2_disgnl);
        if(u1_t_swi_act == (U1)IOHW_DIFLT_SWITCH_ACT){

            u4_t_ch   = (U4)st_gp_TYDC_DIL_SWI[u4_t_swi_cnt].u2_dil_ch;
            u4_t_wof  = ((u4_t_ch >> TYDC_DIL_CH_TO_GR) * (U4)TYDC_DIL_NUM_CHB) + (U4)TYDC_DIL_CHB_NEX;
            u4_t_bit  = (U4)0x00000001U << (u4_t_ch & (U4)TYDC_DIL_CH_TO_BI);

            u4_gp_tydc_dil_chb[u4_t_wof] |= u4_t_bit;
        }

        u4_t_swi_cnt++;
    }

    u1_s_tydc_dil_tslot_cnt++;

    if(u1_s_tydc_dil_tslot_cnt >= (U1)TYDC_DIL_NUM_TSLOT){
        vd_s_TydcDilLogNext(u1_a_EOM);
        vd_s_TydcDilMemSynchk(u1_a_EOM);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDilReset(const U1 u1_a_MEM, const U1 u1_a_RUN)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDilReset(const U1 u1_a_MEM, const U1 u1_a_RUN)
{
    U1                         u1_t_res_chk;

    if(u1_a_MEM == (U1)TYDC_DIL_MEM_NVM){

        if((u1_a_RUN               == (U1)TRUE            ) &&
           (u1_s_tydc_dil_res_ctrl >  (U1)TYDC_DIL_RES_RUN)){

            vd_s_TydcDilLogReset(u1_a_MEM);

            u2_s_tydc_dil_res_tocnt = (U2)0U;
            u1_s_tydc_dil_res_ctrl  = (U1)TYDC_DIL_RES_RUN;
        }

        u1_t_res_chk = u1_s_tydc_dil_res_ctrl;
    }
    else if(u1_a_MEM == (U1)TYDC_DIL_MEM_BRA){

        vd_s_TydcDilLogReset(u1_a_MEM);

        u1_t_res_chk = (U1)TYDC_DIL_RES_SUC;
    }
    else{
        u1_t_res_chk = (U1)TYDC_DIL_RES_UNK;
    }

    return(u1_t_res_chk);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDilAnsTx(U1 * u1_ap_ans_tx, const U2 u2_a_TX)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDilAnsTx(U1 * u1_ap_ans_tx, const U2 u2_a_TX)
{
    U1                         u1_t_proc;

    if(u2_a_TX < u2_g_TYDC_DIL_NUM_TX){
        u1_t_proc = u1_g_TyDoCANBiTx(u1_ap_ans_tx, &st_gp_TYDC_DIL_TX[u2_a_TX]);
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDilLasAct(const U2 u2_a_DIL_CH)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDilLasAct(const U2 u2_a_DIL_CH)
{
    return(u1_s_TydcDilChAct(u2_a_DIL_CH, (U4)TYDC_DIL_CHB_LAS));
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDilLogAct(const U2 u2_a_DIL_CH)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDilLogAct(const U2 u2_a_DIL_CH)
{
    return(u1_s_TydcDilChAct(u2_a_DIL_CH, (U4)TYDC_DIL_CHB_LOG));
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDilLogNext(const U1 u1_a_EOM)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDilLogNext(const U1 u1_a_EOM)
{
    U4 *                       u4_tp_chb;

    U4                         u4_t_lpcnt;

    U4                         u4_t_wof;
    U4                         u4_t_vom;
    U4                         u4_t_log;
    U4                         u4_t_nex;

    U2                         u2_t_mem;
    U1                         u1_t_ign;

    u1_t_ign = u1_a_EOM & (U1)TYDC_DIL_EOM_IGN_ON;
    if(u1_t_ign != (U1)0U){

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DIL_NUM_GR; u4_t_lpcnt++){

            u4_t_wof                     = u4_t_lpcnt * (U4)TYDC_DIL_NUM_CHB;
            u4_tp_chb                    = &u4_gp_tydc_dil_chb[u4_t_wof];

            u4_t_vom                     = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u4p_vom[TYDC_DIL_VOM_IGN];
            u4_t_log                     = u4_tp_chb[TYDC_DIL_CHB_LAS];
            u4_t_nex                     = u4_tp_chb[TYDC_DIL_CHB_NEX] & u4_t_vom;

            u4_tp_chb[TYDC_DIL_CHB_LAS]  = u4_t_nex;
            u4_tp_chb[TYDC_DIL_CHB_NEX]  = (U4)0U;

            u4_t_log                     = u4_t_log ^ u4_t_nex;

            u2_t_mem = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u2_mem;
            if(u2_t_mem == (U1)TYDC_DIL_MEM_NVM){
                u4_t_log                 = u4_t_log & u4_t_nex;
            }
            u4_tp_chb[TYDC_DIL_CHB_LOG] |= u4_t_log;
        }
    }
    else{

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DIL_NUM_GR; u4_t_lpcnt++){

            u4_t_wof                     = u4_t_lpcnt * (U4)TYDC_DIL_NUM_CHB;
            u4_tp_chb                    = &u4_gp_tydc_dil_chb[u4_t_wof];

            u4_t_vom                     = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u4p_vom[TYDC_DIL_VOM_BAT];
            u4_t_nex                     = u4_tp_chb[TYDC_DIL_CHB_NEX] & u4_t_vom;

            u4_tp_chb[TYDC_DIL_CHB_LAS]  = u4_t_nex;
            u4_tp_chb[TYDC_DIL_CHB_NEX]  = (U4)0U;
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDilMemSynchk(const U1 u1_a_EOM)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDilMemSynchk(const U1 u1_a_EOM)
{
    static const U2            u2_s_TYDC_DIL_NVM_SYN_TOUT = (U2)2000U / (U2)OXDC_MAIN_TICK;

    U4                         u4_t_tocnt;

    U1                         u1_t_nwo_en;
    U1                         u1_t_syn_chk;

    u4_t_tocnt = (U4)u2_s_tydc_dil_nvm_tocnt + (U4)TYDC_DIL_NUM_TSLOT;
    if(u4_t_tocnt > (U4)U2_MAX){
        u4_t_tocnt = (U4)U2_MAX;
    }

    if(u4_t_tocnt >= (U4)u2_s_TYDC_DIL_NVM_SYN_TOUT){
        u1_t_nwo_en = (U1)TYDC_DIL_NVM_SYN_STA;
    }
    else{
        u1_t_nwo_en = (U1)0U;
    }

    if(u1_s_tydc_dil_res_ctrl == (U1)TYDC_DIL_RES_RUN){
        u1_t_syn_chk = u1_s_TydcDilMemInit(u1_t_nwo_en);
    }
    else if(u1_a_EOM >= (U1)TYDC_DIL_EOM_SI_ACT){
        u1_t_syn_chk = (U1)TYDC_DIL_NVM_SYN_FIN;
    }
    else{
        u1_t_syn_chk = u1_s_TydcDilMemUpdt(u1_t_nwo_en);
    }

    if(u1_t_syn_chk == (U1)TYDC_DIL_NVM_SYN_FIN){
        u4_t_tocnt = (U4)U2_MAX;
    }
    else if(u1_t_syn_chk >= (U1)TYDC_DIL_NVM_SYN_STA){
        u4_t_tocnt = (U4)0U;
    }
    else{
        /* Do nothing */
    }
    u2_s_tydc_dil_nvm_tocnt = (U2)u4_t_tocnt;

    vd_s_TydcDilNvmReschk(u1_t_syn_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcDilMemInit(const U1 u1_a_NWO_EN)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcDilMemInit(const U1 u1_a_NWO_EN)
{
    U4                         u4_t_lpcnt;

    U4                         u4_t_next;

    U2                         u2_t_mem;
    U2                         u2_t_mid;

    U1                         u1_t_syn_chk;

    u1_t_syn_chk = (U1)TYDC_DIL_NVM_SYN_FIN;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DIL_NUM_GR; u4_t_lpcnt++){

        u4_t_next = (U4)0U;
        u2_t_mem  = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u2_mem;
        u2_t_mid  = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u2_mid;
        if(u2_t_mem == (U1)TYDC_DIL_MEM_NVM){
            u1_t_syn_chk |= u1_s_TydcDilNvmNext(u2_t_mid, u1_a_NWO_EN, &u4_t_next);
        }
        else if(u2_t_mem == (U1)TYDC_DIL_MEM_BRA){
            vd_g_Rim_WriteU4(u2_t_mid, u4_t_next);
        }
        else{
            /* Do nothing */
        }
    }

    return(u1_t_syn_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcDilMemUpdt(const U1 u1_a_NWO_EN)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcDilMemUpdt(const U1 u1_a_NWO_EN)
{
    U4                         u4_t_lpcnt;

    U4                         u4_t_wof;

    U2                         u2_t_mem;
    U2                         u2_t_mid;

    U1                         u1_t_syn_chk;
    
    u1_t_syn_chk = (U1)TYDC_DIL_NVM_SYN_FIN;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DIL_NUM_GR; u4_t_lpcnt++){

        u4_t_wof = (u4_t_lpcnt * (U4)TYDC_DIL_NUM_CHB) + (U4)TYDC_DIL_CHB_LOG;
        u2_t_mem = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u2_mem;
        u2_t_mid = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u2_mid;
        if(u2_t_mem == (U1)TYDC_DIL_MEM_NVM){
            u1_t_syn_chk |= u1_s_TydcDilNvmNext(u2_t_mid, u1_a_NWO_EN, &u4_gp_tydc_dil_chb[u4_t_wof]);
        }
        else if(u2_t_mem == (U1)TYDC_DIL_MEM_BRA){
            vd_g_Rim_WriteU4(u2_t_mid, u4_gp_tydc_dil_chb[u4_t_wof]);
        }
        else{
            /* Do nothing */
        }
    }

    return(u1_t_syn_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcDilNvmNext(const U2 u2_a_NID, const U1 u1_a_NWO_EN, U4 * u4_ap_next)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcDilNvmNext(const U2 u2_a_NID, const U1 u1_a_NWO_EN, U4 * u4_ap_next)
{
    U4                         u4_t_nvm_last;
    U4                         u4_t_nvm_next;
    U1                         u1_t_nvm_chk;
    U1                         u1_t_syn_chk;
    U1                         u1_t_nwo_chk;

    u4_t_nvm_next = (*u4_ap_next) & ((U4)U4_MAX ^ (U4)TYDC_DIL_LOG_NVM_UNK);
    u4_t_nvm_last = (U4)0U;
    u1_t_nvm_chk  = u1_g_Nvmc_ReadU4withSts(u2_a_NID, &u4_t_nvm_last);
    if((u1_t_nvm_chk >= (U1)NVMC_STATUS_KIND_NG ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_ERRCOMP ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_CACHE_NG)){

        (*u4_ap_next) |= (U4)TYDC_DIL_LOG_NVM_UNK;
        u1_t_syn_chk   = (U1)TYDC_DIL_NVM_SYN_STA | (U1)TYDC_DIL_NVM_SYN_RUN;
    }
    else if(u4_t_nvm_next != u4_t_nvm_last){
        u1_t_syn_chk   = (U1)TYDC_DIL_NVM_SYN_STA | (U1)TYDC_DIL_NVM_SYN_RUN;
    }
    else if(u1_t_nvm_chk == (U1)NVMC_STATUS_WRITING){
        u1_t_syn_chk   = (U1)TYDC_DIL_NVM_SYN_RUN;
    }
    else{
        u1_t_syn_chk   = (U1)TYDC_DIL_NVM_SYN_FIN;
        (*u4_ap_next)  = u4_t_nvm_next;
    }

    u1_t_nwo_chk = u1_t_syn_chk & u1_a_NWO_EN;
    if(u1_t_nwo_chk == (U1)TYDC_DIL_NVM_SYN_STA){
        vd_g_Nvmc_WriteU4(u2_a_NID, u4_t_nvm_next);
    }
    else{
        u1_t_syn_chk &= (U1)TYDC_DIL_NVM_SYN_RUN;
    }

    return(u1_t_syn_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDilNvmReschk(const U1 u1_a_SYN_CHK)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDilNvmReschk(const U1 u1_a_SYN_CHK)
{
    U4                         u4_t_tocnt;

    u4_t_tocnt = (U4)u2_s_tydc_dil_res_tocnt + (U4)TYDC_DIL_NUM_TSLOT;
    if(u4_t_tocnt > (U4)U2_MAX){
        u4_t_tocnt = (U4)U2_MAX;
    }
    u2_s_tydc_dil_res_tocnt = (U2)u4_t_tocnt;

    if(u1_s_tydc_dil_res_ctrl > (U1)TYDC_DIL_RES_RUN){
     /* u1_s_tydc_dil_res_ctrl = keep last;            */
    }
    else if(u1_a_SYN_CHK == (U1)TYDC_DIL_NVM_SYN_FIN){
        u1_s_tydc_dil_res_ctrl = (U1)TYDC_DIL_RES_SUC;
    }
    else if(u4_t_tocnt >= (U4)u2_g_TYDC_DIL_RES_TOUT){
        u1_s_tydc_dil_res_ctrl = (U1)TYDC_DIL_RES_FAI;
    }
    else{
     /* u1_s_tydc_dil_res_ctrl = (U1)TYDC_DIL_RES_RUN; */
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDilLogReset(const U1 u1_a_MEM)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDilLogReset(const U1 u1_a_MEM)
{
    U4                         u4_t_lpcnt;
    U4                         u4_t_wof;
    U2                         u2_t_mem;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DIL_NUM_GR; u4_t_lpcnt++){

        u2_t_mem = st_gp_TYDC_DIL_GR[u4_t_lpcnt].u2_mem;
        if(u2_t_mem == (U2)u1_a_MEM){
            u4_t_wof                     = (u4_t_lpcnt * (U4)TYDC_DIL_NUM_CHB) + (U4)TYDC_DIL_CHB_LOG;
            u4_gp_tydc_dil_chb[u4_t_wof] = (U4)0U;
        }
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcDilChAct(const U2 u2_a_DIL_CH, const U4 u4_a_CHB)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcDilChAct(const U2 u2_a_DIL_CH, const U4 u4_a_CHB)
{
    U4                         u4_t_gr;
    U4                         u4_t_lsb;
    U4                         u4_t_wof;
    U4                         u4_t_act;

    if(u2_a_DIL_CH < u2_g_TYDC_DIL_NUM_CH){

        u4_t_gr  = (U4)u2_a_DIL_CH >> TYDC_DIL_CH_TO_GR;
        u4_t_lsb = (U4)u2_a_DIL_CH & (U4)TYDC_DIL_CH_TO_BI;
        u4_t_wof = (u4_t_gr * (U4)TYDC_DIL_NUM_CHB) + u4_a_CHB;
        u4_t_act = (u4_gp_tydc_dil_chb[u4_t_wof] >> u4_t_lsb) & (U4)TRUE;
    }
    else{
        u4_t_act = (U4)FALSE;
    }

    return((U1)u4_t_act);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/17/2020  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
