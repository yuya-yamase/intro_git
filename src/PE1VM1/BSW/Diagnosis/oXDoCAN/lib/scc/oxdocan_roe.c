/* 1.0.2 */
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
#define OXDOCAN_ROE_C_PATCH                     (2U)

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
#define OXDC_ROE_NVM_BLK_SIZE                   (32U)   /* NVMC Data size = DTF Block size = 32byte    */
#define OXDC_ROE_NVM_DATA_SIZE                  (31U)   /* size of Dcm_Dsp_SID86_StorageEventLogicType */
#define OXDC_ROE_DID_READ_NB_MAX                (4U)

#define OXDC_ROE_STSBIT_TIM_START               (0x01U)
#define OXDC_ROE_STSBIT_PRE_READ                (0x02U)
#define OXDC_ROE_STSBIT_MASK_PRE_READ           (U1_MAX ^ OXDC_ROE_STSBIT_PRE_READ)

#define OXDC_ROE_IGTIM_MAX                      (0xFFFEU)

#define OXDC_ROE_DID_DATA_IDX_4TH               (0U)
#define OXDC_ROE_DID_DATA_IDX_3RD               (1U)
#define OXDC_ROE_DID_DATA_IDX_2ND               (2U)
#define OXDC_ROE_DID_DATA_IDX_1ST               (3U)
#define OXDC_ROE_DID_DATA_LSB_4TH               (24U)
#define OXDC_ROE_DID_DATA_LSB_3RD               (16U)
#define OXDC_ROE_DID_DATA_LSB_2ND               (8U)
/*#define OXDC_ROE_DID_DATA_LSB_1ST               (0U)*/

#define OXDC_ROE_DID_LEN                        (2U)
#define OXDC_ROE_DID_HI                         (0U)
#define OXDC_ROE_DID_LO                         (1U)
#define OXDC_ROE_LSB_DID_HI                     (8U)

#define OXDC_ROE_SF03REQ_IDX_RES_DID            (5U)

