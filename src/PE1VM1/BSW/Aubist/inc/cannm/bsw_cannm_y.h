/* bsw_cannm_y_h_v3-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/Y/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_Y_H
#define BSW_CANNM_Y_H

#include <nm/bsw_nmstack_types.h>
#include <cannm/bsw_cannm.h>
#include <CanNm_Y.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    CANNM_Y_PDU_NUM                       (BSW_CANNM_Y_PDU_NUM)    /* Number of Pdu-ID */

/* Function */
#define    CanNmY_Init                           (bsw_cannm_y_ctrl_Init)
#define    CanNmY_DeInit                         (bsw_cannm_y_ctrl_DeInit)
#define    CanNmY_PassiveStartUp                 (bsw_cannm_y_ctrl_PsvStartUp)
#define    CanNmY_NetworkRequest                 (bsw_cannm_y_ctrl_NwRequest)
#define    CanNmY_NetworkRelease                 (bsw_cannm_y_ctrl_NwRelease)
#define    CanNmY_DisableCommunication           (bsw_cannm_y_ctrl_DisableCom)
#define    CanNmY_EnableCommunication            (bsw_cannm_y_ctrl_EnableCom)
#define    CanNmY_GetState                       (bsw_cannm_y_ctrl_GetState)
#define    CanNmY_MainFunction                   (bsw_cannm_y_ctrl_MainFunction)

#define    CanNmY_Wakeup                         (bsw_cannm_y_ctrl_Wakeup)
#define    CanNmY_Sleep                          (bsw_cannm_y_ctrl_Sleep)
#define    CanNmY_CheckAwake                     (bsw_cannm_y_ctrl_CheckAwake)
#define    CanNmY_GetIPDUState                   (bsw_cannm_y_ctrl_GetIPDUState)
#define    CanNmY_CheckRam                       (bsw_cannm_y_ctrl_CheckRam)

#define    CanNmY_GetNodeIdentifier              (bsw_cannm_y_ctrl_GetNodeId)
#define    CanNmY_GetLocalNodeIdentifier         (bsw_cannm_y_ctrl_GetLclNodeId)
#define    CanNmY_SetUserData                    (bsw_cannm_y_ctrl_SetUserData)
#define    CanNmY_GetUserData                    (bsw_cannm_y_ctrl_GetUserData)
#define    CanNmY_GetPduData                     (bsw_cannm_y_ctrl_GetPduData)

#define    CanNmY_TransmitEvtWkup                (bsw_cannm_y_ctrl_TxEvtWakeup)
#define    CanNmY_CancelEvtWkup                  (bsw_cannm_y_ctrl_CancelEvtWkup)

#define    CanNmY_SetSleepReadyBit               (bsw_cannm_y_ctrl_SetSlpReadyBit)
#define    CanNmY_RequestBusSynchronization      (bsw_cannm_y_ctrl_RequestBusSync)
#define    CanNmY_RequestSynchronizedPncShutdown (bsw_cannm_y_ctrl_ReqSyncPncShutdown)
#define    CanNmY_CancelSynchronizedPncShutdown  (bsw_cannm_y_ctrl_CancelReqSyncPncShutdown)

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

#endif  /* BSW_CANNM_Y_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/01/13                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
