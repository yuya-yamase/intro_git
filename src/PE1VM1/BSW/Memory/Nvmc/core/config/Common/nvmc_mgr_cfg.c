/* 1.7.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr                                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MGR_CFG_C_MAJOR                     (1U)
#define NVMC_MGR_CFG_C_MINOR                     (7U)
#define NVMC_MGR_CFG_C_PATCH                     (1U)

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

#include "veh_opemd.h"

/* Add-in Headers */
#include "nvmc_mod_lib_private.h"
#include "nvmc_mod_lib_oth_private.h"
#include "nvmc_mod_1bit_sngl_private.h"
#include "nvmc_mod_1bit_trpl_private.h"
#include "nvmc_mod_pack_e3e4_private.h"
#include "nvmc_mod_pack_e6e10_private.h"
#include "nvmc_mod_sign3bit_2xtrpl_private.h"
#include "nvmc_mod_sign3bit_dbl_private.h"
#include "nvmc_mod_sign3bit_sngl_private.h"
#include "nvmc_mod_sign3bit_trpl_private.h"
#include "nvmc_mod_typi_sngl_private.h"
#include "nvmc_mod_typi_trpl_private.h"
#include "nvmc_mod_typi_eep_trpl_private.h"
#include "nvmc_mod_u2x2_trpl_private.h"
/* #include "nvmc_mod_oth_sum_sngl_private.h" */ /* large sector type of flash specific */
/* #include "nvmc_mod_oth_sum_dbl_private.h"  */ /* large sector type of flash specific */
#include "nvmc_mod_oth_sum_eep_sngl_private.h"
#include "nvmc_mod_oth_sum_eep_dbl_private.h"
#include "nvmc_mod_oth_sngl_private.h"
#include "nvmc_mod_oth_dbl_private.h"
#include "nvmc_mod_oth_sum_sngl_smll_private.h"
#include "nvmc_mod_oth_sum_dbl_smll_private.h"

#include "nvmc_dtf_private.h"
#include "nvmc_eep_private.h"
#include "nvmc_dtf_cfg_private.h"
#include "nvmc_eep_cfg_private.h"
#include "nvmc_dtf_adapt_private.h"
#include "nvmc_eep_adapt_private.h"
#include "nvmc_dtf_inactdummy.h"

/* START : ##TOOL_OUT#NVMC_APP_FUNC_INCLUDE_HEADER## */
#include "odo_nvmif.h"
/* END : ##TOOL_OUT#NVMC_APP_FUNC_INCLUDE_HEADER## */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MGR_CFG_C_MAJOR != NVMC_MGR_PRIVATE_H_MAJOR) || \
     (NVMC_MGR_CFG_C_MINOR != NVMC_MGR_PRIVATE_H_MINOR) || \
     (NVMC_MGR_CFG_C_PATCH != NVMC_MGR_PRIVATE_H_PATCH))
#error "nvmc_mgr_cfg.c and nvmc_mgr_private.h : source and header files are inconsistent!"
#endif

#if ((NVMC_MGR_CFG_C_MAJOR != NVMC_MGR_CFG_PRIVATE_H_MAJOR) || \
     (NVMC_MGR_CFG_C_MINOR != NVMC_MGR_CFG_PRIVATE_H_MINOR) || \
     (NVMC_MGR_CFG_C_PATCH != NVMC_MGR_CFG_PRIVATE_H_PATCH))
#error "nvmc_mgr_cfg.c and nvmc_mgr_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* START : ##TOOL_OUT#NVMC_APP_ACS_NUM## */
#define NVMC_APP_ACS_NUM                         (3U)
/* END : ##TOOL_OUT#NVMC_APP_ACS_NUM## */

#define NVMC_READ_BUF_SIZE                       (NVMC_DTF_READ_BUFFER_SIZE + NVMC_EEP_READ_BUFFER_SIZE)

#define NVMC_MGR_CFG_2BYTE_SHIFT                 (16U)
#define NVMC_MGR_CFG_1BYTE_SHIFT                 (8U)
#define NVMC_MGR_CFG_1NIBBLE_SHIFT               (4U)

#define NVMC_MGR_CFG_LO_BYTE_MASK                (0x0FU)

