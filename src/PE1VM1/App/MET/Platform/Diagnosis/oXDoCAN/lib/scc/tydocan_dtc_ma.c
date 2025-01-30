/* 1.4.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota Diag on CAN / Dtc Message Authentication                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DTC_MA_C_MAJOR                   (1U)
#define TYDOCAN_DTC_MA_C_MINOR                   (4U)
#define TYDOCAN_DTC_MA_C_PATCH                   (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "tydocan_dtc_ma_cfg_private.h"
#include "tydocan_evlog_cfg_private.h"

#include "SecOC.h"                    /* SecOC_RxPduProcessing[] and SECOC_RX_PDU_PROCESSING_MAX are defined in SecOC_Cfg.h */
                                      /* SecOC_Cfg.h is included in SecOC.h                                                 */

#include "oxdocan_aubif.h"
#include "oxdocan_aubif_ma.h"         /* oxdocan_aubif_ma.h shall be included after SecOC.h is included.                    */
#include "Dem.h"
#include "Dem_Dcm.h"

#include "memfill_u1.h"
#include "memfill_u2.h"
#include "memcpy_u1.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_DTC_MA_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_dtc_ma.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (TYDOCAN_DTC_MA_C_MAJOR != OXDOCAN_AUBIF_MA_H_MAJOR)
#error "tydocan_dtc_ma.c and oxdocan_aubif_ma.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_MA_C_MAJOR != TYDOCAN_DTC_MA_CFG_H_MAJOR) || \
     (TYDOCAN_DTC_MA_C_MINOR != TYDOCAN_DTC_MA_CFG_H_MINOR) || \
     (TYDOCAN_DTC_MA_C_PATCH != TYDOCAN_DTC_MA_CFG_H_PATCH))
#error "tydocan_dtc_ma.c and tydocan_dtc_ma_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_MA_SYN_INA                      (0xffffU)
#define TYDC_DTC_MA_SYN_MAX                      (0xfffeU)
#define TYDC_DTC_MA_SYN_VRFY_MAX                 (3U)

#define TYDC_DTC_U2302_EV_CAPT                   (0x54U)     /* bit 0 : 000b = no rx                  */
                                                             /* bit 1 : 001b = verification ok        */
                                                             /* bit 2 : 010b = verification not ok    */
                                                             /* bit 3 : 011b = verification ok/not ok */
                                                             /* bit 4 : 100b = verification not ok    */
                                                             /* bit 5 : 101b = verification ok/not ok */
                                                             /* bit 6 : 110b = verification not ok    */
                                                             /* bit 7 : 111b = verification ok/not ok */

/* event and status */
#define TYDC_DTC_MA_RF_EAS_TOUT                  (0x01U)
#define TYDC_DTC_MA_RF_EAS_RFC_ENA               (0x02U)

#define TYDC_DTC_MA_RF_ACT_TO_STA                (0U)
#define TYDC_DTC_MA_RF_ACT_TO_RUN                (1U)
#define TYDC_DTC_MA_RF_ACT_STA                   (2U)
#define TYDC_DTC_MA_RF_ACT_RUN                   (3U)

#define TYDC_DTC_MA_RFC_MAX                      (1U)

#define TYDC_DTC_MA_NUM_REC_AB_U2B74             (5U)
#define TYDC_DTC_MA_SEC_TRNC_SIZE                (8U)

#define TYDC_DTC_MA_BR_UNK                       (0x0000U)
#define TYDC_DTC_MA_BR_LAS                       (0x5aa5U)

#define TYDC_DTC_MA_NWCM_MAECNT_SIZE             (4U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_MA_DTC_VALUE                    (0x00EB7400U)
#define TYDC_DTC_MA_DID_ERRCNT                   (0x0110U)
#define TYDC_DTC_MA_DID_MAERR_SIZE               (0x23U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_REBYID_0110_ANS_RFC_0               (0U)
#define TYDC_REBYID_0110_ANS_RFC_1               (1U)
#define TYDC_REBYID_0110_ANS_RFC_2               (2U)
#define TYDC_REBYID_0110_ANS_RFC_3               (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_MA_LSB_BYTE_4TH                 (24U)
#define TYDC_DTC_MA_LSB_BYTE_3RD                 (16U)
#define TYDC_DTC_MA_LSB_BYTE_2ND                 (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2        u2_s_tydc_dtc_ma_rf_elpsd;
static U2        u2_s_tydc_dtc_ma_rf_cnt;
static U1        u1_s_tydc_dtc_ma_rf_chk;

