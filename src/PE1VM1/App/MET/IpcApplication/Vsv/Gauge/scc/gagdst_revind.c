/* 2.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET : Rev Indicator                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_REVIND_C_MAJOR                    (2)
#define GAGDST_REVIND_C_MINOR                    (0)
#define GAGDST_REVIND_C_PATCH                    (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gagdst_revind_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GAGDST_REVIND_C_MAJOR != GAGDST_REVIND_H_MAJOR) || \
     (GAGDST_REVIND_C_MINOR != GAGDST_REVIND_H_MINOR) || \
     (GAGDST_REVIND_C_PATCH != GAGDST_REVIND_H_PATCH))
#error "gagdst_revind.c and gagdst_revind.h : source and header files are inconsistent!"
#endif

#if ((GAGDST_REVIND_C_MAJOR != GAGDST_REVIND_CFG_H_MAJOR) || \
     (GAGDST_REVIND_C_MINOR != GAGDST_REVIND_CFG_H_MINOR) || \
     (GAGDST_REVIND_C_PATCH != GAGDST_REVIND_CFG_H_PATCH))
#error "gagdst_revind.c and gagdst_revind_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_REVIND_HYS                           (200U)          /* RevIndicator OFF Hysteresis   :  200 rpm (LSB 1 rpm)          */

#define GAGDST_REVIND_TH_LOW_VAL                    (2000U)

#define GAGDST_REVIND_BIT_NUM                       (4U)            /* Revindicator status bit type                                  */
#define GAGDST_REVIND_BIT_INDOFF                    (0x00U)         /* Revindicator status bit : OFF                                 */
#define GAGDST_REVIND_BIT_INDFIX                    (0x01U)         /* Revindicator status bit : Fixed                               */
#define GAGDST_REVIND_BIT_INDOPT                    (0x02U)         /* Revindicator status bit : Optional                            */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1           u1_s_gagdst_revind_sts;                         /* Result of Rev Indicator decision                              */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_GagdstRevindJdg(const U2 u2_a_RPM, const U2 u2_a_ON_TH, const U2 u2_a_OFF_TH, const U1 u1_a_IND_STS, const U1 u1_a_BIT_ON);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_GagdstRevindInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstRevindInit(void)
{
    u1_s_gagdst_revind_sts = (U1)GAGDST_REVIND_OFF;
}

