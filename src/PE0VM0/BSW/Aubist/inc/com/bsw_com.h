/* bsw_com_h_v2-2-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COM/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_COM_H
#define BSW_COM_H

#include <Com.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define COM_IPDUGROUP_NONE              (0x00U)
#define COM_IPDUGROUP_BAT               (0x01U)
#define COM_IPDUGROUP_ACC               (0x02U)
#define COM_IPDUGROUP_IG                (0x04U)
#define COM_IPDUGROUP_USER1             (0x08U)
#define COM_IPDUGROUP_USER2             (0x10U)
#define COM_IPDUGROUP_USER3             (0x20U)
#define COM_IPDUGROUP_USER4             (0x40U)
#define COM_IPDUGROUP_USER5             (0x80U)

/* Function */
#define Com_SetTxStatus                 (bsw_com_tx_SetStatus)
#define Com_ResetPeriodicTx             (bsw_com_tx_ResetPeriodicTx)
#define Com_SetWakeupMask               (bsw_com_rx_SetWakeupMask)
#define Com_CheckRam                    (bsw_com_fs_CheckRam)
#define Com_GetCurrentTxMode            (bsw_com_tx_GetCurentTxMode)
#define Com_SetRxTickTime               (bsw_com_rx_SetRxTickTime)
#define Com_ClearNonAwakeEvtTxIpdu      (bsw_com_tx_ClearNonAwakeEvt)
#define Com_StartChangePeriodCh         (bsw_com_tx_StartChangePeriodCh)
#define Com_StopChangePeriodCh          (bsw_com_tx_StopChangePeriodCh)
#define Com_PncIpduGroupControl         (bsw_com_ctrl_PncIpduGroupCtrl)
#define Com_PncReceptionDMControl       (bsw_com_rx_PncReceptionDMCtrl)
#define Com_SetPncIpduGroupTxStatus     (bsw_com_tx_SetPncIpduGrpTxSts)
#define Com_SetFirstTxStatus            (bsw_com_tx_SetFirstTxStatus)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define Com_SysStatusType           Bsw_Com_SysStatusType
#define Com_PncIpduGroupVector      Bsw_Com_PncIpduGroupVector

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_COM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/06/24                                             */
/*  v2-1-0          :2022/05/16                                             */
/*  v2-2-0          :2022/05/23                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
