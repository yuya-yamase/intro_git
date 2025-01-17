/* 1.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr AcsReq                                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MGR_ACSREQ_C_MAJOR                  (1U)
#define NVMC_MGR_ACSREQ_C_MINOR                  (2U)
#define NVMC_MGR_ACSREQ_C_PATCH                  (1U)

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

#include "memfill_u1.h"

#include "rim_func_private.h"
#include "nvmc_mgr_acsreq_private.h"
#include "nvmc_dck_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MGR_ACSREQ_C_MAJOR != NVMC_MGR_ACSREQ_PRIVATE_H_MAJOR) || \
     (NVMC_MGR_ACSREQ_C_MINOR != NVMC_MGR_ACSREQ_PRIVATE_H_MINOR) || \
     (NVMC_MGR_ACSREQ_C_PATCH != NVMC_MGR_ACSREQ_PRIVATE_H_PATCH))
#error "nvmc_mgr_acsreq.c and nvmc_mgr_acsreq_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* R/W Data type */
#define NVMC_READ_RDATA                          (0U)
#define NVMC_READ_WDATA                          (1U)

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
static U1   u1_s_Nvmc_ReadMain(const U2 u2_a_NVMCID, U4 * u4_ap_data, const U2 u2_a_SIZE, const U1 u1_a_RW);
static U1   u1_s_Nvmc_ReadMain_GetData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_data, const U2 u2_a_SIZE, const U1 u1_a_RW);
static U1   u1_s_Nvmc_WriteMain(const U2 u2_a_NVMCID, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE);
static U1   u1_s_Nvmc_WriteMain_SetData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE);
static U1   u1_s_Nvmc_WriteMain_ChkData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_GetDataSts(const U2 u2_a_NVMCID)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*  Return:         U1 u1_t_ret : Status                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_GetDataSts(const U2 u2_a_NVMCID)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
    const   ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
            U2                      u2_t_no;
            U2                      u2_t_id;
            U1                      u1_t_ret;
            U1                      u1_t_device;
            U1                      u1_t_acs;
            U1                      u1_t_rimsts;

    u1_t_ret = (U1)NVMC_STATUS_NG_PRM_ID;
    u1_t_device = (U1)((u2_a_NVMCID & (U2)NVMC_ID_DEVICE_MASK) >> NVMC_ID_DEVICE_SHIFT);
    if(u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_device];
        u2_t_id = u2_a_NVMCID & (U2)NVMC_ID_DATAID_MASK;
        u1_t_acs = u1_d_Nvmc_GetDataTblNo(st_tp_DEVICE_CFG, u2_t_id, &u2_t_no);
        if(u1_t_acs == (U1)NVMC_ACS_INNVM){
            st_tp_CFGDATA = &((st_tp_DEVICE_CFG->st_p_CFGDATA)[u2_t_no]);
            u1_t_rimsts = u1_g_Rim_ReadU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, &u1_t_ret);
            if((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_NG){
                u1_t_ret = (U1)NVMC_STATUS_CACHE_NG;
                (void)u1_g_Rim_WriteU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, (U1)NVMC_STATUS_CACHE_NG);
            }
            else{
                /* In case of RIM_RESULT_KIND_NG_PRM, u1_t_ret is not updated in RIM and it's NVMC_STATUS_NG_PRM_ID. */
                /* In normal case, u1_t_ret is updated in RIM */
            }
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_WriteU1(const U2 u2_a_NVMCID, const U1 u1_a_DATA)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> u1_a_DATA   : Write Data                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_WriteU1(const U2 u2_a_NVMCID, const U1 u1_a_DATA)
{
    U4  u4_t_wr_data;

    u4_t_wr_data = (U4)u1_a_DATA;
    (void)u1_s_Nvmc_WriteMain(u2_a_NVMCID, &u4_t_wr_data, (U2)NVMC_SIZE_1BYTE);
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_WriteU2(const U2 u2_a_NVMCID, const U2 u2_a_DATA)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> u2_a_DATA   : Write Data                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_WriteU2(const U2 u2_a_NVMCID, const U2 u2_a_DATA)
{
    U4  u4_t_wr_data;

    u4_t_wr_data = (U4)u2_a_DATA;
    (void)u1_s_Nvmc_WriteMain(u2_a_NVMCID, &u4_t_wr_data, (U2)NVMC_SIZE_2BYTE);
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_WriteU4(const U2 u2_a_NVMCID, const U4 u4_a_DATA)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> u4_a_DATA   : Write Data                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_WriteU4(const U2 u2_a_NVMCID, const U4 u4_a_DATA)
{
    U4  u4_t_wr_data;

    u4_t_wr_data = u4_a_DATA;
    (void)u1_s_Nvmc_WriteMain(u2_a_NVMCID, &u4_t_wr_data, (U2)NVMC_SIZE_4BYTE);
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_WriteOthr(const U2 u2_a_NVMCID, const U2 u2_a_SIZE, const U1 * const u1_ap_DATA)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> u2_a_SIZE   : Size                                                                                           */
/*                  --> *u1_ap_DATA : Write Data Pointer                                                                             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_WriteOthr(const U2 u2_a_NVMCID, const U2 u2_a_SIZE, const U1 * const u1_ap_DATA)
{
    if(u1_ap_DATA != vdp_PTR_NA){
        /* Expected pointer cast for commonization. */
        /* Pointer data will be access after converted to U1 pointer type. */
        (void)u1_s_Nvmc_WriteMain(u2_a_NVMCID, (const U4 *)u1_ap_DATA, u2_a_SIZE);      /* QAC : Intentional pointer cast */
    }
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_ReadU1withSts(const U2 u2_a_NVMCID, U1 *u1_ap_data)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> *u1_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_ReadU1withSts(const U2 u2_a_NVMCID, U1 *u1_ap_data)
{
    U1  u1_t_ret;
    U4  u4_t_data;

    if(u1_ap_data == vdp_PTR_NA){
        u1_t_ret = (U1)NVMC_STATUS_NG_PRM_DATA_P;
    }
    else{
        u4_t_data = (U4)0U;
        u1_t_ret = u1_s_Nvmc_ReadMain(u2_a_NVMCID, &u4_t_data, (U2)NVMC_SIZE_1BYTE, (U1)NVMC_READ_RDATA);
        if((u1_t_ret & (U1)NVMC_STATUS_KIND_MASK) == (U1)NVMC_STATUS_KIND_OK){
            *u1_ap_data = (U1)u4_t_data;
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_ReadU2withSts(const U2 u2_a_NVMCID, U2 *u2_ap_data)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> *u2_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_ReadU2withSts(const U2 u2_a_NVMCID, U2 *u2_ap_data)
{
    U1  u1_t_ret;
    U4  u4_t_data;

    if(u2_ap_data == vdp_PTR_NA){
        u1_t_ret = (U1)NVMC_STATUS_NG_PRM_DATA_P;
    }
    else{
        u4_t_data = (U4)0U;
        u1_t_ret = u1_s_Nvmc_ReadMain(u2_a_NVMCID, &u4_t_data, (U2)NVMC_SIZE_2BYTE, (U1)NVMC_READ_RDATA);
        if((u1_t_ret & (U1)NVMC_STATUS_KIND_MASK) == (U1)NVMC_STATUS_KIND_OK){
            *u2_ap_data = (U2)u4_t_data;
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_ReadU4withSts(const U2 u2_a_NVMCID, U4 *u4_ap_data)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> *u4_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_ReadU4withSts(const U2 u2_a_NVMCID, U4 *u4_ap_data)
{
    U1  u1_t_ret;
    U4  u4_t_data;

    if(u4_ap_data == vdp_PTR_NA){
        u1_t_ret = (U1)NVMC_STATUS_NG_PRM_DATA_P;
    }
    else{
        u4_t_data = (U4)0U;
        u1_t_ret = u1_s_Nvmc_ReadMain(u2_a_NVMCID, &u4_t_data, (U2)NVMC_SIZE_4BYTE, (U1)NVMC_READ_RDATA);
        if((u1_t_ret & (U1)NVMC_STATUS_KIND_MASK) == (U1)NVMC_STATUS_KIND_OK){
            *u4_ap_data = u4_t_data;
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_ReadOthrwithSts(const U2 u2_a_NVMCID, const U2 u2_a_SIZE, U1 *u1_ap_data)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> u2_a_SIZE   : Size                                                                                           */
/*                  --> *u1_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_ReadOthrwithSts(const U2 u2_a_NVMCID, const U2 u2_a_SIZE, U1 *u1_ap_data)
{
    U1  u1_t_ret;

    if(u1_ap_data == vdp_PTR_NA){
        u1_t_ret = (U1)NVMC_STATUS_NG_PRM_DATA_P;
    }
    else{
        /* Expected pointer cast for commonization. */
        /* Pointer data will be access after converted to U1 pointer type. */
        u1_t_ret = u1_s_Nvmc_ReadMain(u2_a_NVMCID, (U4 *)u1_ap_data, u2_a_SIZE, (U1)NVMC_READ_RDATA);       /* QAC : Intentional pointer cast */
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_ReadStrValU1withSts(const U2 u2_a_NVMCID, U1 *u1_ap_data)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> *u1_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_ReadStrValU1withSts(const U2 u2_a_NVMCID, U1 *u1_ap_data)
{
    U1  u1_t_ret;
    U4  u4_t_data;

    if(u1_ap_data == vdp_PTR_NA){
        u1_t_ret = (U1)NVMC_STATUS_NG_PRM_DATA_P;
    }
    else{
        u4_t_data = (U4)0U;
        u1_t_ret = u1_s_Nvmc_ReadMain(u2_a_NVMCID, &u4_t_data, (U2)NVMC_SIZE_1BYTE, (U1)NVMC_READ_WDATA);
        if((u1_t_ret & (U1)NVMC_STATUS_KIND_MASK) == (U1)NVMC_STATUS_KIND_OK){
            *u1_ap_data = (U1)u4_t_data;
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_ReadStrValU2withSts(const U2 u2_a_NVMCID, U2 *u2_ap_data)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> *u2_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_ReadStrValU2withSts(const U2 u2_a_NVMCID, U2 *u2_ap_data)
{
    U1  u1_t_ret;
    U4  u4_t_data;

    if(u2_ap_data == vdp_PTR_NA){
        u1_t_ret = (U1)NVMC_STATUS_NG_PRM_DATA_P;
    }
    else{
        u4_t_data = (U4)0U;
        u1_t_ret = u1_s_Nvmc_ReadMain(u2_a_NVMCID, &u4_t_data, (U2)NVMC_SIZE_2BYTE, (U1)NVMC_READ_WDATA);
        if((u1_t_ret & (U1)NVMC_STATUS_KIND_MASK) == (U1)NVMC_STATUS_KIND_OK){
            *u2_ap_data = (U2)u4_t_data;
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_ReadStrValU4withSts(const U2 u2_a_NVMCID, U4 *u4_ap_data)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> *u4_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_ReadStrValU4withSts(const U2 u2_a_NVMCID, U4 *u4_ap_data)
{
    U4  u4_t_data;
    U1  u1_t_ret;

    if(u4_ap_data == vdp_PTR_NA){
        u1_t_ret = (U1)NVMC_STATUS_NG_PRM_DATA_P;
    }
    else{
        u4_t_data = (U4)0U;
        u1_t_ret = u1_s_Nvmc_ReadMain(u2_a_NVMCID, &u4_t_data, (U2)NVMC_SIZE_4BYTE, (U1)NVMC_READ_WDATA);
        if((u1_t_ret & (U1)NVMC_STATUS_KIND_MASK) == (U1)NVMC_STATUS_KIND_OK){
            *u4_ap_data = u4_t_data;
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_ReadStrValOthrwithSts(const U2 u2_a_NVMCID, const U2 u2_a_SIZE, U1 *u1_ap_data)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> u2_a_SIZE   : Size                                                                                           */
/*                  --> *u1_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_ReadStrValOthrwithSts(const U2 u2_a_NVMCID, const U2 u2_a_SIZE, U1 *u1_ap_data)
{
    U1  u1_t_ret;

    if(u1_ap_data == vdp_PTR_NA){
        u1_t_ret = (U1)NVMC_STATUS_NG_PRM_DATA_P;
    }
    else{
        /* Expected pointer cast for commonization. */
        /* Pointer data will be access after converted to U1 pointer type. */
        u1_t_ret = u1_s_Nvmc_ReadMain(u2_a_NVMCID, (U4 *)u1_ap_data, u2_a_SIZE, (U1)NVMC_READ_WDATA);       /* QAC : Intentional pointer cast */
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_SyncData(const U2 u2_a_NVMCID)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_SyncData(const U2 u2_a_NVMCID)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
    const   ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
            U2                      u2_t_data_id;
            U2                      u2_t_cache_id;
            U2                      u2_t_rimid;
            U2                      u2_t_req_id;
            U1                      u1_t_ret;
            U1                      u1_t_device;
            U1                      u1_t_acs_type;
            U1                      u1_t_data_sts;
            U1                      u1_t_rimsts;
            U1                      u1_t_chkid;
            U1                      u1_t_req;

    u1_t_ret = (U1)NVMC_STATUS_NG_PRM_ID;
    u1_t_device = (U1)((u2_a_NVMCID & (U2)NVMC_ID_DEVICE_MASK) >> NVMC_ID_DEVICE_SHIFT);
    if(u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_device];
        u2_t_data_id = u2_a_NVMCID & (U2)NVMC_ID_DATAID_MASK;
        u1_t_acs_type = u1_d_Nvmc_GetDataTblNo(st_tp_DEVICE_CFG, u2_t_data_id, &u2_t_cache_id);
        if(u1_t_acs_type == (U1)NVMC_ACS_INNVM){
            st_tp_CFGDATA = &((st_tp_DEVICE_CFG->st_p_CFGDATA)[u2_t_cache_id]);
            u2_t_rimid = st_tp_CFGDATA->u2_rimid_nvmsts;
            u1_t_data_sts = (U1)NVMC_STATUS_CACHE_NG;
            u1_t_rimsts = u1_g_Rim_ReadU1withStatus(u2_t_rimid, &u1_t_data_sts);
            if((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_NG_PRM){
                /* Parameter error */
                /* u1_t_ret = (U1)NVMC_STATUS_NG_PRM_ID; */
            }
            else{
                u1_t_chkid = (U1)FALSE;

                if(u1_t_data_sts == (U1)NVMC_STATUS_READING){
                    /* No need to update status */
                }
                else if(u1_t_data_sts == (U1)NVMC_STATUS_WRITING){
                    u1_t_req = u1_d_Nvmc_GetAcsReqSub(st_tp_DEVICE_CFG, u2_t_data_id);
                    if(u1_t_req != (U1)TRUE){
                        u1_t_data_sts = (U1)NVMC_STATUS_READING;
                        (void)u1_g_Rim_WriteU1withStatus(u2_t_rimid, u1_t_data_sts);
                        u1_t_chkid = (U1)TRUE;
                    }
                }
                else{
                    u1_t_data_sts = (U1)NVMC_STATUS_READING;
                    (void)u1_g_Rim_WriteU1withStatus(u2_t_rimid, u1_t_data_sts);
                    u1_t_chkid = (U1)TRUE;
                }
                vd_d_Nvmc_SetAcsReqSub(st_tp_DEVICE_CFG, u2_t_data_id, (U1)TRUE);

                if(u1_t_chkid == (U1)TRUE){
                    u2_t_req_id = u2_t_data_id;
                    (void)u1_g_Rim_ReadU2withStatus(st_tp_DEVICE_CFG->u2_rimid_initid, &u2_t_req_id);
                    if(u2_t_req_id == u2_t_data_id){
                        (void)u1_g_Rim_WriteU2withStatus(st_tp_DEVICE_CFG->u2_rimid_initid, (U2)NVMC_REQID_TASK_IDLE);
                    }
                }

                u1_t_ret = u1_t_data_sts;
            }
        }
    }
    return(u1_t_ret);
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
/*  static U1   u1_s_Nvmc_ReadMain(const U2 u2_a_NVMCID, U4 * u4_ap_data, const U2 u2_a_SIZE, const U1 u1_a_RW)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> *u4_ap_data : Data Pointer                                                                                   */
/*                  --> u2_a_SIZE   : RimSize                                                                                        */
/*                  --> u1_a_RW     : Read data or Write Data                                                                        */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_ReadMain(const U2 u2_a_NVMCID, U4 * u4_ap_data, const U2 u2_a_SIZE, const U1 u1_a_RW)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
    const   ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
            U2                      u2_t_id;
            U2                      u2_t_no;
            U2                      u2_t_req_id;
            U1                      u1_t_ret;
            U1                      u1_t_device;
            U1                      u1_t_acs;

    u1_t_ret = (U1)NVMC_STATUS_NG_PRM_ID;
    u1_t_device = (U1)((u2_a_NVMCID & (U2)NVMC_ID_DEVICE_MASK) >> NVMC_ID_DEVICE_SHIFT);
    if(u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_device];
        u2_t_id = u2_a_NVMCID & (U2)NVMC_ID_DATAID_MASK;
        u1_t_acs = u1_d_Nvmc_GetDataTblNo(st_tp_DEVICE_CFG, u2_t_id, &u2_t_no);
        if(u1_t_acs == (U1)NVMC_ACS_INNVM){
            st_tp_CFGDATA = &((st_tp_DEVICE_CFG->st_p_CFGDATA)[u2_t_no]);
            u1_t_ret = u1_s_Nvmc_ReadMain_GetData(st_tp_CFGDATA, u4_ap_data, u2_a_SIZE, u1_a_RW);
            if(u1_t_ret == (U1)NVMC_STATUS_CACHE_NG){
                if((st_tp_CFGDATA->u1_mgr_bit_cfg & (U1)NVMC_SETT_CMN_ERR_SYNC_MASK) != (U1)0U){
                    (void)u1_g_Rim_WriteU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, (U1)NVMC_STATUS_READING);
                    vd_d_Nvmc_SetAcsReqSub(st_tp_DEVICE_CFG, u2_t_id, (U1)TRUE);

                    u2_t_req_id = u2_t_id;
                    (void)u1_g_Rim_ReadU2withStatus(st_tp_DEVICE_CFG->u2_rimid_initid, &u2_t_req_id);
                    if(u2_t_req_id == u2_t_id){
                        (void)u1_g_Rim_WriteU2withStatus(st_tp_DEVICE_CFG->u2_rimid_initid, (U2)NVMC_REQID_TASK_IDLE);
                    }
                }
                else{
                    (void)u1_g_Rim_WriteU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, (U1)NVMC_STATUS_CACHE_NG);
                }
            }
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_ReadMain_GetData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA,                                              */
/*                                         U4 * u4_ap_data,                                                                          */
/*                                         const U2 u2_a_SIZE, const U1 u1_a_RW)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : CFG DATA                                                                                    */
/*                  --> *u4_ap_data    : Data Pointer                                                                                */
/*                  --> u2_a_SIZE      : RimSize                                                                                     */
/*                  --> u1_a_RW        : Read data or Write Data                                                                     */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_ReadMain_GetData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA,
                                       U4 * u4_ap_data,
                                       const U2 u2_a_SIZE, const U1 u1_a_RW)
{
    U2  u2_t_cache_id;
    U2  u2_t_offset;

    U1  u1_t_rim_chk;
    U1  u1_t_nvmc_st;

    u1_t_nvmc_st = (U1)NVMC_STATUS_CACHE_NG;
    u1_t_rim_chk = u1_g_Rim_ReadU1withStatus(st_ap_CFGDATA->u2_rimid_nvmsts, &u1_t_nvmc_st);
    if((st_ap_CFGDATA->u1_map >= u1_d_NVMC_MODULE_NUM      ) ||
       (u1_t_rim_chk          >= (U1)RIM_RESULT_KIND_NG_PRM)){   /* #define RIM_RESULT_KIND_NG_PRM (0x20U) */

        u1_t_nvmc_st = (U1)NVMC_STATUS_NG_PRM_ID;
    }
    else{

        if(u1_a_RW == (U1)NVMC_READ_RDATA){

            u2_t_offset   = (U2)st_ap_CFGDATA->u1_mgr_bit_cfg & (U2)NVMC_SETT_CMN_READID_MASK;
            u2_t_cache_id = st_ap_CFGDATA->u2_rimid_wdata + u2_t_offset;
        }
        else{

            u2_t_offset   = (U2)0U;
            u2_t_cache_id = st_ap_CFGDATA->u2_rimid_wdata;
        }

        u1_t_rim_chk = u1_d_Nvmc_GetRimData(u2_t_cache_id, u4_ap_data, u2_a_SIZE);
        if(u1_t_rim_chk == (U1)RIM_RESULT_NG_PRM_SIZE){          /* #define RIM_RESULT_NG_PRM_SIZE (0x22U) */
            u1_t_nvmc_st = (U1)NVMC_STATUS_NG_PRM_SIZE;          /* Size error                             */
        }
        else if(u1_t_rim_chk >= (U1)RIM_RESULT_KIND_NG_PRM){     /* #define RIM_RESULT_KIND_NG_PRM (0x20U) */
            u1_t_nvmc_st = (U1)NVMC_STATUS_NG_PRM_ID;            /* This is call parameter error case. */
        }
        else if(u1_t_rim_chk >= (U1)RIM_RESULT_KIND_NG){         /* #define RIM_RESULT_KIND_NG_PRM (0x10U) */

            vd_d_Nvmc_DCK_SetDefaultData(st_ap_CFGDATA, u4_ap_data, (U1)u2_a_SIZE);

            if(u1_t_nvmc_st == (U1)NVMC_STATUS_READING){
                /* return u1_t_nvmc_st as it is */
            }
            else if((u1_t_nvmc_st == (U1)NVMC_STATUS_WRITING) &&
                    (u2_t_offset  != (U2)0U                 )){  /* && (u1_a_RW == (U1)NVMC_READ_RDATA)    */
                /* return u1_t_nvmc_st as it is */
            }
            else{
                u1_t_nvmc_st = (U1)NVMC_STATUS_CACHE_NG;
            }
        }
        else if(u1_t_nvmc_st > (U1)NVMC_STATUS_MAX){
            u1_t_nvmc_st = (U1)NVMC_STATUS_CACHE_NG;
        }
        else{
            /* return u1_t_nvmc_st as it is */
        }
    }

    return(u1_t_nvmc_st);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_WriteMain(const U2 u2_a_NVMCID, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NVMCID : NvmcId                                                                                         */
/*                  --> *u4_ap_DATA : Data Pointer                                                                                   */
/*                  --> u2_a_SIZE   : RimSize                                                                                        */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_WriteMain(const U2 u2_a_NVMCID, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
    const   ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
            U2                      u2_t_id;
            U2                      u2_t_no;
            U2                      u2_t_req_id;
            U1                      u1_t_ret;
            U1                      u1_t_device;
            U1                      u1_t_acs;

    u1_t_ret = (U1)NVMC_STATUS_NG_PRM_ID;
    u1_t_device = (U1)((u2_a_NVMCID & (U2)NVMC_ID_DEVICE_MASK) >> NVMC_ID_DEVICE_SHIFT);
    if(u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_device];
        u2_t_id = u2_a_NVMCID & (U2)NVMC_ID_DATAID_MASK;
        u1_t_acs = u1_d_Nvmc_GetDataTblNo(st_tp_DEVICE_CFG, u2_t_id, &u2_t_no);
        if(u1_t_acs == (U1)NVMC_ACS_INNVM){
            st_tp_CFGDATA = &((st_tp_DEVICE_CFG->st_p_CFGDATA)[u2_t_no]);
            u1_t_ret = u1_s_Nvmc_WriteMain_SetData(st_tp_CFGDATA, u4_ap_DATA, u2_a_SIZE);
            if(u1_t_ret == (U1)NVMC_STATUS_WRITING){
                vd_d_Nvmc_SetAcsReqSub(st_tp_DEVICE_CFG, u2_t_id, (U1)TRUE);
                /* Clear write sequence parameter. */
                vd_d_Nvmc_InitNvmWriteSts(st_tp_DEVICE_CFG, u2_t_no);

                u2_t_req_id = u2_t_id;
                (void)u1_g_Rim_ReadU2withStatus(st_tp_DEVICE_CFG->u2_rimid_initid, &u2_t_req_id);
                if(u2_t_req_id == u2_t_id){
                    (void)u1_g_Rim_WriteU2withStatus(st_tp_DEVICE_CFG->u2_rimid_initid, (U2)NVMC_REQID_TASK_IDLE);
                }
            }
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_WriteMain_SetData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : CFG DATA                                                                                    */
/*                  --> *u4_ap_DATA    : Data Pointer                                                                                */
/*                  --> u2_a_SIZE      : RimSize                                                                                     */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_WriteMain_SetData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE)
{
            U1                      u1_t_rimrslt_sts;
            U1                      u1_t_rimrslt_dat;
            U1                      u1_t_ret;

    u1_t_ret = u1_s_Nvmc_WriteMain_ChkData(st_ap_CFGDATA, u4_ap_DATA, u2_a_SIZE);
    if(u1_t_ret == (U1)NVMC_STATUS_COMP){
        u1_t_ret = (U1)NVMC_STATUS_NG_PRM_ID;

        /* Update data status to writing state. */
        u1_t_rimrslt_sts = u1_g_Rim_WriteU1withStatus(st_ap_CFGDATA->u2_rimid_nvmsts, (U1)NVMC_STATUS_WRITING);
        if((u1_t_rimrslt_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            u1_t_rimrslt_dat = u1_d_Nvmc_SetRimData(st_ap_CFGDATA->u2_rimid_wdata, u4_ap_DATA, u2_a_SIZE);
            if((u1_t_rimrslt_dat & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
                u1_t_ret = (U1)NVMC_STATUS_WRITING;
            }
            else {
                (void)u1_g_Rim_WriteU1withStatus(st_ap_CFGDATA->u2_rimid_nvmsts, (U1)NVMC_STATUS_CACHE_NG);
                if(u1_t_rimrslt_dat == (U1)RIM_RESULT_NG_PRM_SIZE){
                    /* Size error */
                    u1_t_ret = (U1)NVMC_STATUS_NG_PRM_SIZE;
                }
                else if((u1_t_rimrslt_dat & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_NG_PRM){
                    /* Parameter error */
                    /* u1_t_ret = (U1)NVMC_STATUS_NG_PRM_ID; */
                }
                else{
                    /* RIM fail */
                    u1_t_ret = (U1)NVMC_STATUS_NG;
                }
            }
        }
        else if((u1_t_rimrslt_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_NG_PRM){
            /* Parameter error. Could be configuration error */
            /* u1_t_ret = (U1)NVMC_STATUS_NG_PRM_ID; */
        }
        else{
            /* RIM fail */
            u1_t_ret = (U1)NVMC_STATUS_NG;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_WriteMain_ChkData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : CFG DATA                                                                                    */
/*                  --> *u4_ap_DATA    : Data Pointer                                                                                */
/*                  --> u2_a_SIZE      : RimSize                                                                                     */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_WriteMain_ChkData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE)
{
    const   ST_NVMC_MODULE_CFG  *   st_tp_MODULE_CFG;
            U1                      u1_t_range_ok;
            U1                      u1_t_map_ptrn;
            U1                      u1_t_ret;

    u1_t_ret = (U1)NVMC_STATUS_NG_PRM_ID;

    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    if(u1_t_map_ptrn < u1_d_NVMC_MODULE_NUM){
        st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
        if(
            (st_tp_MODULE_CFG->fp_p_vd_GetRdnWrite                             != vdp_PTR_NA) &&
            ((st_ap_CFGDATA->u1_mgr_bit_cfg & (U1)NVMC_SETT_CMN_READONLY_MASK) == (U1)0     )
        ){
            if(u2_a_SIZE != (U2)(st_tp_MODULE_CFG->u1_datasize)){
                /* Size error */
                u1_t_ret = (U1)NVMC_STATUS_NG_PRM_SIZE;
            }
            else{
                u1_t_range_ok = u1_d_Nvmc_DCK_ChkDataRange(st_ap_CFGDATA, u4_ap_DATA, st_tp_MODULE_CFG->u1_datasize);
                if(u1_t_range_ok == (U1)TRUE){
                    /* chk complete */
                    u1_t_ret = (U1)NVMC_STATUS_COMP;
                }
                else{
                    /* Range error */
                    u1_t_ret = (U1)NVMC_STATUS_NG_PRM_DATA;
                }
            }
        }
        else{
            /* u1_t_ret = (U1)NVMC_STATUS_NG_PRM_ID; */
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           12/16/2015   KM      New.                                                                                        */
/*  1.0.1            1/ 8/2016   KM      Update u1_s_Nvmc_ReadMain_GetData for readability.                                          */
/*                                       vd_d_Nvmc_DCK_SetErrData() name was changed to vd_d_Nvmc_DCK_SetDefaultData().              */
/*  1.0.2            1/13/2016   KM      Update u1_s_Nvmc_ReadMain_GetData for readability.                                          */
/*  1.0.3            2/ 1/2016   KM      Fixed Unit Test issue.                                                                      */
/*  1.0.4            2/23/2016   KM      Deleted NVMC_MOD_ATTR_READONLY_BIT.                                                         */
/*  1.0.5            3/25/2016   KM      Fixed Unit Test issue.                                                                      */
/*  1.0.6            4/11/2016   HK      Fixed function comments.                                                                    */
/*  1.0.7            4/22/2016   KM      Fixed u1_s_Nvmc_WriteMain_SetData and Added u1_s_Nvmc_WriteMain_ChkData.                    */
/*  1.0.8            5/30/2016   KM      Fixed a case running ID the same as the request ID.                                         */
/*  1.1.0            11/3/2016   HK      Changed with the small sector correspondence.                                               */
/*  1.1.1            8/22/2016   HK      Fixed AIP3GBSW-146 issue.                                                                   */
/*  1.1.2            9/14/2021   TN      NULL -> vdp_PTR_NA.                                                                         */
/*  1.2.0           10/ 5/2021   TN      QAC warning#2996 was fixed. u1_s_Nvmc_ReadMain_GetData was optimized.                       */
/*  1.2.1           11/ 8/2023   KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                            */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
