/* com_h_v2-1-0                                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | COM/HEADER                                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_COM_AR_H
#define BSW_COM_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <com/bsw_com_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define COM_UNINIT                      (BSW_COM_UNINIT)
#define COM_INIT                        (BSW_COM_INIT)

#define COM_SERVICE_NOT_AVAILABLE       (BSW_COM_SERVICE_NOT_AVAILABLE)
#define COM_BUSY                        (BSW_COM_BUSY)
#define COM_INVALID                     (BSW_COM_INVALID)
#define COM_FIRST_RX                    (BSW_COM_FIRST_RX)

#define COM_TX_MODE_PERIODIC            (BSW_COM_TX_MODE_PERIODIC)
#define COM_TX_MODE_EVENT               (BSW_COM_TX_MODE_EVENT)
#define COM_TX_MODE_ALL                 (BSW_COM_TX_MODE_ALL)
#define COM_TX_MODE_INVALID             (BSW_COM_TX_MODE_INVALID)

#define COM_TRX_START                   (BSW_COM_TRX_START)
#define COM_FAILINIT                    (BSW_COM_FAILINIT)
#define COM_TXSTOP                      (BSW_COM_TXSTOP)
#define COM_TIMEOUT                     (BSW_COM_TIMEOUT)
#define COM_NO_RX                       (BSW_COM_NO_RX)

#define COM_DATATYPE_S                  (BSW_COM_DATATYPE_S)
#define COM_DATATYPE_U                  (BSW_COM_DATATYPE_U)

#define COM_TX_DISABLE                  (BSW_COM_TX_DISABLE)
#define COM_PERIODIC_TX_ENABLE          (BSW_COM_PERIODIC_TX_ENABLE)
#define COM_EVENT_TX_ENABLE             (BSW_COM_EVENT_TX_ENABLE)

/* Vendor ID */
#define COM_VENDOR_ID                   (BSW_COM_VENDOR_ID)

/* Module ID */
#define COM_MODULE_ID                   (BSW_COM_MODULE_ID)

/* AUTOSAR Release Version */
#define COM_AR_RELEASE_MAJOR_VERSION    (BSW_COM_AR_RELEASE_MAJOR_VERSION)
#define COM_AR_RELEASE_MINOR_VERSION    (BSW_COM_AR_RELEASE_MINOR_VERSION)
#define COM_AR_RELEASE_REVISION_VERSION (BSW_COM_AR_RELEASE_REVISION_VERSION)

/* Vendor Specification Version */
#define COM_SW_MAJOR_VERSION            (BSW_COM_SW_MAJOR_VERSION)
#define COM_SW_MINOR_VERSION            (BSW_COM_SW_MINOR_VERSION)
#define COM_SW_PATCH_VERSION            (BSW_COM_SW_PATCH_VERSION)

/* Frame ID */
#define COM_INVALID_FRAME_ID            (BSW_COM_INVALID_FRAME_ID)

