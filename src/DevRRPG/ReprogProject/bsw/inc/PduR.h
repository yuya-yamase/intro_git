/* PduR_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | PduR/HEADER                                                 */
/******************************************************************************/
#ifndef PDUR_H
#define PDUR_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
#include <ComStack_Types.h>
#include <SubMiconIf.h>
#include <Gdn.h>
#include <CanTp/Gdn_CanTp.h>
#endif

#if (REPROG_CFG_ETH_USE == STD_ON)
 #if (REPROG_CFG_ETH_DOIP_USE == STD_ON)
 #include <DoIP.h>
 #else
 #include <SoAd.h>
 #endif
#endif

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
#define PduR_SubMiconIfStartOfReception(RxPduId, PduInfoPtr, TpSduLength, RxBufferSizePtr)    \
    ((BufReq_ReturnType)Gdn_PduR_SubMiconIfStartOfReception((RxPduId), (PduInfoPtr), (TpSduLength), (RxBufferSizePtr)))
#define PduR_SubMiconIfCopyRxData(RxPduId, PduInfoPtr, RxBufferSizePtr) \
    ((BufReq_ReturnType)Gdn_PduR_SubMiconIfCopyRxData((RxPduId), (PduInfoPtr), (RxBufferSizePtr)))
#define PduR_SubMiconIfRxIndication(RxPduId, Result)    \
    (Gdn_PduR_SubMiconIfRxIndication((Gdn_PduIdType)(RxPduId), (Gdn_NotifResultType)(Result)))
#define PduR_SubMiconIfCopyTxData(TxPduId, PduInfoPtr, RetryInfoPtr, TxDataCntPtr)  \
    ((BufReq_ReturnType)Gdn_PduR_SubMiconIfCopyTxData((TxPduId), (PduInfoPtr), (RetryInfoPtr), (TxDataCntPtr)))
#define PduR_SubMiconIfTxConfirmation(TxPduId, Result)  \
    (Gdn_PduR_SubMiconIfTxConfirmation((TxPduId), (Result)))
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
FUNC(Std_ReturnType, PDUR_CODE_SLOW) PduR_CancelReceive
(
    VAR(PduIdType, AUTOMATIC) RxSduId
);
FUNC(Std_ReturnType, PDUR_CODE_SLOW) PduR_CancelTransmit
(
    VAR(PduIdType, AUTOMATIC) TxSduId
);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* PDUR_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

