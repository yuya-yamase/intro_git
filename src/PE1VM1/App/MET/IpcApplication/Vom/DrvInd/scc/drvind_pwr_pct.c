/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* Power Indicator                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DRVIND_PWR_PCT_C_MAJOR                    (1)
#define DRVIND_PWR_PCT_C_MINOR                    (0)
#define DRVIND_PWR_PCT_C_PATCH                    (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "drvind_pwr_pct_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DRVIND_PWR_PCT_C_MAJOR != DRVIND_PWR_PCT_H_MAJOR) || \
     (DRVIND_PWR_PCT_C_MINOR != DRVIND_PWR_PCT_H_MINOR) || \
     (DRVIND_PWR_PCT_C_PATCH != DRVIND_PWR_PCT_H_PATCH))
#error "drvind_pwr_pct.c and drvind_pwr_pct.h : source and header files are inconsistent!"
#endif

#if ((DRVIND_PWR_PCT_C_MAJOR != DRVIND_PWR_PCT_CFG_H_MAJOR) || \
     (DRVIND_PWR_PCT_C_MINOR != DRVIND_PWR_PCT_CFG_H_MINOR) || \
     (DRVIND_PWR_PCT_C_PATCH != DRVIND_PWR_PCT_CFG_H_PATCH))
#error "drvind_pwr_pct.c and drvind_pwr_pct_cfg_private.h : source and header files are inconsistent!"
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
static S4       s4_s_drvind_pwr_pct_mvsum;                                      /* The Sum of Moving Quantities                      */
static S2       s2_s_drvind_pwr_pct_fltrd;                                      /* Moving Average Value                              */
static U1       u1_s_drvind_pwr_smpl_oldest;                                    /* The Oldest Sample Value                           */

static S2       s2_s_drvind_pwr_pct_inst;                                       /* Initial Signal Value                              */
static U1       u1_s_drvind_evcr_stsbit;                                        /* PMEVCR Status                                     */

static S1       s1_s_drvind_pwr_pct_chgth;                                      /* Limit Regenerative Value                          */
static U1       u1_s_drvind_chgth_stsbit;                                       /* PMCHGTH Status                                    */

