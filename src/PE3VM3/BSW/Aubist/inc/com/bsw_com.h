/* bsw_com_h_v3-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
#define COM_IPDUGROUP_NONE              (BSW_COM_IPDUGROUP_NONE)
#define COM_IPDUGROUP_BAT               (BSW_COM_IPDUGROUP_BAT)
#define COM_IPDUGROUP_ACC               (BSW_COM_IPDUGROUP_ACC)
#define COM_IPDUGROUP_IG                (BSW_COM_IPDUGROUP_IG)
#define COM_IPDUGROUP_USER1             (BSW_COM_IPDUGROUP_USER1)
#define COM_IPDUGROUP_USER2             (BSW_COM_IPDUGROUP_USER2)
#define COM_IPDUGROUP_USER3             (BSW_COM_IPDUGROUP_USER3)
#define COM_IPDUGROUP_USER4             (BSW_COM_IPDUGROUP_USER4)
#define COM_IPDUGROUP_USER5             (BSW_COM_IPDUGROUP_USER5)
#define COM_IPDUGROUP_USER6             (BSW_COM_IPDUGROUP_USER6)
#define COM_IPDUGROUP_USER7             (BSW_COM_IPDUGROUP_USER7)
#define COM_IPDUGROUP_USER8             (BSW_COM_IPDUGROUP_USER8)
#define COM_IPDUGROUP_USER9             (BSW_COM_IPDUGROUP_USER9)
#define COM_IPDUGROUP_USER10            (BSW_COM_IPDUGROUP_USER10)
#define COM_IPDUGROUP_USER11            (BSW_COM_IPDUGROUP_USER11)
#define COM_IPDUGROUP_USER12            (BSW_COM_IPDUGROUP_USER12)
#define COM_IPDUGROUP_USER13            (BSW_COM_IPDUGROUP_USER13)
#define COM_IPDUGROUP_USER14            (BSW_COM_IPDUGROUP_USER14)
#define COM_IPDUGROUP_USER15            (BSW_COM_IPDUGROUP_USER15)
#define COM_IPDUGROUP_USER16            (BSW_COM_IPDUGROUP_USER16)
#define COM_IPDUGROUP_USER17            (BSW_COM_IPDUGROUP_USER17)
#define COM_IPDUGROUP_USER18            (BSW_COM_IPDUGROUP_USER18)
#define COM_IPDUGROUP_USER19            (BSW_COM_IPDUGROUP_USER19)
#define COM_IPDUGROUP_USER20            (BSW_COM_IPDUGROUP_USER20)
#define COM_IPDUGROUP_USER21            (BSW_COM_IPDUGROUP_USER21)
#define COM_IPDUGROUP_USER22            (BSW_COM_IPDUGROUP_USER22)
#define COM_IPDUGROUP_USER23            (BSW_COM_IPDUGROUP_USER23)
#define COM_IPDUGROUP_USER24            (BSW_COM_IPDUGROUP_USER24)
#define COM_IPDUGROUP_USER25            (BSW_COM_IPDUGROUP_USER25)
#define COM_IPDUGROUP_USER26            (BSW_COM_IPDUGROUP_USER26)
#define COM_IPDUGROUP_USER27            (BSW_COM_IPDUGROUP_USER27)
#define COM_IPDUGROUP_USER28            (BSW_COM_IPDUGROUP_USER28)
#define COM_IPDUGROUP_USER29            (BSW_COM_IPDUGROUP_USER29)

/* Periodic Tx Reset Reason */
#define COM_RSTR_BUSWAKEUP              (BSW_COM_RSTR_BUSWAKEUP)
#define COM_RSTR_RESUMETX               (BSW_COM_RSTR_RESUMETX)

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
#define Com_BusWakeup                   (bsw_com_tx_BusWakeup)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
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
/*  v3-0-0          :2024/09/19                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
