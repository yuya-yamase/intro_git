/* bsw_cannm_a_nmcfgtbl_v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A/NMCFGTBL/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANNM_A_NMCFGTBL_H
#define BSW_CANNM_A_NMCFGTBL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*** CANNM TABLE DEFINITION ***/
/* CanNmA Channel setting */
#define BSW_CANNM_A_NONECH                  (0xffU)     /* No NM function for channel               */

/* NM Message related definitions */
#define BSW_CANNM_A_MSG_DATA_LEN            (6U)        /* NM Msg Data length                      */
#define BSW_CANNM_A_MSGQUE_LEN              (32U)       /* NM Msg Maximum number of storage                  */
#define BSW_CANNM_A_MSGQUE_MASK             (0x1fU)     /* NM Msg Stored maximum number mask(LEN(32)-1) */
#define BSW_CANNM_A_MSGQUE_MASK_REV         (0xe0U)     /* NM Msg Stored maximum number mask inversion value      */
#define BSW_CANNM_A_MSGQUE_MASK_NONE        (0x00U)     /* NM Msg Stored maximum number mask(0)         */
#define BSW_CANNM_A_OPCODE_NONE             (0x00U)     /* NM Msg OpCode Bit None             */
#define BSW_CANNM_A_OPCODE_SLPACK           (0x20U)     /* NM Msg OpCode Bit SleepAck         */
#define BSW_CANNM_A_OPCODE_SLPACK_REV       (0xdfU)     /* NM Msg OpCode Bit SleepAck inverted value   */
#define BSW_CANNM_A_OPCODE_SLPIND           (0x10U)     /* NM Msg OpCode Bit SleepInd         */
#define BSW_CANNM_A_OPCODE_SLPIND_REV       (0xefU)     /* NM Msg OpCode Bit SleepInd inverted value   */
#define BSW_CANNM_A_OPCODE_LIMPH            (0x04U)     /* NM Msg OpCode Bit LimpHome         */
#define BSW_CANNM_A_OPCODE_RING             (0x02U)     /* NM Msg OpCode Bit Ring             */
#define BSW_CANNM_A_OPCODE_ALIVE            (0x01U)     /* NM Msg OpCode Bit Alive            */
#define BSW_CANNM_A_NODEID_INVALID          (0x00U)     /* Node ID disabled value                     */

/* Timer definition */
#define BSW_CANNM_A_TIMER_TBLMAX            (16U)       /* Number of timers                           */

#define BSW_CANNM_A_TIMER_CNT_TBL_SIZE      (3U)        /* Maximum number of timers to hold (CVT-NM, OSEK-NM)   */

/* Event definition */
#define BSW_CANNM_A_EVT_QMAX                (8U)        /* Number of event queues CVT,OSEK        */

/*** CanNmA COMMON DEFINITION ***/
#define BSW_CANNM_A_CANNM_CLR               (0U)        /* CanNm Common Definitions:Cleared                */
#define BSW_CANNM_A_CANNM_SET               (1U)        /* CanNm Common Definitions:Set                */

#define BSW_CANNM_A_COMMON_CVT              (1U)        /* CanNm Common Definitions:CVT-NM                */
#define BSW_CANNM_A_COMMON_OSEK             (2U)        /* CanNm Common Definitions:OSEK-NM               */

#define BSW_CANNM_A_COMMON_IDX00            (0U)        /* CanNm Common Definitions:Index 0           */

#define BSW_CANNM_A_COMMON_OFF              (0xe1U)     /* CanNm Common Definitions:OFF                   */
#define BSW_CANNM_A_COMMON_ON               (0xd2U)     /* CanNm Common Definitions:ON                    */

#define BSW_CANNM_A_u1ALLBIT_SET            ((BswU1)0xffU)  /* Macro for bit inversion (1byte)      */
#define BSW_CANNM_A_u2ALLBIT_SET            ((BswU2)0xffffU)/* Macro for bit inversion (2byte)      */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Type definition for configuration */
typedef struct
{
    BswU1  u1Node;                /* Own channel node ID          */
    BswU1  u1ImmOffsetUse;        /* Enables/disables use of periodic transmit offset during immediate bus wake-up */
    BswU1  u1BusSleepUse;         /* Bus-sleep used/not used        */
    BswU1  u1MsgData[BSW_CANNM_A_MSG_DATA_LEN]; /* NM Data section */
} Bsw_CanNmA_STConfgTblChType;

