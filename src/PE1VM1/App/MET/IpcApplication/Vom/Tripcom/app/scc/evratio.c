/* 2.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  EV Ratio for Trip Computer                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVRATIO_C_MAJOR                      (2)
#define EVRATIO_C_MINOR                      (0)
#define EVRATIO_C_PATCH                      (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "evratio_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((EVRATIO_C_MAJOR != EVRATIO_H_MAJOR) || \
     (EVRATIO_C_MINOR != EVRATIO_H_MINOR) || \
     (EVRATIO_C_PATCH != EVRATIO_H_PATCH))
#error "evratio.c and evratio.h : source and header files are inconsistent!"
#endif

#if ((EVRATIO_C_MAJOR != EVRATIO_CFG_H_MAJOR) || \
     (EVRATIO_C_MINOR != EVRATIO_CFG_H_MINOR) || \
     (EVRATIO_C_PATCH != EVRATIO_CFG_H_PATCH))
#error "evratio.c and evratio_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#define EVRATIO_NUM_EVTBIT             (4U)
#define EVRATIO_EVTBIT_CALCTMEXPIRD    (0x01U)
#define EVRATIO_EVTBIT_PTSON           (0x02U)

#define EVRATIO_NUM_CALCSTS            (2U)
#define EVRATIO_CALCSTS_INACT          (0x00U)
#define EVRATIO_CALCSTS_ACT            (0x01U)

#define EVRATIO_ACT_UPDATE             (0x02U)
#define EVRATIO_ACT_VALINIT            (0x04U)
#define EVRATIO_ACT_MASK               (0x08U)

#define EVRATIO_CALCACT_INACT          (EVRATIO_CALCSTS_INACT                                             )
#define EVRATIO_CALCACT_ACT            (EVRATIO_CALCSTS_ACT                                               )
#define EVRATIO_CALCACT_ACT_UPDT       (EVRATIO_CALCSTS_ACT     | EVRATIO_ACT_UPDATE                      )
#define EVRATIO_CALCACT_ACT_RESET      (EVRATIO_CALCSTS_ACT     | EVRATIO_ACT_UPDATE | EVRATIO_ACT_VALINIT)

#define EVRATIO_CALC_INTRVL            (100U / TRIPCOM_TICK)
#define EVRATIO_TIM_MSKTIM             (5000U / TRIPCOM_TICK)
#define EVRATIO_DSP_INTRVL             (1000U / TRIPCOM_TICK)

#define EVRATIO_ACCMLTMAX              (36000000U)

#define EVRATIO_CALC_PER               (100U)
#define EVRATIO_RESCONV                (6000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1           u1_s_evratio_appsts;
static  U1           u1_s_evratio_calcsts;
static  U2           u2_s_evratio_calctim;
static  U2           u2_s_evratio_msktim;
static  U2           u2_s_evratio_dsptim;
static  U1           u1_s_evratio_initupdt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_EvRatioCountDspIntrvl(void);

/*===================================================================================================================================*/
/* void            vd_g_EvRatioInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_EvRatioInit(void)
{
    U4  u4_t_evratio;

    u1_s_evratio_appsts   = (U1)TRIPCOM_STSBIT_UNKNOWN;
    u1_s_evratio_calcsts  = (U1)EVRATIO_CALCSTS_INACT;
    u2_s_evratio_calctim  = (U2)0U;
    u2_s_evratio_msktim   = (U2)0U;
    u2_s_evratio_dsptim   = (U2)0U;
    u1_s_evratio_initupdt = (U1)FALSE;

    u4_t_evratio = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_EVRATIO_DT);
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_EVRATIO_DV, u4_t_evratio);
}

/*===================================================================================================================================*/
/* void            vd_g_EvRatioApplTask(const U2 * u2_ap_STSFIELD)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_EvRatioApplTask(const U2 * u2_ap_STSFIELD)
{
    U2                       u2_t_jdgbit;
    U1                       u1_t_ne1sts;

    if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & (U2)TRIPCOM_VEHSTS_IGON) != (U2)0U) {
        u1_s_evratio_appsts = (U1)TRIPCOM_STSBIT_VALID;

        u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN;
        u1_t_ne1sts = u1_g_TripcomCfgGetNe1Sts();

        if ((u2_t_jdgbit != (U2)0U) ||
            ((u1_t_ne1sts & (U1)TRIPCOM_EVRATIO_UNKNOWN) != (U1)0U)) {
            u1_s_evratio_appsts = (U1)TRIPCOM_STSBIT_UNKNOWN;
        }

        u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID;

        if ((u2_t_jdgbit != (U2)0U) ||
            ((u1_t_ne1sts & (U1)TRIPCOM_EVRATIO_INVALID) != (U1)0U)) {
            u1_s_evratio_appsts |= (U1)TRIPCOM_STSBIT_INVALID;
        }
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_EvRatioCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_EvRatioCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    static const U1  u1_sp2_EVRATIO_CALC_STM[EVRATIO_NUM_EVTBIT][EVRATIO_NUM_CALCSTS]  ={
        {   (U1)EVRATIO_CALCACT_INACT,            (U1)EVRATIO_CALCACT_INACT                     },
        {   (U1)EVRATIO_CALCACT_INACT,            (U1)EVRATIO_CALCACT_INACT                     },
        {   (U1)EVRATIO_CALCACT_ACT_RESET,        (U1)EVRATIO_CALCACT_ACT                       },
        {   (U1)EVRATIO_CALCACT_ACT_RESET,        (U1)EVRATIO_CALCACT_ACT_UPDT                  }
    };
    U1                       u1_t_update;
    U1                       u1_t_evtbit;
    U1                       u1_t_calcact;
    U1                       u1_t_rstflg;

    /* Timer Count */
    if (u1_s_evratio_calcsts == (U1)EVRATIO_CALCSTS_ACT) {
        if (u2_s_evratio_calctim < (U2)U2_MAX) {
            u2_s_evratio_calctim++;
        }
        if (u2_s_evratio_msktim  < (U2)U2_MAX) {
            u2_s_evratio_msktim++;
        }
    }
    else {
        u2_s_evratio_calctim = (U2)0U;
        u2_s_evratio_msktim  = (U2)0U;
    }

    /* Event Check */
    u1_t_evtbit  = (U1)0U;
    if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U) {
        u1_t_evtbit  = (U1)EVRATIO_EVTBIT_PTSON;
    }
    if (u2_s_evratio_calctim >= (U2)EVRATIO_CALC_INTRVL) {
        u1_t_evtbit |= (U1)EVRATIO_EVTBIT_CALCTMEXPIRD;
    }

    /* State Transition */
    u1_t_calcact = (U1)EVRATIO_CALCACT_INACT;
    if (u1_s_evratio_calcsts < (U1)EVRATIO_NUM_CALCSTS) {
        u1_t_calcact = u1_sp2_EVRATIO_CALC_STM[u1_t_evtbit][u1_s_evratio_calcsts];
    }

    /* Action */
    u1_t_update = (U1)FALSE;
    if ((u1_t_calcact & (U1)EVRATIO_ACT_UPDATE ) != (U1)0U) {
        u1_t_update = (U1)TRUE;
        u2_s_evratio_calctim = (U2)0U;
    }
    u1_t_rstflg = (U1)FALSE;
    if ((u1_t_calcact & (U1)EVRATIO_ACT_VALINIT) != (U1)0U) {
        u1_t_rstflg = (U1)TRUE;
    }

    u1_s_evratio_calcsts  = u1_t_calcact & (U1)EVRATIO_CALCSTS_ACT;
    u1_s_evratio_initupdt = u1_t_rstflg;

    vd_s_EvRatioCountDspIntrvl();

    return (u1_t_update);
}

