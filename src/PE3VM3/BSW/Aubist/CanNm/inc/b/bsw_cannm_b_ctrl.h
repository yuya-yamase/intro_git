/* bsw_cannm_b_ctrl_h_v2-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/B/CTRL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANNM_B_CTRL_H
#define BSW_CANNM_B_CTRL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*-------------------*/
/* Unit internal public definition    */
/*-------------------*/
#define BSW_CANNM_B_u1BUSAWAKE_NONE   ((BswU1)0xF0U)      /* Bus awake factor:None */
#define BSW_CANNM_B_u1BUSAWAKE_EXIST  ((BswU1)0xE1U)      /* Bus awake factor:Exist */

#define BSW_CANNM_B_u1COMCTRL_NOREQ   ((BswU1)0xF0U)      /* Communication Control Request : None */
#define BSW_CANNM_B_u1COMCTRL_REQ     ((BswU1)0xE1U)      /* Communication Control Request : Exist */

#define BSW_CANNM_B_u1ALLBIT_SET      ((BswU1)0xFFU)      /* Macro for bit inversion (1byte)    */

#define BSW_CANNM_B_u2MASK_LOW        ((BswU2)0x00FFU)

/* The upper 1 byte is a mirror value of the lower 1 byte */
#define BSW_CANNM_B_u2ST_DISABLE_TRX          ((BswU2)0x7B84U)
#define BSW_CANNM_B_u2ST_DISABLE_TX           ((BswU2)0x758AU)
#define BSW_CANNM_B_u2ST_RUN                  ((BswU2)0x7C83U)
#define BSW_CANNM_B_u2ST_SLP_WAIT_PWON        ((BswU2)0x6B94U)
#define BSW_CANNM_B_u2ST_SLEEP                ((BswU2)0x6798U)
#define BSW_CANNM_B_u2ST_DISABLE_TX_WU        ((BswU2)0x1FE0U)
#define BSW_CANNM_B_u2ST_STOP                 ((BswU2)0x3EC1U)
#define BSW_CANNM_B_u2ST_INVALID              ((BswU2)0x00FFU)
#define BSW_CANNM_B_u2ST_SLEEP_WAIT           ((BswU2)0x738CU)
#define BSW_CANNM_B_u2ST_SENDWKUP_WAIT        ((BswU2)0x3FC0U)
#define BSW_CANNM_B_u2ST_SLEEP_READY          ((BswU2)0x57A8U)
#define BSW_CANNM_B_u2ST_SHUTDOWN             ((BswU2)0x7689U)

#define BSW_CANNM_B_u1ON                      ((BswU1)0xE1U)
#define BSW_CANNM_B_u1OFF                     ((BswU1)0xF0U)

#define BSW_CANNM_B_MAXDLC                    (8U)

#define BSW_CANNM_B_u2PDUID_WKUP              ((BswU2)0x0000U)
#define BSW_CANNM_B_u2PDUID_NM                ((BswU2)0x0001U)
#define BSW_CANNM_B_u2PDUID_EVENTWAKEUP       ((BswU2)0x0002U)

#define BSW_CANNM_B_u1FRM_BYTEPOS             ((BswU1)1U)       /* NM frame BYTE position               */
#define BSW_CANNM_B_u1FRM_COMREQ_BITPOS       ((BswU1)0x20U)    /* NM frame communication continuation request flag position */
#define BSW_CANNM_B_u1FRM_WKUP_BITPOS         ((BswU1)0x10U)    /* NM frame WKUP identification flag position     */

#define BSW_CANNM_B_u1IDX_0                   ((BswU1)(0U))
#define BSW_CANNM_B_u1IDX_1                   ((BswU1)(1U))
#define BSW_CANNM_B_u1IDX_2                   ((BswU1)(2U))
#define BSW_CANNM_B_u1IDX_3                   ((BswU1)(3U))
#define BSW_CANNM_B_u1IDX_4                   ((BswU1)(4U))
#define BSW_CANNM_B_u1IDX_5                   ((BswU1)(5U))
#define BSW_CANNM_B_u1IDX_6                   ((BswU1)(6U))
#define BSW_CANNM_B_u1IDX_7                   ((BswU1)(7U))

