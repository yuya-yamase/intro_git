/* PduR_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | PduR/CODE                                                   */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <ComStack_Types.h>

#if (REPROG_CFG_ETH_USE == STD_ON)
#include <Gdn.h>
#include <ComM.h>
 #if (REPROG_CFG_ETH_DOIP_USE == STD_ON)
 #include <PduR_DoIP.h>
 #else
 #include <PduR_SoAd.h>
 #endif
#endif
#include <PduR.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define PDUR_START_SEC_VAR
#include <PduR_MemMap.h>

#define PDUR_STOP_SEC_VAR
#include <PduR_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define PDUR_START_SEC_CST
#include <PduR_MemMap.h>

#define PDUR_STOP_SEC_CST
#include <PduR_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define PDUR_START_SEC_CODE
#include <PduR_MemMap.h>

#if (REPROG_CFG_ETH_USE == STD_ON)
 #if (REPROG_CFG_ETH_DOIP_USE == STD_ON)
/******************************************************************************/
/* Function Name | PduR_DoIPTpStartOfReception                                */
/* Description   | Wrapper of Gdn_PduR_DoIPStartOfReception                   */
/* Preconditions |                                                            */
/* Parameters    | [IN]id               : PduId                               */
/*               | [IN]info             : Pointer to PduData                  */
/*               | [IN]TpSduLength      : Length of SduData                   */
/*               | [OUT]bufferSizePtr   : Pointer to buffer size              */
/* Return Value  | Status                                                     */
/*               |  BUFREQ_OK                                                 */
/*               |  BUFREQ_E_NOT_OK                                           */
/*               |  BUFREQ_E_OVFL                                             */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE_SLOW) PduR_DoIPTpStartOfReception
(
    VAR(PduIdType, AUTOMATIC) id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) info,
    VAR(PduLengthType, AUTOMATIC) TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr
)
{
    VAR(BufReq_ReturnType, AUTOMATIC) Result;

    Result = (BufReq_ReturnType)Gdn_PduR_DoIPStartOfReception( (Gdn_PduIdType) id,
                                                               (const Gdn_PduInfoType*) info,
                                                               (Gdn_PduLengthType) TpSduLength,
                                                               (Gdn_PduLengthType*) bufferSizePtr );

    return Result;
}

/******************************************************************************/
/* Function Name | PduR_DoIPTpCopyRxData                                      */
/* Description   | Wrapper of Gdn_PduR_DoIPCopyRxData                         */
/* Preconditions |                                                            */
/* Parameters    | [IN]id               : PduId                               */
/*               | [IN]info             : Pointer to PduData                  */
/*               | [OUT]bufferSizePtr   : Pointer to buffer size              */
/* Return Value  | Status                                                     */
/*               |  BUFREQ_OK                                                 */
/*               |  BUFREQ_E_NOT_OK                                           */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE_SLOW) PduR_DoIPTpCopyRxData
(
    VAR(PduIdType, AUTOMATIC) id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr
)
{
    VAR(BufReq_ReturnType, AUTOMATIC) Result;

    Result = (BufReq_ReturnType)Gdn_PduR_DoIPCopyRxData( (Gdn_PduIdType) id,
                                                         (const Gdn_PduInfoType*) info,
                                                         (Gdn_PduLengthType*) bufferSizePtr );

    return Result;
}

/******************************************************************************/
/* Function Name | PduR_DoIPTpRxIndication                                    */
/* Description   | Wrapper of Gdn_PduR_DoIPRxIndication                       */
/* Preconditions |                                                            */
/* Parameters    | [IN]id       : PduId                                       */
/*               | [IN]result   : Result of reception                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) PduR_DoIPTpRxIndication
(
    VAR(PduIdType, AUTOMATIC) id,
    VAR(Std_ReturnType, AUTOMATIC) result
)
{
    Gdn_PduR_DoIPRxIndication( (Gdn_PduIdType) id,
                               (Gdn_NotifResultType) result );

    return;
}

/******************************************************************************/
/* Function Name | PduR_DoIPTpCopyTxData                                      */
/* Description   | Wrapper of Gdn_PduR_DoIPCopyTxData                         */
/* Preconditions |                                                            */
/* Parameters    | [IN]id               : PduId                               */
/*               | [IN]info             : Pointer to PduData                  */
/*               | [IN]retry            : Pointer to information of retry     */
/*               | [OUT]availableDataPtr: Pointer to remaining size           */
/* Return Value  | Status                                                     */
/*               |  BUFREQ_OK                                                 */
/*               |  BUFREQ_E_NOT_OK                                           */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE_SLOW) PduR_DoIPTpCopyTxData
(
    VAR(PduIdType, AUTOMATIC) id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) info,
    P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr
)
{
    VAR(BufReq_ReturnType, AUTOMATIC) Result;

    Result = (BufReq_ReturnType)Gdn_PduR_DoIPCopyTxData( (Gdn_PduIdType) id,
                                                         (const Gdn_PduInfoType*) info,
                                                         (const Gdn_RetryInfoType*) retry,
                                                         (Gdn_PduLengthType*) availableDataPtr );

    return Result;
}

