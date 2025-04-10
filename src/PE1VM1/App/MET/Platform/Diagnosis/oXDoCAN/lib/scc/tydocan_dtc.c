/* 1.9.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  SID 0x14 0x19 0x85                                                                                                               */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DTC_C_MAJOR                      (1U)
#define TYDOCAN_DTC_C_MINOR                      (9U)
#define TYDOCAN_DTC_C_PATCH                      (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "tydocan_dtc_cfg_private.h"

#include "Rte_Dem.h"
#include "Dem_NvM_Connector.h"
#include "Dem_Clear_Callout.h"

#include "oxdocan_aubif.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_DTC_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_dtc.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_C_MAJOR != TYDOCAN_DTC_CFG_H_MAJOR) || \
     (TYDOCAN_DTC_C_MINOR != TYDOCAN_DTC_CFG_H_MINOR) || \
     (TYDOCAN_DTC_C_PATCH != TYDOCAN_DTC_CFG_H_PATCH))
#error "tydocan_dtc.c and tydocan_dtc_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_EVM_NUM_CTRL                    (3U)
#define TYDC_DTC_EVM_CTRL_S14                    (0U)
#define TYDC_DTC_EVM_CTRL_MSK                    (1U)
#define TYDC_DTC_EVM_CTRL_INA                    (2U)

#define TYDC_DTC_EVM_EAS_S14_RUN                 (OXDC_DTC_EVM_S14) /* 0x01U */
#define TYDC_DTC_EVM_EAS_MSK_RUN                 (OXDC_DTC_EVM_MSK) /* 0x02U */
#define TYDC_DTC_EVM_EAS_S14_ABT                 (0x04U)

#define TYDC_DTC_EVM_ACT_TO_S14                  (0U)
#define TYDC_DTC_EVM_ACT_TO_MSK                  (1U)
#define TYDC_DTC_EVM_ACT_S14_TO_INA              (2U)
#define TYDC_DTC_EVM_ACT_MSK_TO_INA              (3U)
#define TYDC_DTC_EVM_ACT_S14                     (4U)
#define TYDC_DTC_EVM_ACT_INA                     (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_TRBL_LSR_WID                    (5U)
#define TYDC_DTC_TRBL_BIT_LSB                    (0x001fU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_NVM_SIZE_U4                         (4U)
#define TYDC_NVM_IDX_P0                          (0U)
#define TYDC_NVM_IDX_P1                          (1U)
#define TYDC_NVM_IDX_P2                          (2U)
#define TYDC_NVM_IDX_P3                          (3U)
#define TYDC_NVM_U4_LSB_4TH                      (24U)
#define TYDC_NVM_U4_LSB_3RD                      (16U)
#define TYDC_NVM_U4_LSB_2ND                      (8U)
/* #define TYDC_NVM_U4_LSB_1ST                      (0U) */
#define TYDC_DTC_LSB_3RD                         (16U)
#define TYDC_DTC_LSB_2ND                         (8U)
/* #define TYDC_DTC_LSB_1ST                         (0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_A006_ANS_CNT                    (0U)
#define TYDC_DTC_A006_ANS_DTC_H                  (1U)
#define TYDC_DTC_A006_ANS_DTC_M                  (2U)
#define TYDC_DTC_A006_ANS_DTC_L                  (3U)
#define TYDC_DTC_A006_ANS_MEMSEL                 (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_NVM_BLK_MAX_SIZE                (32U)
#define TYDC_DEMEVT_IDX_STSDTC                   (1U)   /* index of StatusOfDTC in Dem_EventRecordType    */
                                                        /* index of StatusOfDTC in Dem_UdmEventRecordType */
#define TYDC_DEMEVT_MSK_STSDTC                   (DEM_DTCSTATUS_PRODUCT_SUPPORT_BIT)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXDC_MAIN_TICK  == 0U             ) || \
     (OXCAN_MAIN_TICK == 0U             ) || \
     (OXDC_MAIN_TICK  != OXCAN_MAIN_TICK))
#error "tydocan_dtc.c : OXDC_MAIN_TICK shall be equal to OXCAN_MAIN_TICK."
#endif

#if (OXDC_DTC_TR_INA != 0U)
#error "tydocan_dtc.c : OXDC_DTC_TR_INA shall be equal to 0."
#endif

#if (OXDC_DTC_TR_UNK == 0U)
#error "tydocan_dtc.c : OXDC_DTC_TR_UNK shall NOT be equal to 0."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4     u4_s_tydc_dtc_key_unlock;

static U2     u2_s_tydc_dtc_rxc_cyctim;

static U2     u2_s_tydc_dtc_evm_tocnt;
static U1     u1_s_tydc_dtc_evm_ctrl;
static U1     u1_s_tydc_dtc_evm_act;

static U1     u1_s_tydc_dtc_log_rx_idx;

static U1     u1_s_tydc_dtc_udm_ev_cnt;
static U2     u2_s_tydc_dtc_udm_last_ev_id;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void           vd_s_TydcDtcInit(void);
static U4             u4_s_TydcDtcTrblchk(const U2 u2_a_TSLOT, const U1 u1_a_EOM, const U1 u1_a_SES);
static void           vd_s_TydcDtcTrDeAct(void);
static void           vd_s_TydcDtcRxcInit(void);
static void           vd_s_TydcDtcEvmAct(const U1 u1_a_ACT);

static U4             u4_s_TydcDtcTrchk(const U2 u2_a_TSLOT, const U2 u2_a_ELPSD, const U1 u1_a_EVM);
static U4             u4_s_TydcDtcComRx(const U2 u2_a_TSLOT, const U2 u2_a_ELPSD, const U1 u1_a_EVM);
static U1             u1_s_TydcDtcPduRx(const ST_TYDC_DTC_COM_RX * st_ap_COM_RX, const U2 u2_a_ELPSD, const U1 u1_a_EVM);
static U4             u4_s_TydcDtcLogRx(void);

