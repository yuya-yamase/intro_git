/* bsw_pdur_rt_h_v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/PDUR/RT/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_PDUR_RT_H
#define BSW_PDUR_RT_H

#include <Std_Types.h>
#include <ComStack_Types.h>

#include <com/bsw_com.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Number of components to be connected to PduR (excluding SecOC/IpduM) */
#define BSW_PDUR_MAX_LOCMPNUM      (12U)
#define BSW_PDUR_MAX_UPCMPNUM      (5U)

/* For PDU ID processing */
#define BSW_PDUR_SHIFT_IDBIT       (11U)

/* SecOC not used */
#define BSW_PDUR_INVALID_PDUID     (0xFFFFU)

/* Zero-cost operation */
#define BSW_PDUR_ZEROCOST_CAN      (0x00U)
#define BSW_PDUR_ZEROCOST_LIN      (0x01U)
#define BSW_PDUR_ZEROCOST_ETH      (0x02U)
#define BSW_PDUR_ZEROCOST_CDD1     (0x03U)
#define BSW_PDUR_ZEROCOST_CDD2     (0x04U)
#define BSW_PDUR_ZEROCOST_NOUSE    (0xFFU)

/* For SecOC PDU ID processing */
#define BSW_PDUR_SECOC_ID_MASK     (0x7FFFU)
#define BSW_PDUR_SECOC_KIND_MASK   (0x8000U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    PduIdType   u2PduId;                                /* PDU-ID           */
    BswU2       u2SecOCId;                              /* SecOC PDU-ID     */
} Bsw_PduR_RoutingType;                                 /* PduR Routing Table Type */

