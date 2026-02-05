/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Locale                                                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LOCALE_CFG_C_MAJOR                     (2)
#define LOCALE_CFG_C_MINOR                     (1)
#define LOCALE_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "locale_cfg_private.h"
#include "vardef.h"
#include "oxcan.h"
#include "rim_ctl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((LOCALE_CFG_C_MAJOR != LOCALE_H_MAJOR) || \
     (LOCALE_CFG_C_MINOR != LOCALE_H_MINOR) || \
     (LOCALE_CFG_C_PATCH != LOCALE_H_PATCH))
#error "locale_cfg.c and locale.h : source and header files are inconsistent!"
#endif

#if ((LOCALE_CFG_C_MAJOR != LOCALE_CFG_H_MAJOR) || \
     (LOCALE_CFG_C_MINOR != LOCALE_CFG_H_MINOR) || \
     (LOCALE_CFG_C_PATCH != LOCALE_CFG_H_PATCH))
#error "locale_cfg.c and locale_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LOCALE_UNIT_CH2_KM  (1U)
#define LOCALE_UNIT_CH2_MI  (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1  u1_mcst_id;
    U1  u1_vdf_id;
}ST_UNITIDX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV Rebase provisionally */
#else   /* BEV Rebase provisionally */
static U1                                       u1_s_locale_timfmt;
static U1                                       u1_s_locale_unit_dist;
static U1                                       u1_s_locale_unit_speed;
static U1                                       u1_s_locale_unit_fueco;
static U1                                       u1_s_locale_unit_eleco;
static U1                                       u1_s_locale_unit_ambtmp;
#endif   /* BEV Rebase provisionally */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_UNITIDX st_sp_LOCALE_UNITIDX[UNIT_NUM_IDX] = {
#if 0   /* BEV Rebase provisionally */
    { (U1)MCST_BFI_DIST,   (U1)VDF_DEST_LAW_DBF_DEFUNIT_SPD    }, /*   UNIT_IDX_DIST                       (0U) */
    { (U1)MCST_BFI_SPEED,  (U1)VDF_DEST_LAW_DBF_DEFUNIT_SPD    }, /*   UNIT_IDX_SPEED                      (1U) */
    { (U1)MCST_BFI_FUECO,  (U1)VDF_DEST_LAW_DBF_DEFUNIT_FUECO  }, /*   UNIT_IDX_FUECO                      (2U) */
    { (U1)MCST_BFI_ELECO,  (U1)VDF_DEST_LAW_DBF_DEFUNIT_ELECO  }, /*   UNIT_IDX_ELECO                      (3U) */
    { (U1)MCST_BFI_AMBTMP, (U1)VDF_DEST_DBF_AMBTMP             }  /*   UNIT_IDX_AMBTMP                     (4U) */
#else   /* BEV Rebase provisionally */
    { (U1)U1_MAX,          (U1)VDF_DEST_LAW_DBF_DEFUNIT_SPD    }, /*   UNIT_IDX_DIST                       (0U) */
    { (U1)U1_MAX,          (U1)VDF_DEST_LAW_DBF_DEFUNIT_SPD    }, /*   UNIT_IDX_SPEED                      (1U) */
    { (U1)U1_MAX,          (U1)VDF_DEST_LAW_DBF_DEFUNIT_FUECO  }, /*   UNIT_IDX_FUECO                      (2U) */
    { (U1)U1_MAX,          (U1)VDF_DEST_LAW_DBF_DEFUNIT_ELECO  }, /*   UNIT_IDX_ELECO                      (3U) */
    { (U1)U1_MAX,          (U1)VDF_DEST_DBF_AMBTMP             }  /*   UNIT_IDX_AMBTMP                     (4U) */
