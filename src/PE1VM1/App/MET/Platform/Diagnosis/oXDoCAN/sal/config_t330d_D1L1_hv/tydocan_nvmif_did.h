/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN NvM Interface                                                                                                            */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  tydocan_nvmif_did.h is included in tydocan_nvmif.h                                                                               */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*===================================================================================================================================*/

#ifndef TYDOCAN_NVM_IF_DID_H
#define TYDOCAN_NVM_IF_DID_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_NVM_IF_DID_H_MAJOR               (1)
#define TYDOCAN_NVM_IF_DID_H_MINOR               (0)
#define TYDOCAN_NVM_IF_DID_H_PATCH               (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------------------------------------- */
/* WARNING :                                                                                                         */
/* ----------------------------------------------------------------------------------------------------------------- */
/* Following #defines are refered by lib/xid/tydocan_met_did_xxx.                                                    */
/*                                                                                                                   */
/* If #defines are modified, lib_ipc_tycan_xxx.a shall be recompiled and rebuilt.                                    */
/*                                                                                                                   */
#define TYDC_NVM_2E_2002                         (0U)     /* MET Customization / Odo Display-On Delay                */
#define TYDC_NVM_2E_2003                         (1U)     /* HUD Customization / Memory Call ..                      */
#define TYDC_NVM_2E_2004                         (2U)     /* MET Customization / Post-Charge Flag                    */
#define TYDC_NVM_2E_2021                         (3U)     /* MET XM Authentication                                   */
#define TYDC_NVM_2E_2041                         (4U)     /* MET Customization / Body Function                       */
#define TYDC_NVM_2E_2042                         (5U)     /* MET Customization / Lane Change Support                 */
#define TYDC_NVM_2E_2043                         (6U)     /* MET Customization / Tic-Toc Volume                      */
#define TYDC_NVM_2E_2045                         (7U)     /* MET Customization / Lane Change Support2                */
#define TYDC_NVM_2E_20C1                         (8U)     /* MET Customization / Shift-By-Wire Reverse Buzzer        */
#define TYDC_NVM_2E_20C2                         (9U)     /* MET Customization / Shift-By-Wire Reverse Buzzer 2      */
/* #define TYDC_NVM_2E_2202                                  HUD Calibration   / Trapezoidal                         */
/* #define TYDC_NVM_2E_2203                                  HUD Calibration   / Distortion                          */
#define TYDC_NVM_2E_2204                         (10U)    /* HUD Customization / Audio F/B, Master Caution  ...      */
#define TYDC_NVM_2E_2209                         (11U)    /* Touch Pad Calibration                                   */
/*                                                                                                                   */
/* Above #defines are refered by lib/xid/tydocan_met_did_xxx.                                                        */
/*                                                                                                                   */
/* If #defines are modified, lib_ipc_tycan_xxx.a shall be recompiled and rebuilt.                                    */
/* ----------------------------------------------------------------------------------------------------------------- */

#define TYDC_NVM_BA_RTA                          (12U)
#define TYDC_NVM_BA_DAX                          (13U)  /* Display Adjustment X       */
#define TYDC_NVM_BA_DAY                          (14U)  /* Display Adjustment Y       */
#define TYDC_NVM_BA_SPC                          (15U)
#define TYDC_NVM_BA_ESN                          (16U)
#define TYDC_NVM_BA_SKN                          (17U)

#define TYDC_NVM_RSI                             (18U)

#define TYDC_NVM_2E_FD00                         (19U)
#define TYDC_NVM_2E_FD01                         (20U)
#define TYDC_NVM_2E_FD02                         (21U)
#define TYDC_NVM_2E_FD03                         (22U)
#define TYDC_NVM_2E_FD04                         (23U)


#define TYDC_NVM_BA_CSR_F                        (24U)
#define TYDC_NVM_BA_CSR_R                        (25U)
#define TYDC_NVM_BA_THFAD_I                      (26U)
#define TYDC_NVM_BA_THRAD_I                      (27U)

#define TYDC_NVM_NUM_DID                         (28U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_NVM_BA_NB_RTA                       (2U)   /* Real Time clock Adjustment */
#define TYDC_NVM_BA_NB_DA                        (2U)   /* Display Adjustment         */
#define TYDC_NVM_BA_NB_SPC                       (2U)   /* Sampling Point check       */
#define TYDC_NVM_BA_NB_ESN                       (12U)  /* ECU Serial Number          */
#define TYDC_NVM_BA_NB_SKN                       (16U)  /* Safe Key Number            */
#define TYDC_NVM_NB_RSI                          (4U)   /* Rewriting Spec Info        */
#define TYDC_NVM_BA_NB_CSR                       (4U)   /* Flasher AD Calicration     */
#define TYDC_NVM_BA_NB_THAD_I                    (4U)   /* TURHAZ_AD_I                */

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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* TYDOCAN_NVM_IF_DID_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tydocan_nvmif_cfg.c                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
