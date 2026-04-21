/* 2.7.0 */
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
#define TRIPCOM_PRIVATE_H_MINOR                 (7)
#define TRIPCOM_PRIVATE_H_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_TICK                            (50U)

#define TRIPCOM_NUM_STSFIELD                    (6U)
#define TRIPCOM_STSFIELD_VSTS                   (0U)
#define TRIPCOM_STSFIELD_SNSR                   (1U)
#define TRIPCOM_STSFIELD_MANUAL_RSTRQ           (2U)
#define TRIPCOM_STSFIELD_AUTO_RSTRQ             (3U)
#define TRIPCOM_STSFIELD_MARST_IMMW             (4U)
#define TRIPCOM_STSFIELD_OTHRQ                  (5U)

/*  TRIPCOM_STSFIELD_VSTS                       */
#define TRIPCOM_VEHSTS_ACCON                    (0x0001U)
#define TRIPCOM_VEHSTS_IGON                     (0x0002U)
#define TRIPCOM_VEHSTS_DRVCYC                   (0x0020U)
#define TRIPCOM_VEHSTS_VEHMV                    (0x0040U)

/*  TRIPCOM_STSFIELD_SNSR                       */
#define TRIPCOM_SNSRBIT_ELPSDTM_UNKNOWN         (0x0001U)
#define TRIPCOM_SNSRBIT_ELPSDTM_INVALID         (0x0002U)
#define TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN          (0x0004U)
#define TRIPCOM_SNSRBIT_ODOCNT_INVALID          (0x0008U)
#define TRIPCOM_SNSRBIT_INSTEE_UNKNOWN          (0x0040U)
#define TRIPCOM_SNSRBIT_INSTEE_INVALID          (0x0080U)
#define TRIPCOM_SNSRBIT_AVGEE_UNKNOWN           (0x0400U)
#define TRIPCOM_SNSRBIT_AVGEE_INVALID           (0x0800U)

/*  TRIPCOM_STSFIELD_RSTRQ                      */
/* #define TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TA      (0x0002U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_PTSRUNDIST_LC     (0x0010U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_PTSRUNTM_LC       (0x0020U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_AVGEE_TA          (0x0080U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_AVGEE_ONEM        (0x0100U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_A    (0x0200U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_B    (0x0400U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_PTSRUNDIST_TR_A   (0x0800U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_PTSRUNDIST_TR_B   (0x1000U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_A     (0x2000U)                   defined at tripcom.h                                     */
/* #define TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_B     (0x4000U)                   defined at tripcom.h                                     */
#define TRIPCOM_RSTRQBIT_A_DRVCYC               (0x0001U)
#define TRIPCOM_RSTRQBIT_A_DRVCYC_OFF           (0x0040U)
#define TRIPCOM_RSTRQBIT_A_UPDTEEUSD            (0x0080U)

/*  TRIPCOM_STSFIELD_MARST_IMMW                  */
/* see TRIPCOM_STSFIELD_RSTRQ */

#define TRIPCOM_NUM_DELTA                       (8U)
#define TRIPCOM_DELTA_DC_ELPSD_10MS             (0U)                    /* Unsigned : Elapsed time during driving cycle                        [10ms]    */
#define TRIPCOM_DELTA_DC_ELPSD_SEC              (1U)                    /* Unsigned : Elapsed time during driving cycle                        [1sec]    */
#define TRIPCOM_DELTA_DC_ODOCNT_PC              (2U)                    /* Unsigned : Distance when driving cycle                              [1count]  */
#define TRIPCOM_DELTA_DC_ODOCNT_KM              (3U)                    /* Unsigned : Distance when driving cycle                              [1km]     */
#define TRIPCOM_DELTA_EV_ODOCNT_PC              (4U)                    /* Unsigned : Distance between rx ep                                   [1count]  */
#define TRIPCOM_DELTA_DC_INSTEPUSD_PC           (5U)                    /* Signed   : Instantaneous Electric Power used when driving cycle     [1count]  */
#define TRIPCOM_DELTA_DC_EVRUNDIST_PC           (6U)                    /* Unsigned : EV Run Distance when driving cycle                       [1count]  */
#define TRIPCOM_DELTA_DC_EPUSD_PC               (7U)                    /* Unsigned : Electric Power used when driving cycle                   [1count]  */

#define TRIPCOM_EPUSD_PC_PER_KWH                (100000U)
#define TRIPCOM_ELPSDTM_HR_TO_SE                (3600U)
#define TRIPCOM_ELPSDTM_MI_TO_SE                (60U)
#define TRIPCOM_ODOCNT_PC_PER_KM                (5096U)
#define TRIPCOM_EVDIST_PC_PER_KM                (10000U)

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
U1              u1_g_TripcomGetPIEVSTS(U1 * u1p_a_pievsts);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* TRIPCOM_PRIVATE_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tripcom.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