#endif   /* BEV Rebase provisionally */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1 u1_sp_LOCALE_COMTX_UNIT_CH2[UNIT_NUM_VAL_SPEED] = {
    (U1)LOCALE_UNIT_CH2_KM, /* UNIT_VAL_SPEED_KMPH                 (0U) */
    (U1)LOCALE_UNIT_CH2_MI  /* UNIT_VAL_SPEED_MPH                  (1U) */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void  vd_g_LocaleComTxInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_LocaleComTxInit(void)
{
    U1  u1_t_unit_speed;
    U1  u1_t_unit_ch2;
#if 0   /* BEV Rebase provisionally */
#else   /* BEV Rebase provisionally */
    U1  u1_t_nvm_sts;
    U2  u2_t_nvmc_frmt;

    u1_s_locale_unit_dist    = (U1)U1_MAX;
    u1_s_locale_unit_speed   = (U1)U1_MAX;
    u1_s_locale_unit_fueco   = (U1)U1_MAX;
    u1_s_locale_unit_eleco   = (U1)U1_MAX;
    u1_s_locale_unit_ambtmp  = (U1)U1_MAX;

    u2_t_nvmc_frmt = (U2)0U;
    u1_t_nvm_sts   = u1_g_Nvmc_ReadStrValU2withSts((U2)NVMCID_U2_DATESI_TIMEFMT, &u2_t_nvmc_frmt);
    if((u1_t_nvm_sts == NVMC_STATUS_COMP) && (u2_t_nvmc_frmt <= (U2)U1_MAX)){
        u1_s_locale_timfmt = (U1)u2_t_nvmc_frmt;
    }
    else{
        u1_s_locale_timfmt = (U1)TIMEFMT_NUM_VAL;
    }
#endif   /* BEV Rebase provisionally */

    u1_t_unit_ch2   = (U1)LOCALE_UNIT_CH2_KM;
    u1_t_unit_speed = u1_g_Unit((U1)UNIT_IDX_SPEED);
    if(u1_t_unit_speed < (U1)UNIT_NUM_VAL_SPEED){
        u1_t_unit_ch2 = u1_sp_LOCALE_COMTX_UNIT_CH2[u1_t_unit_speed];
    }
    (void)Com_SendSignal(ComConf_ComSignal_UNIT_CH2 , &u1_t_unit_ch2);

}
/*===================================================================================================================================*/
/*  void  vd_g_LocaleComTxTask(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_LocaleComTxTask(void)
{
    U1  u1_t_unit_speed;
    U1  u1_t_pre_unit_ch2;
    U1  u1_t_unit_ch2;

    (void)Com_ReceiveSignal(ComConf_ComSignal_UNIT_CH2 , &u1_t_pre_unit_ch2);

    u1_t_unit_ch2   = (U1)LOCALE_UNIT_CH2_KM;
    u1_t_unit_speed = u1_g_Unit((U1)UNIT_IDX_SPEED);
    if(u1_t_unit_speed < (U1)UNIT_NUM_VAL_SPEED){
        u1_t_unit_ch2 = u1_sp_LOCALE_COMTX_UNIT_CH2[u1_t_unit_speed];
    }

    (void)Com_SendSignal(ComConf_ComSignal_UNIT_CH2 , &u1_t_unit_ch2);
    if(u1_t_pre_unit_ch2 != u1_t_unit_ch2){
        (void)Com_TriggerIPDUSend(MSG_MET1S11_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  U1  u1_g_LocaleCfgTimeFormatDef(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1  u1_g_LocaleCfgTimeFormatDef(void)
{
    return(u1_g_VardefDefTmFmtByPid());
}
/*===================================================================================================================================*/
/*  U1  u1_g_LocaleCfgSubSpd(const U1 u1_a_UNIT)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1  u1_g_LocaleCfgSubSpd(const U1 u1_a_UNIT)
{
    U1 u1_t_var_subspd;
    U1 u1_t_unit_subspd;

    u1_t_var_subspd = u1_g_VardefSubDigSpdByPid();

    if(( u1_a_UNIT       == (U1)UNIT_VAL_SPEED_KMPH) &&
       ((u1_t_var_subspd == (U1)VDF_SUBDIGSPD_MPH ) ||
        (u1_t_var_subspd == (U1)VDF_SUBDIGSPD_BOTH))){
        u1_t_unit_subspd = (U1)UNIT_SUB_SPD_MPH;
    }
    else if(( u1_a_UNIT       == (U1)UNIT_VAL_SPEED_MPH ) &&
            ((u1_t_var_subspd == (U1)VDF_SUBDIGSPD_KMPH) ||
             (u1_t_var_subspd == (U1)VDF_SUBDIGSPD_BOTH))){
        u1_t_unit_subspd = (U1)UNIT_SUB_SPD_KMPH;
    }
    else{
        u1_t_unit_subspd = (U1)UNIT_SUB_SPD_NON;
    }

    return(u1_t_unit_subspd);
}

/*===================================================================================================================================*/
/*  U1      u1_g_LocaleCfgUnit(const U1 u1_a_UNITIDX)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_LocaleCfgUnit(const U1 u1_a_UNITIDX)
{
    U1  u1_t_idx;
    U1  u1_t_unit;

    u1_t_idx   = st_sp_LOCALE_UNITIDX[u1_a_UNITIDX].u1_mcst_id;
#if 0   /* BEV Rebase provisionally */
    u1_t_unit  = u1_g_McstBf(u1_t_idx);
