/* 1.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* Hybrid System Indicator                                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DRVIND_HV_PCT_C_MAJOR                    (1)
#define DRVIND_HV_PCT_C_MINOR                    (5)
#define DRVIND_HV_PCT_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "drvind_hv_pct_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DRVIND_HV_PCT_C_MAJOR != DRVIND_HV_PCT_H_MAJOR) || \
     (DRVIND_HV_PCT_C_MINOR != DRVIND_HV_PCT_H_MINOR) || \
     (DRVIND_HV_PCT_C_PATCH != DRVIND_HV_PCT_H_PATCH))
#error "drvind_hv_pct.c and drvind_hv_pct.h : source and header files are inconsistent!"
#endif

#if ((DRVIND_HV_PCT_C_MAJOR != DRVIND_HV_PCT_CFG_H_MAJOR) || \
     (DRVIND_HV_PCT_C_MINOR != DRVIND_HV_PCT_CFG_H_MINOR) || \
     (DRVIND_HV_PCT_C_PATCH != DRVIND_HV_PCT_CFG_H_PATCH))
#error "drvind_hv_pct.c and drvind_hv_pct_cfg_private.h : source and header files are inconsistent!"
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
static S4       s4_s_drvind_hv_pct_mvsum;                                       /* The Sum of Moving Quantities                      */
static S2       s2_s_drvind_hv_pct_fltrd;                                       /* Moving Average Value                              */
static U1       u1_s_drvind_hv_smpl_oldest;                                     /* The Oldest Sample Value                           */

