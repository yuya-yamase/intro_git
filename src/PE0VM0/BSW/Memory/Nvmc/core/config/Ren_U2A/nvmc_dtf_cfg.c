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
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)0U),  /* SAMPLE_U1      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)1U),  /* SAMPLE_U2      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)2U),  /* SAMPLE_U4      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)3U),  /* SAMPLE_OTR32   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)4U),  /* SAMPLE_OTR32CS */
    ((U2)NVMC_ACCSS_TYPE_INAPP | (U2)0U)   /* Recovery       */
/* END : ##TOOL_OUT#NVMC_DTF_ID_CONV_TBL## */
};

const ST_NVMC_CFGDATA    st_dp_NVMC_DTF_DATA_CFG_TBL[NVMC_DTF_INNVM_NUM] = {
/* START : ##TOOL_OUT#NVMC_DTF_DATA_CFG_TBL## */
/*                     u2_addr                    u2_offset    u2_rimid_wdata                     u2_rimid_nvmsts               u1_map                              u1_rangeretry  u1_verifyretry  u1_mgr_bit_cfg  u4_module_bit_cfg   DEF              MIN              MAX           */ 
/* SAMPLE_U1      */ {(U2)BlockDescriptor_00002, (U2)0x0001U, (U2)RIMID_U1_NVMC_DA_DTF_WRI_000,  (U2)RIMID_U1_NVMC_ST_DTF_000, (U1)NVMC_MODULE_U1_P1_TRPL,         (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01002004U,   {(U4)0x77U,       (U4)0x00U,       (U4)0xFFU      }},
/* SAMPLE_U2      */ {(U2)BlockDescriptor_00005, (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_001,  (U2)RIMID_U1_NVMC_ST_DTF_001, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01002004U,   {(U4)0x7777U,     (U4)0x1111U,     (U4)0xEEEEU    }},
/* SAMPLE_U4      */ {(U2)BlockDescriptor_00008, (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_002,  (U2)RIMID_U1_NVMC_ST_DTF_002, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01002004U,   {(U4)0x77777777U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* SAMPLE_OTR32   */ {(U2)BlockDescriptor_00011, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_003, (U2)RIMID_U1_NVMC_ST_DTF_003, (U1)NVMC_MODULE_OTHDBL_32,          (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01003534U,   {(U4)0x77777777U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* SAMPLE_OTR32CS */ {(U2)BlockDescriptor_00013, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_004, (U2)RIMID_U1_NVMC_ST_DTF_004, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_28, (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01003534U,   {(U4)0x77777777U, (U4)0x00000000U, (U4)0xFFFFFFFFU}} 
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