static U2        u2_s_tydc_dtc_ma_syn_elpsd;
static U1        u1_s_tydc_dtc_ma_syn_chk;

static U1        u1_s_tydc_dtc_ma_syn_cnt;                      /* verify ok count of sync msg      */
static U1        u1_s_tydc_dtc_kup_chk;                         /* Key Update Incomplete DTC        */
static U1        u1_s_tydc_dtc_mae_chk;                         /* Message authentication error DTC */
static U1        u1_s_tydc_dtc_mae_chk_ev;                      /* Message authentication error Event Logging */

static SecOC_VerificationStatusType st_s_tydc_dtc_ma_RSLT;
static U1                           u1_sp_tydc_dtc_ma_SduData[TYDC_DTC_MA_SEC_TRNC_SIZE];
static PduLengthType                st_s_tydc_dtc_ma_SduLength;
static U2                           u2_s_tydc_dtc_ma_ev_cnt;

static U2                           u2_sp_tydc_dtc_ma_id_idx[TYDC_DTC_MA_NUM_REC_AB_U2B74];
static U1                           u1_s_tydc_dtc_ma_id_cnt;
static U1                           u1_s_tydc_dtc_ma_id_next;
static U1                           u1_s_tydc_dtc_ma_id_ref;
static U2                           u2_s_tydc_dtc_ma_br_chk;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_TydcDtcMaSynchk(const U1 u1_a_IGN_ON);     /* gnsecmacrs-a00-06-a */
static void    vd_s_TydcDtcMaRfchk(const U1 u1_a_IGN_ON);

static void    vd_s_TydcDtcMaRf_ToSta(void);
static void    vd_s_TydcDtcMaRf_ToRun(void);

