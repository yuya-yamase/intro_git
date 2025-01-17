/* can_user_c_v2-1-2                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/USER/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <can/common/can_cm_log.h>
#include <can/common/can_syscfg_ext.h>

#include <Can.h>
#include "../cfg/common/can_cv_cfg.h"

#if ((CAN_CFG_IP0 != CAN_IP_NOUSE) || (CAN_CFG_IP1 != CAN_IP_NOUSE))
#include "oxcan_aubif.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


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


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Can_URefreshRegister                                     */
/* Description   | Indication for Refreshing Register                       */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   CAN Controller ID(MCU CAN Controller ID)               */
/* Return Value  | None                                                     */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
void
Can_URefreshRegister( uint8 Controller )
{
}


/****************************************************************************/
/* Function Name | Can_UEdgeInit                                            */
/* Description   | Indication for Initializing Edge Detection               */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   CAN Controller ID(MCU CAN Controller ID)               */
/* Return Value  | None                                                     */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
void
Can_UEdgeInit( uint8 Controller )
{
}


/****************************************************************************/
/* Function Name | Can_UEdgeEnableDetect                                    */
/* Description   | Indication for Enabling Edge Detection                   */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   CAN Controller ID(MCU CAN Controller ID)               */
/* Return Value  | None                                                     */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
#ifndef OXCAN_AUBIF_H
void
Can_UEdgeEnableDetect( uint8 Controller )
{
}
#endif

/****************************************************************************/
/* Function Name | Can_UEdgeDisableDetect                                   */
/* Description   | Indication for Disabling Edge Detection                  */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   CAN Controller ID(MCU CAN Controller ID)               */
/* Return Value  | None                                                     */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
#ifndef OXCAN_AUBIF_H
void
Can_UEdgeDisableDetect( uint8 Controller )
{
}
#endif

/****************************************************************************/
/* Function Name | Can_UEdgeClearStatus                                     */
/* Description   | Indication for Clearing Edge Detection History Status    */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   CAN Controller ID(MCU CAN Controller ID)               */
/* Return Value  | None                                                     */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
#ifndef OXCAN_AUBIF_H
void
Can_UEdgeClearStatus( uint8 Controller )
{
}
#endif

/****************************************************************************/
/* Function Name | Can_UEdgeGetStatus                                       */
/* Description   | Indication for Getting Edge Detection History Status     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   CAN Controller ID(MCU CAN Controller ID)               */
/* Return Value  | Can_ReturnType Edge Detection History Status             */
/*               |   CAN_OK     :                                           */
/*               |     Occurred(Edge Detection History exist)               */
/*               |   CAN_NOT_OK :                                           */
/*               |     Not occurred(Edge Detection History doesn't exist)   */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
#ifndef OXCAN_AUBIF_H
Can_ReturnType
Can_UEdgeGetStatus( uint8 Controller )
{
    return ((Can_ReturnType)CAN_NOT_OK);
}
#endif

#if(CAN_CFG_CV != CAN_USE)
/*====== Edit Area when CAN IP Abstraction Function is NOUSE [Start] =======*/
/****************************************************************************/
/* Function Name | Can_UTxConfirmation                                      */
/* Description   | Confirmation of User Transmission Completion             */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller :                                     */
/*               |   CAN Controller ID(CAN IP CAN Controller ID)            */
/*               | uint8 u1MsgBuffer  : Tx MBOX Number                      */
/* Return Value  | None                                                     */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
void
Can_UTxConfirmation( uint8 u1Controller, uint8 u1MsgBuffer )
{
}


/****************************************************************************/
/* Function Name | Can_URxIndication                                        */
/* Description   | Indication for User Reception Completion                 */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller  :                                    */
/*               |   CAN Controller ID(CAN IP CAN Controller ID)            */
/*               | uint8 u1MsgBuffer   : Rx MBOX Number                     */
/*               | CanConstR CanMsgType* ptMsg : Pointer to Rx Message      */
/*               |   uint8* ptData     : Pointer to Rx Data                 */
/*               |   uint32 u4Id       : CAN ID                             */
/*               |   uint8  u1Length   : Data Length                        */
/* Return Value  | uint8 Necessity of Indication for CANIF                  */
/*               |   CAN_PROC_OK : Indication for CANIF is necessary        */
/*               |   CAN_PROC_NG : Indication for CANIF is unnecessary      */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
uint8
Can_URxIndication( uint8 u1Controller, uint8 u1MsgBuffer, CanConstR CanMsgType* ptMsg )
{
    return ((uint8)CAN_PROC_OK);
}