#else   /* BEV Rebase provisionally */
    switch(u1_a_UNITIDX){
    case  (U1)UNIT_IDX_DIST:
        u1_t_unit  = u1_s_locale_unit_dist;
        break;
    case (U1)UNIT_IDX_SPEED:
        u1_t_unit  = u1_s_locale_unit_speed;
        break;
    case (U1)UNIT_IDX_FUECO:
        u1_t_unit  = u1_s_locale_unit_fueco;
        break;
    case (U1)UNIT_IDX_ELECO:
        u1_t_unit  = u1_s_locale_unit_eleco;
        break;
    case (U1)UNIT_IDX_AMBTMP:
        u1_t_unit  = u1_s_locale_unit_ambtmp;
        break;
    default:
        u1_t_unit  = (U1)U1_MAX;
        break;
    }
#endif   /* BEV Rebase provisionally */
    return(u1_t_unit);
}

/*===================================================================================================================================*/
/*  void    vd_g_LocaleCfgUnitPut(const U1 u1_a_UNITIDX, const U1 u1_a_VAL)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_LocaleCfgUnitPut(const U1 u1_a_UNITIDX, const U1 u1_a_VAL)
{
    U1  u1_t_idx;
    u1_t_idx   = st_sp_LOCALE_UNITIDX[u1_a_UNITIDX].u1_mcst_id;
#if 0   /* BEV Rebase provisionally */
    vd_g_McstBfPut(u1_t_idx , u1_a_VAL);
