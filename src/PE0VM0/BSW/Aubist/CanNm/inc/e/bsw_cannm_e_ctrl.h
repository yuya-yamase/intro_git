/* bsw_cannm_e_ctrl_h_v2-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/E/CTRL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_E_CTRL_H
#define BSW_CANNM_E_CTRL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* NM state (internal) */
#define BSW_CANNM_E_u2ST_DISABLE_TRX         ((BswU2)0x01FEU)
#define BSW_CANNM_E_u2ST_PWON_WAIT           ((BswU2)0x02FDU)
#define BSW_CANNM_E_u2ST_WAKE_CHECK          ((BswU2)0x03FCU)
#define BSW_CANNM_E_u2ST_BUS_SLEEP           ((BswU2)0x04FBU)
#define BSW_CANNM_E_u2ST_PREP_BUS_SLP        ((BswU2)0x05FAU)
#define BSW_CANNM_E_u2ST_READY_SLEEP         ((BswU2)0x06F9U)
#define BSW_CANNM_E_u2ST_WAKE_PASSIVE        ((BswU2)0x07F8U)
#define BSW_CANNM_E_u2ST_WAKE_ACTIVE         ((BswU2)0x08F7U)
#define BSW_CANNM_E_u2ST_NORMAL_OPE          ((BswU2)0x09F6U)
#define BSW_CANNM_E_u2ST_RPT_MSG             ((BswU2)0x0AF5U)
#define BSW_CANNM_E_u2ST_PREP_BUS_WKUP       ((BswU2)0x0BF4U)
#define BSW_CANNM_E_u2ST_SHUTDOWN            ((BswU2)0x0CF3U)
#define BSW_CANNM_E_u2ST_SLEEP               ((BswU2)0x0DF2U)
#define BSW_CANNM_E_u2ST_INVALID             ((BswU2)0x0EF1U)

/* Mask position */
#define BSW_CANNM_E_u2MASK_HIGH              ((BswU2)0xFF00U)
#define BSW_CANNM_E_u2MASK_LOW               ((BswU2)0x00FFU)

/* Bit shift */
#define BSW_CANNM_E_SHIFT_1BYTE              (8U)

/* Bus awake factor */
#define BSW_CANNM_E_u1BUSAWAKE_NONE          ((BswU1)0x0FU)    /* No bus awake factor */
#define BSW_CANNM_E_u1BUSAWAKE_EXIST         ((BswU1)0x1EU)    /* Bus Awake factor exists */

/* Communication Control Request */
#define BSW_CANNM_E_u1COMCTRL_NOREQ          ((BswU1)0x0FU)    /* Communication Control Request : None */
#define BSW_CANNM_E_u1COMCTRL_REQ            ((BswU1)0x1EU)    /* Communication Control Request : Exist */

/* Receive state */
#define BSW_CANNM_E_u1RX_NONE                ((BswU1)0x00U)    /* No receive Awake   */
#define BSW_CANNM_E_u1RX_AWAKE               ((BswU1)0x01U)    /* AWAKE available         */
#define BSW_CANNM_E_u1RX_EXIST               ((BswU1)0x02U)    /* Receiving exists          */

/* Timer stopping value      */
#define BSW_CANNM_E_u2TIME_STOP              ((BswU2)0U)

/* Initial value of received frame data */
#define BSW_CANNM_E_u1RXDATA_INIT            ((BswU1)0xA5U)

/* Channel power supply */
#define BSW_CANNM_E_u1PWSUPPLY_ON            ((BswU1)0x0FU)    /* Channel power ON    */
#define BSW_CANNM_E_u1PWSUPPLY_OFF           ((BswU1)0x1EU)    /* Channel power OFF   */

/* Action Type */
#define BSW_CANNM_E_u1TYPE_MASTER            ((BswU1)0x00U)    /* Master */
#define BSW_CANNM_E_u1TYPE_SLAVE             ((BswU1)0x01U)    /* Slave */

/* Receiving log */
#define BSW_CANNM_E_u1RXHISTORY_EXIST        ((BswU1)0x0FU)    /* ECU frame Receiving log available */
#define BSW_CANNM_E_u1RXHISTORY_NONE         ((BswU1)0x1EU)    /* ECU frame No Receiving log  */

/* Receive ECU frame */
#define BSW_CANNM_E_u1RXECUFRM_EXIST         ((BswU1)0x0FU)    /* ECU frame received exists      */
#define BSW_CANNM_E_u1RXECUFRM_NONE          ((BswU1)0x1EU)    /* No ECU frame received      */

/* Transmission state */
#define BSW_CANNM_E_u1TXREQMODE_REQ          ((BswU1)0x0FU)    /* WakeUp frame transmission request in progress         */
#define BSW_CANNM_E_u1TXREQMODE_NOREQ        ((BswU1)0x1EU)    /* WakeUp frame transmission request is not in progress */

