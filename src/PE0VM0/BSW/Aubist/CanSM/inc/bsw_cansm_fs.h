/* bsw_cansm_fs_h_v2-1-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANSM/FS/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANSM_FS_H
#define BSW_CANSM_FS_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/************************/
/* Component internal publication definition */
/************************/
/* Fail return state */
#define BSW_CANSM_u2FS_NO_FAIL         ((BswU2)0x00FFU) /* State that no fail                                */
#define BSW_CANSM_u2FS_FAIL_RCV        ((BswU2)0x01FEU) /* State that wait for transmission to start at fail */
#define BSW_CANSM_u2FS_FAIL_DETECT     ((BswU2)0x02FDU) /* State that fail detection                         */
#define BSW_CANSM_u2FS_FAIL_START_WAIT ((BswU2)0x03FCU) /* State that CAN controller start                   */

/* Mask value for CanIf channel failure detection */
#define BSW_CANSM_u2FS_FAIL_MASK      ((BswU2)(CANIF_FAIL_BUSOFF|CANIF_FAIL_SNDLOCK|CANIF_FAIL_RCVLOCK|CANIF_FAIL_MPU|CANIF_FAIL_USER|CANIF_FAIL_NMTXTIMEOUT_STABLE|CANIF_FAIL_NMTXTIMEOUT_UNSTABLE))

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/************************/
/* Component internal publication definition */
/************************/
/* Structure for maintaining channel status */
typedef struct
{
    BswU2 u2FailRcvState;         /* Fail return state             */
    BswS2 s2FailRcvTimer;         /* Transmission start delay time             */
    BswU2 u2CanIfFailSts;         /* CanIf failure state                */
    BswU1 u1CanCtrlErrSts;        /* Can controller failure state      */
    BswU1 u1Dmy;
} Bsw_CanSM_FsStsType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/************************/
/* Component internal publication definition */
/************************/
void  bsw_cansm_fs_Init( void );
void  bsw_cansm_fs_MainFunction( void );
void  bsw_cansm_fs_ClrFailStatus( void );
void  bsw_cansm_fs_UpdateFailStatus( BswU1 u1ChId );
void  bsw_cansm_fs_NotifyFail( NetworkHandleType Network, BswU2 u2Fail );

/************************/
/* Unit internal public definition       */
/************************/
BswU1    bsw_cansm_fs_ChkCtrlErr( BswU1 u1ChId, BswU2 u2FailState );
BswU1    bsw_cansm_fs_ChkCtrlErrNone( BswU1 u1ChId, BswU2 u2FailState );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/************************/
/* Component internal publication definition */
/************************/
extern Bsw_CanSM_FsStsType       bsw_cansm_fs_stFsSts[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/************************/
/* Unit internal public definition       */
/************************/
extern BswConst BswS2      bsw_cansm_fs_s2BorTimeL1[];
extern BswConst BswS2      bsw_cansm_fs_s2SndRockRestart[];
extern BswU1 (* BswConst bsw_cansm_fs_ptChkCtrlErrFunc[])( BswU1 u1ChId, BswU2 u2FailState );
extern BswConst BswU1      bsw_cansm_fs_u1CtrlStartWait[];


#endif /* BSW_CANSM_FS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/06/02                                             */
/*  v1-1-0          :2018/06/25                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-1-0          :2022/09/08                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