/* Function */
#define Com_Init                        (bsw_com_st_Init)
#define Com_Wakeup                      (bsw_com_st_Wakeup)
#define Com_DeInit                      (bsw_com_st_Shutdown)
#define Com_Sleep                       (bsw_com_st_Sleep)
#define Com_Reset                       (bsw_com_st_Reset)
#define Com_IpduGroupControl            (bsw_com_ctrl_IpduGroupCtrl)
#define Com_ClearIpduGroupVector        (bsw_com_ctrl_ClearIpduGroup)
#define Com_SetIpduGroup                (bsw_com_ctrl_SetIpduGroup)
#define Com_ReceptionDMControl          (bsw_com_rx_ReceptionDMCtrl)
#define Com_GetVersionInfo              (bsw_com_st_GetVersionInfo)
#define Com_TriggerIPDUSend             (bsw_com_tx_SetTxReq)
#define Com_ImmTriggerIPDUSend          (bsw_com_tx_ImmSetTxReq)
#define Com_TriggerPeriodicIPDUSend     (bsw_com_tx_SetPeriTxReq)
#define Com_SwitchIpduTxMode            (bsw_com_tx_SwitchIpduTxMode)
#define Com_TriggerTransmit             (bsw_com_tx_TriggerTransmit)
#define Com_RxIndication                (bsw_com_rx_ReceiveIndication)
#define Com_TpRxIndication              (bsw_com_rx_TpRxIndication)
#define Com_TxConfirmation              (bsw_com_tx_TxConfirmation)
#define Com_TpTxConfirmation            (bsw_com_tx_TpTransmitCfm)
#define Com_StartOfReception            (bsw_com_rx_StartOfReception)
#define Com_CopyRxData                  (bsw_com_rx_CopyRxData)
#define Com_CopyTxData                  (bsw_com_tx_CopyTxData)
#define Com_MainFunctionRx              (bsw_com_rx_MainFunctionRx)
#define Com_MainFunctionTx              (bsw_com_tx_MainFunctionTx)
#define Com_WriteIPDU                   (bsw_com_data_WriteMsg)
#define Com_InitIPDU                    (bsw_com_data_SetInitMsg)
#define Com_InitIPDUStatus              (bsw_com_data_SetInitMsgStatus)
#define Com_SendSignalB                 (bsw_com_data_SendSignalB)
#define Com_SendSignalL                 (bsw_com_data_SendSignalL)
#define Com_SendSignalEvB               (bsw_com_data_SendSignalEvB)
#define Com_SendSignalEvL               (bsw_com_data_SendSignalEvL)
#define Com_ReceiveSignalB              (bsw_com_data_ReceiveSignalB)
#define Com_ReceiveSignalL              (bsw_com_data_ReceiveSignalL)
#define Com_WriteIPDUMskTxCnt           (bsw_com_data_WriteIpduMskTxCnt)
#define Com_SendIPDU                    (bsw_com_data_SendIPDU)
#define Com_SendIPDUMskTxCnt            (bsw_com_data_SendIPDUMskTxCnt)
#define Com_ReadIPDU                    (bsw_com_data_ReadMsg)
#define Com_ReadIPDUSize                (bsw_com_data_GetMsgSize)
#define Com_GetFrameID                  (bsw_com_data_GetFrameID)
#define Com_SetTickTime                 (bsw_com_rx_SetTickTime)
#define Com_GetTickTimeConfig           (bsw_com_rx_GetTickTimeConfig)
#define Com_StopTxIPDU                  (bsw_com_tx_StopTx)
#define Com_ResumeTxIPDU                (bsw_com_tx_ResumeTx)
#define Com_GetSignalStatus             (bsw_com_data_GetDataStat)
#define Com_GetIPDUStatus               (bsw_com_data_GetMsgStat)
#define Com_ClearTickTime               (bsw_com_rx_ClearTickTime)
#define Com_FailInitIPDU                (bsw_com_data_FailInitMsg)
#define Com_ClearTxIpdu                 (bsw_com_tx_ClearTxIpdu)
#define Com_CancelTxIpdu                (bsw_com_tx_CancelTxIpdu)
#define Com_GetBackupIPDU               (bsw_com_data_GetBackupIPDU)
#define Com_SetBackupIPDU               (bsw_com_data_SetBackupIPDU)
#define Com_SndSgnlGrpArry              (bsw_com_data_SndSgnlGrpArry)
#define Com_SndSgnlGrpArryEv            (bsw_com_data_SndSgnlGrpArryEv)
#define Com_RcvSgnlGrpArry              (bsw_com_data_RcvSgnlGrpArry)
#define Com_GetStatus                   (bsw_com_st_GetStatus)
#define Com_SendSignalB64               (bsw_com_data_SendSignalB64)
#define Com_SendSignalL64               (bsw_com_data_SendSignalL64)
#define Com_SendSignalEvB64             (bsw_com_data_SendSignalEvB64)
#define Com_SendSignalEvL64             (bsw_com_data_SendSignalEvL64)
#define Com_ReceiveSignalB64            (bsw_com_data_ReceiveSignalB64)
#define Com_ReceiveSignalL64            (bsw_com_data_ReceiveSignalL64)
#define Com_SendSignalBOvA              (bsw_com_data_SendSignalBOvA)
#define Com_SendSignalLOvA              (bsw_com_data_SendSignalLOvA)
#define Com_SendSignalEvBOvA            (bsw_com_data_SendSignalEvBOvA)
#define Com_SendSignalEvLOvA            (bsw_com_data_SendSignalEvLOvA)
#define Com_SendSignalB64OvA            (bsw_com_data_SendSignalB64OvA)
#define Com_SendSignalL64OvA            (bsw_com_data_SendSignalL64OvA)
#define Com_SendSignalEvB64OvA          (bsw_com_data_SendSignalEvB64OvA)
#define Com_SendSignalEvL64OvA          (bsw_com_data_SendSignalEvL64OvA)
#define Com_ReceiveSignalBOvA           (bsw_com_data_ReceiveSignalBOvA)
#define Com_ReceiveSignalLOvA           (bsw_com_data_ReceiveSignalLOvA)
#define Com_ReceiveSignalB64OvA         (bsw_com_data_ReceiveSignalB64OvA)
#define Com_ReceiveSignalL64OvA         (bsw_com_data_ReceiveSignalL64OvA)

