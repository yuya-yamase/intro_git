/* Dcm_Dsl_TxMsg_Connector_c(v5-0-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_TxMsg_Connector/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include <PduR_Dcm.h>

#include "../../Dsl/cfg/Dcm_Dsl_Main_Connector_Cfg.h"
#include "../../Dsl/usr/Dcm_Dsl_TxMsg_Connector.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* Function Name | Dcm_Dsl_Cnct_Transmit                                    */
/* Description   | This function is a connector for -                       */
/*               | PduR_DcmTransmit function.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] TxPduId : Identification of the I-PDU.              */
/*               |                                                          */
/*               | [in] info : Length and pointer to the buffer of the      */
/*               |             I-PDU.                                       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK     : request is accepted by the destination module */
/*               |                   transmission is continued.             */
/*               | E_NOT_OK : request is not accepted by the destination    */
/*               |            module transmission is aborted.               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_Cnct_Transmit
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info
)
{
    return PduR_DcmTransmit(TxPduId, info);
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Cnct_Transmit32                                  */
/* Description   | This function is a connector for -                       */
/*               | XxxTpTransmit function.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] id : Identification of the I-PDU.                   */
/*               |                                                          */
/*               | [in] info : Length and pointer to the buffer of the      */
/*               |             I-PDU.                                       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK     : request is accepted by the destination module */
/*               |                   transmission is continued.             */
/*               | E_NOT_OK : request is not accepted by the destination    */
/*               |            module transmission is aborted.               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_Cnct_Transmit32
(
    PduIdType id,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) info
)
{
    /* Call XxxTpTransmit function corresponding to 32-bit Pdu length based on TxPdu Id */
    return Dcm_Dsl_Transmit32(id, info);
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Cnct_CancelTransmit                              */
/* Description   | This function is a connector for -                       */
/*               | PduR_DcmCancelTransmit function.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] TxPduId : Identification of the I-PDU to be         */
/*               |                cancelled.                                */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK     : Cancellation was executed successfully by the */
/*               |            destination module.                           */
/*               | E_NOT_OK : Cancellation was rejected by the destination  */
/*               |            module.                                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_Cnct_CancelTransmit
(
    PduIdType TxPduId
)
{
    return PduR_DcmCancelTransmit(TxPduId);
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2021-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