/* CONTROL Type Definition */
typedef struct
{
    BswU1 u1StateCtrl;     /* CONTOROL state        */
    BswU1 u1StateMirror;   /* CONTOROL state mirror */
    BswU1 u1BusAwakeSelf;  /* Own-node bus Awake factor */
    BswU1 u1BusAwakeOther; /* Other-node bus Aweke factor available */
} Bsw_CanNmA_STCtrlTableType;

/* Type definition for CVT */
typedef struct
{
    BswU1 u1StateCvt;    /* CVT-NM status             */
    BswU1 u1StateMirror; /* CVT-NM Status Mirror      */
    BswU1 u1WkupData;    /* WKUP,INIT state         */
    BswU1 u1WkupDtMirror;/* WKUP,INIT state mirror  */
    BswU1 u1WkupFct;     /* Startup State Save         */
    BswU1 u1BusWkupKind; /* Bus wake-up type */
    BswU1 u1ChPower;     /* Channel power supply           */
    BswU1 u1ComMsgSt;    /* Control message transmission enable/disable */
} Bsw_CanNmA_STCvtTableType;

/* Type definition for OSEK */
typedef struct
{
    BswU1  u1RingStable;
    BswU1  u1BusError;
    BswU1  u1NMActive;
    BswU1  u1LimpHome;
    BswU1  u1BusSleep;
    BswU1  u1WaitBusSleep;
    BswU1  u1TxRingDataAllowed;
    BswU1  u1BusSleepInd;
} Bsw_CanNmA_STNwStatusFlags1Type;

typedef struct
{
    BswU1 u1PrepSleep;
    BswU1 u1RingReqStable;
    BswU1 u1LhSndMarker;
    BswU1 u1ResetDelay;
    BswU1 u1Wait1stRingSnd; /* Manage the initial ring  */
} Bsw_CanNmA_STNwStatusFlags2Type;

typedef struct
{
    BswConst       BswU1 *ptMsgData;   /*  Pointer to data for Alive, Ring, and LimpHome         */
    BswU1 u1TxLimit;                   /*  Upper limit of the transmission counter  */
    BswU1 u1RxLimit;                   /*  Receive counter upper limit  */
} Bsw_CanNmA_STNmOsekRomDataType;

typedef struct
{
    BswU1 u1StateLocal;                /*  OSEK-NM status         */
    BswU1 u1StateMirror;               /*  OSEK-NM state mirror   */
    BswU1 u1StateOsek;                 /*  OSEK-NM compliant state     */
    BswU1 u1RingMsgAckTxFlg;           /*  Ring message (ack=1) transmission request in progress flag */
    Bsw_CanNmA_STNwStatusFlags1Type stNetStatus1;    /*  Net status (OSEK-NM specification)   */
    Bsw_CanNmA_STNwStatusFlags2Type stNetStatus2;    /*  Net status (for internal processing)    */
    Bsw_CanNmA_STNwStatusFlags1Type stStatusPub;     /*  Net status for external publication      */
    BswU1 u1LogicalSuccessor;          /*  Logical successor                */
    BswU1 u1TxCount;                   /*  Transmission counter    */
    BswU1 u1RxCount;                   /*  Receive counter    */
} Bsw_CanNmA_STNmOsekRamDataType;

typedef struct
{
    BswConst       Bsw_CanNmA_STNmOsekRomDataType *ptRom;
    Bsw_CanNmA_STNmOsekRamDataType       *ptRam;
} Bsw_CanNmA_STNmOsekCntXTType;

/* Type definition for timers */
typedef struct
{
    BswU2  u2Tstart;       /* Start time                */
    BswU2  u2Ttopcnt;      /* Maximum value at overflow    */
    BswU2  u2Tlowcnt;      /* Minimum value at overflow    */
    BswU2  u2Tend;         /* Timeout period        */
    BswU1  u1TimerNo;      /* Timer number              */
    BswU1  u1TimerNoMirror;/* Timer number(Mirror)       */
    BswU1  u1Ton;          /* Timer start flag        */
    BswU1  u1TonMrr;       /* Timer start flag Mirror */
} Bsw_CanNmA_STTimerTableType;

