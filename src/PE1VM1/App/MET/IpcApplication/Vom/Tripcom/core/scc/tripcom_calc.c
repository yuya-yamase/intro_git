/* 2.0.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Calculate                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_CALC_C_MAJOR                    (2)
#define TRIPCOM_CALC_C_MINOR                    (0)
#define TRIPCOM_CALC_C_PATCH                    (3)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_calc_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPCOM_CALC_C_MAJOR != TRIPCOM_CALC_H_MAJOR) || \
     (TRIPCOM_CALC_C_MINOR != TRIPCOM_CALC_H_MINOR) || \
     (TRIPCOM_CALC_C_PATCH != TRIPCOM_CALC_H_PATCH))
#error "tripcom_calc.c and tripcom_calc.h : source and header files are inconsistent!"
#endif

#if ((TRIPCOM_CALC_C_MAJOR != TRIPCOM_CALC_CFG_H_MAJOR) || \
     (TRIPCOM_CALC_C_MINOR != TRIPCOM_CALC_CFG_H_MINOR) || \
     (TRIPCOM_CALC_C_PATCH != TRIPCOM_CALC_CFG_H_PATCH))
#error "tripcom_calc.c and tripcom_calc_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_CALC_KMPX_TO_XPKM               (100000000U)

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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* U4              u4_g_TripcomCalcMuldiv(const U4 u4_a_MLTPLCND, const  U4 u4_a_NUMER, const  U4 u4_a_DENOM, const  U4 u4_a_MIN)    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4              u4_g_TripcomCalcMuldiv(const U4 u4_a_MLTPLCND, const  U4 u4_a_NUMER, const  U4 u4_a_DENOM, const  U4 u4_a_MIN)
{
    U4          u4_t_val;
    U4          u4_tp_term[CALC_U8_NUM_TERM];
    U4          u4_tp_rslt[CALC_U8_NUM_RSLT];
    U1          u1_t_calcrslt;


    if (u4_a_NUMER == (U4)0U) {
        u4_t_val = (U4)0U;
    }
    else if (u4_a_DENOM == (U4)0U) {
        u4_t_val = (U4)U4_MAX;
    }
    else {
        u4_tp_term[CALC_U8_LO]  = u4_a_MLTPLCND;
        u4_tp_term[CALC_U8_HI]  = u4_a_NUMER;
        u4_tp_term[CALC_U8_DIV] = u4_a_DENOM;

        u4_tp_rslt[CALC_U8_QUO] = (U4)0U;
        u4_tp_rslt[CALC_U8_RES] = (U4)0U;
        u1_t_calcrslt = u1_g_MuldivU8(&u4_tp_term[0], &u4_tp_rslt[0]) & (U1)CALC_U8_RSLT_OVRFLW_U4;

        if (u1_t_calcrslt != (U1)0U) {
            u4_t_val = (U4)U4_MAX;
        }
        else if (u4_tp_rslt[CALC_U8_QUO] == (U4)0U) {
            u4_t_val = u4_a_MIN;
        }
        else {
            u4_t_val = u4_tp_rslt[CALC_U8_QUO];
        }
    }

    return (u4_t_val);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomCalcTxCnvtFE(U4 * u4p_a_kmpl_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomCalcTxCnvtFE(U4 * u4p_a_kmpl_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL)
{
    U4          u4_t_mul;
    U4          u4_t_div;
    U1          u1_t_status;


    u1_t_status = (U1)TRIPCOM_STSBIT_VALID;
    switch (u1_a_UNIT) {
        case (U1)TRIPCOM_CALC_FEUNT_KMPL:
            /* Do not have to convert */
            break;
        case (U1)TRIPCOM_CALC_FEUNT_LP100KM:
            if ((*u4p_a_kmpl_to) == (U4)0U) {
                if (u1_a_USEAPRXVAL == (U1)TRUE) {
                    (*u4p_a_kmpl_to) = (U4)U4_MAX;
                }
            }
            else {
                (*u4p_a_kmpl_to) = (U4)TRIPCOM_CALC_KMPX_TO_XPKM / (*u4p_a_kmpl_to);
            }
            break;
        case (U1)TRIPCOM_CALC_FEUNT_MPGUS:
            u4_t_mul = (U4)(TRIPCOM_CALC_KM_TO_MI_MLT * TRIPCOM_CALC_LI_TO_GAUS_DIV);
            u4_t_div = (U4)(TRIPCOM_CALC_KM_TO_MI_DIV * TRIPCOM_CALC_LI_TO_GAUS_MLT);
            (*u4p_a_kmpl_to) = u4_g_TripcomCalcMuldiv(u4_t_mul, (*u4p_a_kmpl_to), u4_t_div, (U4)0U);
            break;
        case (U1)TRIPCOM_CALC_FEUNT_MPGUK:
            u4_t_mul = (U4)(TRIPCOM_CALC_KM_TO_MI_MLT * TRIPCOM_CALC_LI_TO_GAUK_DIV);
            u4_t_div = (U4)(TRIPCOM_CALC_KM_TO_MI_DIV * TRIPCOM_CALC_LI_TO_GAUK_MLT);
            (*u4p_a_kmpl_to) = u4_g_TripcomCalcMuldiv(u4_t_mul, (*u4p_a_kmpl_to), u4_t_div, (U4)0U);
            break;
        case (U1)TRIPCOM_CALC_FEUNT_KMPG:
            u4_t_mul = (U4)TRIPCOM_CALC_LI_TO_GAUK_DIV;
            u4_t_div = (U4)TRIPCOM_CALC_LI_TO_GAUK_MLT;
            (*u4p_a_kmpl_to) = u4_g_TripcomCalcMuldiv(u4_t_mul, (*u4p_a_kmpl_to), u4_t_div, (U4)0U);
            break;
     /* case TRIPCOM_CALC_FEUNT_KMPKG: */
        default:
            u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
            break;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomCalcTxCnvtHE(U4 * u4p_a_kmpkg_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomCalcTxCnvtHE(U4 * u4p_a_kmpkg_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL)
{
    U4          u4_t_mul;
    U4          u4_t_div;
    U1          u1_t_status;


    u1_t_status = (U1)TRIPCOM_STSBIT_VALID;
    switch (u1_a_UNIT) {
        case (U1)TRIPCOM_CALC_HEUNT_KMPKG:
            /* Do not have to convert */
            break;
        case (U1)TRIPCOM_CALC_HEUNT_KGP100KM:
            if ((*u4p_a_kmpkg_to) == (U4)0U) {
                if (u1_a_USEAPRXVAL == (U1)TRUE) {
                    (*u4p_a_kmpkg_to) = (U4)U4_MAX;
                }
            }
            else {
                (*u4p_a_kmpkg_to) = (U4)TRIPCOM_CALC_KMPX_TO_XPKM / (*u4p_a_kmpkg_to);
            }
            break;
        case (U1)TRIPCOM_CALC_HEUNT_MPGE:
            u4_t_mul = (U4)TRIPCOM_CALC_KM_TO_MI_MLT;
            u4_t_div = (U4)TRIPCOM_CALC_KM_TO_MI_DIV;
            (*u4p_a_kmpkg_to) = u4_g_TripcomCalcMuldiv(u4_t_mul, (*u4p_a_kmpkg_to), u4_t_div, (U4)0U);
            break;
        default:
            u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
            break;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomCalcTxCnvtInstEE(U4 * u4p_a_kmpkwh_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomCalcTxCnvtInstEE(U4 * u4p_a_kmpkwh_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL)
{
    U4          u4_t_mul;
    U4          u4_t_div;
    U1          u1_t_status;


    u1_t_status = (U1)TRIPCOM_STSBIT_VALID;
    switch (u1_a_UNIT) {
        case (U1)TRIPCOM_CALC_EEUNT_KMPKWH:
            /* Do not have to convert */
            break;
        case (U1)TRIPCOM_CALC_EEUNT_KWHP100KM:
            if ((*u4p_a_kmpkwh_to) == (U4)0U) {
                if (u1_a_USEAPRXVAL == (U1)TRUE) {
                    (*u4p_a_kmpkwh_to) = (U4)U4_MAX;
                }
            }
            else {
                (*u4p_a_kmpkwh_to) = (U4)TRIPCOM_CALC_KMPX_TO_XPKM / (*u4p_a_kmpkwh_to);
            }
            break;
        case (U1)TRIPCOM_CALC_EEUNT_MPKWH:
            u4_t_mul = (U4)TRIPCOM_CALC_KM_TO_MI_MLT;
            u4_t_div = (U4)TRIPCOM_CALC_KM_TO_MI_DIV;
            (*u4p_a_kmpkwh_to) = u4_g_TripcomCalcMuldiv(u4_t_mul, (*u4p_a_kmpkwh_to), u4_t_div, (U4)0U);

            break;
        default:
            u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
            break;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomCalcTxCnvtAvgEE(U4 * u4p_a_kmpkwh_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomCalcTxCnvtAvgEE(U4 * u4p_a_kmpkwh_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL)
{
    U4          u4_t_mul;
    U4          u4_t_div;
    U1          u1_t_status;


    u1_t_status = (U1)TRIPCOM_STSBIT_VALID;
    switch (u1_a_UNIT) {
        case (U1)TRIPCOM_CALC_EEUNT_KMPKWH:
            /* Do not have to convert */
            break;
        case (U1)TRIPCOM_CALC_EEUNT_KWHP100KM:
            if ((*u4p_a_kmpkwh_to) == (U4)0U) {
                if (u1_a_USEAPRXVAL == (U1)TRUE) {
                    (*u4p_a_kmpkwh_to) = (U4)U4_MAX;
                }
            }
            else {
                (*u4p_a_kmpkwh_to) = (U4)TRIPCOM_CALC_KMPX_TO_XPKM / (*u4p_a_kmpkwh_to);
            }
            break;
        case (U1)TRIPCOM_CALC_EEUNT_MPKWH:
            u4_t_mul = (U4)TRIPCOM_CALC_EVRUN_KM_TO_MI_MLT;
            u4_t_div = (U4)TRIPCOM_CALC_EVRUN_KM_TO_MI_DIV;
            (*u4p_a_kmpkwh_to) = u4_g_TripcomCalcMuldiv(u4_t_mul, (*u4p_a_kmpkwh_to), u4_t_div, (U4)0U);

            break;
        default:
            u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
            break;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomCalcTxCnvtSpeed(U4 * u4_a_kmph_to, const U1 u1_a_UNIT)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomCalcTxCnvtSpeed(U4 * u4_a_kmph_to, const U1 u1_a_UNIT)
{
    U4          u4_t_mul;
    U4          u4_t_div;
    U1          u1_t_status;


    u1_t_status = (U1)TRIPCOM_STSBIT_VALID;
    switch (u1_a_UNIT) {
        case (U1)TRIPCOM_CALC_SPDUNT_KMPH:
            /* Do not have to convert */
            break;
        case (U1)TRIPCOM_CALC_SPDUNT_MPH:
            u4_t_mul = (U4)TRIPCOM_CALC_KM_TO_MI_MLT;
            u4_t_div = (U4)TRIPCOM_CALC_KM_TO_MI_DIV;
            (*u4_a_kmph_to) = u4_g_TripcomCalcMuldiv(u4_t_mul, (*u4_a_kmph_to), u4_t_div, (U4)0U);
            break;
        default:
            u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
            break;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomCalcTxCnvtDist(U4 * u4_a_km_to, const U1 u1_a_UNIT)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomCalcTxCnvtDist(U4 * u4_a_km_to, const U1 u1_a_UNIT)
{
    U4          u4_t_mul;
    U4          u4_t_div;
    U1          u1_t_status;


    u1_t_status = (U1)TRIPCOM_STSBIT_VALID;
    switch (u1_a_UNIT) {
        case (U1)TRIPCOM_CALC_DSTUNT_KM:
            /* Do not have to convert */
            break;
        case (U1)TRIPCOM_CALC_DSTUNT_MILE:
            u4_t_mul = (U4)TRIPCOM_CALC_KM_TO_MI_MLT;
            u4_t_div = (U4)TRIPCOM_CALC_KM_TO_MI_DIV;
            (*u4_a_km_to) = u4_g_TripcomCalcMuldiv(u4_t_mul, (*u4_a_km_to), u4_t_div, (U4)0U);
            break;
        default:
            u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
            break;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomCalcTxCnvtEvDte(U4 * u4_a_km_to, const U1 u1_a_UNIT)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomCalcTxCnvtEvDte(U4 * u4_a_km_to, const U1 u1_a_UNIT)
{
    U4          u4_t_mul;
    U4          u4_t_div;
    U1          u1_t_status;


    u1_t_status = (U1)TRIPCOM_STSBIT_VALID;
    switch (u1_a_UNIT) {
        case (U1)TRIPCOM_CALC_DSTUNT_KM:
            /* Do not have to convert */
            break;
        case (U1)TRIPCOM_CALC_DSTUNT_MILE:
            u4_t_mul = (U4)TRIPCOM_CALC_EVRUN_KM_TO_MI_MLT;
            u4_t_div = (U4)TRIPCOM_CALC_EVRUN_KM_TO_MI_DIV;
            (*u4_a_km_to) = u4_g_TripcomCalcMuldiv(u4_t_mul, (*u4_a_km_to), u4_t_div, (U4)0U);
            break;
        default:
            u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
            break;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U1       u1_g_TripcomCalcAddU1U1(const U1 u1_a_1ST, const U1 u1_a_2ND)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1       u1_g_TripcomCalcAddU1U1(const U1 u1_a_1ST, const U1 u1_a_2ND)
{
    U1  u1_t_ret;


    if(((U1)U1_MAX - u1_a_1ST) < u1_a_2ND){
        u1_t_ret = (U1)U1_MAX;
    }
    else{
        u1_t_ret = u1_a_1ST + u1_a_2ND;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* U1       u1_g_TripcomCalcMulU1U1(const U1 u1_a_1ST, const U1 u1_a_2ND)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1       u1_g_TripcomCalcMulU1U1(const U1 u1_a_1ST, const U1 u1_a_2ND)
{
    U1  u1_t_ret;


    if(u1_a_1ST != (U1)0U){
        if(((U1)U1_MAX / u1_a_1ST) > u1_a_2ND){
            u1_t_ret = u1_a_1ST * u1_a_2ND;
        }
        else{
            u1_t_ret = (U1)U1_MAX;
        }
    }
    else{
        u1_t_ret = (U1)0U;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* U4       u4_g_TripcomCalcAddU4U4(const U4 u4_a_1ST, const U4 u4_a_2ND)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4       u4_g_TripcomCalcAddU4U4(const U4 u4_a_1ST, const U4 u4_a_2ND)
{
    U4  u4_t_ret;


    if(((U4)U4_MAX - u4_a_1ST) < u4_a_2ND){
        u4_t_ret = (U4)U4_MAX;
    }
    else{
        u4_t_ret = u4_a_1ST + u4_a_2ND;
    }
    return(u4_t_ret);
}

/*===================================================================================================================================*/
/* U4       u4_g_TripcomCalcSubU4U4(const U4 u4_a_1ST, const U4 u4_a_2ND)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4       u4_g_TripcomCalcSubU4U4(const U4 u4_a_1ST, const U4 u4_a_2ND)
{
    U4  u4_t_ret;


    if(u4_a_1ST < u4_a_2ND){
        u4_t_ret = (U4)0U;
    }
    else{
        u4_t_ret = u4_a_1ST - u4_a_2ND;
    }
    return(u4_t_ret);
}

/*===================================================================================================================================*/
/* U4       u4_g_TripcomCalcMulU4U4(const U4 u4_a_1ST, const U4 u4_a_2ND)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4       u4_g_TripcomCalcMulU4U4(const U4 u4_a_1ST, const U4 u4_a_2ND)
{
    U4  u4_t_ret;


    if(u4_a_1ST != (U4)0U){
        if(((U4)U4_MAX / u4_a_1ST) > u4_a_2ND){
            u4_t_ret = u4_a_1ST * u4_a_2ND;
        }
        else{
            u4_t_ret = (U4)U4_MAX;
        }
    }
    else{
        u4_t_ret = (U4)0U;
    }
    return(u4_t_ret);
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
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.0.3    12/13/2022  TA(M)    Change TRIPCOM_CALC_KM_TO_MI_MLT 25480 to 1000, TRIPCOM_CALC_KM_TO_MI_DIV 41000 to 1609            */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