#define BSW_CANNM_B_u4MSK_CANFD               (0xBFFFFFFFUL)    /* CAN-FD Message Mask */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*-------------------*/
/* Unit internal public definition    */
/*-------------------*/
/* State by channel */
typedef struct
{
    BswU2  u2NmSt;                  /* NM status                                   */
    BswU2  u2SendWaitTimer;         /* Tansmission waiting timer                           */
    BswU2  u2SleepWaitTimer;        /* State transition wait timer                       */
    BswU2  u2WkupTxTimeoutTimer;    /* Timer waiting for completion of wake-up frame transmission */
    BswU2  u2NmTxTimer;             /* NM frame regular transmission timer                 */
    BswU1  u1ChPower;               /* Channel power on/off                         */
    BswU1  u1dmy;                   /* Dummy (For future extension)                       */
} Bsw_CanNmB_ChStsType;

/* Events by Channel */
typedef struct
{
    BswU1  u1SendWkup;              /* Wake-up frame transmission completion flag     */
    BswU1  u1BusAwakeOther;         /* Temporary memory of the other-node bus wake-up factor       */
    BswU1  u1BusAwakeInf;           /* Temporary storage of own-node bus-awake factor       */
} Bsw_CanNmB_ChEvtType;

/* By Channel Received NM message information */
typedef struct
{
    BswU4  u4CanID;             /* CANID of received NM message                          */
    BswU1  u1ComReqFlagBytePos; /* Position of the communication continuation request flag byte of the received NM message   */
    BswU1  u1ComReqFlagMask;    /* Position of the communication continuation request flag bit of the received NM message   */
    BswU1  u1WakeupFlagBytePos; /* Position of the wake-up flag byte in the received NM message */
    BswU1  u1WakeupFlagMask;    /* Position of the wake-up flag bit in the received NM message */
}Bsw_CanNmB_RxMsgCfgType;

/* By Channel Transmission NM message information */
typedef struct
{
    BswU1  u1Dlc;               /* DLC                                              */
    BswU1  u1ComReqFlagBytePos; /* Location of the communication continuity request flag byte in the transmission NM message   */
    BswU1  u1ComReqFlagMask;    /* Location of the communication continuity request flag bit in the transmission NM message   */
    BswU1  u1WakeupFlagBytePos; /* Location of the wake-up flag byte in the transmission NM message */
    BswU1  u1WakeupFlagMask;    /* Location of the wake-up flag bit in the transmission NM message */
}Bsw_CanNmB_TxMsgCfgType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*-------------------*/
/* Unit internal public definition    */
/*-------------------*/
Std_ReturnType bsw_cannm_b_ctrl_JudgeWuFrame( BswU1 u1NetID, BswU4 u4RxCanID, BswU1 u1Len, BswConstR BswU1* ptDat );
void bsw_cannm_b_ctrl_RxComReq( BswU1 u1NetID, BswU4 u4RxCanID, BswU1 u1Len, BswConstR BswU1 *ptDat );
void bsw_cannm_b_ctrl_SetComReq( BswU1 u1NetID, BswU1 u1Len, BswU1 *ptDat );

void bsw_cannm_b_ctrl_TransNmFrame( BswU1 u1NetID );
void bsw_cannm_b_ctrl_TransWkupFrame( BswU1 u1NetID );
void bsw_cannm_b_ctrl_TransWkupCtrl( BswU1 u1NetID );
void bsw_cannm_b_ctrl_TransWkupNn( BswU1 u1NetID );

void bsw_cannm_b_ctrl_RxComReqNone( BswU1 u1NetID, BswU4 u4RxCanID, BswU1 u1Len, BswConstR BswU1 *ptDat );
void bsw_cannm_b_ctrl_SetComReqNone( BswU1 u1NetID, BswU1 u1Len, BswU1 *ptDat );

BswU1 bsw_cannm_b_ctrl_ChkU2Dat( BswU2 u2Dat );
BswU1 bsw_cannm_b_ctrl_TransmitFrame( BswU1 u1NetID, BswU1 u1Len, BswU1* ptDat, BswU2 u2PduId ); /* Transmit NM message */

void  bsw_cannm_b_ctrl_InitEvtWkup( void );
void  bsw_cannm_b_ctrl_InitEvtWkupNn( void );
void  bsw_cannm_b_ctrl_ClrEvtWkupReq( BswU1 u1NetID );
void  bsw_cannm_b_ctrl_ClrEvWkupRqNn( BswU1 u1NetID );
void  bsw_cannm_b_ctrl_TxEvtWkupFr( BswU1 u1NetID, BswU1 u1BusAwake );
void  bsw_cannm_b_ctrl_TxEvtWkupFrNn( BswU1 u1NetID, BswU1 u1BusAwake );
void  bsw_cannm_b_ctrl_EvWkCnfNotInd( NetworkHandleType nmNetworkHandle, uint16 DisableTime );

