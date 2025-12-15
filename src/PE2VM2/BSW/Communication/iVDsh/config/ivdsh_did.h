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
#define IVDSH_NUM_DID_WRI                        (21U)

/*-------------------------------------------------------------------------------*/
/* CPREQ_XXX = "https://wiki.geniie.net/x/Wcq5pQ" numbering list (sample config) */
/*-------------------------------------------------------------------------------*/
#define IVDSH_DID_WRI_VM2TO3_STBY                (0U)
#define IVDSH_DID_WRI_VM2TO1_TIMOFST             (1U)
#define IVDSH_DID_WRI_VM2TO1_TIMFMT              (2U)
#define IVDSH_DID_WRI_VM2TO1_DSPTIM              (3U)
#define IVDSH_DID_WRI_VM2TO1_DSPCAL              (4U)
#define IVDSH_DID_WRI_VM2TO1_CAL                 (5U)
#define IVDSH_DID_WRI_VM2TO1_CAM_DIAP            (6U)
#define IVDSH_DID_WRI_VM2TO3_WHLINI_REQ          (7U)
#define IVDSH_DID_WRI_VM2TO3_STRMODE             (8U)
#define IVDSH_DID_WRI_VM2TO3_OPESTS              (9U)
#define IVDSH_DID_WRI_GPS_REQ                    (10U)
#define IVDSH_DID_WRI_VM2TO1_WHLINI_REQ          (11U)
#define IVDSH_DID_WRI_VM2TO3_DIN2_STAT           (12U)
#define IVDSH_DID_WRI_VM2TO1_DMS1S02             (13U)
#define IVDSH_DID_WRI_VM2TO1_MET1S27             (14U)
#define IVDSH_DID_WRI_VM2TO1_MET1S28             (15U)
#define IVDSH_DID_WRI_VM2TO1_MET1S29             (16U)
#define IVDSH_DID_WRI_VM2TO1_MET1S30             (17U)
#define IVDSH_DID_WRI_VM2TO1_MET1S43             (18U)
#define IVDSH_DID_WRI_VM2TO1_MET1S62             (19U)
#define IVDSH_DID_WRI_VM2TO1_MET1S70             (20U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_NUM_DID_REA                        (21U)

/* Read from VM#0 */
#define IVDSH_DID_REA_CANBUS_STS_2M1             (21U)
#define IVDSH_DID_REA_CANBUS_STS_5M              (22U)
#define IVDSH_DID_REA_CANBUS_STS_2M2             (23U)
#define IVDSH_DID_REA_CANBUS_STS_LCAN            (24U)
/* Read from VM#1 */
#define IVDSH_DID_REA_VM1TO2_TIMOFST             (25U)
#define IVDSH_DID_REA_VM1TO2_TIMFMT              (26U)
#define IVDSH_DID_REA_VM1TO2_CAL                 (27U)
#define IVDSH_DID_REA_VM1TO2_CALDEF              (28U)
#define IVDSH_DID_REA_VM1TO2_CALMIN              (29U)
#define IVDSH_DID_REA_VM1TO2_CAM_DIAP            (30U)
#define IVDSH_DID_REA_VM1TO2_FLYNOP              (31U)
#define IVDSH_DID_REA_VM1TO23_FSLP               (32U)
#define IVDSH_DID_REA_VM1TO2_WHLINI_RES          (33U)
#define IVDSH_DID_REA_VM1TO2_MET1D51             (34U)
/* Read from VM#3 */
#define IVDSH_DID_REA_VM3TO2_SIPERR_INF          (35U)
#define IVDSH_DID_REA_VM3TO2_OTA_OFFSTS          (36U)
#define IVDSH_DID_REA_VM3TO2_BOOTLOG_INF         (37U)
#define IVDSH_DID_REA_VM3TO12_RESTART            (38U)
#define IVDSH_DID_REA_VM3TO2_BOOT_CNT            (39U)
#define IVDSH_DID_REA_VM3TO2_BOOT_TIME           (40U)
#define IVDSH_DID_REA_GPS_STS                    (41U)

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
