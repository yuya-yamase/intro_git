/* 2.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*   Toyota IPC/MET :Engine Rotation Speed                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ENGSPD_RPM_C_MAJOR                       (2)
#define ENGSPD_RPM_C_MINOR                       (0)
#define ENGSPD_RPM_C_PATCH                       (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "engspd_rpm_cfg_private.h"
#include "engspd_varrz.h"

#include "vehspd_kmph.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ENGSPD_RPM_C_MAJOR != ENGSPD_RPM_H_MAJOR) || \
     (ENGSPD_RPM_C_MINOR != ENGSPD_RPM_H_MINOR) || \
     (ENGSPD_RPM_C_PATCH != ENGSPD_RPM_H_PATCH))
#error "engspd_rpm.c and engspd_rpm.h : source and header files are inconsistent!"
#endif

#if ((ENGSPD_RPM_C_MAJOR != ENGSPD_RPM_CFG_H_MAJOR) || \
     (ENGSPD_RPM_C_MINOR != ENGSPD_RPM_CFG_H_MINOR) || \
     (ENGSPD_RPM_C_PATCH != ENGSPD_RPM_CFG_H_PATCH))
#error "engspd_rpm.c and engspd_rpm_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ENGSPD_STOP_SPD_THRESHOLD                (175U)              /* 1.75 Km/h (LSB 0.01 Km/h)       */

#define ENGSPD_RPM_MIN                           (200U)              /* 200 rpm (LSB 1 rpm)             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1           u1_s_engspd_stsbit;        /* Engine speed status bit                   */
static U2           u2_s_engspd_rpm_fltrd;     /* Engine speed filtered (LSB 1 rpm)         */
static U4           u4_s_engspd_rpmsum_old;    /* Sum of RPM                                */
static U2           u2_s_engspd_rpmave_old;    /* Average of RPM                            */
static U1           u1_s_engspd_denom_old;     /* DENOM of the weighted average             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        void    vd_s_EngspdInit(void);
static        void    vd_s_EngspdOldRamClr(void);
static        U2      u2_s_EngspdRpmWghtAvg(const U2 u2_a_RPM);
static inline U1      u1_s_EngspdCalibU1MinChk(const U1 u1_a_CALIBID, const U1 u1_a_MIN, const U1 u1_a_DEF);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_EngspdBonInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_EngspdBonInit(void)
{
    vd_s_EngspdInit();
    vd_g_EngspdVarrzBonInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_EngspdRstwkInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_EngspdRstwkInit(void)
{
    vd_s_EngspdInit();
    vd_g_EngspdVarrzRstwkInit();
}
/*===================================================================================================================================*/
/*  void    vd_s_EngspdInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_EngspdInit(void)
{
    u1_s_engspd_stsbit     = (U1)ENGSPD_STSBIT_UNKNOWN;
    u2_s_engspd_rpm_fltrd  = (U2)0U;

    vd_s_EngspdOldRamClr();
}

/*===================================================================================================================================*/
/*  void    vd_g_EngspdMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_EngspdMainTask(void)
{
    U1                  u1_t_igon;
    U1                  u1_t_stsbit;
    U2                  u2_t_fltrd;
    U2                  u2_t_inst;

    u2_t_fltrd  = (U2)0U;

    u1_t_igon = u1_g_EngspdRpmCfgIgOn();

    if(u1_t_igon == (U1)TRUE){
        u2_t_inst   = (U2)0U;
        u1_t_stsbit = u1_g_EngspdRpmCfgRpmInst(&u2_t_inst) & ((U1)ENGSPD_STSBIT_INVALID | (U1)ENGSPD_STSBIT_UNKNOWN);

        if((u1_t_stsbit & (U1)ENGSPD_STSBIT_INVALID) != (U1)0U){
            u2_t_fltrd = u2_s_engspd_rpm_fltrd;     /* Keep Last            */
            vd_s_EngspdOldRamClr();
        }
        else if(u1_t_stsbit == (U1)ENGSPD_STSBIT_UNKNOWN){
            /* u2_t_fltrd = (U2)0U; */
            vd_s_EngspdOldRamClr();
        }
        else{
            if(u2_t_inst >= (U2)ENGSPD_RPM_MIN){
                u2_t_fltrd = u2_t_inst;
            }
            u2_t_fltrd = u2_s_EngspdRpmWghtAvg(u2_t_fltrd);
        }

        u2_s_engspd_rpm_fltrd = u2_t_fltrd;
        u1_s_engspd_stsbit    = u1_t_stsbit;
    }
    else{
        vd_s_EngspdInit();
    }
    vd_g_EngspdVarrzRzrpmUpdt();
}

