/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  Serivice Application Interface                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  oxdocan_saif.h is included in oxdocan_sal.h.                                                                                     */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef OXDOCAN_SAIF_H
#define OXDOCAN_SAIF_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_SAIF_H_MAJOR                     (1U)
#define OXDOCAN_SAIF_H_MINOR                     (0U)
#define OXDOCAN_SAIF_H_PATCH                     (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_did_ssr_ch.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_DATA_XID_ML[].u2_req_nbyte                                                                        */
/*  oxdocan_xid_cfg.c / st_gp_OXDC_DATA_XID_ML[].u2_ans_nbyte                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DATA_REA_ANS_NB_A100                (32U)                   /* DataIdentifierIndex  */
#define OXDC_DATA_REA_ANS_NB_A002                (6U)                    /* GMT  */
#define OXDC_DATA_REA_ANS_NB_A003                (4U)                    /* Odo  */
#define OXDC_DATA_REA_ANS_NB_A005                (1U)                    /* Number of identified event  */
#define OXDC_DATA_REA_ANS_NB_A006                (5U)                    /* MostRecentTestFailed UserDefMemoryDTC  */
#define OXDC_DATA_REA_ANS_NB_A800                (7U)                    /* Time Stamp  */
#define OXDC_DATA_REA_ANS_NB_F186                (1U)                    /* Active Session  */
#define OXDC_DATA_REA_ANS_NB_A1XX                (32U)                   /* Support Information by Data Group  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/

