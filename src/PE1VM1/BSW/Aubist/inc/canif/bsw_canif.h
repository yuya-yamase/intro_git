/* bsw_canif_h_v3-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW_CANIF/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_CANIF_H
#define     BSW_CANIF_H

#include <pdur/bsw_pdur_canif.h>
#include <canif/bsw_can_generaltypes.h>
#include <CanIf.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CANIF_FAIL_NONE                 (BSW_CANIF_FAIL_NONE)
#define CANIF_FAIL_BUSOFF               (BSW_CANIF_FAIL_BUSOFF)
#define CANIF_FAIL_SNDLOCK              (BSW_CANIF_FAIL_SNDLOCK)
#define CANIF_FAIL_RCVLOCK              (BSW_CANIF_FAIL_RCVLOCK)
#define CANIF_FAIL_REGCHECK             (BSW_CANIF_FAIL_REGCHECK)
#define CANIF_FAIL_UNUSEDREGCHK         (BSW_CANIF_FAIL_UNUSEDREGCHK)
#define CANIF_FAIL_MPU                  (BSW_CANIF_FAIL_MPU)
#define CANIF_FAIL_INITNG               (BSW_CANIF_FAIL_INITNG)
#define CANIF_FAIL_USER                 (BSW_CANIF_FAIL_USER)
#define CANIF_FAIL_NMTXTIMEOUT_STABLE   (BSW_CANIF_FAIL_NMTXTIMEOUT_STABLE)
#define CANIF_FAIL_NMTXTIMEOUT_UNSTABLE (BSW_CANIF_FAIL_NMTXTIMEOUT_UNSTABLE)

#define CANIF_KIND_NMTXTIMEOUT_STABLE   (BSW_CANIF_KIND_NMTXTIMEOUT_STABLE)
#define CANIF_KIND_NMTXTIMEOUT_UNSTABLE (BSW_CANIF_KIND_NMTXTIMEOUT_UNSTABLE)

#define CANIF_EDGE_NONE                 (BSW_CANIF_EDGE_NONE)
#define CANIF_EDGE_EXIST                (BSW_CANIF_EDGE_EXIST)

#define CANIF_STATE_MPUINIT             (BSW_CANIF_STATE_MPUINIT)
#define CANIF_STATE_INIT                (BSW_CANIF_STATE_INIT)
#define CANIF_STATE_READY               (BSW_CANIF_STATE_READY)
#define CANIF_STATE_RUN                 (BSW_CANIF_STATE_RUN)

#/* Function */
#define CanIf_CheckStopCompletion          (bsw_canif_st_CheckStpCompletion)
#define CanIf_GetRxIndicationState         (bsw_canif_rx_GetRxIndState)
#define CanIf_InitDriver                   (bsw_canif_st_InitDriver)
#define CanIf_GetTxConfirmedPdu            (bsw_canif_tx_GetConfirmedPdu)
#define CanIf_ResetController              (bsw_canif_st_Reset)
#define CanIf_ClearTransmitRequest         (bsw_canif_tx_ClearTransmitReq)
#define CanIf_EnableRcvLock                (bsw_canif_fs_EnableRcvLock)
#define CanIf_DisableRcvLock               (bsw_canif_fs_DisableRcvLock)
#define CanIf_GetControllerError           (bsw_canif_fs_GetControllerError)
#define CanIf_MainFunctionTx               (bsw_canif_tx_MainFuncTx)
#define CanIf_MainFunctionRx               (bsw_canif_rx_MainFunctionRx)
#define CanIf_MainFunction                 (bsw_canif_st_MainFunction)
#define CanIf_CheckRam                     (bsw_canif_fs_CheckRam)
#define CanIf_GetFailStatus                (bsw_canif_fs_GetStatus)
#define CanIf_EdgeInit                     (bsw_canif_edge_EdgeInit)
#define CanIf_EdgeClearStatus              (bsw_canif_edge_EdgeClearStatus)
#define CanIf_EdgeEnableDetect             (bsw_canif_edge_EdgeEnableDtct)
#define CanIf_EdgeDisableDetect            (bsw_canif_edge_EdgeDisableDtct)
#define CanIf_EdgeGetStatus                (bsw_canif_edge_EdgeGetStatus)
#define CanIf_GetState                     (bsw_canif_st_GetState)
#define CanIf_NmTxTimeoutException         (bsw_canif_fs_NmTxToutException)
#define CanIf_ClearNmTxTimeoutUnStable     (bsw_canif_fs_ClrNmTxToutUnSt)
#define CanIf_MainFunctionTxFail           (bsw_canif_tx_MainFuncTxFail)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define CanIf_RxPduType                 Bsw_CanIf_RxPduType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANIF_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/12/09                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
