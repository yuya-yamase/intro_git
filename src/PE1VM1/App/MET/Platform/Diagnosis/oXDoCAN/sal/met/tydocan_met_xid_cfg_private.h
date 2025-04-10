/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN MET Configuration                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TYDOCAN_MET_XID_CFG_H
#define TYDOCAN_MET_XID_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_MET_XID_CFG_H_MAJOR              (1)
#define TYDOCAN_MET_XID_CFG_H_MINOR              (1)
#define TYDOCAN_MET_XID_CFG_H_PATCH              (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_util.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x12A1 */
#define TYDC_OM_MI_UNK                           (0xffU)
#define TYDC_OM_MI_MAX                           (0xfeU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_XID_PTS_22_1042                     (0U)             /* SID 0x22 : Engine Speed                  */
#define TYDC_XID_PTS_22_1241                     (1U)             /* SID 0x22 : Coolant Temperature           */   
#define TYDC_XID_PTS_22_1641                     (2U)             /* SID 0x22 : Hybrid System Indicator       */   
#define TYDC_XID_PTS_2F_2802                     (3U)             /* SID 0x2F : Tacho Meter                   */   
#define TYDC_XID_PTS_2F_2805                     (4U)             /* SID 0x2F : Temp Gauge                    */   
#define TYDC_XID_PTS_2F_2808                     (5U)             /* SID 0x2F : Hybrid System Indicator       */   
#define TYDC_XID_PTS_31_1101                     (6U)             /* SID 0x31 : DTE Initialization            */   
#define TYDC_XID_PTS_22_1401                     (7U)             /* SID 0x22 : ChassisArea                   */   

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_FUEL_CH_MA                          (0U)             /* Fuel Sender Channel : MAIN               */
#define TYDC_FUEL_CH_SU                          (1U)             /* Fuel Sender Channel : SUB                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_FUEL_EVC_SS_LIT                     (0U)
#define TYDC_FUEL_EVC_SS_VEU                     (1U)

#define TYDC_FUEL_EVC_LIT_BFR_L                  (0U)
#define TYDC_FUEL_EVC_LIT_BFR_H                  (8U)
#define TYDC_FUEL_EVC_LIT_AFT_L                  (16U)
#define TYDC_FUEL_EVC_LIT_AFT_H                  (24U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_NUM_PN                              (4U)
#define TYDC_PN_0105                             (0U)             /* SID 0x22 / DID 0x0105 ECU Product Number */
#define TYDC_PN_F188                             (1U)             /* SID 0x22 / DID 0xF188 Software Number    */
#define TYDC_PN_F18C                             (2U)             /* SID 0x22 / DID 0xF18C ECU Serial Number  */
#define TYDC_PN_0107                             (3U)             /* SID 0x22 / DID 0x0107 exECU Software Num */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x1021 */
#define TYDC_PWR_VOL_UNK                         (0xffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0xAA00 */
/* MET-M_TESTMODE-CSTD-0-02-A-C2.docx */
#define TYDC_TES_MD_BIT_ACC                      (0x00000020U)    /* ACC 100 Volt       : On/Off              */
#define TYDC_TES_MD_BIT_DUN                      (0x00000010U)    /* Distance Unit      : KM/MI               */
#define TYDC_TES_MD_BIT_RSU                      (0x00000008U)    /* Rear Sun Shade     : Open/Close          */
#define TYDC_TES_MD_BIT_VSW                      (0x00008000U)    /* Vaccum Switch      : On/Off              */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* RID 0x1901 */
#define TYDC_HUD_RES_SUC                         (0x00U)
#define TYDC_HUD_RES_FAI                         (0x01U)
#define TYDC_HUD_RES_RUN                         (0x02U)
#define TYDC_HUD_RES_UNK                         (0xffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* LOG INDEX (RAM) */
#define TYDC_NUM_LOGRAM                          (2U)
#define TYDC_LOGRAM_10A7                         (0U)
#define TYDC_LOGRAM_10A9                         (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    const U2 *  u2p_RIMID;
    U1          u1_nb;
}ST_TYDC_LOG_RAM;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef OXDC_DATA_REA_ANS_NB_12A1
U1      u1_g_oXDoCANDidSup_OmMI(void);                            /* DID 0x12A1 : Oilmaint                                        */
U1      u1_g_TyDoCANOmMI(void);                                   /* DID 0x12A1 : Oilmaint,      Return : [/100 miles]            */
#endif /* #ifdef OXDC_DATA_REA_ANS_NB_12A1 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_TyDoCANXidSup_Pts(const U1 u1_a_XID);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_TyDoCANXidSup_MpxSw(void);                           /* Return     : MPX-SW Support , TRUE = SUPPORT FALSE = Not.    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_TyDoCANXidSup_Fuel(const U1 u1_a_CH);                /* Return     : Fuel Support , TRUE = SUPPORT FALSE = Not.     */

