/* 2.6.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Trip Computer                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TRIPCOM_H
#define TRIPCOM_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_H_MAJOR                         (2)
#define TRIPCOM_H_MINOR                         (6)
#define TRIPCOM_H_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* Bit[0-1] : Common Bit Definition             */
#define TRIPCOM_STSBIT_VALID                    (0x00U)                 /*  Valid                                                    */
#define TRIPCOM_STSBIT_UNKNOWN                  (0x01U)                 /*  Unknown                                                  */
#define TRIPCOM_STSBIT_INVALID                  (0x02U)                 /*  Invalid                                                  */

/* Bit[2-7] : Extra Bit Definition              */
/* 07 EV Distance To Empty                      */
#define TRIPCOM_STSBIT_EVDTE_RCVZERO            (0x04U)                 /*  Receive Pievd06 = 0                                      */

/*  TRIPCOM_STSFIELD_RSTRQ                      */
#define TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TA         (0x0002U)               /*  Total Ave.  : Vehicle speed                              */
#define TRIPCOM_RSTRQBIT_M_PTSRUNDIST_LC        (0x0010U)               /*  Life Cycle  : Powertrain run distance                    */
#define TRIPCOM_RSTRQBIT_M_PTSRUNTM_LC          (0x0020U)               /*  Life Cycle  : Powertrain run time                        */
#define TRIPCOM_RSTRQBIT_M_AVGEE_TA             (0x0080U)               /*  Total Ave.  : Electric economy , History Graph           */
#define TRIPCOM_RSTRQBIT_M_AVGEE_ONEM           (0x0100U)               /*  One minutes : Electric economy , Transition Graph        */
#define TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_A       (0x0200U)               /*  Trip A.     : Vehicle speed                              */
#define TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_B       (0x0400U)               /*  Trip B.     : Vehicle speed                              */
#define TRIPCOM_RSTRQBIT_M_PTSRUNDIST_TR_A      (0x0800U)               /*  Trip A.     : Powertrain run distance                    */
#define TRIPCOM_RSTRQBIT_M_PTSRUNDIST_TR_B      (0x1000U)               /*  Trip B.     : Powertrain run distance                    */
#define TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_A        (0x2000U)               /*  Trip A.     : Powertrain run time                        */
#define TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_B        (0x4000U)               /*  Trip B.     : Powertrain run time                        */
/* #define TRIPCOM_RSTRQBIT_A_DRVCYC            (0x0001U)                   defined at tripcom_private.h                             */
/* #define TRIPCOM_RSTRQBIT_A_DRVCYC_OFF        (0x0040U)                   defined at tripcom_private.h                             */
/* #define TRIPCOM_RSTRQBIT_A_UPDTEEUSD         (0x0080U)                   defined at tripcom_private.h                             */

#define TRIPCOM_CANTX_UNKNOWN                   (0xFFFEU)
#define TRIPCOM_CANTX_TIMEOUT                   (0xFFFFU)

