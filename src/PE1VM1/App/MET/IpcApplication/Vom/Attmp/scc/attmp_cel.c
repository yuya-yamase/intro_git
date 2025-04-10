/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Automatic Transmission Oil Temperature                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ATTMP_CEL_C_MAJOR                       (1)
#define ATTMP_CEL_C_MINOR                       (1)
#define ATTMP_CEL_C_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "attmp_cel_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ATTMP_CEL_C_MAJOR != ATTMP_CEL_H_MAJOR) || \
     (ATTMP_CEL_C_MINOR != ATTMP_CEL_H_MINOR) || \
     (ATTMP_CEL_C_PATCH != ATTMP_CEL_H_PATCH))
#error "attmp_cel.c and attmp_cel.h : source and header files are inconsistent!"
#endif

#if ((ATTMP_CEL_C_MAJOR != ATTMP_CEL_CFG_H_MAJOR) || \
     (ATTMP_CEL_C_MINOR != ATTMP_CEL_CFG_H_MINOR) || \
     (ATTMP_CEL_C_PATCH != ATTMP_CEL_CFG_H_PATCH))
#error "attmpl_cel.c and attmp_cel_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ATTMP_FLTR_STS_INACT                    (0U)
#define ATTMP_FLTR_STS_ACT                      (1U)

#define ATTMP_CEL_OFFSET_B_THOCL_0P001          (273150U - 40000U) /* -40.000[cel]                                                   */

#define ATTMP_FLTR_MVAVG_TMS_MAX                (4U)
#define ATTMP_DIV_CAL_TO_OUT                    (10U)
#define ATTMP_0P001_MAX                         (552525U)          /* ((511 * 320 * 1000) / (256 * 2)) + (273150 - 40000) = 552,525. */

#define ATTMP_B_THOCL_VLD_MAX                   (511U)             /* 9bit data max                                                  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ATTMP_CNV_LSB_TO_0P001(s)                (((U4)(s) * 320U * 1000U) / (2U * 256U))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1       u1_s_attmp_stsbit;      /* Status of Automatic Transmission Oil Temperature                                          */
static U2       u2_s_attmp_cel_fltrd;   /* Automatic Transmission Oil Temperature (filtered)  LSB:0.01[cel] Offset:-273.15[cel]      */