#define NVMC_MGR_CFG_ERROR_LOG_INVALID           (0xFFFFFFFFU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
ST_NVMC_READ_BUF     st_sp_nvmc_temp_read_buf[NVMC_DEVICE_TYPE_NUM];
ST_NVMC_WRITE_BUF    st_sp_nvmc_temp_write_buf[NVMC_DEVICE_TYPE_NUM];

ST_NVMC_READ_STS     st_sp_nvmc_read_sts[NVMC_DEVICE_TYPE_NUM];
ST_NVMC_WRITE_STS    st_sp_nvmc_write_sts[NVMC_DTF_INNVM_NUM + NVMC_EEP_INNVM_NUM];

U4                   u4_dp_nvmc_read_data_buf[NVMC_READ_BUF_SIZE];
U1                   u1_dp_nvmc_read_status_buf[NVMC_READ_BUF_SIZE];

U2                   u2_dp_nvmc_proc_id[NVMC_DEVICE_TYPE_NUM];
U2                   u2_dp_nvmc_suspend_timer[NVMC_DEVICE_TYPE_NUM];
U1                   u1_dp_nvmc_suspend_req[NVMC_DEVICE_TYPE_NUM];
U1                   u1_dp_nvmc_recovery_retry[NVMC_DEVICE_TYPE_NUM];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* START : ##TOOL_OUT#NVMC_NVMC_SHTDWN_TO_MAX## */
const U2 u2_d_NVMC_SHTDWN_TO_MAX    = (U2)2100U;      /* Resolution : 20 [ms] */
/* END : ##TOOL_OUT#NVMC_NVMC_SHTDWN_TO_MAX## */
const U1 u1_d_NVMC_DEVICE_TYPE_NUM = (U1)NVMC_DEVICE_TYPE_NUM;
const U1 u1_d_NVMC_APP_ACS_NUM = (U1)NVMC_APP_ACS_NUM;
const U1 u1_d_NVMC_READ_BUF_SIZE = (U1)NVMC_READ_BUF_SIZE;
const U1 u1_d_NVMC_MODULE_NUM = (U1)NVMC_MODULE_NUM;

