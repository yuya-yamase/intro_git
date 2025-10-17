/* SecOC_Cfg_h_v2-1-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Cfg/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/

#ifndef SECOC_CFG_H
#define SECOC_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "SecOC_CfgStd.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define SECOC_DEV_ERROR_DETECT (STD_OFF)
#define SECOC_VERSION_INFO_API (STD_OFF)
#define SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING (STD_OFF)
#define SECOC_AB_TRIAL_WORK (STD_OFF)
#define SECOC_ENABLE_FORCED_PASS_OVERRIDE (STD_OFF)
#define SECOC_OVERRIDE_STATUS_WITH_DATA_ID (STD_OFF)
#define SECOC_RX_PDU_PROCESSING (STD_OFF)
#define SECOC_TX_PDU_PROCESSING (STD_ON)
#define SECOC_AB_EXTENDED_ENABLE (STD_ON)
#define SECOC_AB_EXTD_INIT (STD_ON)
#define SECOC_AB_EXTD_DEINIT (STD_ON)
#define SECOC_AB_EXTD_VERIFY_STATUS_OVERRIDE (STD_ON)
#define SECOC_AB_EXTD_TRANSMIT (STD_OFF)
#define SECOC_AB_EXTD_BUS_RESET (STD_OFF)
#define SECOC_AB_EXTD_MAIN_FUNC_PERIOD_TX (STD_OFF)
#define SECOC_AB_EXTD_MAIN_FUNC_PERIOD_RX (STD_OFF)
#define SECOC_AB_EXTD_FV_UPDATE_JUDGE (STD_ON)
#define SECOC_AB_EXTD_MSG_NOTIFY_JUDGE (STD_ON)
#define SECOC_AB_EXTD_VERIFICATION_FINAL_STATUS (STD_OFF)
#define SECOC_AB_EXTD_AFTER_ASYNC_NOTIFY_TX (STD_OFF)
#define SECOC_AB_EXTD_AFTER_ASYNC_NOTIFY_RX (STD_OFF)
#define SECOC_AB_EXTD_AFTER_GET_RX_FV (STD_OFF)
#define SECOC_AB_EXTD_PRE_VER_OK_NOTIFY (STD_OFF)
#define SECOC_AB_EXTD_AFTER_MAC_GENERATE (STD_OFF)
#define SECOC_AB_EXTD_MEMUTIL (STD_OFF)

#define SECOC_AB_FORCE_RECEIVE (STD_OFF)
#define SECOC_AB_FIXED_MESSAGE_SIZE (STD_OFF)
#define SECOC_AB_TRANSMIT_CONDITION_CHECK (STD_OFF)
#define SECOC_AB_EQUIVALENT_FV_VERIFY (STD_OFF)
#define SECOC_AB_EARLY_TXCNF (STD_OFF)
#define SECOC_AB_RAM_ERROR_CHK (STD_OFF)
#define SECOC_AB_INTERFACE_PARAM_DETAIL_CHK (STD_ON)
#define SECOC_AB_MSG_AUTH_19PF_COMPATIBILITY (STD_OFF)
#define SECOC_DEFAULT_AUTH_INFO (STD_OFF)
#define SECOC_AB_CACHE_ALIGN_TX_AUTHINFO (16U)
#define SECOC_AB_CACHE_ALIGN_TX_AUTHSIZE (4U)
#define SECOC_AB_CACHE_ALIGN_RX_AUTHINFO (16U)
#define SECOC_AB_CACHE_ALIGN_RX_VERIFYRESULT (1U)
#define SECOC_VERIFICATION_STATUS_CALLOUT_MAX (0U)
#define SECOC_AB_FULL_FRESHNESS_VALUE_CALLOUT_MAX (1U)
#define SECOC_AB_REPORT_ERROR_CALLOUT_MAX (0U)
#define SECOC_JOBID_2_MSG_TBL_IDX_MAX (16U)

#define SECOC_RX_BUFFER_LENGTH_TOTAL (0U)
#define SECOC_TX_BUFFER_LENGTH_TOTAL (896U)
#define SECOC_AB_TRIP_CNT_LENGTH (16U)
#define SECOC_AB_RESET_CNT_LENGTH (20U)
#define SECOC_AB_MSG_CNT_LENGTH (8U)
#define SECOC_AB_RESET_FLAG_LENGTH (2U)
#define SECOC_AB_FULLFV_TRIP_CNT_LENGTH (24U)
#define SECOC_AB_FULLFV_MSG_CNT_LENGTH (32U)
#define SECOC_TX_INPUT_DATA_LENGTH_TOTAL (896U)
#define SECOC_AB_TX_PDU_TRUNCFV_MAX (0U)
#define SECOC_AB_RX_PDU_TRUNCFV_MAX (0U)
#define SECOC_AB_TX_PDU_FULLFV_MAX (16U)
#define SECOC_AB_RX_PDU_FULLFV_MAX (0U)
#define SECOC_AB_BUS_TRUNC_MAX (0U)
#define SECOC_AB_BUS_FULL_MAX (4U)
#define SECOC_AB_TX_FV_BUFF_SIZE (8U)

#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SB7_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (0U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SC1_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (1U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SC2_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (2U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SC3_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (3U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SC4_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (4U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SC5_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (5U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SC6_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (6U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SC7_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (7U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SC8_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (8U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SC9_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (9U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SD1_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (10U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SD2_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (11U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_AVN1SD3_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (12U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_CDC1S01_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (13U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_MET1S30_Tx_CANFD_G2M_1_BUS_Tx_CANFD_G2M_1_BUS (14U)
#define SecOCConf_SecOCTxAuthenticPduLayer_Auth_MET1S44_Tx_CANFD_G5M_BUS_Tx_CANFD_G5M_BUS (15U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SB7_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (0U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SC1_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (1U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SC2_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (2U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SC3_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (3U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SC4_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (4U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SC5_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (5U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SC6_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (6U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SC7_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (7U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SC8_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (8U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SC9_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (9U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SD1_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (10U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SD2_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (11U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_AVN1SD3_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (12U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_CDC1S01_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (13U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_MET1S30_Tx_CANFD_G2M_1_BUS_SPDU_Tx_CANFD_G2M_1_BUS (14U)
#define SecOCConf_SecOCTxSecuredPdu_SecuPdu_MET1S44_Tx_CANFD_G5M_BUS_SPDU_Tx_CANFD_G5M_BUS (15U)



/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>
FUNC(void, SECOC_CODE) SecOC_Config_Init
(
    P2CONST(SecOC_ConfigType, AUTOMATIC, SECOC_APPL_DATA) SecOC_ConfigData
);
#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CONST_CONFIG
#include <SecOC_MemMap.h>
extern CONST(SecOC_SPduTxConfirmationType, SECOC_CONST_CONFIG) SecOC_Ab_FullFVCallout[SECOC_AB_FULL_FRESHNESS_VALUE_CALLOUT_MAX];
extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_ProcessingCount;
extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_TxProcessingCount;
extern CONST(uint32, SECOC_CONST_CONFIG) SecOC_Ab_RxAuthTpCopyTotalSize;
extern CONST(uint32, SECOC_CONST_CONFIG) SecOC_Ab_TxAuthTpCopyTotalSize;
extern CONST(SecOC_TxPduProcessingType, SECOC_CONST_CONFIG) SecOC_TxPduProcessing[SECOC_TX_PDU_PROCESSING_MAX];
extern CONST(SecOC_Ab_BusCollectionType, SECOC_CONST_CONFIG) SecOC_Ab_BusCollection[SECOC_AB_BUS_MAX];
extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_JobId2MsgTblIdx[SECOC_JOBID_2_MSG_TBL_IDX_MAX];
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_RxPduProcessingMax;
#endif
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_TxPduProcessingMax;
#endif
#if (SECOC_VERIFICATION_STATUS_CALLOUT_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_VerStaCoMax;
#endif
extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_BusMax;
#if (SECOC_AB_BUS_FULL_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_BusFullMax;
#endif
#if (SECOC_AB_BUS_TRUNC_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_BusTruncMax;
#endif
#if (SECOC_AB_FULL_FRESHNESS_VALUE_CALLOUT_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_FullFvCoMax;
#endif
#if (SECOC_AB_REPORT_ERROR_CALLOUT_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_RepErrCoMax;
#endif
#if (SECOC_AB_RX_PDU_FULLFV_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_RxPduFullFvMax;
#endif
#if (SECOC_AB_TX_PDU_FULLFV_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_TxPduFullFvMax;
#endif
#if (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_RxPduTruncFvMax;
#endif
#if (SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_TxPduTruncFvMax;
#endif
#if (SECOC_AB_RXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_RxMsgBusyDestCoMax;
#endif
#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_TxMsgBusyDestCoMax;
#endif
#if (SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_RxMsgOvfDestCoMax;
#endif
#if (SECOC_AB_VERIFICATION_FINAL_STATUS_CALLOUT_MAX > 0U)
    extern CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_VerFinStaCoMax;
#endif
#if (SECOC_DEFAULT_AUTH_INFO == STD_ON)
    extern CONST(uint8, SECOC_CONST_CONFIG) SecOC_DefaultAuthInfoPattern;
#endif
#if ((SECOC_AB_RX_SECURED_MSG_IN_BUS_COUNT_MAX > 0U) || (SECOC_AB_TX_SECURED_MSG_IN_BUS_COUNT_MAX > 0U))
    extern CONST(SecOC_Ab_BusId2SecuredMsgIdxType, SECOC_CONST_CONFIG) SecOC_Ab_BusId2SecuredMsgIdxLists[SECOC_AB_BUS_MAX];
#endif
#define SECOC_STOP_SEC_CONST_CONFIG
#include <SecOC_MemMap.h>


#endif /* SECOC_CFG_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

