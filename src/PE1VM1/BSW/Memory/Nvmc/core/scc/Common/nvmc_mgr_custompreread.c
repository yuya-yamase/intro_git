/* 1.4.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr Custom Pre Read                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MGR_CUSTOMPREREAD_C_MAJOR           (1U)
#define NVMC_MGR_CUSTOMPREREAD_C_MINOR           (0U)
#define NVMC_MGR_CUSTOMPREREAD_C_PATCH           (0U)

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
#include "nvmc_mgr_custom.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MGR_CUSTOMPREREAD_C_MAJOR != NVMC_MGR_CUSTOM_H_MAJOR) || \
     (NVMC_MGR_CUSTOMPREREAD_C_MINOR != NVMC_MGR_CUSTOM_H_MINOR) || \
     (NVMC_MGR_CUSTOMPREREAD_C_PATCH != NVMC_MGR_CUSTOM_H_PATCH))
#error "nvmc_mgr_custompreread.c and nvmc_mgr_custom.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Custum Pre Read : Range */
#define NVMC_CPR_DATA_SIZE                       (4U)
#define NVMC_CPR_REDUNDANT_COUNT                 (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_Nvmc_CprReadData(const ST_NVMC_CFGDATA * st_ap_CFGDATA, U4 *u4_ap_data, const U4 u4_a_PONSTS);
static U1   u1_s_Nvmc_CprReadBKRAM(const ST_NVMC_CFGDATA * st_ap_CFGDATA, U4 *u4_ap_data);
static U1   u1_s_Nvmc_CprReadDTF(const ST_NVMC_CFGDATA * st_ap_CFGDATA, U4 *u4_ap_data);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1    u1_g_Nvmc_CustomPreReadU4(const U2 u2_a_NVMCID, U4 *u4_ap_data, const U4 u4_a_PONSTS)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID   : NvmcId                                                                                       */
/*                  --> u4_ap_data    : Read data                                                                                    */
/*                  --> u4_a_PONSTS   : Status of Power On                                                                           */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1    u1_g_Nvmc_CustomPreReadU4(const U2 u2_a_NVMCID, U4 *u4_ap_data, const U4 u4_a_PONSTS)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
    const   ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
    const   ST_NVMC_MODULE_CFG  *   st_tp_MODULE_CFG;
            U2                      u2_t_id;
            U2                      u2_t_no;
            U1                      u1_t_ret;
            U1                      u1_t_device;
            U1                      u1_t_acs;
            U1                      u1_t_map_ptrn;
    
    u1_t_ret = (U1)NVMC_CPR_DTF_READ_FAIL;
    
    u1_t_device = (U1)((u2_a_NVMCID & (U2)NVMC_ID_DEVICE_MASK) >> NVMC_ID_DEVICE_SHIFT);
    /* Check Device */
    if(u1_t_device == (U1)NVMC_DEVICE_TYPE_DTF){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[NVMC_DEVICE_TYPE_DTF];
        u2_t_id = u2_a_NVMCID & (U2)NVMC_ID_DATAID_MASK;
        u1_t_acs = u1_d_Nvmc_GetDataTblNo(st_tp_DEVICE_CFG, u2_t_id, &u2_t_no);
        /* Check Access Type */
        if(u1_t_acs == (U1)NVMC_ACS_INNVM){
            st_tp_CFGDATA = &((st_tp_DEVICE_CFG->st_p_CFGDATA)[u2_t_no]);
            /* Check Size and Redundant */
            u1_t_map_ptrn    = st_tp_CFGDATA->u1_map;
            st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
            if((st_tp_MODULE_CFG->u1_rdnnum   == (U1)NVMC_CPR_REDUNDANT_COUNT) &&
               (st_tp_MODULE_CFG->u1_datasize == (U1)NVMC_CPR_DATA_SIZE)){
                u1_t_ret = u1_s_Nvmc_CprReadData(st_tp_CFGDATA, u4_ap_data, u4_a_PONSTS);
            }
        }
    }
    
    return u1_t_ret;
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
/*  U1    u1_s_Nvmc_CprReadData(const ST_NVMC_CFGDATA * st_ap_CFGDATA, U4 *u4_ap_data, const U4 u4_a_PONSTS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_CFGDATA : Config Data                                                                                  */
/*                  --> u4_ap_data    : Read data                                                                                    */
/*                  --> u4_a_PONSTS   : Status of Power On                                                                           */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1    u1_s_Nvmc_CprReadData(const ST_NVMC_CFGDATA * st_ap_CFGDATA, U4 *u4_ap_data, const U4 u4_a_PONSTS)
{
    U1                      u1_t_ret;
    
    u1_t_ret = (U1)NVMC_CPR_DTF_READ_FAIL;
    
    /* Read BackupRAM (RIM) */
    if(u4_a_PONSTS == (U4)NVMC_CPR_POWER_STATE_NOT_B_ON){
        u1_t_ret = u1_s_Nvmc_CprReadBKRAM(st_ap_CFGDATA, u4_ap_data);
    }
    
    /* Read DTF */
    if(u1_t_ret == (U1)NVMC_CPR_DTF_READ_FAIL){
        u1_t_ret = u1_s_Nvmc_CprReadDTF(st_ap_CFGDATA, u4_ap_data);
    }
    
    return u1_t_ret;
}

