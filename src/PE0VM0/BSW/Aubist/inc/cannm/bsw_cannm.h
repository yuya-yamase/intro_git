/* bsw_cannm_h_v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_H
#define BSW_CANNM_H

#include <nm/bsw_nmstack_types.h>
#include <CanNm.h>

#include <cannm/bsw_cannm_z.h>
#include <cannm/bsw_cannm_a.h>
#include <cannm/bsw_cannm_a2.h>
#include <cannm/bsw_cannm_b.h>
#include <cannm/bsw_cannm_c2.h>
#include <cannm/bsw_cannm_e.h>
#include <cannm/bsw_cannm_x.h>
#include <cannm/bsw_cannm_y.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CANNM_u1OK                         (BSW_CANNM_u1OK)
#define CANNM_u1NG                         (BSW_CANNM_u1NG)
#define CANNM_u1DRVFULL                    (BSW_CANNM_u1DRVFULL)
#define CANNM_u1DRVNG                      (BSW_CANNM_u1DRVNG)

/* Function */
#define CanNm_MainFunctionHigh             (bsw_cannm_ch_MainFunctionHigh)
#define CanNm_GetIPDUState                 (bsw_cannm_ch_GetIPDUState)
#define CanNm_SetBusOff                    (bsw_cannm_ch_SetBusOff)
#define CanNm_TransmitEvtWakeup            (bsw_cannm_ch_TransEvtWkup)
#define CanNm_CancelEvtWakeup              (bsw_cannm_ch_CancelEvtWkup)
#define CanNm_CheckRam                     (bsw_cannm_ch_CheckRam)

#define CanNm_GetTxConfirmedPdu            (bsw_cannm_ch_GetTxConfirmedPdu)
#define CanNm_GetTxCanID                   (bsw_cannm_ch_GetTxCanID)
#define CanNm_GetRxCanID                   (bsw_cannm_ch_GetRxCanID)

#define CanNm_Wakeup                       (bsw_cannm_ch_Wakeup)
#define CanNm_Sleep                        (bsw_cannm_ch_Sleep)
#define CanNm_CheckAwake                   (bsw_cannm_ch_CheckAwake)
#define CanNm_GetBackupData                (bsw_cannm_ch_GetBackupData)
#define CanNm_SetBackupData                (bsw_cannm_ch_SetBackupData)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_CANNM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/09/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
