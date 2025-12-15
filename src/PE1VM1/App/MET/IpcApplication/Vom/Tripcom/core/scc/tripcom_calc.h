/* 2.0.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Calculate                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TRIPCOM_CALC_H
#define TRIPCOM_CALC_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_CALC_H_MAJOR                    (2)
#define TRIPCOM_CALC_H_MINOR                    (0)
#define TRIPCOM_CALC_H_PATCH                    (3)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_CALC_FE_KMPL                    ((TRIPCOM_FUELUSD_PC_PER_L * 1000U) / TRIPCOM_ODOCNT_PC_PER_KM)
                                                                        /* ([count/l] * [0.001 km/l]) / [count/km]                   */
#define TRIPCOM_CALC_HE_KMPKG                   ((TRIPCOM_HYDRUSD_PC_PER_KG * 1000U) / TRIPCOM_ODOCNT_PC_PER_KM)
                                                                        /* ([mg/kg] * [0.001 km/kg]) / [count/km]                    */
#define TRIPCOM_CALC_INSTEE_KMPKWH              ((TRIPCOM_EPUSD_PC_PER_KWH * 1000U) / TRIPCOM_ODOCNT_PC_PER_KM)
                                                                        /* ([wh/kwh] * [0.001 km/kwh]) / [count/km]                  */
#define TRIPCOM_CALC_AVGEE_KMPKWH               ((TRIPCOM_EPUSD_PC_PER_KWH * 1000U) / TRIPCOM_EVDIST_PC_PER_KM)
                                                                        /* ([wh/kwh] * [0.001 km/kwh]) / [0.1m/km]                   */
#define TRIPCOM_CALC_SEC_TO_10MS                (100U)
#define TRIPCOM_CALC_VEHSPD_KMPH                ((TRIPCOM_ELPSDTM_HR_TO_SE * TRIPCOM_CALC_SEC_TO_10MS * 100U) / TRIPCOM_ODOCNT_PC_PER_KM)
                                                                        /* ([10 ms/h] * [0.01 km/h]) / [count/km]                    */
#define TRIPCOM_CALC_DTE_UNITCONV               (100U)

/* for Fuel Economy                             */
#define TRIPCOM_CALC_FEUNT_KMPL                 (1U)
#define TRIPCOM_CALC_FEUNT_LP100KM              (2U)
#define TRIPCOM_CALC_FEUNT_MPGUS                (3U)
#define TRIPCOM_CALC_FEUNT_MPGUK                (4U)
/* #define TRIPCOM_CALC_FEUNT_KMPKG             (5U)    */
#define TRIPCOM_CALC_FEUNT_KMPG                 (6U)

/* for Hydrogen Economy                         */
#define TRIPCOM_CALC_HEUNT_KMPKG                (1U)
#define TRIPCOM_CALC_HEUNT_KGP100KM             (2U)
#define TRIPCOM_CALC_HEUNT_MPGE                 (3U)    /* == Mile / Kg */

/* for Electric Economy                         */
#define TRIPCOM_CALC_EEUNT_KMPKWH               (1U)
#define TRIPCOM_CALC_EEUNT_KWHP100KM            (2U)
#define TRIPCOM_CALC_EEUNT_MPKWH                (3U)

/* for Speed                                    */
#define TRIPCOM_CALC_SPDUNT_KMPH                (1U)
#define TRIPCOM_CALC_SPDUNT_MPH                 (2U)

/* for Distance                                 */
#define TRIPCOM_CALC_DSTUNT_KM                  (1U)
#define TRIPCOM_CALC_DSTUNT_MILE                (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Attention :                                                                                                                       */
/* In this case, When distance unit changes to "L/100Km", Km/L->L/100Km conversion result needs to be 100 L/100Km.                   */
/* Because displayed value of Km/L is XX.X, due to round up calculation, display value is set to 0.0 Km/L                            */
/* When MPG is selected, the display value can be set to 0.0 [unit] because of same trick                                            */
#define u4_g_TripcomCalcFeKmpl(u4_a_ODOCNT, u4_a_FUELUSD) \
        (u4_g_TripcomCalcMuldiv((U4)TRIPCOM_CALC_FE_KMPL, u4_a_ODOCNT, u4_a_FUELUSD, (U4)1U))
