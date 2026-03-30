/* 1.0.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  Time Stamp Control                                                                                                               */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_TMSTP_C_MAJOR                    (1U)
#define TYDOCAN_TMSTP_C_MINOR                    (0U)
#define TYDOCAN_TMSTP_C_PATCH                    (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "tydocan_tmstp_cfg_private.h"

#include "Dcm.h"

#include "oxdocan_aubif.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_TMSTP_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_tmstp.c and tydocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (TYDOCAN_TMSTP_C_MAJOR != OXDOCAN_SAL_H_MAJOR)
#error "tydocan_tmstp.c and tydocan_sal.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_TMSTP_C_MAJOR != TYDOCAN_TMSTP_CFG_H_MAJOR) || \
     (TYDOCAN_TMSTP_C_MINOR != TYDOCAN_TMSTP_CFG_H_MINOR) || \
     (TYDOCAN_TMSTP_C_PATCH != TYDOCAN_TMSTP_CFG_H_PATCH))
#error "tydocan_tmstp.c and tydocan_tmstp_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_TMSTP_BR_UNK                       (0x0000U)
#define OXDC_TMSTP_BR_LAS                       (0x5aa5U)

#define OXDC_TMSTP_NVM_SIZE                     (8U)
#define OXDC_TMSTP_NVM_TRIC_IDX_2ND             (0U)
#define OXDC_TMSTP_NVM_TRIC_IDX_1ST             (1U)
#define OXDC_TMSTP_NVM_TIMC_IDX_4TH             (2U)
#define OXDC_TMSTP_NVM_TIMC_IDX_3RD             (3U)
#define OXDC_TMSTP_NVM_TIMC_IDX_2ND             (4U)
#define OXDC_TMSTP_NVM_TIMC_IDX_1ST             (5U)

#define OXDC_DTF_SIZE_TMSP                      (32U)

#define OXDC_TMSTP_BCD_DIGIT_BASE               (10U)
#define OXDC_TMSTP_BCD_DIGIT_LSB_NEXT           (4U)
#define OXDC_TMSTP_BCD_DIGIT_BIT_LEAST          (0x0000000fU)
#define OXDC_TMSTP_BCD_CNVRT_BCD_MAX            (0x99999999U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1                 u1_min;
    U1                 u1_max;
}ST_OXDC_TMSTP_GMT;

typedef struct{
    U4                 u4_odo;          /* unit : 0.1km */
    U2                 u2_tri_cnt;
    U1                 u1_sync;
    U1                 u1_run;
    volatile U2        u2_chk;
}ST_OXDC_TMSTP_BR;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef OXDC_BSS_BACK
static ST_OXDC_TMSTP_BR      st_s_oxdc_tmstp_br  __attribute__((section(".bss_BACK")));
static U4                    u4_s_oxdc_tmstp_timc_ofst_br  __attribute__((section(".bss_BACK")));
static U4                    u4_s_oxdc_tmstp_timc_nvm_br  __attribute__((section(".bss_BACK")));
#else
static ST_OXDC_TMSTP_BR      st_s_oxdc_tmstp_br;
static U4                    u4_s_oxdc_tmstp_timc_ofst_br;
static U4                    u4_s_oxdc_tmstp_timc_nvm_br;
#endif

static U4                    u4_s_oxdc_tmstp_odo;       /* unit : 0.1km */
static U4                    u4_s_oxdc_tmstp_tim_cnt;
static U2                    u2_s_oxdc_tmstp_tri_cnt;
static U1                    u1_s_oxdc_tmstp_sync;
static U1                    u1_s_oxdc_tmstp_run;

static U4                    u4_sp_oxdc_tmstp_gmt[OXDC_TMSTP_GMT_NDWORD];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_oXdcTmstpStampUpdt(const U2 u2_a_TSLOT, const U1 u1_a_TMSTP_POW);
static void    vd_s_oXdcTmstpTripUpdt(void);
static void    vd_s_oXdcTmstpGmtUpdt(void);

