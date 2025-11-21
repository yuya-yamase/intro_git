/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Vehicle Speed                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_KMPH_C_MAJOR                      (2)
#define VEHSPD_KMPH_C_MINOR                      (1)
#define VEHSPD_KMPH_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vehspd_kmph_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VEHSPD_KMPH_C_MAJOR != VEHSPD_KMPH_H_MAJOR) || \
     (VEHSPD_KMPH_C_MINOR != VEHSPD_KMPH_H_MINOR) || \
     (VEHSPD_KMPH_C_PATCH != VEHSPD_KMPH_H_PATCH))
#error "vehspd_kmph.c and vehspd_kmph.h : source and header files are inconsistent!"
#endif

#if ((VEHSPD_KMPH_C_MAJOR != VEHSPD_KMPH_CFG_H_MAJOR) || \
     (VEHSPD_KMPH_C_MINOR != VEHSPD_KMPH_CFG_H_MINOR) || \
     (VEHSPD_KMPH_C_PATCH != VEHSPD_KMPH_CFG_H_PATCH))
#error "vehspd_kmph.c and vehspd_kmph_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_FLUCT_NUM_STS                     (4U)

#define VEHSPD_FLUCT_NUM_CHK                     (6U)
#define VEHSPD_FLUCT_CHKBIT_GE_5_KMPH            (0x01U)
#define VEHSPD_FLUCT_CHKBIT_DECR_BH              (0x02U)   /* Speed is decelerated below hysteresis  */
#define VEHSPD_FLUCT_CHKBIT_INCR_OH              (0x04U)   /* Speed is accelerated over hysteresis   */

#define VEHSPD_FLUCT_ACT_TO_ZERO                 (0U)
#define VEHSPD_FLUCT_ACT_TO_INCR                 (1U)
#define VEHSPD_FLUCT_ACT_INCR                    (2U)
#define VEHSPD_FLUCT_ACT_TO_OVTH                 (3U)
#define VEHSPD_FLUCT_ACT_TO_DECR                 (4U)
#define VEHSPD_FLUCT_ACT_DECR                    (5U)

#define VEHSPD_FLUCT_10_KMPH                     (1000U)
#define VEHSPD_FLUCT_4_KMPH                      (400U)
#define VEHSPD_FLUCT_HYS_1_KMPH                  (100U)
#define VEHSPD_FLUCT_5_KMPH                      (500U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_NUM_KMPH                          (3U)
#define VEHSPD_KMPH_OW_DI                        (0U)
#define VEHSPD_KMPH_OW_EN                        (1U)
#define VEHSPD_KMPH_BIASD                        (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_SPD0KMPH                          (175U)                     /* Vehicle Speed Threshold for treating as 0km/h */
#define VEHSPD_RES_0P1_TO_0P01_KMPH              (10U)                      /* Resolution 0.1km/h to 0.01km/h                */
#define VEHSPD_IDX_CALIB_CORPT                   (1U + VEHSPD_CORPT + 1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4       u4_s_vehspd_ow_unlock;                     /* Overwrite unlock key                   */
static U2       u2_s_vehspd_ow_tout;                       /* Overwrite timer                        */

static U2       u2_sp_vehspd_kmph[VEHSPD_NUM_KMPH];        /* Vehicle speed (LSB: 0.01 km/h)         */
static U1       u1_sp_vehspd_stsbit[VEHSPD_NUM_KMPH];      /* Vehicle speed status                   */
static U1       u1_s_vehspd_if_idx;                        /* Interface index                        */

