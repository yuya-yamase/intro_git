/* 2.0.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET : Revpeak                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_REVPEAK_C_MAJOR                   (2)
#define GAGDST_REVPEAK_C_MINOR                   (0)
#define GAGDST_REVPEAK_C_PATCH                   (3)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gagdst_revpeak_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GAGDST_REVPEAK_C_MAJOR != GAGDST_REVPEAK_H_MAJOR) || \
     (GAGDST_REVPEAK_C_MINOR != GAGDST_REVPEAK_H_MINOR) || \
     (GAGDST_REVPEAK_C_PATCH != GAGDST_REVPEAK_H_PATCH))
#error "gagdst_revpeak.c and gagdst_revpeak.h : source and header files are inconsistent!"
#endif

#if ((GAGDST_REVPEAK_C_MAJOR != GAGDST_REVPEAK_CFG_H_MAJOR) || \
     (GAGDST_REVPEAK_C_MINOR != GAGDST_REVPEAK_CFG_H_MINOR) || \
     (GAGDST_REVPEAK_C_PATCH != GAGDST_REVPEAK_CFG_H_PATCH))
#error "gagdst_revpeak.c and gagdst_revpeak_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_REVPEAK_MAIN_TICK                 (20U)

#define GAGDST_REVPEAK_RPMBUFNUM                 (520U  / GAGDST_REVPEAK_MAIN_TICK)         /* (Past:500ms + latest:20ms) / 20ms     */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U2      u2_s_gagdst_revpeak_cnttim;                              /* Elapsed time since displaying Revpeak                    */
static  U2      u2_s_gagdst_revpeak_dsptim;                              /* display time                                             */
static  U2      u2_s_gagdst_revpeak_dsprpm;                              /* RPM displaying as Revpeak                                */

static  U2      u2_sp_gagdst_revpeak_rpmbuf[GAGDST_REVPEAK_RPMBUFNUM];   /* RPM history on 500ms duration                            */

static  U1      u1_s_gagdst_revpeak_idx_latest;                          /* Latest index of RPM history                              */
static  U1      u1_s_gagdst_revpeak_idx_peak;                            /* Index of Peak RPM in RPM history                         */
static  U2      u2_s_gagdst_revpeak_rpm_btm;                             /* Bottom RPM(Latest)                                       */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1    u1_s_GagdstRevpeakPeakUpdt(void);
static  U2    u2_s_GagdstRevpeakBtmUpdt(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_GagdstRevPeakInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstRevpeakInit(void)
{
    U2                  u2_t_dsptim;
    U4                  u4_t_lpcnt;

    u2_s_gagdst_revpeak_cnttim = (U2)U2_MAX;
    u2_s_gagdst_revpeak_dsprpm = (U2)0U;

    u2_t_dsptim = u2_g_GagdstRevpeakCfgDispTime_1ms();
    u2_s_gagdst_revpeak_dsptim = u2_t_dsptim / (U2)GAGDST_REVPEAK_MAIN_TICK;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)GAGDST_REVPEAK_RPMBUFNUM; u4_t_lpcnt++){
        u2_sp_gagdst_revpeak_rpmbuf[u4_t_lpcnt] = (U2)0U;
    }

    u1_s_gagdst_revpeak_idx_latest = (U1)0U;
    u1_s_gagdst_revpeak_idx_peak   = (U1)0U;
    u2_s_gagdst_revpeak_rpm_btm    = (U2)0U;
}

