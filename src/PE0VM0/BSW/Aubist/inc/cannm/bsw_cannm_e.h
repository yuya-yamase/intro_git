/* bsw_cannm_e_h_v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/E/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_E_H
#define BSW_CANNM_E_H

#include <nm/bsw_nmstack_types.h>
#include <cannm/bsw_cannm.h>
#include <CanNm_E.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    CANNM_E_PDU_NUM                   (BSW_CANNM_E_PDU_NUM)       /* Number of Pdu-ID */

/* Function */
#define    CanNmE_Init                       (bsw_cannm_e_ctrl_Init)
#define    CanNmE_DeInit                     (bsw_cannm_e_ctrl_DeInit)
#define    CanNmE_PassiveStartUp             (bsw_cannm_e_ctrl_PsvStartUp)
#define    CanNmE_NetworkRequest             (bsw_cannm_e_ctrl_NwRequest)
#define    CanNmE_NetworkRelease             (bsw_cannm_e_ctrl_NwRelease)

#define    CanNmE_GetState                   (bsw_cannm_e_ctrl_GetState)
#define    CanNmE_GetIPDUState               (bsw_cannm_e_ctrl_GetIPDUState)

#define    CanNmE_MainFunction               (bsw_cannm_e_ctrl_MainFunction)

#define    CanNmE_Wakeup                     (bsw_cannm_e_ctrl_Wakeup)
#define    CanNmE_Sleep                      (bsw_cannm_e_ctrl_Sleep)
#define    CanNmE_CheckAwake                 (bsw_cannm_e_ctrl_CheckAwake)

#define    CanNmE_DisableCommunication       (bsw_cannm_e_ctrl_DisableCom)
#define    CanNmE_EnableCommunication        (bsw_cannm_e_ctrl_EnableCom)

#define    CanNmE_CheckRam                   (bsw_cannm_e_ctrl_CheckRam)

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

#endif  /* BSW_CANNM_E_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/06/17                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
