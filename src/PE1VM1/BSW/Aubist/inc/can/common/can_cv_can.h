/* can_cv_can_h_v3-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/CV/CAN/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_CV_CAN_H
#define     CAN_CV_CAN_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void               Can_IP0_Init( uint8 CanConfigSet );
Can_ReturnType     Can_IP0_InitController( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
Can_ReturnType     Can_IP0_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition );
void               Can_IP0_MainFunction_Mode( void );
void               Can_IP0_Shutdown( void );
void               Can_IP0_ResetController( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
Can_ReturnType     Can_IP0_CheckStopCompletion( uint8 Controller );
Can_CtrlStType     Can_IP0_GetControllerStatus( uint8 Controller );

Can_ReturnType     Can_IP0_Write( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo );
void               Can_IP0_MainFunction_Write( void );
Can_ReturnType     Can_IP0_AbortSend( Can_HwHandleType Hth );

void               Can_IP0_MainFunction_Read( void );

void               Can_IP0_MainFunction_BusOff( void );
Can_ReturnType     Can_IP0_CheckStuckRegister( uint8 Controller );
void               Can_IP0_RefreshRegister( uint8 Controller );
void               Can_IP0_MainFunction_Fail( void );
Can_ErrStType      Can_IP0_GetErrorStatus( uint8 Controller );

void               Can_IP0_EdgeInit( uint8 Controller );
void               Can_IP0_EdgeEnableDetect( uint8 Controller );
void               Can_IP0_EdgeDisableDetect( uint8 Controller );
void               Can_IP0_EdgeClearStatus( uint8 Controller );
Can_ReturnType     Can_IP0_EdgeGetStatus( uint8 Controller );

void               Can_IP1_Init( uint8 CanConfigSet );
Can_ReturnType     Can_IP1_InitController( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
Can_ReturnType     Can_IP1_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition );
void               Can_IP1_MainFunction_Mode( void );
void               Can_IP1_Shutdown( void );
void               Can_IP1_ResetController( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
Can_ReturnType     Can_IP1_CheckStopCompletion( uint8 Controller );
Can_CtrlStType     Can_IP1_GetControllerStatus( uint8 Controller );

Can_ReturnType     Can_IP1_Write( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo );
void               Can_IP1_MainFunction_Write( void );
Can_ReturnType     Can_IP1_AbortSend( Can_HwHandleType Hth );

void               Can_IP1_MainFunction_Read( void );

void               Can_IP1_MainFunction_BusOff( void );
Can_ReturnType     Can_IP1_CheckStuckRegister( uint8 Controller );
void               Can_IP1_RefreshRegister( uint8 Controller );
void               Can_IP1_MainFunction_Fail( void );
Can_ErrStType      Can_IP1_GetErrorStatus( uint8 Controller );

void               Can_IP1_EdgeInit( uint8 Controller );
void               Can_IP1_EdgeEnableDetect( uint8 Controller );
void               Can_IP1_EdgeDisableDetect( uint8 Controller );
void               Can_IP1_EdgeClearStatus( uint8 Controller );
Can_ReturnType     Can_IP1_EdgeGetStatus( uint8 Controller );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* CAN_CV_CAN_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2018/04/04                                              */
/*  v2-0-2         :2021/12/01                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
