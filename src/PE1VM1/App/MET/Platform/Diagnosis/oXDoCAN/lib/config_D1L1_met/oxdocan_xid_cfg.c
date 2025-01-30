/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  SID 0x22/0x2E/0x2F/0x31 DataIdentifer and Routine Identifer                                                                      */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_XID_CFG_C_MAJOR                  (1U)
#define OXDOCAN_XID_CFG_C_MINOR                  (0U)
#define OXDOCAN_XID_CFG_C_PATCH                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "oxdocan_xid_cfg_private.h"

/* #include "nvmc_mgr.h"             nvmc_mgr.h is included in oxdocan_cfg_private.h              */
/* #include "oxcan.h"                oxcan.h is included in oxdocan_cfg_private.h                 */

#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)  ) && \
     (BSW_BSWM_CS_CFG_FUNC_CS    == BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC == BSW_USE))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_dtc_ma_cfg_private.h"
#include "tydocan_xid_ma_cfg_private.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && ... */
/* Application Headers */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXDOCAN_XID_CFG_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "oxdocan_xid_cfg.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((OXDOCAN_XID_CFG_C_MAJOR != OXDOCAN_XID_CFG_H_MAJOR) || \
     (OXDOCAN_XID_CFG_C_MINOR != OXDOCAN_XID_CFG_H_MINOR) || \
     (OXDOCAN_XID_CFG_C_PATCH != OXDOCAN_XID_CFG_H_PATCH))
#error "oxdocan_xid_cfg.c and oxdocan_xid_cfg_private.h : source and header files are inconsistent!"
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
U1      u1_s_oXDoCANDidSecPtnOta(const U1 u1_a_LVL);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                        u2_g_OXDC_XID_SUP_LP_LMT   = (U2)50U;  /* 50 times loop executable to check if XID is supported */
const U2                        u2_g_OXDC_IOC_RDBK_DLY_MAX = (U2)20U / (U2)10U; /* 20 milliseconds */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_OXDC_IOC_IF            st_gp_OXDC_IOC_IF[] = {
/*   fp_u1_CSM_CHK                  fp_vd_ACT                       fp_vd_DEACT                    fp_u1_SEC_CHK*/
    {&u1_g_oXDoCANIocCsmchk_2803,   &vd_g_oXDoCANIocAct_2803,       &vd_g_oXDoCANIocDeAct_2803,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2804,   &vd_g_oXDoCANIocAct_2804,       &vd_g_oXDoCANIocDeAct_2804,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2805,   &vd_g_oXDoCANIocAct_2805,       &vd_g_oXDoCANIocDeAct_2805,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2806,   &vd_g_oXDoCANIocAct_2806,       &vd_g_oXDoCANIocDeAct_2806,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2809,   &vd_g_oXDoCANIocAct_2809,       &vd_g_oXDoCANIocDeAct_2809,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_280B,   &vd_g_oXDoCANIocAct_280B,       &vd_g_oXDoCANIocDeAct_280B,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_280C,   &vd_g_oXDoCANIocAct_280C,       &vd_g_oXDoCANIocDeAct_280C,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2821,   &vd_g_oXDoCANIocAct_2821,       &vd_g_oXDoCANIocDeAct_2821,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2822,   &vd_g_oXDoCANIocAct_2822,       &vd_g_oXDoCANIocDeAct_2822,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2823,   &vd_g_oXDoCANIocAct_2823,       &vd_g_oXDoCANIocDeAct_2823,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2824,   &vd_g_oXDoCANIocAct_2824,       &vd_g_oXDoCANIocDeAct_2824,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2825,   &vd_g_oXDoCANIocAct_2825,       &vd_g_oXDoCANIocDeAct_2825,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2827,   &vd_g_oXDoCANIocAct_2827,       &vd_g_oXDoCANIocDeAct_2827,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2829,   &vd_g_oXDoCANIocAct_2829,       &vd_g_oXDoCANIocDeAct_2829,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2831,   &vd_g_oXDoCANIocAct_2831,       &vd_g_oXDoCANIocDeAct_2831,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2901,   &vd_g_oXDoCANIocAct_2901,       &vd_g_oXDoCANIocDeAct_2901,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2911,   &vd_g_oXDoCANIocAct_2911,       &vd_g_oXDoCANIocDeAct_2911,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2912,   &vd_g_oXDoCANIocAct_2912,       &vd_g_oXDoCANIocDeAct_2912,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2921,   &vd_g_oXDoCANIocAct_2921,       &vd_g_oXDoCANIocDeAct_2921,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2922,   &vd_g_oXDoCANIocAct_2922,       &vd_g_oXDoCANIocDeAct_2922,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2931,   &vd_g_oXDoCANIocAct_2931,       &vd_g_oXDoCANIocDeAct_2931,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2932,   &vd_g_oXDoCANIocAct_2932,       &vd_g_oXDoCANIocDeAct_2932,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2933,   &vd_g_oXDoCANIocAct_2933,       &vd_g_oXDoCANIocDeAct_2933,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2941,   &vd_g_oXDoCANIocAct_2941,       &vd_g_oXDoCANIocDeAct_2941,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2942,   &vd_g_oXDoCANIocAct_2942,       &vd_g_oXDoCANIocDeAct_2942,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2943,   &vd_g_oXDoCANIocAct_2943,       &vd_g_oXDoCANIocDeAct_2943,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2944,   &vd_g_oXDoCANIocAct_2944,       &vd_g_oXDoCANIocDeAct_2944,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2951,   &vd_g_oXDoCANIocAct_2951,       &vd_g_oXDoCANIocDeAct_2951,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2952,   &vd_g_oXDoCANIocAct_2952,       &vd_g_oXDoCANIocDeAct_2952,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2961,   &vd_g_oXDoCANIocAct_2961,       &vd_g_oXDoCANIocDeAct_2961,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2981,   &vd_g_oXDoCANIocAct_2981,       &vd_g_oXDoCANIocDeAct_2981,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2A01,   &vd_g_oXDoCANIocAct_2A01,       &vd_g_oXDoCANIocDeAct_2A01,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2A21,   &vd_g_oXDoCANIocAct_2A21,       &vd_g_oXDoCANIocDeAct_2A21,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2A22,   &vd_g_oXDoCANIocAct_2A22,       &vd_g_oXDoCANIocDeAct_2A22,    vdp_PTR_NA},
    {&u1_g_oXDoCANIocCsmchk_2B01,   &vd_g_oXDoCANIocAct_2B01,       &vd_g_oXDoCANIocDeAct_2B01,    vdp_PTR_NA}
};
const U2                        u2_g_OXDC_NUM_IOC = (U2)(sizeof(st_gp_OXDC_IOC_IF) / sizeof(ST_OXDC_IOC_IF));

