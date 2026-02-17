/* 2.2.0 */
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
#define LOCALE_CFG_C_MINOR                     (2)
#define LOCALE_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "locale_cfg_private.h"
#include "vardef.h"
#include "mcst.h"
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
static U1                                       u1_s_locale_unit_ambtmp;
#endif   /* BEV Rebase provisionally */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_UNITIDX st_sp_LOCALE_UNITIDX[UNIT_NUM_IDX] = {
    { (U1)MCST_BFI_DIST,   (U1)VDF_DEST_LAW_DBF_DEFUNIT_SPD    }, /*   UNIT_IDX_DIST                       (0U) */
    { (U1)MCST_BFI_SPEED,  (U1)VDF_DEST_LAW_DBF_DEFUNIT_SPD    }, /*   UNIT_IDX_SPEED                      (1U) */
    { (U1)MCST_BFI_ELECO,  (U1)VDF_DEST_LAW_DBF_DEFUNIT_ELECO  }, /*   UNIT_IDX_ELECO                      (2U) */
#if 0   /* BEV Rebase provisionally */
    { (U1)MCST_BFI_AMBTMP, (U1)VDF_DEST_DBF_AMBTMP             }  /*   UNIT_IDX_AMBTMP                     (3U) */
#else   /* BEV Rebase provisionally */
    { (U1)U1_MAX,          (U1)VDF_DEST_DBF_AMBTMP             }  /*   UNIT_IDX_AMBTMP                     (3U) */
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
    u1_s_locale_unit_ambtmp  = (U1)U1_MAX;
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
    U4  u4_t_chk_value;

    switch(u1_a_UNITIDX){
    case (U1)UNIT_IDX_DIST:
    case (U1)UNIT_IDX_SPEED:
    case (U1)UNIT_IDX_ELECO:
        u1_t_idx   = st_sp_LOCALE_UNITIDX[u1_a_UNITIDX].u1_mcst_id;
        u4_t_chk_value = u4_g_McstBf(u1_t_idx);
        if(u4_t_chk_value > (U4)U1_MAX){
            u4_t_chk_value = (U4)U1_MAX;
        }
        u1_t_unit  = (U1)u4_t_chk_value;
        break;
    case (U1)UNIT_IDX_AMBTMP:
#if 0   /* BEV Rebase provisionally */
#else   /* BEV Rebase provisionally */
        u1_t_unit  = u1_s_locale_unit_ambtmp;
#endif   /* BEV Rebase provisionally */
        break;
    default:
        u1_t_unit  = (U1)U1_MAX;
        break;
    }
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

    switch(u1_a_UNITIDX){
    case (U1)UNIT_IDX_DIST:
    case (U1)UNIT_IDX_SPEED:
    case (U1)UNIT_IDX_ELECO:
        u1_t_idx   = st_sp_LOCALE_UNITIDX[u1_a_UNITIDX].u1_mcst_id;
        vd_g_McstBfPut(u1_t_idx , (U4)u1_a_VAL);
        break;
    case (U1)UNIT_IDX_AMBTMP:
#if 0   /* BEV Rebase provisionally */
#else   /* BEV Rebase provisionally */
        u1_s_locale_unit_ambtmp = u1_a_VAL;
#endif   /* BEV Rebase provisionally */
        break;
    default:
        /* do nothing */
        break;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT)
{
    vd_g_McstBfPut((U1)MCST_BFI_TIMEFMT, (U4)u1_a_FRMT);
}

/*===================================================================================================================================*/
/*  void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_LocaleCfgTfm(void)
{
    U4  u4_t_timfmt;

    u4_t_timfmt = u4_g_McstBf((U1)MCST_BFI_TIMEFMT);
    if(u4_t_timfmt > (U4)U1_MAX){
        u4_t_timfmt = (U4)U1_MAX;
    }
    return((U1)u4_t_timfmt);
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
/*  2.1.0    02/09/2026  SN(K)    See locale.c v2.1.0                                                                                */
/*  2.2.0    01/30/2026  YN       See locale.c v2.2.0                                                                                */
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
/*  BEV-5    02/09/2026  SN(K)    Delete the u1_s_locale_unit_fueco definition and related handling.(BEV3CDCMET-3860)                */
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
/*  * SN(K)= Shizuka Nakajima, KSE                                                                                                   */
/*  * YN   = Yujiro Nagaya, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
