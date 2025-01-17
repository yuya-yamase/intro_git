/* bsw_canif_tx_h_v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANIF/TX/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_CANIF_TX_H
#define     BSW_CANIF_TX_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Unit internal public definition */
/****************************************************/
/* State value                                           */
/*--------------------------------------------------*/
/* -Identify the state with two or more bits                       */
/* -All 0 is not used                              */
/* -All 1 is not used                              */
/****************************************************/
/* Transmit queue status */
#define BSW_CANIF_TX_QUESTS_NONE               (0x69U)     /* No request             */
#define BSW_CANIF_TX_QUESTS_REQ                (0x5AU)     /* Request in progress               */
#define BSW_CANIF_TX_QUESTS_ABT                (0x3CU)     /* Requesting interruption           */
#define BSW_CANIF_TX_QUESTS_FAIL               (0xC3U)     /* Fails occur         */
#define BSW_CANIF_TX_QUESTS_WAITCLR            (0xA5U)     /* Wait to be cleared           */

/* HTH status */
#define BSW_CANIF_TX_HTHSTS_NONE               (0x69U)     /* No request             */
#define BSW_CANIF_TX_HTHSTS_REQ                (0x5AU)     /* Request accepted in progress           */
#define BSW_CANIF_TX_HTHSTS_WAIT               (0x3CU)     /* Request rejected in progress           */

#define BSW_CANIF_TX_NONSNDQUE                 (0x0020U)
#define BSW_CANIF_TX_NONSNDQUEMASK             (0x0020U)
#define BSW_CANIF_TX_HTH_SHIFT_7BIT            (7U)

/* Enable/Disable transmission failure notification */
#define BSW_CANIF_TX_ERRNOTIFSTS_NONE          (0x69U)     /* No transmission failure notification     */
#define BSW_CANIF_TX_ERRNOTIFSTS_EXIST         (0x5AU)     /* Transmission failure notification exists     */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    BswU2  u2Size;                      /* Number of steps in the transmit queue                   */
    BswU1  u1IntvTim;                   /* Transmission interval Tick time         */
    BswU1  u1Call;                      /* Notification timing from Can          */
    BswU1  u1HthIdx;                    /* HTH index value                  */
    BswU1  u1Extend;                    /* For future extension                       */
    BswU2  u2Hth;                       /* HOH for transmission                        */
    BswU2  u2QueHdl;                    /* Transmit queue handle               */
} Bsw_CanIf_SndQueInfType;              /* Transmit queue information type                 */

/* Unit internal public definition */
typedef struct
{
    BswU4  u4CanId;                     /* CAN ID                           */
    BswU1  u1Ch;                        /* Channel                         */
    BswU1  u1Extend;                    /* For future extension                       */
    BswU2  u2SndQue;                    /* Transmit queue number                   */
} Bsw_CanIf_TxPduTblType;

typedef void (*Bsw_CanIf_UpperTxCfmType)( PduIdType TxPduId, Std_ReturnType result );


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void  bsw_canif_tx_DeliverSndPdu( BswU1 u1Ch, BswConstR Bsw_CanIf_PduType* ptMsg, Std_ReturnType u1Result );
                                                          /* Notify the completion of transmission to the upper component */

void  bsw_canif_tx_InitSndSts( void );                    /* Transmission initialization                   */
void  bsw_canif_tx_ClrSndSts ( BswU1 u1Ch );              /* Clear the transmission status                   */
void  bsw_canif_tx_StrtSndSts( BswU1 u1Ch );              /* Set transmission at the communication start               */
void  bsw_canif_tx_StpSndSts ( BswU1 u1Ch );              /* Set transmission when communication is stopped               */

void  bsw_canif_tx_InitSndStsNone( void );                /* Transmission initialization (Dummy function)         */
void  bsw_canif_tx_ClrSndStsNone ( BswU1 u1Ch );          /* Clear the transmission status (Dummy function)         */
void  bsw_canif_tx_StrtSndStsNone( BswU1 u1Ch );          /* Set transmission at the communication start (Dummy function)     */
void  bsw_canif_tx_StpSndStsNone ( BswU1 u1Ch );          /* Set transmission when communication is stopped(Dummy function)     */

/* Unit internal public definition */