#define OXDC_DATA_REA_ANS_NB_1001                (4U)
#define OXDC_DATA_REA_ANS_NB_1002                (2U)
#define OXDC_DATA_REA_ANS_NB_1003                (2U)
#define OXDC_DATA_REA_ANS_NB_1021                (1U)
#define OXDC_DATA_REA_ANS_NB_1022                (2U)
#define OXDC_DATA_REA_ANS_NB_1023                (2U)
#define OXDC_DATA_REA_ANS_NB_1024                (1U)
#define OXDC_DATA_REA_ANS_NB_1025                (1U)
#define OXDC_DATA_REA_ANS_NB_1027                (1U)
#define OXDC_DATA_REA_ANS_NB_1041                (1U)
#define OXDC_DATA_REA_ANS_NB_1042                (1U)
#define OXDC_DATA_REA_ANS_NB_1043                (2U)
#define OXDC_DATA_REA_ANS_NB_1044                (3U)
#define OXDC_DATA_REA_ANS_NB_1081                (1U)
#define OXDC_DATA_REA_ANS_NB_10A1                (12U)
#define OXDC_DATA_REA_ANS_NB_10A2                (24U)
#define OXDC_DATA_REA_ANS_NB_10A3                (30U)
#define OXDC_DATA_REA_ANS_NB_10A5                (12U)
#define OXDC_DATA_REA_ANS_NB_10A6                (2U)
#define OXDC_DATA_REA_ANS_NB_10A7                (96U)
#define OXDC_DATA_REA_ANS_NB_10A8                (22U)
#define OXDC_DATA_REA_ANS_NB_10AB                (12U)
#define OXDC_DATA_REA_ANS_NB_10AC                (1U)
#define OXDC_DATA_REA_ANS_NB_10AD                (12U)
#define OXDC_DATA_REA_ANS_NB_10AE                (33U)
#define OXDC_DATA_REA_ANS_NB_10AF                (12U)
#define OXDC_DATA_REA_ANS_NB_10B0                (11U)
#define OXDC_DATA_REA_ANS_NB_10B1                (28U)
#define OXDC_DATA_REA_ANS_NB_10C1                (8U)
#define OXDC_DATA_REA_ANS_NB_1141                (2U)
#define OXDC_DATA_REA_ANS_NB_1142                (2U)
#define OXDC_DATA_REA_ANS_NB_11A1                (2U)
#define OXDC_DATA_REA_ANS_NB_11A2                (80U)
#define OXDC_DATA_REA_ANS_NB_11A3                (2U)
#define OXDC_DATA_REA_ANS_NB_1241                (1U)
#define OXDC_DATA_REA_ANS_NB_12A1                (1U)
#define OXDC_DATA_REA_ANS_NB_14A1                (2U)
#define OXDC_DATA_REA_ANS_NB_15A1                (2U)
#define OXDC_DATA_REA_ANS_NB_1641                (2U)
#define OXDC_DATA_REA_ANS_NB_18A1                (2U)
#define OXDC_DATA_REA_ANS_NB_18A2                (2U)
#define OXDC_DATA_REA_ANS_NB_2002                (1U)
#define OXDC_DATA_REA_ANS_NB_2003                (2U)
#define OXDC_DATA_REA_ANS_NB_2041                (4U)
#define OXDC_DATA_REA_ANS_NB_2042                (1U)
#define OXDC_DATA_REA_ANS_NB_2043                (1U)
#define OXDC_DATA_REA_ANS_NB_2045                (1U)
#define OXDC_DATA_REA_ANS_NB_20C2                (1U)
#define OXDC_DATA_REA_ANS_NB_2202                (1U)
#define OXDC_DATA_REA_ANS_NB_2203                (1U)
#define OXDC_DATA_REA_ANS_NB_2204                (2U)
#define OXDC_DATA_REA_ANS_NB_2803                (2U)
#define OXDC_DATA_REA_ANS_NB_2804                (2U)
#define OXDC_DATA_REA_ANS_NB_2805                (2U)
#define OXDC_DATA_REA_ANS_NB_2806                (2U)
#define OXDC_DATA_REA_ANS_NB_2809                (2U)
#define OXDC_DATA_REA_ANS_NB_280B                (2U)
#define OXDC_DATA_REA_ANS_NB_280C                (1U)
#define OXDC_DATA_REA_ANS_NB_2821                (4U)
#define OXDC_DATA_REA_ANS_NB_2822                (4U)
#define OXDC_DATA_REA_ANS_NB_2823                (4U)
#define OXDC_DATA_REA_ANS_NB_2824                (4U)
#define OXDC_DATA_REA_ANS_NB_2825                (4U)
#define OXDC_DATA_REA_ANS_NB_2827                (4U)
#define OXDC_DATA_REA_ANS_NB_2829                (8U)
#define OXDC_DATA_REA_ANS_NB_2831                (2U)
#define OXDC_DATA_REA_ANS_NB_2901                (2U)
#define OXDC_DATA_REA_ANS_NB_2911                (4U)
#define OXDC_DATA_REA_ANS_NB_2912                (4U)
#define OXDC_DATA_REA_ANS_NB_2921                (4U)
#define OXDC_DATA_REA_ANS_NB_2922                (2U)
#define OXDC_DATA_REA_ANS_NB_2931                (4U)
#define OXDC_DATA_REA_ANS_NB_2932                (4U)
#define OXDC_DATA_REA_ANS_NB_2933                (2U)
#define OXDC_DATA_REA_ANS_NB_2941                (4U)
#define OXDC_DATA_REA_ANS_NB_2942                (4U)
#define OXDC_DATA_REA_ANS_NB_2943                (2U)
#define OXDC_DATA_REA_ANS_NB_2944                (1U)
#define OXDC_DATA_REA_ANS_NB_2951                (4U)
#define OXDC_DATA_REA_ANS_NB_2952                (6U)
#define OXDC_DATA_REA_ANS_NB_2961                (4U)
#define OXDC_DATA_REA_ANS_NB_2981                (2U)
#define OXDC_DATA_REA_ANS_NB_2A01                (4U)
#define OXDC_DATA_REA_ANS_NB_2A21                (4U)
#define OXDC_DATA_REA_ANS_NB_2A22                (2U)
#define OXDC_DATA_REA_ANS_NB_2B01                (2U)
#define OXDC_DATA_REA_ANS_NB_A007                (1U)
#define OXDC_DATA_REA_ANS_NB_A008                (1U)
#define OXDC_DATA_REA_ANS_NB_A00A                (1U)
#define OXDC_DATA_REA_ANS_NB_AA00                (4U)
#define OXDC_DATA_REA_ANS_NB_AB00                (1U)
#define OXDC_DATA_REA_ANS_NB_AB01                (1U)
#define OXDC_DATA_REA_ANS_NB_AB02                (4U)
#define OXDC_DATA_REA_ANS_NB_F050                (16U)
#define OXDC_DATA_REA_ANS_NB_F07F                (0U)
#define OXDC_DATA_REA_ANS_NB_F082                (66U)
#define OXDC_DATA_REA_ANS_NB_F083                (66U)
#define OXDC_DATA_REA_ANS_NB_F084                (66U)
#define OXDC_DATA_REA_ANS_NB_F085                (66U)
#define OXDC_DATA_REA_ANS_NB_F120                (24U)
#define OXDC_DATA_REA_ANS_NB_F121                (24U)
#define OXDC_DATA_REA_ANS_NB_F122                (24U)
#define OXDC_DATA_REA_ANS_NB_F123                (24U)
#define OXDC_DATA_REA_ANS_NB_F124                (24U)
#define OXDC_DATA_REA_ANS_NB_F125                (24U)
#define OXDC_DATA_REA_ANS_NB_F188                (104U)
#define OXDC_DATA_REA_ANS_NB_F18A                (2U)
#define OXDC_DATA_REA_ANS_NB_F18C                (20U)
#define OXDC_DATA_REA_ANS_NB_F191                (41U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DATA_WRI_REQ_NB_2002                (1U)
#define OXDC_DATA_WRI_REQ_NB_2003                (2U)
#define OXDC_DATA_WRI_REQ_NB_2041                (4U)
#define OXDC_DATA_WRI_REQ_NB_2042                (1U)
#define OXDC_DATA_WRI_REQ_NB_2043                (1U)
#define OXDC_DATA_WRI_REQ_NB_2045                (1U)
#define OXDC_DATA_WRI_REQ_NB_20C2                (1U)
#define OXDC_DATA_WRI_REQ_NB_2202                (1U)
#define OXDC_DATA_WRI_REQ_NB_2203                (1U)
#define OXDC_DATA_WRI_REQ_NB_2204                (2U)
#define OXDC_DATA_WRI_REQ_NB_AA00                (4U)
#define OXDC_DATA_WRI_REQ_NB_F050                (16U)
#define OXDC_DATA_WRI_REQ_NB_F122                (24U)
#define OXDC_DATA_WRI_REQ_NB_F123                (24U)
#define OXDC_DATA_WRI_REQ_NB_F124                (24U)
#define OXDC_DATA_WRI_REQ_NB_F125                (24U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DATA_IOC_REQ_NB_2803                (4U)
#define OXDC_DATA_IOC_REQ_NB_2804                (4U)
#define OXDC_DATA_IOC_REQ_NB_2805                (4U)
#define OXDC_DATA_IOC_REQ_NB_2806                (4U)
#define OXDC_DATA_IOC_REQ_NB_2809                (4U)
#define OXDC_DATA_IOC_REQ_NB_280B                (4U)
#define OXDC_DATA_IOC_REQ_NB_280C                (2U)
#define OXDC_DATA_IOC_REQ_NB_2821                (8U)
#define OXDC_DATA_IOC_REQ_NB_2822                (8U)
#define OXDC_DATA_IOC_REQ_NB_2823                (8U)
#define OXDC_DATA_IOC_REQ_NB_2824                (8U)
#define OXDC_DATA_IOC_REQ_NB_2825                (8U)
#define OXDC_DATA_IOC_REQ_NB_2827                (8U)
#define OXDC_DATA_IOC_REQ_NB_2829                (16U)
#define OXDC_DATA_IOC_REQ_NB_2831                (4U)
#define OXDC_DATA_IOC_REQ_NB_2901                (4U)
#define OXDC_DATA_IOC_REQ_NB_2911                (8U)
#define OXDC_DATA_IOC_REQ_NB_2912                (8U)
#define OXDC_DATA_IOC_REQ_NB_2921                (8U)
#define OXDC_DATA_IOC_REQ_NB_2922                (4U)
#define OXDC_DATA_IOC_REQ_NB_2931                (8U)
#define OXDC_DATA_IOC_REQ_NB_2932                (8U)
#define OXDC_DATA_IOC_REQ_NB_2933                (4U)
#define OXDC_DATA_IOC_REQ_NB_2941                (8U)
#define OXDC_DATA_IOC_REQ_NB_2942                (8U)
#define OXDC_DATA_IOC_REQ_NB_2943                (4U)
#define OXDC_DATA_IOC_REQ_NB_2944                (2U)
#define OXDC_DATA_IOC_REQ_NB_2951                (8U)
#define OXDC_DATA_IOC_REQ_NB_2952                (12U)
#define OXDC_DATA_IOC_REQ_NB_2961                (8U)
#define OXDC_DATA_IOC_REQ_NB_2981                (4U)
#define OXDC_DATA_IOC_REQ_NB_2A01                (8U)
#define OXDC_DATA_IOC_REQ_NB_2A21                (8U)
#define OXDC_DATA_IOC_REQ_NB_2A22                (2U)
#define OXDC_DATA_IOC_REQ_NB_2B01                (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_01[].u2_req_nbyte                                                                  */
/*  oxdocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_01[].u2_ans_nbyte                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_ROUT_STA_REQ_NB_11FD                (0U)
#define OXDC_ROUT_STA_ANS_NB_11FD                (1U)

#define OXDC_ROUT_STA_REQ_NB_11FF                (0U)
#define OXDC_ROUT_STA_ANS_NB_11FF                (1U)

#define OXDC_ROUT_STA_REQ_NB_D000                (4U)
#define OXDC_ROUT_STA_ANS_NB_D000                (263U)

#define OXDC_ROUT_STA_REQ_NB_D001                (0U)
#define OXDC_ROUT_STA_ANS_NB_D001                (1U)

#define OXDC_ROUT_STA_REQ_NB_DA00                (0U)
#define OXDC_ROUT_STA_ANS_NB_DA00                (1U)

#define OXDC_ROUT_STA_REQ_NB_DB01                (0U)
#define OXDC_ROUT_STA_ANS_NB_DB01                (2U)

#define OXDC_ROUT_STA_REQ_NB_DB03                (0U)
#define OXDC_ROUT_STA_ANS_NB_DB03                (2U)

#define OXDC_ROUT_STA_REQ_NB_DD01                (67U)
#define OXDC_ROUT_STA_ANS_NB_DD01                (3U)

#define OXDC_ROUT_STA_REQ_NB_DD02                (0U)
#define OXDC_ROUT_STA_ANS_NB_DD02                (2U)

#define OXDC_ROUT_STA_REQ_NB_FF00                (9U)
#define OXDC_ROUT_STA_ANS_NB_FF00                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/

#define OXDC_ROUT_STA_REQ_NB_D100                (0U)                    /* RoutineIdentifierIndex  */
#define OXDC_ROUT_STA_ANS_NB_D100                (33U)                   /* RoutineIdentifierIndex  */

