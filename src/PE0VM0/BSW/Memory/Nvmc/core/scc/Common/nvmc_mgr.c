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
#define NVMC_MGR_C_MAJOR                         (1U)
#define NVMC_MGR_C_MINOR                         (7U)
#define NVMC_MGR_C_PATCH                         (1U)

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

#include "memcpy_u1.h"
#include "lsbsrch.h"

#include "rim_func_private.h"
#include "nvmc_dck_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MGR_C_MAJOR != NVMC_MGR_H_MAJOR) || \
     (NVMC_MGR_C_MINOR != NVMC_MGR_H_MINOR) || \
     (NVMC_MGR_C_PATCH != NVMC_MGR_H_PATCH))
#error "nvmc_mgr.c and nvmc_mgr.h : source and header files are inconsistent!"
#endif

#if ((NVMC_MGR_C_MAJOR != NVMC_MGR_PRIVATE_H_MAJOR) || \
     (NVMC_MGR_C_MINOR != NVMC_MGR_PRIVATE_H_MINOR) || \
     (NVMC_MGR_C_PATCH != NVMC_MGR_PRIVATE_H_PATCH))
#error "nvmc_mgr.c and nvmc_mgr_private.h : source and header files are inconsistent!"
#endif

#if ((NVMC_MGR_C_MAJOR != NVMC_MGR_CFG_H_MAJOR) || \
     (NVMC_MGR_C_MINOR != NVMC_MGR_CFG_H_MINOR) || \
     (NVMC_MGR_C_PATCH != NVMC_MGR_CFG_H_PATCH))
#error "nvmc_mgr.c and nvmc_mgr_cfg.h : source and header files are inconsistent!"
#endif

#if ((NVMC_MGR_C_MAJOR != NVMC_MGR_CFG_PRIVATE_H_MAJOR) || \
     (NVMC_MGR_C_MINOR != NVMC_MGR_CFG_PRIVATE_H_MINOR) || \
     (NVMC_MGR_C_PATCH != NVMC_MGR_CFG_PRIVATE_H_PATCH))
#error "nvmc_mgr.c and nvmc_mgr_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Request bit */
#define NVMC_ID_REQNUM_SHIFT                     (5U)
#define NVMC_ID_REQUEST_MASK                     (0x001FU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U2      u2_s_nvmc_shtdwn_cnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_Nvmc_RamInitial(void);
static void vd_s_Nvmc_ReadWriteDataClear(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG);