/******************************************************************************/
/* Function Name | PduR_DoIPTpTxConfirmation                                  */
/* Description   | Wrapper of Gdn_PduR_DoIPTxConfirmation                     */
/* Preconditions |                                                            */
/* Parameters    | [IN]id       : PduId                                       */
/*               | [IN]result   : Result of transmission                      */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) PduR_DoIPTpTxConfirmation
(
    VAR(PduIdType, AUTOMATIC) id,
    VAR(Std_ReturnType, AUTOMATIC) result
)
{
    Gdn_PduR_DoIPTxConfirmation( (Gdn_PduIdType) id,
                                 (Gdn_NotifResultType) result );

    return;
}

/******************************************************************************/
/* Function Name | PduR_DoIPIfTxConfirmation                                  */
/* Description   | Dummy Function(IF-TxConfirmation)                          */
/* Preconditions |                                                            */
/* Parameters    | [IN]id   : PduId                                           */
/* Return Value  | None                                                       */
/* Notes         | This function is not called. If this function is called,   */
/*               | there are not anything to do.                              */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) PduR_DoIPIfTxConfirmation
(
    VAR(PduIdType, AUTOMATIC) id
)
{
    /* No process */
    return;
}

 #else
/******************************************************************************/
/* Function Name | PduR_SoAdTpStartOfReception                                */
/* Description   | Wrapper of Gdn_PduR_SoAdStartOfReception                   */
/* Preconditions |                                                            */
/* Parameters    | [IN]id               : PduId                               */
/*               | [IN]info             : Pointer to PduData                  */
/*               | [IN]TpSduLength      : Length of SduData                   */
/*               | [OUT]bufferSizePtr   : Pointer to buffer size              */
/* Return Value  | Status                                                     */
/*               |  BUFREQ_OK                                                 */
/*               |  BUFREQ_E_NOT_OK                                           */
/*               |  BUFREQ_E_OVFL                                             */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE_SLOW) PduR_SoAdTpStartOfReception
(
    VAR(PduIdType, AUTOMATIC) id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) info,
    VAR(PduLengthType, AUTOMATIC) TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr
)
{
    VAR(BufReq_ReturnType, AUTOMATIC) Result;

    Result = (BufReq_ReturnType)Gdn_PduR_SoAdStartOfReception( (Gdn_PduIdType) id,
                                                               (const Gdn_PduInfoType*) info,
                                                               (Gdn_PduLengthType) TpSduLength,
                                                               (Gdn_PduLengthType*) bufferSizePtr );

    return Result;
}

/******************************************************************************/
/* Function Name | PduR_SoAdTpCopyRxData                                      */
/* Description   | Wrapper of Gdn_PduR_SoAdCopyRxData                         */
/* Preconditions |                                                            */
/* Parameters    | [IN]id               : PduId                               */
/*               | [IN]info             : Pointer to PduData                  */
/*               | [OUT]bufferSizePtr   : Pointer to buffer size              */
/* Return Value  | Status                                                     */
/*               |  BUFREQ_OK                                                 */
/*               |  BUFREQ_E_NOT_OK                                           */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE_SLOW) PduR_SoAdTpCopyRxData
(
    VAR(PduIdType, AUTOMATIC) id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr
)
{
    VAR(BufReq_ReturnType, AUTOMATIC) Result;

    Result = (BufReq_ReturnType)Gdn_PduR_SoAdCopyRxData( (Gdn_PduIdType) id,
                                                         (const Gdn_PduInfoType*) info,
                                                         (Gdn_PduLengthType*) bufferSizePtr );

    return Result;
}