#define OXDC_ROUT_STA_REQ_NB_D1XX                (0U)                    /* Support Information by Routine Group  */
#define OXDC_ROUT_STA_ANS_NB_D1XX                (33U)                   /* Support Information by Routine Group  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_02[].u2_req_nbyte                                                                  */
/*  oxdocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_02[].u2_ans_nbyte                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_03[].u2_req_nbyte                                                                  */
/*  oxdocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_03[].u2_ans_nbyte                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_ROUT_RES_REQ_NB_D001                (0U)
#define OXDC_ROUT_RES_ANS_NB_D001                (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_rebyid.c                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_REBYID_NUMOFDID_MAX                 (6U)
#define OXDC_REBYID_DIDMAX_PFYS                  (6U)
#define OXDC_REBYID_DIDMAX_FUNC                  (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_esi_cfg.c / st_gp_TYDC_ESI_CFG[].u2_req_nbyte                                                                            */
/*  tydocan_esi_cfg.c / st_gp_TYDC_ESI_CFG[].u2_ans_nbyte                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_ESI_REQ_NB_22FD11XX                 (3U)
#define OXDC_ESI_ANS_NB_22FD11XX                 (4U)

#define OXDC_ESI_REQ_NB_22FD60XX                 (3U)
#define OXDC_ESI_ANS_NB_22FD60XX                 (14U)

#define OXDC_ESI_REQ_NB_2FFD80XX                 (3U)
#define OXDC_ESI_ANS_NB_2FFD80XX                 (3U)

#define OXDC_ESI_REQ_NB_22FDC0XX                 (4U)
#define OXDC_ESI_ANS_NB_22FDC0XX                 (6U)

#define OXDC_ESI_REQ_NB_2EFDD0XX                 (4U)
#define OXDC_ESI_ANS_NB_2EFDD0XX                 (4U)

#define OXDC_ESI_REQ_NB_22FDD1XX                 (4U)
#define OXDC_ESI_ANS_NB_22FDD1XX                 (5U)

#define OXDC_ESI_REQ_NB_2EFDE0XX                 (3U)
#define OXDC_ESI_ANS_NB_2EFDE0XX                 (4U)

#define OXDC_ESI_REQ_NB_1101XXXX                 (2U)
#define OXDC_ESI_ANS_NB_1101XXXX                 (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_did_ssr_cfg.c / st_gp_OXDC_DID_SSR_CH_CFG [].u1_num_rec                                                                  */
/*  oxdocan_did_ssr_cfg.c / st_gp_OXDC_DID_SSR_CH_CFG [].u1_mem_nbyte                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DID_SSR_NUM_REC_11A2                (10U)
#define OXDC_DID_SSR_MEM_NB_11A2                 (24U)
#define OXDC_DID_SSR_NUM_REC_10A1                (3U)
#if 0/*Phase6Diag Stub*/
#define OXDC_DID_SSR_MEM_NB_10A1                 (24U)
#else
#define OXDC_DID_SSR_MEM_NB_10A1                 (20U)
#endif

