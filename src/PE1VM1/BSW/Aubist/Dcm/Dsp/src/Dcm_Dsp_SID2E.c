/* Dcm_Dsp_SID2E_c(v5-0-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID2E/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID2E.h>
#if ( DCM_SUPPORT_SID2E == STD_ON )
#include <Dcm/Dcm_Dsp_DidMng.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_EvtDistr.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID2E_DIDLEN        ((uint8)0x02U)
#define DCM_DSP_SID2E_DIDSHIFT      ((uint8)8U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2E_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2E_CancelProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2E_IsDidAvailableProc
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2E_CheckSessionProc
(
    void
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2E_DidRangeDataLenProc
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2E_WriteDidDataProc
(
    const Dcm_OpStatusType u1OpStatus
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* data                                                                       */
/*----------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2E_u2RangeIndex;
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2E_u2DidInfo;

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_SID2E                                                */
/* Description   | SID2E request processing                                 */
/* Preconditions |                                                          */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID2E /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )           /* DCM_INITIAL */
    {
        u1_RetVal = Dcm_Dsp_SID2E_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )       /* DCM_CANCEL */
    {
        u1_RetVal = Dcm_Dsp_SID2E_CancelProc( &Dcm_Dsp_Main_stMsgContext );
    }
    else                                    /* DCM_PENDING */
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2E_IsDidAvailableCbk                          */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_IsDidAvailable                                       */
/* Preconditions |                                                          */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2E_IsDidAvailableCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId
)
{

    (void)Dcm_Dsp_SID2E_IsDidAvailableProc( DCM_PENDING ); /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2E_DidRangeDataLenCbk                         */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_ReadDidRangeDataLength                               */
/* Preconditions |                                                          */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2E_DidRangeDataLenCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId
)
{

    (void)Dcm_Dsp_SID2E_DidRangeDataLenProc( DCM_PENDING ); /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2E_WriteDidDataCbk                            */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_WriteDidData                                         */
/* Preconditions |                                                          */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2E_WriteDidDataCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId
)
{

    (void)Dcm_Dsp_SID2E_WriteDidDataProc( DCM_PENDING ); /* no return check required */

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2E_InitialProc                                */
/* Description   | Execute SID 2E request processing                        */
/* Preconditions |                                                          */
/*               | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2E_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType                  u1_RetVal;
    Dcm_Main_ReturnCheckType    u1_RetDidRange;
    uint8                           u1_ReadWriteSupport;

    u1_RetVal = E_OK;
    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE                                  */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= ( DCM_DSP_SID2E_DIDLEN + (uint8)1U ) )
    {
        Dcm_Dsp_SID2E_u2DidInfo = (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[0]) << DCM_DSP_SID2E_DIDSHIFT ) | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[1]);

        u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( Dcm_Dsp_SID2E_u2DidInfo, DCM_DSP_DIDMNG_DID_RANGE, &Dcm_Dsp_SID2E_u2RangeIndex, &u1_ReadWriteSupport );

        if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
        {
            if( ( u1_ReadWriteSupport & DCM_DSP_DIDMNG_WRITE_ONLY ) != (uint8)0U )
            {
                u1_RetVal = Dcm_Dsp_SID2E_IsDidAvailableProc( DCM_INITIAL );
            }
            else
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            }
        }
        else if( u1_RetDidRange == DCM_MAIN_E_CHECK_NOT_OK )
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2E_CancelProc                                 */
/* Description   | SID2E request cancel processing                          */
/* Preconditions |                                                          */
/*               | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2E_CancelProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    boolean                         b_UserNotifyFlag;
    Dcm_DidSupportedType            u1_Supported;
    uint16                          u2_DataLength;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    uint32                          u4_DataLength;

    u1_ErrorCode    = 0x00U;
    u2_DataLength   = (uint16)0U;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        ( void )Dcm_Dsp_DidMng_CallAvailableFnc( Dcm_Dsp_SID2E_u2RangeIndex, Dcm_Dsp_SID2E_u2DidInfo, DCM_CANCEL, &u1_Supported ); /* no return check required */

        ( void )Dcm_Dsp_DidMng_CallDataLengthFnc( Dcm_Dsp_SID2E_u2RangeIndex, Dcm_Dsp_SID2E_u2DidInfo, DCM_CANCEL, &u4_DataLength ); /* no return check required */

        ( void )Dcm_Dsp_DidMng_CallWriteDidFnc( Dcm_Dsp_SID2E_u2RangeIndex, Dcm_Dsp_SID2E_u2DidInfo, ptMsgContext->reqData, DCM_CANCEL, u2_DataLength, &u1_ErrorCode ); /* no return check required */

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        ( void )Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID2E_DIDAVAILABLE,    (boolean)FALSE ); /* no return check required */
        ( void )Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID2E_RANGE_DATA_LEN,  (boolean)FALSE ); /* no return check required */
        ( void )Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID2E_WRITE_DID_DATA,  (boolean)FALSE ); /* no return check required */
    }
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE                                   */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2E_IsDidAvailableProc                         */
/* Description   | Call the Xxx_IsDidAvailable                              */
/* Preconditions |                                                          */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID2E_IsDidAvailableProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType          u1_RetVal;
    Std_ReturnType          u1_RetAvailbleFnc;
    Std_ReturnType          u1_RetSupportedDid;
    Dcm_DidSupportedType    u1_Supported;

    u1_RetVal = E_OK;

    u1_RetAvailbleFnc = Dcm_Dsp_DidMng_CallAvailableFnc( Dcm_Dsp_SID2E_u2RangeIndex, Dcm_Dsp_SID2E_u2DidInfo, u1OpStatus, &u1_Supported );

    if( u1_RetAvailbleFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        if( u1_Supported == (Dcm_DidSupportedType)DCM_DID_SUPPORTED )
        {
            u1_RetSupportedDid = Dcm_Dsp_DidMng_CheckSupportedDid( Dcm_Dsp_SID2E_u2DidInfo, DCM_DID_REQTYPE_WRITE, Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
            if( u1_RetSupportedDid == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID2E_CheckSessionProc();
            }
            else
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            }
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    else if( u1_RetAvailbleFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2E_DIDAVAILABLE ); /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2E_CheckSessionProc                           */
/* Description   | Check Session by the reqest DID                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID2E_CheckSessionProc
(
    void
)
{
    Std_ReturnType    u1_RetVal;
    Std_ReturnType    u1_ReChkDidInfo;
    uint8    u1_SesLevel;

    u1_RetVal = E_OK;

    ( void )Dcm_GetSesCtrlType( &u1_SesLevel ); /* no return check required */

    u1_ReChkDidInfo = Dcm_Dsp_DidMng_ChkDidInfo( Dcm_Dsp_SID2E_u2RangeIndex, DCM_DSP_DIDMNG_DID_RANGE, DCM_DSP_DIDMNG_CHECK_WRITE_SES, u1_SesLevel );

    if( u1_ReChkDidInfo == (Std_ReturnType)E_OK )
    {
        u1_RetVal = Dcm_Dsp_SID2E_DidRangeDataLenProc( DCM_INITIAL );
    }
    else
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2E_DidRangeDataLenProc                        */
/* Description   | Call the Xxx_ReadDidRangeDataLength                      */
/* Preconditions |                                                          */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID2E_DidRangeDataLenProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType    u1_RetVal;
    Std_ReturnType    u1_RetDataLengthFnc;
    Std_ReturnType    u1_RetChkDidInfo;
    uint8    u1_SecLevel;
    uint32            u4_DataLength;

    u1_RetVal = E_OK;

    u1_RetDataLengthFnc = Dcm_Dsp_DidMng_CallDataLengthFnc( Dcm_Dsp_SID2E_u2RangeIndex, Dcm_Dsp_SID2E_u2DidInfo, u1OpStatus, &u4_DataLength );

    if( u1_RetDataLengthFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        if( u4_DataLength == ( Dcm_Dsp_Main_stMsgContext.reqDataLen - DCM_DSP_SID2E_DIDLEN ) )  /* no wrap around */
        {
            ( void )Dcm_GetSecurityLevel( &u1_SecLevel ); /* no return check required */

            u1_RetChkDidInfo = Dcm_Dsp_DidMng_ChkDidInfo( Dcm_Dsp_SID2E_u2RangeIndex, DCM_DSP_DIDMNG_DID_RANGE, DCM_DSP_DIDMNG_CHECK_WRITE_SEC, u1_SecLevel );

            if( u1_RetChkDidInfo == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID2E_WriteDidDataProc( DCM_INITIAL );
            }
            else
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_SECURITYACCESSDENIED );
            }
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
        }
    }
    else if( u1_RetDataLengthFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2E_RANGE_DATA_LEN ); /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2E_WriteDidDataProc                           */
