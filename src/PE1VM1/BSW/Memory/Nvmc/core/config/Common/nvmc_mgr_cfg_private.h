/* 1.7.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr                                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef NVMC_MGR_CFG_PRIVATE_H
#define NVMC_MGR_CFG_PRIVATE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MGR_CFG_PRIVATE_H_MAJOR             (1U)
#define NVMC_MGR_CFG_PRIVATE_H_MINOR             (7U)
#define NVMC_MGR_CFG_PRIVATE_H_PATCH             (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "nvmc_mgr_acstask_private.h"
#include "nvmc_mgr_private.h"
#include "nvmc_mgr.h"

#include "rim_ctl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* START : ##TOOL_OUT#NVMC_MODULE_NUM## */
#define NVMC_MODULE_NUM                          (5U)
/* END : ##TOOL_OUT#NVMC_MODULE_NUM## */

/* START : ##TOOL_OUT#NVMC_MODULE_ID## */
#define NVMC_MODULE_U4_TRPL                      (0U)
#define NVMC_MODULE_U4_SNGL                      (1U)
#define NVMC_MODULE_OTHSNGL_8                    (2U)
#define NVMC_MODULE_OTHSNGL_12                   (3U)
#define NVMC_MODULE_OTHSNGL_32                   (4U)
/* END : ##TOOL_OUT#NVMC_MODULE_ID## */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define vd_d_Nvmc_CfgDeInit                      (vd_g_Nvmc_DeInit)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U2 u2_d_NVMC_SHTDWN_TO_MAX;
extern const U1 u1_d_NVMC_DEVICE_TYPE_NUM;
extern const U1 u1_d_NVMC_APP_ACS_NUM;
extern const U1 u1_d_NVMC_READ_BUF_SIZE;
extern const U1 u1_d_NVMC_MODULE_NUM;

extern const ST_NVMC_DEVICE_CFG st_dp_NVMC_DEVICE_CFG[];
extern const ST_NVMC_MODULE_CFG st_dp_NVMC_MODULE_CFG[];
extern const ST_NVMC_APP_FUNC st_NVMC_APP_FUNC_TABLE[];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_d_Nvmc_CfgBonInit(void);             /* invoked at vd_g_Nvmc_BonInit  */
void    vd_d_Nvmc_CfgWkupInit(void);            /* invoked at vd_g_Nvmc_WkupInit */
/* void    vd_d_Nvmc_CfgDeInit(void); */
void    vd_d_Nvmc_CfgAcsStart(void);            /* invoked at vd_g_Nvmc_Task     */
void    vd_d_Nvmc_CfgAcsFinish(void);           /* invoked at vd_g_Nvmc_Task     */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_d_Nvmc_IsRecoveryEnable(void);
U1      u1_d_Nvmc_IsKeepAwake(void);
void    vd_d_Nvmc_ReadErrorHook(const U2 u2_a_NVMCID, const U1 u1_a_ERROR, const U1 u1_a_ERROR_DETAIL);
void    vd_d_Nvmc_WriteErrorHook(const U2 u2_a_NVMCID, const U1 u1_a_ERROR, const U1 u1_a_ERROR_DETAIL);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern ST_NVMC_READ_STS     st_sp_nvmc_read_sts[];
extern ST_NVMC_WRITE_STS    st_sp_nvmc_write_sts[];

extern ST_NVMC_READ_BUF     st_sp_nvmc_temp_read_buf[];
extern ST_NVMC_WRITE_BUF    st_sp_nvmc_temp_write_buf[];

extern U4                   u4_dp_nvmc_read_data_buf[];
extern U1                   u1_dp_nvmc_read_status_buf[];

extern U2                   u2_dp_nvmc_proc_id[];
extern U2                   u2_dp_nvmc_suspend_timer[];
extern U1                   u1_dp_nvmc_suspend_req[];
extern U1                   u1_dp_nvmc_recovery_retry[];

#endif /* NVMC_MGR_CFG_PRIVATE_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see nvmc_mgr.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
