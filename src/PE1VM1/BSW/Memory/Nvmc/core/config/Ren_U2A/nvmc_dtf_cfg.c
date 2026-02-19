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
    ((U2)NVMC_ACCSS_TYPE_INAPP | (U2)0U ),  /* ODO              */
    ((U2)NVMC_ACCSS_TYPE_INAPP | (U2)1U ),  /* ODO_TRIP         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)0U ),  /* VDF_ESO_W0       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)1U ),  /* VDF_ESO_W1       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)2U ),  /* VDF_ESO_W2       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)3U ),  /* VDF_ESO_W3       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)4U ),  /* VDF_ESO_W4       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)5U ),  /* VDF_ESO_W5       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)6U ),  /* VDF_ESO_W6       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)7U ),  /* VDF_ESO_W7       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)8U ),  /* VDF_ESO_W8       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)9U ),  /* DATESI_CALENDAR  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)10U),  /* DATESI_OFFSET    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)11U),  /* ODO_INHERIT_FLG  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)12U),  /* MCST_IDX_USER1_1 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)13U),  /* MCST_IDX_USER1_2 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)14U),  /* MCST_IDX_USER2_1 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)15U),  /* MCST_IDX_USER2_2 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)16U),  /* MCST_IDX_USER3_1 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)17U),  /* MCST_IDX_USER3_2 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)18U),  /* MCST_IDX_GUEST_1 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)19U),  /* MCST_IDX_GUEST_2 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)20U),  /* DRVPS_MRRPOS01   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)21U),  /* DRVPS_MRRPOS02   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)22U),  /* DRVPS_MRRPOS03   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)23U),  /* DRVPS_MRRPOS04   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)24U),  /* DRVPS_MRRPOS05   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)25U),  /* DRVPS_MRRPOS06   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)26U),  /* DRVPS_MRRPOS07   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)27U),  /* DRVPS_MRRPOS08   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)28U),  /* DRVPS_MRRPOS09   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)29U),  /* DRVPS_MRRPOS10   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)30U),  /* DRVPS_MRRPOS11   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)31U),  /* DRVPS_MRRPOS12   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)32U),  /* DRVPS_MRRPOS13   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)33U),  /* DRVPS_MRRPOS14   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)34U),  /* DRVPS_MRRPOS15   */
    ((U2)NVMC_ACCSS_TYPE_INAPP | (U2)2U )   /* Recovery         */
/* END : ##TOOL_OUT#NVMC_DTF_ID_CONV_TBL## */
};