#define OXDC_DTF_SIZE_ROE                      (32U)
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
static void    vd_s_oXdcRoeEvReqCtrl(const U1 u1_a_ROE_EV_ID, const U1 u1_a_ROE_STS, const U1 u1_a_CUR_SES);
static U1      u1_s_oXdcRoeChkScheRate(const U1 u1_a_ROE_EV_ID);
static U1      u1_s_oXdcRoeChkDidEnable(const U1 u1_a_ROE_EV_ID, const U2 u2_a_DID_IDX, const U1 u1_a_CUR_SES);
static void    vd_s_oXdcRoeReqDidChgEv(const U1 u1_a_ROE_EV_ID, const U2 u2_a_DID_IDX, const U1 u1_a_ROE_STS);
static U1      u1_s_oXdcRoeMemcmp(const U1* u1_ap_DATA1, const U1* u1_ap_DATA2, const U4 u4_a_SIZE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1               u1_gp_TYDC_DTF_INIT_ROE[OXDC_DTF_SIZE_ROE] = {
    (U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,
    (U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0x00U,(U1)0xFFU,(U1)0x00U,(U1)0xFFU
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRoePreInitChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRoePreInit(const U1 u1_a_BON_INIT)
{
    const   Dcm_Dsp_SID86_StorageEventLogicType    st_t_INITDATA = {
        (U2)U2_MAX,     /* uint16  u2ConnectionId                   */
        (U2)U2_MAX,     /* uint16  u2StartConnectionId              */
        {(U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U},
                        /* uint8   u1ServiceToRespondToRecord[13]   */
        {(U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U, (U1)0U},
                        /* uint8   u1EventTypeRecord[10]            */
        (U1)0U,         /* uint8   u1EventWindowTime                */
        (U1)0U,         /* uint8   u1ServiceToRespondToRecordLength */
        (U1)U1_MAX,     /* uint8   u1RcvSubFunc                     */
        (U1)0U,         /* boolean bRoeStart                        */
    };
    U1          u1_tp_src[OXDC_ROE_NVM_BLK_SIZE];
    U1*         u1_tp_dst;
    U2          u2_t_nvmc_id;
    U1          u1_t_evt_idx;
    U1          u1_t_nvmc_sts;
    U1          u1_t_sum;
    U1          u1_t_res;

    for(u1_t_evt_idx = (U1)0U; u1_t_evt_idx < u1_g_OXDC_ROE_EVENT_NUM; u1_t_evt_idx++){

        u2_t_nvmc_id  = st_gp_OXDC_ROE_DID[u1_t_evt_idx].u2_nvmc_id;
        u1_tp_dst = (U1*)&Dcm_Dsp_SID86_stStorageEventLogic[u1_t_evt_idx];

        u1_t_nvmc_sts = u1_g_Nvmc_ReadOthrwithSts(u2_t_nvmc_id, (U2)OXDC_ROE_NVM_BLK_SIZE, &u1_tp_src[0]);

        if(u1_t_nvmc_sts == (U1)NVMC_STATUS_COMP){
            vd_g_MemcpyU1(u1_tp_dst, &u1_tp_src[0], (U4)OXDC_ROE_NVM_DATA_SIZE);
        }
        else{
            vd_g_MemcpyU1(u1_tp_dst, (const U1*)&st_t_INITDATA, (U4)OXDC_ROE_NVM_DATA_SIZE);
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRoeInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRoeInit(void)
{
    vd_g_MemfillU4(&u4_gp_oxdc_roe_did_data[0],  (U4)0U,      (U4)u1_g_OXDC_ROE_EVENT_NUM);
    vd_g_MemfillU2(&u2_gp_oxdc_roe_sche_time[0], (U2)U2_MAX,  (U4)u1_g_OXDC_ROE_EVENT_NUM);
    vd_g_MemfillU1(&u1_gp_oxdc_roe_evt_sts[0],   (U1)0U,      (U4)u1_g_OXDC_ROE_EVENT_NUM);
    u2_s_oxdc_roe_task_wrapcnt = (U2)0U;
    u2_s_oxdc_roe_task_igon_cnt = (U2)U2_MAX;
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
    U1          u1_t_mode;
    U1          u1_t_sf;
    U1          u1_t_res;
    U1          u1_t_cur_ses;

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

        (void)Dcm_GetSesCtrlType(&u1_t_cur_ses);
        for(u1_t_evt_idx = (U1)0U; u1_t_evt_idx < u1_g_OXDC_ROE_EVENT_NUM; u1_t_evt_idx++){

            u1_t_res = Dcm_GetRoeEventStatus(u1_t_evt_idx, &u1_t_mode, &u1_t_sf);

            if((u1_t_res == (U1)E_OK) &&
               ((u1_t_mode == DCM_EVENT_STARTED) || (u1_t_mode == DCM_EVENT_STOPPED)) &&
               (u2_s_oxdc_roe_task_igon_cnt >= st_gp_OXDC_ROE_DID[u1_t_evt_idx].u2_read_ofst)){

                vd_s_oXdcRoeEvReqCtrl(u1_t_evt_idx, u1_t_mode, u1_t_cur_ses);
            }
            else{
                u1_gp_oxdc_roe_evt_sts[u1_t_evt_idx]   = (U1)0x00U;     /* TIM_START OFF, PRE_READ OFF */
                u2_gp_oxdc_roe_sche_time[u1_t_evt_idx] = (U2)U2_MAX;
            }
        }
    }
    else{
        if(u2_s_oxdc_roe_task_igon_cnt != (U2)U2_MAX){
            u2_s_oxdc_roe_task_igon_cnt = (U2)U2_MAX;

            vd_g_MemfillU4(&u4_gp_oxdc_roe_did_data[0],  (U4)0U,      (U4)u1_g_OXDC_ROE_EVENT_NUM);
            vd_g_MemfillU2(&u2_gp_oxdc_roe_sche_time[0], (U2)U2_MAX,  (U4)u1_g_OXDC_ROE_EVENT_NUM);
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
    if(u2_a_BID < (U2)u1_g_OXDC_ROE_EVENT_NUM){

        u1_t_mem_chk = u1_g_Nvmc_GetDataSts(st_gp_OXDC_ROE_DID[u2_a_BID].u2_nvmc_id);

        if((u1_t_mem_chk == (U1)NVMC_STATUS_COMP   ) ||
           (u1_t_mem_chk == (U1)NVMC_STATUS_READING) ||
           (u1_t_mem_chk == (U1)NVMC_STATUS_WRITING)){
            u1_t_ret = DCM_NVM_REQ_OK;
        }
        else{
            /* u1_t_mem_chk is NVMC_STATUS_ERRCOMP:     */
            /* u1_t_mem_chk is NVMC_STATUS_CACHE_NG:    */
            /* u1_t_mem_chk is NVMC_STATUS_NG:          */
            /* u1_t_mem_chk is NVMC_STATUS_NG_PRM_XXX:  */
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
    U1          u1_tp_data[OXDC_ROE_NVM_BLK_SIZE];
    U1*         u1_tp_src;
    U2          u2_t_mem_id;
    U1          u1_t_nvm_chk;
    U1          u1_t_skip;
    if(u2_a_BID < (U2)u1_g_OXDC_ROE_EVENT_NUM){
        u2_t_mem_id = st_gp_OXDC_ROE_DID[u2_a_BID].u2_nvmc_id;
        u1_t_skip = (U1)FALSE;
        u1_tp_src = (U1*)&Dcm_Dsp_SID86_stStorageEventLogic[u2_a_BID];

        u1_t_nvm_chk = u1_g_Nvmc_ReadOthrwithSts(u2_t_mem_id, (U2)OXDC_ROE_NVM_BLK_SIZE, u1_tp_data);
        if((u1_t_nvm_chk == (U1)NVMC_STATUS_COMP   ) ||
           (u1_t_nvm_chk == (U1)NVMC_STATUS_READING) ||
           (u1_t_nvm_chk == (U1)NVMC_STATUS_WRITING)){

            u1_t_skip = u1_s_oXdcRoeMemcmp(&u1_tp_data[0], (const U1*)u1_tp_src, (U4)OXDC_ROE_NVM_DATA_SIZE);
        }
        if(u1_t_skip == (U1)FALSE){
            vd_g_Nvmc_WriteOthr(u2_t_mem_id, (U2)OXDC_ROE_NVM_BLK_SIZE, (const U1*)u1_tp_src);
        }
    }
    
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfRoeChkDidSup(const uint8 *u1_ap_DID)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANAubIfRoeChkDidSup(const uint8 *u1_ap_DID)
{
    U2          u2_t_did;
    U2          u2_t_did_idx;
    U1          u1_t_ret;
    U1          u1_t_sup;

    u1_t_ret = (U1)E_NOT_OK;

    u2_t_did  = (U2)u1_ap_DID[OXDC_ROE_DID_HI] << OXDC_ROE_LSB_DID_HI;
    u2_t_did |= (U2)u1_ap_DID[OXDC_ROE_DID_LO];
    
    u2_t_did_idx = u2_g_oXDoCANXidSearchDid(u2_t_did, &st_gp_OXDC_DATA_XID[0], u2_g_OXDC_DATA_NUM_XID);

    if((u2_t_did_idx < u2_g_OXDC_DATA_NUM_XID) &&
       (st_gp_OXDC_DATA_XID_ML[u2_t_did_idx].u2_ans_nbyte <= (U2)OXDC_ROE_DID_READ_NB_MAX)){

        if(st_gp_OXDC_DATA_XID[u2_t_did_idx].fp_u1_SUP == vdp_PTR_NA){
            u1_t_ret = (U1)E_OK;
        }
        else{
            u1_t_sup = (*st_gp_OXDC_DATA_XID[u2_t_did_idx].fp_u1_SUP)();
            if(u1_t_sup < (U1)OXDC_XID_SUP_NOT){
                u1_t_ret = (U1)E_OK;
            }
        }
    }

    return (u1_t_ret);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfRoeChkServToRes(Dcm_NegativeResponseCodeType *u1_ap_ErrorCode)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANAubIfRoeChkServToRes(Dcm_NegativeResponseCodeType *u1_ap_ErrorCode)
{
    ST_OXDC_REQMSG  st_t_req;
    U4              u4_t_did_num;
    U4              u4_t_cnt;
    U4              u4_t_idx;
    U2              u2_t_did;
    U2              u2_t_did_idx;
    U1              u1_t_did_ena;
    U1              u1_t_res;

    u1_t_res = (U1)E_OK;
    vd_g_oXDoCANGetStoredReqData(&st_t_req);

/* st_t_req.u4_nbyte is confirmed to be between 5 and 18, unless the RAM is corrupted. */
    if((st_t_req.u4_nbyte <= (U4)OXDC_ROE_SF03REQ_IDX_RES_DID) ||
       (((st_t_req.u4_nbyte - (U4)OXDC_ROE_SF03REQ_IDX_RES_DID) % (U4)OXDC_ROE_DID_LEN) != (U4)0U)){

        u1_t_res         = (U1)E_NOT_OK;
        *u1_ap_ErrorCode = (U1)DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    else{
        u4_t_did_num = (st_t_req.u4_nbyte - (U4)OXDC_ROE_SF03REQ_IDX_RES_DID) / (U4)OXDC_ROE_DID_LEN;

        u4_t_idx = (U4)OXDC_ROE_SF03REQ_IDX_RES_DID;
        for(u4_t_cnt = (U4)0U; u4_t_cnt < u4_t_did_num; u4_t_cnt++){
            u2_t_did  = (U2)st_t_req.u1p_RX[u4_t_idx++] << OXDC_ROE_LSB_DID_HI;
            u2_t_did |= (U2)st_t_req.u1p_RX[u4_t_idx++];
            u2_t_did_idx = u2_g_oXDoCANXidSearchDid(u2_t_did, &st_gp_OXDC_DATA_XID[0], u2_g_OXDC_DATA_NUM_XID);

            if(u2_t_did_idx < u2_g_OXDC_DATA_NUM_XID){
                u1_t_did_ena = u1_s_oXdcRoeChkDidEnable((U1)U1_MAX, u2_t_did_idx, (U1)DCM_DEFAULT_SESSION);
                if(u1_t_did_ena == (U1)FALSE){
                    u1_t_res         = (U1)E_NOT_OK;
                    *u1_ap_ErrorCode = (U1)DCM_E_REQUESTOUTOFRANGE;
                    break;
                }
            }
            else{
                u1_t_res         = (U1)E_NOT_OK;
                *u1_ap_ErrorCode = (U1)DCM_E_REQUESTOUTOFRANGE;
                break;
            }
        }
    }

    return(u1_t_res);
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcRoeEvReqCtrl(const U1 u1_a_ROE_EV_ID, const U1 u1_a_ROE_STS, const U1 u1_a_CUR_SES)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcRoeEvReqCtrl(const U1 u1_a_ROE_EV_ID, const U1 u1_a_ROE_STS, const U1 u1_a_CUR_SES)
{
    U2          u2_t_did;
    U2          u2_t_did_idx;
    U1          u1_t_read_req;
    U1          u1_t_did_ena;

    u1_t_read_req = u1_s_oXdcRoeChkScheRate(u1_a_ROE_EV_ID);

    if(u1_t_read_req == (U1)TRUE){
        u2_t_did = st_gp_OXDC_ROE_DID[u1_a_ROE_EV_ID].u2_did;
        u2_t_did_idx = u2_g_oXDoCANXidSearchDid(u2_t_did, &st_gp_OXDC_DATA_XID[0], u2_g_OXDC_DATA_NUM_XID);

        if(u2_t_did_idx < u2_g_OXDC_DATA_NUM_XID){
            u1_t_did_ena = u1_s_oXdcRoeChkDidEnable(u1_a_ROE_EV_ID, u2_t_did_idx, u1_a_CUR_SES);

            if(u1_t_did_ena == (U1)TRUE){
                vd_s_oXdcRoeReqDidChgEv(u1_a_ROE_EV_ID, u2_t_did_idx, u1_a_ROE_STS);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRoeChkScheRate(const U1 u1_a_ROE_EV_ID)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRoeChkScheRate(const U1 u1_a_ROE_EV_ID)
{
    U2          u2_t_elpsd_sche;
    U1          u1_t_read_req;

    u1_t_read_req = (U1)FALSE;

    if((u1_gp_oxdc_roe_evt_sts[u1_a_ROE_EV_ID] & (U1)OXDC_ROE_STSBIT_TIM_START) == (U1)0x00U){
        u1_gp_oxdc_roe_evt_sts[u1_a_ROE_EV_ID]  |= (U1)OXDC_ROE_STSBIT_TIM_START;
        u2_gp_oxdc_roe_sche_time[u1_a_ROE_EV_ID] = u2_s_oxdc_roe_task_wrapcnt;
        u1_t_read_req = (U1)TRUE;
    }
    else{
        u2_t_elpsd_sche = u2_s_oxdc_roe_task_wrapcnt - u2_gp_oxdc_roe_sche_time[u1_a_ROE_EV_ID];    /* deliberate wraparound */
        if(u2_t_elpsd_sche >= u2_g_OXDC_ROE_SCHE_RATE){
            u2_gp_oxdc_roe_sche_time[u1_a_ROE_EV_ID] = u2_s_oxdc_roe_task_wrapcnt;
            u1_t_read_req = (U1)TRUE;
        }
    }

    return(u1_t_read_req);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRoeChkDidEnable(const U1 u1_a_ROE_EV_ID, const U2 u2_a_DID_IDX, const U1 u1_a_CUR_SES)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRoeChkDidEnable(const U1 u1_a_ROE_EV_ID, const U2 u2_a_DID_IDX, const U1 u1_a_CUR_SES)
{
    U2          u2_t_conf_ses;
    U1          u1_t_seschk;
    U1          u1_t_sup;
    U1          u1_t_did_ena;

    u1_t_did_ena = (U1)FALSE;

    if(st_gp_OXDC_DATA_XID[u2_a_DID_IDX].fp_u1_SUP == vdp_PTR_NA){
        u1_t_sup = (U1)OXDC_XID_SUP_PUB;
    }
    else{
        u1_t_sup = (*st_gp_OXDC_DATA_XID[u2_a_DID_IDX].fp_u1_SUP)();
    }

    if(u1_t_sup < (U1)OXDC_XID_SUP_NOT){
        u2_t_conf_ses = st_gp_OXDC_DATA_XID[u2_a_DID_IDX].u2_rd_ses;
        u1_t_seschk = u1_g_oXDoCANCfgDidSessionBitChk(u1_a_CUR_SES, u2_t_conf_ses);

        if(u1_t_seschk == (U1)E_OK){
            u1_t_did_ena = (U1)TRUE;
        }
    }
    else{
        if(u1_a_ROE_EV_ID < (U1)DCM_DSP_SID86_ROE_EVENT_NUM){
            u1_gp_oxdc_roe_evt_sts[u1_a_ROE_EV_ID] &= (U1)OXDC_ROE_STSBIT_MASK_PRE_READ;        /* PRE_READ OFF */
        }
    }

    return(u1_t_did_ena);
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcRoeReqDidChgEv(const U1 u1_a_ROE_EV_ID, const U2 u2_a_DID_IDX, const U1 u1_a_ROE_STS)                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcRoeReqDidChgEv(const U1 u1_a_ROE_EV_ID, const U2 u2_a_DID_IDX, const U1 u1_a_ROE_STS)
{
    U1          u1_t_data[OXDC_ROE_DID_READ_NB_MAX];
    U4          u4_t_data_new;
    U1          u1_t_res;

    vd_g_MemfillU1(&u1_t_data[0],  (U1)0x00U,  (U4)OXDC_ROE_DID_READ_NB_MAX);
    u1_t_res = st_gp_OXDC_DATA_CFG[u2_a_DID_IDX].fp_u1_READ(&u1_t_data[0], (U2)0U);

    if(u1_t_res == (U1)OXDC_SAL_PROC_FIN){
            
        u4_t_data_new  = (U4)((U4)u1_t_data[OXDC_ROE_DID_DATA_IDX_4TH] << OXDC_ROE_DID_DATA_LSB_4TH);
        u4_t_data_new |= (U4)((U4)u1_t_data[OXDC_ROE_DID_DATA_IDX_3RD] << OXDC_ROE_DID_DATA_LSB_3RD);
        u4_t_data_new |= (U4)((U4)u1_t_data[OXDC_ROE_DID_DATA_IDX_2ND] << OXDC_ROE_DID_DATA_LSB_2ND);
        u4_t_data_new |= (U4)u1_t_data[OXDC_ROE_DID_DATA_IDX_1ST];
    
        if(((u1_gp_oxdc_roe_evt_sts[u1_a_ROE_EV_ID] & (U1)OXDC_ROE_STSBIT_PRE_READ) != (U1)0x00U    ) &&
           (u4_gp_oxdc_roe_did_data[u1_a_ROE_EV_ID]                                 != u4_t_data_new)){
        
            if(u1_a_ROE_STS == DCM_EVENT_STARTED){
                (void)Dcm_TriggerOnEvent(u1_a_ROE_EV_ID);
            }
        }
        u1_gp_oxdc_roe_evt_sts[u1_a_ROE_EV_ID] |= (U1)OXDC_ROE_STSBIT_PRE_READ;         /* PRE_READED ON */
        u4_gp_oxdc_roe_did_data[u1_a_ROE_EV_ID] = u4_t_data_new;
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
/*  1.0.1     7/17/2024  TI       Added did support/session check.                                                                   */
/*                                Removed RIM, Changed how nvm data is read.                                                         */
/*  1.0.2     9/ 6/2024  TI       Added u1_g_oXDoCANAubIfRoeChkServToRes.                                                            */
/*                                                                                                                                   */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
