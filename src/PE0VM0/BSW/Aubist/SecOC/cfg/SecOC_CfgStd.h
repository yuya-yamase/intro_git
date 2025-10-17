/* SecOC_CfgStd_h_v2-1-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/CfgStd/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/

#ifndef SECOC_CFGSTD_H
#define SECOC_CFGSTD_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOC_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define SECOC_RX_PDU_PROCESSING_MAX (0U)
#define SECOC_AB_RX_SECURED_MSG_IN_BUS_COUNT_MAX (0U)
#define SECOC_TX_PDU_PROCESSING_MAX (16U)
#define SECOC_AB_TX_SECURED_MSG_IN_BUS_COUNT_MAX (15U)
#define SECOC_AB_BUS_MAX (4U)
#define SECOC_AB_VERIFICATION_FINAL_STATUS_CALLOUT_MAX (0U)
#define SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX (0U)
#define SECOC_AB_RXMSG_BUSY_DESTRUCTION_CALLOUT_MAX (0U)
#define SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX (0U)
#define SECOC_BOTH (0U)
#define SECOC_FAILURE_ONLY (1U)
#define SECOC_NONE (2U)
#define SECOC_AB_FV_NONE (0U)
#define SECOC_AB_FV_RTE (1U)
#define SECOC_AB_FV_CFUNC (2U)
#define SECOC_AB_MSGTYPE_SECURED (0U)
#define SECOC_AB_MSGTYPE_SYNC (1U)
#define SECOC_AB_MSGTYPE_TRIPSYNC (2U)
#define SECOC_AB_MSGTYPE_RESETSYNC (3U)
#define SECOC_AB_MSGTYPE_RESYNC (4U)
#define SECOC_AB_PROTOCOL_CAN (0U)
#define SECOC_AB_PROTOCOL_ETHER (1U)
#define SECOC_IFPDU (0U)
#define SECOC_TPPDU (1U)
#define SECOC_AB_FV_TRUNC (0U)
#define SECOC_AB_FV_FULL (1U)
#define SECOC_AB_DESTRUCTION_OVERRIDE (0U)
#define SECOC_AB_DESTRUCTION_IGNORE (1U)
#define SECOC_AB_CSM_REQ_SC (0U)
#define SECOC_AB_CSM_REQ_SA (1U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef P2FUNC( void, SECOC_CODE_CALLOUT, SecOC_VerificationStatusCalloutType )( SecOC_VerificationStatusType verificationStatus );
typedef P2FUNC( void, SECOC_CODE_CALLOUT, SecOC_VerificationFinalStatusCalloutType )( SecOC_VerificationStatusType verificationStatus, P2CONST( uint8, AUTOMATIC, SECOC_APPL_DATA ) SduDataPtr, PduLengthType SduLength);
typedef P2FUNC( void, SECOC_CD_FV_CODE, SecOC_Ab_FreshnessValueCalloutType )( SecOC_VerificationStatusType stVerResult );

typedef P2FUNC( Std_ReturnType, SECOC_CD_FV_CODE, SecOC_GetTxFreshnessTruncDataType )( uint16 SecOCFreshnessValueID, P2VAR( uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA ) SecOCFreshnessValue, P2VAR( uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA ) SecOCFreshnessValueLength, P2VAR( uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA ) SecOCTruncatedFreshnessValue, P2VAR( uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA ) SecOCTruncatedFreshnessValueLength );
typedef P2FUNC( void, SECOC_CD_FV_CODE, SecOC_SPduTxConfirmationType )( uint16 SecOCFreshnessValueID );
typedef P2FUNC( Std_ReturnType, SECOC_CD_FV_CODE, SecOC_GetRxFreshnessType )( uint16 SecOCFreshnessValueID, P2CONST( uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA ) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength, uint16 SecOCAuthVerifyAttempts, P2VAR( uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA ) SecOCFreshnessValue, P2VAR( uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA ) SecOCFreshnessValueLength );
typedef P2FUNC( Std_ReturnType, SECOC_CODE_CALLOUT, SecOC_Ab_ReportErrorCalloutType )( SecOC_ErrorStatusType udErrorStatus );
typedef P2FUNC( void, SECOC_CODE_CALLOUT, SecOC_ErrorDetailNotifyCalloutType )( uint16 u2FreshnessValueId, Std_ReturnType udErrorDetail );
typedef P2FUNC( void, SECOC_CODE_CALLOUT,SecOC_Ab_RxMsgOverflowDestructionCalloutType )( uint16 FvId, uint32 SecOC_Ab_DataId, uint8 notice );
typedef P2FUNC( void, SECOC_CODE_CALLOUT,SecOC_Ab_RxMsgBusyDestructionCalloutType )(uint16 FvId, uint32 SecOC_Ab_DataId );
typedef P2FUNC( void, SECOC_CODE_CALLOUT,SecOC_Ab_TxMsgBusyDestructionCalloutType )(uint16 FvId, uint32 SecOC_Ab_DataId );

typedef struct {
    uint32   CsmJobId;
    uint8    CsmProcessingMode;
    uint8    dummy[3];
} SecOC_AuthServiceConfigRefType;

typedef struct {
    uint16                               Ab_BusID;
    uint16                               Ab_Protocol;
    uint32                               Ab_VerifyStartCount;
    uint16                               Ab_FreshnessValueID;
    uint8                                Ab_ClearAcceptanceWindow;
    uint8                                dummy1;
    uint16                               Ab_FvType;
    uint16                               Ab_FvTypeIndex;
    uint16                               Ab_DataIdLength;
    uint16                               dummy2;
} SecOC_Ab_BusCollectionType;


typedef struct {
    uint16                              Ab_AuthInfoLength;
    uint16                              AuthInfoTruncLength;
    uint16                              Ab_BusIndex;
    uint16                              Ab_TxSecurityDataSize;
    uint16                              AuthenticationBuildAttempts;
    uint16                              Ab_QueryFreshnessValue;
    uint32                              Ab_DataId;
    uint16                              FreshnessValueId;
    uint16                              FreshnessValueLength;
    uint16                              FreshnessValueTruncLength;
    uint16                              Ab_ProtDataPaddingSize;
    SecOC_AuthServiceConfigRefType      TxAuthServiceConfigRef;
    uint32                              SameBufferPduRef;
    uint32                              Ab_BufferStartOffset;
    uint32                              Ab_TxMakeAuthBufferSize;
    uint32                              Ab_TxBufferStartOffset;
    SecOC_SPduTxConfirmationType        Ab_SecuredPduTransmitFuncName;
    uint16                              TxAuthenticLayerPduId;
    uint16                              TxSecuredLayerPduId;
    SecOC_GetTxFreshnessTruncDataType   Ab_FreshnessValueFuncName;
    SecOC_ErrorDetailNotifyCalloutType  Ab_ErrorDetailNotifyCallout;
    uint32                              Ab_TxAuthTpCopySize;
    uint16                              dummy1;
    uint16                              Ab_MessageTypeIndex;
    uint8                               Ab_MessageType;
    uint8                               TxAuthPduType;
    uint8                               Ab_TxSecuredPduType;
    uint8                               Ab_CsmReqType;
    uint16                              Ab_TxAuthTpCopyAttempts;
    uint16                              Ab_TxAuthenticLayerPduRefId;
    uint16                              Ab_TxSecuredLayerPduRefId;
    uint16                              Ab_TxTransmitAttempts;
    SecOC_Ab_TxMsgBusyDestructionCalloutType  Ab_TxMsgBusyDestructionCallout[1];
    uint32                              Ab_CsmReqSaSizeMax;
} SecOC_TxPduProcessingType;


typedef struct {
    uint16     Ab_ProcessingCount;
    uint16     Ab_TxProcessingCount;
} SecOC_SecOCGeneralConfigType;

typedef struct {
    uint16     AuthInfoTruncLength;
    uint16     AuthenticationBuildAttempts;
    uint32     Ab_DataId;
    uint16     FreshnessValueId;
    uint16     FreshnessValueLength;
    uint16     FreshnessValueTruncLength;
    uint8      VerifyStatusPropagationMode;
    uint8      dummy1;
} SecOC_SecOCRxPduProcessingConfigType;

typedef struct {
    uint16     AuthInfoTruncLength;
    uint16     FreshnessValueId;
    uint16     FreshnessValueLength;
    uint16     FreshnessValueTxLength;
    uint32     Ab_DataId;
} SecOC_SecOCTxPduProcessingConfigType;

typedef struct {
    uint16     Ab_VerifyStart;
    uint8      Ab_ClearAcceptanceWindow;
    uint8      dummy;
} SecOC_SecOC_Ab_BusCollectionConfigType;

typedef struct {
    SecOC_SecOCGeneralConfigType          SecOCGeneral;
    SecOC_SecOCTxPduProcessingConfigType  SecOCTxPduProcessing[SECOC_TX_PDU_PROCESSING_MAX];
    SecOC_SecOC_Ab_BusCollectionConfigType SecOCAbBusCollection[SECOC_AB_BUS_MAX];
} SecOC_ConfigType;

typedef struct {
    uint16 Ab_TxSecuredMsgCount;
    uint16 Ab_TxSecuredMsgIdxList[SECOC_AB_TX_SECURED_MSG_IN_BUS_COUNT_MAX];
} SecOC_Ab_BusId2SecuredMsgIdxType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/



#endif /* SECOC_CFGSTD_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