static U2       u2_s_drvind_pwr_pct_pwrth;                                      /* Limit Output Value                                */
static U1       u1_s_drvind_pwrth_stsbit;                                       /* PMPWRTH Status                                    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_DrvIndPwrFltrInit(const S2 s2_a_PCT);
static void    vd_s_DrvIndPwrEvcrSigChk(S2 * const s2p_a_FLTRD, S2 * const s2p_a_INST);
static void    vd_s_DrvIndPwrFltrdCal(const S2 s2_a_FLTRD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_DrvIndPwrInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrvIndPwrInit(void)
{
    vd_s_DrvIndPwrFltrInit((S2)DRVIND_PWR_PCT_INIT);

    s2_s_drvind_pwr_pct_inst  = (S2)DRVIND_PWR_PCT_INIT;
    s1_s_drvind_pwr_pct_chgth = (S1)DRVIND_PWR_CHGTH_INIT;
    u2_s_drvind_pwr_pct_pwrth = (U2)DRVIND_PWR_PWRTH_INIT;
    u1_s_drvind_evcr_stsbit   = (U1)DRVIND_PWR_STSBIT_UNKNOWN;
    u1_s_drvind_chgth_stsbit  = (U1)DRVIND_PWR_STSBIT_UNKNOWN;
    u1_s_drvind_pwrth_stsbit  = (U1)DRVIND_PWR_STSBIT_UNKNOWN;
}
/*===================================================================================================================================*/
/*  void    vd_g_DrvIndPwrMainTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrvIndPwrMainTask(void)
{
    S2                  s2_t_fltrd;                                             /* Moving Average Value                              */
    S2                  s2_t_inst;                                              /* Initial Signal Value                              */
    S1                  s1_t_chgth;                                             /* Limit Regenerative Value                          */
    U2                  u2_t_pwrth;                                             /* Limit Output Value                                */
    U1                  u1_t_igon;                                              /* Ignition on Status                                */
    U1                  u1_t_evcr_stsbit;                                       /* PMEVCR Status                                     */
    U1                  u1_t_chgth_stsbit;                                      /* PMCHGTH Status                                    */
    U1                  u1_t_pwrth_stsbit;                                      /* PMPWRTH Status                                    */

    u1_t_igon = u1_g_DrvIndPwrCfgIgOn();
    if(u1_t_igon == (U1)TRUE){

        s2_t_fltrd        = (S2)DRVIND_PWR_PCT_INIT;
        s2_t_inst         = (S2)DRVIND_PWR_PCT_INIT;
        s1_t_chgth        = (S1)DRVIND_PWR_CHGTH_INIT;
        u2_t_pwrth        = (U2)DRVIND_PWR_PWRTH_INIT;

        u1_t_evcr_stsbit  = u1_g_DrvIndPwrCfgComRxPMEVCR(&s2_t_inst);
        u1_t_chgth_stsbit = u1_g_DrvIndPwrCfgComRxPMCHGTH(&s1_t_chgth);
        u1_t_pwrth_stsbit = u1_g_DrvIndPwrCfgComRxPMPWRTH(&u2_t_pwrth);

        if(u1_t_evcr_stsbit == (U1)DRVIND_PWR_STSBIT_VALID){
            vd_s_DrvIndPwrEvcrSigChk(&s2_t_fltrd, &s2_t_inst);
            vd_s_DrvIndPwrFltrdCal(s2_t_fltrd);
            s2_s_drvind_pwr_pct_inst = s2_t_inst;
        }
        else{
            vd_s_DrvIndPwrFltrInit((S2)DRVIND_PWR_PCT_INIT);
            s2_s_drvind_pwr_pct_inst = (S2)DRVIND_PWR_PCT_INIT;
        }

        if(u1_t_chgth_stsbit != (U1)DRVIND_PWR_STSBIT_VALID){
            s1_t_chgth               = (S1)DRVIND_PWR_CHGTH_INIT;
        }

        if(u1_t_pwrth_stsbit != (U1)DRVIND_PWR_STSBIT_VALID){
            u2_t_pwrth               = (U2)DRVIND_PWR_PWRTH_INIT;
        }

        s1_s_drvind_pwr_pct_chgth = s1_t_chgth;
        u2_s_drvind_pwr_pct_pwrth = u2_t_pwrth;
        u1_s_drvind_evcr_stsbit   = u1_t_evcr_stsbit;
        u1_s_drvind_chgth_stsbit  = u1_t_chgth_stsbit;
        u1_s_drvind_pwrth_stsbit  = u1_t_pwrth_stsbit;
    }
    else{
        vd_g_DrvIndPwrInit();
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_DrvIndPwrEvcrSigChk(S2 * const s2p_a_FLTRD, S2 * const s2p_a_INST)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S2 * const s2p_a_FLTRD : Moving Average Value                                                                    */
/*                  S2 * const s2p_a_INST  : Initial Signal Value                                                                    */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DrvIndPwrEvcrSigChk(S2 * const s2p_a_FLTRD, S2 * const s2p_a_INST)
{
    if(((*s2p_a_INST) <= (S2)DRVIND_PWR_PCT_MAX) && ((*s2p_a_INST) >= (S2)DRVIND_PWR_PCT_MIN)){
        if((((*s2p_a_INST) <= (S2)DRVIND_PWR_PCT_INV_MAX) && ((*s2p_a_INST) >= (S2)DRVIND_PWR_PCT_INV_MIN)) ||
           ((*s2p_a_INST)  == (S2)DRVIND_PWR_PCT_MIN                                                      )){
            (*s2p_a_FLTRD) = (S2)DRVIND_PWR_PCT_0;
        }
        else{
            (*s2p_a_FLTRD) = (*s2p_a_INST);
        }
    }
    else{
        (*s2p_a_FLTRD) = (S2)DRVIND_PWR_PCT_0;
        (*s2p_a_INST)  = (S2)DRVIND_PWR_PCT_0;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_DrvIndPwrFltrdCal(const S2 s2_a_FLTRD)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const S2 s2_a_FLTRD : Moving Average Value                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DrvIndPwrFltrdCal(const S2 s2_a_FLTRD)
{
    S2                  s2_t_oldest;                                            /* The Oldest Sample Value                           */

    if(u1_s_drvind_evcr_stsbit != (U1)DRVIND_PWR_STSBIT_VALID){
        vd_s_DrvIndPwrFltrInit(s2_a_FLTRD);
    }
    else if(u1_g_DRVIND_PWR_FLTR_MVAVGTIMS > (U1)1U){

        if(u1_s_drvind_pwr_smpl_oldest >= u1_g_DRVIND_PWR_FLTR_MVAVGTIMS){
            u1_s_drvind_pwr_smpl_oldest = (U1)0U;
        }

        s2_t_oldest = s2_gp_drvind_pwr_pct_smpl[u1_s_drvind_pwr_smpl_oldest];
        s2_gp_drvind_pwr_pct_smpl[u1_s_drvind_pwr_smpl_oldest] = s2_a_FLTRD;

        s4_s_drvind_pwr_pct_mvsum -= (S4)s2_t_oldest;
        s4_s_drvind_pwr_pct_mvsum += (S4)s2_a_FLTRD;

        u1_s_drvind_pwr_smpl_oldest++;                                           /* PRQA S 3383                                      */
        /* The maximum value of u1_g_DRVIND_PWR_FLTR_MVAVGTIMS is 255.                                                               */
        /* Since u1_s_drvind_hv_smpl_oldest is determined whether it is larger than u1_g_DRVIND_PWR_FLTR_MVAVGTIMS                   */
        /* it is not necessary to check the wraparound.                                                                              */

        s2_s_drvind_pwr_pct_fltrd = (S2)(s4_s_drvind_pwr_pct_mvsum / (S4)((U4)u1_g_DRVIND_PWR_FLTR_MVAVGTIMS));
    }
    else{
        s2_s_drvind_pwr_pct_fltrd = s2_a_FLTRD;
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_DrvIndPwrPctInst(S2 * const s2p_a_PCT)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S2 * const s2p_a_PCT               : Initial Signal Value                                                        */
/*  Return:         U1         u1_s_drvind_evcr_stsbit : PMEVCR Status                                                               */
/*===================================================================================================================================*/
U1      u1_g_DrvIndPwrPctInst(S2 * const s2p_a_PCT)
{
    U1                  u1_t_unk;                                               /* Unknown Status                                    */

    u1_t_unk = u1_s_drvind_evcr_stsbit & (U1)DRVIND_PWR_STSBIT_UNKNOWN;
    if((u1_t_unk  == (U1)0U    ) &&
       (s2p_a_PCT != vdp_PTR_NA)){
        (*s2p_a_PCT) = s2_s_drvind_pwr_pct_inst;
    }

    return (u1_s_drvind_evcr_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DrvIndPwrPctFltrd(S2 * const s2p_a_PCT)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S2 * const s2p_a_PCT               : Moving Average Value                                                        */
/*  Return:         U1         u1_s_drvind_evcr_stsbit : PMEVCR Status                                                               */
/*===================================================================================================================================*/
U1      u1_g_DrvIndPwrPctFltrd(S2 * const s2p_a_PCT)
{
    U1                  u1_t_unk;                                               /* Unknown Status                                    */

    u1_t_unk = u1_s_drvind_evcr_stsbit & (U1)DRVIND_PWR_STSBIT_UNKNOWN;
    if((u1_t_unk  == (U1)0U    ) &&
       (s2p_a_PCT != vdp_PTR_NA)){
        (*s2p_a_PCT) = s2_s_drvind_pwr_pct_fltrd;
    }

    return (u1_s_drvind_evcr_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DrvIndPwrPctChgth(S1 * const s1p_a_PCT)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S1 * const s1p_a_PCT                : Limit Regenerative Value                                                   */
/*  Return:         U1         u1_s_drvind_chgth_stsbit : PMCHGTH Status                                                             */
/*===================================================================================================================================*/
U1      u1_g_DrvIndPwrPctChgth(S1 * const s1p_a_PCT)
{
    U1                  u1_t_unk;                                               /* Unknown Status                                    */

    u1_t_unk = u1_s_drvind_chgth_stsbit & (U1)DRVIND_PWR_STSBIT_UNKNOWN;
    if((u1_t_unk  == (U1)0U    ) &&
       (s1p_a_PCT != vdp_PTR_NA)){
        (*s1p_a_PCT) = s1_s_drvind_pwr_pct_chgth;
    }

    return (u1_s_drvind_chgth_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DrvIndPwrPctPwrth(U2 * const u2p_a_PCT)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2 * const s2p_a_PCT                : Limit Output Value                                                         */
/*  Return:         U1         u1_s_drvind_pwrth_stsbit : PMPWRTH Status                                                             */
/*===================================================================================================================================*/
U1      u1_g_DrvIndPwrPctPwrth(U2 * const u2p_a_PCT)
{
    U1                  u1_t_unk;                                               /* Unknown Status                                    */

    u1_t_unk = u1_s_drvind_pwrth_stsbit & (U1)DRVIND_PWR_STSBIT_UNKNOWN;
    if((u1_t_unk  == (U1)0U    ) &&
       (u2p_a_PCT != vdp_PTR_NA)){
        (*u2p_a_PCT) = u2_s_drvind_pwr_pct_pwrth;
    }

    return (u1_s_drvind_pwrth_stsbit);
}
/*===================================================================================================================================*/
/*  static void    vd_s_DrvIndPwrFltrInit(const S2 s2_a_PCT)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const S2 s2_a_PCT : PWR Percent                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DrvIndPwrFltrInit(const S2 s2_a_PCT)
{
    U4                  u4_t_lpcnt;                                             /* Loop Counter                                      */

    s4_s_drvind_pwr_pct_mvsum   = (S4)s2_a_PCT * (S4)((U4)u1_g_DRVIND_PWR_FLTR_MVAVGTIMS);
    s2_s_drvind_pwr_pct_fltrd   = s2_a_PCT;
    u1_s_drvind_pwr_smpl_oldest = (U1)U1_MAX;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_DRVIND_PWR_FLTR_MVAVGTIMS; u4_t_lpcnt++){
        s2_gp_drvind_pwr_pct_smpl[u4_t_lpcnt] = s2_a_PCT;
    }
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version           Date          Author    Change Description                                                                     */
/*  --------------    ----------    ------    -------------------------------------------------------------------------------------  */
/*  1.0.0             2021.02.16    TA        New.                                                                                   */
/*  1.0.1             2022.02.01    TA        Change the definition of the null pointer used.(BSW v115_r008).                        */
/*                    2022.02.17    TA        Secure Coding Support.                                                                 */
/*                                                                                                                                   */
/*  * TA = Tsubasa Aki, Denso Techno                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
