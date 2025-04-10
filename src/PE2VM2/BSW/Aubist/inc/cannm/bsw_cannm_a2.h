/* bsw_cannm_a2_h_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A2/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_A2_H
#define BSW_CANNM_A2_H

#include <nm/bsw_nmstack_types.h>
#include <cannm/bsw_cannm.h>
#include <CanNm_A2.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    CANNM_A2_PDU_NUM                  (BSW_CANNM_A2_PDU_NUM)

/* Function */
#define    CanNmA2_Init                      (bsw_cannm_a2_ctrl_Init)
#define    CanNmA2_DeInit                    (bsw_cannm_a2_ctrl_DeInit)
#define    CanNmA2_PassiveStartUp            (bsw_cannm_a2_ctrl_PsvStartUp)
#define    CanNmA2_NetworkRequest            (bsw_cannm_a2_ctrl_NwRequest)
#define    CanNmA2_NetworkRelease            (bsw_cannm_a2_ctrl_NwRelease)
#define    CanNmA2_DisableCommunication      (bsw_cannm_a2_ctrl_DisableCom)
#define    CanNmA2_EnableCommunication       (bsw_cannm_a2_ctrl_EnableCom)
#define    CanNmA2_GetState                  (bsw_cannm_a2_ctrl_GetState)
#define    CanNmA2_MainFunction              (bsw_cannm_a2_ctrl_MainFunction)

#define    CanNmA2_Wakeup                    (bsw_cannm_a2_ctrl_Wakeup)
#define    CanNmA2_Sleep                     (bsw_cannm_a2_ctrl_Sleep)
#define    CanNmA2_CheckAwake                (bsw_cannm_a2_ctrl_CheckAwake)
#define    CanNmA2_GetIPDUState              (bsw_cannm_a2_ctrl_GetIPDUState)
#define    CanNmA2_SetBusOff                 (bsw_cannm_a2_ctrl_SetBusOff)
#define    CanNmA2_TransmitEvtWkup           (bsw_cannm_a2_ctrl_TxEvtWakeup)
#define    CanNmA2_CancelEvtWkup             (bsw_cannm_a2_ctrl_CancelEvtWkup)
#define    CanNmA2_CheckRam                  (bsw_cannm_a2_ctrl_CheckRam)

#define    CanNmA2_GetNodeIdentifier         (bsw_cannm_a2_ctrl_GetNodeId)
#define    CanNmA2_GetLocalNodeIdentifier    (bsw_cannm_a2_ctrl_GetLclNodeId)
#define    CanNmA2_SetUserData               (bsw_cannm_a2_ctrl_SetUserData)
#define    CanNmA2_GetUserData               (bsw_cannm_a2_ctrl_GetUserData)
#define    CanNmA2_GetPduData                (bsw_cannm_a2_ctrl_GetPduData)

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

#endif  /* BSW_CANNM_A2_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/06/17                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
