/* nm_h_v3-0-0                                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NM/HEADER                                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_NM_AR_H
#define BSW_NM_AR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <NmStack_Types.h>
#include <nm/bsw_nm_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Vendor ID */
#define NM_VENDOR_ID                      (BSW_NM_VENDOR_ID)

/* Module ID */
#define NM_MODULE_ID                      (BSW_NM_MODULE_ID)

/* AUTOSAR Release Version */
#define NM_AR_RELEASE_MAJOR_VERSION       (BSW_NM_AR_RELEASE_MAJOR_VERSION)
#define NM_AR_RELEASE_MINOR_VERSION       (BSW_NM_AR_RELEASE_MINOR_VERSION)
#define NM_AR_RELEASE_REVISION_VERSION    (BSW_NM_AR_RELEASE_REVISION_VERSION)

/* Vendor Specification Version */
#define NM_SW_MAJOR_VERSION               (BSW_NM_SW_MAJOR_VERSION)
#define NM_SW_MINOR_VERSION               (BSW_NM_SW_MINOR_VERSION)
#define NM_SW_PATCH_VERSION               (BSW_NM_SW_PATCH_VERSION)

/* Function */
#define Nm_Init                           (bsw_nm_status_Init)
#define Nm_DeInit                         (bsw_nm_status_DeInit)
#define Nm_PassiveStartUp                 (bsw_nm_sw_PassiveStartUp)
#define Nm_NetworkRequest                 (bsw_nm_sw_NetworkRequest)
#define Nm_NetworkRelease                 (bsw_nm_sw_NetworkRelease)
#define Nm_DisableCommunication           (bsw_nm_sw_DisableComm)
#define Nm_EnableCommunication            (bsw_nm_sw_EnableComm)
#define Nm_SetUserData                    (bsw_nm_sw_SetUserData)
#define Nm_GetUserData                    (bsw_nm_sw_GetUserData)
#define Nm_GetPduData                     (bsw_nm_sw_GetPduData)
#define Nm_GetNodeIdentifier              (bsw_nm_sw_GetNodeId)
#define Nm_GetLocalNodeIdentifier         (bsw_nm_sw_GetLocalNodeId)
#define Nm_GetState                       (bsw_nm_sw_GetState)
#define Nm_GetVersionInfo                 (bsw_nm_status_GetVersionInfo)
#define Nm_MainFunction                   (bsw_nm_status_MainFunction)

#define Nm_CbkPduRxIndication             (bsw_nm_sw_CbkPduRxIndication)
#define Nm_CbkCtrlCoBusAwake              (bsw_nm_coord_CbkCtrlCoBusAwake)
#define Nm_CbkPreTxMsg                    (bsw_nm_sw_CbkPreTxMsg)
#define Nm_CbkTRxIndication               (bsw_nm_sw_CbkTRxIndication)
#define Nm_CbkStateChangeNotification     (bsw_nm_sw_CbkStateChangeNotif)
#define Nm_CbkSetDisableTxTime            (bsw_nm_sw_CbkSetDisableTxTime)

#define Nm_StartSyncSleep                 (bsw_nm_coord_StartSyncSleep)
#define Nm_CancelSyncSleep                (bsw_nm_coord_CancelSyncSleep)
#define Nm_RequestSynchronizedPncShutdown (bsw_nm_coord_ReqSyncPncSlp)
#define Nm_CancelSynchronizedPncShutdown  (bsw_nm_coord_CancelSyncPncSlp)

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

#endif  /* BSW_NM_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/07/18                                             */
/*  v1-1-0          :2018/02/23                                             */
/*  v1-2-0          :2020/04/15                                             */
/*  v2-0-0          :2022/01/13                                             */
/*  v3-0-0          :2024/09/03                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
