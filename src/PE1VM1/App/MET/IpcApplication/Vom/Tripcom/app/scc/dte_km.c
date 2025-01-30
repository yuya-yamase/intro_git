/* 2.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Distance To Empty for Trip Computer                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DTE_KM_C_MAJOR                          (2)
#define DTE_KM_C_MINOR                          (0)
#define DTE_KM_C_PATCH                          (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "dte_km_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DTE_KM_C_MAJOR != DTE_KM_H_MAJOR) || \
     (DTE_KM_C_MINOR != DTE_KM_H_MINOR) || \
     (DTE_KM_C_PATCH != DTE_KM_H_PATCH))
#error "dte_km.c and dte_km.h : source and header files are inconsistent!"
#endif

#if ((DTE_KM_C_MAJOR != DTE_KM_CFG_H_MAJOR) || \
     (DTE_KM_C_MINOR != DTE_KM_CFG_H_MINOR) || \
     (DTE_KM_C_PATCH != DTE_KM_CFG_H_PATCH))
#error "dte_km.c and dte_km_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DTE_CANTX_RESCNV                        (1000U)
#define DTE_CANTX_MAX                           (0x270FU)
#define DTE_KM_MAX                              (0xfffffffeU)
#define DTE_KM_FUELECON_MIN                     (500U)

#define DTE_STSBIT_VALID                        (0x00U)
#define DTE_STSBIT_UNKNOWN                      (0x01U)
#define DTE_STSBIT_INVALID                      (0x02U)
#define DTE_STSBIT_ODOCNT_INVALID               (0x04U)
#define DTE_STSBIT_FUELUSED_INVALID             (0x08U)
#define DTE_STSBIT_B_FC_INVALID                 (0x10U)

#if ((DTE_STSBIT_VALID   != TRIPCOM_STSBIT_VALID) || \
     (DTE_STSBIT_UNKNOWN != TRIPCOM_STSBIT_UNKNOWN) || \
     (DTE_STSBIT_INVALID != TRIPCOM_STSBIT_INVALID))
#error "DTE_STSBIT_XXX and TRIPCOM_STSBIT_XXX  are inconsistent!"
#endif
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1                                      u1_s_dte_applsts;
static  U1                                      u1_s_dte_engsts;
static  U4                                      u4_s_dte_fuelused;
static  U4                                      u4_s_dte_fuelecon;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_DteCalcParamCg(const U2  u2_a_RSTRQ);
static void     vd_s_DteCgLimitChk(U4 * u4p_a_paramcg);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_DteInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DteInit(void)
{
    u1_s_dte_applsts  = (U1)DTE_STSBIT_UNKNOWN;
    u1_s_dte_engsts   = (U1)DTE_STSBIT_UNKNOWN;
    u4_s_dte_fuelused = (U4)0U;
    u4_s_dte_fuelecon = (U4)0U;
}

/*===================================================================================================================================*/
/* void            vd_g_DteApplTask(const U2 * u2_ap_STSFIELD)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DteApplTask(const U2 * u2_ap_STSFIELD)
{
    static const U1 u1_s_DUMMY_DTE_ENGSTS = (U1)TRIPCOM_STSBIT_VALID;
    U2          u2_t_igon;
    U2          u2_t_jdgbit;
    U1          u1_t_sts;
    U1          u1_t_invalid;
    U1          u1_t_dummy;

    u2_t_igon = u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & (U2)TRIPCOM_VEHSTS_IGON;
    if (u2_t_igon != (U2)0U) {
        u1_t_sts     = (U1)DTE_STSBIT_VALID;

        u2_t_jdgbit  = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN  |
                                                                (U2)TRIPCOM_SNSRBIT_FUELUSD_UNKNOWN |
                                                                (U2)TRIPCOM_SNSRBIT_B_FC_UNKNOWN     );
        if (u2_t_jdgbit != (U2)0U) {
            u1_t_sts |= (U1)DTE_STSBIT_UNKNOWN;
        }

        u2_t_jdgbit  = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID;
        if (u2_t_jdgbit != (U2)0U) {
            u1_t_sts |= (U1)DTE_STSBIT_ODOCNT_INVALID;
        }

        u2_t_jdgbit  = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_FUELUSD_INVALID;
        if (u2_t_jdgbit != (U2)0U) {
            u1_t_sts |= (U1)DTE_STSBIT_FUELUSED_INVALID;
        }

        u2_t_jdgbit  = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_B_FC_INVALID;
        if (u2_t_jdgbit != (U2)0U) {
            u1_t_sts |= (U1)DTE_STSBIT_B_FC_INVALID;
        }
        if ((u1_s_dte_applsts & (U1)DTE_STSBIT_B_FC_INVALID) != (U1)0U) {
            u1_t_sts |= (U1)DTE_STSBIT_B_FC_INVALID;
        }

        u1_t_invalid = u1_t_sts & ((U1)DTE_STSBIT_ODOCNT_INVALID | (U1)DTE_STSBIT_B_FC_INVALID | (U1)DTE_STSBIT_FUELUSED_INVALID);
        if (u1_t_invalid != (U1)0U) {
            u1_t_sts |= (U1)DTE_STSBIT_INVALID;
        }

        u1_s_dte_engsts = u1_s_DUMMY_DTE_ENGSTS;
        u2_t_jdgbit      = ((U2)u1_s_dte_engsts & ((U2)TRIPCOM_STSBIT_UNKNOWN | (U2)TRIPCOM_STSBIT_INVALID));
        if (u2_t_jdgbit != (U2)0U) {
            u1_t_sts |= (U1)DTE_STSBIT_INVALID;
        }

        u1_t_dummy = (U1)0U;
        u1_t_sts  |= u1_g_TripcomGetEMGF(&u1_t_dummy);

        u1_t_dummy = (U1)0U;
        u1_t_sts  |= u1_g_TripcomGetPIEVSTS(&u1_t_dummy);

        u1_t_dummy = (U1)0U;
        u1_t_sts  |= u1_g_TripcomGetPHVMDIND(&u1_t_dummy);

        u1_s_dte_applsts = u1_t_sts;
    }
    else {
        u1_s_dte_applsts &= (U1)(~(U1)DTE_STSBIT_B_FC_INVALID);
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_DteCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DteCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    static const U4 u4_s_DUMMY_DTE_ENGPARAM_DEFFE = (U4)(2160U * 10U);
    U1          u1_t_update;
    U1          u1_t_emgf;
    U4          u4_t_dtekm;
    U4          u4_t_paramcg;

    u1_t_update = (U1)FALSE;
    u4_t_paramcg = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_FE);

    if (u1_s_dte_engsts  == (U1)DTE_STSBIT_VALID) {
        if (u4_t_paramcg == (U4)0U) {
            u4_t_paramcg = u4_s_DUMMY_DTE_ENGPARAM_DEFFE;
        }
        vd_s_DteCgLimitChk(&u4_t_paramcg);
        vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_FE, u4_t_paramcg);


        if (((u2_ap_STSFIELD[TRIPCOM_STSFIELD_OTHRQ] & (U2)TRIPCOM_PSRQBIT_A_DTE_RECHRG) != (U2)0U) &&
            (u4_t_paramcg != (U4)0U                                                               )) {
            u4_s_dte_fuelused = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_AVGFE_RF_FU);
            u4_s_dte_fuelecon = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_AVGFE_RF_FE);
            if (u4_s_dte_fuelecon <= (U4)DTE_KM_FUELECON_MIN) {
                u4_s_dte_fuelecon = u4_s_DUMMY_DTE_ENGPARAM_DEFFE;
            }
        }

        vd_s_DteCalcParamCg(u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ]);
    }
    if (((u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ] & (U2)TRIPCOM_RSTRQBIT_A_DTE_RECHRG) != (U2)0U) ||
        ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ] & (U2)TRIPCOM_RSTRQBIT_A_FRCRECHRG ) != (U2)0U)) {
        u4_t_dtekm = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_OC);
        /* Do not update by refueling before Dte calculation is started */
        if (u4_t_dtekm != (U4)U4_MAX) {
            u1_t_update = (U1)TRUE;
        }
    }
    
    u1_t_emgf = (U1)0U;
    (void)u1_g_TripcomGetEMGF(&u1_t_emgf);
    
    if (((u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U  ) ||
        (u1_t_emgf                                                           == (U1)TRUE)) {
            if(u1_s_dte_applsts == (U1)DTE_STSBIT_VALID) {

                if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_OTHRQ] & (U2)TRIPCOM_PSRQBIT_A_DTE_RECHRG) == (U2)0U) {
                    u1_t_update = (U1)TRUE;
                }
            }
    }

    return (u1_t_update);
}

