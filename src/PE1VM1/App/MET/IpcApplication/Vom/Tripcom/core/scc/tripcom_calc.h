/* 2.1.0 */
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
#define TRIPCOM_CALC_H_MINOR                    (1)
#define TRIPCOM_CALC_H_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_CALC_INSTEE_KMPKWH              ((TRIPCOM_EPUSD_PC_PER_KWH * 1000U) / TRIPCOM_ODOCNT_PC_PER_KM)
                                                                        /* ([wh/kwh] * [0.001 km/kwh]) / [count/km]                  */
#define TRIPCOM_CALC_AVGEE_KMPKWH               ((TRIPCOM_EPUSD_PC_PER_KWH * 1000U) / TRIPCOM_EVDIST_PC_PER_KM)
                                                                        /* ([wh/kwh] * [0.001 km/kwh]) / [0.1m/km]                   */
#define TRIPCOM_CALC_SEC_TO_10MS                (100U)
#define TRIPCOM_CALC_VEHSPD_KMPH                ((TRIPCOM_ELPSDTM_HR_TO_SE * TRIPCOM_CALC_SEC_TO_10MS * 100U) / TRIPCOM_ODOCNT_PC_PER_KM)
                                                                        /* ([10 ms/h] * [0.01 km/h]) / [count/km]                    */

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
/* In this case, When distance unit changes to "Kwh/100Km", Km/Kwh->Kwh/100Km conversion result needs to be 100 Kwh/100Km.           */
/* Because displayed value of Km/Kwh is XX.X, due to round up calculation, display value is set to 0.0 Km/Kwh                        */
#define u4_g_TripcomCalcInstEeKmpkwh(u4_a_ODOCNT, u4_a_EPWRUSD) \
        (u4_g_TripcomCalcMuldiv((U4)TRIPCOM_CALC_INSTEE_KMPKWH, u4_a_ODOCNT, u4_a_EPWRUSD, (U4)1U))

#define u4_g_TripcomCalcAvgEeKmpkwh(u4_a_ODOCNT, u4_a_EPWRUSD) \
        (u4_g_TripcomCalcMuldiv((U4)TRIPCOM_CALC_AVGEE_KMPKWH, u4_a_ODOCNT, u4_a_EPWRUSD, (U4)1U))

#define u4_g_TripcomCalcVehspdKmph(u4_a_ODOCNT, u4_a_ELPSDTM) \
        (u4_g_TripcomCalcMuldiv((U4)TRIPCOM_CALC_VEHSPD_KMPH, u4_a_ODOCNT, u4_a_ELPSDTM, (U4)0U))

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