const ST_NVMC_DEVICE_CFG    st_dp_NVMC_DEVICE_CFG[NVMC_DEVICE_TYPE_NUM] = {
    {
#if (NVMC_DTF_ID_NUM > 0U)
        &u2_dp_NVMC_DTF_ID_CONV_TBL[0],                     /* Access type table                 */
        &st_dp_NVMC_DTF_DATA_CFG_TBL[0],                    /* Data configuration table          */
        (U2)NVMC_DTF_ID_NUM,                                /* Number of IDs                     */
        (U2)NVMC_DTF_INNVM_NUM,                             /* Number of data accessed by NVMC   */
        (U2)24400U,  /* DTF timeout(325s) * 150% */         /* Read Timeout(LSB:20ms)            */
        (U2)24400U,  /* DTF timeout(325s) * 150% */         /* Write Timeout(LSB:20ms)           */
        (U2)3U,                                             /* SyncRead Timeout(LSB:Times)       */
        (U2)100U,                                           /* Suspend Timeout(LSB:20ms)         */
        (U2)RIMID_U2_NVMC_INITID_DTF,                       /* Rim ID : Proccessing ID           */
        (U2)RIMID_U4_NVMC_REQ_DTF0,                         /* Rim ID : Request bit              */
        (U2)0U,                                             /* Read buffer base index            */
        (U2)0U,                                             /* Write status base index           */
        (U2)NVMC_RECOVERY_DTF_ID,                           /* Recovery request NVMC id          */
        (U2)RIMID_U2_NVMC_RECOVERY_DTF,                     /* Rim ID : Proccessign ID of Recovery */
        (U2)RIMID_U1_NVMC_NEXT_W_RDNNO_DTF,                 /* Rim ID : Next Write Rdn No        */
        (U1)NVMC_DTF_READ_BUFFER_SIZE,                      /* NVMACS : Use buf size             */
        (U1)1U,                                             /* Number of read retry              */
        (U1)1U,                                             /* Number of write retry             */
        (U1)10U,                                            /* Number of recovery retry          */
        (U1)0U,                                             /* Device ID                         */
        &vd_d_Nvmc_DTF_ExecDriver,                          /* Driver execution task function    */
        &u1_d_Nvmc_ReadBlock_DTF,                           /* Read request function             */
        &u1_d_Nvmc_WriteBlock_DTF,                          /* Write request function            */
        vdp_PTR_NA,                                         /* Erase request function            */
        &u1_d_Nvmc_Dtf_Adapt_ReadDrctBlock,                 /* Direct read request function      */
        &u1_d_Nvmc_IsDeviceIdle_DTF                         /* Idle check function               */
#else
        vdp_PTR_NA,                                         /* Access type table                 */
        vdp_PTR_NA,                                         /* Data configuration table          */
        (U2)NVMC_DTF_ID_NUM,                                /* Number of IDs                     */
        (U2)NVMC_DTF_INNVM_NUM,                             /* Number of data accessed by NVMC   */
        (U2)1U,      /* DTF timeout(300s) * 150% */         /* Read Timeout(LSB:20ms)            */
        (U2)1U,      /* DTF timeout(300s) * 150% */         /* Write Timeout(LSB:20ms)           */
        (U2)1U,                                             /* SyncRead Timeout(LSB:Times)       */
        (U2)1U,                                             /* Suspend Timeout(LSB:20ms)         */
        (U2)NVMC_INVALID_RIM_ID,                            /* Rim ID : Proccessing ID           */
        (U2)NVMC_INVALID_REQ_ID,                            /* Rim ID : Request bit              */
        (U2)0U,                                             /* Read buffer base index            */
        (U2)0U,                                             /* Write status base index           */
        (U2)NVMC_INVALID_REQ_ID,                            /* Recovery request NVMC id          */
        (U2)NVMC_INVALID_RIM_ID,                            /* Rim ID : Proccessign ID of Recovery */
        (U2)NVMC_INVALID_RIM_ID,                            /* Rim ID : Next Write Rdn No        */
        (U1)NVMC_DTF_READ_BUFFER_SIZE,                      /* NVMACS : Use buf size             */
        (U1)0U,                                             /* Number of read retry              */
        (U1)0U,                                             /* Number of write retry             */
        (U1)0U,                                             /* Number of recovery retry          */
        (U1)0U,                                             /* Device ID                         */
        &vd_g_Nvmc_DTF_InactDummy_Execute,                  /* Driver execution task function    */
        &u1_g_Nvmc_DTF_InactDummy_Read,                     /* Read request function             */
        &u1_g_Nvmc_DTF_InactDummy_Write,                    /* Write request function            */
        vdp_PTR_NA,                                         /* Erase request function            */
        vdp_PTR_NA,                                         /* Direct read request function      */
        &u1_g_Nvmc_DTF_InactDummy_Idle                      /* Idle check function               */
#endif /* #if (NVMC_DTF_ID_NUM > 0U) */
#if (NVMC_EEP_ID_NUM > 0U)
    },
    {
        &u2_dp_NVMC_EEP_ID_CONV_TBL[0],                     /* Access type table                 */
        &st_dp_NVMC_EEP_DATA_CFG_TBL[0],                    /* Data configuration table          */
        (U2)NVMC_EEP_ID_NUM,                                /* Number of IDs                     */
        (U2)NVMC_EEP_INNVM_NUM,                             /* Number of data accessed by NVMC   */
        (U2)5U,                                             /* Read Timeout(LSB:20ms)            */
        (U2)5U,                                             /* Write Timeout(LSB:20ms)           */
        (U2)5U,                                             /* SyncRead Timeout(LSB:Times)       */
        (U2)100U,                                           /* Suspend Timeout(LSB:20ms)         */
        (U2)RIMID_U2_NVMC_INITID_EEP,                       /* Rim ID : Proccessing ID           */
        (U2)RIMID_U4_NVMC_REQ_EEP0,                         /* Rim ID : Request bit              */
        (U2)NVMC_DTF_READ_BUFFER_SIZE,                      /* Read buffer base index            */
        (U2)NVMC_DTF_INNVM_NUM,                             /* Write status base index           */
        (U2)NVMC_INVALID_REQ_ID,                            /* Recovery request NVMC id          */
        (U2)NVMC_INVALID_RIM_ID,                            /* Rim ID : Proccessign ID of Recovery */
        (U2)RIMID_U1_NVMC_NEXT_W_RDNNO_EEP,                 /* Rim ID : Next Write Rdn No        */
        (U1)NVMC_EEP_READ_BUFFER_SIZE,                      /* NVMACS : Use buf size             */
        (U1)1U,                                             /* Number of read retry              */
        (U1)1U,                                             /* Number of write retry             */
        (U1)0U,                                             /* Number of recovery retry          */
        (U1)1U,                                             /* Device ID                         */
        &vd_d_Nvmc_MainFunc_EEP,                            /* Driver execution task function    */
        &u1_d_Nvmc_ReadBlock_EEP,                           /* Read request function             */
        &u1_d_Nvmc_WriteBlock_EEP,                          /* Write request function            */
        vdp_PTR_NA,                                         /* Erase request function            */
        &u1_d_Nvmc_Eep_Adapt_ReadDrctBlock,                 /* Direct read request function      */
        &u1_d_Nvmc_IsDeviceIdle_EEP                         /* Idle check function               */
#endif /* #if (NVMC_EEP_ID_NUM > 0U) */
    }
};

