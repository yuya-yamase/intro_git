/* bsw_com_fs_h_v3-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COM/FS/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_COM_FS_H
#define BSW_COM_FS_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_COM_ALIVECOUNTER_MASK      (0x10U)

/* Mask value definition */
#define BSW_COM_u1MSG_MASK_NONE        ((BswU1)0x00U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    BswU2                   u2BytePos;
    BswU1                   u1BitMask_Hi;
    BswU1                   u1BitMask_Lo;
} Bsw_Com_AlvCntPosType;

typedef struct {
    BswU2                   u2BytePos;
    BswU1                   u1BitPos;
    BswU1                   u1Size;
} Bsw_Com_AliveInfoType;

typedef struct {
    BswU2                   u2BytePos;
    BswU1                   u1BitPos;
    BswU1                   u1Size;
    BswU1                   u1Endian;
    BswU1                   u1Extend;
} Bsw_Com_AlvCnt3TxInfoType;

typedef struct {
    BswU2                   u2BytePos;
    BswU1                   u1BitPos;
    BswU1                   u1Size;
    BswU1                   u1Endian;
    BswU1                   u1AllowVal;
    BswU1                   u1CntHold;
    BswU1                   u1Extend;
} Bsw_Com_AlvCnt3RxInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* Unit internal public definition */
void            bsw_com_fs_AliveCounterTxNone( PduIdType u2PduId, BswConstR PduInfoType *ptCanTrsMsg );
void            bsw_com_fs_AliveCounterTx0( PduIdType u2PduId, BswConstR PduInfoType *ptCanTrsMsg );
void            bsw_com_fs_AliveCounterTx1( PduIdType u2PduId, BswConstR PduInfoType *ptCanTrsMsg );
void            bsw_com_fs_AliveCounterTx2( PduIdType u2PduId, BswConstR PduInfoType *ptCanTrsMsg );
void            bsw_com_fs_AliveCounterTx3( PduIdType u2PduId, BswConstR PduInfoType *ptCanTrsMsg );

Std_ReturnType  bsw_com_fs_AliveCounterRxNone( PduIdType u2PduId, BswConstR PduInfoType *ptCanRcvMsg, BswU1 *ptPreviousCounter, BswU1 *ptReceivedCounter );
Std_ReturnType  bsw_com_fs_AliveCounterRx0( PduIdType u2PduId, BswConstR PduInfoType *ptCanRcvMsg, BswU1 *ptPreviousCounter, BswU1 *ptReceivedCounter );
Std_ReturnType  bsw_com_fs_AliveCounterRx1( PduIdType u2PduId, BswConstR PduInfoType *ptCanRcvMsg, BswU1 *ptPreviousCounter, BswU1 *ptReceivedCounter );
Std_ReturnType  bsw_com_fs_AliveCounterRx2( PduIdType u2PduId, BswConstR PduInfoType *ptCanRcvMsg, BswU1 *ptPreviousCounter, BswU1 *ptReceivedCounter );
Std_ReturnType  bsw_com_fs_AliveCounterRx3( PduIdType u2PduId, BswConstR PduInfoType *ptCanRcvMsg, BswU1 *ptPreviousCounter, BswU1 *ptReceivedCounter );

void            bsw_com_fs_AlvCntPosTxNone( PduIdType u2PduId, Bsw_Com_AlvCntPosType *ptAlvCntPos );
void            bsw_com_fs_AliveCounterPosTx0( PduIdType u2PduId, Bsw_Com_AlvCntPosType *ptAlvCntPos );
void            bsw_com_fs_AliveCounterPosTx1( PduIdType u2PduId, Bsw_Com_AlvCntPosType *ptAlvCntPos );
void            bsw_com_fs_AliveCounterPosTx2( PduIdType u2PduId, Bsw_Com_AlvCntPosType *ptAlvCntPos );
void            bsw_com_fs_AliveCounterPosTx3( PduIdType u2PduId, Bsw_Com_AlvCntPosType *ptAlvCntPos );

void            bsw_com_fs_Init( void );
void            bsw_com_fs_SetFailFlg( void );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern  BswU1                     bsw_com_fs_u1FailChk;                     /* Failure detection flag               */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* Unit internal public definition */
extern  BswConst Bsw_Com_AliveInfoType      bsw_com_AlvCnt2TxInfo[];           /* Alive counter storage position table (Transmission)     */
extern  BswConst Bsw_Com_AliveInfoType      bsw_com_AlvCnt2RxInfo[];           /* Alive counter storage position table ( Receiving )     */
extern  BswConst Bsw_Com_AlvCnt3TxInfoType  bsw_com_AlvCnt3TxInfo[];           /* Alive counter pattern 3 information table (transmit)  */
extern  BswConst Bsw_Com_AlvCnt3RxInfoType  bsw_com_AlvCnt3RxInfo[];           /* Alive counter pattern 3 information table (receive)  */


#endif /* BSW_COM_FS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/03/14                                             */
/*  v1-1-0          :2019/10/02                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
