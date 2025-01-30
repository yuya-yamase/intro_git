/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Power-train System Coolant Temperature WTSSR                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTSCTMP_WTSSR_C_MAJOR                      (2)
#define PTSCTMP_WTSSR_C_MINOR                      (1)
#define PTSCTMP_WTSSR_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ptsctmp_cel_cfg_private.h"
#include "ptsctmp_wtssr.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((PTSCTMP_WTSSR_C_MAJOR != PTSCTMP_WTSSR_H_MAJOR) || \
     (PTSCTMP_WTSSR_C_MINOR != PTSCTMP_WTSSR_H_MINOR) || \
     (PTSCTMP_WTSSR_C_PATCH != PTSCTMP_WTSSR_H_PATCH))
#error "ptsctmp_cel.c and ptsctmp_cel.h : source and header files are inconsistent!"
#endif

#if ((PTSCTMP_WTSSR_C_MAJOR != PTSCTMP_CEL_CFG_H_MAJOR) || \
     (PTSCTMP_WTSSR_C_MINOR != PTSCTMP_CEL_CFG_H_MINOR) || \
     (PTSCTMP_WTSSR_C_PATCH != PTSCTMP_CEL_CFG_H_PATCH))
#error "ptsctmpl_cel.c and ptsctmp_cel_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTSCTMP_FLTR_MVAVG_FIRST                 (4U)
#define PTSCTMP_FLTR_MVAVG_TMS_MAX               (8U)
#define PTSCTMP_WTSSR_CNTMAX                     (PTSCTMP_FLTR_MVAVG_TMS_MAX - 1U)

#define PTSCTMP_WTSSR_SMPL_STS_UNDEF             (0U)
#define PTSCTMP_WTSSR_SMPL_STS_NORMA             (1U)

