/* 2.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Trip Computer                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TRIPCOM_PRIVATE_H
#define TRIPCOM_PRIVATE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_PRIVATE_H_MAJOR                 (2)
#define TRIPCOM_PRIVATE_H_MINOR                 (4)
#define TRIPCOM_PRIVATE_H_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_TICK                            (50U)

#define TRIPCOM_NUM_STSFIELD                    (5U)
#define TRIPCOM_STSFIELD_VSTS                   (0U)
#define TRIPCOM_STSFIELD_SNSR                   (1U)
#define TRIPCOM_STSFIELD_MANUAL_RSTRQ           (2U)
#define TRIPCOM_STSFIELD_AUTO_RSTRQ             (3U)
#define TRIPCOM_STSFIELD_OTHRQ                  (4U)

/*  TRIPCOM_STSFIELD_VSTS                       */
#define TRIPCOM_VEHSTS_ACCON                    (0x0001U)
#define TRIPCOM_VEHSTS_IGON                     (0x0002U)
#define TRIPCOM_VEHSTS_ECORUNUNK                (0x0004U)
#define TRIPCOM_VEHSTS_ECORUNINV                (0x0008U)
#define TRIPCOM_VEHSTS_ECOSTP                   (0x0010U)
#define TRIPCOM_VEHSTS_DRVCYC                   (0x0020U)
#define TRIPCOM_VEHSTS_VEHMV                    (0x0040U)

/*  TRIPCOM_STSFIELD_SNSR                       */
#define TRIPCOM_SNSRBIT_ELPSDTM_UNKNOWN         (0x0001U)
#define TRIPCOM_SNSRBIT_ELPSDTM_INVALID         (0x0002U)
#define TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN          (0x0004U)
#define TRIPCOM_SNSRBIT_ODOCNT_INVALID          (0x0008U)
#define TRIPCOM_SNSRBIT_FUELUSD_UNKNOWN         (0x0010U)
#define TRIPCOM_SNSRBIT_FUELUSD_INVALID         (0x0020U)
#define TRIPCOM_SNSRBIT_INSTEE_UNKNOWN          (0x0040U)
#define TRIPCOM_SNSRBIT_INSTEE_INVALID          (0x0080U)
#define TRIPCOM_SNSRBIT_HYDRUSD_UNKNOWN         (0x0100U)
#define TRIPCOM_SNSRBIT_HYDRUSD_INVALID         (0x0200U)
#define TRIPCOM_SNSRBIT_AVGEE_UNKNOWN           (0x0400U)
#define TRIPCOM_SNSRBIT_AVGEE_INVALID           (0x0800U)
#define TRIPCOM_SNSRBIT_B_FC_UNKNOWN            (0x1000U)
#define TRIPCOM_SNSRBIT_B_FC_INVALID            (0x2000U)

#define TRIPCOM_SNSRBIT_DTEED_ODOCNT_UNKNOWN    (0x0001U)
#define TRIPCOM_SNSRBIT_DTEED_ODOCNT_INVALID    (0x0002U)
#define TRIPCOM_SNSRBIT_DTEED_FUELUSD_UNKNOWN   (0x0004U)
#define TRIPCOM_SNSRBIT_DTEED_FUELUSD_INVALID   (0x0008U)
#define TRIPCOM_SNSRBIT_DTEED_B_FC_UNKNOWN      (0x0010U)
#define TRIPCOM_SNSRBIT_DTEED_B_FC_INVALID      (0x0020U)

/*  TRIPCOM_STSFIELD_RSTRQ                      */
/* #define TRIPCOM_RSTRQBIT_M_AVGFEHE_TA        (0x0001U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TA      (0x0002U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_SAVEFS_LC         (0x0004U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_ECOSTPTM_LC       (0x0008U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_PTSRUNDIST_LC     (0x0010U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_PTSRUNTM_LC       (0x0020U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_AVGFEHE_ONEM      (0x0040U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_AVGEE_TA          (0x0080U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_AVGEE_ONEM        (0x0100U)                   defined at tripcom.h                                     */
#define TRIPCOM_RSTRQBIT_A_DRVCYC               (0x0001U)
#define TRIPCOM_RSTRQBIT_A_FE_RECHRG            (0x0002U)
#define TRIPCOM_RSTRQBIT_A_DTE_RECHRG           (0x0004U)
#define TRIPCOM_RSTRQBIT_A_FRCRECHRG            (0x0008U)
#define TRIPCOM_RSTRQBIT_A_ECOSTP               (0x0010U)
#define TRIPCOM_RSTRQBIT_A_UPDTFEHUSD           (0x0020U)
#define TRIPCOM_RSTRQBIT_A_DRVCYC_OFF           (0x0040U)
#define TRIPCOM_RSTRQBIT_A_UPDTEEUSD            (0x0080U)

