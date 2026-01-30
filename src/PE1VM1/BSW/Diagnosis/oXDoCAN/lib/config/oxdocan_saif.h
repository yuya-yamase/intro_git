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

#define OXDC_DATA_REA_ANS_NB_0105                (12U)
#define OXDC_DATA_REA_ANS_NB_0119                (4U)
#define OXDC_DATA_REA_ANS_NB_0204                (4U)
#define OXDC_DATA_REA_ANS_NB_1001                (4U)
#define OXDC_DATA_REA_ANS_NB_1002                (2U)
#define OXDC_DATA_REA_ANS_NB_1021                (1U)
#define OXDC_DATA_REA_ANS_NB_1022                (2U)
#define OXDC_DATA_REA_ANS_NB_1023                (2U)
#define OXDC_DATA_REA_ANS_NB_1024                (1U)
#define OXDC_DATA_REA_ANS_NB_1041                (1U)
#define OXDC_DATA_REA_ANS_NB_1042                (1U)
#define OXDC_DATA_REA_ANS_NB_10A1                (12U)
#define OXDC_DATA_REA_ANS_NB_10A2                (24U)
#define OXDC_DATA_REA_ANS_NB_10A3                (30U)
#define OXDC_DATA_REA_ANS_NB_10A4                (2U)
#define OXDC_DATA_REA_ANS_NB_10A5                (12U)
#define OXDC_DATA_REA_ANS_NB_1101                (6U)
#define OXDC_DATA_REA_ANS_NB_1141                (2U)
#define OXDC_DATA_REA_ANS_NB_11A1                (2U)
#define OXDC_DATA_REA_ANS_NB_11A2                (80U)
#define OXDC_DATA_REA_ANS_NB_1201                (2U)
#define OXDC_DATA_REA_ANS_NB_1241                (1U)
#define OXDC_DATA_REA_ANS_NB_12A1                (1U)
#define OXDC_DATA_REA_ANS_NB_1401                (2U)
#define OXDC_DATA_REA_ANS_NB_14A1                (2U)
#define OXDC_DATA_REA_ANS_NB_15A1                (2U)
#define OXDC_DATA_REA_ANS_NB_1641                (2U)
#define OXDC_DATA_REA_ANS_NB_2001                (2U)
#define OXDC_DATA_REA_ANS_NB_2002                (1U)
#define OXDC_DATA_REA_ANS_NB_2021                (2U)
#define OXDC_DATA_REA_ANS_NB_2041                (4U)
#define OXDC_DATA_REA_ANS_NB_2042                (1U)
#define OXDC_DATA_REA_ANS_NB_2043                (1U)
#define OXDC_DATA_REA_ANS_NB_2081                (2U)
#define OXDC_DATA_REA_ANS_NB_20C1                (1U)
#define OXDC_DATA_REA_ANS_NB_2801                (4U)
#define OXDC_DATA_REA_ANS_NB_2802                (4U)
#define OXDC_DATA_REA_ANS_NB_2803                (2U)
#define OXDC_DATA_REA_ANS_NB_2804                (2U)
#define OXDC_DATA_REA_ANS_NB_2805                (2U)
#define OXDC_DATA_REA_ANS_NB_2806                (2U)
#define OXDC_DATA_REA_ANS_NB_2807                (2U)
#define OXDC_DATA_REA_ANS_NB_2808                (2U)
#define OXDC_DATA_REA_ANS_NB_2809                (2U)
#define OXDC_DATA_REA_ANS_NB_280A                (2U)
#define OXDC_DATA_REA_ANS_NB_2821                (4U)
#define OXDC_DATA_REA_ANS_NB_2822                (4U)
#define OXDC_DATA_REA_ANS_NB_2823                (4U)
#define OXDC_DATA_REA_ANS_NB_2824                (4U)
#define OXDC_DATA_REA_ANS_NB_2825                (4U)
#define OXDC_DATA_REA_ANS_NB_2826                (4U)
#define OXDC_DATA_REA_ANS_NB_2827                (4U)
#define OXDC_DATA_REA_ANS_NB_2831                (2U)
#define OXDC_DATA_REA_ANS_NB_2832                (4U)
#define OXDC_DATA_REA_ANS_NB_2901                (2U)
#define OXDC_DATA_REA_ANS_NB_2911                (4U)
#define OXDC_DATA_REA_ANS_NB_2912                (4U)
#define OXDC_DATA_REA_ANS_NB_2921                (4U)
#define OXDC_DATA_REA_ANS_NB_2931                (4U)
#define OXDC_DATA_REA_ANS_NB_2932                (4U)
#define OXDC_DATA_REA_ANS_NB_2933                (2U)
#define OXDC_DATA_REA_ANS_NB_2941                (4U)
#define OXDC_DATA_REA_ANS_NB_2942                (4U)
#define OXDC_DATA_REA_ANS_NB_2943                (2U)
#define OXDC_DATA_REA_ANS_NB_2951                (4U)
#define OXDC_DATA_REA_ANS_NB_2952                (6U)
#define OXDC_DATA_REA_ANS_NB_2961                (4U)
#define OXDC_DATA_REA_ANS_NB_2971                (2U)
#define OXDC_DATA_REA_ANS_NB_2981                (2U)
#define OXDC_DATA_REA_ANS_NB_2A01                (4U)
#define OXDC_DATA_REA_ANS_NB_2A21                (4U)
#define OXDC_DATA_REA_ANS_NB_2A22                (2U)
#define OXDC_DATA_REA_ANS_NB_AB00                (1U)
#define OXDC_DATA_REA_ANS_NB_AB01                (1U)
#define OXDC_DATA_REA_ANS_NB_AB02                (4U)
#define OXDC_DATA_REA_ANS_NB_F050                (16U)
#define OXDC_DATA_REA_ANS_NB_F080                (384U)
#define OXDC_DATA_REA_ANS_NB_F081                (384U)
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
#define OXDC_DATA_REA_ANS_NB_F181                (49U)
#define OXDC_DATA_REA_ANS_NB_F188                (19U)
#define OXDC_DATA_REA_ANS_NB_F191                (15U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DATA_WRI_REQ_NB_0204                (4U)
#define OXDC_DATA_WRI_REQ_NB_2001                (2U)
#define OXDC_DATA_WRI_REQ_NB_2002                (1U)
#define OXDC_DATA_WRI_REQ_NB_2021                (2U)
#define OXDC_DATA_WRI_REQ_NB_2041                (4U)
#define OXDC_DATA_WRI_REQ_NB_2042                (1U)
#define OXDC_DATA_WRI_REQ_NB_2043                (1U)
#define OXDC_DATA_WRI_REQ_NB_2081                (2U)
#define OXDC_DATA_WRI_REQ_NB_20C1                (1U)
#define OXDC_DATA_WRI_REQ_NB_F050                (16U)
#define OXDC_DATA_WRI_REQ_NB_F122                (24U)
#define OXDC_DATA_WRI_REQ_NB_F123                (24U)
#define OXDC_DATA_WRI_REQ_NB_F124                (24U)
#define OXDC_DATA_WRI_REQ_NB_F125                (24U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DATA_IOC_REQ_NB_2801                (4U)
#define OXDC_DATA_IOC_REQ_NB_2802                (4U)
#define OXDC_DATA_IOC_REQ_NB_2803                (2U)
#define OXDC_DATA_IOC_REQ_NB_2804                (2U)
#define OXDC_DATA_IOC_REQ_NB_2805                (2U)
#define OXDC_DATA_IOC_REQ_NB_2806                (2U)
#define OXDC_DATA_IOC_REQ_NB_2807                (2U)
#define OXDC_DATA_IOC_REQ_NB_2808                (2U)
#define OXDC_DATA_IOC_REQ_NB_2809                (2U)
#define OXDC_DATA_IOC_REQ_NB_280A                (2U)
#define OXDC_DATA_IOC_REQ_NB_2821                (4U)
#define OXDC_DATA_IOC_REQ_NB_2822                (4U)
#define OXDC_DATA_IOC_REQ_NB_2823                (4U)
#define OXDC_DATA_IOC_REQ_NB_2824                (4U)
#define OXDC_DATA_IOC_REQ_NB_2825                (4U)
#define OXDC_DATA_IOC_REQ_NB_2826                (4U)
#define OXDC_DATA_IOC_REQ_NB_2827                (4U)
#define OXDC_DATA_IOC_REQ_NB_2831                (2U)
#define OXDC_DATA_IOC_REQ_NB_2832                (4U)
#define OXDC_DATA_IOC_REQ_NB_2901                (2U)
#define OXDC_DATA_IOC_REQ_NB_2911                (4U)
#define OXDC_DATA_IOC_REQ_NB_2912                (4U)
#define OXDC_DATA_IOC_REQ_NB_2921                (4U)
#define OXDC_DATA_IOC_REQ_NB_2931                (4U)
#define OXDC_DATA_IOC_REQ_NB_2932                (4U)
#define OXDC_DATA_IOC_REQ_NB_2933                (2U)
#define OXDC_DATA_IOC_REQ_NB_2941                (4U)
#define OXDC_DATA_IOC_REQ_NB_2942                (4U)
#define OXDC_DATA_IOC_REQ_NB_2943                (2U)
#define OXDC_DATA_IOC_REQ_NB_2951                (4U)
#define OXDC_DATA_IOC_REQ_NB_2952                (6U)
#define OXDC_DATA_IOC_REQ_NB_2961                (4U)
#define OXDC_DATA_IOC_REQ_NB_2971                (2U)
#define OXDC_DATA_IOC_REQ_NB_2981                (2U)
#define OXDC_DATA_IOC_REQ_NB_2A01                (4U)
#define OXDC_DATA_IOC_REQ_NB_2A21                (4U)
#define OXDC_DATA_IOC_REQ_NB_2A22                (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_01[].u2_req_nbyte                                                                  */
/*  oxdocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_01[].u2_ans_nbyte                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_ROUT_STA_REQ_NB_1004                (2U)
#define OXDC_ROUT_STA_ANS_NB_1004                (0U)

#define OXDC_ROUT_STA_REQ_NB_1101                (1U)
#define OXDC_ROUT_STA_ANS_NB_1101                (0U)

#define OXDC_ROUT_STA_REQ_NB_11FD                (0U)
#define OXDC_ROUT_STA_ANS_NB_11FD                (0U)

#define OXDC_ROUT_STA_REQ_NB_11FE                (0U)
#define OXDC_ROUT_STA_ANS_NB_11FE                (0U)

#define OXDC_ROUT_STA_REQ_NB_11FF                (0U)
#define OXDC_ROUT_STA_ANS_NB_11FF                (0U)

#define OXDC_ROUT_STA_REQ_NB_D000                (4U)
#define OXDC_ROUT_STA_ANS_NB_D000                (263U)

#define OXDC_ROUT_STA_REQ_NB_D001                (0U)
#define OXDC_ROUT_STA_ANS_NB_D001                (1U)

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
#define OXDC_ROUT_RES_REQ_NB_1101                (0U)
#define OXDC_ROUT_RES_ANS_NB_1101                (0U)

#define OXDC_ROUT_RES_REQ_NB_D001                (0U)
#define OXDC_ROUT_RES_ANS_NB_D001                (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_rebyid.c                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_REBYID_NUMOFDID_MAX                 (6U)
#define OXDC_REBYID_DIDMAX_PFYS                  (6U)
#define OXDC_REBYID_DIDMAX_FUNC                  (6U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_esi_cfg.c / st_gp_TYDC_ESI_CFG[].u2_req_nbyte                                                                            */
/*  tydocan_esi_cfg.c / st_gp_TYDC_ESI_CFG[].u2_ans_nbyte                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_did_ssr_cfg.c / st_gp_OXDC_DID_SSR_CH_CFG [].u1_num_rec                                                                  */
/*  oxdocan_did_ssr_cfg.c / st_gp_OXDC_DID_SSR_CH_CFG [].u1_mem_nbyte                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DID_SSR_NUM_REC_11A2                (10U)
#define OXDC_DID_SSR_MEM_NB_11A2                 (24U)
#define OXDC_DID_SSR_NUM_REC_10A1                (3U)
#define OXDC_DID_SSR_MEM_NB_10A1                 (24U)

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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_dtc_cfg.c / st_gp_TYDC_DTC_TR_CHK[].fp_u1_CHK                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANDtcTrchk_U1807(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1500(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1501(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1502(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1503(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1504(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1505(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1506(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1507(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1508(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1509(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B150A(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B150B(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B150C(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B150D(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1510(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1511(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1518(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B1519(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_B151A(const U2 u2_a_ELPSD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_DATA_XID[].fp_u1_SUP                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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

U1      u1_g_oXDoCANRebyId_0105(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_0119(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_0204(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1001(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1002(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1021(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1022(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1023(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1024(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1041(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1042(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A2(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A3(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A4(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10A5(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1101(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1141(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_11A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_11A2(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1201(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1241(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_12A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1401(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_14A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_15A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1641(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2001(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2002(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2021(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2041(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2042(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2043(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2081(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_20C1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2801(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2802(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2803(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2804(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2805(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2806(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2807(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2808(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2809(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_280A(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2821(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2822(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2823(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2824(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2825(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2826(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2827(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2831(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2832(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2901(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2911(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2912(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2921(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2931(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2932(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2933(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2941(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2942(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2943(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2951(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2952(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2961(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2971(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2981(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2A01(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2A21(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_2A22(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_AB00(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_AB01(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_AB02(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F080(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F081(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F082(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F083(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F084(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F085(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F120(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F121(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F181(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F188(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F191(U1 * u1_ap_ans, const U2 u2_a_ELPSD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_DATA_CFG[].fp_u1_WRITE                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANWrbyId_0204(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2001(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2002(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2021(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2041(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2042(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2043(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_2081(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_20C1(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_F050(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_F122(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_F123(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_F124(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANWrbyId_F125(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_IOC_IF[].fp_u1_CSM_CHK                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANIocCsmchk_2801(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2802(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2803(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2804(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2805(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2806(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2807(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2808(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2809(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_280A(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2821(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2822(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2823(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2824(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2825(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2826(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2827(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2831(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2832(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2901(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2911(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2912(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2921(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2931(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2932(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2933(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2941(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2942(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2943(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2951(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2952(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2961(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2971(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2981(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2A01(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2A21(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_2A22(const U1 u1_a_PRM, const U1 * u1_ap_CSM);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_IOC_IF[].fp_vd_ACT                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXDoCANIocAct_2801(void);
void    vd_g_oXDoCANIocAct_2802(void);
void    vd_g_oXDoCANIocAct_2803(void);
void    vd_g_oXDoCANIocAct_2804(void);
void    vd_g_oXDoCANIocAct_2805(void);
void    vd_g_oXDoCANIocAct_2806(void);
void    vd_g_oXDoCANIocAct_2807(void);
void    vd_g_oXDoCANIocAct_2808(void);
void    vd_g_oXDoCANIocAct_2809(void);
void    vd_g_oXDoCANIocAct_280A(void);
void    vd_g_oXDoCANIocAct_2821(void);
void    vd_g_oXDoCANIocAct_2822(void);
void    vd_g_oXDoCANIocAct_2823(void);
void    vd_g_oXDoCANIocAct_2824(void);
void    vd_g_oXDoCANIocAct_2825(void);
void    vd_g_oXDoCANIocAct_2826(void);
void    vd_g_oXDoCANIocAct_2827(void);
void    vd_g_oXDoCANIocAct_2831(void);
void    vd_g_oXDoCANIocAct_2832(void);
void    vd_g_oXDoCANIocAct_2901(void);
void    vd_g_oXDoCANIocAct_2911(void);
void    vd_g_oXDoCANIocAct_2912(void);
void    vd_g_oXDoCANIocAct_2921(void);
void    vd_g_oXDoCANIocAct_2931(void);
void    vd_g_oXDoCANIocAct_2932(void);
void    vd_g_oXDoCANIocAct_2933(void);
void    vd_g_oXDoCANIocAct_2941(void);
void    vd_g_oXDoCANIocAct_2942(void);
void    vd_g_oXDoCANIocAct_2943(void);
void    vd_g_oXDoCANIocAct_2951(void);
void    vd_g_oXDoCANIocAct_2952(void);
void    vd_g_oXDoCANIocAct_2961(void);
void    vd_g_oXDoCANIocAct_2971(void);
void    vd_g_oXDoCANIocAct_2981(void);
void    vd_g_oXDoCANIocAct_2A01(void);
void    vd_g_oXDoCANIocAct_2A21(void);
void    vd_g_oXDoCANIocAct_2A22(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_IOC_IF[].fp_vd_DEACT                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXDoCANIocDeAct_2801(void);
void    vd_g_oXDoCANIocDeAct_2802(void);
void    vd_g_oXDoCANIocDeAct_2803(void);
void    vd_g_oXDoCANIocDeAct_2804(void);
void    vd_g_oXDoCANIocDeAct_2805(void);
void    vd_g_oXDoCANIocDeAct_2806(void);
void    vd_g_oXDoCANIocDeAct_2807(void);
void    vd_g_oXDoCANIocDeAct_2808(void);
void    vd_g_oXDoCANIocDeAct_2809(void);
void    vd_g_oXDoCANIocDeAct_280A(void);
void    vd_g_oXDoCANIocDeAct_2821(void);
void    vd_g_oXDoCANIocDeAct_2822(void);
void    vd_g_oXDoCANIocDeAct_2823(void);
void    vd_g_oXDoCANIocDeAct_2824(void);
void    vd_g_oXDoCANIocDeAct_2825(void);
void    vd_g_oXDoCANIocDeAct_2826(void);
void    vd_g_oXDoCANIocDeAct_2827(void);
void    vd_g_oXDoCANIocDeAct_2831(void);
void    vd_g_oXDoCANIocDeAct_2832(void);
void    vd_g_oXDoCANIocDeAct_2901(void);
void    vd_g_oXDoCANIocDeAct_2911(void);
void    vd_g_oXDoCANIocDeAct_2912(void);
void    vd_g_oXDoCANIocDeAct_2921(void);
void    vd_g_oXDoCANIocDeAct_2931(void);
void    vd_g_oXDoCANIocDeAct_2932(void);
void    vd_g_oXDoCANIocDeAct_2933(void);
void    vd_g_oXDoCANIocDeAct_2941(void);
void    vd_g_oXDoCANIocDeAct_2942(void);
void    vd_g_oXDoCANIocDeAct_2943(void);
void    vd_g_oXDoCANIocDeAct_2951(void);
void    vd_g_oXDoCANIocDeAct_2952(void);
void    vd_g_oXDoCANIocDeAct_2961(void);
void    vd_g_oXDoCANIocDeAct_2971(void);
void    vd_g_oXDoCANIocDeAct_2981(void);
void    vd_g_oXDoCANIocDeAct_2A01(void);
void    vd_g_oXDoCANIocDeAct_2A21(void);
void    vd_g_oXDoCANIocDeAct_2A22(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_XID[].fp_u1_SUP                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRidSup_1101(void);
U1      u1_g_oXDoCANRidSup_11FD(void);
U1      u1_g_oXDoCANRidSup_11FE(void);
U1      u1_g_oXDoCANRidSup_11FF(void);
U1      u1_g_oXDoCANRidSup_DB01(void);
U1      u1_g_oXDoCANRidSup_DB03(void);
U1      u1_g_oXDoCANRidSup_DD01(void);
U1      u1_g_oXDoCANRidSup_DD02(void);
U1      u1_g_oXDoCANRidSup_FF00(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_CFG[].fp_u1_COR_CHK                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRoutCorchk_1004(const U1 u1_a_SUBF, const U1 * u1_ap_COR);
U1      u1_g_oXDoCANRoutCorchk_1101(const U1 u1_a_SUBF, const U1 * u1_ap_COR);
U1      u1_g_oXDoCANRoutCorchk_D000(const U1 u1_a_SUBF, const U1 * u1_ap_COR);
U1      u1_g_oXDoCANRoutCorchk_DD01(const U1 u1_a_SUBF, const U1 * u1_ap_COR);
U1      u1_g_oXDoCANRoutCorchk_FF00(const U1 u1_a_SUBF, const U1 * u1_ap_COR);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_CFG[].fp_u1_START                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRoutStart_D100(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_D1XX(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRoutStart_1004(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_1101(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_11FD(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_11FE(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_11FF(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_D000(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_D001(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
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
U1      u1_g_oXDoCANRoutRslt_1101(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutRslt_D001(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_esi_cfg.c / st_gp_TYDC_ESI_CFG[].fp_u1_TRX                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* OXDOCAN_SAIF_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :                                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