/******************************************************************************/
/* Function Name | PduR_SoAdTpRxIndication                                    */
/* Description   | Wrapper of Gdn_PduR_SoAdRxIndication                       */
/* Preconditions |                                                            */
/* Parameters    | [IN]id       : PduId                                       */
/*               | [IN]result   : Result of reception                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) PduR_SoAdTpRxIndication
(
    VAR(PduIdType, AUTOMATIC) id,
    VAR(Std_ReturnType, AUTOMATIC) result
)
{
    Gdn_PduR_SoAdRxIndication( (Gdn_PduIdType) id,
                               (Gdn_NotifResultType) result );

    return;
}

/******************************************************************************/
/* Function Name | PduR_SoAdTpCopyTxData                                      */
/* Description   | Wrapper of Gdn_PduR_SoAdCopyTxData                         */
/* Preconditions |                                                            */
/* Parameters    | [IN]id               : PduId                               */
/*               | [IN]info             : Pointer to PduData                  */
/*               | [IN]retry            : Pointer to information of retry     */
/*               | [OUT]availableDataPtr: Pointer to remaining size           */
/* Return Value  | Status                                                     */
/*               |  BUFREQ_OK                                                 */
/*               |  BUFREQ_E_NOT_OK                                           */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE_SLOW) PduR_SoAdTpCopyTxData
(
    VAR(PduIdType, AUTOMATIC) id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) info,
    P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr
)
{
    VAR(BufReq_ReturnType, AUTOMATIC) Result;

    Result =  (BufReq_ReturnType)Gdn_PduR_SoAdCopyTxData( (Gdn_PduIdType) id,
                                                          (const Gdn_PduInfoType*) info,
                                                          (const Gdn_RetryInfoType*) retry,
                                                          (Gdn_PduLengthType*) availableDataPtr );

    return Result;
}

/******************************************************************************/
/* Function Name | PduR_SoAdTpTxConfirmation                                  */
/* Description   | Wrapper of Gdn_PduR_SoAdTxConfirmation                     */
/* Preconditions |                                                            */
/* Parameters    | [IN]id       : PduId                                       */
/*               | [IN]result   : Result of transmission                      */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) PduR_SoAdTpTxConfirmation
(
    VAR(PduIdType, AUTOMATIC) id,
    VAR(Std_ReturnType, AUTOMATIC) result
)
{
    Gdn_PduR_SoAdTxConfirmation( (Gdn_PduIdType) id,
                                 (Gdn_NotifResultType) result );

    return;
}

/******************************************************************************/
/* Function Name | PduR_SoAdIfRxIndication                                    */
/* Description   | Dummy Function(IF-RxIndication)                            */
/* Preconditions |                                                            */
/* Parameters    | [IN]id   : PduId                                           */
/*               | [IN]info : Pointer to PduData                              */
/* Return Value  | None                                                       */
/* Notes         | This function is not called. If this function is called,   */
/*               | there are not anything to do.                              */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) PduR_SoAdIfRxIndication
(
    VAR(PduIdType, AUTOMATIC) id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) info
)
{
    /* No process */
    return ;
}

/******************************************************************************/
/* Function Name | PduR_SoAdIfTxConfirmation                                  */
/* Description   | Dummy Function(IF-TxConfirmation)                          */
/* Preconditions |                                                            */
/* Parameters    | [IN]id   : PduId                                           */
/* Return Value  | None                                                       */
/* Notes         | This function is not called. If this function is called,   */
/*               | there are not anything to do.                              */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) PduR_SoAdIfTxConfirmation
(
    VAR(PduIdType, AUTOMATIC) id
)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Function Name | PduR_SoConModeChg                                          */
/* Description   | Notification about a SoAd socket connection state change   */
/* Preconditions |                                                            */
/* Parameters    | [IN]SoConId: socket connection index                       */
/*               | [IN]Mode   : new socket connection mode                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) PduR_SoConModeChg
(
    VAR(SoAd_SoConIdType, AUTOMATIC) SoConId,
    VAR(SoAd_SoConModeType, AUTOMATIC) Mode
)
{
    if( Mode == SOAD_SOCON_ONLINE)
    {
        ComM_NotifyCommunicationStart();
    }

    return;
}
 #endif
#endif

#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )

/******************************************************************************/
/* Function Name | PduR_CancelReceive                                         */
/* Description   | CancelReceive dummy function                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] RxSduId : Receive SduId                               */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE_SLOW) PduR_CancelReceive
(
    VAR(PduIdType, AUTOMATIC) RxSduId
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_OK;

    return Ret;
}

/******************************************************************************/
/* Function Name | PduR_CancelTransmit                                        */
/* Description   | CancelTransmit dummy function                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] TxSduId : Transmit SduId                              */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE_SLOW) PduR_CancelTransmit
(
    VAR(PduIdType, AUTOMATIC) TxSduId
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_OK;

    return Ret;
}

#endif

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define PDUR_STOP_SEC_CODE
#include <PduR_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