/* Judge the transition from reset startup */
#define BSW_CANNM_E_u1TRNSRESETACTV_ON       ((BswU1)0x0FU)    /* Transition from reset startup         */
#define BSW_CANNM_E_u1TRNSRESETACTV_OFF      ((BswU1)0x1EU)    /* Not a transition from reset startup */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Structure for maintaining channel status */
typedef struct
{
    BswU2 u2NmSt;                /* NM status                                    */
    BswU2 u2NmStateTimer;        /* State transition timer (WAKEUP,APPLICATION,SLEEP)  */
    BswU2 u2SndSlpTimer;         /* Stop transmitting monitoring timer(SEND_SLEEP)            */
    BswU2 u2PwonWaitTimer;       /* CPU awake hold timer at power-on           */
    BswU1 u1BusAwakeEcu;         /* ECU activation factors                               */
    BswU1 u1BusAwakeSelf;        /* Own-node bus wake-up factor            */
    BswU1 u1PassiveEvent;        /* Other-node bus wake-up factor            */
    BswU1 u1StateChgAwake;       /* Awake factor at state transition                  */
    BswU1 u1ChPower;             /* Channel power on/off                          */

    BswU1 u1RxEvent;             /* NM information received or not                            */
    BswU1 u1RxEcuFrm;            /* Update whether ECU frames are received                   */
    BswU1 u1RxEcuFrmFix;         /* Determine whether ECU frame are received                   */
    BswU1 u1RxEcuFrmHistory;     /* Hold whether ECU frames are received                    */
    BswU1 u1WkUpFrmTxReqMode;    /* WakeUp frame transmission completion or not                */
    BswU1 u1TrnsRstActvFlg;      /* Judge the transition from reset startup                */
    BswU1 u1Dummy;               /* Padding for alignment adjustment      */
} Bsw_CanNmE_ChStsType;

/* By Channel Received NM message information */
typedef struct
{
    BswU4  u4CanID;                 /* CANID of received NM message              */
    BswU1  u1RxWkupSlpFlagBytePos;  /* NM information byte position of received NM message   */
    BswU1  u1RxWkupSlpFlagBitPos;   /* NM information bit position of received NM message   */
    BswU2  u2DummyPad;              /* Padding for alignment adjustment */
}Bsw_CanNmE_RxMsgCfgType;

/* By Channel Transmission NM message information */
typedef struct
{
    BswU1  u1TxWkupSlpFlagBytePos;  /* Location of the NM information byte in the transmission NM message */
    BswU1  u1TxWkupSlpFlagBitPos;   /* Location of the NM information bit in the transmission NM message */
}Bsw_CanNmE_TxMsgCfgType;

/* Received state by message received */
typedef struct
{
    BswU2  u2RecvTimer;       /* Per-frame receive monitoring timer (JudgeMent)   */
    BswU1  u1RecvData;        /* NM information receiving state for each frame              */
    BswU1  u1DummyPad;        /* Padding for alignment adjustment    */
}Bsw_CanNmE_RxMsgStsType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* Component internal publication definition */
void     bsw_cannm_e_ctrl_RdySlpMst( BswU1 u1NetID, BswU1 u1RxStatus );
void     bsw_cannm_e_ctrl_POWaitMst( BswU1 u1NetID, BswU1 u1RxStatus );
void     bsw_cannm_e_ctrl_PrpWkUpMst( BswU1 u1NetID, BswU1 u1RxStatus );
void     bsw_cannm_e_ctrl_NrmlOpeMst( BswU1 u1NetID, BswU1 u1RxStatus );
void     bsw_cannm_e_ctrl_SendWakeUpFrm( BswU1 u1NetID );
void     bsw_cannm_e_ctrl_AbortWakeUpFrm( BswU1 u1NetID );
void     bsw_cannm_e_ctrl_InitComCtrl( void );
BswU1    bsw_cannm_e_ctrl_GetComCtrlSts( BswU1 u1NetID );

