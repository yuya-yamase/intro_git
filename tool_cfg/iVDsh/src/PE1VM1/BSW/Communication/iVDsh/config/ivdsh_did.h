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
#define IVDSH_NUM_DID_WRI                        (14U)

/*-------------------------------------------------------------------------------*/
/* CPREQ_XXX = "https://wiki.geniie.net/x/Wcq5pQ" numbering list (sample config) */
/*-------------------------------------------------------------------------------*/
#define IVDSH_DID_WRI_VM1TO3_STBY                (0U)
#define IVDSH_DID_WRI_VM1TO2_TIMOFST             (1U)
#define IVDSH_DID_WRI_VM1TO2_TIMFMT              (2U)
#define IVDSH_DID_WRI_VM1TO2_CAL                 (3U)
#define IVDSH_DID_WRI_VM1TO2_CALDEF              (4U)
#define IVDSH_DID_WRI_VM1TO2_CALMIN              (5U)
#define IVDSH_DID_WRI_VM1TO3_SPI_FAIL            (6U)
#define IVDSH_DID_WRI_VM1TO2_CAM_DIAP            (7U)
#define IVDSH_DID_WRI_VM1TO2_FLYNOP              (8U)
#define IVDSH_DID_WRI_VM1TO23_FSLP               (9U)
#define IVDSH_DID_WRI_VM1TO2_WHLINI_RES          (10U)
#define IVDSH_DID_WRI_VM1TO3_WHLINI_INF          (11U)
#define IVDSH_DID_WRI_VM1TO2_MET1D51             (12U)
#define IVDSH_DID_WRI_FWUPXRES                   (13U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_NUM_DID_REA                        (18U)

/* Read from VM#2 */
#define IVDSH_DID_REA_VM2TO1_TIMOFST             (14U)
#define IVDSH_DID_REA_VM2TO1_TIMFMT              (15U)
#define IVDSH_DID_REA_VM2TO1_DSPTIM              (16U)
#define IVDSH_DID_REA_VM2TO1_DSPCAL              (17U)
#define IVDSH_DID_REA_VM2TO1_CAL                 (18U)
#define IVDSH_DID_REA_VM2TO1_CAM_DIAP            (19U)
#define IVDSH_DID_REA_VM2TO1_WHLINI_REQ          (20U)
#define IVDSH_DID_REA_VM2TO1_DMS1S02             (21U)
#define IVDSH_DID_REA_VM2TO1_MET1S27             (22U)
#define IVDSH_DID_REA_VM2TO1_MET1S28             (23U)
#define IVDSH_DID_REA_VM2TO1_MET1S29             (24U)
#define IVDSH_DID_REA_VM2TO1_MET1S30             (25U)
#define IVDSH_DID_REA_VM2TO1_MET1S43             (26U)
#define IVDSH_DID_REA_VM2TO1_MET1S62             (27U)
#define IVDSH_DID_REA_VM2TO1_MET1S70             (28U)
#define IVDSH_DID_REA_FWUPXREQ_H                 (29U)
#define IVDSH_DID_REA_FWUPXREQ_D                 (30U)
/* Read from VM#3 */
#define IVDSH_DID_REA_VM3TO12_RESTART            (31U)

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