/*===================================================================================================================================*/
/* void            vd_g_EvRatioAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_EvRatioAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)
{
    U4                       u4_t_elpsdtm;
    U1                       u1_t_evmode;
    U1                       u1_t_ovf;
    U1                       u1_t_memid;

    u1_t_evmode = u1_g_TripcomCfgGetTEVRNSts();
    if (u1_s_evratio_initupdt == (U1)TRUE){

        vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_EVRATIO_EV_ET,  (U4)0U);
        vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_EVRATIO_NEV_ET, (U4)0U);
    }
    else if (u1_s_evratio_appsts == (U1)TRIPCOM_STSBIT_VALID) {

        if (u1_t_evmode == (U1)TRUE) {
            u1_t_memid = (U1)TRIPCOM_MS_ID_EVRATIO_EV_ET;
        }
        else {
            u1_t_memid = (U1)TRIPCOM_MS_ID_EVRATIO_NEV_ET;
        }

        u4_t_elpsdtm  = u4_g_TripcomMsGetAccmltVal(u1_t_memid);
        u1_t_ovf      = u1_g_TripcomOvrfChk(u4_t_elpsdtm, u4_ap_DELTA[TRIPCOM_DELTA_DC_ELPSD_10MS], (U4)EVRATIO_ACCMLTMAX);
        
        if (u1_t_ovf == (U1)FALSE) {
            u4_t_elpsdtm += u4_ap_DELTA[TRIPCOM_DELTA_DC_ELPSD_10MS];
            /* u1_g_TripcomOvrfChk() verified not to exceed U4_MAX.         */
            vd_g_TripcomMsSetAccmltVal(u1_t_memid, u4_t_elpsdtm);
        }
        else {
            vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_EVRATIO_EV_ET,  (U4)0U);
            vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_EVRATIO_NEV_ET, (U4)0U);
        }
    }
    else {
        /* Do Nothing */
    }

}