/* Function:Callback  */
#define Com_CbkClrIPDUGrpTxReq          (bsw_com_tx_TxReqClear)
#define Com_CbkStartIPDU                (bsw_com_ctrl_CbkStartIPDU)
#define Com_CbkStopIPDU                 (bsw_com_ctrl_CbkStopIPDU)
#define Com_CbkRxAck                    (bsw_com_rx_RxMsg)
#define Com_RxIpduCallout               (bsw_com_rx_PreStoreMsg)
#define Com_CbkRxTOut                   (bsw_com_rx_TimeoutMsg)
#define Com_CbkTxTOut                   (bsw_com_tx_TimeoutTxMsg)
#define Com_CbkPreEventTxReq            (bsw_com_tx_PreEventTxReq)
#define Com_CbkCounterErr               (bsw_com_fs_RxAliveCounter)
#define Com_CbkTxReq                    (bsw_com_tx_CbkTxReq)
#define Com_CbkTxAck                    (bsw_com_tx_CbkTxAck)
#define Com_CbkTxErr                    (bsw_com_tx_CbkTxErr)
#define Com_CbkPrePeriodicTxRetrigger   (bsw_com_tx_CbkPrePeriTxRtrgr)
#define Com_TxIpduCallout               (bsw_com_tx_PreTxIpdu)
#define Com_TriggerTransmitIpduCallout  (bsw_com_tx_PreTrgTxIPdu)
#define Com_CbkSetTxStatus              (bsw_com_tx_CbkSetStatus)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define Com_StatusType              Bsw_Com_StatusType
#define Com_SignalIdType            Bsw_Com_SignalIdType
#define Com_SignalGroupIdType       Bsw_Com_SignalGroupIdType
#define Com_IpduGroupIdType         Bsw_Com_IpduGroupIdType
#define Com_IpduGroupVector         Bsw_Com_IpduGroupVector
#define Com_ServiceIdType           Bsw_Com_ServiceIdType
#define Com_ConfigType              Bsw_Com_ConfigType
#define Com_TxModeType              Bsw_Com_TxModeType
#define Com_DataHandlerType         Bsw_Com_DataHandlerType
#define Com_MsgOffsetType           Bsw_Com_MsgOffsetType
#define Com_MsgSizeType             Bsw_Com_MsgSizeType
#define Com_IpduStatusType          Bsw_Com_IpduStatusType
#define Com_TxStatusType            Bsw_Com_TxStatusType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_COM_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/05/15                                             */
/*  v1-1-0          :2018/09/14                                             */
/*  v1-2-0          :2019/09/27                                             */
/*  v2-0-0          :2021/06/24                                             */
/*  v2-1-0          :2022/09/05                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
