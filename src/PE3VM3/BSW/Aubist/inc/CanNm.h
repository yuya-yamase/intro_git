/* cannm_h_v3-0-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CANNM/HEADER                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_AR_H
#define BSW_CANNM_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>

#include <ComStack_Types.h>
#include <NmStack_Types.h>
#include <cannm/bsw_cannm_public.h>

#include <CanNm_Z.h>
#include <CanNm_A.h>
#include <CanNm_A2.h>
#include <CanNm_B.h>
#include <CanNm_C2.h>
#include <CanNm_E.h>
#include <CanNm_X.h>
#include <CanNm_Y.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CANNM_PDU_BYTE_0                     (BSW_CANNM_PDU_BYTE_0)           /* Data position : byte0         */
#define CANNM_PDU_BYTE_1                     (BSW_CANNM_PDU_BYTE_1)           /* Data position : byte1         */
#define CANNM_PDU_OFF                        (BSW_CANNM_PDU_OFF)              /* Data position : NOUSE         */

#define CANNM_IPDU_DISABLE_SEND              (BSW_CANNM_IPDU_DISABLE_SEND)    /* Disable Send                  */
#define CANNM_IPDU_ENABLE_EVENT              (BSW_CANNM_IPDU_ENABLE_EVENT)    /* Enable Event Message          */
#define CANNM_IPDU_ENABLE_PERI               (BSW_CANNM_IPDU_ENABLE_PERI)     /* Enable Periodic Message       */

#define CANNM_MSGTYP_ACTIVE                  (BSW_CANNM_MSGTYP_ACTIVE)        /* NM Message Type : ACTIVE      */
#define CANNM_MSGTYP_WAKEUP                  (BSW_CANNM_MSGTYP_WAKEUP)        /* NM Message Type : WAKEUP      */
#define CANNM_MSGTYP_SLEEP                   (BSW_CANNM_MSGTYP_SLEEP)         /* NM Message Type : SLEEP       */

#define CANNM_BUSWKUP_WBS_IMM                (BSW_CANNM_BUSWKUP_WBS_IMM)      /* BusWakeup Type : WaitBusSleep(Immidiate) */
#define CANNM_BUSWKUP_WBS                    (BSW_CANNM_BUSWKUP_WBS)          /* BusWakeup Type : WaitBusSleep            */
#define CANNM_BUSWKUP_BS                     (BSW_CANNM_BUSWKUP_BS)           /* BusWakeup Type : BusSleep                */
#define CANNM_BUSWKUP_WBS_LIMPHOME           (BSW_CANNM_BUSWKUP_WBS_LIMPHOME) /* BusWakeup Type : WaitBusSleep(LimpHome)  */

#define CANNM_WKUP_PWON                      (BSW_CANNM_WKUP_PWON)            /* Wakeup Type : PowerOn         */
#define CANNM_WKUP_BS                        (BSW_CANNM_WKUP_BS)              /* Wakeup Type : BusSleep        */

#define CANNM_BUSAWAKE_NONE                  (BSW_CANNM_BUSAWAKE_NONE)        /* BusAwake Kind : None          */
#define CANNM_BUSAWAKE_ACTIVE                (BSW_CANNM_BUSAWAKE_ACTIVE)      /* BusAwake Kind : Active        */
#define CANNM_BUSAWAKE_PASSIVE               (BSW_CANNM_BUSAWAKE_PASSIVE)     /* BusAwake Kind : Passive       */

#define CANNM_ENATX_WKUP                     (BSW_CANNM_ENATX_WKUP)           /* EnableTx Reason    : Wakeup    */
#define CANNM_ENATX_TXTO                     (BSW_CANNM_ENATX_TXTO)           /* EnableTx Reason    : TxTimeout */

/* Vendor ID */
#define CANNM_VENDOR_ID                      (BSW_CANNM_VENDOR_ID)

/* Module ID */
#define CANNM_MODULE_ID                      (BSW_CANNM_MODULE_ID)

/* AUTOSAR Release Version */
#define CANNM_AR_RELEASE_MAJOR_VERSION       (BSW_CANNM_AR_RELEASE_MAJOR_VERSION)
#define CANNM_AR_RELEASE_MINOR_VERSION       (BSW_CANNM_AR_RELEASE_MINOR_VERSION)
#define CANNM_AR_RELEASE_REVISION_VERSION    (BSW_CANNM_AR_RELEASE_REVISION_VERSION)