static U1       u1_s_attmp_fltr_ctl;                                /* Filtering control status                                      */
static U4       u4_sp_attmp_fltr_smpl[ATTMP_FLTR_MVAVG_TMS_MAX];    /* The oil temperature samples for filtering                     */
static U1       u1_s_attmp_fltr_pos_oldest;                         /* The oldest index of the oil temperature samples               */
static U1       u1_s_attmp_fltr_rxcnt;                              /* B_THOCL rx event counter for filtering                        */
static U4       u4_s_attmp_fltr_sum;                                /* Sum of the oil temperature samples                            */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2       u2_s_AttmpFltrCel(const U2 u2_a_B_THOCL, const U1 u1_a_RXCNT);
static void     vd_s_AttmpMvAvgInit(const U4 u4_a_0P001CEL);
static U2       u2_s_AttmpMvAvgUpdt(const U4 u4_a_0P001CEL);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AttmpInit(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AttmpInit(void)
{
    U4                  u4_t_lpcnt;

    u1_s_attmp_stsbit          = (U1)ATTMP_STSBIT_UNKNOWN;
    u2_s_attmp_cel_fltrd       = (U2)0U;
    u1_s_attmp_fltr_ctl        = (U1)ATTMP_FLTR_STS_INACT;
    u1_s_attmp_fltr_pos_oldest = (U1)U1_MAX;
    u1_s_attmp_fltr_rxcnt      = u1_g_AttmpCfgRxCnt();
    u4_s_attmp_fltr_sum        = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ATTMP_FLTR_MVAVG_TMS_MAX; u4_t_lpcnt++){
        u4_sp_attmp_fltr_smpl[u4_t_lpcnt] = (U4)0U;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_AttmpMainTask(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AttmpMainTask(void)
{
    U2                  u2_t_b_thocl;
    U1                  u1_t_stsbit;
    U1                  u1_t_rxcnt;
    U1                  u1_t_igon;

    u1_t_igon    = u1_g_AttmpCfgIgOn();
    u2_t_b_thocl = (U2)U2_MAX;
    u1_t_rxcnt   = u1_s_attmp_fltr_rxcnt;
    u1_t_stsbit  = u1_g_AttmpCfgB_THOCL(&u2_t_b_thocl, &u1_t_rxcnt) & ((U1)ATTMP_STSBIT_UNKNOWN |
                                                                       (U1)ATTMP_STSBIT_INVALID |
                                                                       (U1)ATTMP_STSBIT_RNGOVR);
    if(u1_t_igon == (U1)0U){
        u1_t_stsbit  = (U1)ATTMP_STSBIT_UNKNOWN;
    }
    else if(u2_t_b_thocl > (U2)ATTMP_B_THOCL_VLD_MAX){
        u1_t_stsbit |= (U1)ATTMP_STSBIT_UNKNOWN;
    }
    else{
        /* Do Nothing */
    }

    if((u1_t_stsbit & (U1)ATTMP_STSBIT_UNKNOWN) != (U1)0U) {
        u2_s_attmp_cel_fltrd = (U2)0U;
        u1_s_attmp_fltr_ctl  = (U1)ATTMP_FLTR_STS_INACT;
    }
    else if((u1_t_stsbit & (U1)ATTMP_STSBIT_INVALID) != (U1)0U) {
        /* u2_s_attmp_cel_fltrd = Keep Last */
        u1_s_attmp_fltr_ctl  = (U1)ATTMP_FLTR_STS_INACT;
    }
    else if(u1_t_stsbit == (U1)ATTMP_STSBIT_RNGOVR){
        /* u2_s_attmp_cel_fltrd = Keep Last */
        u1_s_attmp_fltr_ctl  = (U1)ATTMP_FLTR_STS_ACT;
    }
    else{
        u2_s_attmp_cel_fltrd = u2_s_AttmpFltrCel(u2_t_b_thocl, u1_t_rxcnt);
        u1_s_attmp_fltr_ctl  = (U1)ATTMP_FLTR_STS_ACT;
    }
    u1_s_attmp_stsbit     = (u1_t_stsbit & ((U1)ATTMP_STSBIT_UNKNOWN | (U1)ATTMP_STSBIT_INVALID));
    u1_s_attmp_fltr_rxcnt = u1_t_rxcnt;
}

/*===================================================================================================================================*/
/*  U1      u1_g_AttmpCelFltrd(U2 * u2p_a_0p01cel)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AttmpCelFltrd(U2 * u2p_a_0p01cel)
{
    if(( u2p_a_0p01cel                                 != vdp_PTR_NA) &&
       ((u1_s_attmp_stsbit & (U1)ATTMP_STSBIT_UNKNOWN) == (U1)0U    )){
        (*u2p_a_0p01cel) = u2_s_attmp_cel_fltrd;
    }
    return(u1_s_attmp_stsbit);
}

/*===================================================================================================================================*/
/*  static U2       u2_s_AttmpFltrCel(const U2 u2_a_B_THOCL, const U1 u1_a_RXCNT)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2       u2_s_AttmpFltrCel(const U2 u2_a_B_THOCL, const U1 u1_a_RXCNT)
{
    U4                  u4_t_0p001cel;
    U2                  u2_t_fltrd_cel;

    u4_t_0p001cel  = (U4)ATTMP_CNV_LSB_TO_0P001(u2_a_B_THOCL);
    /* The maximum value of u2_a_B_THOCL is 511.                                                                     */
    /* so ATTMP_CNV_LSB_TO_0P01 left hand maximum value is (511 * 320 * 1000) = 163,520,000, always less than U4_MAX */
    u4_t_0p001cel += (U4)ATTMP_CEL_OFFSET_B_THOCL_0P001;
    /* The maximum value of u4_t_0p001cel is ((511 * 320 * 1000) / (256 * 2)) + (273150 - 40000) = 552,525.          */
    /* so u4_t_0p001cel is always less than U4_MAX.                                                                  */

    if(u1_s_attmp_fltr_ctl == (U1)ATTMP_FLTR_STS_INACT){
        vd_s_AttmpMvAvgInit(u4_t_0p001cel);
        u2_t_fltrd_cel = (U2)(u4_t_0p001cel / (U4)ATTMP_DIV_CAL_TO_OUT);
    }
    else if(u1_s_attmp_fltr_rxcnt != u1_a_RXCNT){
        u2_t_fltrd_cel = u2_s_AttmpMvAvgUpdt(u4_t_0p001cel);
    }
    else{
        u2_t_fltrd_cel = u2_s_attmp_cel_fltrd;
    }
    return(u2_t_fltrd_cel);
}

/*===================================================================================================================================*/
/*  static void     vd_s_AttmpMvAvgInit(const U4 u4_a_0P001CEL)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_AttmpMvAvgInit(const U4 u4_a_0P001CEL)
{
    U4                  u4_t_lpcnt;

    u1_s_attmp_fltr_pos_oldest = (U1)U1_MAX;
    u4_s_attmp_fltr_sum        = u4_a_0P001CEL * (U4)ATTMP_FLTR_MVAVG_TMS_MAX;
    /* The maximum value of u4_a_0P001CEL is 552,525. The value of ATTMP_FLTR_MVAVG_TMS_MAX is 4. */
    /* so u4_s_attmp_fltr_sum is always less than U4_MAX.                                         */
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ATTMP_FLTR_MVAVG_TMS_MAX; u4_t_lpcnt++){
        u4_sp_attmp_fltr_smpl[u4_t_lpcnt] = u4_a_0P001CEL;
    }
}