static void    vd_s_oXdcTmstpTripcnt(const U2 u2_a_TRI_CNT, const U4 u4_a_TIM_CNT, const U1 u1_a_SYNC, U1 * u1_ap_ans);
static void    vd_s_oXdcTmstpOdo(const U4 u4_a_ODO, U1 * u1_ap_ans);
static void    vd_s_oXdcTmstpWriteNvm(const U2 u2_a_TRI_CNT, const U4 u4_a_TIM_CNT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_OXDC_TMSTP_GMT     st_sp_OXDC_TMSTP_GMT[OXDC_TMSTP_GMT_NUM] = {
    {(U1)0U, (U1)99U},    /* OXDC_TMSTP_GMT_IDX_YE (0U) */
    {(U1)1U, (U1)12U},    /* OXDC_TMSTP_GMT_IDX_MO (1U) */
    {(U1)1U, (U1)31U},    /* OXDC_TMSTP_GMT_IDX_DA (2U) */
    {(U1)0U, (U1)23U},    /* OXDC_TMSTP_GMT_IDX_HO (3U) */
    {(U1)0U, (U1)59U},    /* OXDC_TMSTP_GMT_IDX_MI (4U) */
    {(U1)0U, (U1)59U}     /* OXDC_TMSTP_GMT_IDX_SE (5U) */
};

const U1               u1_gp_TYDC_DTF_INIT_TMSP[OXDC_DTF_SIZE_TMSP] = {
    (U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,
    (U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0xE9U,(U1)0x77U,(U1)0x70U,(U1)0x80U
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANTmstpBonInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANTmstpBonInit(void)
{
    U1      u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_SIZE];
    U4      u4_t_tim_cnt;
    U2      u2_t_tri_cnt;
    U1      u1_t_init_tmstp;

    vd_g_MemfillU1(u1_tp_nvm_tmstp, (U1)0U, (U4)OXDC_TMSTP_NVM_SIZE);
    u1_t_init_tmstp = u1_g_Nvmc_ReadOthrwithSts((U2)NVMCID_OTR_OXDC_TMSTP, (U2)OXDC_TMSTP_NVM_SIZE, u1_tp_nvm_tmstp);

    if(u1_t_init_tmstp != (U1)NVMC_STATUS_COMP){
        u2_t_tri_cnt = (U2)0U;
        u4_t_tim_cnt = (U4)0U;
        vd_s_oXdcTmstpWriteNvm(u2_t_tri_cnt, u4_t_tim_cnt);
    }
    else{
        u2_t_tri_cnt  = (U2)((U2)u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TRIC_IDX_2ND] << OXDC_TMSTP_CNT_LSB_2ND);
        u2_t_tri_cnt |= (U2)u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TRIC_IDX_1ST];

        u4_t_tim_cnt  = (U4)((U4)u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TIMC_IDX_4TH] << OXDC_TMSTP_CNT_LSB_4TH);
        u4_t_tim_cnt |= (U4)((U4)u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TIMC_IDX_3RD] << OXDC_TMSTP_CNT_LSB_3RD);
        u4_t_tim_cnt |= (U4)((U4)u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TIMC_IDX_2ND] << OXDC_TMSTP_CNT_LSB_2ND);
        u4_t_tim_cnt |= (U4)u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TIMC_IDX_1ST];
    }
    u4_s_oxdc_tmstp_timc_nvm_br   = u4_t_tim_cnt;
    u4_s_oxdc_tmstp_timc_ofst_br  = u4_t_tim_cnt;

    st_s_oxdc_tmstp_br.u4_odo     = (U4)OXDC_TMSTP_ODO_UNK;
    st_s_oxdc_tmstp_br.u2_chk     = (U2)OXDC_TMSTP_BR_UNK;
    st_s_oxdc_tmstp_br.u2_tri_cnt = u2_t_tri_cnt;
    st_s_oxdc_tmstp_br.u1_sync    = (U1)FALSE;
    st_s_oxdc_tmstp_br.u1_run     = (U1)FALSE;

    u4_s_oxdc_tmstp_odo           = (U4)OXDC_TMSTP_ODO_UNK;
    u4_s_oxdc_tmstp_tim_cnt       = u4_t_tim_cnt;
    u2_s_oxdc_tmstp_tri_cnt       = u2_t_tri_cnt;
    u1_s_oxdc_tmstp_sync          = (U1)FALSE;
    u1_s_oxdc_tmstp_run           = (U1)FALSE;

    u4_sp_oxdc_tmstp_gmt[OXDC_TMSTP_GMT_DW0] = (U4)OXDC_TMSTP_GMT_DWORD_UNK;
    u4_sp_oxdc_tmstp_gmt[OXDC_TMSTP_GMT_DW1] = (U4)OXDC_TMSTP_GMT_DWORD_UNK;