/*  TRIPCOM_STSFIELD_OTHRQ                       */
#define TRIPCOM_PSRQBIT_A_FE_RECHRG             (0x0001U)               /*  Refuel pause                                                                 */
#define TRIPCOM_PSRQBIT_A_DTE_RECHRG            (0x0002U)               /*  Refuel pause                                                                 */
#define TRIPCOM_PSRQBIT_A_FRCRECHRG             (0x0004U)               /*  Force Refuel pause                                                           */
#define TRIPCOM_PSRQBIT_A_EVRUN                 (0x0008U)               /*  EV Run Mode pause                                                            */

#define TRIPCOM_NUM_DELTA                       (14U)
#define TRIPCOM_DELTA_DC_ELPSD_10MS             (0U)                    /* Unsigned : Elapsed time during driving cycle                        [10ms]    */
#define TRIPCOM_DELTA_DC_ELPSD_SEC              (1U)                    /* Unsigned : Elapsed time during driving cycle                        [1sec]    */
#define TRIPCOM_DELTA_IDS_ELPSD_SEC             (2U)                    /* Unsigned : Elapsed time during idle-stop                            [1sec]    */
#define TRIPCOM_DELTA_DC_ODOCNT_PC              (3U)                    /* Unsigned : Distance when driving cycle                              [1count]  */
#define TRIPCOM_DELTA_DC_ODOCNT_KM              (4U)                    /* Unsigned : Distance when driving cycle                              [1km]     */
#define TRIPCOM_DELTA_ANY_ODOCNT_PC             (5U)                    /* Unsigned : Distance between rx fuel/hydr                            [1count]  */
#define TRIPCOM_DELTA_EV_ODOCNT_PC              (6U)                    /* Unsigned : Distance between rx ep                                   [1count]  */
#define TRIPCOM_DELTA_DC_FUELUSD_PC             (7U)                    /* Unsigned : Fuel used when driving cycle                             [1count]  */
#define TRIPCOM_DELTA_DC_HYDRUSD_PC             (8U)                    /* Unsigned : Hydrogen used when driving cycle                         [1count]  */
#define TRIPCOM_DELTA_DC_INSTEPUSD_PC           (9U)                    /* Signed   : Instantaneous Electric Power used when driving cycle     [1count]  */
#define TRIPCOM_DELTA_DC_EVRUNDIST_PC           (10U)                   /* Unsigned : EV Run Distance when driving cycle                       [1count]  */
#define TRIPCOM_DELTA_DC_EPUSD_PC               (11U)                   /* Unsigned : Electric Power used when driving cycle                   [1count]  */
#define TRIPCOM_DELTA_DC_ODOCNT_W_EMGF_PC       (12U)                   /* Unsigned : Distance when driving cycle for DTE_ED with EMGF         [1count]  */
#define TRIPCOM_DELTA_DC_FUELUSD_W_EMGF_PC      (13U)                   /* Unsigned : Fuel used when driving cycle for DTE_ED with EMGF        [1count]  */

#define TRIPCOM_ENGPARAM_DEFFE                  (0U)                    /*  JC08 mode default fe                                                         */
#define TRIPCOM_ENGPARAM_DEFFE_MIN              (1U)                    /*  Learned fe range                                                             */
#define TRIPCOM_ENGPARAM_DEFFE_MAX              (2U)                    /*  Learned fe range                                                             */
#define TRIPCOM_ENGPARAM_DKHCOEF                (3U)                    /*  Coefficient to adjust distance                                               */
#define TRIPCOM_ENGPARAM_SAVEFSRA               (4U)                    /*  Saved fe per sec                                                             */

#define TRIPCOM_NUM_MTRLINFO                    (2U)
#define TRIPCOM_FUELINFO_FULL_10ML              (0U)                    /*  Full fuel volume                                                             */
#define TRIPCOM_FUELINFO_LEFT_10ML              (1U)                    /*  Left fuel volume                                                             */

#define TRIPCOM_FUELUSD_PC_PER_L                (2000000U)
#define TRIPCOM_HYDRUSD_PC_PER_KG               (1000000U)
#define TRIPCOM_EPUSD_PC_PER_KWH                (100000U)
#define TRIPCOM_ELPSDTM_HR_TO_SE                (3600U)
#define TRIPCOM_ELPSDTM_MI_TO_SE                (60U)
#define TRIPCOM_ODOCNT_PC_PER_KM                (5096U)
#define TRIPCOM_EVDIST_PC_PER_KM                (10000U)

#define TRIPCOM_INSTFEHE_UPD                    (0x01U)
#define TRIPCOM_INSTEE_UPD                      (0x02U)


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
/*  for application                                                                                                                  */
U1              u1_g_TripcomOvrfChk(const U4 u4_a_AUGEND, const U4 u4_a_ADDEND, const U4 u4_a_MAX);
U1              u1_g_TripcomGetMaterialInfo(const U1 u1_a_INFOID, U2 * u2p_a_val);
U1              u1_g_TripcomGetEMGF(U1 * u1p_a_emgf);
U1              u1_g_TripcomGetPIEVSTS(U1 * u1p_a_pievsts);
U1              u1_g_TripcomGetPHVMDIND(U1 * u1p_a_phvmdind);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* TRIPCOM_PRIVATE_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tripcom.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
