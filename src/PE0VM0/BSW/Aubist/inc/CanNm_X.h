/* cannm_x_h_v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CANNM/X/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_X_AR_H
#define BSW_CANNM_X_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <NmStack_Types.h>
#include <CanNm.h>
#include <cannm/bsw_cannm_x_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Function */
#define    CanNmX_CbkInit                     (bsw_cannm_x_ctrl_CbkInit)
#define    CanNmX_CbkDeInit                   (bsw_cannm_x_ctrl_CbkDeInit)
#define    CanNmX_CbkPassiveStartUp           (bsw_cannm_x_ctrl_CbkPsvStartUp)
#define    CanNmX_CbkNetworkRequest           (bsw_cannm_x_ctrl_CbkNwRequest)
#define    CanNmX_CbkNetworkRelease           (bsw_cannm_x_ctrl_CbkNwRelease)
#define    CanNmX_CbkGetState                 (bsw_cannm_x_ctrl_CbkGetState)
#define    CanNmX_CbkMainFunction             (bsw_cannm_x_ctrl_CbkMainFunc)

#define    CanNmX_CbkGetIPDUState             (bsw_cannm_x_ctrl_CbkGetIPDUStat)
#define    CanNmX_CbkCheckAwake               (bsw_cannm_x_ctrl_CbkCheckAwake)

#define    CanNmX_CbkWakeup                   (bsw_cannm_x_ctrl_CbkWakeup)
#define    CanNmX_CbkSleep                    (bsw_cannm_x_ctrl_CbkSleep)

#define    CanNmX_CbkDisableCommunication     (bsw_cannm_x_ctrl_CbkDisableCom)
#define    CanNmX_CbkEnableCommunication      (bsw_cannm_x_ctrl_CbkEnableCom)

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

#endif  /* BSW_CANNM_X_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2019/11/04                                             */
/*  v2-0-0          :2021/05/31                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
