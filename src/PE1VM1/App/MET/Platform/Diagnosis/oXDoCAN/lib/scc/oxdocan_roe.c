/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  SID 0x86 Response On Event                                                                                                       */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_ROE_C_MAJOR                     (1U)
#define OXDOCAN_ROE_C_MINOR                     (0U)
#define OXDOCAN_ROE_C_PATCH                     (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "oxdocan_xid_cfg_private.h"
#include "oxdocan_roe_cfg_private.h"

#include "oxdocan_aubif.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXDOCAN_ROE_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "oxdocan_roe.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((OXDOCAN_ROE_C_MAJOR != OXDOCAN_ROE_CFG_H_MAJOR) || \
     (OXDOCAN_ROE_C_MINOR != OXDOCAN_ROE_CFG_H_MINOR) || \
     (OXDOCAN_ROE_C_PATCH != OXDOCAN_ROE_CFG_H_PATCH))
#error "oxdocan_roe.c and oxdocan_roe_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_ROE_MEM_BLK_SIZE                   (32U)
#define OXDC_ROE_DID_READ_NB_MAX                (4U)

#define OXDC_ROE_STSBIT_PRE_READ                (0x01U)
#define OXDC_ROE_STSBIT_READ_REQ                (0x02U)

#define OXDC_ROE_IGTIM_MAX                      (0xFFFEU)

