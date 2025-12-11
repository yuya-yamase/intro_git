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
#define IVDSH_NUM_DID_WRI                        (17U)

/*-------------------------------------------------------------------------------*/
/* CPREQ_XXX = "https://wiki.geniie.net/x/Wcq5pQ" numbering list (sample config) */
/*-------------------------------------------------------------------------------*/
#define IVDSH_DID_WRI_CPREQ_002                  (0U)
#define IVDSH_DID_WRI_CPREQ_004                  (1U)
#define IVDSH_DID_WRI_CPREQ_010                  (2U)
#define IVDSH_DID_WRI_CPREQ_012                  (3U)
#define IVDSH_DID_WRI_CPREQ_014                  (4U)
#define IVDSH_DID_WRI_CPREQ_016                  (5U)
#define IVDSH_DID_WRI_CPREQ_018                  (6U)
#define IVDSH_DID_WRI_CPREQ_021                  (7U)
#define IVDSH_DID_WRI_CPREQ_022                  (8U)
#define IVDSH_DID_WRI_CPREQ_023                  (9U)
#define IVDSH_DID_WRI_VM1TO2_CAM_DIAP            (10U)
#define IVDSH_DID_WRI_CPREQ_028                  (11U)
#define IVDSH_DID_WRI_VM1TO2_FLYNOP              (12U)
#define IVDSH_DID_WRI_CPREQ_044                  (13U)
#define IVDSH_DID_WRI_VM1TO2_WHLINI_RES          (14U)
#define IVDSH_DID_WRI_VM1TO3_WHLINI_INF          (15U)
#define IVDSH_DID_WRI_FWUPXRES                   (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_NUM_DID_REA                        (21U)

/* Read from VM#2 */
#define IVDSH_DID_REA_CPREQ_009                  (17U)
#define IVDSH_DID_REA_CPREQ_011                  (18U)
#define IVDSH_DID_REA_CPREQ_013                  (19U)
#define IVDSH_DID_REA_CPREQ_015                  (20U)
#define IVDSH_DID_REA_CPREQ_017                  (21U)
#define IVDSH_DID_REA_CPREQ_019                  (22U)
#define IVDSH_DID_REA_CPREQ_020                  (23U)
#define IVDSH_DID_REA_VM2TO1_CAM_DIAP            (24U)
#define IVDSH_DID_REA_CPREQ_027                  (25U)
#define IVDSH_DID_REA_VM2TO1_WHLINI_REQ          (26U)
#define IVDSH_DID_REA_VM2TO1_DMS1S02             (27U)
#define IVDSH_DID_REA_VM2TO1_MET1S27             (28U)
#define IVDSH_DID_REA_VM2TO1_MET1S28             (29U)
#define IVDSH_DID_REA_VM2TO1_MET1S29             (30U)
#define IVDSH_DID_REA_VM2TO1_MET1S30             (31U)
#define IVDSH_DID_REA_VM2TO1_MET1S43             (32U)
#define IVDSH_DID_REA_VM2TO1_MET1S62             (33U)
#define IVDSH_DID_REA_VM2TO1_MET1S70             (34U)
#define IVDSH_DID_REA_FWUPXREQ_H                 (35U)
#define IVDSH_DID_REA_FWUPXREQ_D                 (36U)
/* Read from VM#3 */
#define IVDSH_DID_REA_CPREQ_045                  (37U)

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
