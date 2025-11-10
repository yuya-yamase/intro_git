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
#define IVDSH_NUM_DID_WRI                        (25U)

/*-------------------------------------------------------------------------------*/
/* CPREQ_XXX = "https://wiki.geniie.net/x/Wcq5pQ" numbering list (sample config) */
/*-------------------------------------------------------------------------------*/
#define IVDSH_DID_WRI_CPREQ_003                  (0U)
#define IVDSH_DID_WRI_CPREQ_009                  (1U)
#define IVDSH_DID_WRI_CPREQ_011                  (2U)
#define IVDSH_DID_WRI_CPREQ_013                  (3U)
#define IVDSH_DID_WRI_CPREQ_015                  (4U)
#define IVDSH_DID_WRI_CPREQ_017                  (5U)
#define IVDSH_DID_WRI_CPREQ_019                  (6U)
#define IVDSH_DID_WRI_CPREQ_020                  (7U)
#define IVDSH_DID_WRI_CPREQ_024                  (8U)
#define IVDSH_DID_WRI_VM2TO1_CAM_DIAP            (9U)
#define IVDSH_DID_WRI_CPREQ_027                  (10U)
#define IVDSH_DID_WRI_VM2TO3_WHLINI_REQ          (11U)
#define IVDSH_DID_WRI_CPREQ_046                  (12U)
#define IVDSH_DID_WRI_CPREQ_047                  (13U)
#define IVDSH_DID_WRI_GPS_REQ                    (14U)
#define IVDSH_DID_WRI_VM2TO1_WHLINI_REQ          (15U)
#define IVDSH_DID_WRI_CPREQ_055                  (16U)
#define IVDSH_DID_WRI_VM2TO1_DMS1S02             (17U)
#define IVDSH_DID_WRI_VM2TO1_MET1S27             (18U)
#define IVDSH_DID_WRI_VM2TO1_MET1S28             (19U)
#define IVDSH_DID_WRI_VM2TO1_MET1S29             (20U)
#define IVDSH_DID_WRI_VM2TO1_MET1S30             (21U)
#define IVDSH_DID_WRI_VM2TO1_MET1S43             (22U)
#define IVDSH_DID_WRI_VM2TO1_MET1S62             (23U)
#define IVDSH_DID_WRI_VM2TO1_MET1S70             (24U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_NUM_DID_REA                        (26U)

/* Read from VM#0 */
#define IVDSH_DID_REA_CPREQ_006                  (25U)
#define IVDSH_DID_REA_CPREQ_008                  (26U)
#define IVDSH_DID_REA_CPREQ_029                  (27U)
#define IVDSH_DID_REA_CPREQ_032                  (28U)
#define IVDSH_DID_REA_CPREQ_035                  (29U)
#define IVDSH_DID_REA_CPREQ_038                  (30U)
/* Read from VM#1 */
#define IVDSH_DID_REA_CPREQ_004                  (31U)
#define IVDSH_DID_REA_CPREQ_010                  (32U)
#define IVDSH_DID_REA_CPREQ_012                  (33U)
#define IVDSH_DID_REA_CPREQ_014                  (34U)
#define IVDSH_DID_REA_CPREQ_016                  (35U)
#define IVDSH_DID_REA_CPREQ_018                  (36U)
#define IVDSH_DID_REA_CPREQ_021                  (37U)
#define IVDSH_DID_REA_CPREQ_022                  (38U)
#define IVDSH_DID_REA_VM1TO2_CAM_DIAP            (39U)
#define IVDSH_DID_REA_CPREQ_028                  (40U)
#define IVDSH_DID_REA_VM1TO2_FLYNOP              (41U)
#define IVDSH_DID_REA_CPREQ_044                  (42U)
#define IVDSH_DID_REA_VM1TO2_WHLINI_RES          (43U)
/* Read from VM#3 */
#define IVDSH_DID_REA_CPREQ_005                  (44U)
#define IVDSH_DID_REA_CPREQ_007                  (45U)
#define IVDSH_DID_REA_VM3TO2_BOOTLOG_INF         (46U)
#define IVDSH_DID_REA_CPREQ_045                  (47U)
#define IVDSH_DID_REA_CPREQ_048                  (48U)
#define IVDSH_DID_REA_CPREQ_049                  (49U)
#define IVDSH_DID_REA_GPS_STS                    (50U)

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
