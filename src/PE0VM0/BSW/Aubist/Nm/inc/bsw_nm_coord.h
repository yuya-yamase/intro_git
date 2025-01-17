/* bsw_nm_coord_h_v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/NM/COORD/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_NM_COORD_H
#define BSW_NM_COORD_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_NM_u1TIMER_ON            ((BswU1)0x0FU)       /* Shutdown timer measurement flag ON */
#define BSW_NM_u1TIMER_OFF           ((BswU1)0x1EU)       /* Shutdown timer measurement flag OFF */
#define BSW_NM_u2TIME_STOP           ((BswU2)0U)          /* Timer stopping value */
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* NM timer definition structure */
typedef struct
{
    BswU2 u2ShutdownTimer;     /* Shutdown timer                       */
    BswU1 u1ShutdownTimerOn;   /* Flag for shutdown timer measurement availability       */
    BswU1 u1TimDummy;          /* Dummy */
} Bsw_Nm_CoordTimStsType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void             bsw_nm_coord_MainFunction( void );
void             bsw_nm_coord_Init( void );
void             bsw_nm_coord_InitSleepSync( void );
void             bsw_nm_coord_InitSleepSyncNone( void );
void             bsw_nm_coord_DelaySleep( void );
void             bsw_nm_coord_DelaySleepNone( void );
void             bsw_nm_coord_StopSyncSleep( NetworkHandleType NetworkHandle );
void             bsw_nm_coord_StopSleepDelay( NetworkHandleType NetworkHandle );
Std_ReturnType   bsw_nm_coord_RequestBusSyncNone( NetworkHandleType nmChannelHandle );
Std_ReturnType   bsw_nm_coord_CancelSyncPncSlpNone( NetworkHandleType nmNetworkHandle, PNCHandleType PNC );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern Bsw_Nm_CoordTimStsType      bsw_nm_coord_stTimSts[];                  /* Timer state  */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern void                      (* BswConst bsw_nm_coord_ptInitSlpSyncFunc)( void );
extern void                      (* BswConst bsw_nm_coord_ptDelaySleepFunc)( void );
extern Std_ReturnType            (* BswConst bsw_nm_coord_ptRqBusSyncFuncTbl[])( NetworkHandleType nmChannelHandle );
extern Std_ReturnType            (* BswConst bsw_nm_coord_ptCancelSyncPncSlpFn)( NetworkHandleType nmNetworkHandle, PNCHandleType PNC );

extern BswConst BswU2            bsw_nm_coord_ShutdownTim[];                  /* Shutdown time */
extern BswConst BswU2            bsw_nm_coord_u2MaxShutdownTim;               /* Maximum value of the shutdown timer */

#endif /* BSW_NM_COORD_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v2-0-0          :2022/01/06                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
