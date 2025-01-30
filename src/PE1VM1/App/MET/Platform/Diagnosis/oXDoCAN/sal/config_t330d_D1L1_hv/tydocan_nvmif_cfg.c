/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN NvM Interface                                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_NVM_IF_CFG_C_MAJOR               (1)
#define TYDOCAN_NVM_IF_CFG_C_MINOR               (1)
#define TYDOCAN_NVM_IF_CFG_C_PATCH               (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_nvmif_cfg_private.h"
#include "oxdocan_saif.h"

#include "tydocan_nvmif_ba.h"
#include "tydocan_nvmif_2e_usr.h"
#include "tydocan_rsi.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TYDOCAN_NVM_IF_CFG_C_MAJOR != TYDOCAN_NVM_IF_H_MAJOR) || \
     (TYDOCAN_NVM_IF_CFG_C_MINOR != TYDOCAN_NVM_IF_H_MINOR) || \
     (TYDOCAN_NVM_IF_CFG_C_PATCH != TYDOCAN_NVM_IF_H_PATCH))
#error "tydocan_nvmif_cfg.c and tydocan_nvmif.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_NVM_IF_CFG_C_MAJOR != TYDOCAN_NVM_IF_CFG_H_MAJOR) || \
     (TYDOCAN_NVM_IF_CFG_C_MINOR != TYDOCAN_NVM_IF_CFG_H_MINOR) || \
     (TYDOCAN_NVM_IF_CFG_C_PATCH != TYDOCAN_NVM_IF_CFG_H_PATCH))