#ifdef OXDOCAN_TIME_CNT_AVAILABLE
    vd_g_DateclkEtmStart(u1_g_OXDC_TMSTP_DCT_CH, (U4)0U);
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANTmstpRstInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANTmstpRstInit(void)
{
    U4      u4_t_elpsd;

    if(st_s_oxdc_tmstp_br.u2_chk == (U2)OXDC_TMSTP_BR_LAS){

        u2_s_oxdc_tmstp_tri_cnt = st_s_oxdc_tmstp_br.u2_tri_cnt;
#ifdef OXDOCAN_TIME_CNT_AVAILABLE
        u4_t_elpsd              = u4_g_DateclkEtmElapsed(u1_g_OXDC_TMSTP_DCT_CH);
        if(((U4)U4_MAX - u4_t_elpsd) <= u4_s_oxdc_tmstp_timc_ofst_br){
            u4_s_oxdc_tmstp_tim_cnt = (u4_t_elpsd + u4_s_oxdc_tmstp_timc_ofst_br) - (U4)U4_MAX; /* unsigned integer wrapping */
        }
        else{
            u4_s_oxdc_tmstp_tim_cnt = u4_t_elpsd + u4_s_oxdc_tmstp_timc_ofst_br;
        }
#else
        u4_t_elpsd = 0;
        u4_s_oxdc_tmstp_tim_cnt = 0;
#endif /* OXDOCAN_TIME_CNT_AVAILABLE */

        if((u4_s_oxdc_tmstp_timc_nvm_br != u4_s_oxdc_tmstp_timc_ofst_br) ||
           ((u4_t_elpsd & (U4)OXDC_TMSTP_TIMC_REC_MASK) != (U4)0U       )){
#ifdef OXDOCAN_TIME_CNT_AVAILABLE
            vd_g_DateclkEtmStart(u1_g_OXDC_TMSTP_DCT_CH, (U4)0U);
#endif            
            u4_s_oxdc_tmstp_timc_ofst_br = u4_s_oxdc_tmstp_tim_cnt;
            vd_s_oXdcTmstpWriteNvm(u2_s_oxdc_tmstp_tri_cnt, u4_s_oxdc_tmstp_tim_cnt);
        }

        u4_s_oxdc_tmstp_odo  = st_s_oxdc_tmstp_br.u4_odo;
        u1_s_oxdc_tmstp_sync = (U1)FALSE;
        u1_s_oxdc_tmstp_run  = (U1)FALSE;

        u4_sp_oxdc_tmstp_gmt[OXDC_TMSTP_GMT_DW0] = (U4)OXDC_TMSTP_GMT_DWORD_UNK;
        u4_sp_oxdc_tmstp_gmt[OXDC_TMSTP_GMT_DW1] = (U4)OXDC_TMSTP_GMT_DWORD_UNK;
    }
    else{
        vd_g_oXDoCANTmstpBonInit();
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANTmstpWkupInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANTmstpWkupInit(void)
{
    U4      u4_t_elpsd;

    if(st_s_oxdc_tmstp_br.u2_chk == (U2)OXDC_TMSTP_BR_LAS){

        u2_s_oxdc_tmstp_tri_cnt = st_s_oxdc_tmstp_br.u2_tri_cnt;
#ifdef OXDOCAN_TIME_CNT_AVAILABLE        
        u4_t_elpsd              = u4_g_DateclkEtmElapsed(u1_g_OXDC_TMSTP_DCT_CH);
        if(((U4)U4_MAX - u4_t_elpsd) <= u4_s_oxdc_tmstp_timc_ofst_br){
            u4_s_oxdc_tmstp_tim_cnt = (u4_t_elpsd + u4_s_oxdc_tmstp_timc_ofst_br) - (U4)U4_MAX; /* unsigned integer wrapping */
        }
        else{
            u4_s_oxdc_tmstp_tim_cnt = u4_t_elpsd + u4_s_oxdc_tmstp_timc_ofst_br;
        }
#else
        u4_t_elpsd = 0;
        u4_s_oxdc_tmstp_tim_cnt = 0;
#endif /* OXDOCAN_TIME_CNT_AVAILABLE */
        if((u4_s_oxdc_tmstp_timc_nvm_br != u4_s_oxdc_tmstp_timc_ofst_br) ||
           ((u4_t_elpsd & (U4)OXDC_TMSTP_TIMC_REC_MASK) != (U4)0U       )){
#ifdef OXDOCAN_TIME_CNT_AVAILABLE
            vd_g_DateclkEtmStart(u1_g_OXDC_TMSTP_DCT_CH, (U4)0U);
#endif            
            u4_s_oxdc_tmstp_timc_ofst_br = u4_s_oxdc_tmstp_tim_cnt;
            vd_s_oXdcTmstpWriteNvm(u2_s_oxdc_tmstp_tri_cnt, u4_s_oxdc_tmstp_tim_cnt);
        }

        u4_s_oxdc_tmstp_odo  = st_s_oxdc_tmstp_br.u4_odo;
        u1_s_oxdc_tmstp_sync = st_s_oxdc_tmstp_br.u1_sync;
        u1_s_oxdc_tmstp_run  = st_s_oxdc_tmstp_br.u1_run;

        u4_sp_oxdc_tmstp_gmt[OXDC_TMSTP_GMT_DW0] = (U4)OXDC_TMSTP_GMT_DWORD_UNK;
        u4_sp_oxdc_tmstp_gmt[OXDC_TMSTP_GMT_DW1] = (U4)OXDC_TMSTP_GMT_DWORD_UNK;
    }
    else{
        vd_g_oXDoCANTmstpBonInit();
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANTmstpMainTask(const U2 u2_a_TSLOT, const U1 u1_a_EOM)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANTmstpMainTask(const U2 u2_a_TSLOT, const U1 u1_a_EOM)
{
    U1                        u1_t_tmstp_pow;
    U1                        u1_t_acc;

    u1_t_tmstp_pow = (U1)0U;
    if((u1_a_EOM & (U1)OXDC_EOM_IGN_ON) != (U1)0U){
        u1_t_tmstp_pow |= (U1)OXDC_TMSTP_POW_IGN_ON;
    }
    u1_t_acc = u1_g_oXDoCANTmstpCfgAccOn();
    if(u1_t_acc != (U1)0U){
        u1_t_tmstp_pow |= (U1)OXDC_TMSTP_POW_ACC_ON;
    }

    vd_s_oXdcTmstpStampUpdt(u2_a_TSLOT, u1_t_tmstp_pow);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANTmstpStaTmrwk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANTmstpStaTmrwk(void)
{
#ifdef OXDOCAN_TIME_CNT_AVAILABLE
    U4      u4_t_elpsd;

    u4_t_elpsd = u4_g_DateclkEtmElapsed(u1_g_OXDC_TMSTP_DCT_CH);
    if((u4_t_elpsd & (U4)OXDC_TMSTP_TIMC_REC_MASK) != (U4)0U){
        vd_g_DateclkEtmStart(u1_g_OXDC_TMSTP_DCT_CH, (U4)0U);
        if(((U4)U4_MAX - u4_t_elpsd) <= u4_s_oxdc_tmstp_timc_ofst_br){
            u4_s_oxdc_tmstp_timc_ofst_br = (u4_t_elpsd + u4_s_oxdc_tmstp_timc_ofst_br) - (U4)U4_MAX;    /* unsigned integer wrapping */
        }
        else{
            u4_s_oxdc_tmstp_timc_ofst_br = u4_t_elpsd + u4_s_oxdc_tmstp_timc_ofst_br;
        }
    }
#else
    u4_s_oxdc_tmstp_timc_ofst_br = 0;
#endif /* OXDOCAN_TIME_CNT_AVAILABLE */
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfTripcnt(uint8 * u1_ap_tripcnt)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANAubIfTripcnt(uint8 * u1_ap_tripcnt)
{
    /* ---------------------------------------------------------------------------------------------------- */
    /* Attention                                                                                            */
    /* ---------------------------------------------------------------------------------------------------- */
    /* Caller : ./Dem/cfg/Dem_Data_Cfg.c                                                                    */
    /*                                                                                                      */
    /* CONST( AB_83_ConstV Dem_DataElementClassType,DEM_CONFIG_DATA) Dem_DataElementClassTable[]            */
    /* Return Value  | Std_ReturnType                                                                       */
    /*               |   E_OK                                                                               */
    /*               |   E_NOT_OK                                                                           */
    /* ---------------------------------------------------------------------------------------------------- */

    if(u1_ap_tripcnt != vdp_PTR_NA){
        vd_s_oXdcTmstpTripcnt(u2_s_oxdc_tmstp_tri_cnt, u4_s_oxdc_tmstp_tim_cnt, u1_s_oxdc_tmstp_sync, &u1_ap_tripcnt[0]);
    }

    return((Std_ReturnType)E_OK);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfOdo(uint8 * u1_ap_odo)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANAubIfOdo(uint8 * u1_ap_odo)
{
    /* ---------------------------------------------------------------------------------------------------- */
    /* Attention                                                                                            */
    /* ---------------------------------------------------------------------------------------------------- */
    /* Caller : ./Dem/cfg/Dem_Data_Cfg.c                                                                    */
    /*                                                                                                      */
    /* CONST( AB_83_ConstV Dem_DataElementClassType,DEM_CONFIG_DATA) Dem_DataElementClassTable[]            */
    /* Return Value  | Std_ReturnType                                                                       */
    /*               |   E_OK                                                                               */
    /*               |   E_NOT_OK                                                                           */
    /* ---------------------------------------------------------------------------------------------------- */

    if(u1_ap_odo != vdp_PTR_NA){
        vd_s_oXdcTmstpOdo(u4_s_oxdc_tmstp_odo, &u1_ap_odo[0]);
    }

    return((Std_ReturnType)E_OK);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfGmt(uint8 * u1_ap_gmt)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANAubIfGmt(uint8 * u1_ap_gmt)
{
    /* ---------------------------------------------------------------------------------------------------- */
    /* Attention                                                                                            */
    /* ---------------------------------------------------------------------------------------------------- */
    /* Caller : ./Dem/cfg/Dem_Data_Cfg.c                                                                    */
    /*                                                                                                      */
    /* CONST( AB_83_ConstV Dem_DataElementClassType,DEM_CONFIG_DATA) Dem_DataElementClassTable[]            */
    /* Return Value  | Std_ReturnType                                                                       */
    /*               |   E_OK                                                                               */
    /*               |   E_NOT_OK                                                                           */
    /* ---------------------------------------------------------------------------------------------------- */

    U1 *                      u1_tp_src;
    U1 *                      u1_tp_dst;

    U4                        u4_t_lpcnt;

    if(u1_ap_gmt != vdp_PTR_NA){

        u1_tp_src = (U1 *)&u4_sp_oxdc_tmstp_gmt[0];
        u1_tp_dst = &u1_ap_gmt[0];
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXDC_DATA_REA_ANS_NB_A002; u4_t_lpcnt++){
            u1_tp_dst[u4_t_lpcnt] = u1_tp_src[u4_t_lpcnt];
        }
    }

    return((Std_ReturnType)E_OK);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_A800(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_A800(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    vd_s_oXdcTmstpTripcnt(u2_s_oxdc_tmstp_tri_cnt, u4_s_oxdc_tmstp_tim_cnt, u1_s_oxdc_tmstp_sync, u1_ap_ans);
    return((U1)OXDC_SAL_PROC_FIN);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_A003(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_A003(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    vd_s_oXdcTmstpOdo(u4_s_oxdc_tmstp_odo, u1_ap_ans);
    return((U1)OXDC_SAL_PROC_FIN);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_A002(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_A002(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    U4                        u4_t_lpcnt;
    U1 *                      u1_tp_bcd;

    u1_tp_bcd = (U1 *)&u4_sp_oxdc_tmstp_gmt[0];
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXDC_TMSTP_GMT_NUM; u4_t_lpcnt++){
        u1_ap_ans[u4_t_lpcnt] = u1_tp_bcd[u4_t_lpcnt];
    }

    return((U1)OXDC_SAL_PROC_FIN);
}
/*===================================================================================================================================*/
/*  U2      u2_g_oXDoCANTmstpTripcnt(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U2      u2_g_oXDoCANTmstpTripcnt(void)
{
    return(u2_s_oxdc_tmstp_tri_cnt);
}
/*===================================================================================================================================*/
/*  U4      u4_g_oXDoCANTmstpTimecnt(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U4      u4_g_oXDoCANTmstpTimecnt(void)
{
    return(u4_s_oxdc_tmstp_tim_cnt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANTmstpTripSync(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANTmstpTripSync(void)
{
    return(u1_s_oxdc_tmstp_sync);
}
/*===================================================================================================================================*/
/*  U4      u4_g_oXDoCANTmstpOdo(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U4      u4_g_oXDoCANTmstpOdo(void)
{
    return(u4_s_oxdc_tmstp_odo);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANTmstpGmt(U1 * u1_ap_gmt, const U4 u4_a_size)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
void    vd_g_oXDoCANTmstpGmt(U1 * u1_ap_gmt, const U4 u4_a_size)
{
    U1 *                      u1_tp_bcd;

    u1_tp_bcd = (U1 *)&u4_sp_oxdc_tmstp_gmt[0];

    if(u4_a_size >= (U4)OXDC_TMSTP_GMT_NUM){
        u1_ap_gmt[OXDC_TMSTP_GMT_IDX_YE] = u1_tp_bcd[OXDC_TMSTP_GMT_IDX_YE];
        u1_ap_gmt[OXDC_TMSTP_GMT_IDX_MO] = u1_tp_bcd[OXDC_TMSTP_GMT_IDX_MO];
        u1_ap_gmt[OXDC_TMSTP_GMT_IDX_DA] = u1_tp_bcd[OXDC_TMSTP_GMT_IDX_DA];
        u1_ap_gmt[OXDC_TMSTP_GMT_IDX_HO] = u1_tp_bcd[OXDC_TMSTP_GMT_IDX_HO];
        u1_ap_gmt[OXDC_TMSTP_GMT_IDX_MI] = u1_tp_bcd[OXDC_TMSTP_GMT_IDX_MI];
        u1_ap_gmt[OXDC_TMSTP_GMT_IDX_SE] = u1_tp_bcd[OXDC_TMSTP_GMT_IDX_SE];
    }
}
/*  static void    vd_s_oXdcTmstpStampUpdt(const U2 u2_a_TSLOT, const U1 u1_a_TMSTP_POW)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcTmstpStampUpdt(const U2 u2_a_TSLOT, const U1 u1_a_TMSTP_POW)
{
    U4                        u4_t_odo_0p1km;
    U1                        u1_t_pow_evt;

    vd_s_oXdcTmstpTripUpdt();

    u1_t_pow_evt  = (U1)FALSE;

    if(u1_a_TMSTP_POW != (U1)0U){
        if(u1_s_oxdc_tmstp_run == (U1)FALSE){
            u1_t_pow_evt = (U1)TRUE;
        }
        u1_s_oxdc_tmstp_run = (U1)TRUE;
    }
    else{
        if(u1_s_oxdc_tmstp_run != (U1)FALSE){
            u1_t_pow_evt = (U1)TRUE;
        }
        u1_s_oxdc_tmstp_run = (U1)FALSE;
    }

    if((u2_a_TSLOT   == (U2)OXDC_TSLOT_BIT_0) ||
       (u1_t_pow_evt == (U1)TRUE            )){

        u4_t_odo_0p1km = (U4)OXDC_TMSTP_ODO_UNK;
        vd_g_oXDoCANTmstpCfgOdoRx(&u4_t_odo_0p1km);
        u4_s_oxdc_tmstp_odo = u4_t_odo_0p1km;
        vd_s_oXdcTmstpGmtUpdt();
    }

    st_s_oxdc_tmstp_br.u2_chk     = (U2)OXDC_TMSTP_BR_UNK;
    st_s_oxdc_tmstp_br.u4_odo     = u4_s_oxdc_tmstp_odo;
    st_s_oxdc_tmstp_br.u2_tri_cnt = u2_s_oxdc_tmstp_tri_cnt;
    st_s_oxdc_tmstp_br.u1_sync    = u1_s_oxdc_tmstp_sync;
    st_s_oxdc_tmstp_br.u1_run     = u1_s_oxdc_tmstp_run;
    st_s_oxdc_tmstp_br.u2_chk     = (U2)OXDC_TMSTP_BR_LAS;
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcTmstpTripUpdt(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcTmstpTripUpdt(void)
{
    U4      u4_t_elpsd;
    U2      u2_t_tric_rx;
    U1      u1_t_tri_updt;

    u1_t_tri_updt = (U1)FALSE;

    u2_t_tric_rx = u2_g_oXDoCANTmstpCfgTricRx();
    if(u2_t_tric_rx < (U2)OXDC_TMSTP_TRIC_UNK){
        u1_s_oxdc_tmstp_sync = (U1)TRUE;
        if(u2_s_oxdc_tmstp_tri_cnt != u2_t_tric_rx){
#ifdef OXDOCAN_TIME_CNT_AVAILABLE
            vd_g_DateclkEtmStart(u1_g_OXDC_TMSTP_DCT_CH, (U4)0U);
#endif            
            u2_s_oxdc_tmstp_tri_cnt      = u2_t_tric_rx;
            u4_s_oxdc_tmstp_tim_cnt      = (U4)0U;
            u4_s_oxdc_tmstp_timc_ofst_br = (U4)0U;
            vd_s_oXdcTmstpWriteNvm(u2_t_tric_rx, (U4)0U);
            u1_t_tri_updt = (U1)TRUE;
        }
    }
    else{
        u1_s_oxdc_tmstp_sync = (U1)FALSE;
    }

    if(u1_t_tri_updt == (U1)FALSE){
#ifdef OXDOCAN_TIME_CNT_AVAILABLE        
        u4_t_elpsd = u4_g_DateclkEtmElapsed(u1_g_OXDC_TMSTP_DCT_CH);
        if(((U4)U4_MAX - u4_t_elpsd) <= u4_s_oxdc_tmstp_timc_ofst_br){
            u4_s_oxdc_tmstp_tim_cnt = (u4_t_elpsd + u4_s_oxdc_tmstp_timc_ofst_br) - (U4)U4_MAX; /* unsigned integer wrapping */
        }
        else{
            u4_s_oxdc_tmstp_tim_cnt = u4_t_elpsd + u4_s_oxdc_tmstp_timc_ofst_br;
        }
#else
        u4_t_elpsd = 0;
        u4_s_oxdc_tmstp_tim_cnt = 0;
#endif /* OXDOCAN_TIME_CNT_AVAILABLE */
        if((u4_t_elpsd & (U4)OXDC_TMSTP_TIMC_REC_MASK) != (U4)0U){
#ifdef OXDOCAN_TIME_CNT_AVAILABLE            
            vd_g_DateclkEtmStart(u1_g_OXDC_TMSTP_DCT_CH, (U4)0U);
#endif            
            u4_s_oxdc_tmstp_timc_ofst_br = u4_s_oxdc_tmstp_tim_cnt;
            vd_s_oXdcTmstpWriteNvm(u2_s_oxdc_tmstp_tri_cnt, u4_s_oxdc_tmstp_tim_cnt);
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcTmstpGmtUpdt(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcTmstpGmtUpdt(void)
{
    U1 *                      u1_tp_bcd;
    U4                        u4_t_lpcnt;
    U4                        u4_t_int;

    U1                        u1_t_rx_chk;

    u1_tp_bcd   = (U1 *)&u4_sp_oxdc_tmstp_gmt[0];
    u1_t_rx_chk = u1_g_oXDoCANTmstpCfgGmtRx(u1_tp_bcd);
    if(u1_t_rx_chk == (U1)TRUE){

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXDC_TMSTP_GMT_NUM; u4_t_lpcnt++){
            u4_t_int = u4_g_BcdToInt((U4)u1_tp_bcd[u4_t_lpcnt]);
            if((u4_t_int >= (U4)st_sp_OXDC_TMSTP_GMT[u4_t_lpcnt].u1_min) &&
               (u4_t_int <= (U4)st_sp_OXDC_TMSTP_GMT[u4_t_lpcnt].u1_max)){
                /* Do Nothing */
            }
            else{
                u1_t_rx_chk = (U1)FALSE; 
                break;
            }
        }
    }

    if(u1_t_rx_chk != (U1)TRUE){
        u4_sp_oxdc_tmstp_gmt[OXDC_TMSTP_GMT_DW0] = (U4)OXDC_TMSTP_GMT_DWORD_UNK;
        u4_sp_oxdc_tmstp_gmt[OXDC_TMSTP_GMT_DW1] = (U4)OXDC_TMSTP_GMT_DWORD_UNK;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcTmstpTripcnt(const U2 u2_a_TRI_CNT, const U4 u4_a_TIM_CNT, const U1 u1_a_SYNC, U1 * u1_ap_ans)           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcTmstpTripcnt(const U2 u2_a_TRI_CNT, const U4 u4_a_TIM_CNT, const U1 u1_a_SYNC, U1 * u1_ap_ans)
{
    u1_ap_ans[OXDC_TMSTP_TRIC_IDX_2ND] = (U1)(u2_a_TRI_CNT >> OXDC_TMSTP_CNT_LSB_2ND);
    u1_ap_ans[OXDC_TMSTP_TRIC_IDX_1ST] = (U1)u2_a_TRI_CNT;

    u1_ap_ans[OXDC_TMSTP_TIMC_IDX_4TH] = (U1)(u4_a_TIM_CNT >> OXDC_TMSTP_CNT_LSB_4TH);
    u1_ap_ans[OXDC_TMSTP_TIMC_IDX_3RD] = (U1)(u4_a_TIM_CNT >> OXDC_TMSTP_CNT_LSB_3RD);
    u1_ap_ans[OXDC_TMSTP_TIMC_IDX_2ND] = (U1)(u4_a_TIM_CNT >> OXDC_TMSTP_CNT_LSB_2ND);
    u1_ap_ans[OXDC_TMSTP_TIMC_IDX_1ST] = (U1)u4_a_TIM_CNT;
    u1_ap_ans[OXDC_TMSTP_SYNC_IDX]     = (U1)u1_a_SYNC;
 }
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcTmstpOdo(const U4 u4_a_ODO, U1 * u1_ap_ans)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcTmstpOdo(const U4 u4_a_ODO, U1 * u1_ap_ans)
{
    if(u4_a_ODO != (U4)OXDC_TMSTP_ODO_UNK){
        u1_ap_ans[OXDC_TMSTP_ODO_IDX_4TH] = (U1)(u4_a_ODO >> OXDC_TMSTP_ODO_ANS_LSB_4TH);
        u1_ap_ans[OXDC_TMSTP_ODO_IDX_3RD] = (U1)(u4_a_ODO >> OXDC_TMSTP_ODO_ANS_LSB_3RD);
        u1_ap_ans[OXDC_TMSTP_ODO_IDX_2ND] = (U1)(u4_a_ODO >> OXDC_TMSTP_ODO_ANS_LSB_2ND);
        u1_ap_ans[OXDC_TMSTP_ODO_IDX_1ST] = (U1)u4_a_ODO;
    }
    else{
        u1_ap_ans[OXDC_TMSTP_ODO_IDX_4TH] = (U1)0U;
        u1_ap_ans[OXDC_TMSTP_ODO_IDX_3RD] = (U1)0U;
        u1_ap_ans[OXDC_TMSTP_ODO_IDX_2ND] = (U1)0U;
        u1_ap_ans[OXDC_TMSTP_ODO_IDX_1ST] = (U1)0U;
    }
}
/*===================================================================================================================================*/
/*  static void     vd_s_oXdcTmstpWriteNvm(const U2 u2_a_TRI_CNT, const U4 u4_a_TIM_CNT)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_oXdcTmstpWriteNvm(const U2 u2_a_TRI_CNT, const U4 u4_a_TIM_CNT)
{
    U1      u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_SIZE];

    vd_g_MemfillU1(u1_tp_nvm_tmstp, (U1)0U, (U4)OXDC_TMSTP_NVM_SIZE);
    u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TRIC_IDX_2ND] = (U1)(u2_a_TRI_CNT >> OXDC_TMSTP_CNT_LSB_2ND);
    u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TRIC_IDX_1ST] = (U1)(u2_a_TRI_CNT);
    u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TIMC_IDX_4TH] = (U1)(u4_a_TIM_CNT >> OXDC_TMSTP_CNT_LSB_4TH);
    u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TIMC_IDX_3RD] = (U1)(u4_a_TIM_CNT >> OXDC_TMSTP_CNT_LSB_3RD);
    u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TIMC_IDX_2ND] = (U1)(u4_a_TIM_CNT >> OXDC_TMSTP_CNT_LSB_2ND);
    u1_tp_nvm_tmstp[OXDC_TMSTP_NVM_TIMC_IDX_1ST] = (U1)(u4_a_TIM_CNT);

    vd_g_Nvmc_WriteOthr((U2)NVMCID_OTR_OXDC_TMSTP, (U2)OXDC_TMSTP_NVM_SIZE, u1_tp_nvm_tmstp);

    u4_s_oxdc_tmstp_timc_nvm_br = u4_a_TIM_CNT;
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
/*                                Update to support Phase6 TimeStamp. (DID:A800, A002, A003)                                         */
/*  1.0.1     1/23/2024  TI       u1_g_oXDoCANAubIfxxx : Switched arguments according to DEM_READFUNC_MONITORDATA_SUPPORT            */
/*  1.0.2     2/19/2024  TI       Supported timer count up during ECU sleep.                                                         */
/*  1.0.3     4/15/2024  TI       Changed to perform Odo unit conversion processing on the app side.                                 */
/*  1.0.4     7/04/2024  TI       Changed to receive TRIP_CNT even when IG/ACC OFF. Fixed tim_cnt max value.                         */
/*                                                                                                                                   */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