/*===================================================================================================================================*/
/*  U1      u1_g_EngspdRpmFltrd(U2 * u2p_a_rpm)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_EngspdRpmFltrd(U2 * u2p_a_rpm)
{
    U1                  u1_t_unk;

    u1_t_unk = u1_s_engspd_stsbit & (U1)ENGSPD_STSBIT_UNKNOWN;
    if((u1_t_unk  == (U1)0U    ) &&
       (u2p_a_rpm != vdp_PTR_NA)){
        (*u2p_a_rpm) = u2_s_engspd_rpm_fltrd;
    }

    return(u1_s_engspd_stsbit);
}

/*===================================================================================================================================*/
/*  static void    vd_s_EngspdOldRamClr(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_EngspdOldRamClr(void)
{
    u4_s_engspd_rpmsum_old = (U4)0U;
    u2_s_engspd_rpmave_old = (U2)0U;

    u1_s_engspd_denom_old  = u1_s_EngspdCalibU1MinChk(u1_ENGSPD_CALIB_N2, u1_g_ENGSPD_CALIB_N2_MIN, u1_g_ENGSPD_CALIB_N2_DEF);
}

/*===================================================================================================================================*/
/*  static U2      u2_s_EngspdRpmWghtAvg(const U2 u2_a_RPM)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_EngspdRpmWghtAvg(const U2 u2_a_RPM)
{
    U4                  u4_t_ave_now;
    U4                  u4_t_sum_now;
    U2                  u2_t_vehspd;
    U1                  u1_t_sigstatus;
    U1                  u1_t_denom_now;
    U1                  u1_t_wghtave_n1;
    U1                  u1_t_wghtave_n2;
    U4                  u4_t_work;

    u2_t_vehspd    = (U2)0U;
    u1_t_sigstatus = u1_g_EngspdRpmCfgKmphInst(&u2_t_vehspd);
    if(u1_t_sigstatus != (U1)VEHSPD_STSBIT_VALID){
        u2_t_vehspd = (U2)0U;
    }

    u1_t_wghtave_n1 = u1_s_EngspdCalibU1MinChk(u1_ENGSPD_CALIB_N1, u1_g_ENGSPD_CALIB_N1_MIN, u1_g_ENGSPD_CALIB_N1_DEF);
    u1_t_wghtave_n2 = u1_s_EngspdCalibU1MinChk(u1_ENGSPD_CALIB_N2, u1_g_ENGSPD_CALIB_N2_MIN, u1_g_ENGSPD_CALIB_N2_DEF);

    if(u2_t_vehspd > (U2)ENGSPD_STOP_SPD_THRESHOLD){
        u1_t_denom_now = u1_t_wghtave_n1; /* Running */
    }
    else{
        u1_t_denom_now = u1_t_wghtave_n2; /* Stopping */
    }

    if(u1_t_denom_now == u1_s_engspd_denom_old){
        if(u4_s_engspd_rpmsum_old >= (U4)u2_s_engspd_rpmave_old){
            u4_t_work = u4_s_engspd_rpmsum_old - (U4)u2_s_engspd_rpmave_old;
        }
        else{
            u4_t_work = (U4)0U;
        }

        if(((U4)U4_MAX - u4_t_work) >= (U4)u2_a_RPM){
            u4_t_sum_now = u4_t_work + (U4)u2_a_RPM;
        }
        else{
            u4_t_sum_now = (U4)U4_MAX;
        }
    }
    else{
        if(((U4)U4_MAX / (U4)u1_t_denom_now) >= u4_s_engspd_rpmsum_old){
            u4_t_work = u4_s_engspd_rpmsum_old * (U4)u1_t_denom_now;
        }
        else{
            u4_t_work = (U4)U4_MAX;
        }

        if(u1_s_engspd_denom_old > (U1)0U){
            u4_t_work = u4_t_work / (U4)u1_s_engspd_denom_old;
        }
        else{
            u4_t_work = (U4)0U;
        }

        if(u4_t_work >= (U4)u2_s_engspd_rpmave_old){
            u4_t_work = u4_t_work - (U4)u2_s_engspd_rpmave_old;
        }
        else{
            u4_t_work = (U4)0U;
        }

        if(((U4)U4_MAX - u4_t_work) >= (U4)u2_a_RPM){
            u4_t_sum_now = u4_t_work + (U4)u2_a_RPM;
        }
        else{
            u4_t_sum_now = (U4)U4_MAX;
        }
    }

    u4_t_ave_now = u4_t_sum_now / (U4)u1_t_denom_now;

    if(u4_t_ave_now > (U4)U2_MAX){
        u4_t_ave_now = (U4)U2_MAX;
    }

    u1_s_engspd_denom_old  = u1_t_denom_now;
    u4_s_engspd_rpmsum_old = u4_t_sum_now;
    u2_s_engspd_rpmave_old = (U2)u4_t_ave_now;

    return(u2_s_engspd_rpmave_old);
}