/*===================================================================================================================================*/
/*  static U2       u2_s_AttmpMvAvgUpdt(const U4 u4_a_0P001CEL)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2       u2_s_AttmpMvAvgUpdt(const U4 u4_a_0P001CEL)
{
    U4                  u4_t_cel_oldest;
    U4                  u4_t_avg_cel;
    U4                  u4_t_lpcnt;

    if(u1_s_attmp_fltr_pos_oldest < ((U1)ATTMP_FLTR_MVAVG_TMS_MAX - (U1)1U)){
        u1_s_attmp_fltr_pos_oldest++;
    }
    else{
        u1_s_attmp_fltr_pos_oldest = (U1)0U;
    }

    u4_t_cel_oldest                                   = u4_sp_attmp_fltr_smpl[u1_s_attmp_fltr_pos_oldest];
    u4_sp_attmp_fltr_smpl[u1_s_attmp_fltr_pos_oldest] = u4_a_0P001CEL;

    if((u4_s_attmp_fltr_sum >= u4_t_cel_oldest                                     ) &&
       (u4_s_attmp_fltr_sum <= ((U4)ATTMP_0P001_MAX * (U4)ATTMP_FLTR_MVAVG_TMS_MAX))){

        u4_s_attmp_fltr_sum -= (U4)u4_t_cel_oldest;
        if(((U4)U4_MAX - u4_a_0P001CEL) >= u4_s_attmp_fltr_sum){
            u4_s_attmp_fltr_sum += u4_a_0P001CEL;
        }
        else{
            u4_s_attmp_fltr_sum = (U4)U4_MAX;
        }
    }
    else{

        u4_s_attmp_fltr_sum = (U4)0U;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ATTMP_FLTR_MVAVG_TMS_MAX; u4_t_lpcnt++){
            if(((U4)U4_MAX - u4_sp_attmp_fltr_smpl[u4_t_lpcnt]) >= u4_s_attmp_fltr_sum){
                u4_s_attmp_fltr_sum += u4_sp_attmp_fltr_smpl[u4_t_lpcnt];
            }
            else{
                u4_s_attmp_fltr_sum = (U4)U4_MAX;
            }
        }
    }
    u4_t_avg_cel  = u4_s_attmp_fltr_sum / (U4)ATTMP_FLTR_MVAVG_TMS_MAX;
    u4_t_avg_cel /= (U4)ATTMP_DIV_CAL_TO_OUT;

    if(u4_t_avg_cel > (U4)U2_MAX){
        u4_t_avg_cel = (U4)U2_MAX;
    }
    return((U2)u4_t_avg_cel);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    07/12/2022  YI       New.                                                                                               */
/*  1.0.1    08/29/2022  YI       Change moving average calcuration resolution 0.01cel to 0.001cel.                                  */
/*  1.1.0    10/18/2022  YI       Add input status ATTMP_STSBIT_RNGOVR to ignore range overed b_thocl.                               */
/*                                Change main tick 100 -> 10[ms]. Delete opemd event hook function.                                  */
/*                                                                                                                                   */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
