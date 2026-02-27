/* Dcm_Dsl_TxIf_c(v5-8-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_TxIf/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/inc/Dcm_Dsl_TxIf.h"
#include "../../Dsl/usr/Dcm_Dsl_TxMsg_Connector.h"

#include "../../Dsl/inc/Dcm_Dsl_CommHandling.h"
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_TmrSrv.h>

#include <Dcm.h>
#include <SchM_Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_SINGLE_CLIENT  ((uint8)0x01U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsl_TxIf_StartFsTimer
(void);
static FUNC(void, DCM_CODE) Dcm_Dsl_TxIf_StopFsTimer
(void);
static FUNC(PduIdType, DCM_CODE) Dcm_Dsl_TxIf_GetPeriodicTxPduID
(
    const uint16 u2PduMapIndex,
    const uint8  u1PeriodicIndex
);
static FUNC(uint16, DCM_CODE) Dcm_Dsl_TxIf_GetPduMapIndexByTxConfPduID
(
    const PduIdType uvTxConfPduId
);

#endif /*  DCM_DSL_PERIODICTX_ENABLE == STD_ON  */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

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
/* Function Name | Dcm_Dsl_TxIf_Init                                        */
/* Description   | This function initializes Dsl_TxIf.                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxIf_Init
(void)
{
    return ;
}

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_TxConfirmation                                       */
/* Description   | The lower layer communication interface module confirms  */
/*               | the transmission of an I-PDU.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] TxPduId : ID of the I-PDU that has been transmitted */
/*               |                                                          */
/*               | [in] result : E_OK      The PDU was transmitted.         */
/*               |               E_NOT_OK  Transmission of the PDU failed.  */
/* Return Value  | none                                                     */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_TxConfirmation
(
    PduIdType TxPduId,
    Std_ReturnType result
)
{
    uint16 u2_IfPduMapIndex;

    u2_IfPduMapIndex = Dcm_Dsl_TxIf_GetPduMapIndexByTxConfPduID(TxPduId);
    if( u2_IfPduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        Dcm_Dsl_TxIf_StopFsTimer();
        Dcm_Dsl_Ctrl_IfConfirmation(u2_IfPduMapIndex, result);
    }

    return ;
}
#endif /* DCM_DSL_PERIODICTX_ENABLE == STD_ON */

