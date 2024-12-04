/* bsw_cannm_b_h_v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/B/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_B_H
#define BSW_CANNM_B_H

#include <nm/bsw_nmstack_types.h>
#include <canif/bsw_canif.h>
#include <cannm/bsw_cannm.h>
#include <CanNm_B.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     CANNM_B_PDU_NUM                (BSW_CANNM_B_PDU_NUM)    /* Number of NM-PDU */

/*-----------------------------------*/
/* Unit : control                    */
/*-----------------------------------*/
/* Function */
#define     CanNmB_Init                    (bsw_cannm_b_ctrl_Init)
#define     CanNmB_Wakeup                  (bsw_cannm_b_ctrl_Wakeup)
#define     CanNmB_PassiveStartUp          (bsw_cannm_b_ctrl_PassiveStartUp)
#define     CanNmB_NetworkRequest          (bsw_cannm_b_ctrl_NetworkRequest)
#define     CanNmB_NetworkRelease          (bsw_cannm_b_ctrl_NetworkRelease)
#define     CanNmB_MainFunction            (bsw_cannm_b_ctrl_MainFunction)
#define     CanNmB_CheckAwake              (bsw_cannm_b_ctrl_CheckAwake)
#define     CanNmB_GetState                (bsw_cannm_b_ctrl_GetState)
#define     CanNmB_GetIPDUState            (bsw_cannm_b_ctrl_GetIPDUState)
#define     CanNmB_Sleep                   (bsw_cannm_b_ctrl_Sleep)
#define     CanNmB_DeInit                  (bsw_cannm_b_ctrl_DeInit)
#define     CanNmB_TransmitEvtWkup         (bsw_cannm_b_ctrl_ReqEvtWkup)
#define     CanNmB_CancelEvtWkup           (bsw_cannm_b_ctrl_CancelEvtWkup)
#define     CanNmB_DisableCommunication    (bsw_cannm_b_ctrl_DisableCom)
#define     CanNmB_EnableCommunication     (bsw_cannm_b_ctrl_EnableCom)
#define     CanNmB_CheckRam                (bsw_cannm_b_ctrl_CheckRam)

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

#endif /* BSW_CANNM_B_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/05/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
