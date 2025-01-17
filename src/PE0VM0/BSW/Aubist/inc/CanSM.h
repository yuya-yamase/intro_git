/* cansm_h_v2-1-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CANSM/HEADER                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANSM_AR_H
#define BSW_CANSM_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <CanIf.h>
#include <ComM.h>
#include <cansm/bsw_cansm_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* CanSM State */
#define CANSM_INITED                       (BSW_CANSM_INITED)               /* Inited                      */
#define CANSM_UNINITED                     (BSW_CANSM_UNINITED)             /* UnInited                    */

/* Fail Status */
#define CANSM_FAIL_NONE                    (BSW_CANSM_FAIL_NONE)            /* No Fail                     */
#define CANSM_FAIL_BUSOFF                  (BSW_CANSM_FAIL_BUSOFF)          /* BusOff                      */
#define CANSM_FAIL_SNDLOCK                 (BSW_CANSM_FAIL_SNDLOCK)         /* Send Lock                   */
#define CANSM_FAIL_RCVLOCK                 (BSW_CANSM_FAIL_RCVLOCK)         /* Receive Lock                */
#define CANSM_FAIL_REGCHECK                (BSW_CANSM_FAIL_REGCHECK)        /* Stuck Register              */
#define CANSM_FAIL_UNUSEDREGCHK            (BSW_CANSM_FAIL_UNUSEDREGCHK)    /* Stuck Register(Unused MBox) */
#define CANSM_FAIL_MPU                     (BSW_CANSM_FAIL_MPU)             /* MPU Fail                    */
#define CANSM_FAIL_INITNG                  (BSW_CANSM_FAIL_INITNG)          /* Initialization error        */
#define CANSM_FAIL_USER                    (BSW_CANSM_FAIL_USER)            /* Fail Detected by User       */
#define CANSM_FAIL_ERROR_PASSIVE           (BSW_CANSM_FAIL_ERROR_PASSIVE)   /* Error Passive               */
#define CANSM_FAIL_NMTXTIMEOUT             (BSW_CANSM_FAIL_NMTXTIMEOUT)     /* Nm Tx Timeout               */

/* TX Confirmation/RX Indication Status */
#define CANSM_NO_NOTIFICATION              (BSW_CANSM_NO_NOTIFICATION)      /* No TX/RX Indication         */
#define CANSM_TX_RX_NOTIFICATION           (BSW_CANSM_TX_RX_NOTIFICATION)   /* Exist TX/RX Indication      */

/* CanSM State for BswM */
#define CANSM_BSWM_NO_COMMUNICATION        (BSW_CANSM_BSWM_NO_COMMUNICATION)          /* No Communication            */
#define CANSM_BSWM_SILENT_COMMUNICATION    (BSW_CANSM_BSWM_SILENT_COMMUNICATION)      /* Silent Communication        */
#define CANSM_BSWM_FULL_COMMUNICATION      (BSW_CANSM_BSWM_FULL_COMMUNICATION)        /* Full Communication          */
#define CANSM_BSWM_BUS_OFF                 (BSW_CANSM_BSWM_BUS_OFF)         /* Bus Off                     */
#define CANSM_BSWM_CHANGE_BAUDRATE         (BSW_CANSM_BSWM_CHANGE_BAUDRATE) /* Change Baudrate             */
#define CANSM_BSWM_FAIL                    (BSW_CANSM_BSWM_FAIL)            /* Fail(Extension)             */

/* Vendor ID */
#define CANSM_VENDOR_ID                    (BSW_CANSM_VENDOR_ID)

/* Module ID */
#define CANSM_MODULE_ID                    (BSW_CANSM_MODULE_ID)

/* AUTOSAR Release Version */
#define CANSM_AR_RELEASE_MAJOR_VERSION     (BSW_CANSM_AR_RELEASE_MAJOR_VERSION)
#define CANSM_AR_RELEASE_MINOR_VERSION     (BSW_CANSM_AR_RELEASE_MINOR_VERSION)
#define CANSM_AR_RELEASE_REVISION_VERSION  (BSW_CANSM_AR_RELEASE_REVISION_VERSION)

/* Vendor Specification Version */
#define CANSM_SW_MAJOR_VERSION             (BSW_CANSM_SW_MAJOR_VERSION)
#define CANSM_SW_MINOR_VERSION             (BSW_CANSM_SW_MINOR_VERSION)
#define CANSM_SW_PATCH_VERSION             (BSW_CANSM_SW_PATCH_VERSION)

/* Function */
#define CanSM_Init                         (bsw_cansm_st_Init)
#define CanSM_StartWakeupSource            (bsw_cansm_st_StartWakeupSrc)
#define CanSM_StopWakeupSource             (bsw_cansm_st_StopWakeupSrc)
#define CanSM_GetVersionInfo               (bsw_cansm_st_GetVersionInfo)
#define CanSM_MainFunction                 (bsw_cansm_st_MainFunction)

/* Function:Extention  */
#define CanSM_DeInit                       (bsw_cansm_st_DeInit)
#define CanSM_GetTxConfirmationState       (bsw_cansm_trx_GetTxCfmState)
#define CanSM_GetRxIndicationState         (bsw_cansm_trx_GetRxIndState)
#define CanSM_EnableRcvLock                (bsw_cansm_fs_EnableRcvLock)
#define CanSM_DisableRcvLock               (bsw_cansm_fs_DisableRcvLock)

/* Function:Extention(Callback) */
#define CanSM_CbkJudgeFail                 (bsw_cansm_fs_CbkJudgeFail)
#define CanSM_CbkDetectBusoff              (bsw_cansm_fs_CbkDetectBusoff)
#define CanSM_CbkDetectReceiveLock         (bsw_cansm_fs_CbkDetectRcvLock)
#define CanSM_CbkDetectMPUFail             (bsw_cansm_fs_CbkDetectMPUFail)
#define CanSM_CbkDetectSendLock            (bsw_cansm_fs_CbkDetectSendLock)
#define CanSM_CbkDetectNmTxTimeout         (bsw_cansm_fs_CbkDetectNmTxTout)
#define CanSM_CbkSetBusOffRestartTime      (bsw_cansm_fs_CbkSetBORestartTm)
#define CanSM_CbkSetUserFailRestartTime    (bsw_cansm_fs_CbkSetUFRestartTm)
#define CanSM_CbkPreRestartChCtrl          (bsw_cansm_st_CbkPreRestChCtrl)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Data structure for the post build parameters */
#define CanSM_ConfigType               Bsw_CanSM_ConfigType

/* CanSM State                          */
#define CanSM_StateType                Bsw_CanSM_StateType
/* TX Confirmation/RX Indication Status */
#define CanSM_NotifStatusType          Bsw_CanSM_NotifStatusType

/* CanSM State for BswM */
#define CanSM_BswMCurrentStateType     Bsw_CanSM_BswMCurrentStateType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_CANSM_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2018/02/23                                             */
/*  v2-0-0          :2021/05/24                                             */
/*  v2-1-0          :2022/09/05                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
