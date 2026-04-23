/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Inter-Vm Data SHaring Data-ID                                                                                                    */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  ivdsh_did.h is included in ivdsh.h                                                                                               */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef IVDSH_DID_H
#define IVDSH_DID_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_DID_H_MAJOR                        (1U)
#define IVDSH_DID_H_MINOR                        (0U)
#define IVDSH_DID_H_PATCH                        (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_NUM_DID_WRI                        (15U)

/*-------------------------------------------------------------------------------*/
/* CPREQ_XXX = "https://wiki.geniie.net/x/Wcq5pQ" numbering list (sample config) */
/*-------------------------------------------------------------------------------*/
#define IVDSH_DID_WRI_VM3TO2_SIPERR_INF          (0U)
#define IVDSH_DID_WRI_VM3TO2_OTA_OFFSTS          (1U)
#define IVDSH_DID_WRI_VM3TO2_BOOTLOG_INF         (2U)
#define IVDSH_DID_WRI_VM3TO12_RESTART            (3U)
#define IVDSH_DID_WRI_VM3TO2_BOOT_CNT            (4U)
#define IVDSH_DID_WRI_VM3TO2_BOOT_TIME           (5U)
#define IVDSH_DID_WRI_GPS_STS                    (6U)
#define IVDSH_DID_WRI_VM3TO2_WHLINI_INF          (7U)
#define IVDSH_DID_WRI_VM3TO1_WHLINI_STA          (8U)
#define IVDSH_DID_WRI_VM3TO1_SOC_POW_STS         (9U)
#define IVDSH_DID_WRI_VM3TO2_WKUP_COND           (10U)
#define IVDSH_DID_WRI_VM3TO2_USRRST_MASK         (11U)
#define IVDSH_DID_WRI_VM3TO2_MONI_INF            (12U)
#define IVDSH_DID_WRI_VM3TO2_VMRESET_RES         (13U)
#define IVDSH_DID_WRI_VM3TO1_OTAACT_REQ          (14U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_NUM_DID_REA                        (15U)

/* Read from VM#1 */
#define IVDSH_DID_REA_VM1TO3_STBY                (15U)
#define IVDSH_DID_REA_VM1TO3_SPI_FAIL            (16U)
#define IVDSH_DID_REA_VM1TO23_FSLP               (17U)
#define IVDSH_DID_REA_VM1TO3_WHLINI_INF          (18U)
#define IVDSH_DID_REA_VM1TO3_NMDIAG              (19U)
#define IVDSH_DID_REA_VM1TO3_MAC_ADDRESS         (20U)
#define IVDSH_DID_REA_VM1TO3_OTAACT_INF          (21U)
/* Read from VM#2 */
#define IVDSH_DID_REA_VM2TO3_STBY                (22U)
#define IVDSH_DID_REA_VM2TO3_WHLINI_INF          (23U)
#define IVDSH_DID_REA_VM2TO3_STRMODE             (24U)
#define IVDSH_DID_REA_VM2TO3_OPESTS              (25U)
#define IVDSH_DID_REA_GPS_REQ                    (26U)
#define IVDSH_DID_REA_VM2TO3_DIN2_STAT           (27U)
#define IVDSH_DID_REA_VM2TO3_SIPERRCMP           (28U)
#define IVDSH_DID_REA_VM2TO3_VMRESET_REQ         (29U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_NUM_DID                            (IVDSH_NUM_DID_WRI + IVDSH_NUM_DID_REA)

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

#endif      /* IVDSH_DID_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  ivdsh_cfg.c                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