const ST_OXDC_DID               st_gp_OXDC_DATA_XID[] = {
/*   fp_u1_SUP                      u2_xid          u2_rd_ses          fp_u1_RDSEC_CHK    u2_wr_ses          fp_u1_WRSEC_CHK */
    {&u1_g_oXDoCANDidSup_1001,      (U2)0x1001U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1002,      (U2)0x1002U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1003,      (U2)0x1003U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x1021U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1022,      (U2)0x1022U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1023,      (U2)0x1023U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x1024U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1025,      (U2)0x1025U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1027,      (U2)0x1027U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x1041U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1042,      (U2)0x1042U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1043,      (U2)0x1043U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1044,      (U2)0x1044U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x1081U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10A1,      (U2)0x10A1U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10A2,      (U2)0x10A2U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x10A3U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10A5,      (U2)0x10A5U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x10A6U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10A7,      (U2)0x10A7U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10A8,      (U2)0x10A8U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10AB,      (U2)0x10ABU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10AC,      (U2)0x10ACU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10AD,      (U2)0x10ADU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10AE,      (U2)0x10AEU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10AF,      (U2)0x10AFU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10B0,      (U2)0x10B0U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_10B1,      (U2)0x10B1U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x10C1U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x1141U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1142,      (U2)0x1142U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x11A1U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x11A2U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x11A3U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1241,      (U2)0x1241U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_12A1,      (U2)0x12A1U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x14A1U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x15A1U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_1641,      (U2)0x1641U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_18A1,      (U2)0x18A1U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_18A2,      (U2)0x18A2U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2002U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2003,      (U2)0x2003U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2041,      (U2)0x2041U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2042,      (U2)0x2042U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2043U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2045,      (U2)0x2045U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_20C2,      (U2)0x20C2U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2202,      (U2)0x2202U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2203,      (U2)0x2203U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2204,      (U2)0x2204U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2803,      (U2)0x2803U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2804,      (U2)0x2804U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2805,      (U2)0x2805U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2806,      (U2)0x2806U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2809,      (U2)0x2809U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_280B,      (U2)0x280BU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_280C,      (U2)0x280CU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2821U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2822U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2823U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2824U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2825U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2827U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2829U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2831U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2901,      (U2)0x2901U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2911,      (U2)0x2911U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2912,      (U2)0x2912U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2921,      (U2)0x2921U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2922,      (U2)0x2922U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2931,      (U2)0x2931U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2932,      (U2)0x2932U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2933,      (U2)0x2933U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2941,      (U2)0x2941U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2942,      (U2)0x2942U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2943,      (U2)0x2943U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2944,      (U2)0x2944U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2951,      (U2)0x2951U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2952,      (U2)0x2952U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2961,      (U2)0x2961U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2981,      (U2)0x2981U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2A01U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2A21U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0x2A22U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_2B01,      (U2)0x2B01U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA002U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA003U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA005U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA006U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA007U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA008U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_A00A,      (U2)0xA00AU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA100U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA110U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA111U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA112U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA114U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA115U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA116U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA118U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA120U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA122U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA128U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA129U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA12AU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA12BU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA1A0U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA1A1U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA1A8U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA1AAU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA1ABU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA1F0U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA1F1U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xA800U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xAA00U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0004U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xAB00U,    (U2)0x0009U,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xAB01U,    (U2)0x0009U,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_AB02,      (U2)0xAB02U,    (U2)0x0008U,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_F050,      (U2)0xF050U,    (U2)0x0000U,       vdp_PTR_NA,       (U2)0x0008U,        &u1_s_oXDoCANDidSecPtnOta},
    {vdp_PTR_NA,                    (U2)0xF07FU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xF082U,    (U2)0x0009U,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xF083U,    (U2)0x0009U,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xF084U,    (U2)0x0009U,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xF085U,    (U2)0x0009U,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xF120U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xF121U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {&u1_g_oXDoCANDidSup_F122,      (U2)0xF122U,    (U2)0x0000U,       vdp_PTR_NA,       (U2)0x0008U,        &u1_s_oXDoCANDidSecPtnOta},
    {&u1_g_oXDoCANDidSup_F123,      (U2)0xF123U,    (U2)0x0000U,       vdp_PTR_NA,       (U2)0x0008U,        &u1_s_oXDoCANDidSecPtnOta},
    {&u1_g_oXDoCANDidSup_F124,      (U2)0xF124U,    (U2)0x0000U,       vdp_PTR_NA,       (U2)0x0008U,        &u1_s_oXDoCANDidSecPtnOta},
    {&u1_g_oXDoCANDidSup_F125,      (U2)0xF125U,    (U2)0x0000U,       vdp_PTR_NA,       (U2)0x0008U,        &u1_s_oXDoCANDidSecPtnOta},
    {vdp_PTR_NA,                    (U2)0xF186U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xF188U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xF18AU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xF18CU,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA},
    {vdp_PTR_NA,                    (U2)0xF191U,    (U2)0x000DU,       vdp_PTR_NA,       (U2)0x0000U,        vdp_PTR_NA}
};

const ST_OXDC_XID_ML            st_gp_OXDC_DATA_XID_ML[] = {
/*   u2_req_nbyte                   u2_ans_nbyte */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1001},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1002},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1003},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1021},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1022},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1023},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1024},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1025},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1027},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1041},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1042},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1043},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1044},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1081},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10A1},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10A2},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10A3},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10A5},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10A6},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10A7},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10A8},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10AB},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10AC},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10AD},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10AE},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10AF},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10B0},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10B1},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_10C1},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1141},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1142},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_11A1},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_11A2},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_11A3},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1241},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_12A1},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_14A1},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_15A1},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_1641},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_18A1},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_18A2},
    {(U2)OXDC_DATA_WRI_REQ_NB_2002, (U2)OXDC_DATA_REA_ANS_NB_2002},
    {(U2)OXDC_DATA_WRI_REQ_NB_2003, (U2)OXDC_DATA_REA_ANS_NB_2003},
    {(U2)OXDC_DATA_WRI_REQ_NB_2041, (U2)OXDC_DATA_REA_ANS_NB_2041},
    {(U2)OXDC_DATA_WRI_REQ_NB_2042, (U2)OXDC_DATA_REA_ANS_NB_2042},
    {(U2)OXDC_DATA_WRI_REQ_NB_2043, (U2)OXDC_DATA_REA_ANS_NB_2043},
    {(U2)OXDC_DATA_WRI_REQ_NB_2045, (U2)OXDC_DATA_REA_ANS_NB_2045},
    {(U2)OXDC_DATA_WRI_REQ_NB_20C2, (U2)OXDC_DATA_REA_ANS_NB_20C2},
    {(U2)OXDC_DATA_WRI_REQ_NB_2202, (U2)OXDC_DATA_REA_ANS_NB_2202},
    {(U2)OXDC_DATA_WRI_REQ_NB_2203, (U2)OXDC_DATA_REA_ANS_NB_2203},
    {(U2)OXDC_DATA_WRI_REQ_NB_2204, (U2)OXDC_DATA_REA_ANS_NB_2204},
    {(U2)OXDC_DATA_IOC_REQ_NB_2803, (U2)OXDC_DATA_REA_ANS_NB_2803},
    {(U2)OXDC_DATA_IOC_REQ_NB_2804, (U2)OXDC_DATA_REA_ANS_NB_2804},
    {(U2)OXDC_DATA_IOC_REQ_NB_2805, (U2)OXDC_DATA_REA_ANS_NB_2805},
    {(U2)OXDC_DATA_IOC_REQ_NB_2806, (U2)OXDC_DATA_REA_ANS_NB_2806},
    {(U2)OXDC_DATA_IOC_REQ_NB_2809, (U2)OXDC_DATA_REA_ANS_NB_2809},
    {(U2)OXDC_DATA_IOC_REQ_NB_280B, (U2)OXDC_DATA_REA_ANS_NB_280B},
    {(U2)OXDC_DATA_IOC_REQ_NB_280C, (U2)OXDC_DATA_REA_ANS_NB_280C},
    {(U2)OXDC_DATA_IOC_REQ_NB_2821, (U2)OXDC_DATA_REA_ANS_NB_2821},
    {(U2)OXDC_DATA_IOC_REQ_NB_2822, (U2)OXDC_DATA_REA_ANS_NB_2822},
    {(U2)OXDC_DATA_IOC_REQ_NB_2823, (U2)OXDC_DATA_REA_ANS_NB_2823},
    {(U2)OXDC_DATA_IOC_REQ_NB_2824, (U2)OXDC_DATA_REA_ANS_NB_2824},
    {(U2)OXDC_DATA_IOC_REQ_NB_2825, (U2)OXDC_DATA_REA_ANS_NB_2825},
    {(U2)OXDC_DATA_IOC_REQ_NB_2827, (U2)OXDC_DATA_REA_ANS_NB_2827},
    {(U2)OXDC_DATA_IOC_REQ_NB_2829, (U2)OXDC_DATA_REA_ANS_NB_2829},
    {(U2)OXDC_DATA_IOC_REQ_NB_2831, (U2)OXDC_DATA_REA_ANS_NB_2831},
    {(U2)OXDC_DATA_IOC_REQ_NB_2901, (U2)OXDC_DATA_REA_ANS_NB_2901},
    {(U2)OXDC_DATA_IOC_REQ_NB_2911, (U2)OXDC_DATA_REA_ANS_NB_2911},
    {(U2)OXDC_DATA_IOC_REQ_NB_2912, (U2)OXDC_DATA_REA_ANS_NB_2912},
    {(U2)OXDC_DATA_IOC_REQ_NB_2921, (U2)OXDC_DATA_REA_ANS_NB_2921},
    {(U2)OXDC_DATA_IOC_REQ_NB_2922, (U2)OXDC_DATA_REA_ANS_NB_2922},
    {(U2)OXDC_DATA_IOC_REQ_NB_2931, (U2)OXDC_DATA_REA_ANS_NB_2931},
    {(U2)OXDC_DATA_IOC_REQ_NB_2932, (U2)OXDC_DATA_REA_ANS_NB_2932},
    {(U2)OXDC_DATA_IOC_REQ_NB_2933, (U2)OXDC_DATA_REA_ANS_NB_2933},
    {(U2)OXDC_DATA_IOC_REQ_NB_2941, (U2)OXDC_DATA_REA_ANS_NB_2941},
    {(U2)OXDC_DATA_IOC_REQ_NB_2942, (U2)OXDC_DATA_REA_ANS_NB_2942},
    {(U2)OXDC_DATA_IOC_REQ_NB_2943, (U2)OXDC_DATA_REA_ANS_NB_2943},
    {(U2)OXDC_DATA_IOC_REQ_NB_2944, (U2)OXDC_DATA_REA_ANS_NB_2944},
    {(U2)OXDC_DATA_IOC_REQ_NB_2951, (U2)OXDC_DATA_REA_ANS_NB_2951},
    {(U2)OXDC_DATA_IOC_REQ_NB_2952, (U2)OXDC_DATA_REA_ANS_NB_2952},
    {(U2)OXDC_DATA_IOC_REQ_NB_2961, (U2)OXDC_DATA_REA_ANS_NB_2961},
    {(U2)OXDC_DATA_IOC_REQ_NB_2981, (U2)OXDC_DATA_REA_ANS_NB_2981},
    {(U2)OXDC_DATA_IOC_REQ_NB_2A01, (U2)OXDC_DATA_REA_ANS_NB_2A01},
    {(U2)OXDC_DATA_IOC_REQ_NB_2A21, (U2)OXDC_DATA_REA_ANS_NB_2A21},
    {(U2)OXDC_DATA_IOC_REQ_NB_2A22, (U2)OXDC_DATA_REA_ANS_NB_2A22},
    {(U2)OXDC_DATA_IOC_REQ_NB_2B01, (U2)OXDC_DATA_REA_ANS_NB_2B01},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A002},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A003},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A005},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A006},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A007},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A008},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A00A},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A100},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA110 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA111 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA112 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA114 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA115 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA116 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA118 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA120 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA122 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA128 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA129 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA12A */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA12B */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1A0 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1A1 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1A8 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1AA */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1AB */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1F0 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1F1 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A800},
    {(U2)OXDC_DATA_WRI_REQ_NB_AA00, (U2)OXDC_DATA_REA_ANS_NB_AA00},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_AB00},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_AB01},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_AB02},
    {(U2)OXDC_DATA_WRI_REQ_NB_F050, (U2)OXDC_DATA_REA_ANS_NB_F050},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F07F},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F082},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F083},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F084},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F085},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F120},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F121},
    {(U2)OXDC_DATA_WRI_REQ_NB_F122, (U2)OXDC_DATA_REA_ANS_NB_F122},
    {(U2)OXDC_DATA_WRI_REQ_NB_F123, (U2)OXDC_DATA_REA_ANS_NB_F123},
    {(U2)OXDC_DATA_WRI_REQ_NB_F124, (U2)OXDC_DATA_REA_ANS_NB_F124},
    {(U2)OXDC_DATA_WRI_REQ_NB_F125, (U2)OXDC_DATA_REA_ANS_NB_F125},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F186},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F188},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F18A},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F18C},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F191} 
};