/*===================================================================================================================================*/
/* void            vd_g_EvRatioUpdt(const U1 u1_a_CNTTID)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_EvRatioUpdt(const U1 u1_a_CNTTID)
{
    U4                       u4_t_evtm;
    U4                       u4_t_nevtm;
    U4                       u4_t_evratio;
    U4                       u4_t_sum;

    u4_t_evtm   = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_EVRATIO_EV_ET);
    u4_t_evtm  /= (U4)EVRATIO_RESCONV;

    u4_t_nevtm  = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_EVRATIO_NEV_ET);
    u4_t_nevtm /= (U4)EVRATIO_RESCONV;

    u4_t_sum = u4_t_evtm + u4_t_nevtm;
    /* The maximum value of u4_t_evtm is (U4_MAX / 6000).                           */
    /* The maximum value of u4_t_nevtm is (U4_MAX / 6000),                          */
    /* so (u4_t_evtm + u4_t_nevtm) is always less than U4_MAX.                      */

    if (u4_t_sum == (U4)0U) {
        u4_t_evratio = (U4)0U;
    }
    else {
        u4_t_evratio = (u4_t_evtm * (U4)EVRATIO_CALC_PER) / u4_t_sum;
        /* The maximum value of u4_t_evtm is (U4_MAX / 6000).                       */
        /* The value of EVRATIO_CALC_PER is 100.                                    */
        /* so (u4_t_evtm * (U4)EVRATIO_CALC_PER) is always less than U4_MAX.        */
    }
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_EVRATIO_DT, u4_t_evratio);

    if (u2_s_evratio_dsptim >= (U2)EVRATIO_DSP_INTRVL) {
        vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_EVRATIO_DV, u4_t_evratio);
        u2_s_evratio_dsptim = (U2)0U;
    }


}

/*===================================================================================================================================*/
/* U1              u1_g_EvRunTmRatio(U1 * u1p_a_evratio)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_EvRunTmRatio(U1 * u1p_a_evratio)
{
    U4                       u4_t_value;
    U1                       u1_t_status;

    u4_t_value = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_EVRATIO_DV);
    if (u1p_a_evratio != vdp_PTR_NA) {
        (*u1p_a_evratio) = (U1)u4_t_value;
    }
    
    u1_t_status = u1_s_evratio_appsts;

    if ((u1_s_evratio_calcsts == (U1)EVRATIO_CALCSTS_ACT) &&
        (u2_s_evratio_msktim  <  (U2)EVRATIO_TIM_MSKTIM )) {

        u1_t_status |= (U1)TRIPCOM_STSBIT_EVRATIO_MSKTIM;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* static void     vd_s_EvRatioCountDspIntrvl(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_EvRatioCountDspIntrvl(void)
{
    if (u1_s_evratio_calcsts == (U1)EVRATIO_CALCSTS_ACT) {
        if (u2_s_evratio_dsptim < (U2)U2_MAX) {
            u2_s_evratio_dsptim++;
        }
    }
    else {
        u2_s_evratio_dsptim = (U2)0U;
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    03/30/2020  YA       New.                                                                                               */
/*  1.0.1    07/13/2020  YA       u2_s_evratio_msktim threshold modification                                                         */
/*                                Change status to be determined only during IG-ON                                                   */
/*  1.1.0    10/07/2020  YA       Change for 800B CV-R.                                                                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*                                                                                                                                   */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
