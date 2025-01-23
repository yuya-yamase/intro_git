/* bsw_comm_h_v3-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COMM/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_COMM_H
#define BSW_COMM_H

#include <ComM.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*--------------------------------------*/
/* Unit:ctrl                            */
/*--------------------------------------*/
/* Bus Awake Kind */
#define COMM_BUSAWAKE_KIND_NONE                 (BSW_COMM_BUSAWAKE_KIND_NONE)
#define COMM_BUSAWAKE_KIND_OTHER                (BSW_COMM_BUSAWAKE_KIND_OTHER)
#define COMM_BUSAWAKE_KIND_ECU                  (BSW_COMM_BUSAWAKE_KIND_ECU)
#define COMM_BUSAWAKE_KIND_OWN                  (BSW_COMM_BUSAWAKE_KIND_OWN)
#define COMM_BUSAWAKE_KIND_CO                   (BSW_COMM_BUSAWAKE_KIND_CO)

/* Maximum number of PNC */
#define COMM_PNCMAXNUM                          (BSW_COMM_PNCMAXNUM)

/* Function */
#define ComM_MainFunction                       (bsw_comm_ctrl_MainFunction)
#define ComM_MainFunctionEira                   (bsw_comm_ctrl_MainFunctionEira)
#define ComM_ClearAllCoBusAwake                 (bsw_comm_ctrl_ClrAllCoBusAwake)
#define ComM_SetEventAwake                      (bsw_comm_ctrl_SetEventAwake)
#define ComM_ClearEventAwake                    (bsw_comm_ctrl_ClearEventAwake)
#define ComM_CheckRam                           (bsw_comm_ctrl_ChkRam)
#define ComM_GetBusAwakeKind                    (bsw_comm_ctrl_GetBusAwakeKind)
#define ComM_SetSyncAwake                       (bsw_comm_ctrl_SetSyncAwake)
#define ComM_ClearSyncAwake                     (bsw_comm_ctrl_ClearSyncAwake)
#define ComM_GetPncAwakeFixed                   (bsw_comm_ctrl_GetPncAwakeFixed)
#define ComM_GetPnEiraFixed                     (bsw_comm_ctrl_GetPnEiraFixed)
#define ComM_GetPncReqRdyStatus                 (bsw_comm_ctrl_GetPncReqRdyStat)
#define ComM_GetPncPrepSlpStatus                (bsw_comm_ctrl_GetPncPrepSlpStat)
#define ComM_GetPncEnableTxStatus               (bsw_comm_ctrl_GetPncEnableTxSt)
#define ComM_UpdateChannelBusAwake              (bsw_comm_ctrl_UpdateChBusAwake)

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

#endif /* BSW_COMM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/01/11                                             */
/*  v2-1-0          :2022/09/19                                             */
/*  v2-2-0          :2023/05/08                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