const ST_NVMC_MODULE_CFG    st_dp_NVMC_MODULE_CFG[NVMC_MODULE_NUM] = {
/* START : ##TOOL_OUT#NVMC_MODULE_CFG## */
/*    Read IF                       PreRead IF                    Write IF                     Size                 blocknum blocksize wordbuf_num rdnnum  attr     */
    {&u1_d_NvmcMod_U4R3Al_RdnData, &u1_d_NvmcMod_Lib_PreRdnData, &vd_d_NvmcMod_U4R3Al_WrData, (U1)NVMC_SIZE_4BYTE, (U1)1U,  (U1)4U,   (U1)1U,     (U1)3U, (U1)0x01U}, 
    {&u1_d_NvmcMod_U2R3Lo_RdnData, &u1_d_NvmcMod_Lib_PreRdnData, &vd_d_NvmcMod_U2R3Lo_WrData, (U1)NVMC_SIZE_2BYTE, (U1)1U,  (U1)4U,   (U1)1U,     (U1)3U, (U1)0x01U}  
/* END : ##TOOL_OUT#NVMC_MODULE_CFG## */
};

const ST_NVMC_APP_FUNC st_NVMC_APP_FUNC_TABLE[NVMC_APP_ACS_NUM] = {
/* START : ##TOOL_OUT#NVMC_APP_FUNC_TABLE## */
    {&vd_g_OdoNvmIfOdoRWTask,  &vd_g_OdoNvmIfOdoRWFinhk },
    {&vd_g_OdoNvmIfTripRWTask, &vd_g_OdoNvmIfTripRWFinhk},
    {&vd_d_Nvmc_Recovery_DTF,  vdp_PTR_NA               } 
/* END : ##TOOL_OUT#NVMC_APP_FUNC_TABLE## */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_Nvmc_SetErrorLog(const U2 u2_a_NVMCID, const U1 u1_a_ERROR, const U1 u1_a_ERROR_DETAIL, const U1 u1_a_REQUEST_TYPE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_CfgBonInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_CfgBonInit(void)
{
#if (NVMC_DTF_ID_NUM > 0U)
    vd_d_Nvmc_Dtf_Adapt_Init();
#endif /* #if (NVMC_DTF_ID_NUM > 0U) */

    vd_g_Rim_WriteU4((U2)RIMID_U4_NVMC_ERROR_LOG, (U4)NVMC_MGR_CFG_ERROR_LOG_INVALID);

#if (NVMC_DTF_ID_NUM > 0U)
    vd_d_Nvmc_BonInit_DTF();
#endif /* #if (NVMC_DTF_ID_NUM > 0U) */
#if (NVMC_EEP_ID_NUM > 0U)
    vd_d_Nvmc_EEP_Init();
#endif /* #if (NVMC_EEP_ID_NUM > 0U) */
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_CfgWkupInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_CfgWkupInit(void)
{
#if (NVMC_DTF_ID_NUM > 0U)
    vd_d_Nvmc_Dtf_Adapt_Init();
    vd_d_Nvmc_WkupInit_DTF();
#endif /* #if (NVMC_DTF_ID_NUM > 0U) */

#if (NVMC_EEP_ID_NUM > 0U)
    vd_d_Nvmc_EEP_Init();
#endif /* #if (NVMC_EEP_ID_NUM > 0U) */
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_CfgDeInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_CfgDeInit(void)
{
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_CfgAcsStart(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_CfgAcsStart(void)
{
#if (NVMC_EEP_ID_NUM > 0U)
    vd_d_Nvmc_MainFunc_EEP();
#endif /* #if (NVMC_EEP_ID_NUM > 0U) */
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_CfgAcsFinish(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_CfgAcsFinish(void)
{
#if (NVMC_DTF_ID_NUM > 0U)
    vd_d_Nvmc_MainFunc_DTF_Req();
#endif /* #if (NVMC_DTF_ID_NUM > 0U) */
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_IsRecoveryEnable(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ret : TRUE / FALSE                                                                                       */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_IsRecoveryEnable(void)
{
    U1  u1_t_ret;
/* @todo Z.Yuan start: 250320 application need to consider how to integration */
/*  U1  u1_t_insp; */

    u1_t_ret = (U1)TRUE;
/*  u1_t_insp = u1_g_InspectModeIsAct(); */
/*  if(u1_t_insp == (U1)TRUE){ */
/*      u1_t_ret = (U1)FALSE; */
/*  } */
/* @todo Z.Yuan end: 250320 application need to consider how to integration */
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_IsKeepAwake(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ret : TRUE / FALSE                                                                                       */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_IsKeepAwake(void)
{
    return(u1_g_VehopemdIgnOn());
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_ReadErrorHook(const U2 u2_a_NVMCID, const U1 u1_a_ERROR, const U1 u1_a_ERROR_DETAIL)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID       : NvmcId                                                                                   */
/*                  --> u1_a_ERROR        : NvmcSts                                                                                  */
/*                  --> u1_a_ERROR_DETAIL : Error Detail                                                                             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_ReadErrorHook(const U2 u2_a_NVMCID, const U1 u1_a_ERROR, const U1 u1_a_ERROR_DETAIL)
{
    if(u1_a_ERROR != (U1)NVMC_STATUS_COMP){
        vd_s_Nvmc_SetErrorLog(u2_a_NVMCID, u1_a_ERROR, u1_a_ERROR_DETAIL, (U1)NVMC_REQUEST_TYPE_READ);

        /* if(u1_a_ERROR_DETAIL != (U1)NVMC_MOD_RSLT_LOST){ */      /* Comment out for code analysis tool */
            /* If you insert code here, you must remove above comment out */
            /* Insert user code here */
        /* } */
    }
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_WriteErrorHook(const U2 u2_a_NVMCID, const U1 u1_a_ERROR, const U1 u1_a_ERROR_DETAIL)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID       : NvmcId                                                                                   */
/*                  --> u1_a_ERROR        : NvmcSts                                                                                  */
/*                  --> u1_a_ERROR_DETAIL : Error Detail                                                                             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_WriteErrorHook(const U2 u2_a_NVMCID, const U1 u1_a_ERROR, const U1 u1_a_ERROR_DETAIL)
{
    if(u1_a_ERROR != (U1)NVMC_STATUS_COMP){
        vd_s_Nvmc_SetErrorLog(u2_a_NVMCID, u1_a_ERROR, u1_a_ERROR_DETAIL, (U1)NVMC_REQUEST_TYPE_WRITE);

        /* Insert user code here */
    }
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
/*  static void vd_s_Nvmc_SetErrorLog(const U2 u2_a_NVMCID, const U1 u1_a_ERROR, const U1 u1_a_ERROR_DETAIL, const U1 u1_a_REQUEST_TYPE) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID       : NvmcId                                                                                   */
/*                  --> u1_a_ERROR        : NvmcSts                                                                                  */
/*                  --> u1_a_ERROR_DETAIL : Error Detail                                                                             */
/*                  --> u1_a_REQUEST_TYPE : Request Type                                                                             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_SetErrorLog(const U2 u2_a_NVMCID, const U1 u1_a_ERROR, const U1 u1_a_ERROR_DETAIL, const U1 u1_a_REQUEST_TYPE)
{
    U4  u4_t_log;
    U1  u1_t_error;

    u1_t_error = ((U1)((u1_a_ERROR        & (U1)NVMC_MGR_CFG_LO_BYTE_MASK) << NVMC_MGR_CFG_1NIBBLE_SHIFT)) |
                 (      u1_a_ERROR_DETAIL & (U1)NVMC_MGR_CFG_LO_BYTE_MASK);

    u4_t_log = ((U4)u2_a_NVMCID       << NVMC_MGR_CFG_2BYTE_SHIFT) |
               ((U4)u1_a_REQUEST_TYPE << NVMC_MGR_CFG_1BYTE_SHIFT) |
                (U4)u1_t_error;

    vd_g_Rim_WriteU4((U2)RIMID_U4_NVMC_ERROR_LOG, u4_t_log);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0            8/24/2015  KM      New.                                                                                         */
/*  1.1.0            9/29/2015  KM      Supported other size                                                                         */
/*  1.2.0           10/ 5/2015  KS      Keywords for tool were inserted.                                                             */
/*                  10/ 7/2015  KM      Bug fix.                                                                                     */
/*  1.2.1           10/20/2015  MH      Fixed nvmc_mgr.c issue                                                                       */
/*  1.2.2           10/21/2015  KM      Bug fix.                                                                                     */
/*  1.3.0           10/22/2015  KM      Supported Error log                                                                          */
/*  1.3.1           11/ 2/2015  KS      Keywords for tool were inserted.                                                             */
/*  1.3.2           11/ 6/2015  KS      Keywords for tool were inserted.                                                             */
/*                  11/ 9/2015  KM      Fixed DTF R/W timeout value.                                                                 */
/*  1.3.3           11/17/2015  KM      Fixed BON/Wakeup event order.                                                                */
/*  1.3.4           11/25/2015  KS      Keywords for tool were inserted.                                                             */
/*                                      The Other module headers were added.                                                         */
/*  1.3.5           12/ 7/2015  KS      Keywords for tool were inserted.                                                             */
/*  1.3.6           12/10/2015  KM      fp_dp_vd_NVMC_DEINIT was created.                                                            */
/*  1.3.7           12/15/2015  KM      Version updated.                                                                             */
/*  1.3.8            1/ 8/2016  KM      Version updated.                                                                             */
/*  1.3.9            1/22/2016  KM      Fixed Error log.                                                                             */
/*  1.4.0            2/ 1/2016  KM      Added PreRead Process.                                                                       */
/*                   2/23/2016  MH      Fix "no data" issue in BON/WAKE sequence.                                                    */
/*                   2/26/2016  KM      Fixed Version Check.                                                                         */
/*  1.4.1            3/25/2016  KM      Fixed EEPROM Read/Write/SyncRead Timeout value.                                              */
/*  1.4.2            4/ 4/2016  KM      Fixed PCS3-2 issue.                                                                          */
/*  1.4.3            4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.4.4            4/12/2016  KM      Deleted unnecessary include.                                                                 */
/*                                      Rollbacked u1_d_Nvmc_IsShtdwnTiming to v1.4.2                                                */
/*  1.4.5            5/16/2016  HK      Fixed PCS3-2 issue.                                                                          */
/*  1.4.6            6/ 1/2016  KM      u1_d_Nvmc_IsShtdwnTiming() name was changed to u1_d_Nvmc_IsKeepAwake().                      */
/*                                      Fixed EEPROM Read/Write Timeout value.                                                       */
/*                   6/ 9/2016  KM      Fixed EEPROM SyncRead Timeout value.                                                         */
/*  1.4.7           10/24/2016  HK      Changed that user can disable DTF configuration.                                             */
/*  1.5.0           10/28/2016  HK      Changed with the small sector correspondence.                                                */
/*  1.5.1           12/07/2016  HK      Fixed AIP3GBSW-26 issue.                                                                     */
/*  1.5.2           06/09/2017  HK      Fixed AIP3GBSW-66 issue.                                                                     */
/*  1.5.3           08/28/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.5.4           12/01/2017  HK      Fixed AIP3GBSW-174 issue.                                                                    */
/*  1.5.5           03/20/2018  HK      Fixed AIP3GBSW-266 issue.                                                                    */
/*  1.5.6            9/14/2021  TN      nvmc_mgr.c v1.5.5 -> v1.5.6.                                                                 */
/*  1.6.0            9/15/2021  TN      nvmc_mgr.c v1.5.6 -> v1.6.0.                                                                 */
/*  1.7.0           20/ 2/2023  KM      Fixed SuspendAcs. Added u1_dp_nvmc_suspend_req.                                              */
/*  1.7.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * KS      = Kenichi Sakai,   Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