/* Component internal publication definition (Dummy function) */
void     bsw_cannm_e_ctrl_RdySlpMstNone( BswU1 u1NetID, BswU1 u1RxStatus );
void     bsw_cannm_e_ctrl_POWaitMstNone( BswU1 u1NetID, BswU1 u1RxStatus );
void     bsw_cannm_e_ctrl_PrpWkUpMstNone( BswU1 u1NetID, BswU1 u1RxStatus );
void     bsw_cannm_e_ctrl_NrmlOpeMstNone( BswU1 u1NetID, BswU1 u1RxStatus );
void     bsw_cannm_e_ctrl_SndWkUpFrmNone( BswU1 u1NetID );
void     bsw_cannm_e_ctrl_AbtWkUpFrmNone( BswU1 u1NetID );
void     bsw_cannm_e_ctrl_InitComCtrlNn( void );
BswU1    bsw_cannm_e_ctrl_GetCmCtrlStsNn( BswU1 u1NetID );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern Bsw_CanNmE_ChStsType             bsw_cannm_e_ctrl_stChSts[];                    /* NM status                                */
extern Bsw_CanNmE_RxMsgStsType          bsw_cannm_e_ctrl_stRxMsgSts[];                 /* Receive state                              */
extern BswU1                            bsw_cannm_e_ctrl_u1ComCtrlReq[];               /* Communication restriction request state                      */


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1                   bsw_cannm_e_ctrl_u1ChNum;                      /* Maximum number of channels                */
extern BswConst BswU1                   bsw_cannm_e_ctrl_u1ChOffset;                   /* Channel offset            */
extern BswConst BswU2                   bsw_cannm_e_ctrl_u2PwOnWaitTim;                /* CPU awake holding time at power-on */
extern BswConst BswU2                   bsw_cannm_e_ctrl_u2NmStateTim;                 /* NM state transition timer(NmStateTimer)*/

extern void    (* BswConst bsw_cannm_e_ctrl_ptProcRdySlpFn )( BswU1 u1NetID, BswU1 u1RxStatus ); /* Connection of prepare bus-sleep state processing functions       */
extern void    (* BswConst bsw_cannm_e_ctrl_ptProcPOWaitFn )( BswU1 u1NetID, BswU1 u1RxStatus ); /* Connection of bus sleep state processing function at power-on   */
extern void    (* BswConst bsw_cannm_e_ctrl_ptProcPrpWupFn )( BswU1 u1NetID, BswU1 u1RxStatus ); /* Connect the bus wake-up wait state processing function */
extern void    (* BswConst bsw_cannm_e_ctrl_ptProcNmlOpeFn )( BswU1 u1NetID, BswU1 u1RxStatus ); /* Connection of normal operation state processing function               */
extern void    (* BswConst bsw_cannm_e_ctrl_ptInitComFunc)( void );                              /* Connecting a function to initialize the transmission limitation function           */
extern BswU1   (* BswConst bsw_cannm_e_ctrl_ptGtCmCtStFunc)( BswU1 u1NetID );                    /* Connecting the function to get the enable/disable of the transmission limitation request         */

extern BswConst BswU1                   bsw_cannm_e_ctrl_u1Channel[];                  /* Channel used/not used table         */
extern BswConst BswU1                   bsw_cannm_e_ctrl_u1BusSleepTbl[];              /* Table to judge whether bus-sleep is used or not */
extern BswConst BswU1                   bsw_cannm_e_ctrl_u1CtrlTypeTbl[];              /* Master/slave judgment table       */

extern BswConst BswU2                   bsw_cannm_e_ctrl_u2WakeUpMsTim[];              /* Wake-up wait time(WakeUpTimer)(ms timer)         */
extern BswConst BswU2                   bsw_cannm_e_ctrl_u2AppTim[];                   /* Repeat message state maintenance period (ApplicationTimer)                */
extern BswConst BswU2                   bsw_cannm_e_ctrl_u2WaitSlpTim[];               /* Sleep transition waiting time(SleepTimer)                      */
extern BswConst BswU2                   bsw_cannm_e_ctrl_u2SndSlpTim[];                /* Transmission stop wait time during bus sleep transition (SendSleepTimer)  */
extern BswConst BswU2                   bsw_cannm_e_ctrl_u2RxTimeOut[];                /* NM frame receiving monitoring time                                */
extern BswConst BswU2                   bsw_cannm_e_ctrl_u2RxMsgIndex[];               /* Location information for received NM message definitions                        */
extern BswConst BswU1                   bsw_cannm_e_ctrl_u1WkupFrmLen[];               /* Length of wake-up frame                          */

extern void    (* BswConst bsw_cannm_e_ctrl_ptSndWkUpFrmFn[] )( BswU1 u1NetID );       /* Connection of the wake-up frame transmission function */
extern void    (* BswConst bsw_cannm_e_ctrl_ptAbtWkUpFrmFn[] )( BswU1 u1NetID );       /* Connection of the wake-up frame transmission cancellation function */

extern BswConst Bsw_CanNmE_RxMsgCfgType bsw_cannm_e_RxMsgCfgTbl[];                     /* Received NM message definition */
extern BswConst Bsw_CanNmE_TxMsgCfgType bsw_cannm_e_TxMsgCfgTbl[];                     /* Define the transmission NM message */


#endif  /* BSW_CANNM_E_CTRL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2019/02/01                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
