/* bsw_vcan_h_v2-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VCAN/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_VCAN_H
#define     BSW_VCAN_H

#include <VCan.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Virtual MBOX Setting (Timing)  */
#define VCAN_POLLING                      (BSW_VCAN_POLLING)
#define VCAN_INTERRUPT                    (BSW_VCAN_INTERRUPT)

/* Virtual MBOX Setting (Txkind)  */
#define VCAN_KIND_TRANSMIT                (BSW_VCAN_KIND_TRANSMIT)
#define VCAN_KIND_UTRANSMIT               (BSW_VCAN_KIND_UTRANSMIT)

/* Invalid Node ID */
#define VCAN_INVALID_NODE_ID              (BSW_VCAN_INVALID_NODE_ID)

/* Function */
#define VCan_Init                         (bsw_vcan_st_Init)
#define VCan_Shutdown                     (bsw_vcan_st_Shutdown)
#define VCan_InitController               (bsw_vcan_st_InitController)
#define VCan_SetControllerMode            (bsw_vcan_st_SetControllerMode)
#define VCan_ResetController              (bsw_vcan_st_ResetController)
#define VCan_CheckStopCompletion          (bsw_vcan_st_CheckStopCompletion)
#define VCan_MainFunction_Read            (bsw_vcan_rx_MainFunction_Read)
#define VCan_MainFunction_Write           (bsw_vcan_tx_MainFunction_Write)
#define VCan_Write                        (bsw_vcan_tx_Write)
#define VCan_AbortSend                    (bsw_vcan_tx_AbortSend)
#define VCan_CheckStuckRegister           (bsw_vcan_st_CheckStuckRegister)
#define VCan_GetErrorStatus               (bsw_vcan_st_GetErrorStatus)
#define VCan_EdgeInit                     (bsw_vcan_eg_EdgeInit)
#define VCan_EdgeEnableDetect             (bsw_vcan_eg_EdgeEnableDetect)
#define VCan_EdgeDisableDetect            (bsw_vcan_eg_EdgeDisableDetect)
#define VCan_EdgeClearStatus              (bsw_vcan_eg_EdgeClearStatus)
#define VCan_EdgeGetStatus                (bsw_vcan_eg_EdgeGetStatus)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_VCAN_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/02/15                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
