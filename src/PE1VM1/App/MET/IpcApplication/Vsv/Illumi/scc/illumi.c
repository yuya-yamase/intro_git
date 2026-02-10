/* 2.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Illumination                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ILLUMI_C_MAJOR                          (2)
#define ILLUMI_C_MINOR                          (3)
#define ILLUMI_C_PATCH                          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "illumi_cfg_private.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ILLUMI_C_MAJOR != ILLUMI_H_MAJOR) || \
     (ILLUMI_C_MINOR != ILLUMI_H_MINOR) || \
     (ILLUMI_C_PATCH != ILLUMI_H_PATCH))
#error "illumi.c and illumi.h : source and header files are inconsistent!"
#endif

#if ((ILLUMI_C_MAJOR != ILLUMI_CFG_H_MAJOR) || \
     (ILLUMI_C_MINOR != ILLUMI_CFG_H_MINOR) || \
     (ILLUMI_C_PATCH != ILLUMI_CFG_H_PATCH))
#error "illumi.c and illumi_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static volatile const U1 * u1p_sp_ILLUMI_BL_PCT_DAY[ILLUMI_DIM_LVL_NUM] = {
    &u1_CALIB_MCUID0363_BL_DAY_MIN,
    &u1_CALIB_MCUID0362_BL_DAY_LV20,
    &u1_CALIB_MCUID0361_BL_DAY_LV19,
    &u1_CALIB_MCUID0360_BL_DAY_LV18,
    &u1_CALIB_MCUID0359_BL_DAY_LV17,
    &u1_CALIB_MCUID0358_BL_DAY_LV16,
    &u1_CALIB_MCUID0357_BL_DAY_LV15,
    &u1_CALIB_MCUID0356_BL_DAY_LV14,
    &u1_CALIB_MCUID0355_BL_DAY_LV13,
    &u1_CALIB_MCUID0354_BL_DAY_LV12,
    &u1_CALIB_MCUID0353_BL_DAY_LV11,
    &u1_CALIB_MCUID0352_BL_DAY_LV10,
    &u1_CALIB_MCUID0351_BL_DAY_LV9,
    &u1_CALIB_MCUID0350_BL_DAY_LV8,
    &u1_CALIB_MCUID0349_BL_DAY_LV7,
    &u1_CALIB_MCUID0348_BL_DAY_LV6,
    &u1_CALIB_MCUID0347_BL_DAY_LV5,
    &u1_CALIB_MCUID0346_BL_DAY_LV4,
    &u1_CALIB_MCUID0345_BL_DAY_LV3,
    &u1_CALIB_MCUID0344_BL_DAY_LV2,
    &u1_CALIB_MCUID0343_BL_DAY_LV1,
    &u1_CALIB_MCUID0342_BL_DAY_MAX
};

static volatile const U1 * u1p_sp_ILLUMI_RGB_DAY[ILLUMI_DIM_LVL_NUM] = {
    &u1_CALIB_MCUID0385_RGB_DAY_MIN,
    &u1_CALIB_MCUID0384_RGB_DAY_LV20,
    &u1_CALIB_MCUID0383_RGB_DAY_LV19,
    &u1_CALIB_MCUID0382_RGB_DAY_LV18,
    &u1_CALIB_MCUID0381_RGB_DAY_LV17,
    &u1_CALIB_MCUID0380_RGB_DAY_LV16,
    &u1_CALIB_MCUID0379_RGB_DAY_LV15,
    &u1_CALIB_MCUID0378_RGB_DAY_LV14,
    &u1_CALIB_MCUID0377_RGB_DAY_LV13,
    &u1_CALIB_MCUID0376_RGB_DAY_LV12,
    &u1_CALIB_MCUID0375_RGB_DAY_LV11,
    &u1_CALIB_MCUID0374_RGB_DAY_LV10,
    &u1_CALIB_MCUID0373_RGB_DAY_LV9,
    &u1_CALIB_MCUID0372_RGB_DAY_LV8,
    &u1_CALIB_MCUID0371_RGB_DAY_LV7,
    &u1_CALIB_MCUID0370_RGB_DAY_LV6,
    &u1_CALIB_MCUID0369_RGB_DAY_LV5,
    &u1_CALIB_MCUID0368_RGB_DAY_LV4,
    &u1_CALIB_MCUID0367_RGB_DAY_LV3,
    &u1_CALIB_MCUID0366_RGB_DAY_LV2,
    &u1_CALIB_MCUID0365_RGB_DAY_LV1,
    &u1_CALIB_MCUID0364_RGB_DAY_MAX
};

static volatile const U1 * u1p_sp_ILLUMI_BL_PCT_NGT[ILLUMI_DIM_LVL_NUM] = {
    &u1_CALIB_MCUID0407_BL_NGT_MIN,
    &u1_CALIB_MCUID0406_BL_NGT_LV20,
    &u1_CALIB_MCUID0405_BL_NGT_LV19,
    &u1_CALIB_MCUID0404_BL_NGT_LV18,
    &u1_CALIB_MCUID0403_BL_NGT_LV17,
    &u1_CALIB_MCUID0402_BL_NGT_LV16,
    &u1_CALIB_MCUID0401_BL_NGT_LV15,
    &u1_CALIB_MCUID0400_BL_NGT_LV14,
    &u1_CALIB_MCUID0399_BL_NGT_LV13,
    &u1_CALIB_MCUID0398_BL_NGT_LV12,
    &u1_CALIB_MCUID0397_BL_NGT_LV11,
    &u1_CALIB_MCUID0396_BL_NGT_LV10,
    &u1_CALIB_MCUID0395_BL_NGT_LV9,
    &u1_CALIB_MCUID0394_BL_NGT_LV8,
    &u1_CALIB_MCUID0393_BL_NGT_LV7,
    &u1_CALIB_MCUID0392_BL_NGT_LV6,
    &u1_CALIB_MCUID0391_BL_NGT_LV5,
    &u1_CALIB_MCUID0390_BL_NGT_LV4,
    &u1_CALIB_MCUID0389_BL_NGT_LV3,
    &u1_CALIB_MCUID0388_BL_NGT_LV2,
    &u1_CALIB_MCUID0387_BL_NGT_LV1,
    &u1_CALIB_MCUID0386_BL_NGT_MAX
};
static volatile const U1 * u1p_sp_ILLUMI_RGB_NGT[ILLUMI_DIM_LVL_NUM] = {
    &u1_CALIB_MCUID0429_RGB_NGT_MIN,
    &u1_CALIB_MCUID0428_RGB_NGT_LV20,
    &u1_CALIB_MCUID0427_RGB_NGT_LV19,
    &u1_CALIB_MCUID0426_RGB_NGT_LV18,
    &u1_CALIB_MCUID0425_RGB_NGT_LV17,
    &u1_CALIB_MCUID0424_RGB_NGT_LV16,
    &u1_CALIB_MCUID0423_RGB_NGT_LV15,
    &u1_CALIB_MCUID0422_RGB_NGT_LV14,
    &u1_CALIB_MCUID0421_RGB_NGT_LV13,
    &u1_CALIB_MCUID0420_RGB_NGT_LV12,
    &u1_CALIB_MCUID0419_RGB_NGT_LV11,
    &u1_CALIB_MCUID0418_RGB_NGT_LV10,
    &u1_CALIB_MCUID0417_RGB_NGT_LV9,
    &u1_CALIB_MCUID0416_RGB_NGT_LV8,
    &u1_CALIB_MCUID0415_RGB_NGT_LV7,
    &u1_CALIB_MCUID0414_RGB_NGT_LV6,
    &u1_CALIB_MCUID0413_RGB_NGT_LV5,
    &u1_CALIB_MCUID0412_RGB_NGT_LV4,
    &u1_CALIB_MCUID0411_RGB_NGT_LV3,
    &u1_CALIB_MCUID0410_RGB_NGT_LV2,
    &u1_CALIB_MCUID0409_RGB_NGT_LV1,
    &u1_CALIB_MCUID0408_RGB_NGT_MAX
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_IllumiBonInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IllumiBonInit(void)
{
    U4      u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_ILLUMI_NUM_CH; u4_t_lpcnt++) {
        u2_gp_illumi_lvl_pct[u4_t_lpcnt]          = (U2)0U;
        st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_tocnt = (U2)ILLUMI_OW_TOC_MAX;
        st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_pct   = (U2)ILLUMI_OW_INA;
    }

    vd_g_IllumiCfgBonInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_IllumiRstInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IllumiRstInit(void)
{
    U4      u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_ILLUMI_NUM_CH; u4_t_lpcnt++) {
        u2_gp_illumi_lvl_pct[u4_t_lpcnt]          = (U2)0U;
        st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_tocnt = (U2)ILLUMI_OW_TOC_MAX;
        st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_pct   = (U2)ILLUMI_OW_INA;
    }

    vd_g_IllumiCfgRstInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_IllumiWkupInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IllumiWkupInit(void)
{
    U4      u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_ILLUMI_NUM_CH; u4_t_lpcnt++) {
        u2_gp_illumi_lvl_pct[u4_t_lpcnt]          = (U2)0U;
        st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_tocnt = (U2)ILLUMI_OW_TOC_MAX;
        st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_pct   = (U2)ILLUMI_OW_INA;
    }

    vd_g_IllumiCfgWkupInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_IllumiMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IllumiMainTask(void)
{
    U4      u4_t_lpcnt;

    U2      u2_tp_dim_lvl[ILLUMI_NUM_DIM_LVL];
    U2      u2_t_pct;
    U2      u2_t_ow;

    vd_g_IllumiCfgMainStart();

    u2_tp_dim_lvl[ILLUMI_DIM_LVL_USADJ_DAY]   = u2_g_DimLvlUsadjust((U1)DIM_DAYNIGHT_LVL_DAY);
    u2_tp_dim_lvl[ILLUMI_DIM_LVL_USADJ_NIGHT] = u2_g_DimLvlUsadjust((U1)DIM_DAYNIGHT_LVL_NIGHT);
    u2_tp_dim_lvl[ILLUMI_DIM_LVL_DAYNIGHT]    = (U2)u1_g_DimLvlDaynight();

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_ILLUMI_NUM_CH; u4_t_lpcnt++) {

        if(fp_gp_u2_ILLUMI_LVL_UPDT[u4_t_lpcnt] != vdp_PTR_NA) {
            if(st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_tocnt >= (U2)U2_MAX){
                st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_tocnt = (U2)0U;
            }
            else if(st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_tocnt >= (U2)ILLUMI_OW_TOC_MAX){
                st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_tocnt = (U2)ILLUMI_OW_TOC_MAX;
            }
            else{
                st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_tocnt++; /* QAC over-detection */
            }

            if(st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_tocnt >= u2_g_ILLUMI_OW_TOUT){
                u2_t_ow = (U2)ILLUMI_OW_INA;
            }
            else{
                u2_t_ow = st_gp_illumi_ow_ctrl[u4_t_lpcnt].u2_pct;
            }

            u2_t_pct = (fp_gp_u2_ILLUMI_LVL_UPDT[u4_t_lpcnt])(&u2_tp_dim_lvl[0], u2_t_ow);
        }
        else{
            u2_t_pct = (U2)0U;
        }

        u2_gp_illumi_lvl_pct[u4_t_lpcnt] = u2_t_pct;

    }

    vd_g_IllumiCfgMainFinish();
}
/*===================================================================================================================================*/
/*  U2      u2_g_IllumiLvlPct(const U1 u1_a_ILLUMI_CH)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_IllumiLvlPct(const U1 u1_a_ILLUMI_CH)
{
    U2      u2_t_pct;

    if(u1_a_ILLUMI_CH < u1_g_ILLUMI_NUM_CH){
        u2_t_pct = u2_gp_illumi_lvl_pct[u1_a_ILLUMI_CH];
    }
    else{
        u2_t_pct = (U2)0U;
    }

    return(u2_t_pct);
}
/*===================================================================================================================================*/
/*  U1      u1_g_IllumiTftPct(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_IllumiTftPct(void)
{
    U1                       u1_t_pct;
    U1                       u1_t_daynight;
    U2                       u2_t_lvl;

    u1_t_pct      = (U1)ILLUMI_TFTPCT_OFF;
    u1_t_daynight = u1_g_DimLvlDaynight();
    if(u1_t_daynight < (U1)ILLUMI_DIM_LVL_DAYNIGHT){
        u2_t_lvl = u2_g_DimLvlUsadjust(u1_t_daynight);
        if(u2_t_lvl < (U2)ILLUMI_DIM_LVL_NUM){
            if(u1_t_daynight == (U1)ILLUMI_DIM_LVL_USADJ_DAY){
                u1_t_pct = *(u1p_sp_ILLUMI_BL_PCT_DAY[u2_t_lvl]);
            }
            else{
                u1_t_pct = *(u1p_sp_ILLUMI_BL_PCT_NGT[u2_t_lvl]);
            }
        }
    }
    return(u1_t_pct);
}
/*===================================================================================================================================*/
/*  U1      u1_g_IllumiTftAlpha(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_IllumiTftAlpha(void)
{
    U1                       u1_t_pct;
    U1                       u1_t_daynight;
    U2                       u2_t_lvl;

    u1_t_pct      = (U1)ILLUMI_TFTALPHA_OFF;
    u1_t_daynight = u1_g_DimLvlDaynight();
    if(u1_t_daynight < (U1)ILLUMI_DIM_LVL_DAYNIGHT){
        u2_t_lvl = u2_g_DimLvlUsadjust(u1_t_daynight);
        if(u2_t_lvl < (U2)ILLUMI_DIM_LVL_NUM){
            if(u1_t_daynight == (U1)ILLUMI_DIM_LVL_USADJ_DAY){
                u1_t_pct = *(u1p_sp_ILLUMI_RGB_DAY[u2_t_lvl]);
            }
            else{
                u1_t_pct = *(u1p_sp_ILLUMI_RGB_NGT[u2_t_lvl]);
            }
        }
    }
    return(u1_t_pct);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/19/2018  TN       New.                                                                                               */
/*  1.1.0    10/12/2018  TN       vd_g_IllumiCfgMainStart and vd_g_IllumiCfgMainFinish were implemented.                             */
/*           10/15/2018  TN       u1_g_IllumiShtdwnOk was implemented.                                                               */
/*  1.2.0    04/13/2020  SM       Over Write function was implemented.                                                               */
/*  1.3.0    09/24/2020  SH       illumi_cfg v1.2.0 -> v1.3.0.                                                                       */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.0    02/01/2022  TA(M)    Change to decompose initialization function into Bon / Reset / Wakeup                              */
/*  2.2.0    02/15/2024  TH       for 19PFv3                                                                                         */
/*  2.3.0    01/23/2026  RS       Delete u1_g_IllumiShtdwnOk for BEV FF2.                                                            */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1  04/16/2024  SaH      Add calibration guard                                                                              */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*  * SM = Shota Maegawa, Denso Techno                                                                                               */
/*  * SH = Shota Higashide                                                                                                           */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TH = Taisuke Hirakawa, KSE                                                                                                     */
/*  * SaH  = Sae Hirose, Denso Techno                                                                                                */
/*  * RS   = Ryuki Sako, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