#define OXDC_ROE_DID_DATA_IDX_4TH               (0U)
#define OXDC_ROE_DID_DATA_IDX_3RD               (1U)
#define OXDC_ROE_DID_DATA_IDX_2ND               (2U)
#define OXDC_ROE_DID_DATA_IDX_1ST               (3U)
#define OXDC_ROE_DID_DATA_LSB_4TH               (24U)
#define OXDC_ROE_DID_DATA_LSB_3RD               (16U)
#define OXDC_ROE_DID_DATA_LSB_2ND               (8U)
#define OXDC_ROE_DID_DATA_LSB_1ST               (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U2          u2_s_oxdc_roe_task_wrapcnt;
static  U2          u2_s_oxdc_roe_task_igon_cnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_oXdcRoeMemRead(const U1 u1_a_BR_INIT);
static void    vd_s_oXdcRoeChkScheRate(const U1 u1_a_ROE_EV_ID);
static void    vd_s_oXdcRoeChkDidChgEv(const U1 u1_a_ROE_EV_ID);
static void    vd_s_oXdcRoeEvReq(const U1 u1_a_ROE_EV_ID);
static U1      u1_s_oXdcRoeMemcmp(const U1* u1_ap_DATA1, const U1* u1_ap_DATA2, const U4 u4_a_SIZE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRoeInit(const U1 u1_a_BR_INIT)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRoeInit(const U1 u1_a_BR_INIT)
{
    vd_g_MemfillU4(&u4_gp_oxdc_roe_did_data[0],  (U4)0U,      (U4)u1_g_OXDC_ROE_EVENT_NUM);
    vd_g_MemfillU2(&u2_gp_oxdc_roe_sche_time[0], (U2)0xFFFFU, (U4)u1_g_OXDC_ROE_EVENT_NUM);
    vd_g_MemfillU1(&u1_gp_oxdc_roe_evt_sts[0],   (U1)0U,      (U4)u1_g_OXDC_ROE_EVENT_NUM);
    u2_s_oxdc_roe_task_wrapcnt = (U2)0U;
    u2_s_oxdc_roe_task_igon_cnt = (U2)U2_MAX;

    vd_s_oXdcRoeMemRead(u1_a_BR_INIT);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRoeMainTask(const U1 u1_a_EOM)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRoeMainTask(const U1 u1_a_EOM)
{
    U1          u1_t_evt_idx;

    if((u1_a_EOM & (U1)OXDC_EOM_IGN_ON) != (U1)0U){
        if(u2_s_oxdc_roe_task_igon_cnt < (U2)OXDC_ROE_IGTIM_MAX){
            u2_s_oxdc_roe_task_igon_cnt++;
        }
        else if(u2_s_oxdc_roe_task_igon_cnt == (U2)U2_MAX){
            u2_s_oxdc_roe_task_igon_cnt = (U2)0U;
        }
        else{
            /* Do nothing */
        }

        for(u1_t_evt_idx = (U1)0U; u1_t_evt_idx < u1_g_OXDC_ROE_EVENT_NUM; u1_t_evt_idx++){

            if(u2_s_oxdc_roe_task_igon_cnt >= st_gp_OXDC_ROE_DID[u1_t_evt_idx].u2_read_ofst){

                vd_s_oXdcRoeChkScheRate(u1_t_evt_idx);
                if((u1_gp_oxdc_roe_evt_sts[u1_t_evt_idx] & (U1)OXDC_ROE_STSBIT_READ_REQ) != (U1)0x00U){
                    vd_s_oXdcRoeChkDidChgEv(u1_t_evt_idx);
                }
            }
        }
    }
    else{
        if(u2_s_oxdc_roe_task_igon_cnt != (U2)U2_MAX){
            u2_s_oxdc_roe_task_igon_cnt = (U2)U2_MAX;

            vd_g_MemfillU4(&u4_gp_oxdc_roe_did_data[0],  (U4)0U,      (U4)u1_g_OXDC_ROE_EVENT_NUM);
            vd_g_MemfillU2(&u2_gp_oxdc_roe_sche_time[0], (U2)0xFFFFU, (U4)u1_g_OXDC_ROE_EVENT_NUM);
            vd_g_MemfillU1(&u1_gp_oxdc_roe_evt_sts[0],   (U1)0U,      (U4)u1_g_OXDC_ROE_EVENT_NUM);            
        }
    }

    u2_s_oxdc_roe_task_wrapcnt++;       /* deliberate wraparound */
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfRoeNvmWrStat(const uint16 u2_a_BID)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANAubIfRoeNvmGetErrSt(const uint16 u2_a_BID)
{
    U1          u1_tp_data[OXDC_ROE_MEM_BLK_SIZE];
    U1          u1_t_mem_chk;
    U1          u1_t_ret;

    /* DCM_NVM_REQ_OK                */
    /* DCM_NVM_REQ_NOT_OK            */
    /* DCM_NVM_REQ_PENDING           */
    /* DCM_NVM_REQ_INTEGRITY_FAILED  */
    /* DCM_NVM_REQ_BLOCK_SKIPPED     */
    /* DCM_NVM_REQ_NV_INVALIDATED    */
    /* DCM_NVM_REQ_CANCELED          */
    /* DCM_NVM_REQ_REDUNDANCY_FAILED */
    /* DCM_NVM_REQ_RESTORED_FROM_ROM */
    u1_t_ret = DCM_NVM_REQ_NOT_OK;
    if(u2_a_BID < (U2)u1_g_OXDC_ROE_MEM_BLOCK_NUM){

        if(st_gp_OXDC_ROE_MEM_BLOCK[u2_a_BID].u2_store_evt == (U2)TRUE){
            u1_t_mem_chk = u1_g_Nvmc_GetDataSts(st_gp_OXDC_ROE_MEM_BLOCK[u2_a_BID].u2_mem_id);
            if(u1_t_mem_chk == (U1)NVMC_STATUS_COMP){
                u1_t_ret = DCM_NVM_REQ_OK;
            }
            else if((u1_t_mem_chk == (U1)NVMC_STATUS_READING) ||
                    (u1_t_mem_chk == (U1)NVMC_STATUS_WRITING)){
                u1_t_ret = DCM_NVM_REQ_PENDING;
            }
            else{
                /* u1_t_mem_chk is NVMC_STATUS_ERRCOMP:     */
                /* u1_t_mem_chk is NVMC_STATUS_CACHE_NG:    */
                /* u1_t_mem_chk is NVMC_STATUS_NG:          */
                /* u1_t_mem_chk is NVMC_STATUS_NG_PRM_XXX:  */
            }
        }
        else{
            u1_t_mem_chk = u1_g_Rim_ReadOtherwithStatus(st_gp_OXDC_ROE_MEM_BLOCK[u2_a_BID].u2_mem_id, (U2)OXDC_ROE_MEM_BLK_SIZE, &u1_tp_data[0]);
            if((u1_t_mem_chk == (U1)RIM_RESULT_OK         ) ||
               (u1_t_mem_chk == (U1)RIM_RESULT_OK_REPAIRED)){
                u1_t_ret = DCM_NVM_REQ_OK;
            }
            else{
                /* u1_t_mem_chk is RIM_RESULT_NG:       */
                /* u1_t_mem_chk is RIM_RESULT_NG_XXX:   */
            }
        }
    }

    return (u1_t_ret);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANAubIfRoeNvmWrBlock(const uint16 u2_a_BID)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANAubIfRoeNvmWrBlock(const uint16 u2_a_BID)
{
    U1          u1_tp_data[OXDC_ROE_MEM_BLK_SIZE];
    U2          u2_t_mem_id;
    U1          u1_t_nvm_chk;
    U1          u1_t_skip;

    if(u2_a_BID < (U2)u1_g_OXDC_ROE_MEM_BLOCK_NUM){
        u2_t_mem_id = st_gp_OXDC_ROE_MEM_BLOCK[u2_a_BID].u2_mem_id;
        u1_t_skip = (U1)FALSE;

        if(st_gp_OXDC_ROE_MEM_BLOCK[u2_a_BID].u2_store_evt == (U2)TRUE){
            u1_t_nvm_chk = u1_g_Nvmc_ReadOthrwithSts(u2_t_mem_id, (U2)OXDC_ROE_MEM_BLK_SIZE, u1_tp_data);
            if((u1_t_nvm_chk == NVMC_STATUS_COMP   ) ||
               (u1_t_nvm_chk == NVMC_STATUS_READING) ||
               (u1_t_nvm_chk == NVMC_STATUS_WRITING)){

                u1_t_skip = u1_s_oXdcRoeMemcmp(&u1_tp_data[0], (const U1*)&Dcm_Dsp_SID86_stStorageEventLogic[u2_a_BID], (U4)OXDC_ROE_MEM_BLK_SIZE);
            }
        }
        if(u1_t_skip == (U1)FALSE){
            if(st_gp_OXDC_ROE_MEM_BLOCK[u2_a_BID].u2_store_evt == (U2)TRUE){
                vd_g_Nvmc_WriteOthr(u2_t_mem_id, (U2)OXDC_ROE_MEM_BLK_SIZE, (const U1*)&Dcm_Dsp_SID86_stStorageEventLogic[u2_a_BID]);
            }
            else{
                vd_g_Rim_WriteOther(u2_t_mem_id, (U2)OXDC_ROE_MEM_BLK_SIZE, (const U1*)&Dcm_Dsp_SID86_stStorageEventLogic[u2_a_BID]);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcRoeMemRead(const U1 u1_a_BR_INIT)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcRoeMemRead(const U1 u1_a_BR_INIT)
{
    U1 *        u1_tp_dst;
    U2          u2_t_mem_id;
    U1          u1_t_bid;
    U1          u1_t_mem_chk;

    for(u1_t_bid = (U1)0U; u1_t_bid < u1_g_OXDC_ROE_MEM_BLOCK_NUM; u1_t_bid++){
        u1_tp_dst    = (U1*)&Dcm_Dsp_SID86_stStorageEventLogic[u1_t_bid];
        u2_t_mem_id  = st_gp_OXDC_ROE_MEM_BLOCK[u1_t_bid].u2_mem_id;
        if(st_gp_OXDC_ROE_MEM_BLOCK[u1_t_bid].u2_store_evt == (U2)TRUE){
            u1_t_mem_chk = u1_g_Nvmc_ReadOthrwithSts(u2_t_mem_id, (U2)OXDC_ROE_MEM_BLK_SIZE, u1_tp_dst);
            if((u1_t_mem_chk != (U1)NVMC_STATUS_COMP   ) &&
               (u1_t_mem_chk != (U1)NVMC_STATUS_READING) &&
               (u1_t_mem_chk != (U1)NVMC_STATUS_WRITING)){
                vd_g_MemfillU1(u1_tp_dst, (U1)0x00U, (U4)OXDC_ROE_MEM_BLK_SIZE);
                Dcm_Dsp_SID86_stStorageEventLogic[u1_t_bid].u2ConnectionId      = (uint16)0xFFFFU;
                Dcm_Dsp_SID86_stStorageEventLogic[u1_t_bid].u2StartConnectionId = (uint16)0xFFFFU;
                Dcm_Dsp_SID86_stStorageEventLogic[u1_t_bid].u1RcvSubFunc        = (uint8)0xFFU;
            }
        }
        else{
            if(u1_a_BR_INIT == (U1)TRUE){
                vd_g_MemfillU1(u1_tp_dst, (U1)0x00U, (U4)OXDC_ROE_MEM_BLK_SIZE);
                Dcm_Dsp_SID86_stStorageEventLogic[u1_t_bid].u2ConnectionId      = (uint16)0xFFFFU;
                Dcm_Dsp_SID86_stStorageEventLogic[u1_t_bid].u2StartConnectionId = (uint16)0xFFFFU;
                Dcm_Dsp_SID86_stStorageEventLogic[u1_t_bid].u1RcvSubFunc        = (uint8)0xFFU;
                vd_g_Rim_WriteOther(u2_t_mem_id, (U2)OXDC_ROE_MEM_BLK_SIZE, u1_tp_dst);
            }
            else{
                u1_t_mem_chk = u1_g_Rim_ReadOtherwithStatus(u2_t_mem_id, (U2)OXDC_ROE_MEM_BLK_SIZE, u1_tp_dst);
                if((u1_t_mem_chk != (U1)RIM_RESULT_OK         ) &&
                   (u1_t_mem_chk != (U1)RIM_RESULT_OK_REPAIRED)){
                    vd_g_MemfillU1(u1_tp_dst, (U1)0x00U, (U4)OXDC_ROE_MEM_BLK_SIZE);
                    Dcm_Dsp_SID86_stStorageEventLogic[u1_t_bid].u2ConnectionId      = (uint16)0xFFFFU;
                    Dcm_Dsp_SID86_stStorageEventLogic[u1_t_bid].u2StartConnectionId = (uint16)0xFFFFU;
                    Dcm_Dsp_SID86_stStorageEventLogic[u1_t_bid].u1RcvSubFunc        = (uint8)0xFFU;
                }
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcRoeChkScheRate(const U1 u1_a_ROE_EV_ID)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcRoeChkScheRate(const U1 u1_a_ROE_EV_ID)
{
    U2          u2_t_elpsd_sche;

    if(u1_gp_oxdc_roe_evt_sts[u1_a_ROE_EV_ID] == (U1)0x00U){
        u1_gp_oxdc_roe_evt_sts[u1_a_ROE_EV_ID]  |= (U1)OXDC_ROE_STSBIT_READ_REQ;
        u2_gp_oxdc_roe_sche_time[u1_a_ROE_EV_ID] = u2_s_oxdc_roe_task_wrapcnt;
    }
    else if((u1_gp_oxdc_roe_evt_sts[u1_a_ROE_EV_ID] & (U1)OXDC_ROE_STSBIT_READ_REQ) == (U1)0x00U){

        u2_t_elpsd_sche = u2_s_oxdc_roe_task_wrapcnt - u2_gp_oxdc_roe_sche_time[u1_a_ROE_EV_ID];    /* deliberate wraparound */

        if(u2_t_elpsd_sche >= st_gp_OXDC_ROE_DID[u1_a_ROE_EV_ID].u2_sche_rate){
            u1_gp_oxdc_roe_evt_sts[u1_a_ROE_EV_ID]  |= (U1)OXDC_ROE_STSBIT_READ_REQ;
            u2_gp_oxdc_roe_sche_time[u1_a_ROE_EV_ID] = u2_s_oxdc_roe_task_wrapcnt;
        }
    }
    else{
        /* Do nothing */
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcRoeChkDidChgEv(const U1 u1_a_ROE_EV_ID)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcRoeChkDidChgEv(const U1 u1_a_ROE_EV_ID)
{
    U1          u1_t_data[OXDC_ROE_DID_READ_NB_MAX];
    U4          u4_t_data_new;
    U2          u2_t_elpsd_read;
    U1          u1_t_res;

    if((st_gp_OXDC_ROE_DID[u1_a_ROE_EV_ID].fp_u1_READ   != vdp_PTR_NA                  ) &&
       (st_gp_OXDC_ROE_DID[u1_a_ROE_EV_ID].u2_ans_nbyte <= (U2)OXDC_ROE_DID_READ_NB_MAX)){

        vd_g_MemfillU1(&u1_t_data[0],  (U1)0x00U,  (U4)OXDC_ROE_DID_READ_NB_MAX);
        u2_t_elpsd_read = u2_s_oxdc_roe_task_wrapcnt - u2_gp_oxdc_roe_sche_time[u1_a_ROE_EV_ID];    /* deliberate wraparound */
        u1_t_res = st_gp_OXDC_ROE_DID[u1_a_ROE_EV_ID].fp_u1_READ(&u1_t_data[0], u2_t_elpsd_read);

        if(u1_t_res == (U1)OXDC_SAL_PROC_FIN){
                
            u4_t_data_new  = (U4)((U4)u1_t_data[OXDC_ROE_DID_DATA_IDX_4TH] << OXDC_ROE_DID_DATA_LSB_4TH);
            u4_t_data_new |= (U4)((U4)u1_t_data[OXDC_ROE_DID_DATA_IDX_3RD] << OXDC_ROE_DID_DATA_LSB_3RD);
            u4_t_data_new |= (U4)((U4)u1_t_data[OXDC_ROE_DID_DATA_IDX_2ND] << OXDC_ROE_DID_DATA_LSB_2ND);
            u4_t_data_new |= (U4)u1_t_data[OXDC_ROE_DID_DATA_IDX_1ST];
        
            if(((u1_gp_oxdc_roe_evt_sts[u1_a_ROE_EV_ID] & (U1)OXDC_ROE_STSBIT_PRE_READ) != (U1)0x00U    ) &&
               (u4_gp_oxdc_roe_did_data[u1_a_ROE_EV_ID]                                 != u4_t_data_new)){
               
                vd_s_oXdcRoeEvReq(u1_a_ROE_EV_ID);
            }
            u1_gp_oxdc_roe_evt_sts[u1_a_ROE_EV_ID]  = (U1)OXDC_ROE_STSBIT_PRE_READ;   /* PRE_READED ON, READING OFF */
            u4_gp_oxdc_roe_did_data[u1_a_ROE_EV_ID] = u4_t_data_new;
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcRoeEvReq(const U1 u1_a_ROE_EV_ID)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcRoeEvReq(const U1 u1_a_ROE_EV_ID)
{
    U1          u1_t_mode;
    U1          u1_t_sf;
    U1          u1_t_res;

    u1_t_res = Dcm_GetRoeEventStatus(u1_a_ROE_EV_ID, &u1_t_mode, &u1_t_sf);

    if((u1_t_res  == (U1)E_OK         ) &&
       (u1_t_mode == DCM_EVENT_STARTED)){

        (void)Dcm_TriggerOnEvent(u1_a_ROE_EV_ID);
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRoeMemcmp(const U1* u1_ap_DATA1, const U1* u1_ap_DATA2, const U4 u4_a_SIZE)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRoeMemcmp(const U1* u1_ap_DATA1, const U1* u1_ap_DATA2, const U4 u4_a_SIZE)
{
    U4          u4_t_idx;
    U1          u1_t_ret;
    U1          u1_t_data1_element;
    U1          u1_t_data2_element;
    
    u1_t_ret = (U1)TRUE;
    for(u4_t_idx = (U4)0U; u4_t_idx < u4_a_SIZE; u4_t_idx++){
        u1_t_data1_element = u1_ap_DATA1[u4_t_idx];
        u1_t_data2_element = u1_ap_DATA2[u4_t_idx];
        
        if(u1_t_data1_element != u1_t_data2_element){
            u1_t_ret = (U1)FALSE;
            break;
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
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/11/2024  TI       New.                                                                                               */
/*                                                                                                                                   */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