static void vd_s_Nvmc_CntShtdwnTimer(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_BonInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_BonInit(void)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
            U1                      u1_t_device;

    vd_s_Nvmc_RamInitial();
    vd_d_Nvmc_CfgBonInit();
    for(u1_t_device = (U1)0U; u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM; u1_t_device++){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_device];
        vd_s_Nvmc_ReadWriteDataClear(st_tp_DEVICE_CFG);
        vd_d_Nvmc_SearchInitID(st_tp_DEVICE_CFG, (U1)NVMC_INIT_SEQ_READ_TYPE_BON);
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_WkupInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_WkupInit(void)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
            U1                      u1_t_device;

    vd_s_Nvmc_RamInitial();
    vd_d_Nvmc_CfgWkupInit();
    for(u1_t_device = (U1)0U; u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM; u1_t_device++){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_device];
        vd_d_Nvmc_SearchInitID(st_tp_DEVICE_CFG, (U1)NVMC_INIT_SEQ_READ_TYPE_WAKE);
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_Task(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_Task(void)
{
    U1  u1_t_device;

    vd_d_Nvmc_CfgAcsStart();

    for(u1_t_device = (U1)0U; u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM; u1_t_device++){
        vd_d_Nvmc_AcsTask(u1_t_device);
    }

    vd_d_Nvmc_CfgAcsFinish();
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_PeriodicTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_PeriodicTask(void)
{
    vd_s_Nvmc_CntShtdwnTimer();
    vd_d_Nvmc_ChkDeviceTimer();
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_IsShtdwnOk(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_IsShtdwnOk(void)
{
    U1  u1_t_ret;
    U1  u1_t_device;
    U1  u1_t_rslt;

    u1_t_ret = (U1)TRUE;

    if(u2_s_nvmc_shtdwn_cnt <= u2_d_NVMC_SHTDWN_TO_MAX){
        u1_t_rslt = u1_g_Nvmc_GetAllAcsReq((U1)NVMC_DEVICE_TYPE_ALL);
        if(u1_t_rslt == (U1)TRUE){
            u1_t_ret = (U1)FALSE;
        }

        for(u1_t_device = (U1)0U; u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM; u1_t_device++){
            u1_t_rslt = st_dp_NVMC_DEVICE_CFG[u1_t_device].fp_p_u1_is_idle();
            if(u1_t_rslt != (U1)TRUE){
                u1_t_ret = (U1)FALSE;
                break;
            }
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_ClearShtdwnTimer(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_ClearShtdwnTimer(void)
{
    u2_s_nvmc_shtdwn_cnt = (U2)0U;
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_SetAcsReq(const U2 u2_a_NVMCID, const U1 u1_a_MODE)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> u1_a_MODE   : Mode                                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_SetAcsReq(const U2 u2_a_NVMCID, const U1 u1_a_MODE)
{
            U2                      u2_t_id;
            U2                      u2_t_no;
            U1                      u1_t_device;
            U1                      u1_t_acs;
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;

    u1_t_device = (U1)((u2_a_NVMCID & (U2)NVMC_ID_DEVICE_MASK) >> NVMC_ID_DEVICE_SHIFT);
    if(u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_device];
        u2_t_id = u2_a_NVMCID & (U2)NVMC_ID_DATAID_MASK;
        u1_t_acs = u1_d_Nvmc_GetDataTblNo(st_tp_DEVICE_CFG, u2_t_id, &u2_t_no);
        if(u1_t_acs == (U1)NVMC_ACS_INAPP){
            vd_d_Nvmc_SetAcsReqSub(&st_dp_NVMC_DEVICE_CFG[u1_t_device], u2_t_id, u1_a_MODE);
        }
    }
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_GetAcsReq(const U2 u2_a_NVMCID)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*  Return:         U1 u1_t_ret : Request                                                                                            */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_GetAcsReq(const U2 u2_a_NVMCID)
{
            U1                      u1_t_ret;
            U1                      u1_t_device;
            U2                      u2_t_id;
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;

    u1_t_ret = (U1)FALSE;
    u1_t_device = (U1)((u2_a_NVMCID & (U2)NVMC_ID_DEVICE_MASK) >> NVMC_ID_DEVICE_SHIFT);
    if(u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_device];
        u2_t_id = u2_a_NVMCID & (U2)NVMC_ID_DATAID_MASK;
        /* The range of u2_t_id shall be checked in sub function. */
        u1_t_ret = u1_d_Nvmc_GetAcsReqSub(st_tp_DEVICE_CFG, u2_t_id);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_GetAllAcsReq(const U1 u1_a_DEVICE)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE : Device                                                                                         */
/*  Return:         U1 u1_t_ret : Request                                                                                            */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_GetAllAcsReq(const U1 u1_a_DEVICE)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
            U2                      u2_t_reqid;
            U1                      u1_t_ret;
            U1                      u1_t_num;
            U1                      u1_t_cnt;

    if(u1_a_DEVICE == (U1)NVMC_DEVICE_TYPE_ALL){
        u1_t_cnt = (U1)0U;
        u1_t_num = u1_d_NVMC_DEVICE_TYPE_NUM;
    }
    else if(u1_a_DEVICE < u1_d_NVMC_DEVICE_TYPE_NUM){
        u1_t_cnt = u1_a_DEVICE;
        u1_t_num = u1_t_cnt + (U1)NVMC_SINGLE_DEV_NUM;
    }
    else{
        u1_t_cnt = (U1)U1_MAX;
        u1_t_num = (U1)0U;
    }
    u1_t_ret = (U1)FALSE;
    while(u1_t_cnt < u1_t_num){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_cnt];
        u2_t_reqid = u2_d_Nvmc_GetAcsReqNo(st_tp_DEVICE_CFG);
        if(u2_t_reqid != (U2)NVMC_REQID_TASK_IDLE){
            u1_t_ret = (U1)TRUE;
            break;
        }
        u1_t_cnt++;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1  u1_g_Nvmc_ConvBlockIdToNvmcId(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, U2 *u2_ap_nvmcid)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE   : DEVICE                                                                                       */
/*                  --> u2_a_BLOCKID  : BlockId                                                                                      */
/*                  --> *u2_ap_nvmcid : NvmcId                                                                                       */
/*  Return:         U1 u1_t_num : NvmcId Num                                                                                         */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_ConvBlockIdToNvmcId(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, U2 *u2_ap_nvmcid)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
    const   ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
    const   ST_NVMC_MODULE_CFG  *   st_tp_MODULE_CFG;
            U2                      u2_t_data_id;
            U2                      u2_t_cache_id;
            U2                      u2_t_start_block;
            U2                      u2_t_end_block;
            U2                      u2_t_offset;
            U2                      u2_t_dev_bit;
            U2                      u2_t_data_id_num;
            U1                      u1_t_num;
            U1                      u1_t_acs_type;
            U1                      u1_t_rdn;
            U1                      u1_t_rdn_num;
            U1                      u1_t_map_ptrn;

    u1_t_num = (U1)0U;
    if(
        (u2_ap_nvmcid != vdp_PTR_NA               ) &&
        (u1_a_DEVICE  <  u1_d_NVMC_DEVICE_TYPE_NUM)
    ){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_a_DEVICE];
        u2_t_dev_bit = (U2)u1_a_DEVICE << NVMC_ID_DEVICE_SHIFT;
        u2_t_data_id_num = st_tp_DEVICE_CFG->u2_id_num;
        u2_t_data_id = (U2)0U;
        while(u2_t_data_id < u2_t_data_id_num){
            u1_t_acs_type = u1_d_Nvmc_GetDataTblNo(st_tp_DEVICE_CFG, u2_t_data_id, &u2_t_cache_id);
            if(u1_t_acs_type == (U1)NVMC_ACS_INNVM){
                st_tp_CFGDATA = &((st_tp_DEVICE_CFG->st_p_CFGDATA)[u2_t_cache_id]);
                u2_t_start_block = st_tp_CFGDATA->u2_addr;
                u2_t_offset = st_tp_CFGDATA->u2_offset;
                u1_t_map_ptrn = st_tp_CFGDATA->u1_map;
                if(u1_t_map_ptrn < u1_d_NVMC_MODULE_NUM){
                    st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
                    u2_t_end_block = u2_t_start_block + (U2)(st_tp_MODULE_CFG->u1_blocknum);
                    u1_t_rdn_num = st_tp_MODULE_CFG->u1_rdnnum;
                }
                else{
                 /* u2_t_end_block = (U2)0U; QAC warning #2982 */
                    u1_t_rdn_num   = (U1)0U;
                }
                for(u1_t_rdn = (U1)0U; u1_t_rdn < u1_t_rdn_num; u1_t_rdn++){
                    if(
                        (u2_a_BLOCKID >= u2_t_start_block) &&
                        (u2_a_BLOCKID < u2_t_end_block)
                    ){
                        u2_ap_nvmcid[u1_t_num] = (u2_t_data_id | u2_t_dev_bit);
                        u1_t_num++;
                        if(u1_t_num >= (U1)NVMC_BLOCKID_TO_NVMCID_MAX){
                            u2_t_data_id = (U2)U2_MAX - (U2)1U;
                        }
                        break;
                    }
                    u2_t_start_block += u2_t_offset;
                    u2_t_end_block += u2_t_offset;
                }
            }
            u2_t_data_id++;
        }
    }
    return(u1_t_num);
}

/*===================================================================================================================================*/
/*  U1  u1_d_Nvmc_TickTime(U2 *u2_ap_timer, const U2 u2_a_TIMEOUT)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u2_ap_timer : Timer Pointer                                                                                 */
/*                  --> u2_a_TIMEOUT : Timeout                                                                                       */
/*  Return:         U1 u1_t_ret : Result(TRUE:TimeOut)                                                                               */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_TickTime(U2 * u2_ap_timer, const U2 u2_a_TIMEOUT)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;

    if(*u2_ap_timer > u2_a_TIMEOUT){
        *u2_ap_timer = u2_a_TIMEOUT;
    }
    if(*u2_ap_timer > (U1)0U){
        (*u2_ap_timer)--;
        if(*u2_ap_timer == (U2)0U){
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_SetAcsReqSub(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID, const U1 u1_a_MODE)      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE Pointer                                                                            */
/*                  --> u2_a_DATAID      : DATA ID                                                                                   */
/*                  --> u1_a_MODE        : Mode                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_SetAcsReqSub(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID, const U1 u1_a_MODE)
{
    U4  u4_t_bit;
    U4  u4_t_rimdata;
    U2  u2_t_rimid;
    U1  u1_t_rslt;

    if(u2_a_DATAID < st_ap_DEVICE_CFG->u2_id_num){

        u2_t_rimid   = st_ap_DEVICE_CFG->u2_rimid_req + (u2_a_DATAID >> NVMC_ID_REQNUM_SHIFT);
        u4_t_rimdata = (U4)0U;
        u1_t_rslt    = u1_g_Rim_ReadU4withStatus(u2_t_rimid, &u4_t_rimdata);
        if((u1_t_rslt & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK){
            u4_t_rimdata = (U4)0U;
        }

        u4_t_bit = (U4)0x00000001U << (u2_a_DATAID & (U2)NVMC_ID_REQUEST_MASK);
        if(u1_a_MODE == (U1)TRUE){
            u4_t_rimdata |= u4_t_bit;
        }
        else{
            u4_t_rimdata &= ((U4)U4_MAX ^ u4_t_bit);
        }
        (void)u1_g_Rim_WriteU4withStatus(u2_t_rimid, u4_t_rimdata);
    }
}

/*===================================================================================================================================*/
/*  U1  u1_d_Nvmc_GetAcsReqSub(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG  : DEVICE Pointer                                                                           */
/*                  --> u2_a_DATAID       : DATA ID                                                                                  */
/*  Return:         U1 u1_t_ret : Request                                                                                            */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_GetAcsReqSub(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID)
{
    U4  u4_t_mask;
    U4  u4_t_bit;
    U2  u2_t_size;
    U2  u2_t_rimid;
    U1  u1_t_ret;
    U1  u1_t_rslt;

    u1_t_ret = (U1)FALSE;
    if(u2_a_DATAID < st_ap_DEVICE_CFG->u2_id_num){

        u2_t_size  = u2_a_DATAID >> NVMC_ID_REQNUM_SHIFT;
        u2_t_rimid = st_ap_DEVICE_CFG->u2_rimid_req + u2_t_size;
        u4_t_bit   = (U4)0U;
        u1_t_rslt  = u1_g_Rim_ReadU4withStatus(u2_t_rimid, &u4_t_bit);
        if((u1_t_rslt & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            u4_t_mask = (U4)0x00000001U << (u2_a_DATAID & (U2)NVMC_ID_REQUEST_MASK);
            if((u4_t_bit & u4_t_mask) != (U4)0U){
                u1_t_ret = (U1)TRUE;
            }
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U2  u2_d_Nvmc_GetAcsReqNo(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG  : DEVICE Pointer                                                                           */
/*  Return:         U2 u2_t_ret : Req No                                                                                             */
/*===================================================================================================================================*/
U2      u2_d_Nvmc_GetAcsReqNo(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG)
{
    U4  u4_t_bit;
    U2  u2_t_ret;
    U2  u2_t_size;
    U2  u2_t_rimid;
    U2  u2_t_idnum;
    U2  u2_t_cnt;
    U1  u1_t_lsb;
    U1  u1_t_rimrslt;

    u2_t_ret = (U2)NVMC_REQID_TASK_IDLE;
    u2_t_idnum = st_ap_DEVICE_CFG->u2_id_num;
    u2_t_size = (u2_t_idnum + (U2)NVMC_ID_REQUEST_MASK) >> NVMC_ID_REQNUM_SHIFT;
    u2_t_rimid = st_ap_DEVICE_CFG->u2_rimid_req;
    for(u2_t_cnt = (U2)0U; u2_t_cnt < u2_t_size; u2_t_cnt++){
        u4_t_bit = (U4)0U;
        u1_t_rimrslt = u1_g_Rim_ReadU4withStatus(u2_t_rimid, &u4_t_bit);
        if((u1_t_rimrslt & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK){
            (void)u1_g_Rim_WriteU4withStatus(u2_t_rimid, (U4)0U);
        }
        if(u4_t_bit != (U4)0U){
            u1_t_lsb = u1_g_LsbSrch(u4_t_bit);
            if(u1_t_lsb < (U1)LSB_SRCH_BITLEN_MAX){
                u2_t_ret = (U2)(u2_t_cnt << NVMC_ID_REQNUM_SHIFT) + (U2)u1_t_lsb;
                if(u2_t_ret >= u2_t_idnum){
                    (void)u1_g_Rim_WriteU4withStatus(u2_t_rimid, (U4)0U);
                    u2_t_ret = (U2)NVMC_REQID_TASK_IDLE;
                }
                break;
            }
        }
        u2_t_rimid++;
    }
    return(u2_t_ret);
}

/*===================================================================================================================================*/
/*  U1  u1_d_Nvmc_GetDataTblNo(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID, U2 *u2_ap_no)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG  : DEVICE Pointer                                                                           */
/*                  --> u2_a_DATAID       : DATA ID                                                                                  */
/*                  --> *u2_ap_no         : Common Tbl No Pointer                                                                    */
/*  Return:         U1 u1_t_ret : Acsway(Err:0xFF)                                                                                   */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_GetDataTblNo(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID, U2 * u2_ap_no)
{
    U2  u2_t_type_no;
    U2  u2_t_cache_id;
    U2  u2_t_acs_type_bit;
    U1  u1_t_ret;

    u1_t_ret = (U1)NVMC_ACS_TYPE_ERR;
    if(u2_a_DATAID < st_ap_DEVICE_CFG->u2_id_num){
        u2_t_type_no = st_ap_DEVICE_CFG->u2_p_NO[u2_a_DATAID];
        u2_t_acs_type_bit = u2_t_type_no & (U2)NVMC_ACCSS_TYPE_BIT;
        u2_t_cache_id = u2_t_type_no & (U2)NVMC_ACCSS_REQ_ID_MASK;
        if(u2_t_acs_type_bit == (U2)NVMC_ACCSS_TYPE_INNVM){
            if(u2_t_cache_id < st_ap_DEVICE_CFG->u2_innvm_num){
                u1_t_ret = (U1)NVMC_ACS_INNVM;
                *u2_ap_no = u2_t_cache_id;
            }
        }
        else{
            if(u2_t_cache_id < (U2)u1_d_NVMC_APP_ACS_NUM){
                u1_t_ret = (U1)NVMC_ACS_INAPP;
                *u2_ap_no = u2_t_cache_id;
            }
        }
    }
    else{
        *u2_ap_no = (U2)0U;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1  u1_d_Nvmc_GetRimData(const U2 u2_a_RIMID, U4 * u4_ap_data, const U2 u2_a_SIZE)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_RIMID  : RIMID                                                                                          */
/*                  --> *u4_ap_data : Data Pointer                                                                                   */
/*                  --> u2_a_SIZE   : Size                                                                                           */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_GetRimData(const U2 u2_a_RIMID, U4 * u4_ap_data, const U2 u2_a_SIZE)
{
    U2  u2_t_data;
    U1  u1_t_ret;
    U1  u1_t_data;

    switch(u2_a_SIZE){
        case NVMC_SIZE_1BYTE:
            u1_t_data = (U1)0U;
            u1_t_ret = u1_g_Rim_ReadU1withStatus(u2_a_RIMID, &u1_t_data);
            if((u1_t_ret & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
                *u4_ap_data = (U4)u1_t_data;
            }
            break;
        case NVMC_SIZE_2BYTE:
            u2_t_data = (U2)0U;
            u1_t_ret = u1_g_Rim_ReadU2withStatus(u2_a_RIMID, &u2_t_data);
            if((u1_t_ret & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
                *u4_ap_data = (U4)u2_t_data;
            }
            break;
        case NVMC_SIZE_4BYTE:
            u1_t_ret = u1_g_Rim_ReadU4withStatus(u2_a_RIMID, u4_ap_data);
            break;
        default:
            u1_t_ret = u1_g_Rim_ReadOtherwithStatus(u2_a_RIMID, u2_a_SIZE, (U1 *)u4_ap_data);       /* QAC : Intentional pointer cast */
            break;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1  u1_d_Nvmc_SetRimData(const U2 u2_a_RIMID, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_RIMID  : RIMID                                                                                          */
/*                  --> *u4_ap_DATA : Data Pointer                                                                                   */
/*                  --> u2_a_SIZE   : RimSize                                                                                        */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_SetRimData(const U2 u2_a_RIMID, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE)
{
    U1  u1_t_ret;

    switch(u2_a_SIZE){
        case NVMC_SIZE_1BYTE:
            u1_t_ret = u1_g_Rim_WriteU1withStatus(u2_a_RIMID, (U1)(*u4_ap_DATA));
            break;
        case NVMC_SIZE_2BYTE:
            u1_t_ret = u1_g_Rim_WriteU2withStatus(u2_a_RIMID, (U2)(*u4_ap_DATA));
            break;
        case NVMC_SIZE_4BYTE:
            u1_t_ret = u1_g_Rim_WriteU4withStatus(u2_a_RIMID, (*u4_ap_DATA));
            break;
        default:
            u1_t_ret = u1_g_Rim_WriteOtherwithStatus(u2_a_RIMID, u2_a_SIZE, (const U1 *)u4_ap_DATA);    /* QAC : Intentional pointer cast */
            break;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_ConvPtrU4toU1(U4 * u4_ap_data, const U2 u2_a_NUMBYTE)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u4_ap_data    : In/Out Data                                                                                  */
/*                  --> u2_a_NUMBYTE  : Byte size of data                                                                            */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_ConvPtrU4toU1(U4 * u4_ap_data, const U2 u2_a_NUMBYTE)
{
    U2  u2_t_data;
    U1  u1_t_data;

    switch(u2_a_NUMBYTE){
        case NVMC_SIZE_1BYTE:
            u1_t_data = (U1)*u4_ap_data;
            *u4_ap_data = (U4)0U;                           /* Clear unused area */
            vd_g_MemcpyU1((U1 *)u4_ap_data, &u1_t_data, (U4)u2_a_NUMBYTE);
            break;
        case NVMC_SIZE_2BYTE:
            u2_t_data = (U2)*u4_ap_data;
            *u4_ap_data = (U4)0U;                           /* Clear unused area */
            vd_g_MemcpyU1((U1 *)u4_ap_data, (U1 *)&u2_t_data, (U4)u2_a_NUMBYTE);
            break;
        /* case NVMC_SIZE_4BYTE: */
        default:
            /* Nothing to do */
            break;
    }
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_ConvPtrU1toU4(U4 * u4_ap_cpydst, const U1 * const u1_ap_CPYSRC, const u2_a_NUMBYTE)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u4_ap_cpydst  : Pointer to copy distination                                                                  */
/*                  --> u1_ap_CPYSRC  : Pointer to copy source                                                                       */
/*                  --> u2_a_NUMBYTE  : Byte size of data                                                                            */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_ConvPtrU1toU4(U4 * u4_ap_cpydst, const U1 * const u1_ap_CPYSRC, const U2 u2_a_NUMBYTE)
{
    U2 u2_t_data;

    switch(u2_a_NUMBYTE){
        case NVMC_SIZE_1BYTE:
            *u4_ap_cpydst = (U4)*u1_ap_CPYSRC;
            break;
        case NVMC_SIZE_2BYTE:
            vd_g_MemcpyU1((U1 *)&u2_t_data, u1_ap_CPYSRC, (U4)u2_a_NUMBYTE);
            *u4_ap_cpydst = (U4)u2_t_data;
            break;
        /* case NVMC_SIZE_4BYTE: */
        default:
            vd_g_MemcpyU1((U1 *)u4_ap_cpydst, u1_ap_CPYSRC, (U4)u2_a_NUMBYTE);
            break;
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
/*  static void vd_s_Nvmc_RamInitial(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_RamInitial(void)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
            U4                      u4_t_req_bit;
            U2                      u2_t_cnt;
            U2                      u2_t_rimid;
            U2                      u2_t_size;
            U2                      u2_t_req_id_num;
            U1                      u1_t_device;

    u2_s_nvmc_shtdwn_cnt = (U2)0U;
    for(u1_t_device = (U1)0U; u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM; u1_t_device++){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_device];

        u2_t_req_id_num = st_tp_DEVICE_CFG->u2_id_num;
        u2_t_size = u2_t_req_id_num >> NVMC_ID_REQNUM_SHIFT;
        u2_t_rimid = st_tp_DEVICE_CFG->u2_rimid_req;
        for(u2_t_cnt = (U2)0U; u2_t_cnt < u2_t_size; u2_t_cnt++){
            (void)u1_g_Rim_WriteU4withStatus(u2_t_rimid, (U4)U4_MAX);
            u2_t_rimid++;
        }
        u2_t_req_id_num &= (U2)NVMC_ID_REQUEST_MASK;
        if(u2_t_req_id_num != (U2)0U){
            u4_t_req_bit = ((U4)1U << u2_t_req_id_num) - (U4)1U;
            (void)u1_g_Rim_WriteU4withStatus(u2_t_rimid, u4_t_req_bit);
        }
    }

    vd_d_Nvmc_AcsTaskRamInit();
}

/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_ReadWriteDataClear(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE Pointer                                                                            */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_ReadWriteDataClear(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG)
{
            U4                      u4_tp_buf[NVMC_BUF_SIZE];
    const   ST_NVMC_CFGDATA     *   st_tp_DATA_CFG;
    const   ST_NVMC_CFGDATA     *   st_tp_CFG;
            U2                      u2_t_inid_num;
            U2                      u2_t_innvm_id;
            U2                      u2_t_rim_id;
            U1                      u1_t_size;
            U1                      u1_t_last_index;
            U1                      u1_t_map_ptrn;

    st_tp_DATA_CFG = st_ap_DEVICE_CFG->st_p_CFGDATA;
    u2_t_inid_num = st_ap_DEVICE_CFG->u2_innvm_num;
    for(u2_t_innvm_id = (U2)0U; u2_t_innvm_id < u2_t_inid_num; u2_t_innvm_id++){
        st_tp_CFG = &st_tp_DATA_CFG[u2_t_innvm_id];
        u1_t_map_ptrn = st_tp_CFG->u1_map;
        if(u1_t_map_ptrn < u1_d_NVMC_MODULE_NUM){
            u1_t_size = st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn].u1_datasize;
            if(u1_t_size != (U1)0U){
                u1_t_last_index = (u1_t_size + (U1)NVMC_ARRAY_INDEX_MASK) >> NVMC_ARRAY_INDEX_SHIFT;
                u1_t_last_index--;                          /* No underflow */
                u4_tp_buf[u1_t_last_index] = (U4)0U;
                vd_d_Nvmc_DCK_SetDefaultData(st_tp_CFG, &u4_tp_buf[0], u1_t_size);
                u2_t_rim_id = st_tp_CFG->u2_rimid_wdata;
                (void)u1_d_Nvmc_SetRimData(u2_t_rim_id, &u4_tp_buf[0], (U2)u1_t_size);
                if((st_tp_CFG->u1_mgr_bit_cfg & (U1)NVMC_SETT_CMN_READID_MASK) != (U1)0U){
                    u2_t_rim_id++;
                    (void)u1_d_Nvmc_SetRimData(u2_t_rim_id, &u4_tp_buf[0], (U2)u1_t_size);
                }
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_CntShtdwnTimer(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_CntShtdwnTimer(void)
{
    U1  u1_t_igon;

    u1_t_igon = u1_d_Nvmc_IsKeepAwake();
    if(u1_t_igon == (U1)TRUE){
        u2_s_nvmc_shtdwn_cnt = (U2)0U;
    }
    else if(u2_s_nvmc_shtdwn_cnt < (U2)U2_MAX){
        u2_s_nvmc_shtdwn_cnt++;
    }
    else{
        /* Nothing to do */
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0            8/31/2015   KM      New.                                                                                        */
/*  1.1.0            9/29/2015   KM      Supported other size                                                                        */
/*  1.2.0           10/ 7/2015   KM      Updated & Bug fix.                                                                          */
/*  1.2.1           10/20/2015   MH      Fixed code sonar warning.                                                                   */
/*                                       Updated data read logic for map configuration error.                                        */
/*                                       Removed unnecessary comment.                                                                */
/*  1.2.2           10/21/2015   KM      Bug fix.                                                                                    */
/*  1.3.0           10/21/2015   MH      Updated comments                                                                            */
/*                                       Fixed QAC issue                                                                             */
/*                  10/22/2015   KM      Supported Error log                                                                         */
/*  1.3.1           11/02/2015   KS      vd_s_Nvmc_CntShtdwnTimer() name was changed                                                 */
/*  1.3.2           11/ 9/2015   KM      R/W data is updated when Cache NG.                                                          */
/*  1.3.3           11/20/2015   KM      Fixed u1_s_Nvmc_AcsNvmWriteReq.                                                             */
/*  1.3.4           11/25/2015   KS      Version updated.                                                                            */
/*  1.3.5           12/ 7/2015   KS      Version updated.                                                                            */
/*  1.3.6           12/15/2015   KM      vd_g_Nvmc_DeInit was created.                                                               */
/*                                       Fixed u1_s_Nvmc_ReadMain_GetData.                                                           */
/*                                       Fixed u1_s_Nvmc_GetAct_WkupCondNon.                                                         */
/*  1.3.7           12/16/2015   KM      Divided nvmc_mgr to nvmc_mgr_acsreq and nvmc_mgr_acstask.                                   */
/*  1.3.8            1/ 8/2016   KM      vd_d_Nvmc_DCK_SetErrData() name was changed to vd_d_Nvmc_DCK_SetDefaultData().              */
/*  1.3.9            1/22/2016   KM      Version updated.                                                                            */
/*  1.4.0            2/ 1/2016   KM      Version updated.                                                                            */
/*  1.4.1            3/25/2016   KM      Version updated.                                                                            */
/*  1.4.2            4/ 4/2016   KM      Fixed PCS3-2 issue.                                                                         */
/*  1.4.3            4/11/2016   HK      Fixed function comments.                                                                    */
/*  1.4.4            4/12/2016   KM      Deleted unnecessary include.                                                                */
/*  1.4.5            5/16/2016   HK      Fixed PCS3-2 issue.                                                                         */
/*  1.4.6            5/30/2016   KM      u1_d_Nvmc_IsShtdwnTiming() name was changed to u1_d_Nvmc_IsKeepAwake().                     */
/*  1.4.7           10/24/2016   HK      Changed that user can disable DTF configuration.                                            */
/*  1.5.0           10/28/2016   HK      Changed with the small sector correspondence.                                               */
/*  1.5.1           12/07/2016   HK      Fixed AIP3GBSW-26 issue.                                                                    */
/*                               MH      Fixed AIP3GBSW-28 issue.                                                                    */
/*  1.5.2           06/09/2017   HK      Fixed AIP3GBSW-66 issue.                                                                    */
/*  1.5.3           08/28/2017   HK      Fixed AIP3GBSW-146 issue.                                                                   */
/*  1.5.4           12/01/2017   HK      Fixed AIP3GBSW-174 issue.                                                                   */
/*  1.5.5           03/20/2018   HK      Fixed AIP3GBSW-266 issue.                                                                   */
/*  1.5.6            9/14/2021   TN      NULL -> vdp_PTR_NA.                                                                         */
/*  1.6.0            9/15/2021   TN      vd_g_Fpcall_vd_Fvd(fp_dp_vd_NVMC_BONINIT)   -> vd_d_Nvmc_CfgBonInit                         */
/*                                       vd_g_Fpcall_vd_Fvd(fp_dp_vd_NVMC_WAKEINIT)  -> vd_d_Nvmc_CfgWkupInit                        */
/*                                       vd_g_Nvmc_DeInit                            -> vd_g_Nvmc_CfgDeInit                          */
/*                                       vd_g_Fpcall_vd_Fvd(fp_dp_vd_NVMC_TASK_PRE)  -> vd_d_Nvmc_CfgAcsStart                        */
/*                                       vd_g_Fpcall_vd_Fvd(fp_dp_vd_NVMC_TASK_POST) -> vd_d_Nvmc_CfgAcsFinish                       */
/*                  10/ 1/2021   TN      QAC warning was fixed.                                                                      */
/*                  10/ 4/2021   TN      Codesonar red warnings "Uninitialized Variable" were fixed.                                 */
/*  1.7.0           20/ 2/2023   KM      Fixed SuspendAcs.                                                                           */
/*                                       vd_g_Nvmc_SuspendAcs() -> u1_g_Nvmc_SuspendAcs().                                           */
/*                                       Added u1_g_Nvmc_IsSuspendAcs().                                                             */
/*  1.7.1           11/ 8/2023   KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                            */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * KS      = Kenichi Sakai,   Denso Create                                                                                        */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