#if( DCM_DSL_PERIODICTX_ENABLE == STD_OFF )
FUNC(void, DCM_CODE) Dcm_TxConfirmation
(
    PduIdType      TxPduId,
    Std_ReturnType result
)
{
    if( result == (Std_ReturnType)E_OK )
    {
        /* none */
    }

    if( TxPduId == DCM_DSL_INVALID_U2_DATA )
    {
        /* none */
    }
    return ;
}
#endif /* DCM_DSL_PERIODICTX_ENABLE == STD_OFF */

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_TxIfTOCbk                                        */
/* Description   | This function performs a process in TxFailsafe time out. */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TimerId : not use                                 */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxIfTOCbk
(
    const uint8 u1TimerId /* MISRA DEVIATION */
)
{
    Dcm_Dsl_Ctrl_IfTimeout();

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxIf_PeriodicTransmit                            */
/* Description   | This function sends a periodic response message          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] u1PeriodicIndex : Periodic Connection Index         */
/*               | [in] ptInfo : PduR sending buffer address                */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                     : Success                     */
/*               |   DCM_DSL_TXIF_E_SEND_ERR  : Transmission Error          */
/*               |   DCM_DSL_TXIF_E_DISABLE   : Transmission prohibited     */
/*               |   DCM_DSL_TXIF_E_SUPPRES   : Transmission suppressed     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxIf_PeriodicTransmit
(
    const uint16 u2PduMapIndex,
    const uint8  u1PeriodicIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
)
{
    P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_Info;
    PduIdType      uv_TxPduId;
    Std_ReturnType u1_Result;
    Std_ReturnType u1_Retval;
    boolean        b_IsComEnable;
    boolean        b_IsNoResponsePduId;
    /* Measures to avoid worrying about member MetaDataPtr */
    PduInfoType    st_Info;

    Dcm_Main_SetMemory( (uint8*)&st_Info, (uint8)0U, (uint16)(sizeof(st_Info)) );
    st_Info.SduLength   = (PduLengthType)ptInfo->SduLength;
    st_Info.SduDataPtr  = ptInfo->SduDataPtr;
    pt_Info             = &st_Info;
    u1_Result           = (Std_ReturnType)E_OK;
    b_IsNoResponsePduId = Dcm_Dsl_Ctrl_IsNoResPduID(u2PduMapIndex);

    if( b_IsNoResponsePduId == (boolean)FALSE )
    {
        b_IsComEnable = Dcm_Dsl_CmHdl_IsComEnable(u2PduMapIndex, DCM_DSL_COMTYPE_TRANSMIT);
        if( b_IsComEnable == (boolean)TRUE )
        {
            uv_TxPduId = Dcm_Dsl_TxIf_GetPeriodicTxPduID(u2PduMapIndex, u1PeriodicIndex);
            u1_Retval  = Dcm_Dsl_Cnct_Transmit(uv_TxPduId, pt_Info);
            if( u1_Retval == (Std_ReturnType)E_OK )
            {
                Dcm_Dsl_TxIf_StartFsTimer();
            }
            else
            {
                u1_Result = DCM_DSL_TXIF_E_SEND_ERR;
            }
        }
        else
        {
            u1_Result = DCM_DSL_TXIF_E_DISABLE;
        }
    }
    else
    {
        u1_Result = DCM_DSL_TXIF_E_SUPPRES;
    }

    return u1_Result;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxIf_StartFsTimer                                */
/* Description   | Start fail-safe timer according to parallel transmission */
/*               | status.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxIf_StartFsTimer
(void)
{
    uint32  u4_TimerValue;
    u4_TimerValue = Dcm_Dsl_stGeneral[0].u4FailSafeTimeout;
    Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_TXIFFSTIMER, u4_TimerValue);
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxIf_StopFsTimer                                 */
/* Description   | Stop fail-safe timer according to parallel transmission  */
/*               | status.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxIf_StopFsTimer
(void)
{
    uint8 u1_CurrentNumOfTransmissions;

    u1_CurrentNumOfTransmissions = Dcm_Dsl_Ctrl_GetNumOfConcurrentTxIf();
    if( u1_CurrentNumOfTransmissions == DCM_DSL_SINGLE_CLIENT )
    {
        Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_TXIFFSTIMER);
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxIf_GetTxPduID                                  */
/* Description   | Get a Transimit PduID.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] u1PeriodicIndex : Periodic Connection Index         */
/* Return Value  | PduIdType                                                */
/*               |       0U~PduIdmax             : Transimit PduID          */
/*               |       DCM_DSL_INVALID_U2_DATA : Undefined error          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(PduIdType, DCM_CODE) Dcm_Dsl_TxIf_GetPeriodicTxPduID
(
    const uint16 u2PduMapIndex,
    const uint8  u1PeriodicIndex
)
{
    PduIdType u2_Result;
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;
    P2CONST(AB_83_ConstV Dcm_Dsl_PeriodicTransmissionType, AUTOMATIC, DCM_APPL_CONST) pt_PeriodicTrans;

    u2_Result = DCM_DSL_INVALID_U2_DATA;
    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
    pt_PeriodicTrans = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptPeriodicConnectionRef;

    if( pt_PeriodicTrans != NULL_PTR )
    {
        u2_Result = pt_PeriodicTrans->ptPeriodicConnection[u1PeriodicIndex].TxPdu;
    }

    return  u2_Result;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxIf_GetPduMapIndexByTxConfPduID                 */
/* Description   | This function gets PduMapIndex from txConfirmationId.    */
/* Preconditions | none                                                     */
/* Parameters    | [in] uvTxConfPduId : Transimit Confirmation PduID        */
/* Return Value  | uint16                                                   */
/*               |       0x0000~0xFFFEU          : Valid value              */
/*               |       DCM_DSL_INVALID_U2_DATA : Invalid value            */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(uint16, DCM_CODE) Dcm_Dsl_TxIf_GetPduMapIndexByTxConfPduID
(
    const PduIdType uvTxConfPduId
)
{
    uint16 u2_IfMapIndex;
    uint16 u2_Result;
    uint16 u2_IfPduIdNum;

    u2_IfPduIdNum = Dcm_Dsl_u2IfPduIdNum;
    u2_Result     = DCM_DSL_INVALID_U2_DATA;

    /* Get PduMapIndex by TxConfPduId */
    for( u2_IfMapIndex = (uint16)0U; u2_IfMapIndex < u2_IfPduIdNum; u2_IfMapIndex++ )
    {
        if( Dcm_Dsl_IpduIdMapTable[u2_IfMapIndex].TxConfirmationPduId == uvTxConfPduId )
        {
            if( Dcm_Dsl_IpduIdMapTable[u2_IfMapIndex].u2PduMapIndex != DCM_DSL_INVALID_U2_DATA )
            {
                u2_Result = u2_IfMapIndex;
            }
            break;
        }
    }

    return u2_Result;
}
#endif /* DCM_DSL_PERIODICTX_ENABLE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
