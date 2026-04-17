/* 1.2.0 */
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
#define TYDOCAN_NVM_IF_CFG_C_MINOR               (2)
#define TYDOCAN_NVM_IF_CFG_C_PATCH               (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_nvmif_cfg_private.h"
#include "oxdocan_saif.h"
#include "tydocan_nvmif_ba.h"

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
#define TYDC_NVM_IF_2E_B32                       (0U)
#define TYDC_NVM_IF_2E_N32                       (1U)
#define TYDC_NVM_IF_BA_SKN                       (2U)
#define TYDC_NVM_IF_BA_GMA                       (3U)
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
    /* TYDC_NVM_IF_BA_SKN   (2U) */
    {
        &u1_g_TyDoCANNvmIfRea_Skn,                    /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWri_Skn,                    /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSynchk,                     /* fp_u1_SYN */

        vdp_PTR_NA,                                   /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_Skn,                    /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_Skn                     /* fp_u1_REQ */
    },
    /* TYDC_NVM_IF_BA_GMA   (3U) */
    {
        &u1_g_TyDoCANNvmIfRea_Gma,                    /* fp_u1_REA */
        &u1_g_TyDoCANNvmIfWri_Gma,                    /* fp_u1_WRI */
        &u1_g_TyDoCANNvmIfSynchk,                     /* fp_u1_SYN */

        vdp_PTR_NA,                                   /* fp_u4_MAX */
        &u1_g_TyDoCANNvmIfAns_Gma,                    /* fp_u1_ANS */
        &u1_g_TyDoCANNvmIfReq_Gma                     /* fp_u1_REQ */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_NVM_DID    st_gp_TYDC_NVM_DID[] = {
    /* TYDC_NVM_2E_2002 (0U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_N32],       /* stp_IF    */

        (U2)U2_MAX,                     /* u2_nid    */    /* BEV Diag provisionally */
        (U2)U2_MAX                 /* u2_nbyte  */    /* BEV Diag provisionally */
    },
    /* TYDC_NVM_2E_2003 (1U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_B32],       /* stp_IF    */

        (U2)U2_MAX,                     /* u2_nid    */    /* BEV Diag provisionally */
        (U2)U2_MAX                 /* u2_nbyte  */    /* BEV Diag provisionally */
    },
    /* TYDC_NVM_2E_2041 (2U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_B32],       /* stp_IF    */

        (U2)U2_MAX,                     /* u2_nid    */    /* BEV Diag provisionally */
        (U2)U2_MAX                 /* u2_nbyte  */    /* BEV Diag provisionally */
    },
    /* TYDC_NVM_2E_20C2 (3U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_2E_N32],       /* stp_IF    */

        (U2)U2_MAX,                     /* u2_nid    */    /* BEV Diag provisionally */
        (U2)OXDC_DATA_WRI_REQ_NB_20C2                 /* u2_nbyte  */
    },
    /* TYDC_NVM_BA_SKN  (4U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_BA_SKN],       /* stp_IF    */

        (U2)NVMCID_OTR_OXDC_BA_SAFEKEY_NUM,           /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_SKN                  /* u2_nbyte  */
    },
    /* TYDC_NVM_BA_GMA  (5U) */
    {
        &st_sp_TYDC_NVM_IF[TYDC_NVM_IF_BA_GMA],       /* stp_IF    */

        (U2)NVMCID_OTR_ETH_GLOBAL_MAC_ADDRESS,        /* u2_nid    */
        (U2)OXDC_DATA_WRI_REQ_NB_GMA                  /* u2_nbyte  */
    }
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
/*  1.2.0    12/19/2024  SN       tydocan_nvmif_b32.c v1.1.0 -> v1.2.0.                                                              */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1   10/06/2020  AS       Configured for 800B                                                                                */
/*  19PFv3-1 11/11/2024  SI       Delete DID-2043                                                                                    */
/*  BEV-1    12/17/2025  SI       Delete DID 0x2021/2204                                                                             */
/*  BEV-2    03/27/2026  NY       Added support for SID 0xBA commands(2EFD41XX/2EFD42XX)                                             */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * AS   = Atsunori Sugita, DENSO-TECHNO                                                                                           */
/*  * SI   = Shugo Ichinose, DENSO-TECHNO                                                                                            */
/*  * SN   = Shimon Nambu, DENSO-TECHNO                                                                                              */
/*  * NY = Nobuhiro Yoshiyasu, DENSO-TECHNO                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