/*===================================================================================================================================*/
/*  static inline U1    u1_s_EngspdCalibU1MinChk(const U1 u1_a_CALIBID, const U1 u1_a_MIN, const U1 u1_a_DEF)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_CALIBID                                                                                            */
/*                  const U1 u1_a_MIN                                                                                                */ 
/*                  const U1 u1_a_DEF                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U1    u1_s_EngspdCalibU1MinChk(const U1 u1_a_CALIBID, const U1 u1_a_MIN, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_CALIBID;
    if(u1_t_ret < u1_a_MIN){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     6/ 7/2018  AK       New.                                                                                               */
/*  1.1.0     2/28/2019  TN       Bug Fix : The status of source signal was not checked in order to calculate RPM in                 */
/*                                vd_g_EngspdMainTask.                                                                               */
/*  1.2.0     6/ 6/2019  TN       Bug Fix : Weight average was performed in spite of that it was not required if NE was less than    */
/*                                200 [rpm].                                                                                         */
/*  1.3.0     3/11/2020  HY       Add the new functions for output. u1_g_EngspdRevIndSts(), u1_g_EngspdRevPeak                       */
/*                                and u1_g_EngspdOffInd().                                                                           */
/*                                Modification of the decision of RPM Value from CAN signals.                                        */
/*                                Addition of the decision of pointer position for zero of tachometer.                               */
/*                                Addition of the calculation of the weighted average for RPM.                                       */
/*                                Addition of the decision of RevIND  Lighting or lights out.                                        */
/*  1.4.0     7/16/2020  HY       Apply the improvement of 775B-v131-r015 version.                                                   */
/*                                Apply the REVIND specification of 800B CV-R.                                                       */
/*  2.0.0    06/08/2021  TK       Move pointer zero processing to Gauge.                                                             */
/*  2.0.1    07/28/2021  TK       Renew.                                                                                             */
/*  2.0.2    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  ---------------------------------------------------------------------------------------------------*/
/* 19PFv3-1  12/19/2023  SH       Change reading calibration                                                                         */
/* 19PFv3-2  04/16/2024  SH       Add calibration guard                                                                              */
/* 19PFv3-3  05/16/2024  SH       Change calibration guard                                                                           */
/* 19PFv3-4  06/27/2024  TN(DT)   Delete Calibration Guard Process except for division by 0.                                         */
/* 19PFv3-5  07/12/2024  TN(DT)   Add Calibration Guard to Unify Vehicle Operation.                                                  */
/*                                                                                                                                   */
/*  * AK     = Aiko Kishino, Denso                                                                                                   */
/*  * TN     = Takashi Nagai, DENSO                                                                                                  */
/*  * HY     = Hiroshige Yanase, DensoTechno                                                                                         */
/*  * TK     = Takanori Kuno, DensoTechno                                                                                            */
/*  * TA(M)  = Teruyuki Anjima, NTT Data MSE                                                                                         */
/*  * SH     = Sae Hirose, DensoTechno                                                                                               */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