/* Description   | Call the Xxx_WriteDidData                                */
/* Preconditions |                                                          */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID2E_WriteDidDataProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType    u1_RetVal;
    Std_ReturnType    u1_RetWriteDidFnc;
    Dcm_MsgType pt_WriteData;
    uint16    u2_WriteDataLen;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u1_RetVal = E_OK;
    pt_WriteData = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2E_DIDLEN];
    u2_WriteDataLen = (uint16)( Dcm_Dsp_Main_stMsgContext.reqDataLen - DCM_DSP_SID2E_DIDLEN );  /* no wrap around */

    u1_RetWriteDidFnc = Dcm_Dsp_DidMng_CallWriteDidFnc( Dcm_Dsp_SID2E_u2RangeIndex, Dcm_Dsp_SID2E_u2DidInfo, pt_WriteData, u1OpStatus, u2_WriteDataLen, &u1_ErrorCode );
    if( u1_RetWriteDidFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        if( Dcm_M_General.bVinRefNum == (uint8)0x01U )
        {
            if( Dcm_M_General.u2VinRef == Dcm_Dsp_SID2E_u2DidInfo )
            {
                Dcm_Main_SetVin( pt_WriteData );
            }
        }

        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= DCM_DSP_SID2E_DIDLEN )
        {
            Dcm_Dsp_Main_stMsgContext.resData[0] = Dcm_Dsp_Main_stMsgContext.reqData[0];
            Dcm_Dsp_Main_stMsgContext.resData[1] = Dcm_Dsp_Main_stMsgContext.reqData[1];

            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID2E_DIDLEN;

            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
        else
        {
            /* No process */
        }
    }
    else if( u1_RetWriteDidFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2E_WRITE_DID_DATA ); /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else if( u1_RetWriteDidFnc == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        if( u1_ErrorCode != (Dcm_NegativeResponseCodeType)0x00U )
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
        }
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID2E == STD_ON */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-08-20                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