const ST_OXDC_DATA_IF           st_gp_OXDC_DATA_CFG[] = {
/*   fp_u1_READ                     fp_u1_WRITE                     stp_IOC */
    {&u1_g_oXDoCANRebyId_1001,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1001 */
    {&u1_g_oXDoCANRebyId_1002,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1002 */
    {&u1_g_oXDoCANRebyId_1003,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1003 */
    {&u1_g_oXDoCANRebyId_1021,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1021 */
    {&u1_g_oXDoCANRebyId_1022,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1022 */
    {&u1_g_oXDoCANRebyId_1023,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1023 */
    {&u1_g_oXDoCANRebyId_1024,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1024 */
    {&u1_g_oXDoCANRebyId_1025,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1025 */
    {&u1_g_oXDoCANRebyId_1027,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1027 */
    {&u1_g_oXDoCANRebyId_1041,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1041 */
    {&u1_g_oXDoCANRebyId_1042,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1042 */
    {&u1_g_oXDoCANRebyId_1043,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1043 */
    {&u1_g_oXDoCANRebyId_1044,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1044 */
    {&u1_g_oXDoCANRebyId_1081,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1081 */
    {&u1_g_oXDoCANRebyId_10A1,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10A1 */
    {&u1_g_oXDoCANRebyId_10A2,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10A2 */
    {&u1_g_oXDoCANRebyId_10A3,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10A3 */
    {&u1_g_oXDoCANRebyId_10A5,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10A5 */
    {&u1_g_oXDoCANRebyId_10A6,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10A6 */
    {&u1_g_oXDoCANRebyId_10A7,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10A7 */
    {&u1_g_oXDoCANRebyId_10A8,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10A8 */
    {&u1_g_oXDoCANRebyId_10AB,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10AB */
    {&u1_g_oXDoCANRebyId_10AC,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10AC */
    {&u1_g_oXDoCANRebyId_10AD,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10AD */
    {&u1_g_oXDoCANRebyId_10AE,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10AE */
    {&u1_g_oXDoCANRebyId_10AF,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10AF */
    {&u1_g_oXDoCANRebyId_10B0,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10B0 */
    {&u1_g_oXDoCANRebyId_10B1,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10B1 */
    {&u1_g_oXDoCANRebyId_10C1,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x10C1 */
    {&u1_g_oXDoCANRebyId_1141,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1141 */
    {&u1_g_oXDoCANRebyId_1142,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1142 */
    {&u1_g_oXDoCANRebyId_11A1,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x11A1 */
    {&u1_g_oXDoCANRebyId_11A2,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x11A2 */
    {&u1_g_oXDoCANRebyId_11A3,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x11A3 */
    {&u1_g_oXDoCANRebyId_1241,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1241 */
    {&u1_g_oXDoCANRebyId_12A1,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x12A1 */
    {&u1_g_oXDoCANRebyId_14A1,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x14A1 */
    {&u1_g_oXDoCANRebyId_15A1,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x15A1 */
    {&u1_g_oXDoCANRebyId_1641,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x1641 */
    {&u1_g_oXDoCANRebyId_18A1,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x18A1 */
    {&u1_g_oXDoCANRebyId_18A2,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0x18A2 */
    {&u1_g_oXDoCANRebyId_2002,      &u1_g_oXDoCANWrbyId_2002,       vdp_PTR_NA                    },    /* DID:0x2002 */
    {&u1_g_oXDoCANRebyId_2003,      &u1_g_oXDoCANWrbyId_2003,       vdp_PTR_NA                    },    /* DID:0x2003 */
    {&u1_g_oXDoCANRebyId_2041,      &u1_g_oXDoCANWrbyId_2041,       vdp_PTR_NA                    },    /* DID:0x2041 */
    {&u1_g_oXDoCANRebyId_2042,      &u1_g_oXDoCANWrbyId_2042,       vdp_PTR_NA                    },    /* DID:0x2042 */
    {&u1_g_oXDoCANRebyId_2043,      &u1_g_oXDoCANWrbyId_2043,       vdp_PTR_NA                    },    /* DID:0x2043 */
    {&u1_g_oXDoCANRebyId_2045,      &u1_g_oXDoCANWrbyId_2045,       vdp_PTR_NA                    },    /* DID:0x2045 */
    {&u1_g_oXDoCANRebyId_20C2,      &u1_g_oXDoCANWrbyId_20C2,       vdp_PTR_NA                    },    /* DID:0x20C2 */
    {&u1_g_oXDoCANRebyId_2202,      &u1_g_oXDoCANWrbyId_2202,       vdp_PTR_NA                    },    /* DID:0x2202 */
    {&u1_g_oXDoCANRebyId_2203,      &u1_g_oXDoCANWrbyId_2203,       vdp_PTR_NA                    },    /* DID:0x2203 */
    {&u1_g_oXDoCANRebyId_2204,      &u1_g_oXDoCANWrbyId_2204,       vdp_PTR_NA                    },    /* DID:0x2204 */
    {&u1_g_oXDoCANRebyId_2803,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[0]         },    /* DID:0x2803 */
    {&u1_g_oXDoCANRebyId_2804,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[1]         },    /* DID:0x2804 */
    {&u1_g_oXDoCANRebyId_2805,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[2]         },    /* DID:0x2805 */
    {&u1_g_oXDoCANRebyId_2806,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[3]         },    /* DID:0x2806 */
    {&u1_g_oXDoCANRebyId_2809,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[4]         },    /* DID:0x2809 */
    {&u1_g_oXDoCANRebyId_280B,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[5]         },    /* DID:0x280B */
    {&u1_g_oXDoCANRebyId_280C,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[6]         },    /* DID:0x280C */
    {&u1_g_oXDoCANRebyId_2821,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[7]         },    /* DID:0x2821 */
    {&u1_g_oXDoCANRebyId_2822,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[8]         },    /* DID:0x2822 */
    {&u1_g_oXDoCANRebyId_2823,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[9]         },    /* DID:0x2823 */
    {&u1_g_oXDoCANRebyId_2824,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[10]        },    /* DID:0x2824 */
    {&u1_g_oXDoCANRebyId_2825,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[11]        },    /* DID:0x2825 */
    {&u1_g_oXDoCANRebyId_2827,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[12]        },    /* DID:0x2827 */
    {&u1_g_oXDoCANRebyId_2829,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[13]        },    /* DID:0x2829 */
    {&u1_g_oXDoCANRebyId_2831,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[14]        },    /* DID:0x2831 */
    {&u1_g_oXDoCANRebyId_2901,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[15]        },    /* DID:0x2901 */
    {&u1_g_oXDoCANRebyId_2911,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[16]        },    /* DID:0x2911 */
    {&u1_g_oXDoCANRebyId_2912,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[17]        },    /* DID:0x2912 */
    {&u1_g_oXDoCANRebyId_2921,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[18]        },    /* DID:0x2921 */
    {&u1_g_oXDoCANRebyId_2922,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[19]        },    /* DID:0x2922 */
    {&u1_g_oXDoCANRebyId_2931,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[20]        },    /* DID:0x2931 */
    {&u1_g_oXDoCANRebyId_2932,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[21]        },    /* DID:0x2932 */
    {&u1_g_oXDoCANRebyId_2933,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[22]        },    /* DID:0x2933 */
    {&u1_g_oXDoCANRebyId_2941,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[23]        },    /* DID:0x2941 */
    {&u1_g_oXDoCANRebyId_2942,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[24]        },    /* DID:0x2942 */
    {&u1_g_oXDoCANRebyId_2943,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[25]        },    /* DID:0x2943 */
    {&u1_g_oXDoCANRebyId_2944,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[26]        },    /* DID:0x2944 */
    {&u1_g_oXDoCANRebyId_2951,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[27]        },    /* DID:0x2951 */
    {&u1_g_oXDoCANRebyId_2952,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[28]        },    /* DID:0x2952 */
    {&u1_g_oXDoCANRebyId_2961,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[29]        },    /* DID:0x2961 */
    {&u1_g_oXDoCANRebyId_2981,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[30]        },    /* DID:0x2981 */
    {&u1_g_oXDoCANRebyId_2A01,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[31]        },    /* DID:0x2A01 */
    {&u1_g_oXDoCANRebyId_2A21,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[32]        },    /* DID:0x2A21 */
    {&u1_g_oXDoCANRebyId_2A22,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[33]        },    /* DID:0x2A22 */
    {&u1_g_oXDoCANRebyId_2B01,      vdp_PTR_NA,                     &st_gp_OXDC_IOC_IF[34]        },    /* DID:0x2B01 */
    {&u1_g_oXDoCANRebyId_A002,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA002 */
    {&u1_g_oXDoCANRebyId_A003,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA003 */
    {&u1_g_oXDoCANRebyId_A005,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA005 */
    {&u1_g_oXDoCANRebyId_A006,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA006 */
    {&u1_g_oXDoCANRebyId_A007,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA007 */
    {&u1_g_oXDoCANRebyId_A008,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA008 */
    {&u1_g_oXDoCANRebyId_A00A,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA00A */
    {&u1_g_oXDoCANRebyId_A100,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA100 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA110 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA111 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA112 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA114 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA115 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA116 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA118 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA120 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA122 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA128 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA129 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA12A */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA12B */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1A0 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1A1 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1A8 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1AA */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1AB */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1F0 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1F1 */
    {&u1_g_oXDoCANRebyId_A800,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA800 */
    {&u1_g_oXDoCANRebyId_AA00,      &u1_g_oXDoCANWrbyId_AA00,       vdp_PTR_NA                    },    /* DID:0xAA00 */
    {&u1_g_oXDoCANRebyId_AB00,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xAB00 */
    {&u1_g_oXDoCANRebyId_AB01,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xAB01 */
    {&u1_g_oXDoCANRebyId_AB02,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xAB02 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANWrbyId_F050,       vdp_PTR_NA                    },    /* DID:0xF050 */
    {&u1_g_oXDoCANRebyId_F07F,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF07F */
    {&u1_g_oXDoCANRebyId_F082,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF082 */
    {&u1_g_oXDoCANRebyId_F083,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF083 */
    {&u1_g_oXDoCANRebyId_F084,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF084 */
    {&u1_g_oXDoCANRebyId_F085,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF085 */
    {&u1_g_oXDoCANRebyId_F120,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF120 */
    {&u1_g_oXDoCANRebyId_F121,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF121 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANWrbyId_F122,       vdp_PTR_NA                    },    /* DID:0xF122 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANWrbyId_F123,       vdp_PTR_NA                    },    /* DID:0xF123 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANWrbyId_F124,       vdp_PTR_NA                    },    /* DID:0xF124 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANWrbyId_F125,       vdp_PTR_NA                    },    /* DID:0xF125 */
    {&u1_g_oXDoCANRebyId_F186,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF186 */
    {&u1_g_oXDoCANRebyId_F188,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF188 */
    {&u1_g_oXDoCANRebyId_F18A,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF18A */
    {&u1_g_oXDoCANRebyId_F18C,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF18C */
    {&u1_g_oXDoCANRebyId_F191,      vdp_PTR_NA,                     vdp_PTR_NA                    }     /* DID:0xF191 */
};

const U2                        u2_g_OXDC_DATA_NUM_XID = (U2)(sizeof(st_gp_OXDC_DATA_XID) / sizeof(ST_OXDC_DID));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_OXDC_XID               st_gp_OXDC_ROUT_XID[] = {
/*   fp_u1_SUP                 u2_xid          u2_ses          fp_u1_SEC_CHK */
    {vdp_PTR_NA,               (U2)0x11FDU,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0x11FFU,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0xD000U,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0xD001U,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0xD100U,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0xD111U,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0xD1D0U,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0xD1D1U,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0xD1DAU,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0xD1DBU,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0xD1DDU,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0xD1FFU,    (U2)0x000DU,     vdp_PTR_NA},
    {vdp_PTR_NA,               (U2)0xDA00U,    (U2)0x000DU,     vdp_PTR_NA},
    {&u1_g_oXDoCANRidSup_DB01, (U2)0xDB01U,    (U2)0x0008U,     &u1_s_oXDoCANDidSecPtnOta},
    {&u1_g_oXDoCANRidSup_DB03, (U2)0xDB03U,    (U2)0x0008U,     &u1_s_oXDoCANDidSecPtnOta},
    {&u1_g_oXDoCANRidSup_DD01, (U2)0xDD01U,    (U2)0x0008U,     &u1_s_oXDoCANDidSecPtnOta},
    {&u1_g_oXDoCANRidSup_DD02, (U2)0xDD02U,    (U2)0x0008U,     &u1_s_oXDoCANDidSecPtnOta},
    {&u1_g_oXDoCANRidSup_FF00, (U2)0xFF00U,    (U2)0x0008U,     &u1_s_oXDoCANDidSecPtnOta}
};

const ST_OXDC_XID_ML            st_gp_OXDC_ROUT_XID_ML_SF_01[] = {
/*   u2_req_nbyte                   u2_ans_nbyte */
    {(U2)OXDC_ROUT_STA_REQ_NB_11FD, (U2)OXDC_ROUT_STA_ANS_NB_11FD},     /* RID:0x11FD */
    {(U2)OXDC_ROUT_STA_REQ_NB_11FF, (U2)OXDC_ROUT_STA_ANS_NB_11FF},     /* RID:0x11FF */
    {(U2)OXDC_ROUT_STA_REQ_NB_D000, (U2)OXDC_ROUT_STA_ANS_NB_D000},     /* RID:0xD000 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D001, (U2)OXDC_ROUT_STA_ANS_NB_D001},     /* RID:0xD001 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D100, (U2)OXDC_ROUT_STA_ANS_NB_D100},     /* RID:0xD100 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D1XX, (U2)OXDC_ROUT_STA_ANS_NB_D1XX},     /* RID:0xD111 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D1XX, (U2)OXDC_ROUT_STA_ANS_NB_D1XX},     /* RID:0xD1D0 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D1XX, (U2)OXDC_ROUT_STA_ANS_NB_D1XX},     /* RID:0xD1D1 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D1XX, (U2)OXDC_ROUT_STA_ANS_NB_D1XX},     /* RID:0xD1DA */
    {(U2)OXDC_ROUT_STA_REQ_NB_D1XX, (U2)OXDC_ROUT_STA_ANS_NB_D1XX},     /* RID:0xD1DB */
    {(U2)OXDC_ROUT_STA_REQ_NB_D1XX, (U2)OXDC_ROUT_STA_ANS_NB_D1XX},     /* RID:0xD1DD */
    {(U2)OXDC_ROUT_STA_REQ_NB_D1XX, (U2)OXDC_ROUT_STA_ANS_NB_D1XX},     /* RID:0xD1FF */
    {(U2)OXDC_ROUT_STA_REQ_NB_DA00, (U2)OXDC_ROUT_STA_ANS_NB_DA00},     /* RID:0xDA00 */
    {(U2)OXDC_ROUT_STA_REQ_NB_DB01, (U2)OXDC_ROUT_STA_ANS_NB_DB01},     /* RID:0xDB01 */
    {(U2)OXDC_ROUT_STA_REQ_NB_DB03, (U2)OXDC_ROUT_STA_ANS_NB_DB03},     /* RID:0xDB03 */
    {(U2)OXDC_ROUT_STA_REQ_NB_DD01, (U2)OXDC_ROUT_STA_ANS_NB_DD01},     /* RID:0xDD01 */
    {(U2)OXDC_ROUT_STA_REQ_NB_DD02, (U2)OXDC_ROUT_STA_ANS_NB_DD02},     /* RID:0xDD02 */
    {(U2)OXDC_ROUT_STA_REQ_NB_FF00, (U2)OXDC_ROUT_STA_ANS_NB_FF00}      /* RID:0xFF00 */
};

const ST_OXDC_XID_ML            st_gp_OXDC_ROUT_XID_ML_SF_02[] = {
/*   u2_req_nbyte                   u2_ans_nbyte */
    {(U2)0U,                        (U2)0U                       },     /* RID:0x11FD */
    {(U2)0U,                        (U2)0U                       },     /* RID:0x11FF */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD000 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD001 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD100 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD111 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1D0 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1D1 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1DA */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1DB */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1DD */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1FF */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xDA00 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xDB01 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xDB03 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xDD01 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xDD02 */
    {(U2)0U,                        (U2)0U                       }      /* RID:0xFF00 */
};

const ST_OXDC_XID_ML            st_gp_OXDC_ROUT_XID_ML_SF_03[] = {
/*   u2_req_nbyte                   u2_ans_nbyte */
    {(U2)0U,                        (U2)0U                       },     /* RID:0x11FD */
    {(U2)0U,                        (U2)0U                       },     /* RID:0x11FF */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD000 */
    {(U2)OXDC_ROUT_RES_REQ_NB_D001, (U2)OXDC_ROUT_RES_ANS_NB_D001},     /* RID:0xD001 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD100 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD111 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1D0 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1D1 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1DA */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1DB */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1DD */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1FF */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xDA00 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xDB01 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xDB03 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xDD01 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xDD02 */
    {(U2)0U,                        (U2)0U                       }      /* RID:0xFF00 */
};

const ST_OXDC_ROUT_IF           st_gp_OXDC_ROUT_CFG[] = {
/*   fp_u1_COR_CHK                  fp_u1_START                         fp_u1_STOP                    fp_u1_RESULT */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_11FD,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0x11FD */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_11FF,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0x11FF */
    {&u1_g_oXDoCANRoutCorchk_D000,  &u1_g_oXDoCANRoutStart_D000,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD000 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D001,        vdp_PTR_NA,                   &u1_g_oXDoCANRoutRslt_D001     },   /* RID:0xD001 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D100,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD100 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D1XX,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD111 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D1XX,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD1D0 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D1XX,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD1D1 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D1XX,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD1DA */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D1XX,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD1DB */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D1XX,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD1DD */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D1XX,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD1FF */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_DA00,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xDA00 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_DB01,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xDB01 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_DB03,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xDB03 */
    {&u1_g_oXDoCANRoutCorchk_DD01,  &u1_g_oXDoCANRoutStart_DD01,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xDD01 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_DD02,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xDD02 */
    {&u1_g_oXDoCANRoutCorchk_FF00,  &u1_g_oXDoCANRoutStart_FF00,        vdp_PTR_NA,                   vdp_PTR_NA                     }    /* RID:0xFF00 */
};

const U2                        u2_g_OXDC_ROUT_NUM_XID = (U2)(sizeof(st_gp_OXDC_ROUT_XID) / sizeof(ST_OXDC_XID));

/*-----------------------------------------------------------------------------------------------------------------------------------*/

#ifdef TYDOCAN_XID_MA_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1         u1_sp_TYDC_KZK_RX_D902[] = {                        /* oxdocan_xid_ma_cfg_private.h */
    (U1)TYDC_KZK_RX_PDU_1,   /* MSG_CGW1S11_RXCH0 (105U) */
    (U1)TYDC_KZK_RX_PDU_2,   /* MSG_CGW1S12_RxCH0 (106U) */
    (U1)TYDC_KZK_RX_PDU_3,   /* MSG_CGW1S13_RxCH0 (107U) */
    (U1)TYDC_KZK_RX_PDU_4,   /* MSG_CGW1S14_RxCH0 (108U) */
    (U1)TYDC_KZK_RX_PDU_5,   /* MSG_CGW1S15_RxCH0 (109U) */
    (U1)TYDC_KZK_RX_PDU_6,   /* MSG_CGW1S16_RxCH0 (110U) */
    (U1)TYDC_KZK_RX_PDU_7,   /* MSG_CGW1S17_RxCH0 (111U) */
    (U1)TYDC_KZK_RX_PDU_8    /* MSG_CGW1S18_RxCH0 (112U) */
};
static const U1         u1_sp_TYDC_KZK_RX_D903[] = {                        /* oxdocan_xid_ma_cfg_private.h */
    (U1)TYDC_KZK_RX_PDU_IU,    /* MSG_CGW1S21_RXCH0 (113U) */
    (U1)TYDC_KZK_RX_PDU_11,    /* MSG_CGW1S22_RxCH0 (114U) */
    (U1)TYDC_KZK_RX_PDU_12,    /* MSG_CGW1S23_RxCH0 (115U) */
    (U1)TYDC_KZK_RX_PDU_13,    /* MSG_CGW1S24_RxCH0 (116U) */
    (U1)TYDC_KZK_RX_PDU_14     /* MSG_CGW1S25_RXCH0 (117U) */
};
const ST_TYDC_KZK_RX    st_gp_TYDC_KZK_RX[TYDC_KZK_NUM_RX] = {              /* oxdocan_xid_ma_cfg_private.h */
/*   u1p_KZK_RX                     u2_pdu_min                      u2_pdu_max */
     {&u1_sp_TYDC_KZK_RX_D902[0],    (U2)MSG_CGW1S11_RXCH0,         (U2)MSG_CGW1S18_RXCH0     },
     {&u1_sp_TYDC_KZK_RX_D903[0],    (U2)MSG_CGW1S21_RXCH0,         (U2)MSG_CGW1S25_RXCH0     }
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* #ifdef OXDOCAN_XID_MA_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#ifdef TYDOCAN_XID_MA_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANXidMaCfgSafeKeyNum(U1 * u1_ap_skn)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANXidMaCfgSafeKeyNum(U1 * u1_ap_skn)
{
    /* ----------------------------------------------------------------- */
    /* Attention :                                                       */
    /* ----------------------------------------------------------------- */
    /* The array size of u1_ap_skn = OXDC_DATA_REA_ANS_NB_010B and it's  */
    /* tested in oxdocan_rebyid.c                                        */
    /* ----------------------------------------------------------------- */

    return((U1)FALSE);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANXidMaCfgInputVoltVal(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANXidMaCfgInputVoltVal(void)
{
    /* ----------------------------------------------------------------- */
    /* Attention :                                                       */
    /* ----------------------------------------------------------------- */
    /* Return the input voltage value                                    */
    /* to record in UserDefinedDTC:2300 / 2301                           */
    /* ----------------------------------------------------------------- */

    return((U1)0U);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */
/*===================================================================================================================================*/
/*  U1      u1_s_oXDoCANDidSecPtnOta(const U1 u1_a_LVL)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_s_oXDoCANDidSecPtnOta(const U1 u1_a_LVL)
{
    U1      u1_t_ret;

    if(u1_a_LVL == (U1)OXDC_SECURITY_LVL25){
        u1_t_ret = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_ret = (U1)OXDC_SAL_PROC_NR_33;
    }

    return(u1_t_ret);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     7/25/2022  II       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * II = Itsuki Ito, DENSO                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