#error "tydocan_nvmif_cfg.c and tydocan_nvmif_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
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
#define TYDC_NVM_IF_2E_B32                       (0U)
#define TYDC_NVM_IF_2E_N32                       (1U)
#define TYDC_NVM_IF_2E_2209                      (2U)
#define TYDC_NVM_IF_BA_RTA                       (3U)
#define TYDC_NVM_IF_BA_DA                        (4U)
#define TYDC_NVM_IF_BA_SPC                       (5U)
#define TYDC_NVM_IF_BA_ESN                       (6U)
#define TYDC_NVM_IF_BA_SKN                       (7U)
#define TYDC_NVM_IF_RSI_FSPO                     (8U)
#define TYDC_NVM_IF_2E_SP_DN                     (9U)
#define TYDC_NVM_IF_BA_CSR                       (10U)
#define TYDC_NVM_IF_BA_THAD_I                    (11U)
static const ST_TYDC_NVM_IF   st_sp_TYDC_NVM_IF[] = {
    /* TYDC_NVM_IF_2E_B32   (0U) */
    {
        &u1_g_TyDoCANNvmIfReaB32,                     /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWriB32,                     /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSyn_2E,                     /* fp_u1_SYN */

        &u4_g_TyDoCANNvmIfMax_2E,                     /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_2E,                     /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_2E                      /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_2E_N32   (1U) */
    {
        &u1_g_TyDoCANNvmIfReaN32,                     /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWriN32,                     /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSyn_2E,                     /* fp_u1_SYN */

        &u4_g_TyDoCANNvmIfMax_2E,                     /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_2E,                     /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_2E                      /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_2E_2209  (2U) */
    {
        &u1_g_TyDoCANNvmIfReaN32,                     /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWriN32,                     /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSyn_2E,                     /* fp_u1_SYN */

        &u4_g_TyDoCANNvmIfMax_2E,                     /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_2E_2209,                /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_2E_2209                 /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_BA_RTA   (3U) */
    {
        &u1_g_TyDoCANNvmIfReaN16,                     /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWriN16,                     /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSynchk,                     /* fp_u1_SYN */

        vdp_PTR_NA,                                   /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_Rta,                    /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_Rta                     /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_BA_DA    (4U) */
    {
        &u1_g_TyDoCANNvmIfReaN16,                     /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWriN16,                     /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSynchk,                     /* fp_u1_SYN */

        vdp_PTR_NA,                                   /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_Da,                     /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_Da                      /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_BA_SPC   (5U) */
    {
        &u1_g_TyDoCANNvmIfReaN16,                     /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWriN16,                     /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSynchk,                     /* fp_u1_SYN */

        vdp_PTR_NA,                                   /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_Spc,                    /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_Spc                     /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_BA_ESN   (6U) */
    {
        vdp_PTR_NA,                                   /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWri_Esn,                    /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSyn_Esn,                    /* fp_u1_SYN */

        vdp_PTR_NA,                                   /* fp_u4_MAX */
        vdp_PTR_NA,                                   /* fp_u1_ANS */
        vdp_PTR_NA                                    /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_BA_SKN   (7U) */
    {
        &u1_g_TyDoCANNvmIfRea_Skn,                    /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWri_Skn,                    /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSynchk,                     /* fp_u1_SYN */

        vdp_PTR_NA,                                   /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_Skn,                    /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_Skn                     /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_RSI      (8U) */
    {
        &u1_g_TyDoCANNvmIfReaN32,                     /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWriN32,                     /* fp_u1_WRI */
        &u1_g_TyDoCANRsiNvmIf_Syn,                    /* fp_u1_SYN */

        vdp_PTR_NA,                                   /* fp_u4_MAX */
        &u1_g_TyDoCANRsiNvmIf_Ans,                    /* fp_u1_ANS */
        &u1_g_TyDoCANRsiNvmIf_Req                     /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_2E_SP_DN (9U) */
    {
        &u1_g_TyDoCANNvmIfReaN32,                     /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWriN32,                     /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSynchk,                     /* fp_u1_SYN */

        vdp_PTR_NA,                                   /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_2E_SP_DN,               /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_2E_SP_DN                /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_2E_BA_CSR (10U) */
    {
        &u1_g_TyDoCANNvmIfReaN32,                     /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWriN32,                     /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSynchk,                     /* fp_u1_SYN */

        vdp_PTR_NA,                                   /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_Csr,                    /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_Csr                     /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_BA_THAD_I (11U) */
    {
        &u1_g_TyDoCANNvmIfReaN32,                     /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWriN32,                     /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSynchk,                     /* fp_u1_SYN */

        vdp_PTR_NA,                                   /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_ThadI,                  /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_ThadI                   /* fp_u1_REQ */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_NVM_DID    st_gp_TYDC_NVM_DID[] = {
    /* TYDC_NVM_2E_2002 (0U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_N32],       /* stp_IF    */

        (U2)NVMCID_U4_DS_2E_2002,                     /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_2002                 /* u2_nbyte  */
    },
    /* TYDC_NVM_2E_2003 (1U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_B32],       /* stp_IF    */

        (U2)NVMCID_U4_DS_2E_2003,                     /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_2003                 /* u2_nbyte  */
    },
    /* TYDC_NVM_2E_2004 (2U) */
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
#if 0/*Phase6Diag Stub*/
    /* TYDC_NVM_2E_2021 (3U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_B32],       /* stp_IF    */

        (U2)NVMCID_U4_DS_2E_2021,                     /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_2021                 /* u2_nbyte  */
    },
#else
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
#endif
    /* TYDC_NVM_2E_2041 (4U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_B32],       /* stp_IF    */

        (U2)NVMCID_U4_DS_2E_2041,                     /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_2041                 /* u2_nbyte  */
    },
    /* TYDC_NVM_2E_2042 (5U) */
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    /* TYDC_NVM_2E_2043 (6U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_N32],       /* stp_IF    */

        (U2)NVMCID_U4_DS_2E_2043,                     /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_2043                 /* u2_nbyte  */
    },
    /* TYDC_NVM_2E_2045 (7U) */
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    /* TYDC_NVM_2E_20C1 (8U) */
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    /* TYDC_NVM_2E_20C2 (9U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_N32],       /* stp_IF    */

        (U2)NVMCID_U4_DS_2E_20C2,                     /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_20C2                 /* u2_nbyte  */
    },
    /* TYDC_NVM_2E_2204 (10U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_B32],       /* stp_IF    */

        (U2)NVMCID_U4_DS_2E_2204,                     /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_2204                 /* u2_nbyte  */
    },
    /* TYDC_NVM_2E_2209 (11U) */
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    /* TYDC_NVM_BA_RTA  (12U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_BA_RTA],       /* stp_IF    */

        (U2)NVMCID_U2_CLOCK_RATE_ADJ,                 /* u2_nid    */
        (U2)TYDC_NVM_BA_NB_RTA                        /* u2_nbyte  */
    },
    /* TYDC_NVM_BA_DAX  (13U) */
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    /* TYDC_NVM_BA_DAY  (14U) */
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    /* TYDC_NVM_BA_SPC  (15U) */
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    /* TYDC_NVM_BA_ESN  (16U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_BA_ESN],       /* stp_IF    */

        (U2)NVMCID_OTR_SERI_N_10B,                    /* u2_nid    */
        (U2)TYDC_NVM_BA_NB_ESN                        /* u2_nbyte  */
    },
    /* TYDC_NVM_BA_SKN  (17U) */
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    /* TYDC_NVM_RSI     (18U) */
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
#if 0/*Phase6Diag Stub*/
    /* TYDC_NVM_FD00     (19U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_SP_DN],     /* stp_IF    */

        (U2)NVMCID_U4_DS_SP_2E_FD00,                  /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_FD00                 /* u2_nbyte  */
    },
    /* TYDC_NVM_FD01     (20U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_SP_DN],     /* stp_IF    */

        (U2)NVMCID_U4_DS_SP_2E_FD01,                  /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_FD01                 /* u2_nbyte  */
    },
    /* TYDC_NVM_FD02    (21U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_SP_DN],     /* stp_IF    */

        (U2)NVMCID_U4_DS_SP_2E_FD02,                  /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_FD02                 /* u2_nbyte  */
    },
    /* TYDC_NVM_FD03     (22U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_SP_DN],     /* stp_IF    */

        (U2)NVMCID_U4_DS_SP_2E_FD03,                  /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_FD03                 /* u2_nbyte  */
    },
    /* TYDC_NVM_FD04     (23U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_SP_DN],     /* stp_IF    */

        (U2)NVMCID_U4_DS_SP_2E_FD04,                  /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_FD04                 /* u2_nbyte  */
    },
