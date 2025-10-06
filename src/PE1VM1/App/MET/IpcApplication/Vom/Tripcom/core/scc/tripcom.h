/* 2.4.1 */
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
#define TRIPCOM_H_MINOR                         (4)
#define TRIPCOM_H_PATCH                         (1)

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
/* 12 EV Ratio                                   */
#define TRIPCOM_STSBIT_EVRATIO_MSKTIM           (0x04U)                 /*  Drive monitor calculation possible flag is ON <= MskTim  */

/*  TRIPCOM_STSFIELD_RSTRQ                      */
#define TRIPCOM_RSTRQBIT_M_AVGFEHE_TA           (0x0001U)               /*  Total Ave.  : F/H economy , History Graph                */
#define TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TA         (0x0002U)               /*  Total Ave.  : Vehicle speed                              */
#define TRIPCOM_RSTRQBIT_M_SAVEFS_LC            (0x0004U)               /*  Life Cycle  : Saved fuel supply                          */
#define TRIPCOM_RSTRQBIT_M_ECOSTPTM_LC          (0x0008U)               /*  Life Cycle  : Eco stop time                              */
#define TRIPCOM_RSTRQBIT_M_PTSRUNDIST_LC        (0x0010U)               /*  Life Cycle  : Powertrain run distance                    */
#define TRIPCOM_RSTRQBIT_M_PTSRUNTM_LC          (0x0020U)               /*  Life Cycle  : Powertrain run time                        */
#define TRIPCOM_RSTRQBIT_M_AVGFEHE_ONEM         (0x0040U)               /*  One minutes : F/H economy , Transition Graph             */
#define TRIPCOM_RSTRQBIT_M_AVGEE_TA             (0x0080U)               /*  Total Ave.  : Electric economy , History Graph           */
#define TRIPCOM_RSTRQBIT_M_AVGEE_ONEM           (0x0100U)               /*  One minutes : Electric economy , Transition Graph        */
#define TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_A       (0x0200U)               /*  Trip A.     : Vehicle speed                              */
#define TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_B       (0x0400U)               /*  Trip B.     : Vehicle speed                              */
#define TRIPCOM_RSTRQBIT_M_PTSRUNDIST_TR_A      (0x0800U)               /*  Trip A.     : Powertrain run distance                    */
#define TRIPCOM_RSTRQBIT_M_PTSRUNDIST_TR_B      (0x1000U)               /*  Trip B.     : Powertrain run distance                    */
#define TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_A        (0x2000U)               /*  Trip A.     : Powertrain run time                        */
#define TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_B        (0x4000U)               /*  Trip B.     : Powertrain run time                        */
#define TRIPCOM_RSTRQBIT_M_DTE_RF               (0x8000U)               /*  Refuel      : Distance To Empty                          */
/* #define TRIPCOM_RSTRQBIT_A_DRVCYC            (0x0001U)                   defined at tripcom_private.h                             */
/* #define TRIPCOM_RSTRQBIT_A_FE_RECHRG         (0x0002U)                   defined at tripcom_private.h                             */
/* #define TRIPCOM_RSTRQBIT_A_DTE_RECHRG        (0x0004U)                   defined at tripcom_private.h                             */
/* #define TRIPCOM_RSTRQBIT_A_FRCRECHRG         (0x0008U)                   defined at tripcom_private.h                             */
/* #define TRIPCOM_RSTRQBIT_A_ECOSTP            (0x0010U)                   defined at tripcom_private.h                             */
/* #define TRIPCOM_RSTRQBIT_A_UPDTFEHUSD        (0x0020U)                   defined at tripcom_private.h                             */
/* #define TRIPCOM_RSTRQBIT_A_DRVCYC_OFF        (0x0040U)                   defined at tripcom_private.h                             */
/* #define TRIPCOM_RSTRQBIT_A_UPDTEEUSD         (0x0080U)                   defined at tripcom_private.h                             */

#define TRIPCOM_CANTX_UNKNOWN                   (0xFFFEU)
#define TRIPCOM_CANTX_TIMEOUT                   (0xFFFFU)

