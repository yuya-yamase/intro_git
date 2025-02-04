/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN MET XID Configuration                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_MET_XID_CFG_C_MAJOR              (1)
#define TYDOCAN_MET_XID_CFG_C_MINOR              (1)
#define TYDOCAN_MET_XID_CFG_C_PATCH              (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "tydocan_sal.h"
#include "oxdocan_saif.h"

#include "tydocan_met_xid_cfg_private.h"
#if 0 /*Phase6Diag Stub*/
#include "tydocan_rob_F007.h"
#endif
/*Phase6Diag Stub*/
#include "tydocan_ssr_channel.h"
#include "memfill_u1.h"
#include "memcpy_u1.h"

#include "iohw_adc.h"
#include "veh_opemd.h"

#include "unitconvrt.h"
#include "odo_km.h"

#include "fuelvol_dsif.h"

#include "lcom_spi_dsal.h"

#include "vardef.h"
#include "product.h"

#include "rim_ctl.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TYDOCAN_MET_XID_CFG_C_MAJOR != TYDOCAN_MET_XID_CFG_H_MAJOR) || \
     (TYDOCAN_MET_XID_CFG_C_MINOR != TYDOCAN_MET_XID_CFG_H_MINOR) || \
     (TYDOCAN_MET_XID_CFG_C_PATCH != TYDOCAN_MET_XID_CFG_H_PATCH))
#error "tydocan_met_xid_cfg.c and tydocan_met_xid_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_OM_100_MI                           (100000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_SOFT_N_NUM_SLV                      (1U)       /* The number of Slave Part Number */
#define TYDC_SOFT_N_SLV_ID_1                     (0x01U)    /* Slave Part ID No.1 */

