/* cantp_h_v3-0-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CANTP/HEADER                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANTP_AR_H
#define BSW_CANTP_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>

#include <ComStack_Types.h>
#include <cantp/bsw_cantp_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* User Hook return value */
#define CANTP_PRESEND_TP                   (BSW_CANTP_PRESEND_TP)
#define CANTP_PRESEND_USER_OK              (BSW_CANTP_PRESEND_USER_OK)
#define CANTP_PRESEND_USER_NOT_OK          (BSW_CANTP_PRESEND_USER_NOT_OK)

/* Vendor ID */
#define CANTP_VENDOR_ID                    (BSW_CANTP_VENDOR_ID)

/* Module ID */
#define CANTP_MODULE_ID                    (BSW_CANTP_MODULE_ID)

/* AUTOSAR Release Version */
#define CANTP_AR_RELEASE_MAJOR_VERSION     (BSW_CANTP_AR_RELEASE_MAJOR_VERSION)
#define CANTP_AR_RELEASE_MINOR_VERSION     (BSW_CANTP_AR_RELEASE_MINOR_VERSION)
#define CANTP_AR_RELEASE_REVISION_VERSION  (BSW_CANTP_AR_RELEASE_REVISION_VERSION)

/* Vendor Specification Version */
#define CANTP_SW_MAJOR_VERSION             (BSW_CANTP_SW_MAJOR_VERSION)
#define CANTP_SW_MINOR_VERSION             (BSW_CANTP_SW_MINOR_VERSION)
#define CANTP_SW_PATCH_VERSION             (BSW_CANTP_SW_PATCH_VERSION)

/*---------------------*/
/* Configuration value */
/*---------------------*/
/* ON/OFF */
#define CANTP_ON                           (BSW_CANTP_ON)
#define CANTP_OFF                          (BSW_CANTP_OFF)

/* Network target address type */
#define CANTP_PHYSICAL                     (BSW_CANTP_PHYSICAL)
#define CANTP_FUNCTIONAL                   (BSW_CANTP_FUNCTIONAL)

/* Addressing format */
#define CANTP_STANDARD                     (BSW_CANTP_STANDARD)
#define CANTP_NORMALFIXED                  (BSW_CANTP_NORMALFIXED)
#define CANTP_MIXED                        (BSW_CANTP_MIXED)
#define CANTP_MIXED29BIT                   (BSW_CANTP_MIXED29BIT)
#define CANTP_EXTENDED                     (BSW_CANTP_EXTENDED)

/* Function */
#define CanTp_Init                         (bsw_cantp_cmn_Init)
#define CanTp_GetVersionInfo               (bsw_cantp_cmn_GetVersionInfo)
#define CanTp_Shutdown                     (bsw_cantp_cmn_Shutdown)
#define CanTp_Transmit                     (bsw_cantp_cmn_Transmit)
#define CanTp_CancelTransmit               (bsw_cantp_cmn_CancelTransmit)
#define CanTp_CancelReceive                (bsw_cantp_cmn_CancelReceive)
#define CanTp_ChangeParameter              (bsw_cantp_cmn_ChangeParameter)
#define CanTp_ReadParameter                (bsw_cantp_cmn_ReadParameter)
#define CanTp_MainFunction                 (bsw_cantp_cmn_MainFunction)

#define CanTp_CbkPreCheckSOR               (bsw_cantp_rx_CbkPreCheckSOR)
#define CanTp_CbkRxIndication              (bsw_cantp_rx_CbkRxIndication)
#define CanTp_CbkPreSendControl            (bsw_cantp_tx_CbkPreSendControl)
#define CanTp_CbkPreAbortSendControl       (bsw_cantp_tx_CbkPreAbrtSndCtrl)
#define CanTp_CbkFCCTSRxIndication         (bsw_cantp_tx_CbkFCCTSRxInd)
#define CanTp_CbkEnableTx                  (bsw_cantp_snd_CbkEnableTx)
#define CanTp_CbkDisableTx                 (bsw_cantp_snd_CbkDisableTx)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define CanTp_ConfigType               Bsw_CanTp_ConfigType
#define CanTp_PreSendReturnType        Bsw_CanTp_PreSendReturnType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANTP_AR_H */


/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/09/25                                             */
/*  v1-1-0          :2019/01/14                                             */
/*  v2-0-0          :2021/08/16                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
