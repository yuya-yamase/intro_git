/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN Service Application Layer Interface                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_MET_SAIF_C_MAJOR                 (1)
#define TYDOCAN_MET_SAIF_C_MINOR                 (0)
#define TYDOCAN_MET_SAIF_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "oxdocan_saif.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_xid_cfg.c / st_gp_TYDC_DATA_XID_ML[].u2_req_nbyte                                                                        */
/*  tydocan_xid_cfg.c / st_gp_TYDC_DATA_XID_ML[].u2_ans_nbyte                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (defined(OXDC_DATA_REA_ANS_NB_AA00) && (OXDC_DATA_REA_ANS_NB_AA00 != 4U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_AA00 shall be equal to 4."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_1021) && (OXDC_DATA_REA_ANS_NB_1021 != 1U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_1021 shall be equal to 1."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_1022) && (OXDC_DATA_REA_ANS_NB_1022 != 2U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_1022 shall be equal to 2."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_1023) && (OXDC_DATA_REA_ANS_NB_1023 != 2U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_1023 shall be equal to 2."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_1041) && (OXDC_DATA_REA_ANS_NB_1041 != 1U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_1041 shall be equal to 1."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_1042) && (OXDC_DATA_REA_ANS_NB_1042 != 1U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_1042 shall be equal to 1."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_10A1) && (OXDC_DATA_REA_ANS_NB_10A1 != 12U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_10A1 shall be equal to 12."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_10A2) && (OXDC_DATA_REA_ANS_NB_10A2 != 24U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_10A2 shall be equal to 24."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_10A3) && (OXDC_DATA_REA_ANS_NB_10A3 != 30U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_10A3 shall be equal to 30."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_1141) && (OXDC_DATA_REA_ANS_NB_1141 != 2U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_1141 shall be equal to 2."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_1241) && (OXDC_DATA_REA_ANS_NB_1241 != 1U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_1241 shall be equal to 1."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_12A1) && (OXDC_DATA_REA_ANS_NB_12A1 != 1U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_12A1 shall be equal to 1."
#endif

#if (defined(OXDC_DATA_REA_ANS_NB_1641) && (OXDC_DATA_REA_ANS_NB_1641 != 2U))
#error "tydocan_met_saif.c : OXDC_DATA_REA_ANS_NB_1641 shall be equal to 2."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (defined(OXDC_DATA_WRI_REQ_NB_AA00) && (OXDC_DATA_WRI_REQ_NB_AA00 != 4U))
#error "tydocan_met_saif.c : OXDC_DATA_WRI_REQ_NB_AA00 shall be equal to 4."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_01[].u2_req_nbyte                                                                  */
/*  tydocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_01[].u2_ans_nbyte                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (defined(OXDC_ROUT_STA_REQ_NB_1004) && (OXDC_ROUT_STA_REQ_NB_1004 != 2U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_REQ_NB_1004 shall be equal to 2."
#endif
#if (defined(OXDC_ROUT_STA_ANS_NB_1004) && (OXDC_ROUT_STA_ANS_NB_1004 != 0U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_ANS_NB_1004 shall be equal to 0."
#endif

#if (defined(OXDC_ROUT_STA_REQ_NB_1101) && (OXDC_ROUT_STA_REQ_NB_1101 != 1U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_REQ_NB_1101 shall be equal to 1."
#endif
#if (defined(OXDC_ROUT_STA_ANS_NB_1101) && (OXDC_ROUT_STA_ANS_NB_1101 != 1U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_ANS_NB_1101 shall be equal to 1."
#endif

#if (defined(OXDC_ROUT_STA_REQ_NB_11FD) && (OXDC_ROUT_STA_REQ_NB_11FD != 0U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_REQ_NB_11FD shall be equal to 0."
#endif
#if (defined(OXDC_ROUT_STA_ANS_NB_11FD) && (OXDC_ROUT_STA_ANS_NB_11FD != 1U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_ANS_NB_11FD shall be equal to 1."
#endif

#if (defined(OXDC_ROUT_STA_REQ_NB_11FE) && (OXDC_ROUT_STA_REQ_NB_11FE != 0U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_REQ_NB_11FE shall be equal to 0."
#endif
#if (defined(OXDC_ROUT_STA_ANS_NB_11FE) && (OXDC_ROUT_STA_ANS_NB_11FE != 1U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_ANS_NB_11FE shall be equal to 1."
#endif

#if (defined(OXDC_ROUT_STA_REQ_NB_11FF) && (OXDC_ROUT_STA_REQ_NB_11FF != 0U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_REQ_NB_11FF shall be equal to 0."
#endif
#if (defined(OXDC_ROUT_STA_ANS_NB_11FF) && (OXDC_ROUT_STA_ANS_NB_11FF != 1U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_ANS_NB_11FF shall be equal to 1."
#endif

#if (defined(OXDC_ROUT_STA_REQ_NB_1901) && (OXDC_ROUT_STA_REQ_NB_1901 != 1U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_REQ_NB_1901 shall be equal to 1."
#endif
#if (defined(OXDC_ROUT_STA_ANS_NB_1901) && (OXDC_ROUT_STA_ANS_NB_1901 != 0U))
#error "tydocan_met_saif.c : OXDC_ROUT_STA_ANS_NB_1901 shall be equal to 0."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_03[].u2_req_nbyte                                                                  */
/*  tydocan_xid_cfg.c / st_gp_TYDC_ROUT_XID_ML_SF_03[].u2_ans_nbyte                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (defined(OXDC_ROUT_RES_REQ_NB_1901) && (OXDC_ROUT_RES_REQ_NB_1901 != 0U))
#error "tydocan_met_saif.c : OXDC_ROUT_RES_REQ_NB_1901 shall be equal to 0."
#endif
#if (defined(OXDC_ROUT_RES_ANS_NB_1901) && (OXDC_ROUT_RES_ANS_NB_1901 != 1U))
#error "tydocan_met_saif.c : OXDC_ROUT_RES_ANS_NB_1901 shall be equal to 1."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_rob_cfg.c / st_gp_TYDC_ROB_CFG[].u2_ssr_nbyte                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_esi_cfg.c / st_gp_TYDC_ESI_CFG[].u2_req_nbyte                                                                            */
/*  tydocan_esi_cfg.c / st_gp_TYDC_ESI_CFG[].u2_ans_nbyte                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  tydocan_ssr_cfg.c / st_gp_TYDC_SSR_CH_CFG [].u1_num_rec                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/24/2020  TN       New.                                                                                               */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
