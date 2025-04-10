/* can_rscf4c_fs_h_m10700_v2-2-0                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF4C/FS/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF4C_FS_H
#define     CAN_RSCF4C_FS_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_FS_REGCHK_NONE          (0U)
#define CAN_FS_REGCHK_EXIST         (1U)
#define CAN_FS_REGCHK_OPT_EXIST     (2U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void  Can_fs_Init( void );
void  Can_fs_ClearBusOffStatus( uint8 u1Controller );
void  Can_fs_BusOffInd( uint8 u1Controller );
void  Can_fs_PrepChkRegRetry( uint8 u1Controller );

uint8 Can_fs_ChkBusOff( uint8 u1Controller );
void  Can_fs_BusOffRecovery( uint8 u1Controller );
uint8 Can_fs_ChkReg( uint8 u1Controller, uint8 u1Time );
uint8 Can_fs_CheckMpu( uint8 u1Controller );
void  Can_fs_ResetInterrupt( uint8 u1Controller );
void  Can_fs_DisableInterrupt( uint8 u1Controller );
uint8 Can_fs_GetErrorStatus( uint8 u1Controller );
uint8 Can_fs_ChkParameter( uint8 u1Controller );
void  Can_fs_PhyInit( void );
void  Can_fs_PhyPrepChkRegRetry( uint8 u1Controller );
void  Can_fs_MpuFailInd( uint8 u1Controller );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CAN_RSCF4C_FS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2021/12/10                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