#define TYDC_SOFT_N_BO_D1_SLV                    (1U)
#define TYDC_SOFT_N_BO_SLV_HUD                   (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_LOG_SIZE_2BYTE                      (2U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_TydcProduct_ECU_PN(U1 * u1_ap_ans);
static U1      u1_s_TydcProduct_SOFT_N(U1 * u1_ap_ans);
static U1      u1_s_TydcProduct_SERI_N(U1 * u1_ap_ans);
static U1      u1_s_TydcProduct_HUD_N(U1 * u1_ap_ans);
static U1      u1_s_TyDoCANXidSup_Hud_Pub(void);
static U1      u1_s_TyDoCANXidSup_Hud_Pri(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef OXDC_DATA_REA_ANS_NB_10A1
const U1    u1_g_TYDC_SSR_CH_22_10A1 = (U1)TYDC_SSR_CH_22_10A1;      /* DID 0x10A1 */
#endif /* #ifdef OXDC_DATA_REA_ANS_NB_10A1 */

#ifdef OXDC_DATA_REA_ANS_NB_10A2
const U1    u1_g_TYDC_SSR_CH_22_10A2 = (U1)TYDC_SSR_CH_22_10A2;      /* DID 0x10A2 */
#endif /* #ifdef OXDC_DATA_REA_ANS_NB_10A2 */

#ifdef OXDC_DATA_REA_ANS_NB_10A3
const U1    u1_g_TYDC_SSR_CH_22_10A3 = (U1)TYDC_SSR_CH_22_10A3;      /* DID 0x10A3 */
#endif /* #ifdef OXDC_DATA_REA_ANS_NB_10A3 */

#ifdef OXDC_DATA_REA_ANS_NB_10AB
const U1    u1_g_TYDC_SSR_CH_22_10AB = (U1)TYDC_SSR_CH_22_10AB;      /* DID 0x10AB */
#endif /* #ifdef OXDC_DATA_REA_ANS_NB_10AB */

#ifdef OXDC_DATA_REA_ANS_NB_10AD
const U1    u1_g_TYDC_SSR_CH_22_10AD = (U1)TYDC_SSR_CH_22_10AD;      /* DID 0x10AD */
#endif /* #ifdef OXDC_DATA_REA_ANS_NB_10AB */

#define TYDC_10A7_RIM_NB        (OXDC_DATA_REA_ANS_NB_10A7 / TYDC_LOG_SIZE_2BYTE)
static const U2 u2_sp_TYDC_10A7_RIMID[TYDC_10A7_RIM_NB] = {
    (U2)RIMID_U2_DS_22_10A7_MM_HUD_ONOFF  ,    (U2)RIMID_U2_DS_22_10A7_VR_HUD_ONOFF  ,
    (U2)RIMID_U2_DS_22_10A7_MM_HUD_DIM    ,    (U2)RIMID_U2_DS_22_10A7_MM_HUD_ROT    ,
    (U2)RIMID_U2_DS_22_10A7_MM_HUD_POS    ,    (U2)RIMID_U2_DS_22_10A7_MM_HUD_DSP    ,
    (U2)RIMID_U2_DS_22_10A7_MM_MET_TYPE   ,    (U2)RIMID_U2_DS_22_10A7_MM_MET_TACHO  ,
    (U2)RIMID_U2_DS_22_10A7_MM_MET_DIM    ,    (U2)RIMID_U2_DS_22_10A7_MM_MET_DSP    ,
    (U2)RIMID_U2_DS_22_10A7_MM_IND_ECO    ,    (U2)RIMID_U2_DS_22_10A7_MM_IND_EV     ,
    (U2)RIMID_U2_DS_22_10A7_MM_IND_REVIND ,    (U2)RIMID_U2_DS_22_10A7_MM_IND_REVSET ,
    (U2)RIMID_U2_DS_22_10A7_MM_IND_REVPEK ,    (U2)RIMID_U2_DS_22_10A7_MM_FACT_INIT  ,
    (U2)RIMID_U2_DS_22_10A7_MET_ODO_SHORT ,    (U2)RIMID_U2_DS_22_10A7_MET_ODO_LONG  ,
    (U2)RIMID_U2_DS_22_10A7_VR_ODO        ,    (U2)RIMID_U2_DS_22_10A7_VR_TRIP_A     ,
    (U2)RIMID_U2_DS_22_10A7_VR_TRIP_B     ,    (U2)RIMID_U2_DS_22_10A7_MM_MET_DESIGN ,
    (U2)RIMID_U2_DS_22_10A7_MM_ANALOG_MET ,    (U2)RIMID_U2_DS_22_10A7_MM_FUEL_FLG   ,
    (U2)RIMID_U2_DS_22_10A7_MM_ELEC_FLG   ,    (U2)RIMID_U2_DS_22_10A7_MM_ENG_MONI   ,
    (U2)RIMID_U2_DS_22_10A7_MM_DRVINF_CALC,    (U2)RIMID_U2_DS_22_10A7_MM_DRVINF_ITEM,
    (U2)RIMID_U2_DS_22_10A7_MM_POP_CROSS  ,    (U2)RIMID_U2_DS_22_10A7_MM_POP_TEL    ,
    (U2)RIMID_U2_DS_22_10A7_MM_POP_AUDIO  ,    (U2)RIMID_U2_DS_22_10A7_MM_POP_VOLUME ,
    (U2)RIMID_U2_DS_22_10A7_MM_POP_VOICE  ,    (U2)RIMID_U2_DS_22_10A7_MM_POP_TIME   ,
    (U2)RIMID_U2_DS_22_10A7_MM_POP_NOTIFY ,    (U2)U2_MAX                            ,
    (U2)RIMID_U2_DS_22_10A7_MM_POP_DIM    ,    (U2)RIMID_U2_DS_22_10A7_MM_HV_IND     ,
    (U2)RIMID_U2_DS_22_10A7_MM_MET_TRIP_A ,    (U2)RIMID_U2_DS_22_10A7_MM_MET_TRIP_B ,
    (U2)RIMID_U2_DS_22_10A7_MM_MET_TIMING ,    (U2)RIMID_U2_DS_22_10A7_MM_MET_LAYOUT ,
    (U2)RIMID_U2_DS_22_10A7_MM_EV_DRVINF  ,    (U2)RIMID_U2_DS_22_10A7_MM_4WD_AWD    ,
    (U2)U2_MAX                            ,    (U2)U2_MAX                            ,
    (U2)U2_MAX                            ,    (U2)U2_MAX
};

static const ST_TYDC_LOG_RAM st_sp_TYDC_LOG_RAM[TYDC_NUM_LOGRAM] = {
    /* u2p_RIMID,                       u1_nb                */
    { &u2_sp_TYDC_10A7_RIMID[0],        (U1)TYDC_10A7_RIM_NB }, /* 10A7 */
    { vdp_PTR_NA,                       (U1)0U               }  /* 10A9 */
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/


#ifdef OXDC_DATA_REA_ANS_NB_12A1


/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_OmMI(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_OmMI(void)
{
    return((U1)OXDC_XID_SUP_PUB);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANOmMI(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANOmMI(void)
{
    U4                     u4_t_om_0p001;
    U1                     u1_t_sts_chk;
    U1                     u1_t_om_mi;

    u4_t_om_0p001 = (U4)0U;
    u1_t_sts_chk  = u1_g_OdoTripKm((U1)ODO_TRIP_CH_OM, &u4_t_om_0p001);
    if(u1_t_sts_chk != (U1)ODO_STSBIT_VALID){
        u1_t_om_mi = (U1)TYDC_OM_MI_UNK;
    }
    else{
        u4_t_om_0p001 = u4_g_UnitconvtrKmtoMi(u4_t_om_0p001) / (U4)TYDC_OM_100_MI;
        if(u4_t_om_0p001 >= (U4)TYDC_OM_MI_MAX){
            u1_t_om_mi = (U1)TYDC_OM_MI_MAX;
        }
        else{
            u1_t_om_mi = (U1)u4_t_om_0p001;
        }
    }

    return(u1_t_om_mi);
}
/*===================================================================================================================================*/


#endif /* #ifdef OXDC_DATA_REA_ANS_NB_12A1 */


/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANXidSup_Pts(const U1 u1_a_XID)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANXidSup_Pts(const U1 u1_a_XID)
{
    return((U1)OXDC_XID_SUP_PUB);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANXidSup_MpxSw(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANXidSup_MpxSw(void)
{
    return((U1)FALSE);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANXidSup_Fuel(const U1 u1_a_XID)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANXidSup_Fuel(const U1 u1_a_CH)
{
#if ((TYDC_FUEL_CH_MA != FUEL_VOL_FS_CH_MA) || \
     (TYDC_FUEL_CH_SU != FUEL_VOL_FS_CH_SU))
#error "tydocan_met_xid_cfg.c : FUEL_VOL_FS_CH_XX shall be equal to TYDC_FUEL_CH_XX."
#endif
#if ((TYDC_FUEL_EVC_SS_LIT    != FUEL_VOL_EVC_SS_LIT    ) || \
     (TYDC_FUEL_EVC_SS_VEU    != FUEL_VOL_EVC_SS_VEU    ) || \
     (TYDC_FUEL_EVC_LIT_BFR_L != FUEL_VOL_EVC_LIT_BFR_L ) || \
     (TYDC_FUEL_EVC_LIT_BFR_H != FUEL_VOL_EVC_LIT_BFR_H ) || \
     (TYDC_FUEL_EVC_LIT_AFT_L != FUEL_VOL_EVC_LIT_AFT_L ) || \
     (TYDC_FUEL_EVC_LIT_AFT_H != FUEL_VOL_EVC_LIT_AFT_H ))
#error "tydocan_met_xid_cfg : FUEL_VOL_EVC_XXX shall be equal to TYDC_FUEL_EVC_XXX."
#endif
    return(u1_g_FuelvolDs22SupFsByCh((U2)u1_a_CH));
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TyDoCANXidSup_Hud_Pub(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TyDoCANXidSup_Hud_Pub(void)
{
    U1 u1_t_hud;
    U1 u1_t_sup;

    u1_t_hud = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2);

    if(u1_t_hud == (U1)TRUE){
        u1_t_sup = (U1)OXDC_XID_SUP_PUB;
    }
    else{
        u1_t_sup = (U1)OXDC_XID_SUP_NOT;
    }

    return(u1_t_sup);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TyDoCANXidSup_Hud_Pri(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TyDoCANXidSup_Hud_Pri(void)
{
    U1 u1_t_hud;
    U1 u1_t_sup;

    u1_t_hud = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2);

    if(u1_t_hud == (U1)TRUE){
        u1_t_sup = (U1)OXDC_XID_SUP_PRI;
    }
    else{
        u1_t_sup = (U1)OXDC_XID_SUP_NOT;
    }

    return(u1_t_sup);
}
/*===================================================================================================================================*/
/*  U2      u2_g_TyDoCANFuelLit32(const U1 u1_a_CH)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_TyDoCANFuelLit32(const U1 u1_a_CH)
{
    return(u2_g_FuelvolDs22LitAvg32(u1_a_CH));
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANTrchkFuel(const U1 u1_a_CH)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANTrchkFuel(const U1 u1_a_CH)
{
#if ((OXDC_DTC_TR_INA != FUEL_VOL_OSC_INA) || \
     (OXDC_DTC_TR_ACT != FUEL_VOL_OSC_ACT) || \
     (OXDC_DTC_TR_UNK != FUEL_VOL_OSC_UNK))
#error "tydocan_met_xid_cfg : FUEL_VOL_OSC_XXX shall be equal to TYDC_DTC_TR_XXX."
#endif
    return(u1_g_FuelvolDtcOscRslt(u1_a_CH));
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANProductNum(U1 * u1_ap_ans, const U1 u1_a_PN)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANProductNum(U1 * u1_ap_ans, const U1 u1_a_PN)
{
    static U1 ( * const    fp_u1_TYDC_PN[])(U1 * u1_ap_ans) = {
        &u1_s_TydcProduct_ECU_PN,
        &u1_s_TydcProduct_SOFT_N,
        &u1_s_TydcProduct_SERI_N,
        &u1_s_TydcProduct_HUD_N
    };

    U1                     u1_t_proc;

    if(u1_a_PN > (U1)TYDC_PN_0107){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }
    else{
        u1_t_proc = (*fp_u1_TYDC_PN[u1_a_PN])(u1_ap_ans);
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANPwrVol(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANPwrVol(void)
{
    static const U2        u2_s_TYDC_PWR_VOL_ADC_MAX = (U2)0x03ffU;
    static const U2        u2_s_TYDC_PWR_VOL_MUL     = (U2)401U;
    static const U2        u2_s_TYDC_PWR_VOL_DIV     = (U2)2046U;

    U4                     u4_t_vol;
    U2                     u2_t_adc;

    u2_t_adc = u2_g_IoHwAdcLv((U1)ADC_CH_IG_MON);
    if(u2_t_adc <= u2_s_TYDC_PWR_VOL_ADC_MAX){

        u4_t_vol = ((U4)u2_t_adc * (U4)u2_s_TYDC_PWR_VOL_MUL) / (U4)u2_s_TYDC_PWR_VOL_DIV;
        if(u4_t_vol > (U4)TYDC_PWR_VOL_UNK) {
            u4_t_vol = (U4)TYDC_PWR_VOL_UNK;
        }
    }
    else{
        u4_t_vol = (U4)TYDC_PWR_VOL_UNK;
    }

    return((U1)u4_t_vol);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANTesMd32(U4 * u4_ap_b32)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANTesMd32(U4 * u4_ap_b32)
{
    U2                     u2_t_tes_md_sup;
    U2                     u2_t_tm16;
    U1                     u1_t_rim_chk;
    U1                     u1_t_ok;
    U1                     u1_t_acc_sup;
    U1                     u1_t_dun_sup;

    u2_t_tes_md_sup = (U2)TYDC_TES_MD_BIT_VSW;
    u2_t_tm16    = (U2)0U;
    u1_t_rim_chk = u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_TYDC_WRBYID_AA00, &u2_t_tm16) & (U1)RIM_RESULT_KIND_MASK;

    u1_t_acc_sup = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_SW_AC100V_TESTMODE);
    if(u1_t_acc_sup != (U1)FALSE){
        u2_t_tes_md_sup |= (U2)TYDC_TES_MD_BIT_ACC;
    }

    u1_t_dun_sup = u1_g_VardefUnitSlctTypeByPid();
    if((u1_t_dun_sup == (U1)VDF_UNIT_TYPE_A) || (u1_t_dun_sup == (U1)VDF_UNIT_TYPE_B) || (u1_t_dun_sup == (U1)VDF_UNIT_TYPE_D) ||
       (u1_t_dun_sup == (U1)VDF_UNIT_TYPE_E) || (u1_t_dun_sup == (U1)VDF_UNIT_TYPE_H) || (u1_t_dun_sup == (U1)VDF_UNIT_TYPE_I) ||
       (u1_t_dun_sup == (U1)VDF_UNIT_TYPE_J)){
        u2_t_tes_md_sup |= (U2)TYDC_TES_MD_BIT_DUN;
    }

    if(u1_t_rim_chk == (U1)RIM_RESULT_KIND_OK){

        u4_ap_b32[TYDC_B32_WO_SU] = (U4)u2_t_tes_md_sup;
        u4_ap_b32[TYDC_B32_WO_LA] = (U4)u2_t_tm16 & (U4)u2_t_tes_md_sup;

        u1_t_ok = (U1)TRUE;
    }
    else{
        u1_t_ok = (U1)FALSE;
    }

    return(u1_t_ok);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANTesMdNext(const U4 u4_a_B32)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANTesMdNext(const U4 u4_a_B32)
{
    U1                     u1_t_ok;

    u1_t_ok = u1_g_VehopemdIgnOn();
    if(u1_t_ok == (U1)TRUE){
        vd_g_Rim_WriteU2((U2)RIMID_U2_TYDC_WRBYID_AA00, (U2)u4_a_B32);
    }

    return(u1_t_ok);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANTesMdCancel(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANTesMdCancel(void)
{
    vd_g_Rim_WriteU2((U2)RIMID_U2_TYDC_WRBYID_AA00, (U2)0x0000U);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANEsoReset(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANEsoReset(void)
{
    vd_g_TyDoCANDtcUnlock((U4)OXDC_DTC_KEY_UNLOCK);
    vd_g_TyDoCANDtcLogRxReset();

    (void)u1_g_VardefEsOptReset((U1)TRUE);
    (void)vd_g_VardefPtsRxReset();
    vd_g_VardefPtsRxMilreqReset();

    vd_g_LComSpiDsrUnlock((U4)LCOM_SPI_DSR_UNLOCK);
    vd_g_LComSpiDsrTx((U1)LCOM_SPI_DSR_31_ESO, (U4)LCOM_SPI_ESO_RES_RUN);

    vd_g_VardefMmMthdReset();
    vd_g_VardefHcsRxReset();
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANLogRAM(U1 * u1_ap_ans, const U1 u1_a_DID)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANLogRAM(U1 * u1_ap_ans, const U1 u1_a_DID)
{
    const U2 *    u2_tp_tbl;
    U1            u1_t_nb;

    U4      u4_t_lpcnt;
    U2      u2_t_rm;
    U1      u1_t_idx;

    u2_tp_tbl = st_sp_TYDC_LOG_RAM[u1_a_DID].u2p_RIMID;
    u1_t_nb   = st_sp_TYDC_LOG_RAM[u1_a_DID].u1_nb;

    if((u2_tp_tbl != vdp_PTR_NA) &&
       (u1_t_nb   != (U1)0U    )){

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_t_nb; u4_t_lpcnt++){
            u2_t_rm = (U2)0U;
            (void)u1_g_Rim_ReadU2withStatus(u2_tp_tbl[u4_t_lpcnt], &u2_t_rm);

            u1_t_idx = (U1)(u4_t_lpcnt * (U1)TYDC_LOG_SIZE_2BYTE);
            u1_ap_ans[u1_t_idx         ] = (U1)(u2_t_rm >> 8        );
            u1_ap_ans[u1_t_idx + (U4)1U] = (U1)(u2_t_rm & (U2)U1_MAX);
        }
    }

    return((U1)OXDC_SAL_PROC_FIN);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANLogRAMReset(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANLogRAMReset(void)
{
    const U2 *    u2_tp_tbl;
    U1            u1_t_nb;

    U4      u4_t_ch;
    U4      u4_t_nb;

    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)TYDC_NUM_LOGRAM; u4_t_ch++){

        u2_tp_tbl = st_sp_TYDC_LOG_RAM[u4_t_ch].u2p_RIMID;
        u1_t_nb   = st_sp_TYDC_LOG_RAM[u4_t_ch].u1_nb;

        if((u2_tp_tbl != vdp_PTR_NA) ||
           (u1_t_nb   != (U1)0U    )){

            for(u4_t_nb = (U4)0U; u4_t_nb < (U4)u1_t_nb; u4_t_nb++){
                vd_g_Rim_WriteU2(u2_tp_tbl[u4_t_nb], (U2)0U);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcProduct_ECU_PN(U1 * u1_ap_ans)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcProduct_ECU_PN(U1 * u1_ap_ans)
{
#if 0/*Phase6Diag Stub*/
    U1                     u1_tp_pn_tx[OXDC_DATA_REA_ANS_NB_0105];
    U1                     u1_t_pn_chk;
    U1                     u1_t_proc;

    u1_tp_pn_tx[TYDC_ECU_PN_BO_AZ_0] = (U1)TYDC_ECU_MINOR; /* 0 */
    u1_tp_pn_tx[TYDC_ECU_PN_BO_AZ_1] = (U1)TYDC_ECU_MINOR; /* 0 */

    u1_t_pn_chk = u1_g_Product((U1)PRDCT_PN_ECU_PN, &u1_tp_pn_tx[0], (U1)PRDCT_ECU_PN_NBYTE);
    if(u1_t_pn_chk == (U1)TRUE){

        vd_g_MemcpyU1(u1_ap_ans, &u1_tp_pn_tx[0], (U4)OXDC_DATA_REA_ANS_NB_0105);

        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
    }

    return(u1_t_proc);
#else
    return((U1)OXDC_SAL_PROC_FIN);
#endif
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcProduct_SOFT_N(U1 * u1_ap_ans)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcProduct_SOFT_N(U1 * u1_ap_ans)
{
#if 0/*Phase6Diag Stub*/
    U1                     u1_tp_pn_tx[OXDC_DATA_REA_ANS_NB_F181];
    U1                     u1_t_pn_chk;
    U1                     u1_t_proc;

    u1_tp_pn_tx[0]  = (U1)TYDC_SOFT_N_NUM_CPU;

    u1_t_pn_chk    = u1_g_Product((U1)PRDCT_PN_SOFT_N, &u1_tp_pn_tx[TYDC_SOFT_N_BO_D1_SOF], (U1)PRDCT_SOFT_N_NBYTE);

    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_13] = (U1)0U;
    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_14] = (U1)0U;
    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_15] = (U1)0U;
    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_16] = (U1)0U;

    u1_t_pn_chk    &= u1_g_LComSpiSpnRx((U1)LCOM_SPI_SPN_RX_HYP, &u1_tp_pn_tx[TYDC_SOFT_N_BO_RC_HYP], (U1)LCOM_SPI_SPN_NB_HYP);

    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_29] = (U1)0U;
    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_30] = (U1)0U;
    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_31] = (U1)0U;
    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_32] = (U1)0U;

    u1_t_pn_chk    &= u1_g_LComSpiSpnRx((U1)LCOM_SPI_SPN_RX_EMM, &u1_tp_pn_tx[TYDC_SOFT_N_BO_RC_EMM], (U1)LCOM_SPI_SPN_NB_EMM);

    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_45] = (U1)0U;
    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_46] = (U1)0U;
    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_47] = (U1)0U;
    u1_tp_pn_tx[TYDC_SOFT_N_BO_AN_48] = (U1)0U;

    if(u1_t_pn_chk == (U1)TRUE){

        vd_g_MemcpyU1(u1_ap_ans, &u1_tp_pn_tx[0], (U4)OXDC_DATA_REA_ANS_NB_F181);
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
    }

    return(u1_t_proc);
