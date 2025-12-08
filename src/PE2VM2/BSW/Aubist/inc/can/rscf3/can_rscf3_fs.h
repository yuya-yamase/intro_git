/* can_rscf3_fs_h_m10700_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF3/FS/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF3_FS_H
#define     CAN_RSCF3_FS_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_FS_REGCHK_NONE          (0U)        /* レジスタ固着なし                         */
#define CAN_FS_REGCHK_EXIST         (1U)        /* レジスタ固着検出                         */
#define CAN_FS_REGCHK_OPT_EXIST     (2U)        /* レジスタ固着検出(未使用MBOXでの固着検出) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/**********************/
/* CAN共通部項目      */
/**********************/
void  Can_fs_Init( void );
void  Can_fs_ClearBusOffStatus( uint8 u1Controller );
void  Can_fs_BusOffInd( uint8 u1Controller );
void  Can_fs_PrepChkRegRetry( uint8 u1Controller );

/**********************/
/* マイコン依存部項目 */
/**********************/
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


#endif  /* CAN_RSCF3_FS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-1-0         :2017/08/31                                              */
/*  v2-2-0         :2020/02/26                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
