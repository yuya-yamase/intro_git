/* can_rscf3c_st_h_m10700_v3-0-0                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF3C/ST/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF3C_ST_H
#define     CAN_RSCF3C_ST_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* CANコントローラ状態 */
#define CAN_ST_CTRL_UNINIT             (0x6E91U)            /* 未初期化     */
#define CAN_ST_CTRL_INIT               (0x6D92U)            /* 初期化済     */
#define CAN_ST_CTRL_STOPPED            (0x6B94U)            /* 通信停止     */
#define CAN_ST_CTRL_STARTED            (0x57A8U)            /* 通信中       */
#define CAN_ST_CTRL_TO_STOPPED_NML     (0x3EC1U)            /* 通信停止待ち */
#define CAN_ST_CTRL_TO_STOPPED_RST     (0x3DC2U)            /* 再初期化待ち */
#define CAN_ST_CTRL_TO_STARTED         (0x3BC4U)            /* 通信開始待ち */

/* ビットレートスイッチ使用/未使用 */
#define CAN_ST_BRS_USE                 (0x3CU)              /* ビットレートスイッチ使用   */
#define CAN_ST_BRS_NOUSE               (0x5AU)              /* ビットレートスイッチ未使用 */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/**********************/
/* CAN共通部項目      */
/**********************/
void  Can_st_ControllerStop( uint8 u1Controller );
void  Can_st_StopInd( uint8 u1Controller );
void  Can_st_PreStart( uint8 u1Controller );


/**********************/
/* マイコン依存部項目 */
/**********************/
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
/**********************/
/* CAN共通部項目      */
/**********************/
/* CANコントローラ状態 */
/* 設計上の留意点                                                       */
/*   別ユニットから本変数を直接更新することは禁止し、参照のみ許可する。 */
extern uint16 Can_st_u2ControllerStatus[ CAN_CFG_CONTROLLERNUM_MAX ];


/**********************/
/* マイコン依存部項目 */
/**********************/
/* BRS設定値 */
/* 設計上の留意点                                                       */
/*   別ユニットから本変数を直接更新することは禁止し、参照のみ許可する。 */
extern uint8  Can_st_u1BRSUse[ CAN_CFG_CONTROLLERNUM_MAX ];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CAN_RSCF3C_ST_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2020/02/26                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