Std_ReturnType  bsw_canif_tx_SndPduRStd( BswU1 u1Ch, Bsw_CanIf_PduType *ptMsg );
Std_ReturnType  bsw_canif_tx_SndPduRExtA( BswU1 u1Ch, Bsw_CanIf_PduType *ptMsg );
Std_ReturnType  bsw_canif_tx_SndPduRExtA1( BswU1 u1Ch, Bsw_CanIf_PduType *ptMsg );
Std_ReturnType  bsw_canif_tx_SndPduRExtA2( BswU1 u1Ch, Bsw_CanIf_PduType *ptMsg );
Std_ReturnType  bsw_canif_tx_SndPduRExtB( BswU1 u1Ch, Bsw_CanIf_PduType *ptMsg );
Std_ReturnType  bsw_canif_tx_SndPduRExtE( BswU1 u1Ch, Bsw_CanIf_PduType *ptMsg );

void            bsw_canif_tx_TxConfirmationNone( PduIdType TxPduId, Std_ReturnType result );
Std_ReturnType  bsw_canif_tx_SndPduRNone( BswU1 u1Ch, Bsw_CanIf_PduType *ptMsg );

void            bsw_canif_tx_NmBPreTxMsgNone( BswU1 u1NetID, Bsw_CanIf_PduType* ptMsg );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern BswU1                           bsw_canif_tx_u1SndQueSts [];
extern Bsw_CanIf_QueIdxType            bsw_canif_tx_stSndQueIdx [];
extern BswU4 * BswConst                bsw_canif_tx_ptSndQue[];

/* Unit internal public definition */
extern BswU1                           bsw_canif_tx_u1IntvCnt   [];
extern Bsw_CanIf_NotifStatusType       bsw_canif_tx_u1TxHistory[];
extern PduInfoType                     bsw_canif_tx_stConfirmedPdu[];
extern BswU1                           bsw_canif_tx_u1TxErrNotifSts[];
extern BswU1                           bsw_canif_tx_u1MsgSndBuf[][ BSW_CANIF_MSGSIZE_MAX_CANFD ];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU2                     bsw_canif_tx_u2TxPduNum[];
extern BswConst BswU1                     bsw_canif_tx_u1SndQueNum [];
extern BswConst Bsw_CanIf_SndQueInfType * BswConst    bsw_canif_tx_ptSndQueInf [];
extern BswConst BswU1                     bsw_canif_tx_u1HthNum    [];
extern BswU1 * BswConst                   bsw_canif_tx_ptHthSts    [];

extern void (* BswConst bsw_canif_tx_ptInitSndStsFunc)( void );
extern void (* BswConst bsw_canif_tx_ptClrSndStsFunc)( BswU1 u1Ch );
extern void (* BswConst bsw_canif_tx_ptStrtSndStsFunc)( BswU1 u1Ch );
extern void (* BswConst bsw_canif_tx_ptStpSndStsFunc)( BswU1 u1Ch );

/* Unit internal public definition */
extern BswConst BswU1                      bsw_canif_tx_u1ReqToQue  [][ BSW_CANIF_TBL_MAX_UPCMPNUM ];
extern BswConst BswU4                      bsw_canif_tx_u4PaddingValue;
extern BswConst Bsw_CanIf_UpperTxCfmType   bsw_canif_tx_stSndCompTbl[];
extern BswConst Bsw_CanIf_TxPduTblType * BswConst    bsw_canif_tx_ptTxCompPduTbl[];
extern BswConst Bsw_CanIf_TxPduTblType     bsw_canif_stTxPduRPduTbl[];
extern BswConst Bsw_CanIf_TxPduTblType     bsw_canif_stTxCanNmPduTbl[];
extern BswConst Bsw_CanIf_TxPduTblType     bsw_canif_stTxCanTpPduTbl[];
extern BswConst Bsw_CanIf_TxPduTblType     bsw_canif_stTxCdd1PduTbl[];
extern BswConst Bsw_CanIf_TxPduTblType     bsw_canif_stTxCdd2PduTbl[];
extern BswConst Bsw_CanIf_TxPduTblType     bsw_canif_stTxXcpPduTbl[];
extern BswConst BswU1                      bsw_canif_tx_u1AvcLanPriTbl[];
extern BswConst BswU1                      bsw_canif_tx_u1FuncSnd;

extern Std_ReturnType (* BswConst bsw_canif_tx_ptSndPduRFunc[])( BswU1 u1Ch, Bsw_CanIf_PduType *ptMsg );
extern void (* BswConst bsw_canif_tx_ptNmBPreTxFunc)( BswU1 u1NetID, Bsw_CanIf_PduType* ptMsg );

extern  BswConst BswU1 bsw_canif_tx_u1FuncTxErrNotify;

#endif  /* BSW_CANIF_TX_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/27                                             */
/*  v1-1-0          :2018/10/02                                             */
/*  v2-0-0          :2022/01/25                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