static U4             u4_s_TydcDtcTrPut(const U2 u2_a_ID, const U1 u1_a_CHK);
static inline U1      u1_s_TydcDtcRxTOchk(const U4 u4_a_SUP, const U4 u4_a_UNK, const U4 u4_a_RXTO);

static U1             u1_s_TydcDtcNvmcRead(const U2 u2_a_NVMCID, const U2 u2_a_size, U1 *u1_ap_data);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDtcBonInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANDtcBonInit(void)
{
    vd_s_TydcDtcInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDtcRstInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANDtcRstInit(void)
{
    vd_s_TydcDtcInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDtcWkupInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANDtcWkupInit(void)
{
    vd_s_TydcDtcInit();
}
/*===================================================================================================================================*/
/*  U4    u4_g_oXDoCANDtcMainTask(const U2 u2_a_TSLOT, const ST_OXDC_REQ * st_ap_REQ)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4    u4_g_oXDoCANDtcMainTask(const ST_OXDC_REQ * st_ap_REQ, const U2 u2_a_TSLOT)
{
    U4                         u4_t_ev_dtct;

    u4_t_ev_dtct = u4_s_TydcDtcTrblchk(u2_a_TSLOT, st_ap_REQ->u1_eom_aft, st_ap_REQ->u1_ses_aft);

    return(u4_t_ev_dtct);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfDtcNvmWrStat(const uint16 u2_a_BID)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANAubIfDtcNvmWrStat(const uint16 u2_a_BID)
{
    U1                         u1_t_nvm_chk;
    U1                         u1_t_ret;

    /* DEM_NVM_REQ_OK                */
    /* DEM_NVM_REQ_NOT_OK            */
    /* DEM_NVM_REQ_PENDING           */
    /* DEM_NVM_REQ_INTEGRITY_FAILED  */
    /* DEM_NVM_REQ_BLOCK_SKIPPED     */
    /* DEM_NVM_REQ_NV_INVALIDATED    */
    /* DEM_NVM_REQ_CANCELED          */
    /* DEM_NVM_REQ_REDUNDANCY_FAILED */
    /* DEM_NVM_REQ_RESTORED_FROM_ROM */
    u1_t_ret = DEM_NVM_REQ_NOT_OK;
    if(u2_a_BID < DEM_NVM_USE_NVBLOCK_NUM){

        u1_t_nvm_chk = u1_g_Nvmc_GetDataSts(u2_gp_TYDC_DTC_NVMC_BLOCK[u2_a_BID]);

        if(u1_t_nvm_chk == (U1)NVMC_STATUS_COMP){
            u1_t_ret = DEM_NVM_REQ_OK;
        }
        else if((u1_t_nvm_chk == (U1)NVMC_STATUS_READING) ||
                (u1_t_nvm_chk == (U1)NVMC_STATUS_WRITING)){
            u1_t_ret = DEM_NVM_REQ_PENDING;
        }
        else{
            /* u1_t_sts is NVMC_STATUS_ERRCOMP:    */
            /* u1_t_sts is NVMC_STATUS_CACHE_NG:   */
            /* u1_t_sts is NVMC_STATUS_NG:         */
            /* u1_t_sts is NVMC_STATUS_NG_PRM_XXX: */
        }
    }

    return (u1_t_ret);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANAubIfDtcNvmWrBlock(const uint16 u2_a_BID, const uint8 * u1_ap_SRC)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANAubIfDtcNvmWrBlock(const uint16 u2_a_BID, const uint8 * u1_ap_SRC)
{
    U4                         u4_t_data;
    U4                         u4_t_lpknd;
    U2                         u2_t_nvmc_id;
    U2                         u2_t_nbyte;
    U2                         u2_t_evtid;
    U2                         u2_t_rcrdid;
    U1                         u1_t_rcrdkind;
    U1                         u1_t_stsdtc;
    U1                         u1_t_chk;
    U1                         u1_t_skip;
    U1                         u1_tp_nvmdata[TYDC_DTC_NVM_BLK_MAX_SIZE];

    if(u2_a_BID < DEM_NVM_USE_NVBLOCK_NUM){
        u2_t_nbyte = (U2)0U;
        u2_t_nvmc_id = u2_gp_TYDC_DTC_NVMC_BLOCK[u2_a_BID];
        for(u4_t_lpknd = (U4)0U; u4_t_lpknd < (U4)DEM_MM_NVM_REC_KIND_NUM; u4_t_lpknd++){
            if((Dem_RecordInfo_NvBlockTable[u4_t_lpknd].DemBlockIndexFirst <= u2_a_BID) &&
               (Dem_RecordInfo_NvBlockTable[u4_t_lpknd].DemBlockIndexLast  >= u2_a_BID)){
                u2_t_nbyte   = Dem_RecordInfo_NvBlockTable[u4_t_lpknd].DemBlockSize;
                break;
            }
        }

        u2_t_rcrdid = (U2)DEM_MM_NVM_REC_KIND_NUM;
        u1_t_skip = (U1)FALSE;

        u1_t_chk  = (U1)Dem_GetRecordInfoByNvMBlockId(u2_a_BID, &u2_t_rcrdid, &u2_t_evtid);
        if(u1_t_chk == (U1)E_OK){
            u1_t_rcrdkind = u1_g_TyDoCANDtcCfgNvmKind(u2_t_rcrdid);
            if((u1_t_rcrdkind == (U1)TYDC_DTC_NVM_REC_KIND_PRIM_EVT) || (u1_t_rcrdkind == (U1)TYDC_DTC_NVM_REC_KIND_UDM_EVT)){
                u1_t_stsdtc = u1_ap_SRC[TYDC_DEMEVT_IDX_STSDTC] & (U1)TYDC_DEMEVT_MSK_STSDTC;

                u1_t_chk = u1_s_TydcDtcNvmcRead(u2_t_nvmc_id, u2_t_nbyte, u1_tp_nvmdata);
                if((u1_t_chk == (U1)NVMC_STATUS_COMP) &&
                   (u1_t_stsdtc == (u1_tp_nvmdata[TYDC_DEMEVT_IDX_STSDTC] & (U1)TYDC_DEMEVT_MSK_STSDTC))){
                    u1_t_skip = (U1)TRUE;
                }
            }
        }

        if(u1_t_skip != (U1)TRUE){
            /* 4byte alignment measures. */
            if(u2_t_nbyte == (U2)TYDC_NVM_SIZE_U4){
                u4_t_data =  (U4)((U4)u1_ap_SRC[TYDC_NVM_IDX_P0] << TYDC_NVM_U4_LSB_4TH);
                u4_t_data |= (U4)((U4)u1_ap_SRC[TYDC_NVM_IDX_P1] << TYDC_NVM_U4_LSB_3RD);
                u4_t_data |= (U4)((U4)u1_ap_SRC[TYDC_NVM_IDX_P2] << TYDC_NVM_U4_LSB_2ND);
                u4_t_data |= (U4)(u1_ap_SRC[TYDC_NVM_IDX_P3]);
                vd_g_Nvmc_WriteU4(u2_t_nvmc_id, u4_t_data);
            }
            else{
                vd_g_Nvmc_WriteOthr(u2_t_nvmc_id, u2_t_nbyte, u1_ap_SRC);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANAubIfDtcEvmAct(const uint8 u1_a_EVM)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANAubIfDtcEvmAct(const uint8 u1_a_EVM)
{
    u1_s_tydc_dtc_evm_act |= u1_a_EVM;
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANAubIfDtcEvmDeAct(const uint8 u1_a_EVM)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANAubIfDtcEvmDeAct(const uint8 u1_a_EVM)
{
    u1_s_tydc_dtc_evm_act &= ((U1)U1_MAX ^ u1_a_EVM);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcUnlock(const U4 u4_a_KEY)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcUnlock(const U4 u4_a_KEY)
{
    u4_s_tydc_dtc_key_unlock = u4_a_KEY;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcLogRxReset(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcLogRxReset(void)
{
    U4                         u4_t_lpcnt;

    if(u4_s_tydc_dtc_key_unlock == (U4)OXDC_DTC_KEY_UNLOCK){

        u1_s_tydc_dtc_log_rx_idx = (U1)U1_MAX;

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DTC_NOW_LOG_RX; u4_t_lpcnt++){
            st_gp_tydc_dtc_log_rx[u4_t_lpcnt].u4_ev = st_gp_tydc_dtc_log_rx[u4_t_lpcnt].u4_rx;
            st_gp_tydc_dtc_log_rx[u4_t_lpcnt].u4_rx = (U4)0U;
        }

        vd_s_TydcDtcRxcInit();
    }

    u4_s_tydc_dtc_key_unlock = (U4)0U;
}
/*===================================================================================================================================*/
/*  uint8    u1_g_oXDoCANAubIfDtcUdmDel(const uint16 DTCOrigin)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANAubIfDtcUdmDel(const uint16 DTCOrigin)
{
    U4      u4_t_lpcnt;
    U1      u1_t_result;
    U1      u1_t_ret;

    u1_t_result = (U1)OXDC_DTC_UDM_DEL_OK;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DTC_NUM_UDM_DEL; u4_t_lpcnt++){
        if(st_gp_TYDC_DTC_UDM_DEL[u4_t_lpcnt].u2_mem_slct == DTCOrigin){
            u1_t_result |= st_gp_TYDC_DTC_UDM_DEL[u4_t_lpcnt].fp_u1_UDM_DEL();
        }
    }

    if((U1)(u1_t_result & (U1)OXDC_DTC_UDM_DEL_NG) == (U1)OXDC_DTC_UDM_DEL_NG){
        u1_t_ret = DEM_CALLOUT_NG;
    }
    else if((U1)(u1_t_result & (U1)OXDC_DTC_UDM_DEL_RUN) == (U1)OXDC_DTC_UDM_DEL_RUN){
        u1_t_ret = DEM_CALLOUT_PENDING;
    }
    else{
        u1_t_ret = DEM_CALLOUT_OK;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANAubIfUdmEvStsChg(const uint16 u2_a_EVID, const uint8 u1_a_OLD, const uint8 u1_a_NEW)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
void    vd_g_oXDoCANAubIfUdmEvStsChg(const uint16 u2_a_EVID, const uint8 u1_a_OLD, const uint8 u1_a_NEW)
{
    U1 u1_t_enabled;

    if(((u1_a_OLD & DEM_UDS_STATUS_TF) == (U1)0U) && ((u1_a_NEW & DEM_UDS_STATUS_TF) == DEM_UDS_STATUS_TF)){

        u1_t_enabled = u1_g_TyDoCANDtcCfgUdmEvCntEnabled();
        if(u1_t_enabled == (U1)TRUE){
            u1_s_tydc_dtc_udm_ev_cnt++;     /* this is rolling counter so wrap-around is initentional */
            u2_s_tydc_dtc_udm_last_ev_id = u2_a_EVID;
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_A005(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_A005(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    u1_ap_ans[0] = u1_s_tydc_dtc_udm_ev_cnt;

    return((U1)OXDC_SAL_PROC_FIN);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_A006(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_A006(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    U4 u4_t_dtc;
    U1 u1_t_mem_slct;
    U1 u1_t_ret;

    if(u2_s_tydc_dtc_udm_last_ev_id == U2_MAX){
        u1_t_mem_slct = (U1)0U;
        u4_t_dtc = (U4)0U;
    }
    else{
        u1_t_ret = Dem_GetUserDefinedMemoryIdentifier(u2_s_tydc_dtc_udm_last_ev_id, &u1_t_mem_slct);
        if(u1_t_ret != (U1)E_OK){
            u1_t_mem_slct = (U1)0U;
            u4_t_dtc = (U4)0U;
        }
        else{
            u1_t_ret = Dem_GetDTCOfEvent(u2_s_tydc_dtc_udm_last_ev_id, DEM_DTC_FORMAT_UDS, &u4_t_dtc);
            if(u1_t_ret != (U1)E_OK){
                u4_t_dtc = (U4)0U;
            }
        }
    }

    u1_ap_ans[TYDC_DTC_A006_ANS_CNT]    = u1_s_tydc_dtc_udm_ev_cnt;
    u1_ap_ans[TYDC_DTC_A006_ANS_DTC_H]  = (U1)(u4_t_dtc >>  TYDC_DTC_LSB_3RD);
    u1_ap_ans[TYDC_DTC_A006_ANS_DTC_M]  = (U1)(u4_t_dtc >>  TYDC_DTC_LSB_2ND);
    u1_ap_ans[TYDC_DTC_A006_ANS_DTC_L]  = (U1)(u4_t_dtc);
    u1_ap_ans[TYDC_DTC_A006_ANS_MEMSEL] = u1_t_mem_slct;

    return((U1)OXDC_SAL_PROC_FIN);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcInit(void)
{
    U1 *                       u1_tp_first;
    U1 *                       u1_tp_dst;

    U4                         u4_t_lpcnt;
    U4                         u4_t_log_rx;
    U4                         u4_t_lpknd;
    U4                         u4_t_blkidx;
    U2                         u2_t_nvmc_id;
    U2                         u2_t_nbyte;

    U1                         u1_t_nvm_chk;

    u4_s_tydc_dtc_key_unlock = (U4)0U;

    u2_s_tydc_dtc_rxc_cyctim = (U2)U2_MAX;

    u2_s_tydc_dtc_evm_tocnt  = (U2)0U;
    u1_s_tydc_dtc_evm_ctrl   = (U1)TYDC_DTC_EVM_CTRL_MSK;
    u1_s_tydc_dtc_evm_act    = (U1)0U;

    u1_s_tydc_dtc_log_rx_idx = (U1)U1_MAX;

    u1_s_tydc_dtc_udm_ev_cnt     = (U1)0U;
    u2_s_tydc_dtc_udm_last_ev_id = (U2)U2_MAX;

    u4_t_blkidx = (U4)0U;
    for(u4_t_lpknd = (U4)0U; u4_t_lpknd < (U4)DEM_MM_NVM_REC_KIND_NUM; u4_t_lpknd++){
        u2_t_nbyte   = Dem_RecordInfo_NvBlockTable[u4_t_lpknd].DemBlockSize;
        u1_tp_first  = (U1 *)Dem_RecordInfo_NvBlockTable[u4_t_lpknd].DemRamDataFirstPtr;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)Dem_RecordInfo_NvBlockTable[u4_t_lpknd].DemBlockTotalNum; u4_t_lpcnt++){
            u1_tp_dst    = &u1_tp_first[u4_t_lpcnt * (U4)u2_t_nbyte];
            u2_t_nvmc_id = u2_gp_TYDC_DTC_NVMC_BLOCK[u4_t_blkidx];
            (void)u1_s_TydcDtcNvmcRead(u2_t_nvmc_id, u2_t_nbyte, u1_tp_dst);
            u4_t_blkidx++;
        }
    }

    vd_s_TydcDtcTrDeAct();

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DTC_NUM_PDU_RX; u4_t_lpcnt++){
        u2_gp_tydc_dtc_rxc_st[u4_t_lpcnt] = (U2)0U;
    }
    vd_s_TydcDtcRxcInit();

    u4_t_log_rx = (U4)0U; /* Codesonar Warning "Uninitialized Variable Fix */

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DTC_NOW_LOG_RX; u4_t_lpcnt++){

        st_gp_tydc_dtc_log_rx[u4_t_lpcnt].u4_ev = (U4)0U;
        u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts(u2_gp_TYDC_DTC_NVMC_LOG_RX[u4_t_lpcnt], &u4_t_log_rx);
        if(u1_t_nvm_chk == (U1)NVMC_STATUS_COMP){
            st_gp_tydc_dtc_log_rx[u4_t_lpcnt].u4_rx = u4_t_log_rx;
        }
        else{
            st_gp_tydc_dtc_log_rx[u4_t_lpcnt].u4_rx = (U4)0U;
        }
    }
}
/*===================================================================================================================================*/
/*  static U4      u4_s_TydcDtcTrblchk(const U2 u2_a_TSLOT, const U1 u1_a_EOM, const U1 u1_a_SES)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_TydcDtcTrblchk(const U2 u2_a_TSLOT, const U1 u1_a_EOM, const U1 u1_a_SES)
{
    static const U1            u1_sp_TYDC_DTC_EVM_STM[] = {
        (U1)TYDC_DTC_EVM_ACT_S14_TO_INA, (U1)TYDC_DTC_EVM_ACT_MSK_TO_INA, (U1)TYDC_DTC_EVM_ACT_INA,
        (U1)TYDC_DTC_EVM_ACT_S14,        (U1)TYDC_DTC_EVM_ACT_TO_S14,     (U1)TYDC_DTC_EVM_ACT_TO_S14,
        (U1)TYDC_DTC_EVM_ACT_S14,        (U1)TYDC_DTC_EVM_ACT_TO_MSK,     (U1)TYDC_DTC_EVM_ACT_TO_MSK,
        (U1)TYDC_DTC_EVM_ACT_S14,        (U1)TYDC_DTC_EVM_ACT_TO_S14,     (U1)TYDC_DTC_EVM_ACT_TO_S14,
        (U1)TYDC_DTC_EVM_ACT_S14_TO_INA, (U1)TYDC_DTC_EVM_ACT_MSK_TO_INA, (U1)TYDC_DTC_EVM_ACT_INA,
        (U1)TYDC_DTC_EVM_ACT_S14_TO_INA, (U1)TYDC_DTC_EVM_ACT_TO_S14,     (U1)TYDC_DTC_EVM_ACT_TO_S14,
        (U1)TYDC_DTC_EVM_ACT_S14,        (U1)TYDC_DTC_EVM_ACT_TO_MSK,     (U1)TYDC_DTC_EVM_ACT_TO_MSK,
        (U1)TYDC_DTC_EVM_ACT_S14,        (U1)TYDC_DTC_EVM_ACT_TO_S14,     (U1)TYDC_DTC_EVM_ACT_TO_S14
    };

    U4                         u4_t_ev_dtct;

    U1                         u1_t_eas_chk;
    U1                         u1_t_act;

    u4_s_tydc_dtc_key_unlock = (U4)0U;

    if(u1_s_tydc_dtc_evm_ctrl < (U1)TYDC_DTC_EVM_NUM_CTRL){

        if(u2_s_tydc_dtc_evm_tocnt < (U2)U2_MAX){
            u2_s_tydc_dtc_evm_tocnt++;
        }

        u1_t_eas_chk = u1_s_tydc_dtc_evm_act & ((U1)TYDC_DTC_EVM_EAS_S14_RUN | (U1)TYDC_DTC_EVM_EAS_MSK_RUN);
        if(u1_a_EOM >= (U1)OXDC_EOM_SI_ACT){
            u1_t_eas_chk |= (U1)TYDC_DTC_EVM_EAS_MSK_RUN;
        }
        else{
            /* Do Nothing */
        }

        if(u2_s_tydc_dtc_evm_tocnt >= u2_g_TYDC_DTC_S14_TOUT){
            u1_t_eas_chk |= (U1)TYDC_DTC_EVM_EAS_S14_ABT;
        }

        u1_t_act = (u1_t_eas_chk * (U1)TYDC_DTC_EVM_NUM_CTRL) + u1_s_tydc_dtc_evm_ctrl;
        u1_t_act = u1_sp_TYDC_DTC_EVM_STM[u1_t_act];
    }
    else{
        u1_t_act = (U1)TYDC_DTC_EVM_ACT_MSK_TO_INA;
    }
    vd_s_TydcDtcEvmAct(u1_t_act);

    u2_s_tydc_dtc_rxc_cyctim++;  /* u2_s_tydc_dtc_rxc_cyctim is rolling counter so wrap-around is initentional */

    if(u1_a_EOM >= (U1)OXDC_EOM_NUO_DI){
        u4_t_ev_dtct  = u4_s_TydcDtcLogRx();
    }
    else if(u1_s_tydc_dtc_evm_ctrl < (U1)TYDC_DTC_EVM_CTRL_INA){
        u4_t_ev_dtct  = u4_s_TydcDtcTrchk(u2_a_TSLOT, (U2)0U, (U1)OXDC_DTC_TR_UNK);
        u4_t_ev_dtct |= u4_s_TydcDtcComRx(u2_a_TSLOT, (U2)0U, (U1)OXDC_DTC_TR_UNK);
        u4_t_ev_dtct |= u4_s_TydcDtcLogRx();
    }
    else{
        u4_t_ev_dtct  = u4_s_TydcDtcTrchk(u2_a_TSLOT, u2_s_tydc_dtc_evm_tocnt, (U1)OXDC_DTC_TR_INA);
        u4_t_ev_dtct |= u4_s_TydcDtcComRx(u2_a_TSLOT, u2_s_tydc_dtc_evm_tocnt, (U1)OXDC_DTC_TR_INA);
        u4_t_ev_dtct |= u4_s_TydcDtcLogRx();
    }

    return(u4_t_ev_dtct);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcTrDeAct(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcTrDeAct(void)
{
    U4                         u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DTC_NOW_TR_ACT; u4_t_lpcnt++){
        u4_gp_tydc_dtc_tr_act[u4_t_lpcnt] = (U4)0U;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcRxcInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcRxcInit(void)
{
#if (OXCAN_RX_RXEV_CNT_UNK != 0xffU)
#error "tydocan_dtc.c : OXCAN_RX_RXEV_CNT_UNK shall be equal to 0xff."
#endif
    U4                         u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DTC_NUM_PDU_RX; u4_t_lpcnt++){
        u1_gp_tydc_dtc_rx_cnt[u4_t_lpcnt] = (U1)U1_MAX;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcEvmAct(const U1 u1_a_ACT)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcEvmAct(const U1 u1_a_ACT)
{
    switch(u1_a_ACT){
        case TYDC_DTC_EVM_ACT_TO_S14:
            u2_s_tydc_dtc_evm_tocnt = (U2)0U;
            u1_s_tydc_dtc_evm_ctrl  = (U1)TYDC_DTC_EVM_CTRL_S14;
            break;
        case TYDC_DTC_EVM_ACT_TO_MSK:
            u2_s_tydc_dtc_evm_tocnt = (U2)0U;
            u1_s_tydc_dtc_evm_ctrl  = (U1)TYDC_DTC_EVM_CTRL_MSK;
            break;
        case TYDC_DTC_EVM_ACT_S14_TO_INA:
            vd_s_TydcDtcTrDeAct();
            vd_s_TydcDtcRxcInit();
            vd_g_TyDoCANDtcCfgEvmFinish((U1)TRUE);
            u2_s_tydc_dtc_evm_tocnt = (U2)0U;
            u1_s_tydc_dtc_evm_ctrl  = (U1)TYDC_DTC_EVM_CTRL_INA;
            u1_s_tydc_dtc_evm_act   = (U1)0U;
            break;
        case TYDC_DTC_EVM_ACT_MSK_TO_INA:
            vd_s_TydcDtcTrDeAct();
            vd_s_TydcDtcRxcInit();
            vd_g_TyDoCANDtcCfgEvmFinish((U1)FALSE);
            u2_s_tydc_dtc_evm_tocnt = (U2)0U;
            u1_s_tydc_dtc_evm_ctrl  = (U1)TYDC_DTC_EVM_CTRL_INA;
            u1_s_tydc_dtc_evm_act   = (U1)0U;
            break;
     /* case TYDC_DTC_EVM_ACT_S14: */
     /* case TYDC_DTC_EVM_ACT_INA: */
        default:
            /* Do Nothing */
            break;
    }
}
/*===================================================================================================================================*/
/*  static U4      u4_s_TydcDtcTrchk(const U2 u2_a_TSLOT, const U2 u2_a_ELPSD, const U1 u1_a_EVM)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_TydcDtcTrchk(const U2 u2_a_TSLOT, const U2 u2_a_ELPSD, const U1 u1_a_EVM)
{
    U4                         u4_t_ev_dtct;
    U4                         u4_t_lpcnt;
    U2                         u2_t_smpl_chk;
    U1                         u1_t_tr_chk;

    u4_t_ev_dtct = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DTC_NUM_TR_CHK; u4_t_lpcnt++){

        u2_t_smpl_chk = u2_a_TSLOT & st_gp_TYDC_DTC_TR_CHK[u4_t_lpcnt].u2_smpl_tslot;
        if((u2_t_smpl_chk                               != (U2)0U    ) &&
           (st_gp_TYDC_DTC_TR_CHK[u4_t_lpcnt].fp_u1_CHK != vdp_PTR_NA)){

            u1_t_tr_chk   = (*st_gp_TYDC_DTC_TR_CHK[u4_t_lpcnt].fp_u1_CHK)(u2_a_ELPSD);
            if(u1_t_tr_chk < u1_a_EVM){
                u1_t_tr_chk = u1_a_EVM;
            }
            u4_t_ev_dtct |= u4_s_TydcDtcTrPut(st_gp_TYDC_DTC_TR_CHK[u4_t_lpcnt].u2_dtc_id, u1_t_tr_chk);
        }
    }

    return(u4_t_ev_dtct);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_TydcDtcComRx(const U2 u2_a_TSLOT, const U2 u2_a_ELPSD, const U1 u1_a_EVM)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_TydcDtcComRx(const U2 u2_a_TSLOT, const U2 u2_a_ELPSD, const U1 u1_a_EVM)
{
    U4                         u4_t_lpcnt;
    U4                         u4_t_ev_dtct;

    U2                         u2_t_smpl_chk;

    U1                         u1_t_sup_chk;
    U1                         u1_t_tr_chk;

    u4_t_ev_dtct = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DTC_NUM_COM_RX; u4_t_lpcnt++){

        u2_t_smpl_chk = u2_a_TSLOT & st_gp_TYDC_DTC_COM_RX[u4_t_lpcnt].u2_smpl_tslot;
        if(u2_t_smpl_chk != (U2)0U){

            u1_t_tr_chk = u1_s_TydcDtcPduRx(&st_gp_TYDC_DTC_COM_RX[u4_t_lpcnt], u2_a_ELPSD, u1_a_EVM);
            if(st_gp_TYDC_DTC_COM_RX[u4_t_lpcnt].fp_u1_SUP != vdp_PTR_NA){
                u1_t_sup_chk = (*st_gp_TYDC_DTC_COM_RX[u4_t_lpcnt].fp_u1_SUP)();
                if(u1_t_sup_chk != (U1)TRUE){
                    u1_t_tr_chk = (U1)OXDC_DTC_TR_N_A;
                }
            }

            u4_t_ev_dtct |= u4_s_TydcDtcTrPut(st_gp_TYDC_DTC_COM_RX[u4_t_lpcnt].u2_dtc_id, u1_t_tr_chk);
        }
    }

    return(u4_t_ev_dtct);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcDtcPduRx(const ST_TYDC_DTC_COM_RX * st_ap_COM_RX, const U2 u2_a_ELPSD, const U1 u1_a_EVM)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcDtcPduRx(const ST_TYDC_DTC_COM_RX * st_ap_COM_RX, const U2 u2_a_ELPSD, const U1 u1_a_EVM)
{
    const ST_TYDC_DTC_PDU_RX * st_tp_PDU_RX;

    ST_TYDC_DTC_LOG_RX *       st_tp_log_rx;

    U4                         u4_t_lpcnt;
    U4                         u4_t_lpend;
    U4                         u4_t_log_bit;
    U4                         u4_t_sup_chk;
    U4                         u4_t_unk_chk;
    U4                         u4_t_rxto_chk;

    U2                         u2_t_rxc_inc;
    U2                         u2_t_rx_tout;

    U1                         u1_t_rxc_nex;
    U1                         u1_t_rxc_las;
    U1                         u1_t_rx_stat;

    U1                         u1_t_tr_chk;

    u4_t_lpcnt    = (U4)st_ap_COM_RX->u1_pdu_begin;
    u4_t_lpend    = u4_t_lpcnt + (U4)st_ap_COM_RX->u1_num_pdu;
    if(u4_t_lpend > (U4)u1_g_TYDC_DTC_NUM_PDU_RX){
        u4_t_lpend = (U4)u1_g_TYDC_DTC_NUM_PDU_RX;
    }
    u4_t_log_bit  = (U4)0x00000001U << st_ap_COM_RX->u1_log_bit;
    st_tp_log_rx  = &st_gp_tydc_dtc_log_rx[st_ap_COM_RX->u1_log_idx];

    u4_t_sup_chk  = (U4)0U;
    u4_t_unk_chk  = (U4)0U;
    u4_t_rxto_chk = (U4)0U;

    while(u4_t_lpcnt < u4_t_lpend){

        st_tp_PDU_RX = &st_gp_TYDC_DTC_PDU_RX[u4_t_lpcnt];

        u1_t_rxc_nex = u1_g_oXCANRxEvcnt(st_tp_PDU_RX->u2_pdu_idx);
        u1_t_rxc_las = u1_gp_tydc_dtc_rx_cnt[u4_t_lpcnt];
        if((u1_a_EVM     != (U1)OXDC_DTC_TR_INA         ) ||
           (u1_t_rxc_nex >  (U1)OXCAN_RX_RXEV_CNT_MAX) ||
           (u1_t_rxc_las >  (U1)OXCAN_RX_RXEV_CNT_MAX)){

            u2_gp_tydc_dtc_rxc_st[u4_t_lpcnt] = u2_s_tydc_dtc_rxc_cyctim;
            u1_gp_tydc_dtc_rx_cnt[u4_t_lpcnt] = u1_t_rxc_nex;
        }
        else{

            u2_t_rxc_inc = (U2)((U2)u1_t_rxc_nex - (U2)u1_t_rxc_las) & (U2)OXCAN_RX_RXEV_CNT_MAX;
            if(u2_t_rxc_inc >= st_tp_PDU_RX->u2_rxc_min){
                st_tp_log_rx->u4_ev |= ((st_tp_log_rx->u4_rx ^ u4_t_log_bit) & u4_t_log_bit);
                st_tp_log_rx->u4_rx |= u4_t_log_bit;
            }

            u2_t_rxc_inc = u2_s_tydc_dtc_rxc_cyctim - u2_gp_tydc_dtc_rxc_st[u4_t_lpcnt];
            if(u2_t_rxc_inc >= st_tp_PDU_RX->u2_rxc_cyc){
                u2_gp_tydc_dtc_rxc_st[u4_t_lpcnt] = u2_s_tydc_dtc_rxc_cyctim;
                u1_gp_tydc_dtc_rx_cnt[u4_t_lpcnt] = u1_t_rxc_nex;
            }
        }

        u2_t_rx_tout = st_tp_PDU_RX->u2_rx_tout;
        u1_t_rx_stat = u1_g_oXCANRxStat(st_tp_PDU_RX->u2_pdu_idx, st_tp_PDU_RX->u2_sys_chk, u2_t_rx_tout);
        if((u2_a_ELPSD   < u2_t_rx_tout         ) ||
           (u1_t_rx_stat < (U1)OXCAN_RX_RXST_TOE)){
            u4_t_unk_chk  |= u4_t_log_bit;
        }
        else if(u1_t_rx_stat >= ((U1)OXCAN_RX_RXST_TOE | (U1)COM_TIMEOUT)){
            u4_t_rxto_chk |= u4_t_log_bit;
        }
        else{
            /* Do Nothing */
        }

        u4_t_sup_chk  |= u4_t_log_bit;
        u4_t_log_bit <<= 1U;
        u4_t_lpcnt++;
    }

    u4_t_sup_chk  &= st_tp_log_rx->u4_rx;
    u4_t_unk_chk  &= u4_t_sup_chk;
    u4_t_rxto_chk &= u4_t_sup_chk;
    u1_t_tr_chk    = u1_s_TydcDtcRxTOchk(u4_t_sup_chk, u4_t_unk_chk, u4_t_rxto_chk);

    return(u1_t_tr_chk);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_TydcDtcLogRx(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_TydcDtcLogRx(void)
{
    U4                         u4_t_ev_dtct;

    if(u1_s_tydc_dtc_log_rx_idx >= u1_g_TYDC_DTC_NOW_LOG_RX){
        u1_s_tydc_dtc_log_rx_idx = (U1)0U;
    }

    if(st_gp_tydc_dtc_log_rx[u1_s_tydc_dtc_log_rx_idx].u4_ev != (U4)0U){
        u4_t_ev_dtct = st_gp_tydc_dtc_log_rx[u1_s_tydc_dtc_log_rx_idx].u4_ev;
        vd_g_Nvmc_WriteU4(u2_gp_TYDC_DTC_NVMC_LOG_RX[u1_s_tydc_dtc_log_rx_idx],
                          st_gp_tydc_dtc_log_rx[u1_s_tydc_dtc_log_rx_idx].u4_rx);
    }
    else{
        u4_t_ev_dtct = (U4)0U;
    }
    st_gp_tydc_dtc_log_rx[u1_s_tydc_dtc_log_rx_idx].u4_ev = (U4)0U;
    u1_s_tydc_dtc_log_rx_idx++;

    return(u4_t_ev_dtct);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_TydcDtcTrPut(const U2 u2_a_ID, const U1 u1_a_CHK)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_TydcDtcTrPut(const U2 u2_a_ID, const U1 u1_a_CHK)
{
    U4                         u4_t_wid;
    U4                         u4_t_bit;
    U4                         u4_t_act;

    u4_t_act = (U4)0U;
    u4_t_wid = (U4)u2_a_ID >> TYDC_DTC_TRBL_LSR_WID;
    if(u4_t_wid >= (U4)u1_g_TYDC_DTC_NOW_TR_ACT){

        (void)Dem_SetEventAvailable(u2_a_ID, (U1)FALSE);

     /* u4_t_act = (U4)0U; */
    }
    else if(u1_a_CHK >= (U1)OXDC_DTC_TR_N_A){

        (void)Dem_SetEventAvailable(u2_a_ID, (U1)FALSE);

        u4_t_bit = (U4)0x00000001U << (u2_a_ID & (U2)TYDC_DTC_TRBL_BIT_LSB);
     /* u4_t_act = (U4)0U; */
        u4_gp_tydc_dtc_tr_act[u4_t_wid] &= ((U4)U4_MAX ^ u4_t_bit);
    }
    else if(u1_a_CHK == (U1)OXDC_DTC_TR_UNK){

        (void)Dem_SetEventAvailable(u2_a_ID, (U1)TRUE);

        u4_t_bit = (U4)0x00000001U << (u2_a_ID & (U2)TYDC_DTC_TRBL_BIT_LSB);
     /* u4_t_act = (U4)0U; */
        u4_gp_tydc_dtc_tr_act[u4_t_wid] &= ((U4)U4_MAX ^ u4_t_bit);
    }
    else if(u1_a_CHK == (U1)OXDC_DTC_TR_INA){

        (void)Dem_SetEventAvailable(u2_a_ID, (U1)TRUE);
        (void)Dem_SetEventStatus(u2_a_ID, DEM_EVENT_STATUS_PASSED);

        u4_t_bit = (U4)0x00000001U << (u2_a_ID & (U2)TYDC_DTC_TRBL_BIT_LSB);
     /* u4_t_act = (U4)0U; */
        u4_gp_tydc_dtc_tr_act[u4_t_wid] &= ((U4)U4_MAX ^ u4_t_bit);
    }
    else{

        (void)Dem_SetEventAvailable(u2_a_ID, (U1)TRUE);
        (void)Dem_SetEventStatus(u2_a_ID, DEM_EVENT_STATUS_FAILED);

        u4_t_bit = (U4)0x00000001U << (u2_a_ID & (U2)TYDC_DTC_TRBL_BIT_LSB);
        u4_t_act = (u4_gp_tydc_dtc_tr_act[u4_t_wid] ^ u4_t_bit) & u4_t_bit;
        u4_gp_tydc_dtc_tr_act[u4_t_wid] |= u4_t_bit;
    }

    return(u4_t_act);
}
/*===================================================================================================================================*/
/*  static inline U1      u1_s_TydcDtcRxTOchk(const U4 u4_a_SUP, const U4 u4_a_UNK, const U4 u4_a_RXTO)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U1      u1_s_TydcDtcRxTOchk(const U4 u4_a_SUP, const U4 u4_a_UNK, const U4 u4_a_RXTO)
{
    U1                         u1_t_tr_chk;

    if(u4_a_SUP == (U4)0U){
        u1_t_tr_chk = (U1)OXDC_DTC_TR_N_A;
    }
    else if(u4_a_UNK == u4_a_SUP){
        u1_t_tr_chk = (U1)OXDC_DTC_TR_UNK;
    }
    else if(u4_a_RXTO == (U4)0U){
        u1_t_tr_chk = (U1)OXDC_DTC_TR_INA;
    }
    else{
        u1_t_tr_chk = (U1)OXDC_DTC_TR_ACT;
    }

    return(u1_t_tr_chk);
}
/*===================================================================================================================================*/
/*  static U1             u1_s_TydcDtcNvmcRead(const U2 u2_a_NVMCID, const U2 u2_a_size, U1 *u1_ap_data)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1             u1_s_TydcDtcNvmcRead(const U2 u2_a_NVMCID, const U2 u2_a_size, U1 *u1_ap_data)
{
    U1                         u1_t_nvm_chk;
    U4                         u4_t_data;

    if(u2_a_size == (U2)TYDC_NVM_SIZE_U4){
        u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts(u2_a_NVMCID, &u4_t_data);
        if(u1_t_nvm_chk != (U1)NVMC_STATUS_COMP){
            vd_g_MemfillU1(u1_ap_data, (U1)U1_MAX, (U4)u2_a_size);
        }
        else{
            u1_ap_data[TYDC_NVM_IDX_P0] = (U1)(u4_t_data >> TYDC_NVM_U4_LSB_4TH);
            u1_ap_data[TYDC_NVM_IDX_P1] = (U1)(u4_t_data >> TYDC_NVM_U4_LSB_3RD);
            u1_ap_data[TYDC_NVM_IDX_P2] = (U1)(u4_t_data >> TYDC_NVM_U4_LSB_2ND);
            u1_ap_data[TYDC_NVM_IDX_P3] = (U1)(u4_t_data);
        }
    }
    else{
        u1_t_nvm_chk = u1_g_Nvmc_ReadOthrwithSts(u2_a_NVMCID, u2_a_size, u1_ap_data);
        if(u1_t_nvm_chk != (U1)NVMC_STATUS_COMP){
            vd_g_MemfillU1(u1_ap_data, (U1)U1_MAX, (U4)u2_a_size);
        }
    }

    return (u1_t_nvm_chk);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     5/14/2019  TN       New.                                                                                               */
/*  1.1.0    10/14/2019  TN       vd_g_TyDoCANAubIfDtcRestart and vd_g_TyDoCANAubIfDtcSuspend were implemented.                      */
/*  1.2.0    11/ 8/2019  TN       Bug Fix : DTC detection was performed even though the condition was not met in u1_s_TydcDtcPduRx   */
/*  1.3.0    11/22/2019  TN       Bug Fix : DTC detection was performed even though the condition was not met in u1_s_TydcDtcPduRx   */
/*  1.4.0     2/24/2020  HK       tydocan_dtc_mm v1.3.0 -> v1.4.0                                                                    */
/*  1.5.0     3/13/2020  TN       vd_g_TyDoCANDtcLogRxReset was implemented.                                                         */
/*  1.6.0     7/21/2020  TN       Bug Fix : DTC U1317/Message Authentication Key Install Failure was not logged due to redundant     */
/*                                event mask.                                                                                        */
/*  1.7.0    12/22/2020  TN       ST_TYDC_DTC_PDU_RX.u2_rxc_min was defined in order to support CXPI.                                */
/*  1.8.0     2/19/2021  TN       ST_TYDC_DTC_PDU_RX.u2_rxc_cyc was defined in order to CXPI Rx timeout activiation                  */
/*  1.8.1     4/ 2/2021  HK       QAC warnigs were fixed.                                                                            */
/*  1.8.2     6/ 9/2021  TN       QAC warnigs were fixed.                                                                            */
/*  1.8.3     9/ 9/2021  TN       NULL->vdp_PTR_NA.                                                                                  */
/*                       HK       QAC warnigs were fixed.                                                                            */
/*  1.9.0    10/ 8/2021  TN       Codesonar Warning "Uninitialized Variable was fixed.                                               */
/*  1.9.1     7/ 7/2023  ST       Update for OEM standardization.                                                                    */
/*  1.9.2    11/08/2023  TI       Update for Phase6 NMDiag.                                                                          */
/*  1.9.3     1/23/2024  TI       tydocan_dtc_cfg.c v1.9.2 -> v1.9.3                                                                 */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*  * HK = Hayato Kanamori, DENSO Create                                                                                             */
/*  * ST = Shohei Takada, DENSO                                                                                                      */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
