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
#define COM_IPDUGROUP_USER30            (BSW_COM_IPDUGROUP_USER30)
#define COM_IPDUGROUP_USER31            (BSW_COM_IPDUGROUP_USER31)
#define COM_IPDUGROUP_USER32            (BSW_COM_IPDUGROUP_USER32)
#define COM_IPDUGROUP_USER33            (BSW_COM_IPDUGROUP_USER33)
#define COM_IPDUGROUP_USER34            (BSW_COM_IPDUGROUP_USER34)
#define COM_IPDUGROUP_USER35            (BSW_COM_IPDUGROUP_USER35)
#define COM_IPDUGROUP_USER36            (BSW_COM_IPDUGROUP_USER36)
#define COM_IPDUGROUP_USER37            (BSW_COM_IPDUGROUP_USER37)
#define COM_IPDUGROUP_USER38            (BSW_COM_IPDUGROUP_USER38)
#define COM_IPDUGROUP_USER39            (BSW_COM_IPDUGROUP_USER39)
#define COM_IPDUGROUP_USER40            (BSW_COM_IPDUGROUP_USER40)
#define COM_IPDUGROUP_USER41            (BSW_COM_IPDUGROUP_USER41)
#define COM_IPDUGROUP_USER42            (BSW_COM_IPDUGROUP_USER42)
#define COM_IPDUGROUP_USER43            (BSW_COM_IPDUGROUP_USER43)
#define COM_IPDUGROUP_USER44            (BSW_COM_IPDUGROUP_USER44)
#define COM_IPDUGROUP_USER45            (BSW_COM_IPDUGROUP_USER45)
#define COM_IPDUGROUP_USER46            (BSW_COM_IPDUGROUP_USER46)
#define COM_IPDUGROUP_USER47            (BSW_COM_IPDUGROUP_USER47)
#define COM_IPDUGROUP_USER48            (BSW_COM_IPDUGROUP_USER48)
#define COM_IPDUGROUP_USER49            (BSW_COM_IPDUGROUP_USER49)
#define COM_IPDUGROUP_USER50            (BSW_COM_IPDUGROUP_USER50)
#define COM_IPDUGROUP_USER51            (BSW_COM_IPDUGROUP_USER51)
#define COM_IPDUGROUP_USER52            (BSW_COM_IPDUGROUP_USER52)
#define COM_IPDUGROUP_USER53            (BSW_COM_IPDUGROUP_USER53)
#define COM_IPDUGROUP_USER54            (BSW_COM_IPDUGROUP_USER54)
#define COM_IPDUGROUP_USER55            (BSW_COM_IPDUGROUP_USER55)
#define COM_IPDUGROUP_USER56            (BSW_COM_IPDUGROUP_USER56)
#define COM_IPDUGROUP_USER57            (BSW_COM_IPDUGROUP_USER57)
#define COM_IPDUGROUP_USER58            (BSW_COM_IPDUGROUP_USER58)
#define COM_IPDUGROUP_USER59            (BSW_COM_IPDUGROUP_USER59)
#define COM_IPDUGROUP_USER60            (BSW_COM_IPDUGROUP_USER60)
#define COM_IPDUGROUP_USER61            (BSW_COM_IPDUGROUP_USER61)

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
/*  v3-0-0          :2025/03/12                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
