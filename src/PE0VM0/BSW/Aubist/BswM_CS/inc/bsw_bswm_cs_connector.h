/* bsw_bswm_cs_connector_h_v3-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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

extern  BswConst  Bsw_BswmCS_CddUpFuncTblType    bsw_bswm_cs_cnct_Cdd1UpFuncTbl;
extern  BswConst  Bsw_BswmCS_CddUpFuncTblType    bsw_bswm_cs_cnct_Cdd2UpFuncTbl;

#endif  /* BSW_BSWM_CS_CONNECTOR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/26                                             */
/*  v1-1-0          :2018/09/17                                             */
/*  v2-0-0          :2021/03/02                                             */
/*  v3-0-0          :2024/09/04                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
