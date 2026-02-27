/* 1.4.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr DataFlash                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_DTF_CFG_C_MAJOR                     (1U)
#define NVMC_DTF_CFG_C_MINOR                     (4U)
#define NVMC_DTF_CFG_C_PATCH                     (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "nvmc_mgr_cfg_private.h"   /* #include "aip_common.h"               */
                                    /* #include "nvmc_mgr_private.h"         */
                                    /* #include "nvmc_mgr.h"                 */
                                    /* #include "nvmc_mgr_cfg.h"             */
                                    /* #include "nvmc_mgr_acstask_private.h" */
                                    /* #include "rim_ctl.h"                  */
                                    /* #include "rim_ctl_cfg.h"              */
#include "NvM.h"
#include "NvM_Ext.h"
#include "Mscd.h"
#include "Fee.h"

#include "nvmc_dtf_private.h"
#include "nvmc_dtf_cfg.h"
#include "nvmc_dtf_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_DTF_CFG_C_MAJOR != NVMC_DTF_PRIVATE_H_MAJOR) || \
     (NVMC_DTF_CFG_C_MINOR != NVMC_DTF_PRIVATE_H_MINOR) || \
     (NVMC_DTF_CFG_C_PATCH != NVMC_DTF_PRIVATE_H_PATCH))
#error "nvmc_dtf_cfg.c and nvmc_dtf_private.h : source and header files are inconsistent!"
#endif

#if ((NVMC_DTF_CFG_C_MAJOR != NVMC_DTF_CFG_H_MAJOR) || \
     (NVMC_DTF_CFG_C_MINOR != NVMC_DTF_CFG_H_MINOR) || \
     (NVMC_DTF_CFG_C_PATCH != NVMC_DTF_CFG_H_PATCH))
#error "nvmc_dtf_cfg.c and nvmc_dtf_cfg.h : source and config files are inconsistent!"
#endif

#if ((NVMC_DTF_CFG_C_MAJOR != NVMC_DTF_CFG_PRIVATE_H_MAJOR) || \
     (NVMC_DTF_CFG_C_MINOR != NVMC_DTF_CFG_PRIVATE_H_MINOR) || \
     (NVMC_DTF_CFG_C_PATCH != NVMC_DTF_CFG_PRIVATE_H_PATCH))