/*===================================================================================================================================*/
/*  void    vd_g_GagdstRevpeakUpdt(const U2 u2_a_SRC_CHK, const U2 u2_a_TRGT, const U2 u2_a_OW, const U1 u1_a_ESI)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstRevpeakUpdt(const U2 u2_a_SRC_CHK, const U2 u2_a_TRGT, const U2 u2_a_OW, const U1 u1_a_ESI)
{
    U1                  u1_t_cstm_on;
    U2                  u2_t_setprm;
    U2                  u2_t_disp_hys;
    U2                  u2_t_noise_hys;
    U2                  u2_t_rpm_latest;
    U2                  u2_t_rpm_peak;
    U2                  u2_t_src_chk;
    U2                  u2_t_dsptim;

    u1_t_cstm_on   = u1_g_GagdstRevpeakCfgCstmOn();

    u2_t_dsptim = u2_g_GagdstRevpeakCfgDispTime_1ms();
    u2_s_gagdst_revpeak_dsptim = u2_t_dsptim / (U2)GAGDST_REVPEAK_MAIN_TICK;

    if(((u2_a_SRC_CHK & (U2)GAUGE_SRC_CHK_IGN_ON) == (U2)0U  ) ||
       (u1_t_cstm_on                              != (U1)TRUE)){
        vd_g_GagdstRevpeakInit();
    }
    else{
        u2_t_src_chk = u2_a_SRC_CHK & (u2_g_GAGDST_REVPEAK_SRC_INV | u2_g_GAGDST_REVPEAK_SRC_UNK);
        u2_t_rpm_latest = (U2)0U;
        if(u2_t_src_chk == (U2)0U){
            u2_t_rpm_latest = u2_a_TRGT;
        }

        u2_t_rpm_peak = u2_sp_gagdst_revpeak_rpmbuf[u1_s_gagdst_revpeak_idx_peak];

        u2_sp_gagdst_revpeak_rpmbuf[u1_s_gagdst_revpeak_idx_latest] = u2_t_rpm_latest;

        if((u2_t_rpm_latest                >  u2_t_rpm_peak               ) ||
           (u1_s_gagdst_revpeak_idx_latest == u1_s_gagdst_revpeak_idx_peak)){
            u1_s_gagdst_revpeak_idx_peak = u1_s_GagdstRevpeakPeakUpdt();
            u2_s_gagdst_revpeak_rpm_btm  = u2_s_GagdstRevpeakBtmUpdt();
        }

        u2_t_setprm    = (U2)GAGDST_REVPEAK_PRM_INV;
        u2_t_disp_hys  = (U2)GAGDST_REVPEAK_PRM_INV;
        u2_t_noise_hys = (U2)GAGDST_REVPEAK_PRM_INV;
        vd_g_GagdstRevpeakCfgPrm(&u2_t_setprm, &u2_t_disp_hys, &u2_t_noise_hys);

        if(u2_s_gagdst_revpeak_cnttim < (U2)U2_MAX){
            u2_s_gagdst_revpeak_cnttim++;
        }

        if(u2_s_gagdst_revpeak_cnttim <= u2_s_gagdst_revpeak_dsptim){
            if(u2_t_rpm_latest > u2_s_gagdst_revpeak_dsprpm){
                u2_s_gagdst_revpeak_cnttim = (U2)U2_MAX;
                u2_s_gagdst_revpeak_dsprpm = (U2)0U;
            }
        }
        else{
            if((u2_t_rpm_latest                                                                           >= u2_t_setprm   ) &&
               ((u2_sp_gagdst_revpeak_rpmbuf[u1_s_gagdst_revpeak_idx_peak] - u2_t_rpm_latest            ) >= u2_t_disp_hys ) &&
               ((u2_sp_gagdst_revpeak_rpmbuf[u1_s_gagdst_revpeak_idx_peak] - u2_s_gagdst_revpeak_rpm_btm) >= u2_t_noise_hys)){
                u2_s_gagdst_revpeak_cnttim  = (U2)0U;
                u2_s_gagdst_revpeak_dsprpm  = u2_sp_gagdst_revpeak_rpmbuf[u1_s_gagdst_revpeak_idx_peak];
                u2_s_gagdst_revpeak_rpm_btm = u2_sp_gagdst_revpeak_rpmbuf[u1_s_gagdst_revpeak_idx_peak];
            }
            else{
                u2_s_gagdst_revpeak_dsprpm = (U2)0U;
            }
        }

        if(u1_s_gagdst_revpeak_idx_latest < (U1)U1_MAX){
            u1_s_gagdst_revpeak_idx_latest++;
        }

        if(u1_s_gagdst_revpeak_idx_latest >= (U1)GAGDST_REVPEAK_RPMBUFNUM){
            u1_s_gagdst_revpeak_idx_latest = (U1)0U;
        }
    }
}

/*===================================================================================================================================*/
/*  U1      u1_g_GagdstRevpeakRpm(U2 * u2p_a_rev_dsprpm)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_GagdstRevpeakRpm(U2 * u2p_a_rev_dsprpm)
{
    U1                  u1_t_revpeak_on;

    u1_t_revpeak_on = (U1)FALSE;

    if((u2p_a_rev_dsprpm           != vdp_PTR_NA                ) &&
       (u2_s_gagdst_revpeak_cnttim <= u2_s_gagdst_revpeak_dsptim)){
            u1_t_revpeak_on     = (U1)TRUE;
            (*u2p_a_rev_dsprpm) = u2_s_gagdst_revpeak_dsprpm;
    }

    return(u1_t_revpeak_on);
}

/*===================================================================================================================================*/
/*  static  U1    u1_s_GagdstRevpeakPeakUpdt(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1    u1_s_GagdstRevpeakPeakUpdt(void)
{
    U1                  u1_t_peak_idx;
    U2                  u2_t_peak_rpm;
    U4                  u4_t_lpcnt;

    u1_t_peak_idx = u1_s_gagdst_revpeak_idx_peak;
    u2_t_peak_rpm = (U2)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)GAGDST_REVPEAK_RPMBUFNUM; u4_t_lpcnt++){
        if(u2_sp_gagdst_revpeak_rpmbuf[u4_t_lpcnt] >= u2_t_peak_rpm){
            u1_t_peak_idx = (U1)u4_t_lpcnt;
            u2_t_peak_rpm = u2_sp_gagdst_revpeak_rpmbuf[u4_t_lpcnt];
        }
    }

    return(u1_t_peak_idx);
}

/*===================================================================================================================================*/
/*  static  U2    u2_s_GagdstRevpeakBtmUpdt(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2    u2_s_GagdstRevpeakBtmUpdt(void)
{
    U1                  u1_t_base_idx;
    U1                  u1_t_search_num;
    U2                  u2_t_btm_rpm;
    U4                  u4_t_lpcnt;
    U4                  u4_t_idx;

    u1_t_base_idx = u1_s_gagdst_revpeak_idx_latest + (U1)1U;
    if(u1_t_base_idx >= (U1)GAGDST_REVPEAK_RPMBUFNUM){
        u1_t_base_idx = (U1)0U;
    }

    if(u1_s_gagdst_revpeak_idx_peak >= u1_t_base_idx){
        u1_t_search_num = u1_s_gagdst_revpeak_idx_peak - u1_t_base_idx;
    }
    else{
        u1_t_search_num = ((U1)GAGDST_REVPEAK_RPMBUFNUM - u1_t_base_idx) + u1_s_gagdst_revpeak_idx_peak;
    }

    u2_t_btm_rpm = u2_s_gagdst_revpeak_rpm_btm;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_t_search_num; u4_t_lpcnt++){
        if(((U4)U4_MAX - (U4)u1_t_base_idx) >= u4_t_lpcnt){
            u4_t_idx = (U4)u1_t_base_idx + u4_t_lpcnt;
        }
        else{
            u4_t_idx = (U4)u1_t_base_idx;
        }
        u4_t_idx %= (U4)GAGDST_REVPEAK_RPMBUFNUM;

        if(u2_sp_gagdst_revpeak_rpmbuf[u4_t_idx] < u2_t_btm_rpm){
            u2_t_btm_rpm = u2_sp_gagdst_revpeak_rpmbuf[u4_t_idx];
        }
    }

    return(u2_t_btm_rpm);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/20/2020  HY       New.                                                                                               */
/*  1.1.0     7/ 7/2020  HY       Implement the RevPeak decision logic                                                               */
/*  2.0.0    06/08/2021  TK       Move from Engspd to Gauge.                                                                         */
/*  2.0.1    07/28/2021  TK       Renew.                                                                                             */
/*  2.0.2    09/30/2021  TK       The display time has been configured.                                                              */
/*  2.0.3    10/18/2021  TK       Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*                                                                                                                                   */
/*  * HY   = Hiroshige Yanase, DensoTechno                                                                                           */
/*  * TK   = Takanori Kuno, DensoTechno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
