/* can_rscf4_st_h_m10700_v2-2-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF4/ST/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF4_ST_H
#define     CAN_RSCF4_ST_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_ST_CTRL_UNINIT             (0x6E91U)
#define CAN_ST_CTRL_INIT               (0x6D92U)
#define CAN_ST_CTRL_STOPPED            (0x6B94U)
#define CAN_ST_CTRL_STARTED            (0x57A8U)
#define CAN_ST_CTRL_TO_STOPPED_NML     (0x3EC1U)
#define CAN_ST_CTRL_TO_STOPPED_RST     (0x3DC2U)
#define CAN_ST_CTRL_TO_STARTED         (0x3BC4U)

#define CAN_ST_BRS_USE                 (0x3CU)
#define CAN_ST_BRS_NOUSE               (0x5AU)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void  Can_st_ControllerStop( uint8 u1Controller );
void  Can_st_StopInd( uint8 u1Controller );
void  Can_st_PreStart( uint8 u1Controller );

uint8 Can_st_InitReg( void );
uint8 Can_st_SetControl( uint8 u1Controller );
uint8 Can_st_Start( uint8 u1Controller );
uint8 Can_st_Stop( uint8 u1Controller );
uint8 Can_st_Reset( uint8 u1Controller );
uint8 Can_st_ChkStart( uint8 u1Controller );
uint8 Can_st_ChkStop( uint8 u1Controller );
uint8 Can_st_ChkReset( uint8 u1Controller );
void  Can_st_ShutdownReg( void );
void  Can_st_SetConfigMbox( uint8 u1Controller );
uint8 Can_st_SetBaudrate( uint8 u1Controller, uint16 u2BaudRateConfigID );

void  Can_st_GlobalMode_Reset2Test( void );
void  Can_st_GlobalMode_Any2Reset( void );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern uint16 Can_st_u2ControllerStatus[ CAN_CFG_CONTROLLERNUM_MAX ];

extern uint8  Can_st_u1BRSUse[ CAN_CFG_CONTROLLERNUM_MAX ];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CAN_RSCF4_ST_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2021/12/10                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