/*===================================================================================================================================*/
/* void            vd_g_DteUpdt(const U1 u1_a_CNTTID)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DteUpdt(const U1 u1_a_CNTTID)
{
    static const U4 u4_s_DUMMY_DTE_ENGPARAM_DKHCOEF = (U4)100U;
    U4          u4_t_dtekm;
    U4          u4_t_paramcg;
    U2          u2_t_paramkz;
    U4          u4_t_paramdkh;
    U1          u1_t_status;


    u2_t_paramkz = (U2)0U;
    u1_t_status  = u1_g_TripcomGetMaterialInfo((U1)TRIPCOM_FUELINFO_LEFT_10ML, &u2_t_paramkz);

    if (u1_t_status == (U1)DTE_STSBIT_VALID) {
        u4_t_paramdkh = u4_s_DUMMY_DTE_ENGPARAM_DKHCOEF;
        u4_t_paramcg  = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_FE);

        u4_t_dtekm = u4_g_TripcomCalcDteKm(u4_t_paramcg, u4_t_paramdkh);
        u4_t_dtekm = u4_g_TripcomCalcDteKm(u4_t_dtekm,   (U4)u2_t_paramkz);

        if (u4_t_dtekm > (U4)DTE_KM_MAX) {
            u4_t_dtekm = (U4)DTE_KM_MAX;
        }
        vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_OC, u4_t_dtekm);
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_DteKm(U4 * u4p_a_km)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DteKm(U4 * u4p_a_km)
{
    U4          u4_t_dtekm;
    U1          u1_t_stsbit;

    u4_t_dtekm = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_OC);
    if (u4_t_dtekm > (U4)DTE_KM_MAX) {

        u1_t_stsbit = (U1)DTE_STSBIT_UNKNOWN;
    }
    else {

        u1_t_stsbit = u1_s_dte_applsts & ((U1)DTE_STSBIT_UNKNOWN | (U1)DTE_STSBIT_INVALID);
    }
    
    if(u4p_a_km != vdp_PTR_NA) {
        (*u4p_a_km) = u4_t_dtekm;
    }

    return (u1_t_stsbit);
}

/*===================================================================================================================================*/
/* U1              u1_g_DteTrainedFeKmpl(U4 * u4p_a_kmpl)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DteTrainedFeKmpl(U4 * u4p_a_kmpl)
{
    if (u4p_a_kmpl != vdp_PTR_NA) {
        (*u4p_a_kmpl) = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_FE);
    }
    return (u1_s_dte_applsts);
}

/*===================================================================================================================================*/
/* U2              u2_g_DteCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_DteCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{
    U4          u4_t_dist;
    U2          u2_t_txval;
    U1          u1_t_cnvsts;

    u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN;

    if ((u1_s_dte_applsts & (U1)DTE_STSBIT_INVALID) != (U1)0U) {
        u2_t_txval = (U2)TRIPCOM_CANTX_TIMEOUT;
    }
    else {
        u4_t_dist   = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_OC);
        if(u4_t_dist <= (U4)DTE_KM_MAX){
            u1_t_cnvsts = u1_g_TripcomCalcTxCnvtDist(&u4_t_dist, u1_a_UNIT);
            if (u1_t_cnvsts == (U1)TRIPCOM_STSBIT_VALID) {
                u4_t_dist  /= (U4)DTE_CANTX_RESCNV;
                u2_t_txval  = (U2)DTE_CANTX_MAX;
                if (u4_t_dist  < (U4)u2_t_txval) {
                    u2_t_txval = (U2)u4_t_dist;
                }
            }
        }
    }

    return (u2_t_txval);
}

/*===================================================================================================================================*/
/* void            vd_g_DteAccmltClr(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DteAccmltClr(void)
{

    vd_g_DteInit();
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_FE, (U4)0U);
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_OC, (U4)U4_MAX);
    vd_g_DteUpdt((U1)0U);
}

/*===================================================================================================================================*/
/* static void     vd_s_DteCalcParamCg(const U2  u2_a_RSTRQ)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteCalcParamCg(const U2  u2_a_RSTRQ)
{
    U1                       u1_t_fstatus;
    U2                       u2_t_ffull;
    U4                       u4_t_paramcg;
    U4                       u4_t_traing_fe;
    U4                       u4_t_div;
    static const U4          u4_s_UNTCNV_AND_WGHT    = ((U4)3U * (U4)TRIPCOM_FUELUSD_PC_PER_L) / (U4)100U;  /* 10mL to L = 100 and Weight = 3 */


    u1_t_fstatus = u1_g_TripcomGetMaterialInfo((U1)TRIPCOM_FUELINFO_FULL_10ML, &u2_t_ffull);
    if (((u2_a_RSTRQ & (U2)TRIPCOM_RSTRQBIT_A_DTE_RECHRG) != (U2)0U) &&
        (u1_t_fstatus == (U1)DTE_STSBIT_VALID                      )) {

        u4_t_paramcg = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_FE);
        if (u4_t_paramcg != (U4)0U) {
            if (u2_t_ffull == (U2)0U) {
                u4_t_paramcg = (U4)0U;
            }
            else if (u4_t_paramcg > u4_s_dte_fuelecon) {
                u4_t_traing_fe = u4_g_TripcomCalcTrainingFe((u4_t_paramcg - u4_s_dte_fuelecon), u4_s_dte_fuelused, u4_s_UNTCNV_AND_WGHT);
                /* QAC over-detection.       */
                u4_t_div       = u4_t_traing_fe / (U4)u2_t_ffull;
                u4_t_paramcg   = u4_g_TripcomCalcSubU4U4(u4_t_paramcg, u4_t_div);
            }
            else {
                u4_t_traing_fe = u4_g_TripcomCalcTrainingFe((u4_s_dte_fuelecon - u4_t_paramcg), u4_s_dte_fuelused, u4_s_UNTCNV_AND_WGHT);
                u4_t_div = u4_t_traing_fe / (U4)u2_t_ffull;
                u4_t_paramcg = u4_g_TripcomCalcAddU4U4(u4_t_paramcg, u4_t_div);
            }
            vd_s_DteCgLimitChk(&u4_t_paramcg);
            vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_FE, u4_t_paramcg);
        }
    }
}
/*===================================================================================================================================*/
/* static void     vd_s_DteCgLimitChk(U4 * u4p_a_paramcg)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteCgLimitChk(U4 * u4p_a_paramcg)
{
    static const U4 u4_s_DUMMY_DTE_ENGPARAM_DEFFE_MIN = (U4)((2160U * 10U * 67U) / 100U);
    static const U4 u4_s_DUMMY_DTE_ENGPARAM_DEFFE_MAX = (U4)((2160U * 10U * 150U) / 100U);
    U4  u4_t_mincg;
    U4  u4_t_maxcg;
    U4  u4_t_buf;

    u4_t_mincg = u4_s_DUMMY_DTE_ENGPARAM_DEFFE_MIN;
    u4_t_maxcg = u4_s_DUMMY_DTE_ENGPARAM_DEFFE_MAX;
    u4_t_buf   = (*u4p_a_paramcg);
    if (u4_t_buf < u4_t_mincg) {
        (*u4p_a_paramcg) = u4_t_mincg;
    }
    else if (u4_t_buf > u4_t_maxcg) {
        (*u4p_a_paramcg) = u4_t_maxcg;
    }
    else {
        /* Do Nothing */
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
/*  1.0.0    11/07/2018  HY       New.                                                                                               */
/*  1.1.0    11/07/2019  TA       Add vd_g_DteAccmltClr for accumulate value clear                                                   */
/*  1.1.1    03/19/2020  YA       Change for 800B CV                                                                                 */
/*  1.1.2    07/13/2020  YA       Signal reception state judgment correction                                                         */
/*                                initial value change of Distance To Empty                                                          */
/*  1.2.0    10/07/2020  YA       Change for 800B CV-R.                                                                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.0.2    04/03/2024  DR       Changed to dummy value for enging info values                                                      */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