/* Attention :                                                                                                                       */
/* In this case, When distance unit changes to "Kg/100Km", Km/Kg->Kg/100Km conversion result needs to be 100 Kg/100Km.               */
/* Because displayed value of Km/Kg is XX.X, due to round up calculation, display value is set to 0.0 Km/Kg                          */
#define u4_g_TripcomCalcHeKmpkg(u4_a_ODOCNT, u4_a_HYDRUSD) \
        (u4_g_TripcomCalcMuldiv((U4)TRIPCOM_CALC_HE_KMPKG, u4_a_ODOCNT, u4_a_HYDRUSD, (U4)1U))
/* Attention :                                                                                                                       */
/* In this case, When distance unit changes to "Kwh/100Km", Km/Kwh->Kwh/100Km conversion result needs to be 100 Kwh/100Km.           */
/* Because displayed value of Km/Kwh is XX.X, due to round up calculation, display value is set to 0.0 Km/Kwh                        */
#define u4_g_TripcomCalcInstEeKmpkwh(u4_a_ODOCNT, u4_a_EPWRUSD) \
        (u4_g_TripcomCalcMuldiv((U4)TRIPCOM_CALC_INSTEE_KMPKWH, u4_a_ODOCNT, u4_a_EPWRUSD, (U4)1U))

#define u4_g_TripcomCalcAvgEeKmpkwh(u4_a_ODOCNT, u4_a_EPWRUSD) \
        (u4_g_TripcomCalcMuldiv((U4)TRIPCOM_CALC_AVGEE_KMPKWH, u4_a_ODOCNT, u4_a_EPWRUSD, (U4)1U))

#define u4_g_TripcomCalcVehspdKmph(u4_a_ODOCNT, u4_a_ELPSDTM) \
        (u4_g_TripcomCalcMuldiv((U4)TRIPCOM_CALC_VEHSPD_KMPH, u4_a_ODOCNT, u4_a_ELPSDTM, (U4)0U))

#define u4_g_TripcomCalcSavefsMl(u4_a_ELPSDTM, u4_a_COEF, u4_a_COEF_RES) \
        (u4_g_TripcomCalcMuldiv(u4_a_ELPSDTM, u4_a_COEF, u4_a_COEF_RES, (U4)0U))

#define u4_g_TripcomCalcDteKm(u4_a_MLTPLCND, u4_a_MLTPLR) \
        (u4_g_TripcomCalcMuldiv(u4_a_MLTPLCND, u4_a_MLTPLR, (U4)TRIPCOM_CALC_DTE_UNITCONV, (U4)0U))

#define u4_g_TripcomCalcTrainingFe(u4_a_MLTPLCND, u4_a_NUMER, u4_a_DENOM) \
        (u4_g_TripcomCalcMuldiv(u4_a_MLTPLCND, u4_a_NUMER, u4_a_DENOM, (U4)0U))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4              u4_g_TripcomCalcMuldiv(const U4 u4_a_MLTPLCND, const  U4 u4_a_NUMER, const  U4 u4_a_DENOM, const  U4 u4_a_MIN);
U1              u1_g_TripcomCalcTxCnvtFE(U4 * u4p_a_kmpl_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL);
U1              u1_g_TripcomCalcTxCnvtHE(U4 * u4p_a_kmpkg_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL);
U1              u1_g_TripcomCalcTxCnvtAvgEE(U4 * u4p_a_kmpkwh_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL);
U1              u1_g_TripcomCalcTxCnvtInstEE(U4 * u4p_a_kmpkwh_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL);
U1              u1_g_TripcomCalcTxCnvtSpeed(U4 * u4_a_kmph_to, const U1 u1_a_UNIT);
U1              u1_g_TripcomCalcTxCnvtDist(U4 * u4_a_km_to, const U1 u1_a_UNIT);
U1              u1_g_TripcomCalcTxCnvtEvDte(U4 * u4_a_km_to, const U1 u1_a_UNIT);
U1              u1_g_TripcomCalcAddU1U1(const U1 u1_a_1ST, const U1 u1_a_2ND);
U1              u1_g_TripcomCalcMulU1U1(const U1 u1_a_1ST, const U1 u1_a_2ND);
U4              u4_g_TripcomCalcAddU4U4(const U4 u4_a_1ST, const U4 u4_a_2ND);
U4              u4_g_TripcomCalcSubU4U4(const U4 u4_a_1ST, const U4 u4_a_2ND);
U4              u4_g_TripcomCalcMulU4U4(const U4 u4_a_1ST, const U4 u4_a_2ND);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* TRIPCOM_CALC_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tripcom_calc.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