/****************************************************************************/
/* Function Name | Can_UPreStart                                            */
/* Description   | Indication before CAN Controller start                   */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller :                                     */
/*               |   CAN Controller ID(CAN IP CAN Controller ID)            */
/* Return Value  | None                                                     */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
void
Can_UPreStart( uint8 u1Controller )
{
}
/*====== Edit Area when CAN IP Abstraction Function is NOUSE [End] =========*/


#else /* (CAN_CFG_CV == CAN_USE) */
/*====== Edit Area when CAN IP Abstraction Function is USE [Start] =========*/
/****************************************************************************/
/* Function Name | Can_IP0_UTxConfirmation                                  */
/* Description   | Confirmation of User Transmission Completion             */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller :                                     */
/*               |   CAN Controller ID(CAN IP CAN Controller ID)            */
/*               | uint8 u1MsgBuffer  : Tx MBOX Number                      */
/* Return Value  | None                                                     */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
void
Can_IP0_UTxConfirmation( uint8 u1Controller, uint8 u1MsgBuffer )
{
}


/****************************************************************************/
/* Function Name | Can_IP1_UTxConfirmation                                  */
/* Description   | Confirmation of User Transmission Completion             */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller :                                     */
/*               |   CAN Controller ID(CAN IP CAN Controller ID)            */
/*               | uint8 u1MsgBuffer  : Tx MBOX Number                      */
/* Return Value  | None                                                     */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
void
Can_IP1_UTxConfirmation( uint8 u1Controller, uint8 u1MsgBuffer )
{
}


/****************************************************************************/
/* Function Name | Can_IP0_URxIndication                                    */
/* Description   | Indication for User Reception Completion                 */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller  :                                    */
/*               |   CAN Controller ID(CAN IP CAN Controller ID)            */
/*               | uint8 u1MsgBuffer   : Rx MBOX Number                     */
/*               | CanConstR CanMsgType* ptMsg : Pointer to Rx Message      */
/*               |   uint8* ptData     : Pointer to Rx Data                 */
/*               |   uint32 u4Id       : CAN ID                             */
/*               |   uint8  u1Length   : Data Length                        */
/* Return Value  | uint8 Necessity of Indication for CANIF                  */
/*               |   CAN_PROC_OK : Indication for CANIF is necessary        */
/*               |   CAN_PROC_NG : Indication for CANIF is unnecessary      */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
uint8
Can_IP0_URxIndication( uint8 u1Controller, uint8 u1MsgBuffer, CanConstR CanMsgType* ptMsg )
{
    return ((uint8)CAN_PROC_OK);
}


/****************************************************************************/
/* Function Name | Can_IP1_URxIndication                                    */
/* Description   | Indication for User Reception Completion                 */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller  :                                    */
/*               |   CAN Controller ID(CAN IP CAN Controller ID)            */
/*               | uint8 u1MsgBuffer   : Rx MBOX Number                     */
/*               | CanConstR CanMsgType* ptMsg : Pointer to Rx Message      */
/*               |   uint8* ptData     : Pointer to Rx Data                 */
/*               |   uint32 u4Id       : CAN ID                             */
/*               |   uint8  u1Length   : Data Length                        */
/* Return Value  | uint8 Necessity of Indication for CANIF                  */
/*               |   CAN_PROC_OK : Indication for CANIF is necessary        */
/*               |   CAN_PROC_NG : Indication for CANIF is unnecessary      */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
uint8
Can_IP1_URxIndication( uint8 u1Controller, uint8 u1MsgBuffer, CanConstR CanMsgType* ptMsg )
{
    return ((uint8)CAN_PROC_OK);
}


/****************************************************************************/
/* Function Name | Can_IP0_UPreStart                                        */
/* Description   | Indication before CAN Controller start                   */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller :                                     */
/*               |   CAN Controller ID(CAN IP CAN Controller ID)            */
/* Return Value  | None                                                     */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
void
Can_IP0_UPreStart( uint8 u1Controller )
{
}


/****************************************************************************/
/* Function Name | Can_IP1_UPreStart                                        */
/* Description   | Indication before CAN Controller start                   */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller :                                     */
/*               |   CAN Controller ID(CAN IP CAN Controller ID)            */
/* Return Value  | None                                                     */
/* Notes         | See User's Manual                                        */
/****************************************************************************/
void
Can_IP1_UPreStart( uint8 u1Controller )
{
}
/*====== Edit Area when CAN IP Abstraction Function is USE [End] ===========*/
#endif /* (CAN_CFG_CV) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* ((CAN_CFG_IP0 != CAN_IP_NOUSE) && (CAN_CFG_IP1 != CAN_IP_NOUSE)) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2017/04/24                                              */
/*  v2-1-0         :2017/08/31                                              */
/*  v2-1-1         :2017/12/12                                              */
/*  v2-1-2         :2018/04/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