void  bsw_cannm_b_ctrl_InitComCtrl( void );
void  bsw_cannm_b_ctrl_InitComCtrlNn( void );
BswU1 bsw_cannm_b_ctrl_GetComCtrlSts( BswU1 u1NetID );
BswU1 bsw_cannm_b_ctrl_GetCmCtrlStsNn( BswU1 u1NetID );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*-------------------*/
/* Unit internal public definition    */
/*-------------------*/
extern Bsw_CanNmB_ChStsType    bsw_cannm_b_stChSts[];
extern Bsw_CanNmB_ChEvtType    bsw_cannm_b_stChEvt[];
extern BswU2                   bsw_cannm_b_u2RxNmMsgIndex[];
extern BswU1                   bsw_cannm_b_ctrl_u1EvtWkupReq[];
extern BswU1                   bsw_cannm_b_ctrl_u1ComCtrlReq[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/*-------------------*/
/* Unit internal public definition    */
/*-------------------*/
extern BswConst Bsw_CanNmB_RxMsgCfgType bsw_cannm_b_RxMsgCfgTbl[];
extern BswConst Bsw_CanNmB_TxMsgCfgType bsw_cannm_b_TxMsgCfgTbl[];

extern BswConst BswU2 bsw_cannm_b_ctrl_u2DisableTime;
extern BswConst BswU1 bsw_cannm_b_ctrl_u1MaxCh;            /* Maximum number of channels                         */
extern BswConst BswU1 bsw_cannm_b_ctrl_u1ChOffset;         /* Channel offset                     */
extern BswConst BswU2 bsw_cannm_b_ctrl_u2RxMsgIndex[];     /* Location information for received NM message definitions         */
extern BswConst BswU2 bsw_cannm_b_ctrl_u2SndStrtDrv[];     /* Transmission start wait time at power-on               */
extern BswConst BswU2 bsw_cannm_b_ctrl_u2SndStrtWkup;      /* Transmission starting wait time at bus wake-up   */
extern BswConst BswU2 bsw_cannm_b_ctrl_u2SndStrtFail;      /* Fail-safe time of transmission start waiting timer   */
extern BswConst BswU2 bsw_cannm_b_ctrl_u2TxToutWuFrm;      /* WKUP frame transmission completion wait time           */
extern BswConst BswU2 bsw_cannm_b_ctrl_u2SlpWaitTime;      /* State transition wait time                       */
extern BswConst BswU2 bsw_cannm_b_ctrl_u2NmTxTime[];       /* NM message transmission interval                   */
extern BswConst BswU1 bsw_cannm_b_ctrl_u1Channel[];        /* Channel used/not used table           */
extern BswConst BswU1 bsw_cannm_b_ctrl_u1BusSleepTbl[];    /* Table to judge whether bus-sleep is used or not   */
extern BswConst BswU1 bsw_cannm_b_ctrl_u1ComIf[];          /* Use/Unuse table for NM message notification */

extern void    (* BswConst bsw_cannm_b_ctrl_ptRxComReqFunc)( BswU1 u1NetID, BswU4 u4RxCanID, BswU1 u1Len, BswConstR BswU1* ptDat );
extern void    (* BswConst bsw_cannm_b_ctrl_ptSetComReqFn)( BswU1 u1NetID, BswU1 u1Len, BswU1* ptDat );
extern void    (* BswConst bsw_cannm_b_ctrl_ptTrnsWkupFunc)( BswU1 u1NetID );

extern void    (* BswConst bsw_cannm_b_ctrl_InitEvWkupFunc)( void );
extern void    (* BswConst bsw_cannm_b_ctrl_ClrEvWkReqFunc)( BswU1 u1NetID );
extern void    (* BswConst bsw_cannm_b_ctrl_TxEvWkReqFunc)( BswU1 u1NetID, BswU1 u1BusAwake );
extern void    (* BswConst bsw_cannm_b_ctrl_EvWkCnfIndFunc)( NetworkHandleType nmNetworkHandle, uint16 DisableTime );
extern void    (* BswConst bsw_cannm_b_ctrl_InitComFunc)( void );
extern BswU1   (* BswConst bsw_cannm_b_ctrl_GetCmCtStsFunc)( BswU1 u1NetID );

#endif /* BSW_CANNM_B_CTRL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/06/26                                             */
/*  v1-1-0          :2018/11/15                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