typedef Std_ReturnType (*Bsw_PduR_TransmitType)( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
typedef Std_ReturnType (*Bsw_PduR_CancelTransmitType)( PduIdType TxPduId );
typedef Std_ReturnType (*Bsw_PduR_CancelReceiveType)( PduIdType RxPduId );
typedef uint32 (*Bsw_PduR_ComGetTxIdType)( PduIdType PduId );
typedef uint32 (*Bsw_PduR_ComGetRxIdType)( PduIdType PduId );
typedef uint32 (*Bsw_PduR_ComGetCrrntRxIdType)( PduIdType PduId );

typedef struct
{
    Bsw_PduR_TransmitType            ptTransmit;         /* Transmit         */
    Bsw_PduR_CancelTransmitType      ptCancelTransmit;   /* CancelTransmit   */
    Bsw_PduR_CancelReceiveType       ptCancelReceive;    /* CancelReceive    */
    Bsw_PduR_ComGetTxIdType          ptComGetTxId;       /* ComGetTxId       */
    Bsw_PduR_ComGetRxIdType          ptComGetRxId;       /* ComGetRxId       */
    Bsw_PduR_ComGetCrrntRxIdType     ptComGetCrrntRxId;  /* GetCurrentRxId   */
}Bsw_PduR_LoCompInfoType;

typedef Std_ReturnType (*Bsw_PduR_TriggerTxType)( PduIdType TxPduId, PduInfoType* PduInfoPtr );
typedef void (*Bsw_PduR_TxConfirmationType)( PduIdType TxPduId, Std_ReturnType result );
typedef void (*Bsw_PduR_RxIndicationType)( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
typedef BufReq_ReturnType (*Bsw_PduR_StartOfReceptionType)( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
typedef BufReq_ReturnType (*Bsw_PduR_CopyRxDataType)( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
typedef BufReq_ReturnType (*Bsw_PduR_CopyTxDataType)( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
typedef void (*Bsw_PduR_TpRxIndicationType)( PduIdType id, Std_ReturnType result );
typedef void (*Bsw_PduR_TpTxConfirmationType)( PduIdType id, Std_ReturnType result );
typedef Bsw_Com_TxModeType (*Bsw_PduR_GetCurrentTxModeType)( PduIdType TxPduId );

typedef struct
{
    Bsw_PduR_TriggerTxType           ptTriggerTx;            /* TriggerTransmit  */
    Bsw_PduR_TxConfirmationType      ptTxConfirmation;       /* TxConfirmation   */
    Bsw_PduR_RxIndicationType        ptRxIndication;         /* RxIndication     */
    Bsw_PduR_StartOfReceptionType    ptStartOfReception;     /* StartOfReception */
    Bsw_PduR_CopyRxDataType          ptCopyRxData;           /* CopyRxData       */
    Bsw_PduR_CopyTxDataType          ptCopyTxData;           /* CopyTxData       */
    Bsw_PduR_TpRxIndicationType      ptTpRxIndication;       /* TpRxIndication   */
    Bsw_PduR_TpTxConfirmationType    ptTpTxConfirmation;     /* TpTxConfirmation */
    Bsw_PduR_GetCurrentTxModeType    ptGetCurrentTxMode;     /* GetCurrentTxMode */
}Bsw_PduR_UpCompInfoType;

typedef struct
{
    Bsw_PduR_TransmitType            ptTransmit;         /* Transmit         */
    Bsw_PduR_CancelTransmitType      ptCancelTransmit;   /* CancelTransmit   */
    Bsw_PduR_TriggerTxType           ptTriggerTx;        /* TriggerTransmit  */
    Bsw_PduR_TxConfirmationType      ptTxConfirmation;   /* TxConfirmation   */
    Bsw_PduR_RxIndicationType        ptRxIndication;     /* RxIndication     */
}Bsw_PduR_IpduMInfoType;

typedef struct
{
    Bsw_PduR_TransmitType            ptTransmit;         /* Transmit         */
    Bsw_PduR_CancelTransmitType      ptCancelTransmit;   /* CancelTransmit   */
    Bsw_PduR_TriggerTxType           ptTriggerTx;        /* TriggerTransmit  */
    Bsw_PduR_TxConfirmationType      ptTxConfirmation;   /* TxConfirmation   */
    Bsw_PduR_RxIndicationType        ptRxIndication;     /* RxIndication     */
}Bsw_PduR_SomeIpTpInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* Sub-functions for routing */
BswU4 bsw_pdur_rt_ComGetTxIdMultiP( PduIdType PduId );
BswU4 bsw_pdur_rt_ComGetRxIdMultiP( PduIdType PduId );

Std_ReturnType bsw_pdur_rt_ComTransmitMultiP( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType bsw_pdur_rt_ComCancelTxMultiP( PduIdType TxPduId );
Std_ReturnType bsw_pdur_rt_DcmTransmitMultiP( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType bsw_pdur_rt_DcmCancelTxMultiP( PduIdType TxPduId );
Std_ReturnType bsw_pdur_rt_DcmCancelRxMultiP( PduIdType RxPduId );
Std_ReturnType bsw_pdur_rt_LdComTransmitMultiP( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType bsw_pdur_rt_LdComCancelTxMultiP( PduIdType TxPduId );
Std_ReturnType bsw_pdur_rt_TriggerTxMultiP( PduIdType TxPduId, PduInfoType* PduInfoPtr );
void bsw_pdur_rt_TxConfirmMultiP( PduIdType TxPduId, Std_ReturnType result );
void bsw_pdur_rt_RxIndMultiP( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
BufReq_ReturnType bsw_pdur_rt_SORMultiP( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType bsw_pdur_rt_CopyRxDataMultiP( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
BufReq_ReturnType bsw_pdur_rt_CopyTxDataMultiP( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
void bsw_pdur_rt_TpRxIndMultiP( PduIdType id, Std_ReturnType result );
void bsw_pdur_rt_TpTxConfirmMultiP( PduIdType id, Std_ReturnType result );
Com_TxModeType bsw_pdur_rt_ComGetTxModeMultiP( PduIdType TxPduId );

/* Dummy function */
uint32 bsw_pdur_dummy_ComGetTxId( PduIdType PduId );
uint32 bsw_pdur_dummy_ComGetRxId( PduIdType PduId );
uint32 bsw_pdur_dummy_ComGetCrrntRxId( PduIdType PduId );

Std_ReturnType bsw_pdur_dummy_Transmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType bsw_pdur_dummy_CancelTransmit( PduIdType TxPduId );
Std_ReturnType bsw_pdur_dummy_CancelReceive( PduIdType RxPduId );
Std_ReturnType bsw_pdur_dummy_TriggerTransmit( PduIdType TxPduId, PduInfoType* PduInfoPtr );
void bsw_pdur_dummy_TxConfirmation( PduIdType TxPduId, Std_ReturnType result );
void bsw_pdur_dummy_TxConfExt( PduIdType TxPduId, Std_ReturnType result );
void bsw_pdur_dummy_RxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
BufReq_ReturnType bsw_pdur_dummy_StartOfRecept( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType bsw_pdur_dummy_CopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
BufReq_ReturnType bsw_pdur_dummy_CopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
void bsw_pdur_dummy_TpRxIndication( PduIdType id, Std_ReturnType result );
void bsw_pdur_dummy_TpTxConfirmation( PduIdType id, Std_ReturnType result);
Com_TxModeType bsw_pdur_dummy_ComGetTxMode( PduIdType TxPduId );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/* Config table */
extern  BswConst   PduIdType bsw_pdur_u2ComRoutingTbl[];
extern  BswConst   PduIdType bsw_pdur_u2DcmRoutingTbl[];
extern  BswConst   PduIdType bsw_pdur_u2LdComRoutingTbl[];
extern  BswConst   PduIdType bsw_pdur_u2Cdd1RoutingTbl[];
extern  BswConst   PduIdType bsw_pdur_u2Cdd2RoutingTbl[];

extern  BswConst   PduIdType* BswConst bsw_pdur_u2UpCompRoutingTbl[];
extern  BswConst   PduIdType bsw_pdur_u2DummyUpRoutingTbl[];

extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stCanIfRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stLinIfRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stSoAdIfRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stCdd1IfRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stCdd2IfRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stDoIPIfRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stCanTpRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stLinTpRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stSoAdTpRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stCdd1TpRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stCdd2TpRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stDoIPTpRoutingTbl[];

extern  BswConst   Bsw_PduR_RoutingType* BswConst bsw_pdur_stLoCompRoutingTbl[];
extern  BswConst   Bsw_PduR_RoutingType bsw_pdur_stDummyRoutingTbl[];

extern  BswConst   PduIdType bsw_pdur_u2ComIpduMTbl[];
extern  BswConst   PduIdType bsw_pdur_u2DcmIpduMTbl[];
extern  BswConst   PduIdType bsw_pdur_u2LdComIpduMTbl[];
extern  BswConst   PduIdType bsw_pdur_u2Cdd1IpduMTbl[];
extern  BswConst   PduIdType bsw_pdur_u2Cdd2IpduMTbl[];
extern  BswConst   PduIdType bsw_pdur_u2CanIfIpduMTbl[];
extern  BswConst   PduIdType bsw_pdur_u2LinIfIpduMTbl[];
extern  BswConst   PduIdType bsw_pdur_u2SoAdIfIpduMTbl[];
extern  BswConst   PduIdType bsw_pdur_u2DoIPIfIpduMTbl[];
extern  BswConst   PduIdType bsw_pdur_u2Cdd1IfIpduMTbl[];
extern  BswConst   PduIdType bsw_pdur_u2Cdd2IfIpduMTbl[];

extern  BswConst   PduIdType bsw_pdur_u2SoAdIfSomeIpTbl[];

extern  BswConst   PduIdType* BswConst bsw_pdur_ptIpduMUpRoutingTbl[];
extern  BswConst   PduIdType* BswConst bsw_pdur_ptIpduMLoRoutingTbl[];
extern  BswConst   PduIdType bsw_pdur_u2DummyIpduMTbl[];

extern  BswConst   PduIdType* BswConst bsw_pdur_ptSomeIpTpLoRoutingTbl[];
extern  BswConst   PduIdType bsw_pdur_u2DummySomeIpTpTbl[];

extern  BswConst   PduIdType bsw_pdur_u2ComSecOCTbl[];
extern  BswConst   PduIdType bsw_pdur_u2DcmSecOCTbl[];
extern  BswConst   PduIdType bsw_pdur_u2LdComSecOCTbl[];
extern  BswConst   PduIdType bsw_pdur_u2Cdd1SecOCTbl[];
extern  BswConst   PduIdType bsw_pdur_u2Cdd2SecOCTbl[];

extern  BswConst   PduIdType* BswConst bsw_pdur_u2SecOCUpRoutingTbl[];
extern  BswConst   PduIdType bsw_pdur_u2DummySecOCTbl[];

/* Function table by component */
extern  BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_ComFuncTbl;
extern  BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_DcmFuncTbl;
extern  BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_SecOCFuncTbl;
extern  BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_LdComFuncTbl;
extern  BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_Cdd1FuncTbl;
extern  BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_Cdd2FuncTbl;

extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_CanIfFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_LinIfFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_SoAdIfFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_SecOCIfFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_SecOCTpFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_Cdd1IfFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_Cdd2IfFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_CanTpFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_LinTpFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_SoAdTpFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_Cdd1TpFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_Cdd2TpFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_DoIPIfFuncTbl;
extern  BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_DoIPTpFuncTbl;

extern  BswConst   Bsw_PduR_IpduMInfoType bsw_pdur_rt_IpduMFuncTbl;
extern  BswConst   Bsw_PduR_SomeIpTpInfoType bsw_pdur_rt_SomeIpTpFuncTbl;

extern  BswConst   Bsw_PduR_LoCompInfoType* BswConst bsw_pdur_rt_CompTbl[];
extern  BswConst   Bsw_PduR_UpCompInfoType* BswConst bsw_pdur_UpperCompFuncTbl[];
extern  BswConst   Bsw_PduR_LoCompInfoType* BswConst bsw_pdur_rom_ptSecOCIfLoFunc;
extern  BswConst   Bsw_PduR_LoCompInfoType* BswConst bsw_pdur_rom_ptSecOCTpLoFunc;
extern  BswConst   Bsw_PduR_UpCompInfoType* BswConst bsw_pdur_rom_ptSecOCUpFunc;
extern  BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_DummyFuncTbl;

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* Number of messages by component */
extern  BswConst   BswU2 bsw_pdur_u2ComMsgNum;
extern  BswConst   BswU2 bsw_pdur_u2DcmMsgNum;
extern  BswConst   BswU2 bsw_pdur_u2LdComMsgNum;
extern  BswConst   BswU2 bsw_pdur_u2Cdd1MsgNum;
extern  BswConst   BswU2 bsw_pdur_u2Cdd2MsgNum;
extern  BswConst   BswU2 bsw_pdur_u2UpCompMsgNumTbl[];
extern  BswConst   BswU2 bsw_pdur_u2LoCompMsgNumTbl[];

/* Component use/unuse */
extern  BswConst   BswU1 bsw_pdur_u1IpduMFunc;
extern  BswConst   BswU1 bsw_pdur_u1SomeIpTpFunc;
extern  BswConst   BswU1 bsw_pdur_u1IPduMA;

/* Function Pointer for Zero Cost Operation Switching */
extern  Std_ReturnType (* BswConst bsw_pdur_rom_ptComTransmitFunc)( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
extern  Std_ReturnType (* BswConst bsw_pdur_rom_ptComCancelTxFunc)( PduIdType TxPduId );
extern  Std_ReturnType (* BswConst bsw_pdur_rom_ptDcmTransmitFunc)( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
extern  Std_ReturnType (* BswConst bsw_pdur_rom_ptDcmCancelTxFunc)( PduIdType TxPduId );
extern  Std_ReturnType (* BswConst bsw_pdur_rom_ptDcmCancelRxFunc)( PduIdType RxPduId );
extern  Std_ReturnType (* BswConst bsw_pdur_rom_ptLdComTransmitFn)( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
extern  Std_ReturnType (* BswConst bsw_pdur_rom_ptLdComCancelTxFn)( PduIdType TxPduId );
extern  Std_ReturnType (* BswConst bsw_pdur_rom_ptTriggerTxFunc)( PduIdType TxPduId, PduInfoType* PduInfoPtr );
extern  void (* BswConst bsw_pdur_rom_ptTxConfFunc)( PduIdType TxPduId, Std_ReturnType result );
extern  void (* BswConst bsw_pdur_rom_ptRxIndFunc)( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
extern  BufReq_ReturnType (* BswConst bsw_pdur_rom_ptSorFunc)( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
extern  BufReq_ReturnType (* BswConst bsw_pdur_rom_ptCopyRxDataFunc)( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
extern  BufReq_ReturnType (* BswConst bsw_pdur_rom_ptCopyTxDataFunc)( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
extern  void (* BswConst bsw_pdur_rom_ptTpRxIndFunc)( PduIdType id, Std_ReturnType result );
extern  void (* BswConst bsw_pdur_rom_ptTpTxConfFunc)( PduIdType id, Std_ReturnType result );
extern  BswConst Bsw_PduR_ComGetTxIdType  bsw_pdur_rom_ptComGetTxIdFunc;
extern  BswConst Bsw_PduR_ComGetRxIdType  bsw_pdur_rom_ptComGetRxIdFunc;
extern  Com_TxModeType (* BswConst bsw_pdur_rom_ptComGetTxMode)( PduIdType TxPduId );

/* Assign/unassign component identifiers for zero-cost operations */
extern  BswConst   PduIdType bsw_pdur_PduIdCompMask;
extern  BswConst   PduIdType bsw_pdur_PduIdIfCompSet;
extern  BswConst   PduIdType bsw_pdur_PduIdTpCompSet;

/* Component ID Conversion Table for SecOC */
extern  BswConst   PduIdType bsw_pdur_u2SecOCToUpCompIdTbl[];
extern  BswConst   PduIdType bsw_pdur_u2SecOCToLoCompIdTbl[];

#endif /* BSW_PDUR_RT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/06/26                                             */
/*  v1-0-1          :2018/04/04                                             */
/*  v1-1-0          :2019/01/15                                             */
/*  v1-2-0          :2019/11/05                                             */
/*  v2-0-0          :2022/02/11                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