static void    vd_s_TyDoCANDtcMaEvCtxInit(void);
static void    vd_s_TyDoCANDtcMaIdCtxInit(void);
static void    vd_s_TyDoCANDtcMaEvCapt_U2B74(const U4 u4_a_CANID);
static void    vd_s_TyDoCANDtcMaEvCapt_U2B11(const SecOC_VerificationStatusType st_a_RSLT, const uint8* SduDataPtr, PduLengthType SduLength);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcMaInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcMaInit(void)
{
    U1                            u1_t_ret;
    U4                            u4_t_data;

    u2_s_tydc_dtc_ma_rf_elpsd    = (U2)U2_MAX;
    u2_s_tydc_dtc_ma_rf_cnt      = (U2)0U;

    u1_t_ret = u1_g_NWCMReadData(u1_g_TYDC_DTC_MA_MAECNT_NWCMID, (U1*)&u4_t_data, (U1)TYDC_DTC_MA_NWCM_MAECNT_SIZE);
    if((u1_t_ret & (U1)NWCM_RESULT_NG_NO_READABLE_DATA) != (U1)0U){
        u4_t_data = (U4)0U;
    }
    vd_g_Rim_WriteU4(u2_g_TYDC_DTC_MA_MAECNT_RIMID, u4_t_data);
    u1_s_tydc_dtc_ma_rf_chk      = (U1)TYDC_DTC_MA_RF_CHK_INA;

    u2_s_tydc_dtc_ma_syn_elpsd   = (U2)TYDC_DTC_MA_SYN_INA;
    u1_s_tydc_dtc_ma_syn_chk     = (U1)0U;

    u1_s_tydc_dtc_ma_syn_cnt     = (U1)0U;
    u1_s_tydc_dtc_kup_chk        = (U1)OXDC_DTC_TR_UNK;
    u1_s_tydc_dtc_mae_chk        = (U1)OXDC_DTC_TR_UNK;
    u1_s_tydc_dtc_mae_chk_ev     = (U1)OXDC_DTC_TR_UNK;

    vd_s_TyDoCANDtcMaEvCtxInit();
    vd_s_TyDoCANDtcMaIdCtxInit();
    u2_s_tydc_dtc_ma_br_chk      = (U2)TYDC_DTC_MA_BR_LAS;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcMaRstInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcMaRstInit(void)
{
    u2_s_tydc_dtc_ma_rf_elpsd    = (U2)U2_MAX;
    u2_s_tydc_dtc_ma_rf_cnt      = (U2)0U;

    u1_s_tydc_dtc_ma_rf_chk      = (U1)TYDC_DTC_MA_RF_CHK_INA;

    u2_s_tydc_dtc_ma_syn_elpsd   = (U2)TYDC_DTC_MA_SYN_INA;
    u1_s_tydc_dtc_ma_syn_chk     = (U1)0U;

    u1_s_tydc_dtc_ma_syn_cnt     = (U1)0U;
    u1_s_tydc_dtc_kup_chk        = (U1)OXDC_DTC_TR_UNK;
    u1_s_tydc_dtc_mae_chk        = (U1)OXDC_DTC_TR_UNK;
    u1_s_tydc_dtc_mae_chk_ev     = (U1)OXDC_DTC_TR_UNK;

    vd_s_TyDoCANDtcMaEvCtxInit();
    vd_s_TyDoCANDtcMaIdCtxInit();
    u2_s_tydc_dtc_ma_br_chk      = (U2)TYDC_DTC_MA_BR_LAS;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcMaWkupInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcMaWkupInit(void)
{
    U1                            u1_t_ret_nwcm;
    U1                            u1_t_ret_rim;
    U4                            u4_t_data_nwcm;
    U4                            u4_t_data_rim;

    u2_s_tydc_dtc_ma_rf_elpsd    = (U2)U2_MAX;
    u2_s_tydc_dtc_ma_rf_cnt      = (U2)0U;

    u1_t_ret_nwcm = u1_g_NWCMReadData(u1_g_TYDC_DTC_MA_MAECNT_NWCMID, (U1*)&u4_t_data_nwcm, (U1)TYDC_DTC_MA_NWCM_MAECNT_SIZE);
    u1_t_ret_rim  = u1_g_Rim_ReadU4withStatus(u2_g_TYDC_DTC_MA_MAECNT_RIMID, &u4_t_data_rim);
    if(((u1_t_ret_nwcm & (U1)NWCM_RESULT_NG_NO_READABLE_DATA) == (U1)0U) && (u1_t_ret_rim != (U1)RIM_RESULT_NG_DATA)){
        if(u4_t_data_nwcm < u4_t_data_rim){
            (void)u1_g_NWCMWriteData(u1_g_TYDC_DTC_MA_MAECNT_NWCMID, (U1*)&u4_t_data_rim, (U1)TYDC_DTC_MA_NWCM_MAECNT_SIZE);
        }
        else if(u4_t_data_nwcm > u4_t_data_rim){
            vd_g_Rim_WriteU4(u2_g_TYDC_DTC_MA_MAECNT_RIMID, u4_t_data_nwcm);
        }
        else{
            /* Do nothing. */
        }
    }
    else if(((u1_t_ret_nwcm & (U1)NWCM_RESULT_NG_NO_READABLE_DATA) != (U1)0U) && (u1_t_ret_rim != (U1)RIM_RESULT_NG_DATA)){
        (void)u1_g_NWCMWriteData(u1_g_TYDC_DTC_MA_MAECNT_NWCMID, (U1*)&u4_t_data_rim, (U1)TYDC_DTC_MA_NWCM_MAECNT_SIZE);
    }
    else if(((u1_t_ret_nwcm & (U1)NWCM_RESULT_NG_NO_READABLE_DATA) == (U1)0U) && (u1_t_ret_rim == (U1)RIM_RESULT_NG_DATA)){
        vd_g_Rim_WriteU4(u2_g_TYDC_DTC_MA_MAECNT_RIMID, u4_t_data_nwcm);
    }
    else{
        u4_t_data_nwcm = (U4)0U;
        u4_t_data_rim  = (U4)0U;
        (void)u1_g_NWCMWriteData(u1_g_TYDC_DTC_MA_MAECNT_NWCMID, (U1*)&u4_t_data_rim, (U1)TYDC_DTC_MA_NWCM_MAECNT_SIZE);
        vd_g_Rim_WriteU4(u2_g_TYDC_DTC_MA_MAECNT_RIMID, u4_t_data_nwcm);
    }

    u1_s_tydc_dtc_ma_rf_chk      = (U1)TYDC_DTC_MA_RF_CHK_INA;

    u2_s_tydc_dtc_ma_syn_elpsd   = (U2)TYDC_DTC_MA_SYN_INA;
    u1_s_tydc_dtc_ma_syn_chk     = (U1)0U;

    u1_s_tydc_dtc_ma_syn_cnt     = (U1)0U;
    u1_s_tydc_dtc_kup_chk        = (U1)OXDC_DTC_TR_UNK;
    u1_s_tydc_dtc_mae_chk        = (U1)OXDC_DTC_TR_UNK;
    u1_s_tydc_dtc_mae_chk_ev     = (U1)OXDC_DTC_TR_UNK;

    vd_s_TyDoCANDtcMaEvCtxInit();
    vd_s_TyDoCANDtcMaIdCtxInit();
    u2_s_tydc_dtc_ma_br_chk      = (U2)TYDC_DTC_MA_BR_LAS;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcMaMainTask(const U1 u1_a_EOM)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcMaMainTask(const U1 u1_a_EOM)
{
    U1                         u1_t_ign_on;

    u1_t_ign_on = u1_a_EOM & (U1)OXDC_EOM_IGN_ON;
    vd_s_TydcDtcMaSynchk(u1_t_ign_on);
    vd_s_TydcDtcMaRfchk(u1_t_ign_on);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_0110(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_0110(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    U1                         u1_t_ret;
    U4                         u4_t_data;

    u1_t_ret = u1_g_Rim_ReadU4withStatus(u2_g_TYDC_DTC_MA_MAECNT_RIMID, &u4_t_data);
    if(u1_t_ret == (U1)RIM_RESULT_NG_DATA){
        u4_t_data = (U4)0U;
    }

    u1_ap_ans[TYDC_REBYID_0110_ANS_RFC_0] = (U1)(u4_t_data >> TYDC_DTC_MA_LSB_BYTE_4TH);
    u1_ap_ans[TYDC_REBYID_0110_ANS_RFC_1] = (U1)(u4_t_data >> TYDC_DTC_MA_LSB_BYTE_3RD);
    u1_ap_ans[TYDC_REBYID_0110_ANS_RFC_2] = (U1)(u4_t_data >> TYDC_DTC_MA_LSB_BYTE_2ND);
    u1_ap_ans[TYDC_REBYID_0110_ANS_RFC_3] = (U1)u4_t_data;

    return((U1)OXDC_SAL_PROC_FIN);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcTrchk_U2302(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2302(const U2 u2_a_ELPSD)
{
    U1                            u1_t_dtc_act;

    u1_t_dtc_act = u1_s_tydc_dtc_kup_chk;
    u1_s_tydc_dtc_kup_chk = (U1)OXDC_DTC_TR_INA;

    return(u1_t_dtc_act);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANAubIfSecVerifAck(const SecOC_VerificationStatusType st_a_RSLT)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANAubIfSecVerifAck(const SecOC_VerificationStatusType st_a_RSLT)
{
    /* typedef uint16 SecOC_VerificationResultType;                              */
    /* #define SECOC_VERIFICATIONSUCCESS       ((SecOC_VerificationResultType)0) */
    /* #define SECOC_VERIFICATIONFAILURE       ((SecOC_VerificationResultType)1) */
    /* #define SECOC_FRESHNESSFAILURE          ((SecOC_VerificationResultType)2) */
    /* typedef struct {                                                          */
    /*     uint16                              freshnessValueID;                 */
    /*     SecOC_VerificationResultType        verificationStatus;               */
    /* } SecOC_VerificationStatusType;                                           */

    /* extern CONST(SecOC_RxPduProcessingType, SECOC_CONST_CONFIG)               */
    /*                       SecOC_RxPduProcessing[SECOC_RX_PDU_PROCESSING_MAX]; */
    /*                                                                           */
    /* typedef struct {                                                          */
    /*     ...                                                                   */
    /*     uint8                               Ab_MessageType;                   */
    /*     uint16                              DataId;                           */
    /*     ...                                                                   */
    /* } SecOC_RxPduProcessingType;                                              */
    
    U1                         u1_t_type;
    U1                         u1_t_chk;

    if(u1_s_tydc_dtc_ma_syn_cnt < (U1)TYDC_DTC_MA_SYN_VRFY_MAX){
        if((u2_s_tydc_dtc_ma_syn_elpsd < u2_g_TYDC_DTC_MA_SYN_TOUT       ) &&
        (st_a_RSLT.freshnessValueID < (U2)SECOC_RX_PDU_PROCESSING_MAX)){

            u1_t_type = SecOC_RxPduProcessing[st_a_RSLT.freshnessValueID].Ab_MessageType;
            if(u1_t_type == (U1)SECOC_AB_MSGTYPE_SYNC){
                u1_s_tydc_dtc_ma_syn_chk |= (U1)((U1)0x01U << st_a_RSLT.verificationStatus);

                u1_t_chk = ((U1)TYDC_DTC_U2302_EV_CAPT >> u1_s_tydc_dtc_ma_syn_chk) & (U1)TRUE;
                if(u1_t_chk == (U1)FALSE){
                    u1_s_tydc_dtc_ma_syn_cnt++;
                }
            }
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U2B74(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2B74(const U2 u2_a_ELPSD)
{
    U4                        u4_t_lpcnt;
    U4                        u4_t_lpend;

    if(u1_s_tydc_dtc_mae_chk == (U1)OXDC_DTC_TR_ACT){
        if(u1_s_tydc_dtc_ma_id_cnt < (U1)TYDC_DTC_MA_NUM_REC_AB_U2B74){
            u1_s_tydc_dtc_ma_id_ref  = (U1)0U;
            u4_t_lpend               = (U4)u1_s_tydc_dtc_ma_id_cnt;
        }
        else{
            u1_s_tydc_dtc_ma_id_ref  = u1_s_tydc_dtc_ma_id_next - (U1)1U;
            u4_t_lpend               = (U4)TYDC_DTC_MA_NUM_REC_AB_U2B74;
        }

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_lpend; u4_t_lpcnt++){
            if(u1_s_tydc_dtc_ma_id_ref >= (U1)TYDC_DTC_MA_NUM_REC_AB_U2B74){
                u1_s_tydc_dtc_ma_id_ref = (U1)0U;
            }
            (void)Dem_SetEventFailedWithSyncFreezeFrame((Dem_EventIdType)DemConf_DemEventParameter_DemEventDTC_U2B74);
            u1_s_tydc_dtc_ma_id_ref++;
        }
        vd_s_TyDoCANDtcMaIdCtxInit();
        u1_s_tydc_dtc_mae_chk        = (U1)OXDC_DTC_TR_INA;
    }
    return((U1)OXDC_DTC_TR_UNK);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U2B11(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2B11(const U2 u2_a_ELPSD)
{
    if(u1_s_tydc_dtc_mae_chk_ev == (U1)OXDC_DTC_TR_ACT){
        vd_g_TyDoCANEvlogMsgAtErr(st_s_tydc_dtc_ma_RSLT, u1_sp_tydc_dtc_ma_SduData, st_s_tydc_dtc_ma_SduLength, u2_s_tydc_dtc_ma_ev_cnt);    /* U2B11 */
        vd_s_TyDoCANDtcMaEvCtxInit();
        u1_s_tydc_dtc_mae_chk_ev     = (U1)OXDC_DTC_TR_INA;
    }
    return((U1)OXDC_DTC_TR_UNK);
}
/*===================================================================================================================================*/
/*  void vd_g_TyDoCANAubIfSecVerifFinAck(const SecOC_VerificationStatusType st_a_RSLT,const uint8* SduDataPtr,PduLengthType SduLength)*/
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANAubIfSecVerifFinAck(const SecOC_VerificationStatusType st_a_RSLT, const uint8* SduDataPtr, PduLengthType SduLength)
{
    U4                            u4_t_data;
    U1                            u1_t_ret;

    if((u2_g_TYDC_DTC_MA_RFC_MAX     >  (U2)0U                         ) &&
       (u1_s_tydc_dtc_ma_rf_chk      == (U1)TYDC_DTC_MA_RF_CHK_RUN     ) &&
       (st_a_RSLT.verificationStatus != SECOC_VERIFICATIONSUCCESS      ) &&
       (st_a_RSLT.freshnessValueID   <  (U2)SECOC_RX_PDU_PROCESSING_MAX)){

        if(u2_s_tydc_dtc_ma_rf_cnt < (U2)U2_MAX){
            u2_s_tydc_dtc_ma_rf_cnt++;
        }

        if(u2_s_tydc_dtc_ma_rf_cnt >= u2_g_TYDC_DTC_MA_RFC_MAX){
            if(u2_s_tydc_dtc_ma_br_chk == (U2)TYDC_DTC_MA_BR_LAS){
                u1_s_tydc_dtc_mae_chk    = (U1)OXDC_DTC_TR_ACT;                    /* U2B74 */
                vd_s_TyDoCANDtcMaEvCapt_U2B74(st_a_RSLT.Ab_SecOCDataId);
                u1_s_tydc_dtc_mae_chk_ev = (U1)OXDC_DTC_TR_ACT;                    /* U2B11 */
                vd_s_TyDoCANDtcMaEvCapt_U2B11(st_a_RSLT, SduDataPtr, SduLength);
            }
            u2_s_tydc_dtc_ma_br_chk = (U2)TYDC_DTC_MA_BR_UNK;

            u1_t_ret = u1_g_Rim_ReadU4withStatus(u2_g_TYDC_DTC_MA_MAECNT_RIMID, &u4_t_data);
            if((u1_t_ret != (U1)RIM_RESULT_NG_DATA) && (u4_t_data < (U4)U4_MAX)){
                u4_t_data++;
                vd_g_Rim_WriteU4(u2_g_TYDC_DTC_MA_MAECNT_RIMID, u4_t_data);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcMaErCntClear(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcMaErCntClear(void)
{
    U4              u4_t_maecnt;

    u4_t_maecnt = (U4)0U;
    (void)u1_g_NWCMWriteData(u1_g_TYDC_DTC_MA_MAECNT_NWCMID, (U1*)&u4_t_maecnt, (U1)TYDC_DTC_MA_NWCM_MAECNT_SIZE);
    vd_g_Rim_WriteU4(u2_g_TYDC_DTC_MA_MAECNT_RIMID, u4_t_maecnt);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfMaCanId(uint8 * u1_ap_canid, Dem_MonitorDataType u4_a_mon)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANAubIfMaCanId(uint8 * u1_ap_canid, Dem_MonitorDataType u4_a_mon)
{
    U2              u2_t_canid;

    if((u1_ap_canid != vdp_PTR_NA) &&
       (u1_s_tydc_dtc_ma_id_ref < (U1)TYDC_DTC_MA_NUM_REC_AB_U2B74)){
        u2_t_canid  = u2_sp_tydc_dtc_ma_id_idx[u1_s_tydc_dtc_ma_id_ref];
        u1_ap_canid[0] = (U1)(u2_t_canid >> 8U);
        u1_ap_canid[1] = (U1)(u2_t_canid & (U4)0x000000ffU);
    }
    return((uint8)E_OK);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcMaSynchk(const U1 u1_a_IGN_ON)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcMaSynchk(const U1 u1_a_IGN_ON)
{
    U1                         u1_t_chk;

    if(u1_a_IGN_ON != (U1)OXDC_EOM_IGN_ON){
        u2_s_tydc_dtc_ma_syn_elpsd = (U2)TYDC_DTC_MA_SYN_INA;
    }
    else if(u2_s_tydc_dtc_ma_syn_elpsd >= (U2)TYDC_DTC_MA_SYN_INA){
        u2_s_tydc_dtc_ma_syn_elpsd = (U2)0U;
        u1_s_tydc_dtc_ma_syn_chk   = (U1)0U;
        u1_s_tydc_dtc_ma_syn_cnt   = (U1)0U;
    }
    else if(u2_s_tydc_dtc_ma_syn_elpsd >= (U2)TYDC_DTC_MA_SYN_MAX){
        u2_s_tydc_dtc_ma_syn_elpsd = (U2)TYDC_DTC_MA_SYN_MAX;
    }
    else{
        u2_s_tydc_dtc_ma_syn_elpsd++;
    }

    if(u2_s_tydc_dtc_ma_syn_elpsd == u2_g_TYDC_DTC_MA_SYN_TOUT){
        if(u1_s_tydc_dtc_ma_syn_cnt < (U1)TYDC_DTC_MA_SYN_VRFY_MAX){
            u1_t_chk = ((U1)TYDC_DTC_U2302_EV_CAPT >> u1_s_tydc_dtc_ma_syn_chk) & (U1)TRUE;
            if(u1_t_chk == (U1)TRUE){
                u1_s_tydc_dtc_kup_chk = (U1)OXDC_DTC_TR_ACT;
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcMaRfchk(const U1 u1_a_IGN_ON)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcMaRfchk(const U1 u1_a_IGN_ON)
{
    static const U1            u1_sp_TYDC_DTC_MA_RF_STM[] = {
        (U1)TYDC_DTC_MA_RF_ACT_TO_STA, (U1)TYDC_DTC_MA_RF_ACT_STA,    (U1)TYDC_DTC_MA_RF_ACT_RUN,
        (U1)TYDC_DTC_MA_RF_ACT_TO_STA, (U1)TYDC_DTC_MA_RF_ACT_STA,    (U1)TYDC_DTC_MA_RF_ACT_TO_RUN,
        (U1)TYDC_DTC_MA_RF_ACT_TO_STA, (U1)TYDC_DTC_MA_RF_ACT_STA,    (U1)TYDC_DTC_MA_RF_ACT_RUN,
        (U1)TYDC_DTC_MA_RF_ACT_TO_STA, (U1)TYDC_DTC_MA_RF_ACT_TO_RUN, (U1)TYDC_DTC_MA_RF_ACT_TO_RUN
    };

    static void ( * const      fp_sp_vd_TYDC_DTC_MA_RF_ACT[])(void) = {
        &vd_s_TydcDtcMaRf_ToSta,          /* TYDC_DTC_MA_RF_ACT_TO_STA  (0U) */
        &vd_s_TydcDtcMaRf_ToRun,          /* TYDC_DTC_MA_RF_ACT_TO_RUN  (1U) */
                                          /* TYDC_DTC_MA_RF_ACT_STA     (2U) */
                                          /* TYDC_DTC_MA_RF_ACT_RUN     (3U) */
    };

    U2                         u2_t_eas_chk;
    U2                         u2_t_tout;
    U2                         u2_t_act;
    U1                         u1_t_ena;

    if((u1_a_IGN_ON             != (U1)OXDC_EOM_IGN_ON       ) ||
       (u1_s_tydc_dtc_ma_rf_chk >= (U1)TYDC_DTC_MA_RF_NUM_CHK)){

        u2_s_tydc_dtc_ma_rf_cnt    = (U2)0U;
        u1_s_tydc_dtc_ma_rf_chk    = (U1)TYDC_DTC_MA_RF_CHK_INA;
    }
    else{

        if(u2_s_tydc_dtc_ma_rf_elpsd < (U2)U2_MAX){
            u2_s_tydc_dtc_ma_rf_elpsd++;
        }

        u2_t_tout = u2_gp_TYDC_DTC_MA_RF_TOUT[u1_s_tydc_dtc_ma_rf_chk];
        if((u1_s_tydc_dtc_ma_rf_chk == (U1)TYDC_DTC_MA_RF_CHK_RUN) &&
           (u2_t_tout               == (U2)0U                    )){
            u2_t_eas_chk  = (U2)0U;
        }
        else if(u2_s_tydc_dtc_ma_rf_elpsd >= u2_t_tout){
            u2_t_eas_chk  = (U2)TYDC_DTC_MA_RF_EAS_TOUT;
        }
        else{
            u2_t_eas_chk  = (U2)0U;
        }

        u1_t_ena = u1_g_TyDoCANDtcMaCfgRfcOdochk();
        if(u1_t_ena == (U1)TRUE){
            u2_t_eas_chk |= (U2)TYDC_DTC_MA_RF_EAS_RFC_ENA;
        }

        u2_t_act = (u2_t_eas_chk * (U2)TYDC_DTC_MA_RF_NUM_CHK) + (U2)u1_s_tydc_dtc_ma_rf_chk; 
        u2_t_act = (U2)u1_sp_TYDC_DTC_MA_RF_STM[u2_t_act];
        if(u2_t_act < (U2)TYDC_DTC_MA_RF_ACT_STA){
            (*fp_sp_vd_TYDC_DTC_MA_RF_ACT[u2_t_act])();
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcMaRf_ToSta(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcMaRf_ToSta(void)
{
    u2_s_tydc_dtc_ma_rf_elpsd  = (U2)0U;
    u2_s_tydc_dtc_ma_rf_cnt    = (U2)0U;
    u1_s_tydc_dtc_ma_rf_chk    = (U1)TYDC_DTC_MA_RF_CHK_STA;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcMaRf_ToRun(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcMaRf_ToRun(void)
{
    u2_s_tydc_dtc_ma_rf_elpsd  = (U2)0U;
    u2_s_tydc_dtc_ma_rf_cnt    = (U2)0U;
    u1_s_tydc_dtc_ma_rf_chk    = (U1)TYDC_DTC_MA_RF_CHK_RUN;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TyDoCANDtcMaEvCtxInit(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TyDoCANDtcMaEvCtxInit(void)
{
    st_s_tydc_dtc_ma_RSLT.Ab_SecOCDataId     = (U4)0U;
    st_s_tydc_dtc_ma_RSLT.freshnessValueID   = (U2)0U;
    st_s_tydc_dtc_ma_RSLT.verificationStatus = (SecOC_VerificationResultType)SECOC_VERIFICATIONSUCCESS;
    vd_g_MemfillU1(&(u1_sp_tydc_dtc_ma_SduData[0]), (U1)0U, (U4)TYDC_DTC_MA_SEC_TRNC_SIZE);
    st_s_tydc_dtc_ma_SduLength               = (PduLengthType)0U;
    u2_s_tydc_dtc_ma_ev_cnt                  = (U2)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TyDoCANDtcMaIdCtxInit(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TyDoCANDtcMaIdCtxInit(void)
{
    vd_g_MemfillU2(&(u2_sp_tydc_dtc_ma_id_idx[0]), (U2)U2_MAX, (U4)TYDC_DTC_MA_NUM_REC_AB_U2B74);
    u1_s_tydc_dtc_ma_id_cnt           = (U1)0U;
    u1_s_tydc_dtc_ma_id_next          = (U1)0U; 
    u1_s_tydc_dtc_ma_id_ref           = (U1)0U; 
}
/*===================================================================================================================================*/
/*  static void    vd_s_TyDoCANDtcMaEvCapt_U2B74(const U4 u4_a_CANID)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TyDoCANDtcMaEvCapt_U2B74(const U4 u4_a_CANID)
{
    if(u1_s_tydc_dtc_ma_id_cnt < (U1)U1_MAX){
        u1_s_tydc_dtc_ma_id_cnt++;
    }

    if(u1_s_tydc_dtc_ma_id_next >= (U1)TYDC_DTC_MA_NUM_REC_AB_U2B74){
        u1_s_tydc_dtc_ma_id_next = (U1)0U;
    }
    u2_sp_tydc_dtc_ma_id_idx[u1_s_tydc_dtc_ma_id_next] = (U2)(u4_a_CANID & 0x0000FFFFU);
    u1_s_tydc_dtc_ma_id_next++;
}
/*===================================================================================================================================*/
/* static void vd_s_TyDoCANDtcMaEvCapt_U2B11                                                                                         */
/*                          (const SecOC_VerificationStatusType st_a_RSLT, const uint8* SduDataPtr, PduLengthType SduLength)         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TyDoCANDtcMaEvCapt_U2B11(const SecOC_VerificationStatusType st_a_RSLT, const uint8* SduDataPtr, PduLengthType SduLength)
{
    U4      u4_t_idx;

    if(u2_s_tydc_dtc_ma_ev_cnt == (U2)0U){
        st_s_tydc_dtc_ma_RSLT.Ab_SecOCDataId = st_a_RSLT.Ab_SecOCDataId;
        st_s_tydc_dtc_ma_RSLT.freshnessValueID = st_a_RSLT.freshnessValueID;
        st_s_tydc_dtc_ma_RSLT.verificationStatus = st_a_RSLT.verificationStatus;
        if(SduLength <= (U4)TYDC_DTC_MA_SEC_TRNC_SIZE){
            u4_t_idx = (U1)0U;
            st_s_tydc_dtc_ma_SduLength = SduLength;
        }
        else{
            u4_t_idx = SduLength - (U4)TYDC_DTC_MA_SEC_TRNC_SIZE;
            st_s_tydc_dtc_ma_SduLength = (U4)TYDC_DTC_MA_SEC_TRNC_SIZE;
        }
        vd_g_MemcpyU1(&(u1_sp_tydc_dtc_ma_SduData[0U]), &(SduDataPtr[u4_t_idx]), st_s_tydc_dtc_ma_SduLength);
    }
    if(u2_s_tydc_dtc_ma_ev_cnt < (U2)U2_MAX){
        u2_s_tydc_dtc_ma_ev_cnt++;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcMaResume(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcMaResume(void)
{
    u2_s_tydc_dtc_ma_br_chk      = (U2)TYDC_DTC_MA_BR_LAS;
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     9/14/2023  MI       New                                                                                                */
/*                                                                                                                                   */
/*  * MI   = Masahiko Izumi, DENSO                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
