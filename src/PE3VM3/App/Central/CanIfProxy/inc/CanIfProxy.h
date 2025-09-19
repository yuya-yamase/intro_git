/* v0-2-1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CanIfProxy.h                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef CANIFPROXY_H
#define CANIFPROXY_H

#include "Std_Types.h"
#include "CanIf.h"
#include "Com.h"
#include "Com_Cfg.h"
#include "../../../../BSW/Aubist/VCan/inc/bsw_vcan_vcc.h"
#include "../../../../BSW/Aubist/inc/VCan.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void CanIfProxy_Init( void );
void CanIfProxy_Main( void );
void CanIfProxy_Transmit(const uint16 receive_len, const uint8* const receive_data);
void CanIfProxy_CancelTransmit(const uint16 receive_len, const uint8* const receive_data);

void CanIfProxy_TpTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

/*void CanIfProxy_RxIndication(uint8 u1Controller, uint8 u1MsgBuffer, CanConstR CanMsgType* ptMsg);*/
// BufReq_ReturnType CanIfProxy_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#endif  /* CANIFPROXY_H */
/**** End of File ***********************************************************/