/*===================================================================================================================================*/
/*  void    vd_g_GagdstRevindMainTask(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstRevindUpdt(const U2 u2_a_SRC_CHK, const U2 u2_a_TRGT, const U2 u2_a_OW, const U1 u1_a_ESI)
{
    static const U1     u1_sp_GAGDST_REVIND_INDSTS[GAGDST_REVIND_BIT_NUM] = {
        (U1)GAGDST_REVIND_OFF,
        (U1)GAGDST_REVIND_FIXED_ON,
        (U1)GAGDST_REVIND_OPT_ON,
        (U1)GAGDST_REVIND_FIXED_ON
    };

    U1                  u1_t_ind_jdg;
    U2                  u2_t_rpm;
    U2                  u2_t_src_chk;
    U2                  u2_t_fix_th;
    U2                  u2_t_opt_th;
    U2                  u2_t_off_th;

    u2_t_src_chk = u2_a_SRC_CHK & (u2_g_GAGDST_REVIND_SRC_INV | u2_g_GAGDST_REVIND_SRC_UNK);

    if((u2_a_SRC_CHK & (U2)GAUGE_SRC_CHK_IGN_ON) == (U2)0U){
        u1_s_gagdst_revind_sts = (U1)GAGDST_REVIND_OFF;
    }
    else{
        u2_t_rpm = (U2)0U;
        if(u2_t_src_chk == (U2)0U){
            u2_t_rpm = u2_a_TRGT;
        }

        u2_t_fix_th = (U2)GAGDST_REVIND_TH_INV;
        u2_t_opt_th = (U2)GAGDST_REVIND_TH_INV;
        vd_g_GagdstRevindCfgTh(&u2_t_fix_th, &u2_t_opt_th);

        u1_t_ind_jdg = (U1)GAGDST_REVIND_BIT_INDOFF;

        if((u2_t_fix_th >= (U2)GAGDST_REVIND_TH_LOW_VAL) &&
           (u2_t_fix_th <  (U2)GAGDST_REVIND_TH_INV    )){
            u2_t_off_th  = u2_t_fix_th - (U2)GAGDST_REVIND_HYS;

            if((u2_t_opt_th >= (U2)GAGDST_REVIND_TH_LOW_VAL) &&
               (u2_t_opt_th <  (U2)GAGDST_REVIND_TH_INV    )){
                if(u2_t_opt_th >= u2_t_off_th){
                    u2_t_off_th = u2_t_opt_th - (U2)GAGDST_REVIND_HYS;
                }
            }

            u1_t_ind_jdg = u1_s_GagdstRevindJdg(u2_t_rpm, u2_t_fix_th, u2_t_off_th, (U1)GAGDST_REVIND_FIXED_ON, (U1)GAGDST_REVIND_BIT_INDFIX);
        }

        if((u2_t_opt_th >= (U2)GAGDST_REVIND_TH_LOW_VAL) &&
           (u2_t_opt_th <  (U2)GAGDST_REVIND_TH_INV    )){
            u2_t_off_th   = u2_t_opt_th - (U2)GAGDST_REVIND_HYS;
            u1_t_ind_jdg |= u1_s_GagdstRevindJdg(u2_t_rpm, u2_t_opt_th, u2_t_off_th, (U1)GAGDST_REVIND_OPT_ON,  (U1)GAGDST_REVIND_BIT_INDOPT);
        }

        if(u1_t_ind_jdg < (U1)GAGDST_REVIND_BIT_NUM){
            u1_s_gagdst_revind_sts = u1_sp_GAGDST_REVIND_INDSTS[u1_t_ind_jdg];
        }
        else{
            u1_s_gagdst_revind_sts = (U1)GAGDST_REVIND_OFF;
        }
    }
}

/*===================================================================================================================================*/
/*  U1      u1_g_GagdstRevindSts(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_GagdstRevindSts(void)
{
    return(u1_s_gagdst_revind_sts);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_GagdstRevindJdg(const U2 u2_a_RPM, const U2 u2_a_ON_TH, const U2 u2_a_OFF_TH, const U1 u1_a_IND_STS, const U1 u1_a_BIT_ON) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_GagdstRevindJdg(const U2 u2_a_RPM, const U2 u2_a_ON_TH, const U2 u2_a_OFF_TH, const U1 u1_a_IND_STS, const U1 u1_a_BIT_ON)
{
    U1                  u1_t_res_sts;

    u1_t_res_sts = (U1)GAGDST_REVIND_BIT_INDOFF;

    if(u2_a_RPM >= u2_a_ON_TH){
        u1_t_res_sts = u1_a_BIT_ON;
    }
    else if((u1_s_gagdst_revind_sts == u1_a_IND_STS) &&
            (u2_a_RPM               >= u2_a_OFF_TH )){
            u1_t_res_sts = u1_a_BIT_ON;
    }
    else{
        /* Nothing */
    }

    return(u1_t_res_sts);
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
/*  1.1.0     7/16/2020  HY       Apply the improvement of 775B-v131-r015 version.                                                   */
/*                                Apply the REVIND specification of 800B CV-R                                                        */
/*  2.0.0    06/08/2021  TK       Move from Engspd to Gauge.                                                                         */
/*  2.0.1    07/28/2021  TK       Renew.                                                                                             */
/*  2.0.2    11/15/1021  TK       Change Fixed Indicator Off Condition.                                                              */
/*                                                                                                                                   */
/*  * HY   = Hiroshige Yanase, DensoTechno                                                                                           */
/*  * TK   = Takanori Kuno, DensoTechno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