/* 00 Average Fuel Economy                       */
#define AVGFE_NUM_CNTTS                         (4U)
#define AVGFE_CNTT_TA                           (0U)
#define AVGFE_CNTT_DC                           (1U)
#define AVGFE_CNTT_RF                           (2U)
#define AVGFE_CNTT_ONEM                         (3U)
/* 01 Average Hydrogen Economy                   */
#define AVGHE_NUM_CNTTS                         (3U)
#define AVGHE_CNTT_TA                           (0U)
#define AVGHE_CNTT_DC                           (1U)
#define AVGHE_CNTT_RF                           (2U)
/* 02 Average Electric Economy                   */
#define AVGEE_NUM_CNTTS                         (4U)
#define AVGEE_CNTT_TA                           (0U)
#define AVGEE_CNTT_DC                           (1U)
#define AVGEE_CNTT_ONEM                         (2U)
#define AVGEE_CNTT_FIVEM                        (3U)
/* 03 Inst. Fuel Economy                         */
#define INSTFE_NUM_CNTTS                        (2U)
#define INSTFE_CNTT_RX                          (0U)
#define INSTFEC_CNTT_RX                         (1U)
/* 04 Inst. Hydrogen Economy                     */
#define INSTHE_NUM_CNTTS                        (1U)
#define INSTHE_CNTT_RX                          (0U)
/* 05 Inst. Electric Economy                     */
#define INSTEE_NUM_CNTTS                        (1U)
#define INSTEE_CNTT_RX                          (0U)
/* 06 Distance To Empty                          */
#define DTE_CNTT_FU                             (0U)
/* 07 EV Distance To Empty                       */
#define EVDTE_NUM_CNTTS                         (1U)
#define EVDTE_CNTT_EP                           (0U)
/* 08 Average Vehicle Speed                      */
#define AVGVEHSPD_NUM_CNTTS                     (4U)
#define AVGVEHSPD_CNTT_TA                       (0U)
#define AVGVEHSPD_CNTT_DC                       (1U)
#define AVGVEHSPD_CNTT_TR_A                     (2U)
#define AVGVEHSPD_CNTT_TR_B                     (3U)
/* 09 Powertrain System Run Time                 */
#define PTSRUNTM_NUM_CNTTS                      (7U)
#define PTSRUNTM_CNTT_LC                        (0U)
#define PTSRUNTM_CNTT_DC                        (1U)
#define PTSRUNTM_CNTT_TR_A                      (2U)
#define PTSRUNTM_CNTT_TR_B                      (3U)
#define ECOSTPTM_CNTT_LC                        (4U)
#define ECOSTPTM_CNTT_DC                        (5U)
#define ECOSTPTM_CNTT_ST                        (6U)
/* 10 Saved Fuel Supply                          */
#define SAVEFS_NUM_CNTTS                        (2U)
#define SAVEFS_CNTT_LC                          (0U)
#define SAVEFS_CNTT_DC                          (1U)
/* 11 Powertrain System Run Distance             */
#define PTSRUNDIST_NUM_CNTTS                    (4U)
#define PTSRUNDIST_CNTT_LC                      (0U)
#define PTSRUNDIST_CNTT_DC                      (1U)
#define PTSRUNDIST_CNTT_TR_A                    (2U)
#define PTSRUNDIST_CNTT_TR_B                    (3U)
/* 12 EV Ratio                                   */
#define EVRATIO_CNTT_DC                         (0U)

/* 13 Distance To Empty Electric Delay          */
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
U1              u1_g_EvRunTmRatio(U1 * u1p_a_evratio);
U2              u2_g_EvDteKmDiff(void);

U1              u1_g_AvgVehspdRstImmwRslt(const U1 u1_a_AVG_VEHSPD_CH);/* called by Diagnosis */
U1              u1_g_PtsRunTmRstImmwRslt(const U1 u1_a_PTSRUN_TM_CH);  /* called by Diagnosis */
U1              u1_g_AvgEeRstImmwRslt(const U1 u1_a_AVG_EE_CH);        /* called by Diagnosis */

void            vd_g_TripcomActRefuelEvHk(const U2 u2_a_DELTA, const U1 u1_a_VTM);
void            vd_g_TripcomFrcRefuelEvHk(void);
void            vd_g_TripcomFrcRefuelEvImmWr(void);                    /* called by Diagnosis */
void            vd_g_TripcomRstRq(const U2 u2_a_RSTRQBIT);
void            vd_g_TripcomRstRqImmWr(const U2 u2_a_RSTRQBIT);        /* called by Diagnosis */
void            vd_g_TripcomGrphRstRq(const U2 u2_a_RSTRQBIT);
U1              u1_g_TripcomNvmClear(const U1 u1_a_REQ, const U1 u1_a_RUN);

void            vd_g_TripcomNvmIfRWTask(void);                         /* called by nvmc_mgr_cfg : st_NVMC_APP_FUNC_TABLE[].fp_p_vd_acs_func */
void            vd_g_TripcomNvmIfRWFinhk(const U2 u2_a_BLOCKID,        /* called by nvmc_mgr_cfg : st_NVMC_APP_FUNC_TABLE[].fp_p_vd_hook     */
                                         const U1 u1_a_REQUEST_TYPE,
                                         const U1 u1_a_RESULT,
                                         const U1 * const u1_ap_DATA,
                                         const U2 u2_a_SIZE);
void            vd_g_TripcomNvmIfGrphRWTask(void);                     /* called by nvmc_mgr_cfg : st_NVMC_APP_FUNC_TABLE[].fp_p_vd_acs_func */
void            vd_g_TripcomNvmIfGrphRWFinhk(const U2 u2_a_BLOCKID,    /* called by nvmc_mgr_cfg : st_NVMC_APP_FUNC_TABLE[].fp_p_vd_hook     */
                                             const U1 u1_a_REQUEST_TYPE,
                                             const U1 u1_a_RESULT,
                                             const U1 * const u1_ap_DATA,
                                             const U2 u2_a_SIZE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* TRIPCOM_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tripcom.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
