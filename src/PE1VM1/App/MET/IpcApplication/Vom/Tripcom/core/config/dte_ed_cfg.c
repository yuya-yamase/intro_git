/* 2.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Trip Computer                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DTE_ED_CFG_C_MAJOR                     (2)
#define DTE_ED_CFG_C_MINOR                     (2)
#define DTE_ED_CFG_C_PATCH                     (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "dte_ed_cfg_private.h"

#include "fuelvol_tau.h"
#include "vardef.h"
#include "calibration.h"
#include "tripcom_calc.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DTE_ED_CFG_C_MAJOR != DTE_ED_H_MAJOR) || \
     (DTE_ED_CFG_C_MINOR != DTE_ED_H_MINOR) || \
     (DTE_ED_CFG_C_PATCH != DTE_ED_H_PATCH))
#error "tripcom_cfg.c and tripcom.h : source and header files are inconsistent!"
#endif

#if ((DTE_ED_CFG_C_MAJOR != DTE_ED_CFG_H_MAJOR) || \
     (DTE_ED_CFG_C_MINOR != DTE_ED_CFG_H_MINOR) || \
     (DTE_ED_CFG_C_PATCH != DTE_ED_CFG_H_PATCH))
#error "tripcom_cfg.c and tripcom_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NUM_ENGTYPE                     (2U)
#define TRIPCOM_ENGTYPE_UNDEF                   (0U)
#define TRIPCOM_ENGTYPE_HYBRID                  (1U)

#define DTE_ED_CFG_PER_TO_RATE                  (100U)             /* percent to rate                                                */
#define DTE_ED_CFG_RATE_TO_PER                  (100U)             /* rate to percent                                                */
#define DTE_ED_CFG_FUEL_DEFAULT_RATE            (100U)             /* dafault fuel rate                                              */
#define DTE_ED_CFG_FUEL_LIT_TO_PLS              (100000U)          /* fuel km/L to 0.1pls/10cc                                       */

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
static inline U4    u4_s_DteEdCfgCalibFailChk(const U4 u4_a_CALIBID, const U4 u4_a_MAX, const U4 u4_a_DEF);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_DteEdCfgFuelOOR(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DteEdCfgFuelOOR(void)
{
    U1  u1_t_abn;

    u1_t_abn = u1_g_FuelvolTauEasAct((U1)FUEL_TAU_EAS_ID_VEU_OOR, (U1)FUEL_TAU_EAS_EDG_CRNT);
    return(u1_t_abn);
}

/*===================================================================================================================================*/
/*  U1      u1_g_DteEdCfgFuelRcmGsiAct(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DteEdCfgFuelRcmGsiAct(void)
{
    U1  u1_t_refuel;

    u1_t_refuel  = u1_g_FuelvolTauEasAct((U1)FUEL_TAU_EAS_ID_RCM_ACT   , (U1)FUEL_TAU_EAS_EDG_CRNT);
    u1_t_refuel |= u1_g_FuelvolTauEasAct((U1)FUEL_TAU_EAS_ID_VEU_GFI   , (U1)FUEL_TAU_EAS_EDG_CRNT);

    return(u1_t_refuel);
}

/*===================================================================================================================================*/
/*  U1      u1_g_DteEdCfgFuelInitComp(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DteEdCfgFuelInitComp(void)
{
    U1  u1_t_initcomp;

    u1_t_initcomp  = u1_g_FuelvolTauEasAct((U1)FUEL_TAU_EAS_ID_AVG_I   , (U1)FUEL_TAU_EAS_EDG_CRNT);
    return(u1_t_initcomp);
}

/*===================================================================================================================================*/
/*  U2      u2_g_DteEdCfgCurrLit0p01BaseME(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_DteEdCfgCurrLit0p01BaseME(void)
{
    U2 u2_t_lit_0p01;
    U1 u1_t_sts;

    u2_t_lit_0p01 = (U2)0U;
    u1_t_sts      = u1_g_FuelvolTauLitEst((U1)TRUE, &u2_t_lit_0p01);
    if(u1_t_sts != (U1)FUEL_TAU_STSBIT_VALID){
        u2_t_lit_0p01 = (U2)0U;
    }
    return(u2_t_lit_0p01);
}

/*===================================================================================================================================*/
/*  U2      u2_g_DteEdCfgCurrLit0p01BaseSE(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_DteEdCfgCurrLit0p01BaseSE(void)
{
    U2 u2_t_lit_0p01;
    U1 u1_t_sts;

    u2_t_lit_0p01 = (U2)0U;
    u1_t_sts      = u1_g_FuelvolTauLitEst((U1)FALSE, &u2_t_lit_0p01);
    if(u1_t_sts != (U1)FUEL_TAU_STSBIT_VALID){
        u2_t_lit_0p01 = (U2)0U;
    }
    return(u2_t_lit_0p01);
}

/*===================================================================================================================================*/
/*  U2      u2_g_DteEdCfgSeFullLit0p01(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_DteEdCfgSeFullLit0p01(void)
{
    U1  u1_t_sts;
    U2  u2_tp_lit[FUEL_TAU_LITTBL_ID_NUM];
    U4  u4_t_loop;
    U2  u2_t_lit_sf;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)FUEL_TAU_LITTBL_ID_NUM ; u4_t_loop++){
        u2_tp_lit[u4_t_loop] = (U2)0U;
    }
    u1_t_sts = u1_g_FuelvolTauLitTbl(&u2_tp_lit[0], (U1)FUEL_TAU_LITTBL_ID_NUM);
    u2_t_lit_sf = (U2)0U;
    if(u1_t_sts == (U1)TRUE){
        u2_t_lit_sf = u2_tp_lit[FUEL_TAU_LITTBL_ID_SF];
    }

    return(u2_t_lit_sf);
}

/*===================================================================================================================================*/
/*  U2      u2_g_DteEdCfgMeEmptyLit0p01(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_DteEdCfgMeEmptyLit0p01(void)
{
    return(u2_CALIB_MCUID0240_FULMENP);
}

/*===================================================================================================================================*/
/*  void    vd_g_DteEdCfgPrm(ST_DTE_ED_PRM * stp_a_ed_prm)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DteEdCfgPrm(ST_DTE_ED_PRM * stp_a_ed_prm)
{
    U1 u1_t_ddffuce;
    U1 u1_t_khcor_per;
    U1 u1_t_fulcor_per;
    U1 u1_t_gmin_per;
    U1 u1_t_gcen_per;
    U1 u1_t_gmax_per;
    U4 u4_t_cg_def;
    U4 u4_t_cg_min;
    U4 u4_t_cg_max;
    U4 u4_t_fueleff;
    U4 u4_t_effupr;
    U4 u4_t_efflow;
    U4 u4_t_effupr_per;
    U4 u4_t_efflow_per;
    U4 u4_t_cg_fueleff;
    U4 u4_t_mul;

    u4_t_fueleff    = u4_s_DteEdCfgCalibFailChk(u4_CALIB_MCUID0241_FULEFF,  (U4)CALIB_MCUID0241_MAX, (U4)CALIB_MCUID0241_DEF);
    u1_t_ddffuce    = u1_CALIB_MCUID0242_DDFFUCE;
    u1_t_khcor_per  = u1_CALIB_MCUID0243_DKHCOEF;
    u4_t_effupr     = u4_s_DteEdCfgCalibFailChk(u4_CALIB_MCUID0244_EFFUPR,  (U4)CALIB_MCUID0244_MAX, (U4)CALIB_MCUID0244_DEF);
    u4_t_efflow     = u4_s_DteEdCfgCalibFailChk(u4_CALIB_MCUID0245_EFFLOW,  (U4)CALIB_MCUID0245_MAX, (U4)CALIB_MCUID0245_DEF);
    u1_t_fulcor_per = u1_CALIB_MCUID0246_FULCOEF;
    u1_t_gmin_per   = u1_CALIB_MCUID0247_GCOEFM;
    u1_t_gcen_per   = u1_CALIB_MCUID0248_GCOEFC;
    u1_t_gmax_per   = u1_CALIB_MCUID0249_GCOEFP;

    u4_t_cg_fueleff  = u4_g_TripcomCalcMulU4U4(u4_t_fueleff, (U4)u1_t_ddffuce);
    u4_t_cg_fueleff /= (U4)DTE_ED_CFG_PER_TO_RATE;
    u4_t_mul         = u4_g_TripcomCalcMulU4U4(u4_t_cg_fueleff, (U4)DTE_ED_PLSP1KM);
    u4_t_mul        /= (U4)DTE_ED_CFG_PER_TO_RATE;

    u4_t_effupr_per  = u4_g_TripcomCalcMulU4U4(u4_t_effupr, (U4)DTE_ED_CFG_RATE_TO_PER);
    u4_t_effupr_per /= u4_t_fueleff;


    u4_t_efflow_per = u4_g_TripcomCalcMulU4U4(u4_t_efflow, (U4)DTE_ED_CFG_RATE_TO_PER);
    u4_t_efflow_per /= u4_t_fueleff;

    u4_t_cg_def  = u4_g_TripcomCalcMulU4U4(u4_t_mul, (U4)DTE_ED_CFG_FUEL_DEFAULT_RATE);
    u4_t_cg_def /= (U4)DTE_ED_CFG_FUEL_LIT_TO_PLS;
    u4_t_cg_max  = u4_g_TripcomCalcMulU4U4(u4_t_mul, u4_t_effupr_per);
    u4_t_cg_max /= (U4)DTE_ED_CFG_FUEL_LIT_TO_PLS;
    u4_t_cg_min  = u4_g_TripcomCalcMulU4U4(u4_t_mul, u4_t_efflow_per);
    u4_t_cg_min /= (U4)DTE_ED_CFG_FUEL_LIT_TO_PLS;

    stp_a_ed_prm->u2_cg_def     = (U2)u4_t_cg_def;
    stp_a_ed_prm->u2_cg_min     = (U2)u4_t_cg_min;
    stp_a_ed_prm->u2_cg_max     = (U2)u4_t_cg_max;
    stp_a_ed_prm->u1_khcor_per  = u1_t_khcor_per;
    stp_a_ed_prm->u1_fulcor_per = u1_t_fulcor_per;
    stp_a_ed_prm->u1_g_min_per  = u1_t_gmin_per;
    stp_a_ed_prm->u1_g_cen_per  = u1_t_gcen_per;
    stp_a_ed_prm->u1_g_max_per  = u1_t_gmax_per;
}

/*===================================================================================================================================*/
/*  U1      u1_g_DteEdCfgEMGFExist(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_exist                                                                                                    */
/*===================================================================================================================================*/
U1      u1_g_DteEdCfgEMGFExist(void)
{
    U1  u1_t_ptsys;
    U1  u1_t_exist;

    u1_t_exist = (U1)FALSE;
    u1_t_ptsys = u1_g_VardefPtsRx();
    if(u1_t_ptsys == (U1)VDF_PTS_RX_04_HYB_PLU){
        u1_t_exist = (U1)TRUE;
    }
    return(u1_t_exist);
}

/*===================================================================================================================================*/
/*  static inline U4  u4_s_DteEdCfgCalibFailChk(const U4 u4_a_CALIBID, const U4 u4_a_MAX, const U4 u4_a_DEF)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U4 u4_a_CALIBID                                                                                            */
/*                  const U4 u4_a_MAX                                                                                                */
/*                  const U4 u4_a_DEF                                                                                                */
/*  Return:         U4 u4_t_ret                                                                                                      */
/*===================================================================================================================================*/
static inline U4    u4_s_DteEdCfgCalibFailChk(const U4 u4_a_CALIBID, const U4 u4_a_MAX, const U4 u4_a_DEF)
{
    U4 u4_t_ret;

    u4_t_ret = u4_a_CALIBID;
    if((u4_t_ret >  u4_a_MAX)
    || (u4_t_ret == (U4)0U)){
        u4_t_ret = u4_a_DEF;
    }

    return(u4_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    11/07/2018  HY       New.                                                                                               */
/*  1.1.0    03/17/2020  YA       Change for 800B CV                                                                                 */
/*  1.1.1    07/28/2020  YA       Initial value transmission change                                                                  */
/*  1.2.0    10/07/2020  YA       Change for 800B CV-R.                                                                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/25/2021  TA(M)    tripcom.c v2.0.1 -> v2.0.2.                                                                        */
/*  2.0.3    10/25/2021  TK       tripcom.c v2.0.2 -> v2.0.3.                                                                        */
/*  2.1.1    02/07/2022  TA(M)    dte_ed.c v2.1.0 -> v2.1.1.                                                                         */
/*  2.2.0    04/14/2022  TA(M)    dte_ed.c v2.1.1 -> v2.2.0.                                                                         */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  178D-1   11/22/2021  YA       Changed for 178D 1A                                                                                */
/*  200D     09/04/2022  SK       Changed for 200D 1A                                                                                */
/*  330D     01/09/2023  KK       Changed for 330D CV-R                                                                              */
/*  330D     02/07/2023  HH       Changed for 330D CV-R                                                                              */
/*  19PFv3-1 11/06/2023  SH       Changed to read calibration parameter                                                              */
/*  19PFv3-2 04/01/2024  HK       Changed for Guard Processing of Calibration                                                        */
/*  19PFv3-3 04/16/2024  SH       Add calibration guard                                                                              */
/*  19PFv3-4 05/07/2024  SH       Delete calibration guard (MCUID0243, MCUID0246, MCUID0247, MCUID0248, MCUID0249)                   */
/*  19PFv3-5 05/10/2024  SH       Delete calibration min guard (MCUID0241, MCUID0244, MCUID0245)                                     */
/*  19PFv3-6 07/05/2024  TN       Delete Calibration Guard Process except for division by 0.                                         */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * SK   = Shintaro Kano, Denso Techno                                                                                             */
/*  * KK   = Kohei Kato,    Denso Techno                                                                                             */
/*  * HH   = Hiroki Hara,   Denso Techno                                                                                             */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * HK   = Hiroyuki Kato, Denso Techno                                                                                             */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