/*===================================================================================================================================*/
/*  U1    u1_s_Nvmc_CprReadBKRAM(const ST_NVMC_CFGDATA * st_ap_CFGDATA, U4 *u4_ap_data)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_CFGDATA : Config Data                                                                                  */
/*                  --> u4_ap_data    : Read data                                                                                    */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1    u1_s_Nvmc_CprReadBKRAM(const ST_NVMC_CFGDATA * st_ap_CFGDATA, U4 *u4_ap_data)
{
    U4                      u4_t_wdata;
    U4                      u4_t_rdata;
    U2                      u2_t_cache_wid;
    U2                      u2_t_cache_rid;
    U2                      u2_t_offset;
    U1                      u1_t_ret;
    U1                      u1_t_rslt;
    
    u1_t_ret = (U1)NVMC_CPR_DTF_READ_FAIL;
    
    /* Read WriteBuffer of RIM Data */
    u2_t_cache_wid = st_ap_CFGDATA->u2_rimid_wdata;
    u1_t_rslt = u1_g_Rim_ReadU4withStatus(u2_t_cache_wid, &u4_t_wdata);
    if((u1_t_rslt & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        /* Read ReadBuffer of RIM Data */
        u2_t_offset   = (U2)st_ap_CFGDATA->u1_mgr_bit_cfg & (U2)NVMC_SETT_CMN_READID_MASK;
        u2_t_cache_rid = u2_t_cache_wid + u2_t_offset;
        u1_t_rslt = u1_g_Rim_ReadU4withStatus(u2_t_cache_rid, &u4_t_rdata);
        if((u1_t_rslt & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            *u4_ap_data = u4_t_wdata;
            /* Compare write buffer data and read buffer data */
            if(u4_t_wdata == u4_t_rdata){
                u1_t_ret = (U1)NVMC_CPR_BKRM_READ_OK_MATCH;
            }else{
                u1_t_ret = (U1)NVMC_CPR_BKRM_READ_OK_MISMATCH;
            }
        }
    }
    
    return u1_t_ret;
}

/*===================================================================================================================================*/
/*  U1    u1_s_Nvmc_CprReadDTF(const U1 u1_a_DEVICE, const ST_NVMC_CFGDATA * st_ap_CFGDATA, U4 *u4_ap_data)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_CFGDATA : Config Data                                                                                  */
/*                  --> u4_ap_data    : Read Data                                                                                    */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1    u1_s_Nvmc_CprReadDTF(const ST_NVMC_CFGDATA * st_ap_CFGDATA, U4 *u4_ap_data)
{
    U4                      u4_t_data;
    U4                      u4_t_rdnno;
    U2                      u2_t_blockid;
    U1                      u1_t_ret;
    U1                      u1_t_rslt;
    
    u1_t_ret = (U1)NVMC_CPR_DTF_READ_FAIL;
    
    /* Read the three redundant data of DTF */
    for(u4_t_rdnno = (U4)0; u4_t_rdnno < (U4)NVMC_CPR_REDUNDANT_COUNT; u4_t_rdnno++){
        u2_t_blockid = st_ap_CFGDATA->u2_addr + ((st_ap_CFGDATA->u2_offset) * (U2)u4_t_rdnno);
        u1_t_rslt = u1_g_Nvmc_ReadDrctBlock((U1)NVMC_DEVICE_TYPE_DTF, u2_t_blockid, (U1 *)(&u4_t_data), (U2)NVMC_CPR_DATA_SIZE);
        if(u1_t_rslt == (U1)NVMC_RESULT_OK){
            *u4_ap_data = u4_t_data;
            u1_t_ret = (U1)NVMC_CPR_DTF_READ_OK_FROM_DTF1 + (U1)u4_t_rdnno;
            break;
        }
    }
    
    return u1_t_ret;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           03/05/2026   YY      New.                                                                                        */
/*                                                                                                                                   */
/*  * YY      = Yohei Yamasaka , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
