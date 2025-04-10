/* vcan_h_v3-0-0                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | VCAN/HEADER                                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_VCAN_AR_H
#define BSW_VCAN_AR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <vcan/bsw_vcan_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Virtual channel Mask */
#define VCAN_VIRTUAL_CH                 (BSW_VCAN_VIRTUAL_CH)

/* Function */
#define VCan_UEdgeInit                  (bsw_vcan_eg_UEdgeInit)
#define VCan_UEdgeEnableDetect          (bsw_vcan_eg_UEdgeEnableDetect)
#define VCan_UEdgeDisableDetect         (bsw_vcan_eg_UEdgeDisableDetect)
#define VCan_UEdgeClearStatus           (bsw_vcan_eg_UEdgeClearStatus)
#define VCan_UEdgeGetStatus             (bsw_vcan_eg_UEdgeGetStatus)

#define VCan_CbkPostTx                  (bsw_vcan_tx_CbkPostTx)
#define VCan_TxFinish                   (bsw_vcan_tx_TxFinish)
#define VCan_UTxConfirmation            (bsw_vcan_tx_UTxConfirmation)
#define VCan_TxReq                      (bsw_vcan_tx_TxReq)

#define VCan_RxFinish                   (bsw_vcan_rx_RxFinish)
#define VCan_URxIndication              (bsw_vcan_rx_URxIndication)

#define VCan_GetControllerStatus        (bsw_vcan_st_GetControllerStatus)

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


#endif  /* BSW_VCAN_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/02/15                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