const ST_NVMC_CFGDATA    st_dp_NVMC_DTF_DATA_CFG_TBL[NVMC_DTF_INNVM_NUM] = {
/* START : ##TOOL_OUT#NVMC_DTF_DATA_CFG_TBL## */
/*                       u2_addr                         u2_offset    u2_rimid_wdata                     u2_rimid_nvmsts               u1_map                              u1_rangeretry  u1_verifyretry  u1_mgr_bit_cfg  u4_module_bit_cfg   DEF              MIN              MAX           */ 
/* VDF_ESO_W0       */ {(U2)DTF_BID_VDF_ESO_W0_0,       (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_000,  (U2)RIMID_U1_NVMC_ST_DTF_000, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W1       */ {(U2)DTF_BID_VDF_ESO_W1_0,       (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_001,  (U2)RIMID_U1_NVMC_ST_DTF_001, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W2       */ {(U2)DTF_BID_VDF_ESO_W2_0,       (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_002,  (U2)RIMID_U1_NVMC_ST_DTF_002, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W3       */ {(U2)DTF_BID_VDF_ESO_W3_0,       (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_003,  (U2)RIMID_U1_NVMC_ST_DTF_003, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W4       */ {(U2)DTF_BID_VDF_ESO_W4_0,       (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_004,  (U2)RIMID_U1_NVMC_ST_DTF_004, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W5       */ {(U2)DTF_BID_VDF_ESO_W5_0,       (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_005,  (U2)RIMID_U1_NVMC_ST_DTF_005, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W6       */ {(U2)DTF_BID_VDF_ESO_W6_0,       (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_006,  (U2)RIMID_U1_NVMC_ST_DTF_006, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W7       */ {(U2)DTF_BID_VDF_ESO_W7_0,       (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_007,  (U2)RIMID_U1_NVMC_ST_DTF_007, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W8       */ {(U2)DTF_BID_VDF_ESO_W8_0,       (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_008,  (U2)RIMID_U1_NVMC_ST_DTF_008, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* DATESI_CALENDAR  */ {(U2)DTF_BID_DATESI_CALENDAR_0,  (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_009,  (U2)RIMID_U1_NVMC_ST_DTF_009, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DATESI_OFFSET    */ {(U2)DTF_BID_DATESI_OFFSET_0,    (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_010,  (U2)RIMID_U1_NVMC_ST_DTF_010, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* ODO_INHERIT_FLG  */ {(U2)DTF_BID_ODO_INHERIT_FLG_0,  (U2)0x0001U, (U2)RIMID_U1_NVMC_DA_DTF_WRI_011,  (U2)RIMID_U1_NVMC_ST_DTF_011, (U1)NVMC_MODULE_U1_P1_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x000000FFU}},
/* MCST_IDX_USER1_1 */ {(U2)DTF_BID_MCST_IDX_USER1_1_0, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_012, (U2)RIMID_U1_NVMC_ST_DTF_012, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_USER1_2 */ {(U2)DTF_BID_MCST_IDX_USER1_2_0, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_013, (U2)RIMID_U1_NVMC_ST_DTF_013, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_USER2_1 */ {(U2)DTF_BID_MCST_IDX_USER2_1_0, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_014, (U2)RIMID_U1_NVMC_ST_DTF_014, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_USER2_2 */ {(U2)DTF_BID_MCST_IDX_USER2_2_0, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_015, (U2)RIMID_U1_NVMC_ST_DTF_015, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_USER3_1 */ {(U2)DTF_BID_MCST_IDX_USER3_1_0, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_016, (U2)RIMID_U1_NVMC_ST_DTF_016, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_USER3_2 */ {(U2)DTF_BID_MCST_IDX_USER3_2_0, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_017, (U2)RIMID_U1_NVMC_ST_DTF_017, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_GUEST_1 */ {(U2)DTF_BID_MCST_IDX_GUEST_1_0, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_018, (U2)RIMID_U1_NVMC_ST_DTF_018, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_GUEST_2 */ {(U2)DTF_BID_MCST_IDX_GUEST_2_0, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_019, (U2)RIMID_U1_NVMC_ST_DTF_019, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* DRVPS_MRRPOS01   */ {(U2)DTF_BID_DRVPS_MRRPOS01_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_020,  (U2)RIMID_U1_NVMC_ST_DTF_020, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS02   */ {(U2)DTF_BID_DRVPS_MRRPOS02_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_021,  (U2)RIMID_U1_NVMC_ST_DTF_021, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS03   */ {(U2)DTF_BID_DRVPS_MRRPOS03_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_022,  (U2)RIMID_U1_NVMC_ST_DTF_022, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS04   */ {(U2)DTF_BID_DRVPS_MRRPOS04_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_023,  (U2)RIMID_U1_NVMC_ST_DTF_023, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS05   */ {(U2)DTF_BID_DRVPS_MRRPOS05_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_024,  (U2)RIMID_U1_NVMC_ST_DTF_024, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS06   */ {(U2)DTF_BID_DRVPS_MRRPOS06_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_025,  (U2)RIMID_U1_NVMC_ST_DTF_025, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS07   */ {(U2)DTF_BID_DRVPS_MRRPOS07_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_026,  (U2)RIMID_U1_NVMC_ST_DTF_026, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS08   */ {(U2)DTF_BID_DRVPS_MRRPOS08_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_027,  (U2)RIMID_U1_NVMC_ST_DTF_027, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS09   */ {(U2)DTF_BID_DRVPS_MRRPOS09_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_028,  (U2)RIMID_U1_NVMC_ST_DTF_028, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS10   */ {(U2)DTF_BID_DRVPS_MRRPOS10_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_029,  (U2)RIMID_U1_NVMC_ST_DTF_029, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS11   */ {(U2)DTF_BID_DRVPS_MRRPOS11_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_030,  (U2)RIMID_U1_NVMC_ST_DTF_030, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS12   */ {(U2)DTF_BID_DRVPS_MRRPOS12_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_031,  (U2)RIMID_U1_NVMC_ST_DTF_031, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS13   */ {(U2)DTF_BID_DRVPS_MRRPOS13_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_032,  (U2)RIMID_U1_NVMC_ST_DTF_032, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS14   */ {(U2)DTF_BID_DRVPS_MRRPOS14_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_033,  (U2)RIMID_U1_NVMC_ST_DTF_033, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS15   */ {(U2)DTF_BID_DRVPS_MRRPOS15_0,   (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_034,  (U2)RIMID_U1_NVMC_ST_DTF_034, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}} 
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