U1      u1_g_TyDoCANXidSup_1201(void);                            /* Return     : 1201 Support,  TRUE = SUPPORT FALSE = Not.      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_TyDoCANProductNum(U1 * u1_ap_ans, const U1 u1_a_PN); /* Return     : OXDC_SAL_PROC_FIN or OXDC_SAL_PROC_NR_31        */
                                                                  /* DID 0x0105 : ECU Number                                      */
                                                                  /* DID 0xF181 : Software Number                                 */
                                                                  /* DID 0xF18C : ECU Serial Number                               */

U1      u1_g_TyDoCANPwrVol(void);                                 /* DID 0x1021 : IG/+B Voltage, Return : [/0.1 volt ]            */

U2      u2_g_TyDoCANFuelLit32(const U1 u1_a_CH);                  /* DID 0x1022 : Fuel(main) level, Return : [/0.01 Lit ]         */
                                                                  /* DID 0x1023 : Fuel(sub)  level, Return : [/0.01 Lit ]         */

U1      u1_g_TyDoCANTesMd32(U4 * u4_ap_b32);                      /* DID 0xAA00 : Test Mode.,    Return : TRUE = OK, FALSE = Not. */
U1      u1_g_TyDoCANTesMdNext(const U4 u4_a_B32);                 /*                             Return : TRUE = OK, FALSE = Not. */
void    vd_g_TyDoCANTesMdCancel(void);                            /* RID 0xDA00 : Cancel Test Mode.,                              */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_TyDoCANEsoReset(void);                               /* RID 0x11FF                                                   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_TyDoCANLogRAM(U1 * u1_ap_ans, const U1 u1_a_DID);    /* DID 0x10A7,10A9 : Store user actions in RAM                  */
void    vd_g_TyDoCANLogRAMReset(void);                            /* RID 0x11FD                                                   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_TyDoCANTrchkFuel(const U1 u1_a_CH);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U2      u2_g_TyDoCANCursorCount(void);                            /* DID 0x10A8                                                   */
U1      u1_g_TyDoCANGetDisplaySwitchCntt(void);                   /* DID 0x10A8                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef OXDC_DATA_REA_ANS_NB_10A1
extern const U1    u1_g_TYDC_SSR_CH_22_10A1;                      /* DID 0x10A1 */
#endif /* #ifdef OXDC_DATA_REA_ANS_NB_10A1 */

#ifdef OXDC_DATA_REA_ANS_NB_10A2
extern const U1    u1_g_TYDC_SSR_CH_22_10A2;                      /* DID 0x10A2 */
#endif /* #ifdef OXDC_DATA_REA_ANS_NB_10A2 */

#ifdef OXDC_DATA_REA_ANS_NB_10A3
extern const U1    u1_g_TYDC_SSR_CH_22_10A3;                      /* DID 0x10A3 */
#endif /* #ifdef OXDC_DATA_REA_ANS_NB_10A3 */

#ifdef OXDC_DATA_REA_ANS_NB_10AB
extern const U1    u1_g_TYDC_SSR_CH_22_10AB;                      /* DID 0x10AB */
#endif /* #ifdef OXDC_DATA_REA_ANS_NB_10AB */

#ifdef OXDC_DATA_REA_ANS_NB_10AD
extern const U1    u1_g_TYDC_SSR_CH_22_10AD;                      /* DID 0x10AD */
#endif /* #ifdef OXDC_DATA_REA_ANS_NB_10AD */

#endif      /* TYDOCAN_MET_XID_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tydocan_met_xid_cfg.c                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
