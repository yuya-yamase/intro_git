/* Gdn_PduR_Ucfg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Gdn_PduR/Ucfg/HEADER                                        */
/******************************************************************************/
#ifndef GDN_PDUR_UCFG_H
#define GDN_PDUR_UCFG_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef P2FUNC(void, GDN_CALLOUT_CODE, Gdn_PduR_NwRxDstIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, GDN_APPL_CONST) PduInfoPtr
);
typedef P2FUNC(Gdn_Std_ReturnType, GDN_CALLOUT_CODE, Gdn_PduR_NwTxTrgIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, GDN_APPL_CONST) PduInfoPtr
);
typedef P2FUNC(void, GDN_CALLOUT_CODE, Gdn_PduR_NwTxConIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId
);
typedef P2FUNC(Gdn_Std_ReturnType, GDN_CALLOUT_CODE, Gdn_PduR_NwTxTransIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, GDN_APPL_CONST) PduInfoPtr
);
typedef P2FUNC(Gdn_Std_ReturnType, GDN_CALLOUT_CODE, Gdn_PduR_NwTxCancelIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId
);
typedef P2FUNC(Gdn_BufReq_ReturnType, GDN_CALLOUT_CODE, Gdn_PduR_TpRxStartIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, GDN_APPL_CONST) PduInfoPtr,
    VAR(Gdn_PduLengthType, AUTOMATIC) TpSduLength,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, GDN_APPL_DATA) BufferSizePtr
);
typedef P2FUNC(Gdn_BufReq_ReturnType, GDN_CALLOUT_CODE, Gdn_PduR_TpRxCopyIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, GDN_APPL_CONST) PduInfoPtr,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, GDN_APPL_DATA) BufferSizePtr
);
typedef P2FUNC(void, GDN_CALLOUT_CODE, Gdn_PduR_TpRxIndIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) Result
);
typedef P2FUNC(Gdn_Std_ReturnType, GDN_CALLOUT_CODE, Gdn_PduR_TpTxTransIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, GDN_APPL_CONST) PduInfoPtr
);
typedef P2FUNC(Gdn_BufReq_ReturnType, GDN_CALLOUT_CODE, Gdn_PduR_TpTxCopyIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, GDN_APPL_CONST) PduInfoPtr,
    P2CONST(Gdn_RetryInfoType, AUTOMATIC, GDN_APPL_CONST) RetryInfoPtr,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, GDN_APPL_DATA) BufferSizePtr
);
typedef P2FUNC(void, GDN_CALLOUT_CODE, Gdn_PduR_TpTxConIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) Result
);
typedef P2FUNC(Gdn_Std_ReturnType, GDN_CALLOUT_CODE, Gdn_PduR_TpRxCancelIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId
);
typedef P2FUNC(Gdn_Std_ReturnType, GDN_CALLOUT_CODE, Gdn_PduR_TpRxChgParIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    VAR(Gdn_TPParameterType, AUTOMATIC) Parameter,
    VAR(gdn_uint16, AUTOMATIC) Value
);
typedef P2FUNC(Gdn_Std_ReturnType, GDN_CALLOUT_CODE, Gdn_PduR_TpTxCancelIfType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId
);

typedef struct {
    Gdn_PduR_NwRxDstIfType                  DstInterface;
    Gdn_PduIdType                           PduId;
} Gdn_PduR_LoNwRxDstInfoType;

typedef struct {
    gdn_uint16                              DestinationCnt;
    GdnConst Gdn_PduR_LoNwRxDstInfoType*    DestinationInfo;
} Gdn_PduR_LoNwRxRoutingTblType;

typedef struct {
    Gdn_PduIdType                           PduId;
#if ( GDN_PDUR_TriggerTransmitApi_Nw == GDN_ON )
    Gdn_PduR_NwTxTrgIfType                  TxTriggerIf;
#endif
#if ( GDN_PDUR_TxConfirmationApi_Nw == GDN_ON )
    Gdn_PduR_NwTxConIfType                  TxConfirmIf;
#endif
    Gdn_PduIdType                           SduId;
} Gdn_PduR_LoNwTxRoutingTblType;

typedef struct {
    Gdn_PduR_NwTxTransIfType                TxTransmit;
#if ( GDN_PDUR_CancelTransmitApi_Nw == GDN_ON )
    Gdn_PduR_NwTxCancelIfType               TxCancel;
#endif
    Gdn_PduIdType                           PduId;
} Gdn_PduR_UpNwTxRoutingTblType;

typedef struct {
    Gdn_PduR_TpTxTransIfType                TxTransmit;
    Gdn_PduIdType                           PduId;
    Gdn_PduLengthType*                      TxDataPtr;
} Gdn_PduR_LoTpGatewayInfoType;