/*Phase6Diag Stub*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_ssr_cfg.c / st_gp_TYDC_SSR_CH_CFG [].u1_num_rec                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_SSR_NUM_REC_AB_F001                 (2U)
#define TYDC_SSR_NUM_REC_AB_F002                 (2U)
#define TYDC_SSR_NUM_REC_AB_F007                 (2U)
#define TYDC_SSR_NUM_REC_AB_F008                 (2U)
#define TYDC_SSR_NUM_REC_AB_F009                 (2U)
#define TYDC_SSR_NUM_REC_AB_F00A                 (2U)
#define TYDC_SSR_NUM_REC_AB_F020                 (4U)
#define TYDC_SSR_NUM_REC_AB_F014                 (5U)
#define TYDC_SSR_NUM_REC_AB_F01B                 (2U)

#define TYDC_SSR_NUM_REC_22_10A2                 (3U)
#define TYDC_SSR_NUM_REC_22_10A3                 (3U)
#define TYDC_SSR_NUM_REC_22_10AB                 (3U)
#define TYDC_SSR_NUM_REC_22_10AD                 (3U)
#define TYDC_SSR_NUM_REC_BA_D1L1                 (5U)
#define TYDC_SSR_NUM_REC_BA_RCAR                 (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_SSR_NVM_NB_22_10A2                  (24U)
#define TYDC_SSR_NVM_NB_22_10A3                  (28U)
#define TYDC_SSR_NVM_NB_22_10AB                  (20U)
#define TYDC_SSR_NVM_NB_22_10AD                  (20U)
#define TYDC_SSR_NVM_NB_BA_D1L1                  (24U)
#define TYDC_SSR_NVM_NB_BA_RCAR                  (20U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_rob_cfg.c / st_gp_TYDC_ROB_CFG[].u2_ssr_nbyte                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_ROB_SSR_NB_F007                     (203U)
#define TYDC_ROB_SSR_NB_F008                     (83U)
#define TYDC_ROB_SSR_NB_F009                     (43U)
#define TYDC_ROB_SSR_NB_F00A                     (43U)
#define TYDC_ROB_SSR_NB_F020                     (38U)

/*Phase6Diag Stub*/

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
/*  tydocan_dtc_cfg.c / st_gp_TYDC_DTC_COM_RX[].fp_u1_SUP                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANDtcSup_U0111(void);
U1      u1_g_oXDoCANDtcSup_U025E(void);
U1      u1_g_oXDoCANDtcSup_U1110(void);
/*Phase6Diag Stub*/
U1      u1_g_oXDoCANDtcSup_B1321(void);
/*Phase6Diag Stub*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_dtc_cfg.c / st_gp_TYDC_DTC_TR_CHK[].fp_u1_CHK                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANDtcTrchk_B1328(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1500(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1501(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B150B(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1510(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1511(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1518(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1519(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_U2303(const U2 u2_a_ELPSD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_DATA_XID[].fp_u1_SUP                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANDidSup_1001(void);
U1      u1_g_oXDoCANDidSup_1002(void);
U1      u1_g_oXDoCANDidSup_1003(void);
U1      u1_g_oXDoCANDidSup_1022(void);
U1      u1_g_oXDoCANDidSup_1023(void);
U1      u1_g_oXDoCANDidSup_1025(void);
U1      u1_g_oXDoCANDidSup_1027(void);
U1      u1_g_oXDoCANDidSup_1042(void);
U1      u1_g_oXDoCANDidSup_1043(void);
U1      u1_g_oXDoCANDidSup_1044(void);
U1      u1_g_oXDoCANDidSup_10A1(void);
U1      u1_g_oXDoCANDidSup_10A2(void);
U1      u1_g_oXDoCANDidSup_10A5(void);
U1      u1_g_oXDoCANDidSup_10A7(void);
U1      u1_g_oXDoCANDidSup_10A8(void);
U1      u1_g_oXDoCANDidSup_10AB(void);
U1      u1_g_oXDoCANDidSup_10AC(void);
U1      u1_g_oXDoCANDidSup_10AD(void);
U1      u1_g_oXDoCANDidSup_10AE(void);
U1      u1_g_oXDoCANDidSup_10AF(void);
U1      u1_g_oXDoCANDidSup_10B0(void);
U1      u1_g_oXDoCANDidSup_10B1(void);
U1      u1_g_oXDoCANDidSup_1142(void);
U1      u1_g_oXDoCANDidSup_1241(void);
U1      u1_g_oXDoCANDidSup_12A1(void);
U1      u1_g_oXDoCANDidSup_1641(void);
U1      u1_g_oXDoCANDidSup_18A1(void);
U1      u1_g_oXDoCANDidSup_18A2(void);
U1      u1_g_oXDoCANDidSup_2003(void);
U1      u1_g_oXDoCANDidSup_2041(void);
U1      u1_g_oXDoCANDidSup_2042(void);
U1      u1_g_oXDoCANDidSup_2045(void);
U1      u1_g_oXDoCANDidSup_20C2(void);
U1      u1_g_oXDoCANDidSup_2202(void);
U1      u1_g_oXDoCANDidSup_2203(void);
U1      u1_g_oXDoCANDidSup_2204(void);
U1      u1_g_oXDoCANDidSup_2803(void);
U1      u1_g_oXDoCANDidSup_2804(void);
U1      u1_g_oXDoCANDidSup_2805(void);
U1      u1_g_oXDoCANDidSup_2806(void);
U1      u1_g_oXDoCANDidSup_2809(void);
U1      u1_g_oXDoCANDidSup_280B(void);
U1      u1_g_oXDoCANDidSup_280C(void);
U1      u1_g_oXDoCANDidSup_2901(void);
U1      u1_g_oXDoCANDidSup_2911(void);
U1      u1_g_oXDoCANDidSup_2912(void);
U1      u1_g_oXDoCANDidSup_2921(void);
U1      u1_g_oXDoCANDidSup_2922(void);
U1      u1_g_oXDoCANDidSup_2931(void);
U1      u1_g_oXDoCANDidSup_2932(void);
U1      u1_g_oXDoCANDidSup_2933(void);
U1      u1_g_oXDoCANDidSup_2941(void);
U1      u1_g_oXDoCANDidSup_2942(void);
U1      u1_g_oXDoCANDidSup_2943(void);
U1      u1_g_oXDoCANDidSup_2944(void);
U1      u1_g_oXDoCANDidSup_2951(void);
U1      u1_g_oXDoCANDidSup_2952(void);
U1      u1_g_oXDoCANDidSup_2961(void);
U1      u1_g_oXDoCANDidSup_2981(void);
U1      u1_g_oXDoCANDidSup_2B01(void);
U1      u1_g_oXDoCANDidSup_A00A(void);
U1      u1_g_oXDoCANDidSup_AB02(void);
U1      u1_g_oXDoCANDidSup_F050(void);
U1      u1_g_oXDoCANDidSup_F122(void);
U1      u1_g_oXDoCANDidSup_F123(void);
U1      u1_g_oXDoCANDidSup_F124(void);
U1      u1_g_oXDoCANDidSup_F125(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_DATA_CFG[].fp_u1_READ                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRebyId_A100(U1 * u1_ap_ans, const U2 u2_a_ELPSD);     /* DataIdentifierIndex                  */
U1      u1_g_oXDoCANRebyId_A002(U1 * u1_ap_ans, const U2 u2_a_ELPSD);     /* GMT                                  */
U1      u1_g_oXDoCANRebyId_A003(U1 * u1_ap_ans, const U2 u2_a_ELPSD);     /* Odo                                  */
U1      u1_g_oXDoCANRebyId_A005(U1 * u1_ap_ans, const U2 u2_a_ELPSD);     /* Number of identified event           */
U1      u1_g_oXDoCANRebyId_A006(U1 * u1_ap_ans, const U2 u2_a_ELPSD);     /* MostRecentTestFailed UserDefMemoryDTC*/
U1      u1_g_oXDoCANRebyId_A800(U1 * u1_ap_ans, const U2 u2_a_ELPSD);     /* Time Stamp                           */
U1      u1_g_oXDoCANRebyId_F186(U1 * u1_ap_ans, const U2 u2_a_ELPSD);     /* Active Session                       */
U1      u1_g_oXDoCANRebyId_A1XX(U1 * u1_ap_ans, const U2 u2_a_ELPSD);     /* Support Information by Data Group    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/

U1      u1_g_oXDoCANRebyId_1001(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1002(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1003(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1021(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1022(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1023(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1024(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1025(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1027(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1041(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1042(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1043(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1044(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1081(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A2(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A3(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A5(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A6(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A7(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A8(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10AB(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10AC(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10AD(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10AE(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10AF(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10B0(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10B1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10C1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1141(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1142(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_11A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_11A2(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_11A3(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1241(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_12A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_14A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_15A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1641(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_18A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_18A2(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2002(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2003(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2041(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2042(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2043(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2045(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_20C2(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2202(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2203(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2204(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2803(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2804(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2805(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2806(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2809(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_280B(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_280C(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2821(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2822(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2823(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2824(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2825(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2827(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2829(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2831(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2901(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2911(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2912(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2921(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2922(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2931(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2932(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2933(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2941(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2942(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2943(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2944(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2951(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2952(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2961(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2981(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2A01(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2A21(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2A22(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2B01(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_A007(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_A008(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_A00A(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_AA00(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_AB00(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_AB01(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_AB02(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F050(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F07F(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F082(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F083(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F084(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F085(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F120(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F121(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F122(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F123(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F124(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F125(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F188(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F18A(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F18C(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F191(U1 * u1_ap_ans, const U2 u2_a_ELPSD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_DATA_CFG[].fp_u1_WRITE                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANWrbyId_2002(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2003(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2041(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2042(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2043(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2045(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_20C2(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2202(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2203(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2204(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_AA00(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_F050(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_F122(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_F123(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_F124(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_F125(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_IOC_IF[].fp_u1_CSM_CHK                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANIocCsmchk_2803(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2804(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2805(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2806(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2809(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_280B(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_280C(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2821(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2822(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2823(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2824(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2825(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2827(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2829(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2831(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2901(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2911(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2912(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2921(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2922(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2931(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2932(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2933(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2941(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2942(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2943(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2944(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2951(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2952(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2961(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2981(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2A01(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2A21(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2A22(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2B01(const U1 u1_a_PRM, const U1 * u1_ap_CSM);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_IOC_IF[].fp_vd_ACT                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXDoCANIocAct_2803(void);
void    vd_g_oXDoCANIocAct_2804(void);
void    vd_g_oXDoCANIocAct_2805(void);
void    vd_g_oXDoCANIocAct_2806(void);
void    vd_g_oXDoCANIocAct_2809(void);
void    vd_g_oXDoCANIocAct_280B(void);
void    vd_g_oXDoCANIocAct_280C(void);
void    vd_g_oXDoCANIocAct_2821(void);
void    vd_g_oXDoCANIocAct_2822(void);
void    vd_g_oXDoCANIocAct_2823(void);
void    vd_g_oXDoCANIocAct_2824(void);
void    vd_g_oXDoCANIocAct_2825(void);
void    vd_g_oXDoCANIocAct_2827(void);
void    vd_g_oXDoCANIocAct_2829(void);
void    vd_g_oXDoCANIocAct_2831(void);
void    vd_g_oXDoCANIocAct_2901(void);
void    vd_g_oXDoCANIocAct_2911(void);
void    vd_g_oXDoCANIocAct_2912(void);
void    vd_g_oXDoCANIocAct_2921(void);
void    vd_g_oXDoCANIocAct_2922(void);
void    vd_g_oXDoCANIocAct_2931(void);
void    vd_g_oXDoCANIocAct_2932(void);
void    vd_g_oXDoCANIocAct_2933(void);
void    vd_g_oXDoCANIocAct_2941(void);
void    vd_g_oXDoCANIocAct_2942(void);
void    vd_g_oXDoCANIocAct_2943(void);
void    vd_g_oXDoCANIocAct_2944(void);
void    vd_g_oXDoCANIocAct_2951(void);
void    vd_g_oXDoCANIocAct_2952(void);
void    vd_g_oXDoCANIocAct_2961(void);
void    vd_g_oXDoCANIocAct_2981(void);
void    vd_g_oXDoCANIocAct_2A01(void);
void    vd_g_oXDoCANIocAct_2A21(void);
void    vd_g_oXDoCANIocAct_2A22(void);
void    vd_g_oXDoCANIocAct_2B01(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_IOC_IF[].fp_vd_DEACT                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXDoCANIocDeAct_2803(void);
void    vd_g_oXDoCANIocDeAct_2804(void);
void    vd_g_oXDoCANIocDeAct_2805(void);
void    vd_g_oXDoCANIocDeAct_2806(void);
void    vd_g_oXDoCANIocDeAct_2809(void);
void    vd_g_oXDoCANIocDeAct_280B(void);
void    vd_g_oXDoCANIocDeAct_280C(void);
void    vd_g_oXDoCANIocDeAct_2821(void);
void    vd_g_oXDoCANIocDeAct_2822(void);
void    vd_g_oXDoCANIocDeAct_2823(void);
void    vd_g_oXDoCANIocDeAct_2824(void);
void    vd_g_oXDoCANIocDeAct_2825(void);
void    vd_g_oXDoCANIocDeAct_2827(void);
void    vd_g_oXDoCANIocDeAct_2829(void);
void    vd_g_oXDoCANIocDeAct_2831(void);
void    vd_g_oXDoCANIocDeAct_2901(void);
void    vd_g_oXDoCANIocDeAct_2911(void);
void    vd_g_oXDoCANIocDeAct_2912(void);
void    vd_g_oXDoCANIocDeAct_2921(void);
void    vd_g_oXDoCANIocDeAct_2922(void);
void    vd_g_oXDoCANIocDeAct_2931(void);
void    vd_g_oXDoCANIocDeAct_2932(void);
void    vd_g_oXDoCANIocDeAct_2933(void);
void    vd_g_oXDoCANIocDeAct_2941(void);
void    vd_g_oXDoCANIocDeAct_2942(void);
void    vd_g_oXDoCANIocDeAct_2943(void);
void    vd_g_oXDoCANIocDeAct_2944(void);
void    vd_g_oXDoCANIocDeAct_2951(void);
void    vd_g_oXDoCANIocDeAct_2952(void);
void    vd_g_oXDoCANIocDeAct_2961(void);
void    vd_g_oXDoCANIocDeAct_2981(void);
void    vd_g_oXDoCANIocDeAct_2A01(void);
void    vd_g_oXDoCANIocDeAct_2A21(void);
void    vd_g_oXDoCANIocDeAct_2A22(void);
void    vd_g_oXDoCANIocDeAct_2B01(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_XID[].fp_u1_SUP                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRidSup_DB01(void);
U1      u1_g_oXDoCANRidSup_DB03(void);
U1      u1_g_oXDoCANRidSup_DD01(void);
U1      u1_g_oXDoCANRidSup_DD02(void);
U1      u1_g_oXDoCANRidSup_FF00(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_CFG[].fp_u1_COR_CHK                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRoutCorchk_D000(const U1 u1_a_SUBF, const U1 * u1_ap_COR);
U1      u1_g_oXDoCANRoutCorchk_DD01(const U1 u1_a_SUBF, const U1 * u1_ap_COR);
U1      u1_g_oXDoCANRoutCorchk_FF00(const U1 u1_a_SUBF, const U1 * u1_ap_COR);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_CFG[].fp_u1_START                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRoutStart_D100(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_D1XX(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRoutStart_11FD(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_11FF(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_D000(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_D001(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_DA00(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_DB01(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_DB03(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_DD01(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_DD02(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_FF00(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_CFG[].fp_fp_u1_STOP                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_CFG[].fp_fp_u1_RESULT                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRoutRslt_D001(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_esi_cfg.c / st_gp_TYDC_ESI_CFG[].fp_u1_TRX                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANEsiTRx_22FD11XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_22FD60XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_2FFD80XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_22FDC0XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_2EFDD0XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_22FDD1XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_2EFDE0XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_1101XXXX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* OXDOCAN_SAIF_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :                                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
