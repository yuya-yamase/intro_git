/* can_h_v3-0-0                                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/HEADER                                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     CAN_H
#define     CAN_H

#include <can/common/can_sys.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_T_START                 (0U)
#define CAN_T_STOP                  (1U)
#define CAN_T_SLEEP                 (2U)
#define CAN_T_WAKEUP                (3U)

#define CAN_OK                      (0U)
#define CAN_NOT_OK                  (1U)
#define CAN_BUSY                    (2U)
#define CAN_OPT_NOT_OK              (4U)

#define CAN_ERRST_NOT_OK            (1U)
#define CAN_ERRST_ERROR_ACTIVE      (2U)
#define CAN_ERRST_ERROR_PASSIVE     (4U)
#define CAN_ERRST_BUS_OFF           (8U)

#define CAN_CTRLST_NOT_OK           (1U)
#define CAN_CTRLST_UNINIT           (2U)
#define CAN_CTRLST_INIT             (4U)
#define CAN_CTRLST_STOPPED          (8U)
#define CAN_CTRLST_STARTED          (16U)
#define CAN_CTRLST_TO_STOPPED_NML   (32U)
#define CAN_CTRLST_TO_STOPPED_RST   (64U)
#define CAN_CTRLST_TO_STARTED       (128U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint16          Can_HwHandleType;
typedef uint32          Can_IdType;
typedef uint8           Can_StateTransitionType;
typedef uint8           Can_ReturnType;
typedef uint8           Can_ErrStType;
typedef uint8           Can_CtrlStType;

typedef struct
{
    PduIdType           swPduHandle;
    uint8               length;
    Can_IdType          id;
    uint8*              sdu;
} Can_PduType;

typedef struct
{
    uint8*              ptData;
    uint32              u4Id;
    uint8               u1Length;
} CanMsgType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void               Can_Init( uint8 CanConfigSet );
Can_ReturnType     Can_InitController( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
Can_ReturnType     Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition );
void               Can_MainFunction_Mode( void );
void               Can_Shutdown( void );
void               Can_ResetController( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
Can_ReturnType     Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID );
Can_ReturnType     Can_IP0_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID );
Can_ReturnType     Can_IP1_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID );
Can_ReturnType     Can_CheckStopCompletion( uint8 Controller );
Can_CtrlStType     Can_GetControllerStatus( uint8 Controller );

Can_ReturnType     Can_Write( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo );
void               Can_MainFunction_Write( void );
void               Can_TxFinish_0( void );
void               Can_TxFinish_1( void );
void               Can_TxFinish_2( void );
void               Can_TxFinish_3( void );
void               Can_TxFinish_4( void );
void               Can_TxFinish_5( void );
void               Can_TxFinish_6( void );
void               Can_TxFinish_7( void );
void               Can_TxFinish_8( void );
void               Can_TxFinish_9( void );
void               Can_TxFinish_10( void );
void               Can_TxFinish_11( void );
void               Can_TxFinish_12( void );
void               Can_TxFinish_13( void );
void               Can_TxFinish_14( void );
void               Can_TxFinish_15( void );
Can_ReturnType     Can_AbortSend( Can_HwHandleType Hth );
uint8              Can_TxReq( uint8 u1Controller, uint8 u1MsgBuffer, CanMsgType* ptMsg );
uint8              Can_IP0_TxReq( uint8 u1Controller, uint8 u1MsgBuffer, CanMsgType* ptMsg );
uint8              Can_IP1_TxReq( uint8 u1Controller, uint8 u1MsgBuffer, CanMsgType* ptMsg );

void               Can_MainFunction_Read( void );
void               Can_RxFinish_0( void );
void               Can_RxFinish_1( void );
void               Can_RxFinish_2( void );
void               Can_RxFinish_3( void );
void               Can_RxFinish_4( void );
void               Can_RxFinish_5( void );
void               Can_RxFinish_6( void );
void               Can_RxFinish_7( void );
void               Can_RxFinish_8( void );
void               Can_RxFinish_9( void );
void               Can_RxFinish_10( void );
void               Can_RxFinish_11( void );
void               Can_RxFinish_12( void );
void               Can_RxFinish_13( void );
void               Can_RxFinish_14( void );
void               Can_RxFinish_15( void );

void               Can_MainFunction_BusOff( void );
void               Can_BusOffInterrupt_0( void );
void               Can_BusOffInterrupt_1( void );
void               Can_BusOffInterrupt_2( void );
void               Can_BusOffInterrupt_3( void );
void               Can_BusOffInterrupt_4( void );
void               Can_BusOffInterrupt_5( void );
void               Can_BusOffInterrupt_6( void );
void               Can_BusOffInterrupt_7( void );
void               Can_BusOffInterrupt_8( void );
void               Can_BusOffInterrupt_9( void );
void               Can_BusOffInterrupt_10( void );
void               Can_BusOffInterrupt_11( void );
void               Can_BusOffInterrupt_12( void );
void               Can_BusOffInterrupt_13( void );
void               Can_BusOffInterrupt_14( void );
void               Can_BusOffInterrupt_15( void );
void               Can_IllegalInterrupt_0( void );
void               Can_IllegalInterrupt_1( void );
void               Can_IllegalInterrupt_2( void );
void               Can_IllegalInterrupt_3( void );
void               Can_IllegalInterrupt_4( void );
void               Can_IllegalInterrupt_5( void );
void               Can_IllegalInterrupt_6( void );
void               Can_IllegalInterrupt_7( void );
void               Can_IllegalInterrupt_8( void );
void               Can_IllegalInterrupt_9( void );
void               Can_IllegalInterrupt_10( void );
void               Can_IllegalInterrupt_11( void );
void               Can_IllegalInterrupt_12( void );
void               Can_IllegalInterrupt_13( void );
void               Can_IllegalInterrupt_14( void );
void               Can_IllegalInterrupt_15( void );
void               Can_IllegalInterrupt_Global( void );
void               Can_IP0_IllegalInterrupt_Global( void );
void               Can_IP1_IllegalInterrupt_Global( void );
Can_ReturnType     Can_CheckStuckRegister( uint8 Controller );
void               Can_RefreshRegister( uint8 Controller );
void               Can_MainFunction_Fail( void );
Can_ErrStType      Can_GetErrorStatus( uint8 Controller );

void               Can_EdgeInit( uint8 Controller );
void               Can_EdgeEnableDetect( uint8 Controller );
void               Can_EdgeDisableDetect( uint8 Controller );
void               Can_EdgeClearStatus( uint8 Controller );
Can_ReturnType     Can_EdgeGetStatus( uint8 Controller );

void               Can_URefreshRegister( uint8 Controller );
void               Can_UEdgeInit( uint8 Controller );
void               Can_UEdgeEnableDetect( uint8 Controller );
void               Can_UEdgeDisableDetect( uint8 Controller );
void               Can_UEdgeClearStatus( uint8 Controller );
Can_ReturnType     Can_UEdgeGetStatus( uint8 Controller );
void               Can_UTxConfirmation( uint8 u1Controller, uint8 u1MsgBuffer );
void               Can_IP0_UTxConfirmation( uint8 u1Controller, uint8 u1MsgBuffer );
void               Can_IP1_UTxConfirmation( uint8 u1Controller, uint8 u1MsgBuffer );
uint8              Can_URxIndication( uint8 u1Controller, uint8 u1MsgBuffer, CanConstR CanMsgType* ptMsg );
uint8              Can_IP0_URxIndication( uint8 u1Controller, uint8 u1MsgBuffer, CanConstR CanMsgType* ptMsg );
uint8              Can_IP1_URxIndication( uint8 u1Controller, uint8 u1MsgBuffer, CanConstR CanMsgType* ptMsg );
void               Can_UPreStart( uint8 u1Controller );
void               Can_IP0_UPreStart( uint8 u1Controller );
void               Can_IP1_UPreStart( uint8 u1Controller );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CAN_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-1-0         :2017/12/06                                              */
/*  v2-1-1         :2018/04/04                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