#error "nvmc_dtf_cfg.c and nvmc_dtf_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2 u2_dp_NVMC_DTF_ID_CONV_TBL[NVMC_DTF_ID_NUM] = {
/* START : ##TOOL_OUT#NVMC_DTF_ID_CONV_TBL## */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)0U ),  /* SAMPLE_U1          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)1U ),  /* SAMPLE_U2          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)2U ),  /* SAMPLE_U4          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)3U ),  /* SAMPLE_OTR32       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)4U ),  /* SAMPLE_OTR32CS     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)5U ),  /* BSW_SECOC_TRIP_CNT */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)6U ),  /* OXDC_TMSTP         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)7U ),  /* OXDC_ROE_A005      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)8U ),  /* OXDC_DTC_EVENT001  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)9U ),  /* OXDC_DTC_EVENT002  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)10U),  /* OXDC_DTC_EVENT003  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)11U),  /* OXDC_DTC_EVENT004  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)12U),  /* OXDC_DTC_EVENT005  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)13U),  /* OXDC_DTC_EVENT006  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)14U),  /* OXDC_DTC_EVENT007  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)15U),  /* OXDC_DTC_EVENT008  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)16U),  /* OXDC_DTC_EVENT009  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)17U),  /* OXDC_DTC_EVENT010  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)18U),  /* OXDC_DTC_EVENT011  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)19U),  /* OXDC_DTC_EVENT012  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)20U),  /* OXDC_DTC_EVENT013  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)21U),  /* OXDC_DTC_EVENT014  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)22U),  /* OXDC_DTC_EVENT015  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)23U),  /* OXDC_DTC_EVENT016  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)24U),  /* OXDC_DTC_EVENT017  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)25U),  /* OXDC_DTC_EVENT018  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)26U),  /* OXDC_DTC_EVENT019  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)27U),  /* OXDC_DTC_EVENT020  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)28U),  /* OXDC_DTC_EVENT021  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)29U),  /* OXDC_DTC_FAULT001  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)30U),  /* OXDC_DTC_FAULT002  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)31U),  /* OXDC_DTC_FAULT003  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)32U),  /* OXDC_DTC_FAULT004  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)33U),  /* OXDC_DTC_FAULT005  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)34U),  /* OXDC_DTC_FAULT006  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)35U),  /* OXDC_DTC_FAULT007  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)36U),  /* OXDC_DTC_FAULT008  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)37U),  /* OXDC_DTC_FAULT009  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)38U),  /* OXDC_DTC_FAULT010  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)39U),  /* OXDC_DTC_FAULT011  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)40U),  /* OXDC_DTC_FAULT012  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)41U),  /* OXDC_DTC_FAULT013  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)42U),  /* OXDC_DTC_FAULT014  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)43U),  /* OXDC_DTC_FAULT015  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)44U),  /* OXDC_DTC_FAULT016  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)45U),  /* OXDC_DTC_FAULT017  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)46U),  /* OXDC_DTC_FAULT018  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)47U),  /* OXDC_DTC_FAULT019  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)48U),  /* OXDC_DTC_FAULT020  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)49U),  /* OXDC_DTC_FAULT021  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)50U),  /* OXDC_DTC_FFD001    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)51U),  /* OXDC_DTC_FFD002    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)52U),  /* OXDC_DTC_FFD003    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)53U),  /* OXDC_DTC_FFD004    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)54U),  /* OXDC_DTC_FFD005    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)55U),  /* OXDC_DTC_FFD006    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)56U),  /* OXDC_DTC_FFD007    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)57U),  /* OXDC_DTC_FFD008    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)58U),  /* OXDC_DTC_FFD009    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)59U),  /* OXDC_DTC_FFD010    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)60U),  /* OXDC_DTC_FFD011    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)61U),  /* OXDC_DTC_FFD012    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)62U),  /* OXDC_DTC_FFD013    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)63U),  /* OXDC_DTC_FFD014    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)64U),  /* OXDC_DTC_FFD015    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)65U),  /* OXDC_DTC_FFD016    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)66U),  /* OXDC_DTC_FFD017    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)67U),  /* OXDC_DTC_FFD018    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)68U),  /* OXDC_DTC_FFD019    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)69U),  /* OXDC_DTC_FFD020    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)70U),  /* OXDC_DTC_FFD021    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)71U),  /* OXDC_DTC_CLEARINFO */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)72U),  /* OXDC_DTC_LOGRX1    */
    ((U2)NVMC_ACCSS_TYPE_INAPP | (U2)0U )   /* Recovery           */
/* END : ##TOOL_OUT#NVMC_DTF_ID_CONV_TBL## */
};

