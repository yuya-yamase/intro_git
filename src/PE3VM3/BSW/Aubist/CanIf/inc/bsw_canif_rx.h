/* bsw_canif_rx_h_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANIF/RX/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_CANIF_RX_H
#define     BSW_CANIF_RX_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* MetaData Size */
#define BSW_CANIF_RX_METADATA_SIZE          (4U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    BswU4                               u4CanId;        /* CAN ID               */
    BswU1                               u1SduLen;       /* DLC                  */
    BswU1                               u1Ch;           /* Channel             */
    BswU2                               u2Extend;       /* For future extension           */
} Bsw_CanIf_RxPduTblType;

typedef void (*Bsw_CanIf_UpperRxIndType)( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );

typedef struct
{
    BswConst Bsw_CanIf_RxPduTblType    *ptPduTbl;       /* PDU information table      */
    Bsw_CanIf_UpperRxIndType            ptRxInd;        /* Notify receiving completion         */
    BswConst BswU4                     *ptMaskTbl;      /* CAN ID mask table */
    BswConst BswU4                     *ptRxMsgMaskTbl; /* CAN ID mask for Rx Msg table */
    BswConst BswU2                     *ptPduNumTbl;    /* Pdu number table        */
    BswU2                               u2PduNum;       /* Number of PduId              */
} Bsw_CanIf_RcvCompInfoType;

typedef void (*Bsw_CanIf_RxIndType)( BswU1 u1Ch, BswConstR Bsw_CanIf_PduType* ptMsg, BswU1 u1CompNum );

typedef struct
{
    BswConst BswU1                     *ptHrhToCh;      /* HRH-Channel Conversion Table       */
    BswConst BswU1                     *ptHrhToComp;    /* HRH-Higher Level Module Conversion Table */
    BswU2                               u2HrhNum;       /* Number of HRH                          */
    BswU2                               u2Extend;       /* For future extension                     */
} Bsw_CanIf_RxHrhInfo;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void  bsw_canif_rx_InitRcvSts( void );                          /* Initialize receiving                   */
void  bsw_canif_rx_ClrRcvSts( BswU1 u1Ch );                     /* Clear the receive status                   */
void  bsw_canif_rx_PutRcvQue( BswU1 u1Ch, BswConstR Bsw_CanIf_RxPduType* ptQueMsg );
                                                                /* Store in the receive queue                   */

/* Unit internal public definition */
void    bsw_canif_rx_RcvPduRStd( BswU1 u1Ch, BswConstR Bsw_CanIf_PduType* ptMsg, BswU1 u1CompNum );
void    bsw_canif_rx_RcvPduRExtA( BswU1 u1Ch, BswConstR Bsw_CanIf_PduType* ptMsg, BswU1 u1CompNum );
void    bsw_canif_rx_RcvPduRExtA1( BswU1 u1Ch, BswConstR Bsw_CanIf_PduType* ptMsg, BswU1 u1CompNum );
void    bsw_canif_rx_RcvPduRExtA2( BswU1 u1Ch, BswConstR Bsw_CanIf_PduType* ptMsg, BswU1 u1CompNum );
void    bsw_canif_rx_RcvPduRExtB( BswU1 u1Ch, BswConstR Bsw_CanIf_PduType* ptMsg, BswU1 u1CompNum );
void    bsw_canif_rx_RcvPduRExtE( BswU1 u1Ch, BswConstR Bsw_CanIf_PduType* ptMsg, BswU1 u1CompNum );
void    bsw_canif_rx_RcvCanTp( BswU1 u1Ch, BswConstR Bsw_CanIf_PduType* ptMsg, BswU1 u1CompNum );
void    bsw_canif_rx_RcvComp( BswU1 u1Ch, BswConstR Bsw_CanIf_PduType* ptMsg, BswU1 u1CompNum );

void    bsw_canif_rx_RxIndicationNone( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
void    bsw_canif_rx_RcvPduRNone( BswU1 u1Ch, BswConstR Bsw_CanIf_PduType* ptMsg, BswU1 u1CompNum );

Std_ReturnType  bsw_canif_rx_NmBPreRxMsgNone( BswU1 u1NetID, BswConstR Bsw_CanIf_PduType* ptMsg );
void            bsw_canif_rx_NmBPostRxMsgNone( BswU1 u1NetID, BswConstR Bsw_CanIf_PduType* ptMsg );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern Bsw_CanIf_QueIdxType               bsw_canif_rx_stRcvQueIdx [];

/* Unit internal public definition */
extern BswU4                              bsw_canif_rx_u4CurrentCanId[];
extern Bsw_CanIf_NotifStatusType          bsw_canif_rx_u1RxHistory[];
extern BswU4 * BswConst                   bsw_canif_rx_ptRcvQue[];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU2                       bsw_canif_rx_u2RcvQueSize[];
extern BswConst Bsw_CanIf_RcvCompInfoType * BswConst   bsw_canif_rx_ptRcvCompTbl[];
extern BswConst Bsw_CanIf_RcvCompInfoType   bsw_canif_rx_stRcvPduRTbl;
extern BswConst Bsw_CanIf_RcvCompInfoType   bsw_canif_rx_stRcvCanTpTbl;
extern BswConst Bsw_CanIf_RxPduTblType      bsw_canif_stRxPduRPduTbl[];
extern BswConst Bsw_CanIf_RxPduTblType      bsw_canif_stRxCanNmPduTbl[];
extern BswConst Bsw_CanIf_RxPduTblType      bsw_canif_stRxCanTpPduTbl[];
extern BswConst Bsw_CanIf_RxPduTblType      bsw_canif_stRxCdd1PduTbl[];
extern BswConst Bsw_CanIf_RxPduTblType      bsw_canif_stRxCdd2PduTbl[];
extern BswConst Bsw_CanIf_RxPduTblType      bsw_canif_stRxXcpPduTbl[];
extern BswConst BswU4                       bsw_canif_stRxPduRMskTbl[];
extern BswConst BswU4                       bsw_canif_stRxCanNmMskTbl[];
extern BswConst BswU4                       bsw_canif_stRxCanTpMskTbl[];
extern BswConst BswU4                       bsw_canif_stRxCdd1MskTbl[];
extern BswConst BswU4                       bsw_canif_stRxCdd2MskTbl[];
extern BswConst BswU4                       bsw_canif_stRxXcpMskTbl[];

extern BswConst Bsw_CanIf_RxIndType         bsw_canif_rx_ptRxIndCompFunc[][ BSW_CANIF_TBL_MAX_UPCMPNUM ];

/* Unit internal public definition */
extern BswConst Bsw_CanIf_RxHrhInfo        bsw_canif_rx_stHrhSwitchTbl[];
extern BswConst BswU4                      bsw_canif_rx_u4BdyFmtCanIdLo;
extern BswConst BswU4                      bsw_canif_rx_u4BdyFmtCanIdUp;
extern BswConst BswU2                      bsw_canif_rx_u2PDURPduNumTbl[];
extern BswConst BswU2                      bsw_canif_rx_u2CANTPPduNumTbl[];
extern BswConst BswU1                      bsw_canif_rx_u1CanIdMaskType;
extern BswConst BswU1                      bsw_canif_rx_u1MetaDataFunc;


#endif  /* BSW_CANIF_RX_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2018/10/02                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v3-0-0          :2024/10/16                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
