/* bsw_bswm_cs_connector_h_v2-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/CONNECTOR/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_BSWM_CS_CONNECTOR_H
#define     BSW_BSWM_CS_CONNECTOR_H

#include <ComStack_Types.h>
#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include <nm/bsw_nmstack_types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Dcm Function Table */
typedef struct
{
    void (*NoComModeEntered)( uint8 NetworkId );
    void (*SilentComModeEntered)( uint8 NetworkId );
    void (*FullComModeEntered)( uint8 NetworkId );
} Bsw_BswmCS_DcmComMFuncTblType;

typedef struct
{
    BufReq_ReturnType (*StartOfReception)( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
    BufReq_ReturnType (*CopyRxData)( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
    BufReq_ReturnType (*CopyTxData)( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
    void (*TpRxIndication)( PduIdType id, Std_ReturnType result );
    void (*TpTxConfirmation)( PduIdType id, Std_ReturnType result );
    void (*TxConfirmation)( PduIdType TxPduId, Std_ReturnType result );
} Bsw_BswmCS_DcmPduRFuncTblType;

/* BswM Function Table */
typedef struct
{
    void (*ComM_CurrentMode)( NetworkHandleType Network, ComM_ModeType RequestedMode );
    void (*ComM_CurrentPncMode)( PNCHandleType PNC, ComM_PncModeType RequestedMode );
    void (*ComM_CurrentChPncMode)( NetworkHandleType Network, PNCHandleType PNC, ComM_PncModeType RequestedMode );
} Bsw_BswmCS_BswMFuncTblType;

/* Dem Function Table */
typedef struct
{
    void (*ErrorReport)( uint16 EventId, uint8 EventStatus );
} Bsw_BswmCS_DemFuncTblType;

/* EcuM Function Table */
typedef struct
{
    void (*SetWakeupEvent)( uint32 sources );
} Bsw_BswmCS_EcuMFuncTblType;

/* BswM CDD Function Table */
typedef struct
{
    void  (*Init)( void );
    void  (*DeInit)( void );
    void  (*PrepareDeInit)( void );
    void  (*Wakeup)( void );
    void  (*Sleep)( void );
    void  (*Reset)( void );
    void  (*MainFunctionHighIn)( void );
    void  (*MainFunctionHighOut)( void );
    void  (*MainFunctionMidIn)( void );
    void  (*MainFunctionMidCtrl)( void );
    void  (*MainFunctionMidOut)( void );
    void  (*InitDriver)( void );
    void  (*UpdateIPDUStatus)( void );
    BswU1 (*CheckAwake)( void );
} Bsw_BswmCS_BswMCddFuncTblType;

/* CDD SM Function Table */
typedef struct
{
    Std_ReturnType (*RequestComMode)( NetworkHandleType network, ComM_ModeType ComM_Mode );
    Std_ReturnType (*GetCurrentComMode)( NetworkHandleType network, ComM_ModeType* ComM_Mode );
} Bsw_BswmCS_CddSMFuncTblType;

/* CDD If Function Table */
typedef struct
{
    Std_ReturnType (*Transmit)( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
    Std_ReturnType (*CancelTransmit)( PduIdType TxPduId );
    uint32 (*GetTxId)( PduIdType PduId );
    uint32 (*GetRxId)( PduIdType PduId );
}Bsw_BswmCS_CddIfFuncTblType;

/* CDD Tp Function Table */
typedef struct
{
    Std_ReturnType (*Transmit)( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
    Std_ReturnType (*CancelTransmit)( PduIdType TxPduId );
    Std_ReturnType (*CancelReceive)( PduIdType PduId );
    uint32 (*GetTxId)( PduIdType PduId );
    uint32 (*GetRxId)( PduIdType PduId );
}Bsw_BswmCS_CddTpFuncTblType;

/* CDD Upper Function Table */
typedef struct
{
    Std_ReturnType (*TriggerTx)( PduIdType TxPduId, PduInfoType* PduInfoPtr );
    void (*TxConfirmation)( PduIdType TxPduId, Std_ReturnType result );
    void (*RxIndication)( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
    BufReq_ReturnType (*StartOfReception)( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
    BufReq_ReturnType (*CopyRxData)( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
    BufReq_ReturnType (*CopyTxData)( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
    void (*TpRxIndication)( PduIdType id, Std_ReturnType result );
    void (*TpTxConfirmation)( PduIdType id, Std_ReturnType result );
}Bsw_BswmCS_CddUpFuncTblType;

/* CDD Nm Function Table */
typedef struct
{
    Std_ReturnType  (*PassiveStartUp)( NetworkHandleType NetworkHandle );
    Std_ReturnType  (*NetworkRequest)( NetworkHandleType NetworkHandle );
    Std_ReturnType  (*NetworkRelease)( NetworkHandleType NetworkHandle );
    Std_ReturnType  (*DisableComm)( NetworkHandleType NetworkHandle );
    Std_ReturnType  (*EnableComm)( NetworkHandleType NetworkHandle );
    Std_ReturnType  (*GetState)( NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr );
} Bsw_BswmCS_CddNmFuncTblType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* Dem */
void bsw_bswm_cs_DemErrorReport( uint16 EventId, uint8 EventStatus );

/* BswM */
void bsw_bswm_cs_BswMComMCurrentMode( NetworkHandleType Network, ComM_ModeType RequestedMode );
void bsw_bswm_cs_BswMComMCurrentPncMode( PNCHandleType PNC, ComM_PncModeType RequestedMode );
void bsw_bswm_cs_BswMComMCrntChPncMode( NetworkHandleType Network, PNCHandleType PNC, ComM_PncModeType RequestedMode );


/* Dcm */
void bsw_bswm_cs_DcmNoComModeEntered( uint8 NetworkId );
void bsw_bswm_cs_DcmSilentComModeEntered( uint8 NetworkId );
void bsw_bswm_cs_DcmFullComModeEntered( uint8 NetworkId );
BufReq_ReturnType  bsw_bswm_cs_DcmStartOfReception( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType  bsw_bswm_cs_DcmCopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
BufReq_ReturnType  bsw_bswm_cs_DcmCopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
void bsw_bswm_cs_DcmTpRxIndication( PduIdType id, Std_ReturnType result );
void bsw_bswm_cs_DcmTpTxConfirmation( PduIdType id, Std_ReturnType result );
void bsw_bswm_cs_DcmTxConfirmation( PduIdType TxPduId, Std_ReturnType result );

/* EcuM */
void bsw_bswm_cs_EcuMSetWakeupEvent( uint32 sources );


/* BswM_CDD1 */
void  bsw_bswm_cs_BswMCdd1Init( void );
void  bsw_bswm_cs_BswMCdd1DeInit( void );
void  bsw_bswm_cs_BswMCdd1PrepareDeInit( void );
void  bsw_bswm_cs_BswMCdd1Wakeup( void );
void  bsw_bswm_cs_BswMCdd1Sleep( void );
void  bsw_bswm_cs_BswMCdd1Reset( void );
void  bsw_bswm_cs_BswMCdd1MFuncHighIn( void );
void  bsw_bswm_cs_BswMCdd1MFuncHighOut( void );
void  bsw_bswm_cs_BswMCdd1MFuncMidIn( void );
void  bsw_bswm_cs_BswMCdd1MFuncMidCtrl( void );
void  bsw_bswm_cs_BswMCdd1MFuncMidOut( void );
void  bsw_bswm_cs_BswMCdd1InitDriver( void );
void  bsw_bswm_cs_BswMCdd1UpdateIPDUStat( void );
BswU1 bsw_bswm_cs_BswMCdd1CheckAwake( void );


/* BswM_CDD2 */
void  bsw_bswm_cs_BswMCdd2Init( void );
void  bsw_bswm_cs_BswMCdd2DeInit( void );
void  bsw_bswm_cs_BswMCdd2PrepareDeInit( void );
void  bsw_bswm_cs_BswMCdd2Wakeup( void );
void  bsw_bswm_cs_BswMCdd2Sleep( void );
void  bsw_bswm_cs_BswMCdd2Reset( void );
void  bsw_bswm_cs_BswMCdd2MFuncHighIn( void );
void  bsw_bswm_cs_BswMCdd2MFuncHighOut( void );
void  bsw_bswm_cs_BswMCdd2MFuncMidIn( void );
void  bsw_bswm_cs_BswMCdd2MFuncMidCtrl( void );
void  bsw_bswm_cs_BswMCdd2MFuncMidOut( void );
void  bsw_bswm_cs_BswMCdd2InitDriver( void );
void  bsw_bswm_cs_BswMCdd2UpdateIPDUStat( void );
BswU1 bsw_bswm_cs_BswMCdd2CheckAwake( void );


/* CDD1SM */
Std_ReturnType bsw_bswm_cs_Cdd1SMRequestComMode( NetworkHandleType network, ComM_ModeType ComM_Mode );
Std_ReturnType bsw_bswm_cs_Cdd1SMGetCurrentComMode( NetworkHandleType network, ComM_ModeType* ComM_ModePtr );
/* CDD2SM */
Std_ReturnType bsw_bswm_cs_Cdd2SMRequestComMode( NetworkHandleType network, ComM_ModeType ComM_Mode );
Std_ReturnType bsw_bswm_cs_Cdd2SMGetCurrentComMode( NetworkHandleType network, ComM_ModeType* ComM_ModePtr );


/* CDD1If */
Std_ReturnType bsw_bswm_cs_Cdd1IfTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType bsw_bswm_cs_Cdd1IfCancelTransmit( PduIdType TxPduId );
uint32         bsw_bswm_cs_Cdd1IfGetTxId( PduIdType PduId );
uint32         bsw_bswm_cs_Cdd1IfGetRxId( PduIdType PduId );
/* CDD2If */
Std_ReturnType bsw_bswm_cs_Cdd2IfTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType bsw_bswm_cs_Cdd2IfCancelTransmit( PduIdType TxPduId );
uint32         bsw_bswm_cs_Cdd2IfGetTxId( PduIdType PduId );
uint32         bsw_bswm_cs_Cdd2IfGetRxId( PduIdType PduId );


/* CDD1Tp */
Std_ReturnType bsw_bswm_cs_Cdd1TpTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType bsw_bswm_cs_Cdd1TpCancelTransmit( PduIdType TxPduId );
Std_ReturnType bsw_bswm_cs_Cdd1TpCancelReceive( PduIdType RxPduId );
uint32         bsw_bswm_cs_Cdd1TpGetTxId( PduIdType PduId );
uint32         bsw_bswm_cs_Cdd1TpGetRxId( PduIdType PduId );
/* CDD2Tp */
Std_ReturnType bsw_bswm_cs_Cdd2TpTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType bsw_bswm_cs_Cdd2TpCancelTransmit( PduIdType TxPduId );
Std_ReturnType bsw_bswm_cs_Cdd2TpCancelReceive( PduIdType RxPduId );
uint32         bsw_bswm_cs_Cdd2TpGetTxId( PduIdType PduId );
uint32         bsw_bswm_cs_Cdd2TpGetRxId( PduIdType PduId );


/* CDD1Upper */
Std_ReturnType bsw_bswm_cs_Cdd1UpTriggerTx( PduIdType TxPduId, PduInfoType* PduInfoPtr );
void           bsw_bswm_cs_Cdd1UpTxConfirmation( PduIdType TxPduId, Std_ReturnType result );
void           bsw_bswm_cs_Cdd1UpRxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
BufReq_ReturnType bsw_bswm_cs_Cdd1UpStartOfReception( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType bsw_bswm_cs_Cdd1UpCopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
BufReq_ReturnType bsw_bswm_cs_Cdd1UpCopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
void           bsw_bswm_cs_Cdd1UpTpRxIndication( PduIdType id, Std_ReturnType result );
void           bsw_bswm_cs_Cdd1UpTpTxConfirmation( PduIdType id, Std_ReturnType result );
/* CDD2Upper */
Std_ReturnType bsw_bswm_cs_Cdd2UpTriggerTx( PduIdType TxPduId, PduInfoType* PduInfoPtr );
void           bsw_bswm_cs_Cdd2UpTxConfirmation( PduIdType TxPduId, Std_ReturnType result );
void           bsw_bswm_cs_Cdd2UpRxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
BufReq_ReturnType bsw_bswm_cs_Cdd2UpStartOfReception( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType bsw_bswm_cs_Cdd2UpCopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
BufReq_ReturnType bsw_bswm_cs_Cdd2UpCopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
void           bsw_bswm_cs_Cdd2UpTpRxIndication( PduIdType id, Std_ReturnType result );
void           bsw_bswm_cs_Cdd2UpTpTxConfirmation( PduIdType id, Std_ReturnType result );


/* CDD1 Nm */
Std_ReturnType  bsw_bswm_cs_Cdd1NmPassiveStartUp( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_bswm_cs_Cdd1NmNetworkRequest( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_bswm_cs_Cdd1NmNetworkRelease( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_bswm_cs_Cdd1NmDisableComm( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_bswm_cs_Cdd1NmEnableComm( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_bswm_cs_Cdd1NmGetState( NetworkHandleType nmChannelHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr );
/* CDD2 Nm */
Std_ReturnType  bsw_bswm_cs_Cdd2NmPassiveStartUp( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_bswm_cs_Cdd2NmNetworkRequest( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_bswm_cs_Cdd2NmNetworkRelease( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_bswm_cs_Cdd2NmDisableComm( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_bswm_cs_Cdd2NmEnableComm( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_bswm_cs_Cdd2NmGetState( NetworkHandleType nmChannelHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr );


/* Dummy Function */
void bsw_bswm_cs_DemErrorReport_dummy( uint16 EventId, uint8 EventStatus );
void bsw_bswm_cs_BswMComMCrntMode_dummy( NetworkHandleType Network, ComM_ModeType RequestedMode );
void bsw_bswm_cs_BswMComMCrntPnc_dummy( PNCHandleType PNC, ComM_PncModeType RequestedMode );
void bsw_bswm_cs_BswMComMCrntChPnc_dummy( NetworkHandleType Network, PNCHandleType PNC, ComM_PncModeType RequestedMode );
void bsw_bswm_cs_DcmNoComMode_dummy( uint8 NetworkId );
void bsw_bswm_cs_DcmSilentComMode_dummy( uint8 NetworkId );
void bsw_bswm_cs_DcmFullComMode_dummy( uint8 NetworkId );
BufReq_ReturnType  bsw_bswm_cs_DcmStartOfRecept_dummy( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType  bsw_bswm_cs_DcmCopyRxData_dummy( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
BufReq_ReturnType  bsw_bswm_cs_DcmCopyTxData_dummy( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
void bsw_bswm_cs_DcmTpRxIndication_dummy( PduIdType id, Std_ReturnType result );
void bsw_bswm_cs_DcmTpTxConfirm_dummy( PduIdType id, Std_ReturnType result );
void bsw_bswm_cs_DcmTxConfirm_dummy( PduIdType TxPduId, Std_ReturnType result );
void bsw_bswm_cs_EcuMSetWakeupEv_dummy( uint32 sources );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern  BswConst  Bsw_BswmCS_DcmComMFuncTblType  bsw_bswm_cs_cnct_Dcm_ComM_Func;
extern  BswConst  Bsw_BswmCS_DcmPduRFuncTblType  bsw_bswm_cs_cnct_Dcm_PduR_Func;
extern  BswConst  Bsw_BswmCS_DemFuncTblType      bsw_bswm_cs_cnct_Dem_Func;
extern  BswConst  Bsw_BswmCS_BswMFuncTblType     bsw_bswm_cs_cnct_BswM_Func;
extern  BswConst  Bsw_BswmCS_EcuMFuncTblType     bsw_bswm_cs_cnct_EcuM_Func;

extern  BswConst  Bsw_BswmCS_BswMCddFuncTblType  bsw_bswm_cs_cnct_BswMCdd1_Func;
extern  BswConst  Bsw_BswmCS_BswMCddFuncTblType  bsw_bswm_cs_cnct_BswMCdd2_Func;

extern  BswConst  Bsw_BswmCS_CddSMFuncTblType    bsw_bswm_cs_cnct_Cdd1SM_Func;
extern  BswConst  Bsw_BswmCS_CddSMFuncTblType    bsw_bswm_cs_cnct_Cdd2SM_Func;

extern  BswConst  Bsw_BswmCS_CddIfFuncTblType    bsw_bswm_cs_cnct_Cdd1If_Func;
extern  BswConst  Bsw_BswmCS_CddTpFuncTblType    bsw_bswm_cs_cnct_Cdd1Tp_Func;
extern  BswConst  Bsw_BswmCS_CddIfFuncTblType    bsw_bswm_cs_cnct_Cdd2If_Func;
extern  BswConst  Bsw_BswmCS_CddTpFuncTblType    bsw_bswm_cs_cnct_Cdd2Tp_Func;

extern  BswConst  Bsw_BswmCS_CddUpFuncTblType    bsw_bswm_cs_cnct_Cdd1UpFuncTbl;
extern  BswConst  Bsw_BswmCS_CddUpFuncTblType    bsw_bswm_cs_cnct_Cdd2UpFuncTbl;

extern  BswConst  Bsw_BswmCS_CddNmFuncTblType    bsw_bswm_cs_cnct_Cdd1NmFuncTbl;
extern  BswConst  Bsw_BswmCS_CddNmFuncTblType    bsw_bswm_cs_cnct_Cdd2NmFuncTbl;

#endif  /* BSW_BSWM_CS_CONNECTOR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/26                                             */
/*  v1-1-0          :2018/09/17                                             */
/*  v2-0-0          :2021/03/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