#else   /* BEV Rebase provisionally */
    switch(u1_a_UNITIDX){
    case  (U1)UNIT_IDX_DIST:
        u1_s_locale_unit_dist   = u1_a_VAL;
        break;
    case (U1)UNIT_IDX_SPEED:
        u1_s_locale_unit_speed  = u1_a_VAL;
        break;
    case (U1)UNIT_IDX_FUECO:
        u1_s_locale_unit_fueco  = u1_a_VAL;
        break;
    case (U1)UNIT_IDX_ELECO:
        u1_s_locale_unit_eleco  = u1_a_VAL;
        break;
    case (U1)UNIT_IDX_AMBTMP:
        u1_s_locale_unit_ambtmp = u1_a_VAL;
        break;
    default:
        /* do nothing */
        break;
    }
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT)
{
#if 0   /* BEV Rebase provisionally */
    vd_g_McstBfPut((U1)MCST_BFI_TIMEFMT, u1_a_FRMT);
#else   /* BEV Rebase provisionally */
    if(u1_a_FRMT != u1_s_locale_timfmt){
        vd_g_Nvmc_WriteU2((U2)NVMCID_U2_DATESI_TIMEFMT, (U2)u1_a_FRMT);
        u1_s_locale_timfmt = u1_a_FRMT;
    }
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_LocaleCfgTfm(void)
{
#if 0   /* BEV Rebase provisionally */
    return(u1_g_McstBf((U1)MCST_BFI_TIMEFMT));
#else   /* BEV Rebase provisionally */
    return(u1_s_locale_timfmt);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_LocaleCfgUnitdef(const U1 u1_a_UNITIDX)
{
    U1  u1_t_idx;
    U1  u1_t_unit;

    u1_t_idx  = st_sp_LOCALE_UNITIDX[u1_a_UNITIDX].u1_vdf_id;
    if ( (U1)VDF_DEST_DBF_AMBTMP == u1_t_idx) {
        u1_t_unit  = u1_g_VardefDestDbfByPid(u1_t_idx);
    }
    else {
        u1_t_unit  = u1_g_VardefDestLawDbfByPid(u1_t_idx);
    }
    return(u1_t_unit);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/15/2017  TN       New.                                                                                               */
/*  1.1.0    01/24/2019  TA       See locale.c v1.1.0                                                                                */
/*  1.2.0    08/01/2019  TA       See locale.c v1.2.0                                                                                */
/*  1.3.0    04/29/2020  SF       See locale.c v1.3.0                                                                                */
/*  1.4.0    09/28/2020  SF       See locale.c v1.4.0                                                                                */
/*  1.5.0    01/25/2021  SF       See locale.c v1.5.0                                                                                */
/*  2.0.0    07/09/2021  TA       See locale.c v2.0.0.                                                                               */
/*  2.0.1    12/08/2022  TA(M)    See locale.c v2.0.1                                                                                */
/*  2.0.2    07/04/2025  MN       See locale.c v2.0.2                                                                                */
/*  2.1.0    01/30/2026  yn       See locale.c v2.1.0                                                                                */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1   02/24/2020  SF       Add Variation config for 800B CV.                                                                  */
/*  800B-2   09/28/2020  SF       Change config for 800B CV-R.                                                                       */
/*  800B-1   01/25/2021  SF       Change config for 800B 1A.                                                                         */
/*  840B-1   04/14/2021  AT       Change config for 840B CV                                                                          */
/*  893B-1   11/09/2021  RO       Change config for 893B 1A                                                                          */
/*  840B-2    1/24/2022  RO       Change config for 840B MPT                                                                         */
/*  025D182D-1 4/14/2022 SK       Change config for 025D182D 1A                                                                      */
/*  296D235D 11/28/2022  TX       Add Lang Type18 and Type19                                                                         */
/*  19PFv3-1 08/21/2023  SH       config merge                                                                                       */
/*  19PFv3-2 04/24/2025  SF       Bug fixing for MET19PFV3-43718                                                                     */
/*  BEV-1    07/04/2025  MN       BEV PreCV provisionally                                                                            */
/*  BEV-2    10/15/2025  SN       Configured for BEVstep3_Rebase                                                                     */
/*  BEV-3    11/14/2025  SN       Change initial value                                                                               */
/*  BEV-4    12/08/2025  TS       Change UNIT_CH2 table and units referenced when sending UNIT_CH2                                   */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * SF   = Seiya Fukutome, DensoTechno                                                                                             */
/*  * AT   = Ayano Tomimoto                                                                                                          */
/*  * RO   = Reiya Okuda, KSE                                                                                                        */
/*  * SK   = Shotaro Kitayama, PRD                                                                                                   */
/*  * TX   = Xinyuan Tong, DNST                                                                                                      */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*  * SN   = Shimon Nambu, DensoTechno                                                                                               */
/*  * TS   = Takuo Suganuma, Denso Techno                                                                                            */
/*  * YN   = Yujiro Nagaya, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