/* 00 Average Electric Economy                   */
#define AVGEE_NUM_CNTTS                         (6U)
#define AVGEE_CNTT_TA                           (0U)
#define AVGEE_CNTT_DC                           (1U)
#define AVGEE_CNTT_ONEM                         (2U)
#define AVGEE_CNTT_FIVEM                        (3U)
/* avgee send data ID*/
#define AVGEE_CNTT_DC_DT                        (4U)
#define AVGEE_CNTT_DC_EC                        (5U)
/* avgee total calc cntt ID */
#define AVGEE_CALC_CNTTS_NUM                    (4U)
/* 01 Inst. Electric Economy                     */
#define INSTEE_NUM_CNTTS                        (1U)
#define INSTEE_CNTT_RX                          (0U)
/* 02 EV Distance To Empty                       */
#define EVDTE_NUM_CNTTS                         (1U)
#define EVDTE_CNTT_EP                           (0U)
/* 03 Average Vehicle Speed                      */
#define AVGVEHSPD_NUM_CNTTS                     (4U)
#define AVGVEHSPD_CNTT_TA                       (0U)
#define AVGVEHSPD_CNTT_DC                       (1U)
#define AVGVEHSPD_CNTT_TR_A                     (2U)
#define AVGVEHSPD_CNTT_TR_B                     (3U)
/* 04 Powertrain System Run Time                 */
#define PTSRUNTM_NUM_CNTTS                      (4U)
#define PTSRUNTM_CNTT_LC                        (0U)
#define PTSRUNTM_CNTT_DC                        (1U)
#define PTSRUNTM_CNTT_TR_A                      (2U)
#define PTSRUNTM_CNTT_TR_B                      (3U)
/* 05 Powertrain System Run Distance             */
#define PTSRUNDIST_NUM_CNTTS                    (4U)
#define PTSRUNDIST_CNTT_LC                      (0U)
#define PTSRUNDIST_CNTT_DC                      (1U)
#define PTSRUNDIST_CNTT_TR_A                    (2U)
#define PTSRUNDIST_CNTT_TR_B                    (3U)
/* 06 Distance To Empty for ED                   */
#define DTE_ED_NUM_CNTTS                        (1U)
#define DTE_ED_CNTT_FU                          (0U)

#define TRIPCOM_NVMR_RES_RUN                    (0x00U)
#define TRIPCOM_NVMR_RES_SUC                    (0x01U)
#define TRIPCOM_NVMR_RES_FAI                    (0x02U)
#define TRIPCOM_NVMR_RES_UNK                    (0x03U)

/* u1_g_XXXXRstImmwRslt */
#define TRIPCOM_RSTIMMW_UNK                     (0x00U)
#define TRIPCOM_RSTIMMW_RUN                     (0x01U)
#define TRIPCOM_RSTIMMW_SUC                     (0x02U)
#define TRIPCOM_RSTIMMW_FAI                     (0x04U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void            vd_g_TripcomBonInit(void);
void            vd_g_TripcomWkupInit(void);
void            vd_g_TripcomMainTask(void);
void            vd_g_TripcomSmoothingTask(void);

U1              u1_g_AvgVehspdKmph(const U1 u1_a_AVG_VEHSPD_CH, U2 * u2p_a_kmph);
U1              u1_g_PtsRunDistKm(const U1 u1_a_PTSRUN_DIST_CH, U4 * u4p_a_km);
U1              u1_g_PtsRunTmHrs(const U1 u1_a_PTSRUN_TM_CH, U4 * u4p_a_hhmmss);
U1              u1_g_InstEeKmpkwh(U4 * u4p_a_kmpkwh);
U1              u1_g_AvgEeKmpkwh(const U1 u1_a_AVG_EE_CH, U4 * u4p_a_kmpkwh);
U1              u1_g_EvDteKm(U4 * u4p_a_km, U1 * u1p_a_acsts);
U1              u1_g_TripcomEvDteKmIgOffAcOn(U4 * u4p_a_km);
U1              u1_g_TripcomEvDteKmIgOffAcOff(U4 * u4p_a_km);
U1              u1_g_EvDtePct(U1 * u1p_a_pct);
U2              u2_g_EvDteKmDiff(void);

U1              u1_g_AvgVehspdRstImmwRslt(const U1 u1_a_AVG_VEHSPD_CH);/* called by Diagnosis */
U1              u1_g_PtsRunTmRstImmwRslt(const U1 u1_a_PTSRUN_TM_CH);  /* called by Diagnosis */
U1              u1_g_AvgEeRstImmwRslt(const U1 u1_a_AVG_EE_CH);        /* called by Diagnosis */

void            vd_g_TripcomRstRq(const U2 u2_a_RSTRQBIT);
void            vd_g_TripcomRstRqImmWr(const U2 u2_a_RSTRQBIT);        /* called by Diagnosis */
void            vd_g_TripcomGrphRstRq(const U2 u2_a_RSTRQBIT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* TRIPCOM_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tripcom.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
