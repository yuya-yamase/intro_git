/* bsw_cannm_c2_h_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/C2/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_C2_H
#define BSW_CANNM_C2_H

#include <nm/bsw_nmstack_types.h>
#include <cannm/bsw_cannm.h>
#include <CanNm_C2.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    CANNM_C2_PDU_NUM                (BSW_CANNM_C2_PDU_NUM)    /* Number of Pdu-ID */

/* Function */
#define    CanNmC2_Init                    (bsw_cannm_c2_ctrl_Init)
#define    CanNmC2_DeInit                  (bsw_cannm_c2_ctrl_DeInit)
#define    CanNmC2_PassiveStartUp          (bsw_cannm_c2_ctrl_PsvStartUp)
#define    CanNmC2_NetworkRequest          (bsw_cannm_c2_ctrl_NwRequest)
#define    CanNmC2_NetworkRelease          (bsw_cannm_c2_ctrl_NwRelease)
#define    CanNmC2_DisableCommunication    (bsw_cannm_c2_ctrl_DisableCom)
#define    CanNmC2_EnableCommunication     (bsw_cannm_c2_ctrl_EnableCom)
#define    CanNmC2_GetState                (bsw_cannm_c2_ctrl_GetState)
#define    CanNmC2_MainFunction            (bsw_cannm_c2_ctrl_MainFunction)

#define    CanNmC2_Wakeup                  (bsw_cannm_c2_ctrl_Wakeup)
#define    CanNmC2_Sleep                   (bsw_cannm_c2_ctrl_Sleep)
#define    CanNmC2_CheckAwake              (bsw_cannm_c2_ctrl_CheckAwake)
#define    CanNmC2_GetIPDUState            (bsw_cannm_c2_ctrl_GetIPDUState)
#define    CanNmC2_CheckRam                (bsw_cannm_c2_ctrl_CheckRam)

#define    CanNmC2_GetNodeIdentifier       (bsw_cannm_c2_ctrl_GetNodeId)
#define    CanNmC2_GetLocalNodeIdentifier  (bsw_cannm_c2_ctrl_GetLclNodeId)
#define    CanNmC2_SetUserData             (bsw_cannm_c2_ctrl_SetUserData)
#define    CanNmC2_GetUserData             (bsw_cannm_c2_ctrl_GetUserData)
#define    CanNmC2_GetPduData              (bsw_cannm_c2_ctrl_GetPduData)

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

#endif  /* BSW_CANNM_C2_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/06/17                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
