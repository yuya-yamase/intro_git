/* bsw_bswm_can_h_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CAN/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_BSWM_CAN_H
#define BSW_BSWM_CAN_H

#include <bswm_cs/bsw_bswm_cs.h>
#include <BswM_Can.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*------------------------------*/
/* Unit:status                  */
/*------------------------------*/
/* Function */
#define BswM_Can_Init                    (bsw_bswm_can_st_Init)
#define BswM_Can_PrepareDeInit           (bsw_bswm_can_st_PrepareDeInit)
#define BswM_Can_DeInit                  (bsw_bswm_can_st_DeInit)
#define BswM_Can_Wakeup                  (bsw_bswm_can_st_Wakeup)
#define BswM_Can_Sleep                   (bsw_bswm_can_st_Sleep)
#define BswM_Can_Reset                   (bsw_bswm_can_st_Reset)
#define BswM_Can_MainFunctionHighIn      (bsw_bswm_can_st_MainFuncHiIn)
#define BswM_Can_MainFunctionHighOut     (bsw_bswm_can_st_MainFuncHiOut)
#define BswM_Can_MainFunctionMidIn       (bsw_bswm_can_st_MainFuncMidIn)
#define BswM_Can_MainFunctionMidCtrl     (bsw_bswm_can_st_MainFuncMidCtrl)
#define BswM_Can_MainFunctionMidOut      (bsw_bswm_can_st_MainFuncMidOut)
#define BswM_Can_DetectFail              (bsw_bswm_can_st_DetectFail)
#define BswM_Can_CheckRam                (bsw_bswm_can_st_CheckRam)

/*------------------------------*/
/* Unit:ctrl                    */
/*------------------------------*/
/* Channel Invalid              */
#define BSWM_CAN_CHANNEL_INVALID         (BSW_BSWM_CAN_CHANNEL_INVALID)

/* Function */
#define BswM_Can_InitDriver              (bsw_bswm_can_ctrl_InitDriver)
#define BswM_Can_CheckAwake              (bsw_bswm_can_ctrl_CheckAwake)
#define BswM_Can_UpdateIPDUStatus        (bsw_bswm_can_ctrl_UpdIPDUStatus)
#define BswM_Can_StopTxPdu               (bsw_bswm_can_ctrl_StopTxPdu)
#define BswM_Can_ResumeTxPdu             (bsw_bswm_can_ctrl_ResumeTxPdu)
#define BswM_Can_RestartChCtrl           (bsw_bswm_can_ctrl_RestartChCtrl)
#define BswM_Can_StopDMControl           (bsw_bswm_can_ctrl_StopDMControl)
#define BswM_Can_ResumeDMControl         (bsw_bswm_can_ctrl_ResumeDMCtrl)
#define BswM_Can_GetTxChannel            (bsw_bswm_can_ctrl_GetTxChannel)
#define BswM_Can_GetRxChannel            (bsw_bswm_can_ctrl_GetRxChannel)

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

#endif /* BSW_BSWM_CAN_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/12/09                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