#define PTSCTMP_WTSSR_AD_MAX                     (1023U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2       u2_sp_ptsctmp_wtssr_smpl[PTSCTMP_FLTR_MVAVG_TMS_MAX];
static U1       u1_s_ptsctmp_wtssr_cnt;
static U1       u1_s_ptsctmp_wtssr_smpl_sts;
static U1       u1_s_ptsctmp_wtssr_col;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2 u2_s_WTSSR_BatCorr(const U2 u2_a_AD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_PtsctmpInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PtsctmpWtssrInit(void)
{
    U4  u4_t_loop;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)PTSCTMP_FLTR_MVAVG_TMS_MAX ; u4_t_loop++){
        u2_sp_ptsctmp_wtssr_smpl[u4_t_loop] = (U2)0U;
    }
    u1_s_ptsctmp_wtssr_cnt      = (U1)U1_MAX;
    u1_s_ptsctmp_wtssr_smpl_sts = (U1)PTSCTMP_WTSSR_SMPL_STS_UNDEF;
    u1_s_ptsctmp_wtssr_col      = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void    vd_g_PtsctmpOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PtsctmpWtssrOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)
{
    U4                  u4_t_evtchk;

    u4_t_evtchk = u4_a_EVTBIT & ((U4)VEH_OPEMD_EVTBIT_IGN_TO_ON |(U4)VEH_OPEMD_EVTBIT_IGN_TO_OFF);
    if(u4_t_evtchk != (U4)0U){
        vd_g_PtsctmpWtssrInit();
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_PtsctmpMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_PtsctmpWtssrMainTask(void)
{
    static const U2 u2_sp_PTSCTMP_WTSSR_LIMIT[] = {
        (U2)    0U,  /* MIN 120cel */
        (U2)   40U,  /* MIN 113cel */
        (U2)   45U,  /* MAX 120cel */
        (U2)U2_MAX   /* MAX 113cel */
    };
    static const ST_RNG_CMPR_U2    st_s_PTSCTMP_WTSSR_CMPR = {
        &u2_sp_PTSCTMP_WTSSR_LIMIT[0],      /* u2p_LIMIT   */
        (U2)0U,                             /* u2_idx_init */
        (U2)2U                              /* u2_num_rng  */
    };
    U1      u1_t_igon;
    U1      u1_t_stsbit;
    U2      u2_t_wtssr_ad;
    U4      u4_t_sum;
    U2      u2_t_ave;
    U4      u4_t_loop;
    U1      u1_t_ret;

    u1_t_igon = u1_g_PtsctmpCfgIgOn();
    if(u1_t_igon == (U1)TRUE){
        u2_t_wtssr_ad = (U2)0U;
        u1_t_stsbit   = u1_g_PtsctmpCfgAdcRead(u1_g_PTSCTMP_ADC_CH_WTSSR, &u2_t_wtssr_ad);
        u2_t_wtssr_ad = u2_s_WTSSR_BatCorr(u2_t_wtssr_ad);
        if((u1_t_stsbit   == (U1)TRUE                ) &&
           (u2_t_wtssr_ad <= (U2)PTSCTMP_WTSSR_AD_MAX)) {
            if(u1_s_ptsctmp_wtssr_cnt >= (U1)PTSCTMP_WTSSR_CNTMAX){
                u1_s_ptsctmp_wtssr_cnt = (U1)0U;
            }
            else{
                u1_s_ptsctmp_wtssr_cnt++; /* QAC over-detection                       */
            }
            
            u2_sp_ptsctmp_wtssr_smpl[u1_s_ptsctmp_wtssr_cnt] = u2_t_wtssr_ad;
            if(u1_s_ptsctmp_wtssr_cnt >= (U1)PTSCTMP_WTSSR_CNTMAX){
                u4_t_sum = (U4)0U;
                if(u1_s_ptsctmp_wtssr_smpl_sts == (U1)PTSCTMP_WTSSR_SMPL_STS_NORMA){
                    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)PTSCTMP_FLTR_MVAVG_TMS_MAX; u4_t_loop++){
                        u4_t_sum += (U4)u2_sp_ptsctmp_wtssr_smpl[u4_t_loop];
                        /* The maximum value of u2_t_wtssr_ad is 1023. The value of PTSCTMP_FLTR_MVAVG_TMS_MAX is 7.                 */
                        /* so u4_t_sum is always less than U4_MAX.                                                                   */
                    }
                    u4_t_sum >>= 3U;
                }
                else{
                    for(u4_t_loop = (U4)PTSCTMP_FLTR_MVAVG_FIRST; u4_t_loop < (U4)PTSCTMP_FLTR_MVAVG_TMS_MAX; u4_t_loop++){
                        u4_t_sum += (U4)u2_sp_ptsctmp_wtssr_smpl[u4_t_loop];
                        /* The maximum value of u2_t_wtssr_ad is 1023. The value of PTSCTMP_FLTR_MVAVG_TMS_MAX is 7.                 */
                        /* so u4_t_sum is always less than U4_MAX.                                                                   */
                    }
                    u4_t_sum >>= 2U;
                    u1_s_ptsctmp_wtssr_smpl_sts = (U1)PTSCTMP_WTSSR_SMPL_STS_NORMA;
                }
                if(u4_t_sum >= (U4)U2_MAX){
                    u2_t_ave = (U2)U2_MAX;
                }
                else{
                    u2_t_ave = (U2)u4_t_sum;
                }
                u1_s_ptsctmp_wtssr_col = (U1)u2_g_PtsctmpCfgRngCmprU2((U2)u1_s_ptsctmp_wtssr_col, u2_t_ave, &st_s_PTSCTMP_WTSSR_CMPR);
            }
        }
    }
    else{
        vd_g_PtsctmpWtssrInit();
    }

    u1_t_ret = ((U1)U1_MAX ^ u1_s_ptsctmp_wtssr_col) & (U1)TRUE;

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U2 u2_s_WTSSR_BatCorr(const U2 u2_a_AD)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2 u2_s_WTSSR_BatCorr(const U2 u2_a_AD)
{
    static const U2 u2_s_PTSCTMP_WTSSR_SW5_OK     = (U2)819U;
    static const U2 u2_s_PTSCTMP_WTSSR_SW5_DIFFOK = (U2)205U;
    static const U4 u4_s_PTSCTMP_WTSSR_REF_AD     = (U4)1016U;
    U2  u2_t_sw5_before;
    U2  u2_t_sw5_after;
    U4  u4_t_sw5_ref;
    U2  u2_t_sw5_diff;
    U1  u1_t_stsbit;
    U2  u2_t_corr_res;
    U4  u4_t_corr;

    u2_t_sw5_before = (U2)0U;
    u2_t_sw5_after  = (U2)0U;
    u1_t_stsbit     = u1_g_PtsctmpCfgAdcRead(u1_g_PTSCTMP_ADC_CH_SW5_BEFORE, &u2_t_sw5_before);
    u1_t_stsbit    &= u1_g_PtsctmpCfgAdcRead(u1_g_PTSCTMP_ADC_CH_SW5_AFTER,  &u2_t_sw5_after);

    u2_t_corr_res = (U2)U2_MAX;
    if(u1_t_stsbit == (U1)TRUE){
        if(u2_t_sw5_before < u2_t_sw5_after){
            u2_t_sw5_diff = u2_t_sw5_after - u2_t_sw5_before;
        }
        else{
            u2_t_sw5_diff = u2_t_sw5_before - u2_t_sw5_after;
        }
        if((u2_t_sw5_before >= u2_s_PTSCTMP_WTSSR_SW5_OK    ) &&
           (u2_t_sw5_after  >= u2_s_PTSCTMP_WTSSR_SW5_OK    ) &&
           (u2_t_sw5_diff   <  u2_s_PTSCTMP_WTSSR_SW5_DIFFOK)){
            u4_t_sw5_ref = ((U4)u2_t_sw5_before + (U4)u2_t_sw5_after) >> 1;
            /* The maximum value of u2_t_sw5_before is 1023. The maximum value of u2_t_sw5_after is 1023.                            */
            /* so ((U4)u2_t_sw5_before + (U4)u2_t_sw5_after) is always less than U4_MAX.                                             */

            if(u4_t_sw5_ref != (U4)0U){
                u4_t_corr  = (U4)u2_a_AD * u4_s_PTSCTMP_WTSSR_REF_AD;
                /* The maximum value of u2_a_AD is 1023. The value of u4_s_PTSCTMP_WTSSR_REF_AD is 1016.                             */
                /* so ((U4)u2_a_AD * u4_s_PTSCTMP_WTSSR_REF_AD) is always less than U4_MAX.                                          */
                u4_t_corr /= u4_t_sw5_ref;
                if(u4_t_corr <= (U4)PTSCTMP_WTSSR_AD_MAX){
                    u2_t_corr_res = (U2)u4_t_corr;
                }
                else{
                    u2_t_corr_res = (U2)PTSCTMP_WTSSR_AD_MAX;
                }
            }
            else{
                u2_t_corr_res = (U2)PTSCTMP_WTSSR_AD_MAX;
            }
        }
    }
    return(u2_t_corr_res);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.1.0    10/18/2021  TA(M)    New                                                                                                */
/*                                                                                                                                   */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
