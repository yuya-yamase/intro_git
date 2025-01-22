/* bsw_cannm_a_h_v3-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_A_H
#define BSW_CANNM_A_H

#include <nm/bsw_nmstack_types.h>
#include <cannm/bsw_cannm.h>
#include <CanNm_A.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    CANNM_A_PDU_NUM               (BSW_CANNM_A_PDU_NUM)           /* Number of NM-PDU */

/*------------------------------------------*/
/* Unit: CONTROL(nm)                        */
/*------------------------------------------*/
/* Function */
#define    CanNmA_Init                   (bsw_cannm_a_ctrl_Init)
#define    CanNmA_DeInit                 (bsw_cannm_a_ctrl_DeInit)
#define    CanNmA_PassiveStartUp         (bsw_cannm_a_ctrl_PassiveStartUp)
#define    CanNmA_NetworkRequest         (bsw_cannm_a_ctrl_NetworkRequest)
#define    CanNmA_NetworkRelease         (bsw_cannm_a_ctrl_NetworkRelease)
#define    CanNmA_Wakeup                 (bsw_cannm_a_ctrl_Wakeup)
#define    CanNmA_CheckAwake             (bsw_cannm_a_ctrl_CheckAwake)
#define    CanNmA_Sleep                  (bsw_cannm_a_ctrl_Sleep)
#define    CanNmA_MainFunction           (bsw_cannm_a_ctrl_MainFunction)
#define    CanNmA_SetBusOff              (bsw_cannm_a_ctrl_SetBusOff)
#define    CanNmA_TransmitEvtWkup        (bsw_cannm_a_ctrl_ReqEvtWkup)
#define    CanNmA_CancelEvtWkup          (bsw_cannm_a_ctrl_CancelEvtWkup)
#define    CanNmA_GetState               (bsw_cannm_a_ctrl_GetState)
#define    CanNmA_GetIPDUState           (bsw_cannm_a_ctrl_GetIPDUState)
#define    CanNmA_DisableCommunication   (bsw_cannm_a_ctrl_DisableCom)
#define    CanNmA_EnableCommunication    (bsw_cannm_a_ctrl_EnableCom)
#define    CanNmA_CheckRam               (bsw_cannm_a_ctrl_CheckRam)

/*------------------------------------------*/
/* Unit: CVT-NM(cvtnmch)                    */
/*------------------------------------------*/
/* Function */
#define    CanNmA_GetBackupData          (bsw_cannm_a_cvtnm_GetBackupData)
#define    CanNmA_SetBackupData          (bsw_cannm_a_cvtnm_SetBackupData)

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

#endif /* BSW_CANNM_A_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/06/17                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