typedef struct
{
    BswU1 u1SID;
    BswU1 u1DST;
    BswU1 u1OP;         /* Operation code                    */
                        /* bit7 Transmit/receive type (0:Receive,1:Transmit) */
                        /* bit6 NoUse                    */
                        /* bit5 Sleep.ack                */
                        /* bit4 Sleep.ind                */
                        /* bit3 Nouse                    */
                        /* bit2 LimpHome                 */
                        /* bit1 Ring                     */
                        /* bit0 Alive                    */
} Bsw_CanNmA_STCanNmMsgBufType;

typedef struct
{
    BswU1 u1OldMsgIdx;
    BswU1 u1NewMsgIdx;
    Bsw_CanNmA_STCanNmMsgBufType stMsgQue[BSW_CANNM_A_MSGQUE_LEN]; /* Received storage data part  */
} Bsw_CanNmA_STCanNmMsgQueType ;

typedef struct
{
    BswU1 u1Num;                        /* Msg Yes or No ON:Yes OFF:No */
    Bsw_CanNmA_STCanNmMsgBufType stMsgBuf;   /* Latest data part         */
} Bsw_CanNmA_STCanNmMsgSavType ;

/* Type definition for event storage buffer */
typedef struct
{
    BswU2  u2EventNo;      /* Event Number           */
    BswU2  u2EventNoMirror;/* Event Number Mirror    */
} Bsw_CanNmA_STEventTableType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/* CONTOROL */
extern  Bsw_CanNmA_STCtrlTableType bsw_cannm_a_ctrl_stStsTbl[];  /* CONTOROL control table */

/* CVT-NM */
extern  Bsw_CanNmA_STCvtTableType  bsw_cannm_a_cvtnm_stCtlTbl[];  /* CVT control table */

/* TRANSPORT */
extern  Bsw_CanNmA_STCanNmMsgSavType bsw_cannm_a_trans_stMsgSavBf[];  /* Msg Storage buffer */
extern  Bsw_CanNmA_STCanNmMsgQueType bsw_cannm_a_trans_stMsgQueue[];  /* Msg Storage table for storage */

/* Timer management */
extern  BswU2 bsw_cannm_a_timer_u2Time;
extern  BswU1 bsw_cannm_a_timer_u1RunAwake[];  /* AWAKE holding waiting timer - Run state */
/* CVT timeout control table     */
extern  Bsw_CanNmA_STTimerTableType bsw_cannm_a_timer_stTimerCvtT[][BSW_CANNM_A_TIMER_CNT_TBL_SIZE];
/* OSEK timeout control table    */
extern  Bsw_CanNmA_STTimerTableType bsw_cannm_a_timer_stTimerOsekT[][BSW_CANNM_A_TIMER_CNT_TBL_SIZE];

/* Event Management */
/* CVT event queue (number of channels * number of events) Retained */
extern  Bsw_CanNmA_STEventTableType bsw_cannm_a_event_stCvtQue[][BSW_CANNM_A_EVT_QMAX];
/* OSEK event queue (number of channels * number of events) Retained */
extern  Bsw_CanNmA_STEventTableType bsw_cannm_a_event_stOsekQue[][BSW_CANNM_A_EVT_QMAX];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* CanNmA Maximum number of channels */
extern BswConst BswU1 bsw_cannm_a_ctrl_u1MaxCh;

/* CanNmA Channel Offset */
extern BswConst       BswU1 bsw_cannm_a_tbl_u1ChOffset;

/* CanNmA Number of implemented channels */
extern BswConst       BswU1 bsw_cannm_a_ctrl_u1MaxChTbl;

/* CanNmA Configuration settings per channel */
extern BswConst       Bsw_CanNmA_STConfgTblChType  bsw_cannm_a_ctrl_stChTbl[];

/* CanNmA Channel Number Conversion Table */
extern BswConst       BswU1 bsw_cannm_a_ctrl_u1CnoChgIn[];  /* All CH No. -> CanNmA CH No  */
extern BswConst       BswU1 bsw_cannm_a_ctrl_u1CnoChgOut[]; /* CanNmA CH No -> Entire CH No */

/* OSEK context */
extern BswConst       Bsw_CanNmA_STNmOsekCntXTType bsw_cannm_a_oseknm_stContextTbl[];

/* Timer setting */
extern BswConst      BswU2 bsw_cannm_a_timer_u2TmCntTbl[][BSW_CANNM_A_TIMER_TBLMAX];


#endif  /* BSW_CANNM_A_NMCFGTBL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/07/07                                             */
/*  v1-1-0          :2020/04/10                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