static U2       u2_s_vehspd_fluct_kmph;                    /* Vehicle speed for checking fluctuation */
static U1       u1_s_vehspd_fluct_stat;                    /* Status of vehicle speed fluctuation    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_VehspdOwchk(void);
static U2      u2_s_VehspdBiasCal(const U2 u2_a_KMPH, const ST_VEHSPD_BIAS_FACT * st_ap_FACT);

static void    vd_s_VehspdFluctchk(const U2 u2_a_KMPH);
static U1      u1_s_VehspdFuctHyschk(const U2 u2_a_KMPH);

static void    vd_s_VehspdGetBias(ST_VEHSPD_BIAS_FACT * st_ap_FACT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static volatile const U2 * u2p_sp_VEHSPD_BIAS_USA_CAN[VEHSPD_CALIB_CORPT] = {
    &u2_CALIB_MCUID0757_SP_USA_20KM,
    &u2_CALIB_MCUID0758_SP_USA_40KM,
    &u2_CALIB_MCUID0759_SP_USA_59KM,
    &u2_CALIB_MCUID0760_SP_USA_80KM,
    &u2_CALIB_MCUID0761_SP_USA_100KM,
    &u2_CALIB_MCUID0762_SP_USA_120KM,
    &u2_CALIB_MCUID0763_SP_USA_140KM,
    &u2_CALIB_MCUID0764_SP_USA_160KM,
    &u2_CALIB_MCUID0765_SP_USA_180KM,
    &u2_CALIB_MCUID0766_SP_USA_200KM,
    &u2_CALIB_MCUID0767_SP_USA_220KM,
    &u2_CALIB_MCUID0768_SP_USA_240KM,
    &u2_CALIB_MCUID0769_SP_USA_260KM,
    &u2_CALIB_MCUID0770_SP_USA_280KM,
    &u2_CALIB_MCUID0771_SP_USA_300KM,
    &u2_CALIB_MCUID0772_SP_USA_320KM,
    &u2_CALIB_MCUID0773_SP_USA_340KM,
    &u2_CALIB_MCUID0774_SP_USA_360KM,
    &u2_CALIB_MCUID0775_SP_USA_380KM,
    &u2_CALIB_MCUID0776_SP_USA_400KM
};

static volatile const U2 * u2p_sp_VEHSPD_BIAS_UNR_AUS[VEHSPD_CALIB_CORPT] = {
    &u2_CALIB_MCUID0777_SP_UNR_20KM,
    &u2_CALIB_MCUID0778_SP_UNR_40KM,
    &u2_CALIB_MCUID0779_SP_UNR_59KM,
    &u2_CALIB_MCUID0780_SP_UNR_80KM,
    &u2_CALIB_MCUID0781_SP_UNR_100KM,
    &u2_CALIB_MCUID0782_SP_UNR_120KM,
    &u2_CALIB_MCUID0783_SP_UNR_140KM,
    &u2_CALIB_MCUID0784_SP_UNR_160KM,
    &u2_CALIB_MCUID0785_SP_UNR_180KM,
    &u2_CALIB_MCUID0786_SP_UNR_200KM,
    &u2_CALIB_MCUID0787_SP_UNR_220KM,
    &u2_CALIB_MCUID0788_SP_UNR_240KM,
    &u2_CALIB_MCUID0789_SP_UNR_260KM,
    &u2_CALIB_MCUID0790_SP_UNR_280KM,
    &u2_CALIB_MCUID0791_SP_UNR_300KM,
    &u2_CALIB_MCUID0792_SP_UNR_320KM,
    &u2_CALIB_MCUID0793_SP_UNR_340KM,
    &u2_CALIB_MCUID0794_SP_UNR_360KM,
    &u2_CALIB_MCUID0795_SP_UNR_380KM,
    &u2_CALIB_MCUID0796_SP_UNR_400KM
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VehspdInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehspdInit(void)
{
    ST_VEHSPD_BIAS_FACT           st_t_fact;
    U4                            u4_t_lpcnt;

    u4_s_vehspd_ow_unlock   = (U4)0U;
    u2_s_vehspd_ow_tout     = (U2)VEHSPD_OW_TOC_MAX;

    u2_sp_vehspd_kmph[VEHSPD_KMPH_OW_DI]   = (U2)0U;
    u2_sp_vehspd_kmph[VEHSPD_KMPH_OW_EN]   = (U2)0U;
    u2_sp_vehspd_kmph[VEHSPD_KMPH_BIASD]   = (U2)0U;

    u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_DI] = (U1)VEHSPD_STSBIT_UNKNOWN;
    u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_EN] = (U1)VEHSPD_STSBIT_UNKNOWN;
    u1_sp_vehspd_stsbit[VEHSPD_KMPH_BIASD] = (U1)VEHSPD_STSBIT_UNKNOWN;

    u2_s_vehspd_fluct_kmph  = (U2)0U;
    u1_s_vehspd_fluct_stat  = (U1)VEHSPD_FLUCT_ZERO;
    st_t_fact.u1_toler_a    = (U1)VEHSPD_TOL_A_INITIAL_VALUE;
    st_t_fact.s1_toler_b    = (S1)VEHSPD_TOL_B_INITIAL_VALUE;
    vd_g_VehspdMemfillU2(&st_t_fact.u2p_bias_map[0], (U2)0U, (U2)VEHSPD_CORPT_NUM);

    u1_s_vehspd_if_idx      = u1_g_VehspdCfgIFidx();

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_VEHSPD_IF_NUM_CFG; u4_t_lpcnt++){
        if(st_gp_VEHSPD_IF_CFG[u4_t_lpcnt].fp_vd_INIT != vdp_PTR_NA){
            (st_gp_VEHSPD_IF_CFG[u4_t_lpcnt].fp_vd_INIT)();
        }
    }

    vd_s_VehspdGetBias(&st_t_fact);
    vd_g_VehspdCfgTolerXComTx(&st_t_fact);

}
/*===================================================================================================================================*/
/*  void    vd_g_VehspdOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehspdOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)
{
    U1                            u1_t_cfgidx;
    U1                            u1_t_init;

    u1_t_cfgidx = u1_s_vehspd_if_idx;
    if((u1_t_cfgidx                                       <  u1_g_VEHSPD_IF_NUM_CFG) &&
       (st_gp_VEHSPD_IF_CFG[u1_t_cfgidx].fp_u1_OPEMD_EVHK != vdp_PTR_NA            )){

        u1_t_init = (st_gp_VEHSPD_IF_CFG[u1_t_cfgidx].fp_u1_OPEMD_EVHK)(u4_a_MDBIT, u4_a_EVTBIT);
        if(u1_t_init == (U1)TRUE){

            u2_s_vehspd_ow_tout     = (U2)VEHSPD_OW_TOC_MAX;

            u2_sp_vehspd_kmph[VEHSPD_KMPH_OW_DI]   = (U2)0U;
            u2_sp_vehspd_kmph[VEHSPD_KMPH_OW_EN]   = (U2)0U;
            u2_sp_vehspd_kmph[VEHSPD_KMPH_BIASD]   = (U2)0U;

            u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_DI] = (U1)VEHSPD_STSBIT_UNKNOWN;
            u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_EN] = (U1)VEHSPD_STSBIT_UNKNOWN;
            u1_sp_vehspd_stsbit[VEHSPD_KMPH_BIASD] = (U1)VEHSPD_STSBIT_UNKNOWN;

            u2_s_vehspd_fluct_kmph  = (U2)0U;
            u1_s_vehspd_fluct_stat  = (U1)VEHSPD_FLUCT_ZERO;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_VehspdMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehspdMainTask(void)
{
    ST_VEHSPD_BIAS_FACT           st_t_fact;

    U4                            u4_t_odocnt;
    U2                            u2_t_kmph;
    U1                            u1_t_stsbit;
    U1                            u1_t_cfgidx;

    u4_t_odocnt = (U4)0U;
    u2_t_kmph   = (U2)0U;
    u1_t_stsbit = (U1)VEHSPD_STSBIT_UNKNOWN;
    st_t_fact.u1_toler_a    = (U1)VEHSPD_TOL_A_INITIAL_VALUE;
    st_t_fact.s1_toler_b    = (S1)VEHSPD_TOL_B_INITIAL_VALUE;
    vd_g_VehspdMemfillU2(&st_t_fact.u2p_bias_map[0], (U2)0U, (U2)VEHSPD_CORPT_NUM);

    u1_t_cfgidx = u1_g_VehspdCfgIFidx();
    if(u1_t_cfgidx < u1_g_VEHSPD_IF_NUM_CFG){

        if((u1_s_vehspd_if_idx                          != u1_t_cfgidx) &&
           (st_gp_VEHSPD_IF_CFG[u1_t_cfgidx].fp_vd_INIT != vdp_PTR_NA )){
            (st_gp_VEHSPD_IF_CFG[u1_t_cfgidx].fp_vd_INIT)();
        }

        if(st_gp_VEHSPD_IF_CFG[u1_t_cfgidx].fp_u1_KMPH != vdp_PTR_NA){
            u1_t_stsbit  = (st_gp_VEHSPD_IF_CFG[u1_t_cfgidx].fp_u1_KMPH)(&u2_t_kmph, &u4_t_odocnt);
            u1_t_stsbit &= ((U1)VEHSPD_STSBIT_UNKNOWN | (U1)VEHSPD_STSBIT_INVALID | (U1)VEHSPD_STSBIT_EMSTOP);
        }
        u1_s_vehspd_if_idx = u1_t_cfgidx;
    }
    else{
        u1_s_vehspd_if_idx = (U1)U1_MAX;
    }

    if(u1_t_stsbit != (U1)VEHSPD_STSBIT_INVALID){
        u2_sp_vehspd_kmph[VEHSPD_KMPH_OW_DI] = u2_t_kmph;
    }
    u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_DI] = u1_t_stsbit;

    vd_s_VehspdOwchk();
    vd_s_VehspdGetBias(&st_t_fact);

    u2_t_kmph   = u2_s_VehspdBiasCal(u2_sp_vehspd_kmph[VEHSPD_KMPH_OW_EN], &st_t_fact);
    u1_t_stsbit = u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_EN];
    u2_sp_vehspd_kmph[VEHSPD_KMPH_BIASD]   = u2_t_kmph;
    u1_sp_vehspd_stsbit[VEHSPD_KMPH_BIASD] = u1_t_stsbit;
    vd_g_VehspdCfgTolerXComTx(&st_t_fact);

    if(u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_EN] == (U1)VEHSPD_STSBIT_VALID){
        u2_t_kmph = u2_sp_vehspd_kmph[VEHSPD_KMPH_OW_EN];
    }
    else{
        u2_t_kmph = (U2)0U;
    }
    vd_s_VehspdFluctchk(u2_t_kmph);
    vd_g_VehspdCfgMedspdComTx(u2_t_kmph);

    vd_g_VehspdCfgOdoInst(u4_t_odocnt, u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_DI]);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VehspdKmphInst(U2 * u2_ap_kmph, const U1 u1_a_OW_EN)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VehspdKmphInst(U2 * u2_ap_kmph, const U1 u1_a_OW_EN)
{
    U1                            u1_t_stsbit;
    U1                            u1_t_unk;

#if (VEHSPD_KMPH_OW_DI != FALSE)
#error "vehspd_kmph.c : VEHSPD_KMPH_OW_DI shall be equal to FALSE."
#endif

#if (VEHSPD_KMPH_OW_EN != TRUE)
#error "vehspd_kmph.c : VEHSPD_KMPH_OW_EN shall be equal to TRUE."
#endif

    if(u1_a_OW_EN <= (U1)VEHSPD_KMPH_OW_EN){

        u1_t_stsbit = u1_sp_vehspd_stsbit[u1_a_OW_EN];
        u1_t_unk    = u1_t_stsbit & (U1)VEHSPD_STSBIT_UNKNOWN;

        if((u1_t_unk   == (U1)0U    ) &&
           (u2_ap_kmph != vdp_PTR_NA)){
            (*u2_ap_kmph) = u2_sp_vehspd_kmph[u1_a_OW_EN];
        }
    }
    else{
        u1_t_stsbit = (U1)VEHSPD_STSBIT_UNKNOWN;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VehspdKmphBiased(U2 * u2_ap_kmph, const U1 u1_a_BC)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VehspdKmphBiased(U2 * u2_ap_kmph, const U1 u1_a_BC)
{
    ST_VEHSPD_BIAS_FACT           st_t_fact;

    U1                            u1_t_stsbit;
    U1                            u1_t_unk;

    if(u1_a_BC == (U1)TRUE){

        if(u2_ap_kmph           != vdp_PTR_NA){
            st_t_fact.u1_toler_a    = (U1)VEHSPD_TOL_A_INITIAL_VALUE;
            st_t_fact.s1_toler_b    = (S1)VEHSPD_TOL_B_INITIAL_VALUE;
            vd_g_VehspdMemfillU2(&st_t_fact.u2p_bias_map[0], (U2)0U, (U2)VEHSPD_CORPT_NUM);
            vd_s_VehspdGetBias(&st_t_fact);
            (*u2_ap_kmph) = u2_s_VehspdBiasCal((*u2_ap_kmph), &st_t_fact);
            u1_t_stsbit   = (U1)VEHSPD_STSBIT_VALID;
        }
        else{
            u1_t_stsbit   = (U1)VEHSPD_STSBIT_UNKNOWN;
        }
    }
    else{

        u1_t_stsbit = u1_sp_vehspd_stsbit[VEHSPD_KMPH_BIASD];
        u1_t_unk    = u1_t_stsbit & (U1)VEHSPD_STSBIT_UNKNOWN;
        if((u1_t_unk   == (U1)0U    ) &&
           (u2_ap_kmph != vdp_PTR_NA)){
            (*u2_ap_kmph) = u2_sp_vehspd_kmph[VEHSPD_KMPH_BIASD];
        }
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VehspdFluctStat(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VehspdFluctStat(void)
{
    return(u1_s_vehspd_fluct_stat);
}
/*===================================================================================================================================*/
/*  void    vd_g_VehspdKmphOwUnlock(const U4 u4_a_KEY)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehspdKmphOwUnlock(const U4 u4_a_KEY)
{
    u4_s_vehspd_ow_unlock = u4_a_KEY;
}
/*===================================================================================================================================*/
/*  void    vd_g_VehspdKmphOwAct(const U2 u2_a_KMPH)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehspdKmphOwAct(const U2 u2_a_KMPH)
{
    if(u4_s_vehspd_ow_unlock == (U4)VEHSPD_OW_UNLOCK){

        u2_s_vehspd_ow_tout                    = (U2)U2_MAX;

        u2_sp_vehspd_kmph[VEHSPD_KMPH_OW_EN]   = u2_a_KMPH;
        u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_EN] = u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_DI] & (U1)VEHSPD_STSBIT_EMSTOP;
    }
    u4_s_vehspd_ow_unlock = (U4)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_VehspdKmphOwDeAct(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehspdKmphOwDeAct(void)
{
    u4_s_vehspd_ow_unlock = (U4)0U;
    u2_s_vehspd_ow_tout   = (U2)VEHSPD_OW_TOC_MAX;
}
/*===================================================================================================================================*/
/*  static void    vd_s_VehspdOwchk(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VehspdOwchk(void)
{
    u4_s_vehspd_ow_unlock = (U4)0U;

    if(u2_s_vehspd_ow_tout >= (U2)U2_MAX){
        u2_s_vehspd_ow_tout = (U2)0U;
    }
    else if(u2_s_vehspd_ow_tout >= (U2)VEHSPD_OW_TOC_MAX){
        u2_s_vehspd_ow_tout = (U2)VEHSPD_OW_TOC_MAX;
    }
    else{
        u2_s_vehspd_ow_tout++;/* QAC over-detection */
    }

    if(u2_s_vehspd_ow_tout >= u2_g_VEHSPD_KMPH_OW_TOUT){
        u2_sp_vehspd_kmph[VEHSPD_KMPH_OW_EN]   = u2_sp_vehspd_kmph[VEHSPD_KMPH_OW_DI];
        u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_EN] = u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_DI];
    }
    else{
        u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_EN] = u1_sp_vehspd_stsbit[VEHSPD_KMPH_OW_DI] & (U1)VEHSPD_STSBIT_EMSTOP;
    }
}
/*===================================================================================================================================*/
/*  static U2      u2_s_VehspdBiasCal(const U2 u2_a_KMPH, const ST_VEHSPD_BIAS_FACT * st_ap_FACT)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_VehspdBiasCal(const U2 u2_a_KMPH, const ST_VEHSPD_BIAS_FACT * st_ap_FACT)
{
    U2                            u2_t_kmph_cal;

    u2_t_kmph_cal = u2_g_VehspdLerpU2(u2_a_KMPH, st_ap_FACT->u2p_bias_map);

    return(u2_t_kmph_cal);
}
/*===================================================================================================================================*/
/*  static void    vd_s_VehspdFluctchk(const U2 u2_a_KMPH)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VehspdFluctchk(const U2 u2_a_KMPH)
{
    static const U1               u1_sp_VEHSPD_FLUCT_STM[VEHSPD_FLUCT_NUM_CHK][VEHSPD_FLUCT_NUM_STS]={  /* Action decision table  */
        {(U1)VEHSPD_FLUCT_ACT_TO_ZERO, (U1)VEHSPD_FLUCT_ACT_INCR,    (U1)VEHSPD_FLUCT_ACT_TO_DECR, (U1)VEHSPD_FLUCT_ACT_DECR   },
        {(U1)VEHSPD_FLUCT_ACT_TO_INCR, (U1)VEHSPD_FLUCT_ACT_INCR,    (U1)VEHSPD_FLUCT_ACT_TO_DECR, (U1)VEHSPD_FLUCT_ACT_DECR   },
        {(U1)VEHSPD_FLUCT_ACT_TO_ZERO, (U1)VEHSPD_FLUCT_ACT_TO_DECR, (U1)VEHSPD_FLUCT_ACT_TO_DECR, (U1)VEHSPD_FLUCT_ACT_TO_DECR},
        {(U1)VEHSPD_FLUCT_ACT_TO_INCR, (U1)VEHSPD_FLUCT_ACT_TO_DECR, (U1)VEHSPD_FLUCT_ACT_TO_DECR, (U1)VEHSPD_FLUCT_ACT_TO_DECR},
        {(U1)VEHSPD_FLUCT_ACT_TO_ZERO, (U1)VEHSPD_FLUCT_ACT_TO_INCR, (U1)VEHSPD_FLUCT_ACT_TO_DECR, (U1)VEHSPD_FLUCT_ACT_TO_INCR},
        {(U1)VEHSPD_FLUCT_ACT_TO_INCR, (U1)VEHSPD_FLUCT_ACT_TO_INCR, (U1)VEHSPD_FLUCT_ACT_TO_DECR, (U1)VEHSPD_FLUCT_ACT_TO_INCR}
    };

    U1                            u1_t_chkbit;
    U1                            u1_t_act;

    if(u2_a_KMPH > (U2)VEHSPD_FLUCT_10_KMPH){
        u1_t_act = (U1)VEHSPD_FLUCT_ACT_TO_OVTH;
    }
    else if((u2_a_KMPH              <  (U2)VEHSPD_FLUCT_4_KMPH ) ||
            (u1_s_vehspd_fluct_stat >= (U1)VEHSPD_FLUCT_NUM_STS)){
        u1_t_act = (U1)VEHSPD_FLUCT_ACT_TO_ZERO;
    }
    else{
        u1_t_chkbit = u1_s_VehspdFuctHyschk(u2_a_KMPH);
        u1_t_act = u1_sp_VEHSPD_FLUCT_STM[u1_t_chkbit][u1_s_vehspd_fluct_stat];
    }

    switch(u1_t_act){
        case VEHSPD_FLUCT_ACT_TO_INCR:
            u1_s_vehspd_fluct_stat = (U1)VEHSPD_FLUCT_INCR;
            u2_s_vehspd_fluct_kmph = u2_a_KMPH;
            break;
        case VEHSPD_FLUCT_ACT_INCR:
            u1_s_vehspd_fluct_stat = (U1)VEHSPD_FLUCT_INCR;
            break;
        case VEHSPD_FLUCT_ACT_TO_OVTH:
            u1_s_vehspd_fluct_stat = (U1)VEHSPD_FLUCT_OVTH;
            break;
        case VEHSPD_FLUCT_ACT_TO_DECR:
            u1_s_vehspd_fluct_stat = (U1)VEHSPD_FLUCT_DECR;
            u2_s_vehspd_fluct_kmph = u2_a_KMPH;
            break;
        case VEHSPD_FLUCT_ACT_DECR:
            u1_s_vehspd_fluct_stat = (U1)VEHSPD_FLUCT_DECR;
            break;
        default:
            u1_s_vehspd_fluct_stat = (U1)VEHSPD_FLUCT_ZERO;
            u2_s_vehspd_fluct_kmph = (U2)0U;
            break;
    }
}
/*===================================================================================================================================*/
/*  static U1   u1_s_VehspdFuctHyschk(const U2 u2_a_KMPH)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_VehspdFuctHyschk(const U2 u2_a_KMPH)
{
    U4                            u4_t_inc_chk;
    U4                            u4_t_dec_chk;
    U1                            u1_t_chk;

    u4_t_inc_chk = (U4)u2_s_vehspd_fluct_kmph + (U4)VEHSPD_FLUCT_HYS_1_KMPH;
                                        /* The type of u2_s_vehspd_fluct_kmph is U2, so max value of u2_s_vehspd_fluct_kmph is 65535.*/
                                        /* The value of VEHSPD_FLUCT_HYS_1_KMPH is 100.                                              */
                                        /* Therefor (u2_s_vehspd_fluct_kmph + VEHSPD_FLUCT_HYS_1_KMPH) is always lower than U4_MAX   */
    if(u4_t_inc_chk > (U4)U2_MAX){
        u4_t_inc_chk = (U4)U2_MAX;
    }

    if(u2_s_vehspd_fluct_kmph > (U2)VEHSPD_FLUCT_HYS_1_KMPH){
        u4_t_dec_chk = (U4)u2_s_vehspd_fluct_kmph - (U4)VEHSPD_FLUCT_HYS_1_KMPH; /* QAC over-detection */
    }
    else{
        u4_t_dec_chk = (U4)0U;
    }

    if(u2_a_KMPH >= (U2)VEHSPD_FLUCT_5_KMPH){
        u1_t_chk  = (U1)VEHSPD_FLUCT_CHKBIT_GE_5_KMPH;
    }
    else{
        u1_t_chk  = (U1)0U;
    }

    if(u4_t_inc_chk <= (U4)u2_a_KMPH){
        u1_t_chk |= (U1)VEHSPD_FLUCT_CHKBIT_INCR_OH;
    }
    else if(u4_t_dec_chk >= (U4)u2_a_KMPH){
        u1_t_chk |= (U1)VEHSPD_FLUCT_CHKBIT_DECR_BH;
    }
    else{
        /* Do nothing */
    }

    return(u1_t_chk);
}
/*===================================================================================================================================*/
/*  static void   vd_s_VehspdGetBias(const ST_VEHSPD_BIAS_FACT * st_ap_FACT)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void   vd_s_VehspdGetBias(ST_VEHSPD_BIAS_FACT * st_ap_FACT)
{
    static const U2               u2_sp_VEHSPD_BIAS_MAP_FIXEDVAL[VEHSPD_IDX_CALIB_CORPT] = { /* Const table of "u2p_bias_map" */
        (U2)VEHSPD_CORPT,
        (U2)VEHSPD_SPD0KMPH,  (U2)2000U,  (U2)4000U,  (U2)5900U,  (U2)8000U,  (U2)10000U, (U2)12000U, (U2)14000U, (U2)16000U, (U2)18000U, (U2)20000U, (U2)22000U, (U2)24000U, (U2)26000U, (U2)28000U, (U2)30000U, (U2)32000U, (U2)34000U, (U2)36000U, (U2)38000U, (U2)40000U,
        (U2)0U
    };

    U1                            u1_t_bias_idx;
    U1                            u1_t_toler_a;
    S1                            s1_t_toler_b;
    const volatile U2 *           *u2_tp_BIAS_MAP;
    U2                            u2_t_bias_data_0p1kmph;
    U4                            u4_t_lpcnt;

    u1_t_bias_idx = u1_g_VehspdSpdTlrnc();

    if(u1_t_bias_idx == (U1)VEHSPD_SPDTLRNC_USA_CAN){       /* Vehicle Speed ​​Tolerance in Usa/Canada */
        u1_t_toler_a   = u1_VEHSPD_CALIB_TOLER_A_USA_CAN;
        s1_t_toler_b   = s1_VEHSPD_CALIB_TOLER_B_USA_CAN;
        u2_tp_BIAS_MAP = &u2p_sp_VEHSPD_BIAS_USA_CAN[0]; 
    }
    else{                                                   /* Vehicle Speed ​​Tolerance in UNR/Australia/others or Default Settings */
        u1_t_toler_a   = u1_VEHSPD_CALIB_TOLER_A_UNR_AUS;
        s1_t_toler_b   = s1_VEHSPD_CALIB_TOLER_B_UNR_AUS;
        u2_tp_BIAS_MAP = &u2p_sp_VEHSPD_BIAS_UNR_AUS[0];
    }

    st_ap_FACT->u1_toler_a = u1_t_toler_a;
    st_ap_FACT->s1_toler_b = s1_t_toler_b;
    vd_g_VehspdMemcpyU2(&st_ap_FACT->u2p_bias_map[0], &u2_sp_VEHSPD_BIAS_MAP_FIXEDVAL[0], (U2)VEHSPD_IDX_CALIB_CORPT);
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)VEHSPD_CALIB_CORPT; u4_t_lpcnt++){
        u2_t_bias_data_0p1kmph = *(u2_tp_BIAS_MAP[u4_t_lpcnt]);
        if(((U4)u2_t_bias_data_0p1kmph * (U4)VEHSPD_RES_0P1_TO_0P01_KMPH) < (U4)U2_MAX){
            st_ap_FACT->u2p_bias_map[(U4)VEHSPD_IDX_CALIB_CORPT + u4_t_lpcnt] = u2_t_bias_data_0p1kmph * (U2)VEHSPD_RES_0P1_TO_0P01_KMPH;
        }
        else{
            st_ap_FACT->u2p_bias_map[(U4)VEHSPD_IDX_CALIB_CORPT + u4_t_lpcnt] = (U2)U2_MAX;
        }
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
/*  1.0.0     1/29/2018  TN       New.                                                                                               */
/*  1.1.0     3/ 9/2018  TN       Bias calculation was implemented.                                                                  */
/*  1.2.0     3/21/2018  TN       Improvement : u2_s_vehspd_kmph_biased was initialized to 0 if stsbit was not "valid".              */
/*  1.3.0     7/ 6/2018  TN       Improvement : u2_s_vehspd_kmph_inst could be updated even if u1_t_stsbit is IVALID.                */
/*  1.4.0     2/28/2019  TN       Improvement : The status "UNKNOWN" of source signal was not checked in u1_g_VehspdKmphInst and     */
/*                                u1_g_VehspdKmphBiased.                                                                             */
/*  1.5.0     5/28/2019  TN       Improvement : vd_g_VehspdKmphOwUnlock was implemented.                                             */
/*  1.6.0    10/17/2019  TN       Improvement : u2_s_vehspd_ow_tout handling was optimized.                                          */
/*  1.7.0     7/ 7/2020  HY       Apply the improvement of 775B-v131-r015 version.                                                   */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.0    06/06/2024  SM       Corrected the method of calculating the tolerance of the median tolerance to linear imputation.    */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1  08/22/2023  SN       Delete Tolerance Information Table. Create a new function that returns tolerance information       */
/* 19PFv3-2  01/15/2024  TN(DT)   Change for MCUCONSTv010 Shipping Constant.                                                         */
/* 19PFv3-3  04/16/2024  SH       Add calibration guard                                                                              */
/* BEV-1     10/22/2025  TS       Change for BEV rebase                                                                              */
/*                                                                                                                                   */
/*  * TN     = Takashi Nagai, Denso                                                                                                  */
/*  * HY     = Hiroshige Yanase, Denso Techno                                                                                        */
/*  * TA(M)  = Teruyuki Anjima, NTT Data MSE                                                                                         */
/*  * SN     = Shimon Nambu, Denso Techno                                                                                            */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*  * SH     = Sae Hirose, Denso Techno                                                                                              */
/*  * SM     = Shota Maegawa, Denso Techno                                                                                           */
/*  * TS     = Takuo Suganuma, Denso Techno                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