static S2       s2_s_drvind_hv_pct_inst;                                        /* Initial Signal Value                              */
static U1       u1_s_drvind_hv_hvcr_stsbit;                                     /* IECOHVCR Status                                   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_DrvIndHvFltrInit(const S2 s2_a_PCT);
static void    vd_s_DrvIndHvFltrdCal(const S2 s2_a_FLTRD, const S2 s2_a_INST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_DrvIndHvInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrvIndHvInit(void)
{
    vd_s_DrvIndHvFltrInit((S2)DRVIND_HV_PCT_INIT);

    s2_s_drvind_hv_pct_inst    = (S2)DRVIND_HV_PCT_INIT;
    u1_s_drvind_hv_hvcr_stsbit = (U1)DRVIND_HV_STSBIT_UNKNOWN;
}
/*===================================================================================================================================*/
/*  void    vd_g_DrvIndHvMainTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrvIndHvMainTask(void)
{
    S2                  s2_t_inst;                                              /* Initial Signal Value                              */
    S2                  s2_t_fltrd;                                             /* Moving Average Value                              */
    U1                  u1_t_igon;                                              /* Ignition on Status                                */
    U1                  u1_t_hvcr_stsbit;                                       /* IECOHVCR Status                                   */

    u1_t_igon = u1_g_DrvIndHvCfgIgOn();
    if(u1_t_igon == (U1)TRUE){

        s2_t_inst        = (S2)DRVIND_HV_PCT_INIT;
        u1_t_hvcr_stsbit = u1_g_DrvIndHvCfgComRxIECOHVCR(&s2_t_inst);

        if(((s2_t_inst <= (S2)DRVIND_HV_INV_MAX) && (s2_t_inst >= (S2)DRVIND_HV_INV_MIN)) ||
           (s2_t_inst == (S2)DRVIND_HV_PCT_MIN                                          )){
            s2_t_fltrd = (S2)DRVIND_HV_0_PCT;
        }
        else{
            s2_t_fltrd = s2_t_inst;
        }

        if(u1_t_hvcr_stsbit == (U1)DRVIND_HV_STSBIT_VALID){
            vd_s_DrvIndHvFltrdCal(s2_t_fltrd, s2_t_inst);
        }
        else{
            vd_s_DrvIndHvFltrInit((S2)DRVIND_HV_PCT_INIT);
            s2_s_drvind_hv_pct_inst = (S2)DRVIND_HV_PCT_INIT;
        }

        u1_s_drvind_hv_hvcr_stsbit = u1_t_hvcr_stsbit;
    }
    else{
        vd_g_DrvIndHvInit();
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_DrvIndHvFltrdCal(const S2 s2_a_FLTRD, const S2 s2_a_INST)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const S2 s2_a_FLTRD : Moving Average Value                                                                       */
/*                  const S2 s2_a_INST  : Initial Signal Value                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DrvIndHvFltrdCal(const S2 s2_a_FLTRD, const S2 s2_a_INST)
{
    S2                  s2_t_oldest;                                            /* The Oldest Sample Value                           */

    if(u1_s_drvind_hv_hvcr_stsbit != (U1)DRVIND_HV_STSBIT_VALID){
        vd_s_DrvIndHvFltrInit(s2_a_FLTRD);
    }
    else if(u1_g_DRVIND_HV_FLTR_MVAVGTIMS > (U1)1U){

        if(u1_s_drvind_hv_smpl_oldest >= u1_g_DRVIND_HV_FLTR_MVAVGTIMS){
            u1_s_drvind_hv_smpl_oldest = (U1)0U;
        }

        s2_t_oldest = s2_gp_drvind_hv_pct_smpl[u1_s_drvind_hv_smpl_oldest];
        s2_gp_drvind_hv_pct_smpl[u1_s_drvind_hv_smpl_oldest] = s2_a_FLTRD;

        s4_s_drvind_hv_pct_mvsum -= (S4)s2_t_oldest;
        s4_s_drvind_hv_pct_mvsum += (S4)s2_a_FLTRD;

        u1_s_drvind_hv_smpl_oldest++;                                           /* PRQA S 3383                                       */
        /* The maximum value of u1_g_DRVIND_HV_FLTR_MVAVGTIMS is 255.                                                                */
        /* Since u1_s_drvind_hv_smpl_oldest is determined whether it is larger than u1_g_DRVIND_HV_FLTR_MVAVGTIMS                    */
        /* it is not necessary to check the wraparound.                                                                              */

        s2_s_drvind_hv_pct_fltrd = (S2)(s4_s_drvind_hv_pct_mvsum / (S4)((U4)u1_g_DRVIND_HV_FLTR_MVAVGTIMS));
    }
    else{
        s2_s_drvind_hv_pct_fltrd = s2_a_FLTRD;
    }

    s2_s_drvind_hv_pct_inst = s2_a_INST;
}
/*===================================================================================================================================*/
/*  U1      u1_g_DrvIndHvPctInst(S2 * const s2p_a_PCT)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S2 * const s2p_a_PCT                  : Initial Signal Value                                                     */
/*  Return:         U1         u1_s_drvind_hv_hvcr_stsbit : IECOHVCR Status                                                          */
/*===================================================================================================================================*/
U1      u1_g_DrvIndHvPctInst(S2 * const s2p_a_PCT)
{
    U1                  u1_t_unk;                                               /* Unknown Status                                    */

    u1_t_unk = u1_s_drvind_hv_hvcr_stsbit & (U1)DRVIND_HV_STSBIT_UNKNOWN;
    if((u1_t_unk  == (U1)0U    ) &&
       (s2p_a_PCT != vdp_PTR_NA)){
        (*s2p_a_PCT) = s2_s_drvind_hv_pct_inst;
    }

    return (u1_s_drvind_hv_hvcr_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DrvIndHvPctFltrd(S2 * const s2p_a_PCT)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S2 * const s2p_a_PCT                  : Moving Average Value                                                     */
/*  Return:         U1         u1_s_drvind_hv_hvcr_stsbit : IECOHVCR Status                                                          */
/*===================================================================================================================================*/
U1      u1_g_DrvIndHvPctFltrd(S2 * const s2p_a_PCT)
{
    U1                  u1_t_unk;                                               /* Unknown Status                                    */

    u1_t_unk = u1_s_drvind_hv_hvcr_stsbit & (U1)DRVIND_HV_STSBIT_UNKNOWN;
    if((u1_t_unk  == (U1)0U    ) &&
       (s2p_a_PCT != vdp_PTR_NA)){
        (*s2p_a_PCT) = s2_s_drvind_hv_pct_fltrd;
    }

    return (u1_s_drvind_hv_hvcr_stsbit);
}

/*===================================================================================================================================*/
/*  static void    vd_s_DrvIndHvFltrInit(const S2 s2_a_PCT)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const S2 s2_a_PCT : HV Percent                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DrvIndHvFltrInit(const S2 s2_a_PCT)
{
    U4                  u4_t_lpcnt;                                             /* Loop Counter                                      */

    s4_s_drvind_hv_pct_mvsum   = (S4)s2_a_PCT * (S4)((U4)u1_g_DRVIND_HV_FLTR_MVAVGTIMS);
    s2_s_drvind_hv_pct_fltrd   = s2_a_PCT;
    u1_s_drvind_hv_smpl_oldest = (U1)U1_MAX;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_DRVIND_HV_FLTR_MVAVGTIMS; u4_t_lpcnt++){
        s2_gp_drvind_hv_pct_smpl[u4_t_lpcnt] = s2_a_PCT;
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
/*  1.0.0             2020.02.19    TA        New.                                                                                   */
/*  1.1.0             2020.07.10    TA        Adding diagnosis.                                                                      */
/*                    2020.07.29    TA        Response to QAC (STMIF).                                                               */
/*                    2020.10.07    TA        Response to QAC (const declaration grant).                                             */
/*  1.1.1             2020.12.01    TA        Add Comment.                                                                           */
/*                                            Set invalid value when status is invalid.                                              */
/*                                            Delete redundant s2_s_drvind_hv_pct_inst writes                                        */
/*  1.2.0             2021.01.15    TA        Changing Moving Average Processing for Invalid Data.                                   */
/*  1.3.0             2021.09.22    TA        Addition of Eco-Accelerator Guide.                                                     */
/*  1.3.1             2021.10.25    TA        Change the definition of the null pointer used.(BSW v115_r007)                         */
/*                    2021.11.22    TA        Secure Coding Support.                                                                 */
/*  1.4.0             2024.04.16    YR        Change the Moving Average Number                                                       */
/*  1.5.0             2024.05.24    YR        Removed the processing for IECOHVTH                                                    */
/*                                                                                                                                   */
/*  * TA = Tsubasa Aki, Denso Techno                                                                                                 */
/*  * YR = Yhana Regalario, DTPH                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
