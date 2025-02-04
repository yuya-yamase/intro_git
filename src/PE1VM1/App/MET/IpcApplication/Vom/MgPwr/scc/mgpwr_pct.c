/* 1.0.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* Power Indicator                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MGPWR_PCT_C_MAJOR                    (1)
#define MGPWR_PCT_C_MINOR                    (0)
#define MGPWR_PCT_C_PATCH                    (3)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "mgpwr_pct_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MGPWR_PCT_C_MAJOR != MGPWR_PCT_H_MAJOR) || \
     (MGPWR_PCT_C_MINOR != MGPWR_PCT_H_MINOR) || \
     (MGPWR_PCT_C_PATCH != MGPWR_PCT_H_PATCH))
#error "mgpwr_pct.c and mgpwr_pct.h : source and header files are inconsistent!"
#endif

#if ((MGPWR_PCT_C_MAJOR != MGPWR_PCT_CFG_H_MAJOR) || \
     (MGPWR_PCT_C_MINOR != MGPWR_PCT_CFG_H_MINOR) || \
     (MGPWR_PCT_C_PATCH != MGPWR_PCT_CFG_H_PATCH))
#error "mgpwr_pct.c and mgpwr_pct_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MGPWR_PCT_INIT            (0)
#define MGPWR_PCT_VLD_MIN         (0)
#define MGPWR_PCT_VLD_MAX         (100)
#define MGPWR_NUM_MVAVE           (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static S2       s2_s_mgpwr_pct_mvsum;                                           /* The Sum of Moving Quantities                      */
static S1       s1_s_mgpwr_pct_fltrd;                                           /* Moving Average Value                              */
static U1       u1_s_mgpwr_smpl_oldest;                                         /* The Oldest Sample Value                           */
static U1       u1_s_mgpwr_mgpmet_stsbit;                                       /* MGPWRMET Status                                   */
static S1       s1_sp_mgpwr_pct_mvave[MGPWR_NUM_MVAVE];                         /* Array of Moving Averages                          */
static U1       u1_s_mgpwr_evcnt;                                               /* Event Count                                       */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_MgPwrFltrInit(void);
static S1      s1_s_MgPwrEvcrSigChk(const S1 s1_a_INST);
static void    vd_s_MgPwrFltrdCal(const S1 s1_a_FLTRD, const U1 u1_a_EVCNT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_MgPwrInit(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_MgPwrInit(void)
{
    vd_s_MgPwrFltrInit();

    u1_s_mgpwr_mgpmet_stsbit = (U1)MGPWR_STSBIT_UNKNOWN;
    u1_s_mgpwr_evcnt         = u1_g_MgPwrCfgComRxEvcnt();
}
/*===================================================================================================================================*/
/*  void    vd_g_MgPwrMainTask(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_MgPwrMainTask(void)
{
    S1                  s1_t_fltrd;                                             /* Moving Average Value                              */
    S1                  s1_t_inst;                                              /* Initial Signal Value                              */
    U1                  u1_t_igon;                                              /* Ignition on Status                                */
    U1                  u1_t_mgpmet_stsbit;                                     /* MGPWRMET Status                                   */
    U1                  u1_t_evcnt;                                             /* Event Count                                       */

    u1_t_igon = u1_g_MgPwrCfgIgOn();
    if(u1_t_igon == (U1)TRUE){

        s1_t_inst          = (S1)MGPWR_PCT_INIT;
        u1_t_mgpmet_stsbit = u1_g_MgPwrCfgComRxMGPWRMET(&s1_t_inst);
        u1_t_evcnt         = u1_g_MgPwrCfgComRxEvcnt();
        s1_t_fltrd         = s1_s_MgPwrEvcrSigChk(s1_t_inst);

        if(u1_t_mgpmet_stsbit  == (U1)MGPWR_STSBIT_VALID){
            vd_s_MgPwrFltrdCal(s1_t_fltrd, u1_t_evcnt);
        }

        u1_s_mgpwr_mgpmet_stsbit = u1_t_mgpmet_stsbit;
    }
    else{
        vd_g_MgPwrInit();
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_MgPwrPctFltrd(S1 * const s1p_a_pct)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S1 * const s1p_a_pct                : Moving Average Value                                                       */
/*  Return:         U1         u1_s_mgpwr_mgpmet_stsbit : MGPWRMET Status                                                            */
/*===================================================================================================================================*/
U1      u1_g_MgPwrPctFltrd(S1 * const s1p_a_pct)
{
    U1                  u1_t_unk;                                               /* Unknown Status                                    */

    u1_t_unk = u1_s_mgpwr_mgpmet_stsbit & (U1)MGPWR_STSBIT_UNKNOWN;
    if((u1_t_unk  == (U1)0U    ) &&
       (s1p_a_pct != vdp_PTR_NA)){
        (*s1p_a_pct) = s1_s_mgpwr_pct_fltrd;
    }

    return (u1_s_mgpwr_mgpmet_stsbit);
}
/*===================================================================================================================================*/
/*  static S1    s1_s_MgPwrEvcrSigChk(const S1 s1_a_INST)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const S1 s1_a_INST   : Power Gauge Amount                                                                        */
/*  Return:               S1 s1_t_fltrd  : Moving Average Value                                                                      */
/*===================================================================================================================================*/
static S1    s1_s_MgPwrEvcrSigChk(const S1 s1_a_INST)
{
    S1 s1_t_fltrd;

    if(((S4)s1_a_INST <= MGPWR_PCT_VLD_MAX) && ((S4)s1_a_INST >= MGPWR_PCT_VLD_MIN)){
        s1_t_fltrd = s1_a_INST;
    }
    else{
        s1_t_fltrd = (S1)MGPWR_PCT_INIT;
    }
    return(s1_t_fltrd);
}
/*===================================================================================================================================*/
/*  static void    vd_s_MgPwrFltrdCal(const S1 s1_a_FLTRD, const U1 u1_a_EVCNT)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const S1 s1_a_FLTRD : Moving Average Value                                                                       */
/*                  const U1 u1_a_EVCNT : Event Count                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_MgPwrFltrdCal(const S1 s1_a_FLTRD, const U1 u1_a_EVCNT)
{
    S1                  s1_t_oldest;                                            /* The Oldest Sample Value                           */
    U4                  u4_t_lpcnt;                                             /* Loop Counter                                      */

    if(u1_s_mgpwr_mgpmet_stsbit != (U1)MGPWR_STSBIT_VALID){
        vd_s_MgPwrFltrInit();
    }

    if(u1_a_EVCNT != u1_s_mgpwr_evcnt){
        u1_s_mgpwr_evcnt = u1_a_EVCNT;

        if(u1_s_mgpwr_smpl_oldest < ((U1)MGPWR_NUM_MVAVE - (U1)1U)){
            u1_s_mgpwr_smpl_oldest++;
        }
        else{
            u1_s_mgpwr_smpl_oldest = (U1)0U;
        }

        s1_t_oldest = s1_sp_mgpwr_pct_mvave[u1_s_mgpwr_smpl_oldest];
        s1_sp_mgpwr_pct_mvave[u1_s_mgpwr_smpl_oldest] = s1_a_FLTRD;

        if((s2_s_mgpwr_pct_mvsum >= (S2)((S2)MGPWR_PCT_VLD_MIN * (S2)MGPWR_NUM_MVAVE)) &&
           (s2_s_mgpwr_pct_mvsum <= (S2)((S2)MGPWR_PCT_VLD_MAX * (S2)MGPWR_NUM_MVAVE))){
            s2_s_mgpwr_pct_mvsum -= (S2)s1_t_oldest;
            s2_s_mgpwr_pct_mvsum += (S2)s1_a_FLTRD;
        }
        else{
            s2_s_mgpwr_pct_mvsum  = (S2)0;
            
            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)MGPWR_NUM_MVAVE; u4_t_lpcnt++){
                s2_s_mgpwr_pct_mvsum += (S2)s1_sp_mgpwr_pct_mvave[u4_t_lpcnt];
            }
        }
        s1_s_mgpwr_pct_fltrd = (S1)(s2_s_mgpwr_pct_mvsum / (S2)MGPWR_NUM_MVAVE);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_MgPwrFltrInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_MgPwrFltrInit(void)
{
    U4                  u4_t_lpcnt;                                             /* Loop Counter                                      */

    s2_s_mgpwr_pct_mvsum   = (S2)((S2)MGPWR_PCT_INIT * (S2)MGPWR_NUM_MVAVE);
    s1_s_mgpwr_pct_fltrd   = (S1)MGPWR_PCT_INIT;
    u1_s_mgpwr_smpl_oldest = (U1)U1_MAX;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)MGPWR_NUM_MVAVE; u4_t_lpcnt++){
        s1_sp_mgpwr_pct_mvave[u4_t_lpcnt] = (S1)MGPWR_PCT_INIT;
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
/*  1.0.0             2022.07.19    SN        New.                                                                                   */
/*  1.0.1             2022.09.09    SN        Add range check at calculate filtered value.                                           */
/*  1.0.2             2022.10.20    YI        Fix QAC warning.                                                                       */
/*  1.0.3             2022.11.15    YI        Fix Range Check Condition.                                                             */
/*                                                                                                                                   */
/*  * SN = Shota Nakano, NTT Data MSE                                                                                                */
/*  * YI = Yoshiki Iwata, NTT Data MSE                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
