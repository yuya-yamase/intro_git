/* bsw_vcan_public_h_v3-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VCAN/PUBLIC/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_VCAN_PUBLIC_H
#define     BSW_VCAN_PUBLIC_H

#include <Can.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Virtual Communication Module */
#define BSW_VCAN_IPC                      (0x00U)
#define BSW_VCAN_VCC                      (0x01U)

#define BSW_VCAN_NOUSE                    (0xFFU)

/* Virtual Controller ID */
#define BSW_VCAN_VCONTROLLER0             (0U)
#define BSW_VCAN_VCONTROLLER1             (1U)
#define BSW_VCAN_VCONTROLLER2             (2U)
#define BSW_VCAN_VCONTROLLER3             (3U)
#define BSW_VCAN_VCONTROLLER4             (4U)
#define BSW_VCAN_VCONTROLLER5             (5U)
#define BSW_VCAN_VCONTROLLER6             (6U)
#define BSW_VCAN_VCONTROLLER7             (7U)
#define BSW_VCAN_VCONTROLLER8             (8U)
#define BSW_VCAN_VCONTROLLER9             (9U)
#define BSW_VCAN_VCONTROLLER10            (10U)
#define BSW_VCAN_VCONTROLLER11            (11U)
#define BSW_VCAN_VCONTROLLER12            (12U)
#define BSW_VCAN_VCONTROLLER13            (13U)
#define BSW_VCAN_VCONTROLLER14            (14U)
#define BSW_VCAN_VCONTROLLER15            (15U)

/* Virtual MBOX Setting (Timing)  */
#define BSW_VCAN_POLLING                  (0x00U)
#define BSW_VCAN_INTERRUPT                (0x01U)

/* Virtual MBOX Setting (Txkind)  */
#define BSW_VCAN_KIND_TRANSMIT            (0x00U)
#define BSW_VCAN_KIND_UTRANSMIT           (0x10U)

/* Invalid Node ID */
#define BSW_VCAN_INVALID_NODE_ID          (0xFFFFFFFFU)

/* Virtual channel Mask */
#define BSW_VCAN_VIRTUAL_CH               (0x80U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void               bsw_vcan_st_Init( uint8 CanConfigSet );
void               bsw_vcan_st_Shutdown( void );
Can_ReturnType     bsw_vcan_st_InitController( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
Can_ReturnType     bsw_vcan_st_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition );
void               bsw_vcan_st_ResetController( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
Can_CtrlStType     bsw_vcan_st_GetControllerStatus( uint8 Controller );
Can_ReturnType     bsw_vcan_st_CheckStopCompletion( uint8 Controller );

Can_ReturnType     bsw_vcan_st_CheckStuckRegister( uint8 Controller );
Can_ErrStType      bsw_vcan_st_GetErrorStatus( uint8 Controller );

void               bsw_vcan_eg_EdgeInit( uint8 Controller );
void               bsw_vcan_eg_EdgeEnableDetect( uint8 Controller );
void               bsw_vcan_eg_EdgeDisableDetect( uint8 Controller );
void               bsw_vcan_eg_EdgeClearStatus( uint8 Controller );
Can_ReturnType     bsw_vcan_eg_EdgeGetStatus( uint8 Controller );

void               bsw_vcan_eg_UEdgeInit( uint8 Controller );
void               bsw_vcan_eg_UEdgeEnableDetect( uint8 Controller );
void               bsw_vcan_eg_UEdgeDisableDetect( uint8 Controller );
void               bsw_vcan_eg_UEdgeClearStatus( uint8 Controller );
Can_ReturnType     bsw_vcan_eg_UEdgeGetStatus( uint8 Controller );

void               bsw_vcan_rx_MainFunction_Read( void );
void               bsw_vcan_rx_RxFinish( uint8 Controller );
uint8              bsw_vcan_rx_URxIndication( uint8 u1Controller, uint8 u1MsgBuffer, CanConstR CanMsgType* ptMsg );

void               bsw_vcan_tx_MainFunction_Write( void );
Can_ReturnType     bsw_vcan_tx_Write( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo );
Can_ReturnType     bsw_vcan_tx_AbortSend( Can_HwHandleType Hth );
void               bsw_vcan_tx_TxFinish( uint8 Controller );
void               bsw_vcan_tx_CbkPostTx( uint8 Controller, uint8 MboxNo );
void               bsw_vcan_tx_UTxConfirmation( uint8 u1Controller, uint8 u1MsgBuffer );
uint8              bsw_vcan_tx_TxReq( uint8 u1Controller, uint8 u1MsgBuffer, CanMsgType* ptMsg );

#endif  /* BSW_VCAN_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/02/24                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