#else
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
#endif
#if 0/*Phase6Diag Stub*/
    /* TYDC_NVM_BA_CSR_F    (24U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_BA_CSR],     /* stp_IF    */

        (U2)NVMCID_U4_TURHAZ_FRONT_AD_K,            /* u2_nid    */
        (U2)TYDC_NVM_BA_NB_CSR                      /* u2_nbyte  */
    },
    /* TYDC_NVM_BA_CSR_R    (25U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_BA_CSR],     /* stp_IF    */

        (U2)NVMCID_U4_TURHAZ_REAR_AD_K,             /* u2_nid    */
        (U2)TYDC_NVM_BA_NB_CSR                      /* u2_nbyte  */
    },
    /* TYDC_NVM_BA_THFAD_I    (26U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_BA_THAD_I],  /* stp_IF    */

        (U2)NVMCID_U4_TURHAZ_FRONT_AD_I,            /* u2_nid    */
        (U2)TYDC_NVM_BA_NB_THAD_I                   /* u2_nbyte  */
    },
    /* TYDC_NVM_BA_THRAD_I    (27U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_BA_THAD_I],  /* stp_IF    */

        (U2)NVMCID_U4_TURHAZ_REAR_AD_I,             /* u2_nid    */
        (U2)TYDC_NVM_BA_NB_THAD_I                   /* u2_nbyte  */
    }
#else
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    },
    {
        vdp_PTR_NA,                                   /* stp_IF    */

        (U2)U2_MAX,                                   /* u2_nid    */
        (U2)0U                                        /* u2_nbyte  */
    }
#endif
};
const U2                 u2_g_TYDC_NVM_NUM_DID = (U2)TYDC_NVM_NUM_DID;

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
/*  1.0.0     3/11/2020  TN       New.                                                                                               */
/*  1.1.0    10/06/2020  AS       tydocan_nvmif.c v1.0.0 -> v1.1.0.                                                                  */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1   10/06/2020  AS       Configured for 800B                                                                                */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * AS   = Atsunori Sugita, DENSO-TECHNO                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