typedef struct {
    Gdn_PduR_TpRxStartIfType                StartOfReception;
    Gdn_PduR_TpRxCopyIfType                 CopyRxData;
    Gdn_PduR_TpRxIndIfType                  RxIndication;
    Gdn_PduIdType                           PduId;
    gdn_uint8                               GatewayCnt;
    GdnConst Gdn_PduR_LoTpGatewayInfoType*  GatewayInfo;
    Gdn_PduLengthType                       BufferSize;
    gdn_uint8*                              GatewayBuffer;
} Gdn_PduR_LoTpRxRoutingTblType;

typedef struct {
    gdn_uint8                               PduIdCnt;
    GdnConst Gdn_PduR_LoTpRxRoutingTblType* RxRoutingTbl;
    Gdn_PduLengthType*                      BufPosition;
} Gdn_PduR_LoTpRxTableListType;

typedef struct {
    Gdn_PduIdType                           PduId;
    Gdn_PduR_TpTxCopyIfType                 CopyTxData;
    Gdn_PduR_TpTxConIfType                  TxConfirmation;
    Gdn_PduIdType                           SduId;
    gdn_uint8                               ComponentIdx;
    Gdn_PduIdType                           RxPduId;
    gdn_uint8                               GatewayIdx;
} Gdn_PduR_LoTpTxRoutingTblType;

typedef struct {
    Gdn_PduIdType                           SduId;
#if ( GDN_PDUR_CancelReceiveApi_Tp == GDN_ON )
    Gdn_PduR_TpRxCancelIfType               RxCancel;
#endif
#if ( GDN_PDUR_ChangeParameterApi_Tp == GDN_ON )
    Gdn_PduR_TpRxChgParIfType               ChangeParam;
#endif
    Gdn_PduIdType                           PduId;
} Gdn_PduR_UpTpRxRoutingTblType;

typedef struct {
    Gdn_PduR_TpTxTransIfType                TxTransmit;
#if ( GDN_PDUR_CancelTransmitApi_Tp == GDN_ON )
    Gdn_PduR_TpTxCancelIfType               TxCancel;
#endif
    Gdn_PduIdType                           PduId;
} Gdn_PduR_UpTpTxRoutingTblType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define GDN_PDUR_START_SEC_VAR
#include <Gdn_PduR_MemMap.h>

#if ( ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoTp_0 != 0U ) )
extern Gdn_PduLengthType Gdn_PduR_LoTpRxDataPtr_0[GDN_PDUR_MaxRxPduIdCnt_LoTp_0];
#endif

#define GDN_PDUR_STOP_SEC_VAR
#include <Gdn_PduR_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define GDN_PDUR_START_SEC_CST
#include <Gdn_PduR_MemMap.h>

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_OnlyZeroCost_Tp != GDN_ON ) )
extern GdnConst Gdn_PduR_LoTpRxTableListType gdn_pdur_LoTpRxRoutingTableList[GDN_PDUR_MaxLoLayerCnt_Tp];
#endif
#if ( ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoTp_0 != 0U ) )
extern GdnConst Gdn_PduR_LoTpRxRoutingTblType gdn_pdur_LoTpRxRoutingTbl_0[GDN_PDUR_MaxRxPduIdCnt_LoTp_0];
#endif
#if ( ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxTxPduIdCnt_LoTp_0 != 0U ) )
extern GdnConst Gdn_PduR_LoTpTxRoutingTblType gdn_pdur_LoTpTxRoutingTbl_0[GDN_PDUR_MaxTxPduIdCnt_LoTp_0];
#endif
#if ( ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_UpTp_0 != 0U ) )
extern GdnConst Gdn_PduR_UpTpRxRoutingTblType gdn_pdur_UpTpRxRoutingTbl_0[GDN_PDUR_MaxRxPduIdCnt_UpTp_0];
#endif
#if ( ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_MaxTxPduIdCnt_UpTp_0 != 0U ) )
extern GdnConst Gdn_PduR_UpTpTxRoutingTblType gdn_pdur_UpTpTxRoutingTbl_0[GDN_PDUR_MaxTxPduIdCnt_UpTp_0];
#endif
#if ( ( GDN_PDUR_UseZeroCost_LoNw_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoNw_0 != 0U ) )
extern GdnConst Gdn_PduR_LoNwRxRoutingTblType gdn_pdur_LoNwRxRoutingTbl_0[GDN_PDUR_MaxRxPduIdCnt_LoNw_0];
#endif
#if ( ( GDN_PDUR_UseZeroCost_LoNw_0 != GDN_ON ) && ( GDN_PDUR_MaxTxPduIdCnt_LoNw_0 != 0U ) )
extern GdnConst Gdn_PduR_LoNwTxRoutingTblType gdn_pdur_LoNwTxRoutingTbl_0[GDN_PDUR_MaxTxPduIdCnt_LoNw_0];
#endif

#define GDN_PDUR_STOP_SEC_CST
#include <Gdn_PduR_MemMap.h>


#endif /* GDN_PDUR_UCFG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2019/12/03 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