/* Vendor Specification Version */
#define CANNM_SW_MAJOR_VERSION               (BSW_CANNM_SW_MAJOR_VERSION)
#define CANNM_SW_MINOR_VERSION               (BSW_CANNM_SW_MINOR_VERSION)
#define CANNM_SW_PATCH_VERSION               (BSW_CANNM_SW_PATCH_VERSION)

/* Function */
#define CanNm_Init                           (bsw_cannm_ch_Init)
#define CanNm_DeInit                         (bsw_cannm_ch_DeInit)
#define CanNm_PassiveStartUp                 (bsw_cannm_ch_PassiveStartUp)
#define CanNm_NetworkRequest                 (bsw_cannm_ch_NetworkRequest)
#define CanNm_NetworkRelease                 (bsw_cannm_ch_NetworkRelease)
#define CanNm_DisableCommunication           (bsw_cannm_ch_DisableCom)
#define CanNm_EnableCommunication            (bsw_cannm_ch_EnableCom)
#define CanNm_GetState                       (bsw_cannm_ch_GetState)
#define CanNm_MainFunction                   (bsw_cannm_ch_MainFunction)
#define CanNm_CancelTransmitFrame            (bsw_cannm_ch_CancelTrFr)
#define CanNm_PduRxIndication                (bsw_cannm_ch_PduRxIndication)
#define CanNm_GetVersionInfo                 (bsw_cannm_ch_GetVersionInfo)

#define CanNm_TransmitFrame                  (bsw_cannm_ch_TransmitFrame)
#define CanNm_EdgeDisableDetect              (bsw_cannm_ch_EdgeDisableDetect)
#define CanNm_EdgeEnableDetect               (bsw_cannm_ch_EdgeEnableDetect)

#define CanNm_GetNodeIdentifier              (bsw_cannm_ch_GetNodeId)
#define CanNm_GetLocalNodeIdentifier         (bsw_cannm_ch_GetLocalNodeId)
#define CanNm_SetUserData                    (bsw_cannm_ch_SetUserData)
#define CanNm_GetUserData                    (bsw_cannm_ch_GetUserData)
#define CanNm_GetPduData                     (bsw_cannm_ch_GetPduData)

#define CanNm_SetSleepReadyBit               (bsw_cannm_ch_SetSleepReadyBit)
#define CanNm_RequestBusSynchronization      (bsw_cannm_ch_RequestBusSync)
#define CanNm_RequestSynchronizedPncShutdown (bsw_cannm_ch_ReqSyncPncSlp)
#define CanNm_CancelSynchronizedPncShutdown  (bsw_cannm_ch_CancelSyncPncSlp)

#define CanNm_SetDisableTxTime               (bsw_cannm_ch_SetDisableTxTime)

#define CanNm_CbkPreTxRingMsg                (bsw_cannm_ch_CbkPreTxRingMsg)
#define CanNm_CbkBusWakeup                   (bsw_cannm_ch_CbkBusWakeup)
#define CanNm_CbkEvtWkupTxFinish             (bsw_cannm_ch_CbkEvtWUTxFn)
#define CanNm_CbkTxTimeout                   (bsw_cannm_ch_CbkTxTimeout)
#define CanNm_CbkGetPwonBusAwake             (bsw_cannm_ch_CbkGetPwonBusAwake)
#define CanNm_CbkGetBusAwake                 (bsw_cannm_ch_CbkGetBusAwake)
#define CanNm_CbkPreEnableTx                 (bsw_cannm_ch_CbkPreEnableTx)
#define CanNm_CbkEnableComPreRestartTimer    (bsw_cannm_ch_CbkEnComPreReStTmr)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define CanNm_ConfigType                     Bsw_CanNm_ConfigType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_CANNM_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/07/01                                             */
/*  v1-1-0          :2018/10/02                                             */
/*  v1-2-0          :2020/05/11                                             */
/*  v2-0-0          :2022/01/13                                             */
/*  v2-2-0          :2022/05/12                                             */
/*  v2-4-0          :2023/12/18                                             */
/*  v3-0-0          :2024/09/03                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
