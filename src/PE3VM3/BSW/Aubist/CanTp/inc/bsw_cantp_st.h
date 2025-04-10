/* bsw_cantp_st_h_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTP/ST/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANTP_ST_H
#define BSW_CANTP_ST_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*--------------------------------------*/
/* Module State                         */
/*--------------------------------------*/
/*--------------------------*/
/* CANTP_UNINIT             */
/*--------------------------*/
/* nothing */

/*--------------------------------------*/
/* Connection Channel State             */
/*--------------------------------------*/
/* CANTP_IDLE */
#define BSW_CANTP_ST_u1STS_IDLE                ((Bsw_CanTp_st_ProcStatType)0xE1U)

/* CANTP_TX_PROCESSING */
#define BSW_CANTP_ST_u1STS_TX_WAIT             ((Bsw_CanTp_st_ProcStatType)0xD2U)
#define BSW_CANTP_ST_u1STS_SF_TX               ((Bsw_CanTp_st_ProcStatType)0xC3U)
#define BSW_CANTP_ST_u1STS_FF_TX               ((Bsw_CanTp_st_ProcStatType)0xB4U)
#define BSW_CANTP_ST_u1STS_FC_RX               ((Bsw_CanTp_st_ProcStatType)0xA5U)
#define BSW_CANTP_ST_u1STS_CF_WAIT_CS          ((Bsw_CanTp_st_ProcStatType)0x96U)
#define BSW_CANTP_ST_u1STS_CF_TX               ((Bsw_CanTp_st_ProcStatType)0x87U)
#define BSW_CANTP_ST_u1STS_CF_WIT_STMIN        ((Bsw_CanTp_st_ProcStatType)0x78U)

/* CANTP_RX_PROCESSING */
#define BSW_CANTP_ST_u1STS_FC_WAIT             ((Bsw_CanTp_st_ProcStatType)0x69U)
#define BSW_CANTP_ST_u1STS_FC_TX               ((Bsw_CanTp_st_ProcStatType)0x5AU)
#define BSW_CANTP_ST_u1STS_CF_RX               ((Bsw_CanTp_st_ProcStatType)0x4BU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8                      Bsw_CanTp_st_ProcStatType;      /* State Machine Processing Status             */
typedef uint8                      Bsw_CanTp_st_FSType;            /* Flow Status                                 */

typedef struct
{
    uint32                         u4SenderRemainNSduLen;          /* Sender: Remain Transmition Length           */
    uint16                         u2SenderNSduId;                 /* Sender: Processing NSdu-Id                  */
    uint16                         u2SenderCycle;                  /* Sender: MainFunction cycle count            */
    Bsw_CanTp_st_ProcStatType      u1SenderStat;                   /* Sender: Sender Processing Status            */
    uint8                          u1SenderSN;                     /* Sender: Sequence Number                     */
    uint8                          u1SenderCFNum;                  /* Sender: Number of CF on the block           */
    uint8                          u1SenderBS;                     /* Sender: BS on FC.CTS                        */
    uint8                          u1SenderSTminCycle;             /* Sender: STmin on FC.CTS                     */
    uint8                          u1Padding[BSW_CANTP_PAD_SIZE3]; /* Sender: Padding byte                        */
}Bsw_CanTp_st_SenderStatType;

typedef struct
{
    uint32                         u4ReceiverRemainNSduLen;        /* Receiver: Remain Recevice Length            */
    uint16                         u2ReceiverNSduId;               /* Receiver: Processing NSdu-Id                */
    uint16                         u2ReceiverCycle;                /* Receiver: MainFunction cycle count          */
    uint16                         u2ReceiverFCWaitCnt;            /* Receiver: Number of sent FC.WAIT            */
    Bsw_CanTp_st_ProcStatType      u1ReceiverStat;                 /* Receiver: Receiver Processing Status        */
    uint8                          u1ReceiverRXDL;                 /* Receiver: RXDL                              */
    uint8                          u1ReceiverSN;                   /* Receiver: Sequence Number                   */
    uint8                          u1ReceiverCFNum;                /* Receiver: Number of CF on the block         */
    Bsw_CanTp_st_FSType            u1ReceiverFS;                   /* Receiver: FlowStatus                        */
    uint8                          u1ReceiverAcceptedReqCnt;       /* Receiver: Number of accepted request frames */
}Bsw_CanTp_st_ReceiverStatType;

typedef struct
{
    Bsw_CanTp_st_SenderStatType    stSenderStatTbl;                /* Sender Status Information                   */
    Bsw_CanTp_st_ReceiverStatType  stReceiverStatTbl;              /* Receiver Status Information                 */
}Bsw_CanTp_st_ChStatType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void    bsw_cantp_st_MainFunction_Mode( void );
void    bsw_cantp_st_InitCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl );
void    bsw_cantp_st_ShutdownCore( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern  Bsw_CanTp_st_ChStatType     bsw_cantp_st_stChStatTbl[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* BSW_CANTP_ST_H */


/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/09/25                                             */
/*  v1-1-0          :2018/12/26                                             */
/*  v2-0-0          :2021/09/13                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