#else
    return((U1)OXDC_SAL_PROC_FIN);
#endif
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcProduct_SERI_N(U1 * u1_ap_ans)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcProduct_SERI_N(U1 * u1_ap_ans)
{
#if 0/*Phase6Diag Stub*/
    U1                     u1_tp_pn_tx[OXDC_DATA_REA_ANS_NB_F18C];
    U1                     u1_t_pn_chk;
    U1                     u1_t_proc;

    u1_t_pn_chk  = u1_g_Product((U1)PRDCT_PN_ECU_PN, &u1_tp_pn_tx[0],                 (U1)PRDCT_ECU_PN_NBYTE);
    u1_t_pn_chk &= u1_g_Product((U1)PRDCT_PN_SERI_N, &u1_tp_pn_tx[TYDC_SERI_ECU_LEN], (U1)PRDCT_SERI_N_NBYTE);
    if(u1_t_pn_chk == (U1)TRUE){

        vd_g_MemcpyU1(u1_ap_ans, &u1_tp_pn_tx[0], (U4)OXDC_DATA_REA_ANS_NB_F18C);
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
    }

    return(u1_t_proc);
#else
    return((U1)OXDC_SAL_PROC_FIN);
#endif
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcProduct_HUD_N(U1 * u1_ap_ans)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcProduct_HUD_N(U1 * u1_ap_ans)
{
#if 0/*Phase6Diag Stub*/
    U1                     u1_tp_pn_tx[OXDC_DATA_REA_ANS_NB_0107];
    U1                     u1_t_pn_chk;
    U1                     u1_t_proc;

    u1_tp_pn_tx[0]                     = (U1)TYDC_SOFT_N_NUM_SLV;
    u1_tp_pn_tx[TYDC_SOFT_N_BO_D1_SLV] = (U1)TYDC_SOFT_N_SLV_ID_1;

    u1_t_pn_chk  = u1_g_LComSpiSpnRx((U1)LCOM_SPI_SPN_RX_HUD, &u1_tp_pn_tx[TYDC_SOFT_N_BO_SLV_HUD], (U1)LCOM_SPI_SPN_NB_HUD);

    if(u1_t_pn_chk == (U1)TRUE){

        vd_g_MemcpyU1(u1_ap_ans, &u1_tp_pn_tx[0], (U4)OXDC_DATA_REA_ANS_NB_0107);
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
    }

    return(u1_t_proc);
#else
    return((U1)OXDC_SAL_PROC_FIN);
#endif
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_0107(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_0107(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
} 
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANXidSup_1201(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANXidSup_1201(void)
{
    return((U1)OXDC_XID_SUP_PUB);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_1025(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_1025(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
} 
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_1043(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_1043(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_1044(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_1044(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_10AB(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_10AB(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pri());
} 
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_10AC(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_10AC(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
} 
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_1142(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_1142(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
} 
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_18A1(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_18A1(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
} 
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_18A2(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_18A2(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
} 
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_2202(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_2202(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
} 
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_2203(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_2203(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_280B(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_280B(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_280C(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_280C(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
}
/*===================================================================================================================================*/
/*  U2      u2_g_TyDoCANCursorCount(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_TyDoCANCursorCount(void)
{
    return(u2_g_LcomSpiCursorCntRead());
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANGetDisplaySwitchCntt(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANGetDisplaySwitchCntt(void)
{
    return((U1)0U);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRidSup_1103(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRidSup_1103(void)
{
    return(u1_s_TyDoCANXidSup_Hud_Pub());
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/11/2020  TN       New.                                                                                               */
/*  1.1.0    10/06/2020  AS       Update Phase5 Spec (MET-M_MMPHA5DI-CSTD-0-08-A-C4)                                                 */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1   10/06/2020  AS       Configured for 800B                                                                                */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * AS   = Atsunori Sugita, DENSO-TECHNO                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
