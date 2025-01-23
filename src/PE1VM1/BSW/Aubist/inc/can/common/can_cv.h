/* can_cv_h_v2-0-2                                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/CV/HEADER                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_CV_H
#define     CAN_CV_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_CV_IP0_CONTROLLERNUM_MAX   (8U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    void                (*Init)( uint8 CanConfigSet );
    Can_ReturnType      (*InitController)( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
    Can_ReturnType      (*SetControllerMode)( uint8 Controller, Can_StateTransitionType Transition );
    void                (*MainFunction_Mode)( void );
    void                (*Shutdown)( void );
    void                (*ResetController)( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
    Can_ReturnType      (*CheckStopCompletion)( uint8 Controller );
    Can_CtrlStType      (*GetControllerStatus)( uint8 Controller );
    Can_ReturnType      (*Write)( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo );
    void                (*MainFunction_Write)( void );
    Can_ReturnType      (*AbortSend)( Can_HwHandleType Hth );
    void                (*MainFunction_Read)( void );
    void                (*MainFunction_BusOff)( void );
    Can_ReturnType      (*CheckStuckRegister)( uint8 Controller );
    void                (*RefreshRegister)( uint8 Controller );
    void                (*MainFunction_Fail)( void );
    Can_ErrStType       (*GetErrorStatus)( uint8 Controller );
    void                (*EdgeInit)( uint8 Controller );
    void                (*EdgeEnableDetect)( uint8 Controller );
    void                (*EdgeDisableDetect)( uint8 Controller );
    void                (*EdgeClearStatus)( uint8 Controller );
    Can_ReturnType      (*EdgeGetStatus)( uint8 Controller );
} CanCvFuncTbType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void               Can_MainFunction_Write_Dummy( void );
Can_ReturnType     Can_Write_Dummy( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo );
Can_ReturnType     Can_AbortSend_Dummy( Can_HwHandleType Hth );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern CanConst uint16 Can_cv_ip0_u2HrhNum;
extern CanConst uint16 Can_cv_ip1_u2HrhNum;
extern CanConst uint16 Can_cv_ip0_u2HohNum;

extern CanConst CanCvFuncTbType Can_cv_ip0_stFuncTbl;
extern CanConst CanCvFuncTbType Can_cv_ip1_stFuncTbl;


#endif /* CAN_CV_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2018/04/04                                              */
/*  v2-0-2         :2021/12/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