const ST_NVMC_CFGDATA    st_dp_NVMC_DTF_DATA_CFG_TBL[NVMC_DTF_INNVM_NUM] = {
/* START : ##TOOL_OUT#NVMC_DTF_DATA_CFG_TBL## */
/*                         u2_addr                    u2_offset    u2_rimid_wdata                     u2_rimid_nvmsts               u1_map                               u1_rangeretry  u1_verifyretry  u1_mgr_bit_cfg  u4_module_bit_cfg   DEF              MIN              MAX           */ 
/* SAMPLE_U1          */ {(U2)BlockDescriptor_00002, (U2)0x0001U, (U2)RIMID_U1_NVMC_DA_DTF_WRI_000,  (U2)RIMID_U1_NVMC_ST_DTF_000, (U1)NVMC_MODULE_U1_P1_TRPL,          (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01002004U,   {(U4)0x77U,       (U4)0x00U,       (U4)0xFFU      }},
/* SAMPLE_U2          */ {(U2)BlockDescriptor_00005, (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_001,  (U2)RIMID_U1_NVMC_ST_DTF_001, (U1)NVMC_MODULE_U2_LO_TRPL,          (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01002004U,   {(U4)0x7777U,     (U4)0x1111U,     (U4)0xEEEEU    }},
/* SAMPLE_U4          */ {(U2)BlockDescriptor_00008, (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_002,  (U2)RIMID_U1_NVMC_ST_DTF_002, (U1)NVMC_MODULE_U4_TRPL,             (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01002004U,   {(U4)0x77777777U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* SAMPLE_OTR32       */ {(U2)BlockDescriptor_00011, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_003, (U2)RIMID_U1_NVMC_ST_DTF_003, (U1)NVMC_MODULE_OTHDBL_32,           (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01003534U,   {(U4)0x77777777U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* SAMPLE_OTR32CS     */ {(U2)BlockDescriptor_00013, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_004, (U2)RIMID_U1_NVMC_ST_DTF_004, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_28,  (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01003534U,   {(U4)0x77777777U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* BSW_SECOC_TRIP_CNT */ {(U2)DTF_BID_TRIP_CNT001,   (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_005,  (U2)RIMID_U1_NVMC_ST_DTF_005, (U1)NVMC_MODULE_U4_TRPL,             (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_TMSTP         */ {(U2)DTF_BID_TRIP_TMSTP,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_006, (U2)RIMID_U1_NVMC_ST_DTF_006, (U1)NVMC_MODULE_OTHSNGL_SUM_SMLL_28, (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_ROE_A005      */ {(U2)DTF_BID_ROE_A005,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_007, (U2)RIMID_U1_NVMC_ST_DTF_007, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT001  */ {(U2)DTF_BID_DTC_EVENT001,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_008, (U2)RIMID_U1_NVMC_ST_DTF_008, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT002  */ {(U2)DTF_BID_DTC_EVENT002,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_009, (U2)RIMID_U1_NVMC_ST_DTF_009, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT003  */ {(U2)DTF_BID_DTC_EVENT003,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_010, (U2)RIMID_U1_NVMC_ST_DTF_010, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT004  */ {(U2)DTF_BID_DTC_EVENT004,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_011, (U2)RIMID_U1_NVMC_ST_DTF_011, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT005  */ {(U2)DTF_BID_DTC_EVENT005,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_012, (U2)RIMID_U1_NVMC_ST_DTF_012, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT006  */ {(U2)DTF_BID_DTC_EVENT006,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_013, (U2)RIMID_U1_NVMC_ST_DTF_013, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT007  */ {(U2)DTF_BID_DTC_EVENT007,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_014, (U2)RIMID_U1_NVMC_ST_DTF_014, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT008  */ {(U2)DTF_BID_DTC_EVENT008,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_015, (U2)RIMID_U1_NVMC_ST_DTF_015, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT009  */ {(U2)DTF_BID_DTC_EVENT009,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_016, (U2)RIMID_U1_NVMC_ST_DTF_016, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT010  */ {(U2)DTF_BID_DTC_EVENT010,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_017, (U2)RIMID_U1_NVMC_ST_DTF_017, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT011  */ {(U2)DTF_BID_DTC_EVENT011,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_018, (U2)RIMID_U1_NVMC_ST_DTF_018, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT012  */ {(U2)DTF_BID_DTC_EVENT012,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_019, (U2)RIMID_U1_NVMC_ST_DTF_019, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT013  */ {(U2)DTF_BID_DTC_EVENT013,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_020, (U2)RIMID_U1_NVMC_ST_DTF_020, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT014  */ {(U2)DTF_BID_DTC_EVENT014,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_021, (U2)RIMID_U1_NVMC_ST_DTF_021, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT015  */ {(U2)DTF_BID_DTC_EVENT015,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_022, (U2)RIMID_U1_NVMC_ST_DTF_022, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT016  */ {(U2)DTF_BID_DTC_EVENT016,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_023, (U2)RIMID_U1_NVMC_ST_DTF_023, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT017  */ {(U2)DTF_BID_DTC_EVENT017,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_024, (U2)RIMID_U1_NVMC_ST_DTF_024, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT018  */ {(U2)DTF_BID_DTC_EVENT018,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_025, (U2)RIMID_U1_NVMC_ST_DTF_025, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT019  */ {(U2)DTF_BID_DTC_EVENT019,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_026, (U2)RIMID_U1_NVMC_ST_DTF_026, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT020  */ {(U2)DTF_BID_DTC_EVENT020,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_027, (U2)RIMID_U1_NVMC_ST_DTF_027, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT021  */ {(U2)DTF_BID_DTC_EVENT021,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_028, (U2)RIMID_U1_NVMC_ST_DTF_028, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT001  */ {(U2)DTF_BID_DTC_FAULT001,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_029, (U2)RIMID_U1_NVMC_ST_DTF_029, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT002  */ {(U2)DTF_BID_DTC_FAULT002,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_030, (U2)RIMID_U1_NVMC_ST_DTF_030, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT003  */ {(U2)DTF_BID_DTC_FAULT003,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_031, (U2)RIMID_U1_NVMC_ST_DTF_031, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT004  */ {(U2)DTF_BID_DTC_FAULT004,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_032, (U2)RIMID_U1_NVMC_ST_DTF_032, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT005  */ {(U2)DTF_BID_DTC_FAULT005,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_033, (U2)RIMID_U1_NVMC_ST_DTF_033, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT006  */ {(U2)DTF_BID_DTC_FAULT006,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_034, (U2)RIMID_U1_NVMC_ST_DTF_034, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT007  */ {(U2)DTF_BID_DTC_FAULT007,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_035, (U2)RIMID_U1_NVMC_ST_DTF_035, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT008  */ {(U2)DTF_BID_DTC_FAULT008,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_036, (U2)RIMID_U1_NVMC_ST_DTF_036, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT009  */ {(U2)DTF_BID_DTC_FAULT009,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_037, (U2)RIMID_U1_NVMC_ST_DTF_037, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT010  */ {(U2)DTF_BID_DTC_FAULT010,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_038, (U2)RIMID_U1_NVMC_ST_DTF_038, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT011  */ {(U2)DTF_BID_DTC_FAULT011,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_039, (U2)RIMID_U1_NVMC_ST_DTF_039, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT012  */ {(U2)DTF_BID_DTC_FAULT012,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_040, (U2)RIMID_U1_NVMC_ST_DTF_040, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT013  */ {(U2)DTF_BID_DTC_FAULT013,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_041, (U2)RIMID_U1_NVMC_ST_DTF_041, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT014  */ {(U2)DTF_BID_DTC_FAULT014,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_042, (U2)RIMID_U1_NVMC_ST_DTF_042, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT015  */ {(U2)DTF_BID_DTC_FAULT015,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_043, (U2)RIMID_U1_NVMC_ST_DTF_043, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT016  */ {(U2)DTF_BID_DTC_FAULT016,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_044, (U2)RIMID_U1_NVMC_ST_DTF_044, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT017  */ {(U2)DTF_BID_DTC_FAULT017,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_045, (U2)RIMID_U1_NVMC_ST_DTF_045, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT018  */ {(U2)DTF_BID_DTC_FAULT018,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_046, (U2)RIMID_U1_NVMC_ST_DTF_046, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT019  */ {(U2)DTF_BID_DTC_FAULT019,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_047, (U2)RIMID_U1_NVMC_ST_DTF_047, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT020  */ {(U2)DTF_BID_DTC_FAULT020,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_048, (U2)RIMID_U1_NVMC_ST_DTF_048, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT021  */ {(U2)DTF_BID_DTC_FAULT021,  (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_049, (U2)RIMID_U1_NVMC_ST_DTF_049, (U1)NVMC_MODULE_OTHSNGL_12,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD001    */ {(U2)DTF_BID_DTC_FFD001,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_050, (U2)RIMID_U1_NVMC_ST_DTF_050, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD002    */ {(U2)DTF_BID_DTC_FFD002,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_051, (U2)RIMID_U1_NVMC_ST_DTF_051, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD003    */ {(U2)DTF_BID_DTC_FFD003,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_052, (U2)RIMID_U1_NVMC_ST_DTF_052, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD004    */ {(U2)DTF_BID_DTC_FFD004,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_053, (U2)RIMID_U1_NVMC_ST_DTF_053, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD005    */ {(U2)DTF_BID_DTC_FFD005,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_054, (U2)RIMID_U1_NVMC_ST_DTF_054, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD006    */ {(U2)DTF_BID_DTC_FFD006,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_055, (U2)RIMID_U1_NVMC_ST_DTF_055, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD007    */ {(U2)DTF_BID_DTC_FFD007,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_056, (U2)RIMID_U1_NVMC_ST_DTF_056, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD008    */ {(U2)DTF_BID_DTC_FFD008,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_057, (U2)RIMID_U1_NVMC_ST_DTF_057, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD009    */ {(U2)DTF_BID_DTC_FFD009,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_058, (U2)RIMID_U1_NVMC_ST_DTF_058, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD010    */ {(U2)DTF_BID_DTC_FFD010,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_059, (U2)RIMID_U1_NVMC_ST_DTF_059, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD011    */ {(U2)DTF_BID_DTC_FFD011,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_060, (U2)RIMID_U1_NVMC_ST_DTF_060, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD012    */ {(U2)DTF_BID_DTC_FFD012,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_061, (U2)RIMID_U1_NVMC_ST_DTF_061, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD013    */ {(U2)DTF_BID_DTC_FFD013,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_062, (U2)RIMID_U1_NVMC_ST_DTF_062, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD014    */ {(U2)DTF_BID_DTC_FFD014,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_063, (U2)RIMID_U1_NVMC_ST_DTF_063, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD015    */ {(U2)DTF_BID_DTC_FFD015,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_064, (U2)RIMID_U1_NVMC_ST_DTF_064, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD016    */ {(U2)DTF_BID_DTC_FFD016,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_065, (U2)RIMID_U1_NVMC_ST_DTF_065, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD017    */ {(U2)DTF_BID_DTC_FFD017,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_066, (U2)RIMID_U1_NVMC_ST_DTF_066, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD018    */ {(U2)DTF_BID_DTC_FFD018,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_067, (U2)RIMID_U1_NVMC_ST_DTF_067, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD019    */ {(U2)DTF_BID_DTC_FFD019,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_068, (U2)RIMID_U1_NVMC_ST_DTF_068, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD020    */ {(U2)DTF_BID_DTC_FFD020,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_069, (U2)RIMID_U1_NVMC_ST_DTF_069, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD021    */ {(U2)DTF_BID_DTC_FFD021,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_070, (U2)RIMID_U1_NVMC_ST_DTF_070, (U1)NVMC_MODULE_OTHSNGL_32,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_CLEARINFO */ {(U2)DTF_BID_DTC_CLEARINFO, (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_071, (U2)RIMID_U1_NVMC_ST_DTF_071, (U1)NVMC_MODULE_OTHSNGL_8,           (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_LOGRX1    */ {(U2)DTF_BID_DTC_LOGRX1_1,  (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_072,  (U2)RIMID_U1_NVMC_ST_DTF_072, (U1)NVMC_MODULE_U4_TRPL,             (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}} 
/* END : ##TOOL_OUT#NVMC_DTF_DATA_CFG_TBL## */
};

/* START : ##TOOL_OUT#NVMC_AREA_NUM## */
#define NVMC_AREA_NUM                            (0U)
/* END : ##TOOL_OUT#NVMC_AREA_NUM## */

/* START : ##TOOL_OUT#NVMC_DTF_BON_DUMMY_READ_NUM## */
#define NVMC_DTF_BON_DUMMY_READ_NUM              (5U)
/* END : ##TOOL_OUT#NVMC_DTF_BON_DUMMY_READ_NUM## */
/* START : ##TOOL_OUT#NVMC_DTF_WKUP_DUMMY_READ_NUM## */
#define NVMC_DTF_WKUP_DUMMY_READ_NUM             (5U)
/* END : ##TOOL_OUT#NVMC_DTF_WKUP_DUMMY_READ_NUM## */

const U1 u1_d_NVMC_DTF_DEVICE_TYPE    = (U1)NVMC_DEVICE_TYPE_DTF;
const U2 u2_d_NVMC_NUM_OF_NVRAMBLOCKS = (U2)NVM_NUM_OF_NVRAMBLOCKS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void vd_g_Nvmc_DTF_ErrorFactorHook(const U4 u4_a_ERRORFACTOR)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u4_a_ERRORFACTOR : Error Factor                                                                              */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_DTF_ErrorFactorHook(const U4 u4_a_ERRORFACTOR)
{
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_DTF_StateErrorHook(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_DTF_StateErrorHook(void)
{
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_MemAcc_JobEndHook(const U2 u2_a_AREAID, const U1 u1_a_JOBRESULT)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_AREAID    : Address Area Id                                                                             */
/*                      u1_a_JOBRESULT : Job Result                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_MemAcc_JobEndHook(const U2 u2_a_AREAID, const U1 u1_a_JOBRESULT)
{
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Static Functions                                                                                                                 */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0            8/26/2015  KM      New.                                                                                         */
/*  1.0.1            9/29/2015  KM      Updated.                                                                                     */
/*  1.1.0           10/16/2015  KS      Keywords for tool were inserted.                                                             */
/*  1.1.1           10/21/2015  MH      Fixed QAC issue.                                                                             */
/*  1.1.2           10/29/2015  KS      Keywords for tool were inserted.                                                             */
/*  1.1.3           11/02/2015  KS      Version updated.                                                                             */
/*  1.1.4           11/18/2015  KS      Version updated.                                                                             */
/*  1.1.5           12/10/2015  KM      Version updated.                                                                             */
/*  1.1.6            1/ 6/2016  KM      Version updated.                                                                             */
/*  1.1.7            1/ 8/2016  KM      Fixed u2_dp_NVMC_DTF_DUMMY_READ_TIMEOUT.                                                     */
/*                                      Supported debug simulatior.                                                                  */
/*  1.1.8            1/11/2016  KM      Fixed Keywords for tool.                                                                     */
/*  1.1.9            2/26/2016  KM      Fixed Version Check.                                                                         */
/*  1.1.10           4/ 4/2016  KM      Version updated.                                                                             */
/*  1.1.11           4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.1.12           4/12/2016  KM      Deleted unnecessary include.                                                                 */
/*  1.1.13           4/15/2016  KM      Fixed READ_BUFFER_SIZE                                                                       */
/*  1.1.14           6/ 1/2016  KM      Version updated.                                                                             */
/*  1.1.15          10/24/2016  HK      Changed that user can disable DTF configuration.                                             */
/*                                      Fixed DTF issue : Second argment of bswd_ms_NvM_ReadBlock changed NULL to BSWD_NULL          */
/*  1.2.0           10/28/2016  HK      Changed with the small sector correspondence.                                                */
/*                                      Fixed AIP3GBSW-12, 16 issue.                                                                 */
/*  1.3.0           03/31/2017  HK      Changed from 15BSW DTF to 19BSW DTF.                                                         */
/*  1.3.1           06/09/2017  HK      Add Common Read/Write Callback api of DTF Mirror config.                                     */
/*                                      Changed u1_g_Nvmc_DTF_Hook by DTFDriver update.                                              */
/*  1.3.2           07/05/2017  MH      Remove unnecessary "#include" file.                                                          */
/*  1.3.3           08/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.3.4           09/21/2017  HK      Fixed AIP3GBSW-167 issue.                                                                    */
/*  1.3.5           11/21/2017  HK      Fixed AIP3GBSW-203 issue.                                                                    */
/*                                      Fixed AIP3GBSW-204 issue.                                                                    */
/*  1.3.6           01/19/2018  HK      Fixed AIP3GBSW-241 issue.                                                                    */
/*  1.3.7           03/20/2018  HK      Fixed AIP3GBSW-266 issue.                                                                    */
/*  1.4.0           10/ 4/2021  TN      nvmc_dtf.c v1.3.7 -> v1.4.0.                                                                 */
/*  1.4.1           29/ 7/2022  ST      nvmc_dtf.c v1.4.0 -> v1.4.1.                                                                 */
/*  1.4.2           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * KS      = Kenichi Sakai,   Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, DENSO                                                                                                 */
/*  * ST      = Shohei Takada, DENSO                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
