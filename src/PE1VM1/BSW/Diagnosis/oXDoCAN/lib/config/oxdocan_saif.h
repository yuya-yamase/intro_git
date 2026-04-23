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

#define OXDC_DATA_REA_ANS_NB_1041                (1U)
#define OXDC_DATA_REA_ANS_NB_1044                (3U)
#define OXDC_DATA_REA_ANS_NB_1081                (1U)
#define OXDC_DATA_REA_ANS_NB_10C1                (8U)
#define OXDC_DATA_REA_ANS_NB_1142                (2U)
#define OXDC_DATA_REA_ANS_NB_12A1                (1U)
#define OXDC_DATA_REA_ANS_NB_280B                (2U)
#define OXDC_DATA_REA_ANS_NB_280C                (1U)
#define OXDC_DATA_REA_ANS_NB_A001                (3U)
#define OXDC_DATA_REA_ANS_NB_A007                (1U)
#define OXDC_DATA_REA_ANS_NB_A008                (1U)
#define OXDC_DATA_REA_ANS_NB_A00A                (1U)
#define OXDC_DATA_REA_ANS_NB_F188                (36U)
#define OXDC_DATA_REA_ANS_NB_F18A                (2U)
#define OXDC_DATA_REA_ANS_NB_F18C                (20U)
#define OXDC_DATA_REA_ANS_NB_F191                (41U)
#define OXDC_DATA_REA_ANS_NB_F1A0                (23U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DATA_IOC_REQ_NB_280B                (2U)
#define OXDC_DATA_IOC_REQ_NB_280C                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_01[].u2_req_nbyte                                                                  */
/*  oxdocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_01[].u2_ans_nbyte                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_ROUT_STA_REQ_NB_1103                (1U)
#define OXDC_ROUT_STA_ANS_NB_1103                (1U)

#define OXDC_ROUT_STA_REQ_NB_11FF                (0U)
#define OXDC_ROUT_STA_ANS_NB_11FF                (1U)

#define OXDC_ROUT_STA_REQ_NB_D000                (4U)
#define OXDC_ROUT_STA_ANS_NB_D000                (263U)

#define OXDC_ROUT_STA_REQ_NB_D001                (0U)
#define OXDC_ROUT_STA_ANS_NB_D001                (1U)

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
#define OXDC_ROUT_RES_REQ_NB_1103                (0U)
#define OXDC_ROUT_RES_ANS_NB_1103                (2U)

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
#define OXDC_ESI_REQ_NB_22FD11XX                 (3U)
#define OXDC_ESI_ANS_NB_22FD11XX                 (4U)

#define OXDC_ESI_REQ_NB_2EFD41XX                 (19U)
#define OXDC_ESI_ANS_NB_2EFD41XX                 (4U)

#define OXDC_ESI_REQ_NB_2EFD42XX                 (9U)
#define OXDC_ESI_ANS_NB_2EFD42XX                 (4U)

#define OXDC_ESI_REQ_NB_22FD60XX                 (3U)
#define OXDC_ESI_ANS_NB_22FD60XX                 (14U)

#define OXDC_ESI_REQ_NB_22FDC0XX                 (4U)
#define OXDC_ESI_ANS_NB_22FDC0XX                 (6U)

#define OXDC_ESI_REQ_NB_2EFDD0XX                 (4U)
#define OXDC_ESI_ANS_NB_2EFDD0XX                 (4U)

#define OXDC_ESI_REQ_NB_22FDD1XX                 (4U)
#define OXDC_ESI_ANS_NB_22FDD1XX                 (5U)

#define OXDC_ESI_REQ_NB_ABXXXXXX                 (2U)
#define OXDC_ESI_ANS_NB_ABXXXXXX                 (62U)

#define OXDC_ESI_REQ_NB_1101XXXX                 (2U)
#define OXDC_ESI_ANS_NB_1101XXXX                 (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_did_ssr_cfg.c / st_gp_OXDC_DID_SSR_CH_CFG [].u1_num_rec                                                                  */
/*  oxdocan_did_ssr_cfg.c / st_gp_OXDC_DID_SSR_CH_CFG [].u1_mem_nbyte                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DID_SSR_NUM_REC_11A2                (10U)
#define OXDC_DID_SSR_MEM_NB_11A2                 (28U)
#define OXDC_DID_SSR_NUM_REC_10A1                (3U)
#define OXDC_DID_SSR_MEM_NB_10A1                 (24U)
#define OXDC_DID_SSR_NUM_REC_10A3                (3U)
#define OXDC_DID_SSR_MEM_NB_10A3                 (32U)
#define OXDC_DID_SSR_NUM_REC_10AB                (3U)
#define OXDC_DID_SSR_MEM_NB_10AB                 (24U)
#define OXDC_DID_SSR_NUM_REC_10AD                (3U)
#define OXDC_DID_SSR_MEM_NB_10AD                 (24U)
#define OXDC_DID_SSR_NUM_REC_10AE                (3U)
#define OXDC_DID_SSR_MEM_NB_10AE                 (32U)
#define OXDC_DID_SSR_NUM_REC_10AF                (3U)
#define OXDC_DID_SSR_MEM_NB_10AF                 (24U)
#define OXDC_DID_SSR_NUM_REC_AB00                (5U)
#define OXDC_DID_SSR_MEM_NB_AB00                 (28U)
#define OXDC_DID_SSR_NUM_REC_AB01                (5U)
#define OXDC_DID_SSR_MEM_NB_AB01                 (24U)

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
U1      u1_g_oXDoCANDtcTrchk_U2303(const U2 u2_a_ELPSD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_DATA_XID[].fp_u1_SUP                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANDidSup_1044(void);
U1      u1_g_oXDoCANDidSup_1142(void);
U1      u1_g_oXDoCANDidSup_12A1(void);
U1      u1_g_oXDoCANDidSup_280B(void);
U1      u1_g_oXDoCANDidSup_280C(void);

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

U1      u1_g_oXDoCANRebyId_1041(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1044(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1081(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_10C1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_1142(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_12A1(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_280B(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_280C(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_A001(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_A007(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_A008(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_A00A(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F188(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F18A(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F18C(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F191(U1 * u1_ap_ans, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANRebyId_F1A0(U1 * u1_ap_ans, const U2 u2_a_ELPSD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_DATA_CFG[].fp_u1_WRITE                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_IOC_IF[].fp_u1_CSM_CHK                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANIocCsmchk_280B(const U1 u1_a_PRM, const U1 * u1_ap_CSM);
U1      u1_g_oXDoCANIocCsmchk_280C(const U1 u1_a_PRM, const U1 * u1_ap_CSM);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_IOC_IF[].fp_vd_ACT                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXDoCANIocAct_280B(void);
void    vd_g_oXDoCANIocAct_280C(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_IOC_IF[].fp_vd_DEACT                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXDoCANIocDeAct_280B(void);
void    vd_g_oXDoCANIocDeAct_280C(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_XID[].fp_u1_SUP                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRidSup_1103(void);
U1      u1_g_oXDoCANRidSup_11FF(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_CFG[].fp_u1_COR_CHK                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRoutCorchk_1103(const U1 u1_a_SUBF, const U1 * u1_ap_COR);
U1      u1_g_oXDoCANRoutCorchk_D000(const U1 u1_a_SUBF, const U1 * u1_ap_COR);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_CFG[].fp_u1_START                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRoutStart_D100(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_D1XX(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRoutStart_1103(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_11FF(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_D000(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_D001(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_CFG[].fp_fp_u1_STOP                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  oxdocan_xid_cfg.c / st_gp_OXDC_ROUT_CFG[].fp_fp_u1_RESULT                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRoutRslt_1103(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutRslt_D001(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_esi_cfg.c / st_gp_TYDC_ESI_CFG[].fp_u1_TRX                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANEsiTRx_22FD11XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_2EFD41XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_2EFD42XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_22FD60XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_22FDC0XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_2EFDD0XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_22FDD1XX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANEsiTRx_ABXXXXXX(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD);
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
