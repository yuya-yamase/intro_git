/* 2.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Memory Service for Trip Computer                                                                                                 */
/*                                                                                                                                   */
/*  tripcom_ms.h can only be included from                                                                                           */
/*    - tripcom/core/scc/tripcom_cfg_private.h                                                                                       */
/*    - tripcom/core/scc/tripcom_ms_cfg_private.h                                                                                    */
/*    - tripcom/app/scc/XXX_cfg_private.h                                                                                            */
/*  and an application DOES NOT write other ones data.                                                                               */
/*===================================================================================================================================*/

#ifndef TRIPCOM_MS_H
#define TRIPCOM_MS_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_MS_H_MAJOR                      (2)
#define TRIPCOM_MS_H_MINOR                      (2)
#define TRIPCOM_MS_H_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define TRIPCOM_MS_NUM_ID                    (73U)          defined at tripcom_ms_cfg_private.h */
#define TRIPCOM_MS_ID_AVGEE_TA_EE               ( 0U)
#define TRIPCOM_MS_ID_AVGEE_TA_EU               ( 1U)
#define TRIPCOM_MS_ID_AVGEE_TA_OC               ( 2U)
#define TRIPCOM_MS_ID_AVGEE_DC_EE               ( 3U)
#define TRIPCOM_MS_ID_AVGEE_DC_EU               ( 4U)
#define TRIPCOM_MS_ID_AVGEE_DC_OC               ( 5U)
#define TRIPCOM_MS_ID_AVGEE_DC_ASTOEC           ( 6U)
#define TRIPCOM_MS_ID_AVGEE_DC_ASEVDT           ( 7U)
#define TRIPCOM_MS_ID_AVGEE_ONEM_EE             ( 8U)
#define TRIPCOM_MS_ID_AVGEE_ONEM_EU             ( 9U)
#define TRIPCOM_MS_ID_AVGEE_ONEM_OC             (10U)
#define TRIPCOM_MS_ID_AVGEE_FIVEM_EE            (11U)
#define TRIPCOM_MS_ID_AVGEE_FIVEM_EU            (12U)
#define TRIPCOM_MS_ID_AVGEE_FIVEM_OC            (13U)
#define TRIPCOM_MS_ID_INSTEE_EE                 (14U)
#define TRIPCOM_MS_ID_INSTEE_EU                 (15U)
#define TRIPCOM_MS_ID_INSTEE_OC                 (16U)
#define TRIPCOM_MS_ID_INSTEE_DV                 (17U)
#define TRIPCOM_MS_ID_EVDTE_OC                  (18U)
#define TRIPCOM_MS_ID_EVDTE_PCT                 (19U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TA_SP           (20U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TA_OC           (21U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TA_ET           (22U)
#define TRIPCOM_MS_ID_AVGVEHSPD_DC_SP           (23U)
#define TRIPCOM_MS_ID_AVGVEHSPD_DC_OC           (24U)
#define TRIPCOM_MS_ID_AVGVEHSPD_DC_ET           (25U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_A_SP         (26U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_A_OC         (27U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_A_ET         (28U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_B_SP         (29U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_B_OC         (30U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_B_ET         (31U)
#define TRIPCOM_MS_ID_PTSRUNTM_LC_ET            (32U)
#define TRIPCOM_MS_ID_PTSRUNTM_DC_ET            (33U)
#define TRIPCOM_MS_ID_PTSRUNTM_TR_A_ET          (34U)
#define TRIPCOM_MS_ID_PTSRUNTM_TR_B_ET          (35U)
#define TRIPCOM_MS_ID_PTSRUNDIST_LC_OC          (36U)
#define TRIPCOM_MS_ID_PTSRUNDIST_DC_OC          (37U)
#define TRIPCOM_MS_ID_PTSRUNDIST_TR_A_OC        (38U)
#define TRIPCOM_MS_ID_PTSRUNDIST_TR_B_OC        (39U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_ECON         (40U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_DATE         (41U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE00         (42U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE01         (43U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE02         (44U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE03         (45U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE04         (46U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE05         (47U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE06         (48U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE07         (49U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE08         (50U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE09         (51U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE10         (52U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE11         (53U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE12         (54U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE13         (55U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE14         (56U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE15         (57U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE16         (58U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE17         (59U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE18         (60U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE19         (61U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE20         (62U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE21         (63U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE22         (64U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE23         (65U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE24         (66U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE25         (67U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE26         (68U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE27         (69U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE28         (70U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE29         (71U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_LTST         (72U)

#define TRIPCOM_MS_NVMSTS_NON                   (0x00U)
#define TRIPCOM_MS_NVMSTS_SUC                   (0x01U)
#define TRIPCOM_MS_NVMSTS_FAIL                  (0x02U)
#define TRIPCOM_MS_NVMSTS_REQ                   (0x04U)
#define TRIPCOM_MS_NVMSTS_WAIT                  (0x08U)

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
void            vd_g_TripcomMsBonInit(void);
void            vd_g_TripcomMsInit(void);
void            vd_g_TripcomMsMainTask(void);

U4              u4_g_TripcomMsGetAccmltVal(const U1 u1_a_ID);
void            vd_g_TripcomMsSetAccmltVal(const U1 u1_a_ID, const U4 u4_a_VAL);

void            vd_g_TripcomMsGetGrphEconVal(const U1 u1_a_ID, U4* u4_ap_econ, const U1 u1_a_SIZE);
void            vd_g_TripcomMsSetGrphEconVal(const U1 u1_a_ID, U4* u4_ap_econ, const U1 u1_a_SIZE);
void            vd_g_TripcomMsGetGrphMaxVal(const U1 u1_a_ID, U4* u4_ap_max);
void            vd_g_TripcomMsSetGrphMaxVal(const U1 u1_a_ID, const U4 u4_a_MAX);
void            vd_g_TripcomMsGetGrphDateVal(const U1 u1_a_ID, U2* u2_ap_date, const U1 u1_a_SIZE);
void            vd_g_TripcomMsSetGrphDateVal(const U1 u1_a_ID, U2* u2_ap_date, const U1 u1_a_SIZE);

void            vd_g_TripcomMsSetNvmRqst(const U1 u1_a_ID);

void            vd_g_TripcomMsClrRimRslt(void);
void            vd_g_TripcomMsClrNvmRslt(void);
U1              u1_g_TripcomMsGetNvmRslt(const U1 u1_a_ID);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* TRIPCOM_MS_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tripcom_ms.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
