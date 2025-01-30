/* 2.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Eco Judge                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ECOJDG_C_MAJOR                          (2)
#define ECOJDG_C_MINOR                          (0)
#define ECOJDG_C_PATCH                          (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ecojdg_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ECOJDG_C_MAJOR != ECOJDG_H_MAJOR) || \
     (ECOJDG_C_MINOR != ECOJDG_H_MINOR) || \
     (ECOJDG_C_PATCH != ECOJDG_H_PATCH))
#error "ecojdg.c and ecojdg.h : source and header files are inconsistent!"
#endif

#if ((ECOJDG_C_MAJOR != ECOJDG_CFG_H_MAJOR) || \
     (ECOJDG_C_MINOR != ECOJDG_CFG_H_MINOR) || \
     (ECOJDG_C_PATCH != ECOJDG_CFG_H_PATCH))
#error "ecojdg.c and ecojdg_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ECOJDG_NUM_CLC_ITM                      (3U)
#define ECOJDG_CLC_ITM_STR                      (0U)
#define ECOJDG_CLC_ITM_RUN                      (1U)
#define ECOJDG_CLC_ITM_DEC                      (2U)

#define ECOJDG_CLC_SCR_MAX                      (150U)
#define ECOJDG_DSP_SCR_MAX                      (100U)
#define ECOJDG_KMPH_STP                         (200U)
#define ECOJDG_KMPH_RUN                         (2000U)
#define ECOJDG_DSP_UPD_TIM                      (2000U / ECOJDG_TICK_TIM)

#define ECOJDG_EVT_BIT_UPD                      (0x01U)
#define ECOJDG_EVT_BIT_RUN                      (0x02U)

#define ECOJDG_ACT_NON                          (0U)
#define ECOJDG_ACT_STR_DIS                      (1U)
#define ECOJDG_ACT_STR_UPD                      (2U)
#define ECOJDG_ACT_RUN_FIN                      (3U)
#define ECOJDG_ACT_RUN_UPD                      (4U)
#define ECOJDG_ACT_RUN_SUS                      (5U)
#define ECOJDG_ACT_VEH_STP                      (6U)
#define ECOJDG_ACT_DEC_SUS                      (7U)
#define ECOJDG_ACT_SUS_RES                      (8U)
#define ECOJDG_ACT_ALL_CLR                      (9U)

#define ECOJDG_CNT_LST                          (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U4      u4_sum_scr;
    U4      u4_sum_cnt;
}ST_ECOJDG_CLC;

typedef struct {
    U4      u4_elpsd;
    U1      u1_id;
    U1      u1_cnt;
    U1      u1_std;
    U1      u1_dec;
}ST_ECOJDG_STATE;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_ECOJDG_CLC   st_sp_ecojdg_clc_run[ECOJDG_NUM_CLC_ITM];
static  U1              u1_sp_ecojdg_scr[ECOJDG_NUM_SCR];
static  ST_ECOJDG_STATE st_s_ecojdg_state;
static  U1              u1_s_ecojdg_inv_sts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_EcoJdgAct(const U1 u1_a_ACT);
static void vd_s_EcoJdgCalcScore(const U1 u1_a_ITM);
static void vd_s_EcoJdgCalcTotal(const U1 u1_a_SCR_STR);
static void vd_s_EcoJdgCntScr(const U1 u1_a_ID, const U1 u1_a_SCR, const U1 u1_a_CNT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void        vd_g_EcoJdgInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void        vd_g_EcoJdgInit(void)
{
    U4      u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ECOJDG_NUM_CLC_ITM; u4_t_lpcnt++){
        st_sp_ecojdg_clc_run[u4_t_lpcnt].u4_sum_scr = (U4)0U;
        st_sp_ecojdg_clc_run[u4_t_lpcnt].u4_sum_cnt = (U4)0U;
    }
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ECOJDG_NUM_SCR; u4_t_lpcnt++){
        u1_sp_ecojdg_scr[u4_t_lpcnt] = (U1)ECOJDG_SCR_INVALID;
    }
    st_s_ecojdg_state.u4_elpsd = (U4)0U;
    st_s_ecojdg_state.u1_id    = (U1)ECOJDG_ID_STP;
    st_s_ecojdg_state.u1_cnt   = u1_g_EcoJdgCfgRxCnt();
    st_s_ecojdg_state.u1_std   = (U1)FALSE;
    st_s_ecojdg_state.u1_dec   = (U1)FALSE;
    u1_s_ecojdg_inv_sts        = (U1)0U; 
}
/*===================================================================================================================================*/
/*  void        vd_g_EcoJdgMainTask(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void        vd_g_EcoJdgMainTask(void)
{
    static const U1 u1_sp_ECOJDG_ACT[] = 
    {
        (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_RUN_SUS, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_DIS, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_DIS, (U1)ECOJDG_ACT_RUN_FIN, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_DIS, (U1)ECOJDG_ACT_VEH_STP, (U1)ECOJDG_ACT_VEH_STP, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_VEH_STP,
        (U1)ECOJDG_ACT_STR_DIS, (U1)ECOJDG_ACT_RUN_SUS, (U1)ECOJDG_ACT_DEC_SUS, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_NON,

        (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_DIS, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_DIS, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_DIS, (U1)ECOJDG_ACT_VEH_STP, (U1)ECOJDG_ACT_VEH_STP, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_VEH_STP,
        (U1)ECOJDG_ACT_STR_DIS, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_DEC_SUS, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_NON,

        (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_RUN_SUS, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_UPD, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_UPD, (U1)ECOJDG_ACT_RUN_FIN, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_UPD, (U1)ECOJDG_ACT_VEH_STP, (U1)ECOJDG_ACT_VEH_STP, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_VEH_STP,
        (U1)ECOJDG_ACT_STR_UPD, (U1)ECOJDG_ACT_RUN_SUS, (U1)ECOJDG_ACT_DEC_SUS, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_NON,

        (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_UPD, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_UPD, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_ALL_CLR, (U1)ECOJDG_ACT_SUS_RES,
        (U1)ECOJDG_ACT_STR_UPD, (U1)ECOJDG_ACT_VEH_STP, (U1)ECOJDG_ACT_VEH_STP, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_VEH_STP,
        (U1)ECOJDG_ACT_STR_UPD, (U1)ECOJDG_ACT_RUN_UPD, (U1)ECOJDG_ACT_DEC_SUS, (U1)ECOJDG_ACT_NON,     (U1)ECOJDG_ACT_NON,
    };
    static const U1 u1_s_ECOJDG_NUM_ACT = (U1)(sizeof(u1_sp_ECOJDG_ACT) / sizeof(u1_sp_ECOJDG_ACT[0]));
    U2      u2_t_kmph;
    U1      u1_t_kmph_sts;

    U1      u1_t_idx;
    U1      u1_t_work;
    U1      u1_t_evt;
    U1      u1_t_act;

    U1      u1_t_sts;
    U1      u1_t_id;
    U1      u1_t_scr;
    U1      u1_t_cnt;

    u1_t_id  = (U1)U1_MAX;
    u1_t_scr = (U1)U1_MAX;
    u1_t_cnt = (U1)U1_MAX;

    u1_t_sts       = u1_g_EcoJdgCfgScrInst(&u1_t_id, &u1_t_scr, &u1_t_cnt);
    u1_t_sts      &= (U1)(ECOJDG_STSBIT_UNKNOWN | ECOJDG_STSBIT_INVALID);

    u2_t_kmph      = (U2)0U;
    u1_t_kmph_sts  = u1_g_EcoJdgKmphInst(&u2_t_kmph);
    u1_t_kmph_sts &= (U1)(VEHSPD_STSBIT_UNKNOWN | VEHSPD_STSBIT_INVALID);

    if(u1_t_kmph_sts != (U1)0U){
        u1_t_id   = (U1)ECOJDG_ID_SUS;
        u2_t_kmph = (U2)0U;
    }
    else if((u1_t_sts != (U1)0U               ) ||
            (u1_t_id  >= (U1)ECOJDG_ID_SUS    ) ||
            (u1_t_cnt >  u1_g_ECOJDG_RXCNT_MAX)){

        if(u2_t_kmph < (U2)ECOJDG_KMPH_STP){
            u1_t_id = (U1)ECOJDG_ID_STP;
        }
        else{
            u1_t_id = (U1)ECOJDG_ID_SUS;
        }
    }
    else{
        if(u1_t_scr > (U1)ECOJDG_CLC_SCR_MAX){
            u1_s_ecojdg_inv_sts |= (U1)(1U << u1_t_id);
        }
        else{
            u1_s_ecojdg_inv_sts &= ((U1)U1_MAX ^ (U1)(1U << u1_t_id));
        }
    }

    u1_t_evt  = (U1)0U;
    if(u2_t_kmph >= (U2)ECOJDG_KMPH_RUN){
        u1_t_evt  = (U1)ECOJDG_EVT_BIT_RUN;
    }
    if(st_s_ecojdg_state.u4_elpsd >= (U4)ECOJDG_DSP_UPD_TIM){
        u1_t_evt |= (U1)ECOJDG_EVT_BIT_UPD;
        st_s_ecojdg_state.u4_elpsd = (U4)0U;
    }
    if(( u1_t_id == (U1)ECOJDG_ID_RUN                                           ) ||
       ((u1_t_id == (U1)ECOJDG_ID_DEC) && (st_s_ecojdg_state.u1_std == (U1)TRUE))){
        if(st_s_ecojdg_state.u4_elpsd < (U4)U4_MAX){
            st_s_ecojdg_state.u4_elpsd++;
        }
    }
    else{
        st_s_ecojdg_state.u4_elpsd = (U4)0U;
    }
    u1_t_idx = (U1)0U;
    u1_t_work = (U1)(u1_t_id * (U1)ECOJDG_NUM_ID);
    if(((U1)U1_MAX - st_s_ecojdg_state.u1_id) >= u1_t_work){
        u1_t_idx = u1_t_work + st_s_ecojdg_state.u1_id;
    }
    u1_t_work = u1_t_evt * (U1)(ECOJDG_NUM_ID * ECOJDG_NUM_ID);
    if(((U1)U1_MAX - u1_t_idx) > u1_t_work){
        u1_t_idx = u1_t_idx + u1_t_work;
    }

    u1_t_act = (U1)0U;
    if(u1_t_idx < u1_s_ECOJDG_NUM_ACT){
        u1_t_act  = u1_sp_ECOJDG_ACT[u1_t_idx];
    }
    vd_s_EcoJdgAct(u1_t_act);
    vd_s_EcoJdgCntScr(u1_t_id, u1_t_scr, u1_t_cnt);
}
/*===================================================================================================================================*/
/*  void        vd_g_EcoJdgScr(U1 * u1_ap_scr, const U1 u1_a_NSCR)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void        vd_g_EcoJdgScr(U1 * u1_ap_scr, const U1 u1_a_NSCR)
{
    U4      u4_t_lpcnt;

    if((u1_ap_scr != vdp_PTR_NA        ) && 
       (u1_a_NSCR >= (U1)ECOJDG_NUM_SCR)){
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ECOJDG_NUM_SCR; u4_t_lpcnt++){
            u1_ap_scr[u4_t_lpcnt] = u1_sp_ecojdg_scr[u4_t_lpcnt];
        }
    }
}
/*===================================================================================================================================*/
/*  static void vd_s_EcoJdgAct(const U1 u1_a_ACT)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_EcoJdgAct(const U1 u1_a_ACT)
{
    U4      u4_t_lpcnt;

    switch(u1_a_ACT){
        case ECOJDG_ACT_STR_DIS:
            st_sp_ecojdg_clc_run[ECOJDG_CLC_ITM_STR].u4_sum_scr = (U4)0U;
            st_sp_ecojdg_clc_run[ECOJDG_CLC_ITM_STR].u4_sum_cnt = (U4)0U;
            break;
        case ECOJDG_ACT_STR_UPD:
            vd_s_EcoJdgCalcScore((U1)ECOJDG_CLC_ITM_STR);
            break;
        case ECOJDG_ACT_RUN_FIN:
            if(st_s_ecojdg_state.u1_std != (U1)TRUE){
                st_sp_ecojdg_clc_run[ECOJDG_CLC_ITM_RUN].u4_sum_scr = (U4)0U;
                st_sp_ecojdg_clc_run[ECOJDG_CLC_ITM_RUN].u4_sum_cnt = (U4)0U;
                st_s_ecojdg_state.u4_elpsd = (U4)0U;
            }
            break;
        case ECOJDG_ACT_RUN_UPD:
            vd_s_EcoJdgCalcScore((U1)ECOJDG_CLC_ITM_RUN);
            st_s_ecojdg_state.u1_std   = (U1)TRUE;
            break;
        case ECOJDG_ACT_RUN_SUS:
            if(st_s_ecojdg_state.u1_std != (U1)TRUE){
                st_sp_ecojdg_clc_run[ECOJDG_CLC_ITM_RUN].u4_sum_scr = (U4)0U;
                st_sp_ecojdg_clc_run[ECOJDG_CLC_ITM_RUN].u4_sum_cnt = (U4)0U;
            }
            break;
        case ECOJDG_ACT_VEH_STP:
            if(st_s_ecojdg_state.u1_std != (U1)TRUE){
                st_sp_ecojdg_clc_run[ECOJDG_CLC_ITM_RUN].u4_sum_scr = (U4)0U;
                st_sp_ecojdg_clc_run[ECOJDG_CLC_ITM_RUN].u4_sum_cnt = (U4)0U;
            }
            else{
                vd_s_EcoJdgCalcScore((U1)ECOJDG_CLC_ITM_RUN);
            }
            vd_s_EcoJdgCalcScore((U1)ECOJDG_CLC_ITM_DEC);
            st_s_ecojdg_state.u1_dec   = (U1)FALSE;
            break;
        case ECOJDG_ACT_DEC_SUS:
            st_s_ecojdg_state.u1_dec   = (U1)TRUE;
            break;
        case ECOJDG_ACT_SUS_RES:
            if(st_s_ecojdg_state.u1_dec == (U1)TRUE){
                vd_s_EcoJdgCalcScore((U1)ECOJDG_CLC_ITM_DEC);
            }
            st_s_ecojdg_state.u1_dec = (U1)FALSE;
            st_sp_ecojdg_clc_run[ECOJDG_CLC_ITM_DEC].u4_sum_scr = (U4)0U;
            st_sp_ecojdg_clc_run[ECOJDG_CLC_ITM_DEC].u4_sum_cnt = (U4)0U;
            break;
        case ECOJDG_ACT_ALL_CLR:
            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ECOJDG_NUM_CLC_ITM; u4_t_lpcnt++){
                st_sp_ecojdg_clc_run[u4_t_lpcnt].u4_sum_scr = (U4)0U;
                st_sp_ecojdg_clc_run[u4_t_lpcnt].u4_sum_cnt = (U4)0U;
            }
            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt <= (U4)ECOJDG_SCR_RUN_TOTAL; u4_t_lpcnt++){
                u1_sp_ecojdg_scr[u4_t_lpcnt] = (U1)ECOJDG_SCR_INVALID;
            }
            st_s_ecojdg_state.u1_std   = (U1)FALSE;
            st_s_ecojdg_state.u1_dec   = (U1)FALSE;
            u1_s_ecojdg_inv_sts        = (U1)0U;
            break;
    /*  case ECOJDG_ACT_NON: */
        default:
            /* Do Nothing */
            break;
    }
}
/*===================================================================================================================================*/
/*  static void vd_s_EcoJdgCalcScore(const U1 u1_a_ITM)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_EcoJdgCalcScore(const U1 u1_a_ITM)
{
    U4      u4_t_sum_scr;
    U4      u4_t_sum_cnt;
    U4      u4_t_scr;
    U1      u1_t_inv;

    u4_t_sum_scr = st_sp_ecojdg_clc_run[u1_a_ITM].u4_sum_scr;
    u4_t_sum_cnt = st_sp_ecojdg_clc_run[u1_a_ITM].u4_sum_cnt;
    if(u4_t_sum_cnt != (U4)0U){
        u4_t_scr = (u4_t_sum_scr / u4_t_sum_cnt);
        if(u4_t_scr >  (U4)ECOJDG_DSP_SCR_MAX){
            u4_t_scr = (U4)ECOJDG_DSP_SCR_MAX;
        }

        u1_t_inv = (u1_s_ecojdg_inv_sts & (U1)(1U << u1_a_ITM));
        if(u1_t_inv != (U1)0U){
            u1_sp_ecojdg_scr[u1_a_ITM] = (U1)ECOJDG_SCR_INVALID;
            vd_s_EcoJdgCalcTotal((U1)ECOJDG_SCR_RUN_STR);
        }
        else{
            u1_sp_ecojdg_scr[u1_a_ITM] = (U1)u4_t_scr;
            vd_s_EcoJdgCalcTotal((U1)ECOJDG_SCR_RUN_STR);
        }
    }
}
/*===================================================================================================================================*/
/*  static void vd_s_EcoJdgCalcTotal(const U1 u1_a_SCR_STR)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_EcoJdgCalcTotal(const U1 u1_a_SCR_STR)
{
    U4      u4_t_lpcnt;
    U4      u4_t_sum_scr;
    U4      u4_t_sum_cnt;
    U1      u1_t_scr_total;
    U1      u1_t_total;

    u1_t_total     = (U1)ECOJDG_SCR_INVALID;
    u1_t_scr_total = (U1)ECOJDG_NUM_CLC_ITM + u1_a_SCR_STR;
    u4_t_sum_scr   = (U4)0U;
    u4_t_sum_cnt   = (U4)0U;
    for(u4_t_lpcnt = (U4)u1_a_SCR_STR; u4_t_lpcnt < (U4)u1_t_scr_total; u4_t_lpcnt++){
        if(u1_sp_ecojdg_scr[u4_t_lpcnt] != (U1)ECOJDG_SCR_INVALID){
            if(u4_t_sum_scr <= ((U4)U4_MAX - (U4)u1_sp_ecojdg_scr[u4_t_lpcnt])){
                u4_t_sum_scr += (U4)u1_sp_ecojdg_scr[u4_t_lpcnt];
            }
            else{
                u4_t_sum_scr = (U4)U4_MAX;
            }
            if(u4_t_sum_cnt < (U4)U4_MAX){
                u4_t_sum_cnt++;
            }
            else{
                u4_t_sum_cnt = (U4)U4_MAX;
            }
            u1_t_total    = (U1)(u4_t_sum_scr / u4_t_sum_cnt);
        }
    }
    u1_sp_ecojdg_scr[u1_t_scr_total] = u1_t_total;
}
/*===================================================================================================================================*/
/*  static void vd_s_EcoJdgCntScr(const U1 u1_a_ID, const U1 u1_a_SCR, const U1 u1_a_CNT)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_EcoJdgCntScr(const U1 u1_a_ID, const U1 u1_a_SCR, const U1 u1_a_CNT)
{
    U1      u1_t_inv;

    u1_t_inv = (u1_s_ecojdg_inv_sts & (U1)(1U << u1_a_ID));
    if((u1_a_CNT != st_s_ecojdg_state.u1_cnt) &&
       (u1_t_inv == (U1)0U                  )){
        switch(u1_a_ID){
            case ECOJDG_ID_STR:
                /* Fall Through */
            case ECOJDG_ID_RUN:
                if((st_sp_ecojdg_clc_run[u1_a_ID].u4_sum_scr <= ((U4)U4_MAX - (U4)u1_a_SCR)) &&
                   (st_sp_ecojdg_clc_run[u1_a_ID].u4_sum_cnt <   (U4)U4_MAX                )){

                    st_sp_ecojdg_clc_run[u1_a_ID].u4_sum_scr += (U4)u1_a_SCR;
                    st_sp_ecojdg_clc_run[u1_a_ID].u4_sum_cnt++;
                }
                break;
            case ECOJDG_ID_DEC:
                st_sp_ecojdg_clc_run[u1_a_ID].u4_sum_scr = (U4)u1_a_SCR;
                st_sp_ecojdg_clc_run[u1_a_ID].u4_sum_cnt = (U4)ECOJDG_CNT_LST;
                break;
        /*  case ECOJDG_ID_STP: */
        /*  case ECOJDG_ID_SUS: */
            default:
                /* Do Nothing */
                break;
        }
    }
    st_s_ecojdg_state.u1_id  = u1_a_ID;
    st_s_ecojdg_state.u1_cnt = u1_a_CNT;
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0    08/02/2021  YI       New.                                                                                               */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    01/28/2024  TH       Delete Ending                                                                                     */
/*                                                                                                                                   */
/*  * YI   = Yoshiki Iwata, NTTD MSE                                                                                                 */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
