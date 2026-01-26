/* Dcm_Dsp_SID2F_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID2F/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID2F.h>
#if ( DCM_SUPPORT_SID2F == STD_ON )
#include <Dcm/Dcm_Dsp_DidMng.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define DCM_DSP_SID2F_DID_SHIFT         ((uint8)8U)
#define DCM_DSP_SID2F_VALUE_MAX_U4      ((uint32)0xFFFFFFFFU)
#define DCM_DSP_SID2F_INVLID_DATATYPE   ((uint8)0xFFU)
#define DCM_DSP_SID2F_MASK_BYTESHIFT    ((uint8)3U)
#define DCM_DSP_SID2F_MASK_BIT8         ((uint8)8U)
#define DCM_DSP_SID2F_MASK_BIT1         ((uint8)0x01U)
#define DCM_DSP_SID2F_MASK_BITMASK      ((uint8)0x07U)
#define DCM_DSP_SID2F_MASK_BITMASK_BOOL ((uint16)0x0007U)

#define DCM_DSP_SID2F_REQDATALEN_MIN    ((uint8)3U)
#define DCM_DSP_SID2F_REQDATA_DIDHIGH   ((uint8)0U)
#define DCM_DSP_SID2F_REQDATA_DIDLOW    ((uint8)1U)
#define DCM_DSP_SID2F_REQDATA_IOCP      ((uint8)2U)
#define DCM_DSP_SID2F_REQDATA_STATE     ((uint8)3U)

#define DCM_DSP_SID2F_RESDATALEN_MIN    ((uint8)3U)
#define DCM_DSP_SID2F_RESDATA_DIDHIGH   ((uint8)0U)
#define DCM_DSP_SID2F_RESDATA_DIDLOW    ((uint8)1U)
#define DCM_DSP_SID2F_RESDATA_IOCP      ((uint8)2U)
#define DCM_DSP_SID2F_RESDATA_STATE     ((uint8)3U)

#define DCM_DSP_SID2F_IOCP_RETCTRLECU   ((uint8)0x00U)
#define DCM_DSP_SID2F_IOCP_RSTDEFAULT   ((uint8)0x01U)
#define DCM_DSP_SID2F_IOCP_FREEZE       ((uint8)0x02U)
#define DCM_DSP_SID2F_IOCP_SHTTERMADJ   ((uint8)0x03U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_CancelProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_ChkIOCP
( void );
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_ControlRecord
( void );
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_ControlRecordBool
(
    void
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_SetResDataBool
(
    const uint16 u2CtrlStateLen
);
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_ControlRecordExternal
( void );
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_IOCP_Loop
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_IOCP_LoopBool
(
    const Dcm_OpStatusType u1OpStatus
);
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_IOCP_External
(
    const Dcm_OpStatusType u1OpStatus
);
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_Read_Loop
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_Read_LoopBool
(
    const Dcm_OpStatusType u1OpStatus
);
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_Read_External
(
    const Dcm_OpStatusType u1OpStatus
);
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
static FUNC( uint16, DCM_CODE ) Dcm_Dsp_SID2F_GetCtrlStateLenforResData
(
    const uint16 u2CtrlStateLen
);
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2F_u4CtrlMaskLen;
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2F_u2DidIndex;
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2F_u2CtrlStateLen;
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2F_u2CtrlMaskLen;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2F_u1NumOfData;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2F_u1LoopCnt;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2F_u1SignalType;
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2F_u1IOCP;

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
/* Function Name | Dcm_Dsp_SID2F                                            */
/* Description   | Request processing of SID 2F                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID2F /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID2F_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID2F_CancelProc( &Dcm_Dsp_Main_stMsgContext );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_IOControlCbk                               */
/* Description   | Callback function for event delivery registration of     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2F_IOControlCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId
)
{
    if( Dcm_Dsp_SID2F_u1SignalType == DCM_DSP_UINT8_N )
    {
        (void)Dcm_Dsp_SID2F_IOCP_Loop( DCM_PENDING ); /* no return check required */
    }
    else if( Dcm_Dsp_SID2F_u1SignalType == DCM_DSP_BOOLEAN )
    {
        (void)Dcm_Dsp_SID2F_IOCP_LoopBool( DCM_PENDING ); /* no return check required */
    }
    else
    {
        /* No process */
    }

    return;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2F_IOControlCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId
)
{
    (void)Dcm_Dsp_SID2F_IOCP_External( DCM_PENDING ); /* no return check required */

    return;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_ReadDataCbk                                */
/* Description   | Callback function for event delivery registration of     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2F_ReadDataCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId
)
{
    if( Dcm_Dsp_SID2F_u1SignalType == DCM_DSP_UINT8_N )
    {
        (void)Dcm_Dsp_SID2F_Read_Loop( DCM_PENDING ); /* no return check required */
    }
    else if( Dcm_Dsp_SID2F_u1SignalType == DCM_DSP_BOOLEAN )
    {
        (void)Dcm_Dsp_SID2F_Read_LoopBool( DCM_PENDING ); /* no return check required */
    }
    else
    {
        /* No process */
    }

    return;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2F_ReadDataCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId
)
{
    (void)Dcm_Dsp_SID2F_Read_External( DCM_PENDING ); /* no return check required */

    return;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_RetCtrl_ByChgSec                           */
/* Description   | Notify of security level change.                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SecLevelOld     : Security level before change    */
/*               | [IN] u1SecLevelNew     : Security level after change     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2F_RetCtrl_ByChgSec /* MISRA DEVIATION */
(
    const Dcm_SecLevelType u1SecLevelOld,
    const Dcm_SecLevelType u1SecLevelNew
)
{
    (void)Dcm_Dsp_SID2F_RetCtrlToECUBySec( u1SecLevelOld, u1SecLevelNew ); /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_RetCtrl_ByChgSes                           */
/* Description   | Notify of session state change.                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SesCtrlTypeOld     : Session before change        */
/*               | [IN] u1SesCtrlTypeNew     : Session after change         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2F_RetCtrl_ByChgSes /* MISRA DEVIATION */
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
)
{
    (void)Dcm_Dsp_SID2F_RetCtrlToECUBySes( u1SesCtrlTypeOld, u1SesCtrlTypeNew ); /* no return check required */

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_InitialProc                                */
/* Description   | Initial process of SID 2F request                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType              u1_RetVal;
    Std_ReturnType              u1_RetChkSes;
    Std_ReturnType              u1_RetSupportedDid;
    Dcm_Main_ReturnCheckType    u1_RetChkDid;
    Dcm_SesCtrlType             u1_SesCtrlType;
    uint16                      u2_Did;
    uint8                       u1_CRWSupport;

    u1_RetVal       = E_OK;
    u1_SesCtrlType  = DCM_DEFAULT_SESSION;
    u1_CRWSupport   = (uint8)0U;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE                                  */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    /* Check request message min length */
    if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID2F_REQDATALEN_MIN )
    {
        u2_Did = (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_DIDHIGH]) << DCM_DSP_SID2F_DID_SHIFT )
                        | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_DIDLOW]);

        /* Check DID support */
        u1_RetChkDid = Dcm_Dsp_DidMng_ChkDid( u2_Did,
                                              DCM_DSP_DIDMNG_DID,
                                              &Dcm_Dsp_SID2F_u2DidIndex,
                                              &u1_CRWSupport );

        if( u1_RetChkDid == DCM_MAIN_E_CHECK_OK )
        {
            if( ( u1_CRWSupport & DCM_DSP_DIDMNG_CONTROL_ONLY ) != (uint8)0U )
            {
                u1_RetSupportedDid = Dcm_Dsp_DidMng_CheckSupportedDid( u2_Did, DCM_DID_REQTYPE_CONTROL, Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
                if( u1_RetSupportedDid == (Std_ReturnType)E_OK )
                {
                    /* Get active session */
                    ( void )Dcm_GetSesCtrlType( &u1_SesCtrlType ); /* no return check required */

                    /* Check session support  */
                    u1_RetChkSes = Dcm_Dsp_DidMng_ChkDidInfo( Dcm_Dsp_SID2F_u2DidIndex, DCM_DSP_DIDMNG_DID, DCM_DSP_DIDMNG_CHECK_CTRL_SES, u1_SesCtrlType );
                    if( u1_RetChkSes == (Std_ReturnType)E_OK )
                    {
                        u1_RetVal = Dcm_Dsp_SID2F_ChkIOCP();
                    }
                    else
                    {
                        /* NRC 0x31 */
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                    }
                }
                else
                {
                    /* NRC 0x31 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                }
            }
            else
            {
                /* NRC 0x31 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            }
        }
        else if( u1_RetChkDid == DCM_MAIN_E_CHECK_NOT_OK )
        {
            /* NRC 0x31 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* NRC 0x13 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    }


    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_CancelProc                                 */
/* Description   | Cancel process of SID 2F request                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_CancelProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    boolean                         b_UserNotifyFlag;
    boolean                         b_ReportControlStateOnlyIOCP03;
    boolean                         b_ReportControlState;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    b_ReportControlStateOnlyIOCP03 = Dcm_Dsp_Sid2F_bReportControlStateOnlyIOCP03;
    b_ReportControlState = (boolean)FALSE;
    
    if( b_ReportControlStateOnlyIOCP03 == (boolean)TRUE )
    {
        if( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_SHTTERMADJ )
        {
            b_ReportControlState = (boolean)TRUE;
        }
    }
    else
    {
        b_ReportControlState = (boolean)TRUE;
    }
    
    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        switch( Dcm_Dsp_SID2F_u1IOCP )
        {
            case DCM_DSP_SID2F_IOCP_RETCTRLECU:
                break;
            case DCM_DSP_SID2F_IOCP_RSTDEFAULT:
                (void)Dcm_Dsp_DidMng_CallIOCP01Fnc( Dcm_Dsp_SID2F_u2DidIndex, Dcm_Dsp_SID2F_u1LoopCnt, DCM_CANCEL, &u1_ErrorCode ); /* no return check required */
                break;
            case DCM_DSP_SID2F_IOCP_FREEZE:
                (void)Dcm_Dsp_DidMng_CallIOCP02Fnc( Dcm_Dsp_SID2F_u2DidIndex, Dcm_Dsp_SID2F_u1LoopCnt, DCM_CANCEL, &u1_ErrorCode ); /* no return check required */
                break;
            case DCM_DSP_SID2F_IOCP_SHTTERMADJ:
                (void)Dcm_Dsp_DidMng_CallIOCP03Fnc( Dcm_Dsp_SID2F_u2DidIndex, Dcm_Dsp_SID2F_u1LoopCnt, &(ptMsgContext->reqData[DCM_DSP_SID2F_REQDATA_STATE]), DCM_CANCEL, &u1_ErrorCode ); /* no return check required */
                break;
            default:
                /* No process */
                break;
        }

        if( b_ReportControlState == (boolean)TRUE )
        {
            (void)Dcm_Dsp_DidMng_CallReadFnc( Dcm_Dsp_SID2F_u2DidIndex, Dcm_Dsp_SID2F_u1LoopCnt, DCM_CANCEL, &(ptMsgContext->resData[DCM_DSP_SID2F_RESDATA_STATE]), &u1_ErrorCode ); /* no return check required */
        }
    }

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID2F_IO_CONTROL, (boolean)FALSE ); /* no return check required */
    if( b_ReportControlState == (boolean)TRUE )
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID2F_READ_DATA, (boolean)FALSE ); /* no return check required */
    }
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE                                   */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_CancelProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint8                           u1_SignalIndex;
    boolean                         b_UserNotifyFlag;
    boolean                         b_ReportControlStateOnlyIOCP03;
    boolean                         b_ReportControlState;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ControlMaskInfo;
    
    /* External has only one signal */
    u1_SignalIndex      = (uint8)0U;
    b_ReportControlStateOnlyIOCP03 = Dcm_Dsp_Sid2F_bReportControlStateOnlyIOCP03;
    b_ReportControlState = (boolean)FALSE;
    u1_ErrorCode        = DCM_E_GENERALREJECT;

    if( b_ReportControlStateOnlyIOCP03 == (boolean)TRUE )
    {
        if( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_SHTTERMADJ )
        {
            b_ReportControlState = (boolean)TRUE;
        }
    }
    else
    {
        b_ReportControlState = (boolean)TRUE;
    }
    
    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        /* Check controlmask */
        if( Dcm_Dsp_SID2F_u4CtrlMaskLen != (uint32)0U )
        {
            pt_ControlMaskInfo = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_STATE + Dcm_Dsp_SID2F_u2CtrlStateLen];
        }
        else
        {
            pt_ControlMaskInfo = NULL_PTR;
        }
        
        switch( Dcm_Dsp_SID2F_u1IOCP )
        {
            case DCM_DSP_SID2F_IOCP_RETCTRLECU:
                break;
            case DCM_DSP_SID2F_IOCP_RSTDEFAULT:
                (void)Dcm_Dsp_DidMng_CallIOCP01Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_SignalIndex, DCM_CANCEL, pt_ControlMaskInfo, &u1_ErrorCode ); /* no return check required */
                break;
            case DCM_DSP_SID2F_IOCP_FREEZE:
                (void)Dcm_Dsp_DidMng_CallIOCP02Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_SignalIndex, DCM_CANCEL, pt_ControlMaskInfo, &u1_ErrorCode ); /* no return check required */
                break;
            case DCM_DSP_SID2F_IOCP_SHTTERMADJ:
                (void)Dcm_Dsp_DidMng_CallIOCP03Fnc( Dcm_Dsp_SID2F_u2DidIndex, 
                                                    u1_SignalIndex, 
                                                    &(ptMsgContext->reqData[DCM_DSP_SID2F_REQDATA_STATE]),
                                                    DCM_CANCEL, 
                                                    pt_ControlMaskInfo, 
                                                    &u1_ErrorCode ); /* no return check required */
                break;
            default:
                /* No process */
                break;
        }

        if( b_ReportControlState == (boolean)TRUE )
        {
            (void)Dcm_Dsp_DidMng_CallReadFnc( Dcm_Dsp_SID2F_u2DidIndex, u1_SignalIndex, DCM_CANCEL, &(ptMsgContext->resData[DCM_DSP_SID2F_RESDATA_STATE]), &u1_ErrorCode ); /* no return check required */
        }
    }

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID2F_IO_CONTROL, (boolean)FALSE ); /* no return check required */
    if( b_ReportControlState == (boolean)TRUE )
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID2F_READ_DATA, (boolean)FALSE ); /* no return check required */
    }
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_ChkIOCP                                    */
/* Description   | Check IOCP process of SID 2F request                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_ChkIOCP
( void )
{
    Std_ReturnType              u1_RetVal;
    Std_ReturnType              u1_RetChkIOCP;
    Std_ReturnType              u1_RetGetTopSigType;
    uint8                       u1_DataType;

    u1_RetVal       = E_OK;
    u1_DataType     = DCM_DSP_SID2F_INVLID_DATATYPE;
    
    Dcm_Dsp_SID2F_u1LoopCnt = (uint8)0U;

    Dcm_Dsp_SID2F_u1IOCP = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_IOCP];
    if( ( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_RETCTRLECU ) ||
        ( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_RSTDEFAULT ) ||
        ( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_FREEZE     ) ||
        ( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_SHTTERMADJ ) )
    {
        /* Check inputOutputControlParameter support  */
        u1_RetChkIOCP = Dcm_Dsp_DidMng_ChkIOCP( Dcm_Dsp_SID2F_u2DidIndex, Dcm_Dsp_SID2F_u1IOCP );
        if( u1_RetChkIOCP == (Std_ReturnType)E_OK )
        {
            u1_RetGetTopSigType = Dcm_Dsp_DidMng_GetTopSigType( Dcm_Dsp_SID2F_u2DidIndex, &u1_DataType );

            if( u1_RetGetTopSigType == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_SID2F_u1SignalType = u1_DataType;
                if( u1_DataType == DCM_DSP_UINT8_N )
                {
                    u1_RetVal = Dcm_Dsp_SID2F_ControlRecord();
                }
                else if( u1_DataType == DCM_DSP_BOOLEAN )
                {
                    u1_RetVal = Dcm_Dsp_SID2F_ControlRecordBool();
                }
                else
                {
                    /* No Process */
                }
            }
            else
            {
                /* No Process */
            }
        }
        else
        {
            /* NRC 0x31 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    else
    {
        /* NRC 0x31 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_ChkIOCP
( void )
{
    Std_ReturnType              u1_RetVal;
    Std_ReturnType              u1_RetChkIOCP;

    u1_RetVal       = E_OK;

    Dcm_Dsp_SID2F_u1IOCP = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_IOCP];
    if( ( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_RETCTRLECU ) ||
        ( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_RSTDEFAULT ) ||
        ( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_FREEZE     ) ||
        ( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_SHTTERMADJ ) )
    {
        /* Check inputOutputControlParameter support  */
        u1_RetChkIOCP = Dcm_Dsp_DidMng_ChkIOCP( Dcm_Dsp_SID2F_u2DidIndex, Dcm_Dsp_SID2F_u1IOCP );
        if( u1_RetChkIOCP == (Std_ReturnType)E_OK )
        {
            u1_RetVal = Dcm_Dsp_SID2F_ControlRecordExternal();
        }
        else
        {
            /* NRC 0x31 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    else
    {
        /* NRC 0x31 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */

#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_ControlRecord                              */
/* Description   | ControlRecord process of SID 2F request                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_ControlRecord
( void )
{
    Std_ReturnType      u1_RetVal;
    Std_ReturnType      u1_RetChkSec;
    Std_ReturnType      u1_RetChkCtrlParam;
    Std_ReturnType      u1_RetGetCtrlParamLen;
    Dcm_SecLevelType    u1_SecLevel;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ControlStateInfo;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ControlMaskInfo;
    uint16              u2_CtrlStateLen;
    uint16              u2_CtrlStateLenforResData;

    u1_RetVal   = E_OK;
    u1_SecLevel = DCM_SEC_LEV_LOCKED;
    u2_CtrlStateLen = (uint16)0U;

    u1_RetGetCtrlParamLen = Dcm_Dsp_DidMng_GetCtrlParamLen( Dcm_Dsp_SID2F_u2DidIndex,
                                    &u2_CtrlStateLen,
                                    &Dcm_Dsp_SID2F_u1NumOfData  );

    if( u1_RetGetCtrlParamLen == (Std_ReturnType)E_OK )
    {
        if( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_SHTTERMADJ )
        {
            Dcm_Dsp_SID2F_u2CtrlStateLen = u2_CtrlStateLen;
        }
        else
        {
            Dcm_Dsp_SID2F_u2CtrlStateLen = (uint16)0U;
        }

        if( Dcm_Dsp_SID2F_u1NumOfData > (uint8)1U )
        {
            Dcm_Dsp_SID2F_u2CtrlMaskLen = (uint16)( ( (uint16)Dcm_Dsp_SID2F_u1NumOfData + ( DCM_DSP_SID2F_MASK_BIT8 - (uint8)1U ) ) >> DCM_DSP_SID2F_MASK_BYTESHIFT );
        }
        else
        {
            Dcm_Dsp_SID2F_u2CtrlMaskLen = (uint16)0U;
        }

        /* Check request message length */
        if( Dcm_Dsp_Main_stMsgContext.reqDataLen == ( (uint32)Dcm_Dsp_SID2F_u2CtrlStateLen + Dcm_Dsp_SID2F_u2CtrlMaskLen + DCM_DSP_SID2F_REQDATALEN_MIN ) ) /* no wrap around */
        {
            if( Dcm_Dsp_SID2F_u2CtrlStateLen == (uint16)0U )
            {
                pt_ControlStateInfo = NULL_PTR;
            }
            else
            {
                pt_ControlStateInfo = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_STATE];
            }

            if( Dcm_Dsp_SID2F_u2CtrlMaskLen == (uint16)0U )
            {
                pt_ControlMaskInfo = NULL_PTR;
            }
            else
            {
                pt_ControlMaskInfo = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_STATE + Dcm_Dsp_SID2F_u2CtrlStateLen];
            }

            /* Check controlstate and controlmask parameter */
            u1_RetChkCtrlParam = Dcm_Dsp_DidMng_ChkCtrlParam( Dcm_Dsp_SID2F_u2DidIndex, pt_ControlStateInfo, pt_ControlMaskInfo );
            if( u1_RetChkCtrlParam == (Std_ReturnType)E_OK )
            {
                /* Get active security level */
                ( void )Dcm_GetSecurityLevel( &u1_SecLevel ); /* no return check required */

                /* Check security level support */
                u1_RetChkSec = Dcm_Dsp_DidMng_ChkDidInfo( Dcm_Dsp_SID2F_u2DidIndex, DCM_DSP_DIDMNG_DID, DCM_DSP_DIDMNG_CHECK_CTRL_SEC, u1_SecLevel );
                if( u1_RetChkSec == (Std_ReturnType)E_OK )
                {
                    u2_CtrlStateLenforResData = Dcm_Dsp_SID2F_GetCtrlStateLenforResData(u2_CtrlStateLen);

                    /* Check response message length */
                    if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= ( (uint32)u2_CtrlStateLenforResData + DCM_DSP_SID2F_RESDATALEN_MIN ) ) /* no wrap around */
                    {
                        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_DIDHIGH] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_DIDHIGH];
                        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_DIDLOW ] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_DIDLOW ];
                        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_IOCP   ] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_IOCP   ];
                        Dcm_Dsp_Main_stMsgContext.resDataLen = (uint32)u2_CtrlStateLenforResData + DCM_DSP_SID2F_RESDATALEN_MIN;  /* no wrap around */

                        u1_RetVal = Dcm_Dsp_SID2F_IOCP_Loop( DCM_INITIAL );
                    }
                    else
                    {
                        /* No process */
                    }
                }
                else
                {
                    /* NRC 0x33 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_SECURITYACCESSDENIED );
                }
            }
            else
            {
                /* NRC 0x31 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            }
        }
        else
        {
            /* NRC 0x13 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_ControlRecordBool                          */
/* Description   | ControlRecord process of SID2F request with Bool Data    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_ControlRecordBool
( void )
{
    Std_ReturnType      u1_RetVal;
    Std_ReturnType      u1_RetChkSec;
    Std_ReturnType      u1_RetChkCtrlParam;
    Std_ReturnType      u1_RetGetAnySigPos;
    Std_ReturnType      u1_RetGetSigNum;
    Dcm_SecLevelType    u1_SecLevel;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ControlStateInfo;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ControlMaskInfo;
    uint8               u1_NumOfSignal;
    uint8               u1_LastSignalIndex;
    uint16              u2_SignalPos;
    uint16              u2_CtrlStateLen;
    uint16              u2_CtrlStateLenforResData;

    u1_RetVal   = E_OK;
    u1_SecLevel = DCM_SEC_LEV_LOCKED;
    u1_NumOfSignal = (uint8)0U;
    u2_SignalPos = (uint16)0U;

    u1_RetGetSigNum = Dcm_Dsp_DidMng_GetSigNum( Dcm_Dsp_SID2F_u2DidIndex, &u1_NumOfSignal );

    if( u1_RetGetSigNum == (Std_ReturnType)E_OK )
    {
        if( u1_NumOfSignal > (uint8)0U )
        {
            Dcm_Dsp_SID2F_u1NumOfData = u1_NumOfSignal;
            u1_LastSignalIndex = u1_NumOfSignal - (uint8)1U;

            u1_RetGetAnySigPos = Dcm_Dsp_DidMng_GetAnySigPos( Dcm_Dsp_SID2F_u2DidIndex, u1_LastSignalIndex, &u2_SignalPos );

            if( u1_RetGetAnySigPos == (Std_ReturnType)E_OK )
            {
                u2_CtrlStateLen = (uint16)( u2_SignalPos >> DCM_DSP_SID2F_MASK_BYTESHIFT ) + (uint8)1U;

                if( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_SHTTERMADJ )
                {
                    Dcm_Dsp_SID2F_u2CtrlStateLen = u2_CtrlStateLen;
                }
                else
                {
                    Dcm_Dsp_SID2F_u2CtrlStateLen = (uint16)0U;
                }

                if( u1_NumOfSignal > (uint8)1U )
                {
                    Dcm_Dsp_SID2F_u2CtrlMaskLen = (uint16)( u2_SignalPos >> DCM_DSP_SID2F_MASK_BYTESHIFT ) + (uint8)1U;
                }
                else
                {
                    Dcm_Dsp_SID2F_u2CtrlMaskLen = (uint16)0U;
                }

                /* Check request message length */
                if( Dcm_Dsp_Main_stMsgContext.reqDataLen == ( (uint32)Dcm_Dsp_SID2F_u2CtrlStateLen + Dcm_Dsp_SID2F_u2CtrlMaskLen + DCM_DSP_SID2F_REQDATALEN_MIN ) ) /* no wrap around */
                {
                    if( Dcm_Dsp_SID2F_u2CtrlStateLen == (uint16)0U )
                    {
                        pt_ControlStateInfo = NULL_PTR;
                    }
                    else
                    {
                        pt_ControlStateInfo = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_STATE];
                    }

                    if( Dcm_Dsp_SID2F_u2CtrlMaskLen == (uint16)0U )
                    {
                        pt_ControlMaskInfo = NULL_PTR;
                    }
                    else
                    {
                        pt_ControlMaskInfo = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_STATE + Dcm_Dsp_SID2F_u2CtrlStateLen];
                    }

                    /* Check controlstate and controlmask parameter */
                    u1_RetChkCtrlParam = Dcm_Dsp_DidMng_ChkCtrlParam( Dcm_Dsp_SID2F_u2DidIndex, pt_ControlStateInfo, pt_ControlMaskInfo );
                    if( u1_RetChkCtrlParam == (Std_ReturnType)E_OK )
                    {
                        /* Get active security level */
                        ( void )Dcm_GetSecurityLevel( &u1_SecLevel ); /* no return check required */

                        /* Check security level support */
                        u1_RetChkSec = Dcm_Dsp_DidMng_ChkDidInfo( Dcm_Dsp_SID2F_u2DidIndex, DCM_DSP_DIDMNG_DID, DCM_DSP_DIDMNG_CHECK_CTRL_SEC, u1_SecLevel );
                        if( u1_RetChkSec == (Std_ReturnType)E_OK )
                        {
                            u2_CtrlStateLenforResData = Dcm_Dsp_SID2F_GetCtrlStateLenforResData(u2_CtrlStateLen);
                            u1_RetVal = Dcm_Dsp_SID2F_SetResDataBool( u2_CtrlStateLenforResData );
                        }
                        else
                        {
                            /* NRC 0x33 */
                            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_SECURITYACCESSDENIED );
                        }
                    }
                    else
                    {
                        /* NRC 0x31 */
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                    }
                }
                else
                {
                    /* NRC 0x13 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
                }
            }
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_SetResDataBool                             */
/* Description   | Set Res Data process of SID2F request with Bool Data     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2CtrlStateLen : res ControlState length            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_SetResDataBool
(
    const uint16 u2CtrlStateLen
)
{
    Std_ReturnType      u1_RetVal;
    uint16              u2_LoopCnt;

    u1_RetVal = E_OK;

    /* Check response message length */
    if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= ( (uint32)u2CtrlStateLen + DCM_DSP_SID2F_RESDATALEN_MIN ) )  /* no wrap around */
    {
        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_DIDHIGH] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_DIDHIGH];
        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_DIDLOW ] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_DIDLOW ];
        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_IOCP   ] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_IOCP   ];

        for( u2_LoopCnt = (uint16)0U; u2_LoopCnt < u2CtrlStateLen; u2_LoopCnt++ )
        {
            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_STATE + u2_LoopCnt] = (uint8)0x00U;
        }

        Dcm_Dsp_Main_stMsgContext.resDataLen = (uint32)u2CtrlStateLen + DCM_DSP_SID2F_RESDATALEN_MIN;   /* no wrap around */

        u1_RetVal = Dcm_Dsp_SID2F_IOCP_LoopBool( DCM_INITIAL );
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */

#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_ControlRecordExternal                      */
/* Description   | ControlRecord process of SID 2F request                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_ControlRecordExternal
( void )
{
    Std_ReturnType      u1_RetVal;
    Std_ReturnType      u1_RetChkSec;
    Std_ReturnType      u1_RetChkCtrlParam;
    Std_ReturnType      u1_RetGetCtrlParamLen;
    Dcm_SecLevelType    u1_SecLevel;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ControlStateInfo;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ControlMaskInfo;
    uint32              u4_CtrlMaskLen;
    uint16              u2_CtrlStateLen;
    uint16              u2_CtrlStateLenforResData;

    u1_RetVal   = E_OK;
    u1_SecLevel = DCM_SEC_LEV_LOCKED;
    u2_CtrlStateLen = (uint16)0U;

    u1_RetGetCtrlParamLen = Dcm_Dsp_DidMng_GetCtrlParamLenExternal( Dcm_Dsp_SID2F_u2DidIndex,
                                                                    &u2_CtrlStateLen,
                                                                    &u4_CtrlMaskLen );

    if( u1_RetGetCtrlParamLen == (Std_ReturnType)E_OK )
    {
        if( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_SHTTERMADJ )
        {
            Dcm_Dsp_SID2F_u2CtrlStateLen = u2_CtrlStateLen;
        }
        else
        {
            Dcm_Dsp_SID2F_u2CtrlStateLen = (uint16)0U;
        }
        Dcm_Dsp_SID2F_u4CtrlMaskLen = u4_CtrlMaskLen;


        /* Check request message length */
        
        if( ( (uint32)Dcm_Dsp_SID2F_u2CtrlStateLen + DCM_DSP_SID2F_REQDATALEN_MIN ) < ( DCM_DSP_SID2F_VALUE_MAX_U4 - Dcm_Dsp_SID2F_u4CtrlMaskLen ) ) /* no wrap around */
        {
            if( Dcm_Dsp_Main_stMsgContext.reqDataLen == ( (uint32)Dcm_Dsp_SID2F_u2CtrlStateLen + Dcm_Dsp_SID2F_u4CtrlMaskLen + DCM_DSP_SID2F_REQDATALEN_MIN ) ) /* no wrap around */
            {
                if( Dcm_Dsp_SID2F_u2CtrlStateLen == (uint16)0U )
                {
                    pt_ControlStateInfo = NULL_PTR;
                }
                else
                {
                    pt_ControlStateInfo = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_STATE];
                }

                if( Dcm_Dsp_SID2F_u4CtrlMaskLen == (uint32)0U )
                {
                    pt_ControlMaskInfo = NULL_PTR;
                }
                else
                {
                    pt_ControlMaskInfo = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_STATE + Dcm_Dsp_SID2F_u2CtrlStateLen];
                }

                /* Check controlstate and controlmask parameter */
                u1_RetChkCtrlParam = Dcm_Dsp_DidMng_ChkCtrlParam( Dcm_Dsp_SID2F_u2DidIndex, pt_ControlStateInfo, pt_ControlMaskInfo );
                if( u1_RetChkCtrlParam == (Std_ReturnType)E_OK )
                {
                    /* Get active security level */
                    ( void )Dcm_GetSecurityLevel( &u1_SecLevel ); /* no return check required */

                    /* Check security level support */
                    u1_RetChkSec = Dcm_Dsp_DidMng_ChkDidInfo( Dcm_Dsp_SID2F_u2DidIndex, DCM_DSP_DIDMNG_DID, DCM_DSP_DIDMNG_CHECK_CTRL_SEC, u1_SecLevel );
                    if( u1_RetChkSec == (Std_ReturnType)E_OK )
                    {
                        u2_CtrlStateLenforResData = Dcm_Dsp_SID2F_GetCtrlStateLenforResData(u2_CtrlStateLen);

                        /* Check response message length */
                        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= ( (uint32)u2_CtrlStateLenforResData + DCM_DSP_SID2F_RESDATALEN_MIN ) ) /* no wrap around */
                        {
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_DIDHIGH] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_DIDHIGH];
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_DIDLOW ] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_DIDLOW ];
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_IOCP   ] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_IOCP   ];
                            Dcm_Dsp_Main_stMsgContext.resDataLen = (uint32)u2_CtrlStateLenforResData + DCM_DSP_SID2F_RESDATALEN_MIN;  /* no wrap around */

                            u1_RetVal = Dcm_Dsp_SID2F_IOCP_External( DCM_INITIAL );
                        }
                    }
                    else
                    {
                        /* NRC 0x33 */
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_SECURITYACCESSDENIED );
                    }
                }
                else
                {
                    /* NRC 0x31 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                }
            }
            else
            {
                /* NRC 0x13 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
            }
        }
        else
        {
             /* NRC 0x13 */
             Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */

#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_IOCP_Loop                                  */
/* Description   | IO control loop processing                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_IOCP_Loop
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetIOCPFnc;
    uint8                           u1_LoopCnt;
    uint8                           u1_CtrlMask;
    uint8                           u1_CtrlMaskBit;
    boolean                         b_BreakFlag;
    boolean                         b_ChkMaskFlag;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    Dcm_OpStatusType                u1_OpStatusTmp;

    u1_RetVal           = E_OK;
    u1_RetIOCPFnc       = E_NOT_OK;
    u1_ErrorCode        = (Dcm_NegativeResponseCodeType)0x00U;
    b_BreakFlag         = (boolean)FALSE;
    u1_OpStatusTmp      = u1OpStatus;

    for( u1_LoopCnt = Dcm_Dsp_SID2F_u1LoopCnt; u1_LoopCnt < Dcm_Dsp_SID2F_u1NumOfData; u1_LoopCnt++ )
    {
        b_ChkMaskFlag = (boolean)FALSE;
        b_BreakFlag   = (boolean)FALSE;

        /* Check controlmask */
        if( Dcm_Dsp_SID2F_u2CtrlMaskLen > (uint16)0U )
        {
            u1_CtrlMask = Dcm_Dsp_Main_stMsgContext.reqData[( Dcm_Dsp_SID2F_u2CtrlStateLen + (uint8)( u1_LoopCnt >> DCM_DSP_SID2F_MASK_BYTESHIFT ) ) + DCM_DSP_SID2F_REQDATA_STATE];
            u1_CtrlMaskBit = (uint8)( DCM_DSP_SID2F_MASK_BIT1 << ( ( DCM_DSP_SID2F_MASK_BIT8 - ( u1_LoopCnt & DCM_DSP_SID2F_MASK_BITMASK ) ) - (uint8)1U ) );

            if( ( u1_CtrlMask & u1_CtrlMaskBit ) != (uint8)0U )
            {
                b_ChkMaskFlag = (boolean)TRUE;
            }
        }
        else
        {
            b_ChkMaskFlag = (boolean)TRUE;
        }

        if( b_ChkMaskFlag == (boolean)TRUE )
        {
            switch( Dcm_Dsp_SID2F_u1IOCP )
            {
                case DCM_DSP_SID2F_IOCP_RETCTRLECU:
                    u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP00Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, &u1_ErrorCode );
                    break;
                case DCM_DSP_SID2F_IOCP_RSTDEFAULT:
                    u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP01Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, u1_OpStatusTmp, &u1_ErrorCode );
                    break;
                case DCM_DSP_SID2F_IOCP_FREEZE:
                    u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP02Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, u1_OpStatusTmp, &u1_ErrorCode );
                    break;
                case DCM_DSP_SID2F_IOCP_SHTTERMADJ:
                    u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP03Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, &(Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_STATE]), u1_OpStatusTmp, &u1_ErrorCode );
                    break;
                default:
                    /* No process */
                    break;
            }

            if( u1_RetIOCPFnc == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            }
            else if( u1_RetIOCPFnc == (Std_ReturnType)E_NOT_OK )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                b_BreakFlag = (boolean)TRUE;

                if( u1_ErrorCode != (Dcm_NegativeResponseCodeType)0x00U )
                {
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
                }
            }
            else if( u1_RetIOCPFnc == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                b_BreakFlag = (boolean)TRUE;

                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2F_IO_CONTROL ); /* no return check required */

                u1_RetVal = DCM_E_PENDING;
            }
            else
            {
                /* No process */
            }
        }

        if( b_BreakFlag == (boolean)TRUE )
        {
            Dcm_Dsp_SID2F_u1LoopCnt = u1_LoopCnt;
            break;
        }
        else
        {
            u1_OpStatusTmp = DCM_INITIAL;
        }
    }

    if( b_BreakFlag == (boolean)FALSE )
    {
        Dcm_Dsp_SID2F_u1LoopCnt = (uint8)0U;
        u1_RetVal = Dcm_Dsp_SID2F_Read_Loop( DCM_INITIAL );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_IOCP_LoopBool                              */
/* Description   | IO control loop processing by Bool Data                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_IOCP_LoopBool
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetIOCPFnc;
    Std_ReturnType                  u1_RetGetAnySigPos;
    uint8                           u1_LoopCnt;
    uint8                           u1_CtrlMask;
    uint8                           u1_CtrlMaskBit;
    uint8                           u1_CtrlState;
    uint8                           u1_CtrlStateBit;
    uint8                           u1_BoolReqData;
    uint16                          u2_Pos;
    boolean                         b_BreakFlag;
    boolean                         b_ChkMaskFlag;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    Dcm_OpStatusType                u1_OpStatusTmp;

    u1_RetVal           = E_OK;
    u1_OpStatusTmp      = u1OpStatus;
    u1_RetIOCPFnc       = E_NOT_OK;
    u1_ErrorCode        = (Dcm_NegativeResponseCodeType)0x00U;
    b_BreakFlag         = (boolean)FALSE;

    for( u1_LoopCnt = Dcm_Dsp_SID2F_u1LoopCnt; u1_LoopCnt < Dcm_Dsp_SID2F_u1NumOfData; u1_LoopCnt++ )
    {
        b_ChkMaskFlag = (boolean)FALSE;
        b_BreakFlag = (boolean)FALSE;

        u1_RetGetAnySigPos = Dcm_Dsp_DidMng_GetAnySigPos( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, &u2_Pos );

        if( u1_RetGetAnySigPos == (Std_ReturnType)E_OK )
        {
            if( Dcm_Dsp_SID2F_u2CtrlMaskLen > (uint16)0U )
            {
                u1_CtrlMask = Dcm_Dsp_Main_stMsgContext.reqData[( Dcm_Dsp_SID2F_u2CtrlStateLen + ( u2_Pos >> DCM_DSP_SID2F_MASK_BYTESHIFT ) ) + DCM_DSP_SID2F_REQDATA_STATE];
                u1_CtrlMaskBit = (uint8)( DCM_DSP_SID2F_MASK_BIT1 << ( ( DCM_DSP_SID2F_MASK_BIT8 - ( u2_Pos & DCM_DSP_SID2F_MASK_BITMASK_BOOL ) ) - (uint8)1U ) );
                if( ( u1_CtrlMask & u1_CtrlMaskBit ) != (uint8)0U )
                {
                    b_ChkMaskFlag = (boolean)TRUE;
                }
            }
            else
            {
                b_ChkMaskFlag = (boolean)TRUE;
            }

            if( b_ChkMaskFlag == (boolean)TRUE )
            {
                switch( Dcm_Dsp_SID2F_u1IOCP )
                {
                    case DCM_DSP_SID2F_IOCP_RETCTRLECU:
                        u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP00Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, &u1_ErrorCode );
                        break;
                    case DCM_DSP_SID2F_IOCP_RSTDEFAULT:
                        u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP01Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, u1_OpStatusTmp, &u1_ErrorCode );
                        break;
                    case DCM_DSP_SID2F_IOCP_FREEZE:
                        u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP02Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, u1_OpStatusTmp, &u1_ErrorCode );
                        break;
                    case DCM_DSP_SID2F_IOCP_SHTTERMADJ:

                        u1_CtrlState = Dcm_Dsp_Main_stMsgContext.reqData[( u2_Pos >> DCM_DSP_SID2F_MASK_BYTESHIFT ) + DCM_DSP_SID2F_REQDATA_STATE];
                        u1_CtrlStateBit = (uint8)( DCM_DSP_SID2F_MASK_BIT1 << ( ( DCM_DSP_SID2F_MASK_BIT8 - ( u2_Pos & DCM_DSP_SID2F_MASK_BITMASK_BOOL ) ) - (uint8)1U ) );

                        if( ( u1_CtrlState & u1_CtrlStateBit ) != (uint8)0U )
                        {
                            u1_BoolReqData = (uint8)0x01U;
                        }
                        else
                        {
                            u1_BoolReqData = (uint8)0x00U;
                        }

                        u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP03Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, &u1_BoolReqData, u1_OpStatusTmp, &u1_ErrorCode );
                        break;
                    default:
                        /* No process */
                        break;
                }

                if( u1_RetIOCPFnc == (Std_ReturnType)E_OK )
                {
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                }
                else if( u1_RetIOCPFnc == (Std_ReturnType)E_NOT_OK )
                {
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                    b_BreakFlag = (boolean)TRUE;

                    if( u1_ErrorCode != (Dcm_NegativeResponseCodeType)0x00U )
                    {
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
                    }
                }
                else if( u1_RetIOCPFnc == (Std_ReturnType)DCM_E_PENDING )
                {
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                    b_BreakFlag = (boolean)TRUE;

                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2F_IO_CONTROL ); /* no return check required */

                    u1_RetVal = DCM_E_PENDING;
                }
                else
                {
                    /* No process */
                }
            }
        }
        else
        {
            b_BreakFlag = (boolean)TRUE;
        }

        if( b_BreakFlag == (boolean)TRUE )
        {
            Dcm_Dsp_SID2F_u1LoopCnt = u1_LoopCnt;
            break;
        }
        else
        {
            u1_OpStatusTmp = DCM_INITIAL;
        }
    }

    if( b_BreakFlag == (boolean)FALSE )
    {
        Dcm_Dsp_SID2F_u1LoopCnt = (uint8)0U;
        u1_RetVal = Dcm_Dsp_SID2F_Read_LoopBool( DCM_INITIAL );
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */

#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_IOCP_External                              */
/* Description   | IO control loop processing                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_IOCP_External
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetIOCPFnc;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    uint8                           u1_SignalIndex;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ControlMaskInfo;

    u1_RetVal           = E_OK;
    u1_RetIOCPFnc       = E_NOT_OK;
    u1_ErrorCode        = DCM_E_GENERALREJECT;
    /* External has only one signal */
    u1_SignalIndex      = (uint8)0U;

    /* Check controlmask */
    if( Dcm_Dsp_SID2F_u4CtrlMaskLen != (uint32)0U )
    {
        pt_ControlMaskInfo = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_STATE + Dcm_Dsp_SID2F_u2CtrlStateLen];
    }
    else
    {
        pt_ControlMaskInfo = NULL_PTR;
    }

    switch( Dcm_Dsp_SID2F_u1IOCP )
    {
        case DCM_DSP_SID2F_IOCP_RETCTRLECU:
            u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP00Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_SignalIndex, pt_ControlMaskInfo, &u1_ErrorCode );
            break;
        case DCM_DSP_SID2F_IOCP_RSTDEFAULT:
            u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP01Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_SignalIndex, u1OpStatus, pt_ControlMaskInfo, &u1_ErrorCode );
            break;
        case DCM_DSP_SID2F_IOCP_FREEZE:
            u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP02Fnc( Dcm_Dsp_SID2F_u2DidIndex, u1_SignalIndex, u1OpStatus, pt_ControlMaskInfo, &u1_ErrorCode );
            break;
        case DCM_DSP_SID2F_IOCP_SHTTERMADJ:
            u1_RetIOCPFnc = Dcm_Dsp_DidMng_CallIOCP03Fnc( Dcm_Dsp_SID2F_u2DidIndex, 
                                                          u1_SignalIndex, 
                                                          &(Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2F_REQDATA_STATE]),
                                                          u1OpStatus, 
                                                          pt_ControlMaskInfo, 
                                                          &u1_ErrorCode );
            break;
        default:
            /* No process */
            break;
    }

    if( u1_RetIOCPFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        u1_RetVal = Dcm_Dsp_SID2F_Read_External( DCM_INITIAL );
    }
    else if( u1_RetIOCPFnc == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
    }
    else if( u1_RetIOCPFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2F_IO_CONTROL ); /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */

#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_Read_Loop                                  */
/* Description   | Read loop processing                                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_Read_Loop
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetReadFnc;
    uint8                           u1_LoopCnt;
    boolean                         b_BreakFlag;
    boolean                         b_ReportControlStateOnlyIOCP03;
    boolean                         b_ReportControlState;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    Dcm_OpStatusType                u1_OpStatusTmp;

    u1_RetVal           = E_OK;
    u1_OpStatusTmp      = u1OpStatus;
    u1_ErrorCode        = (Dcm_NegativeResponseCodeType)0x00U;
    b_BreakFlag         = (boolean)FALSE;
    b_ReportControlStateOnlyIOCP03 = Dcm_Dsp_Sid2F_bReportControlStateOnlyIOCP03;
    b_ReportControlState = (boolean)FALSE;

    if( b_ReportControlStateOnlyIOCP03 == (boolean)TRUE )
    {
        if( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_SHTTERMADJ )
        {
            b_ReportControlState = (boolean)TRUE;
        }
    }
    else
    {
        b_ReportControlState = (boolean)TRUE;
    }

    if( b_ReportControlState == (boolean)TRUE )
    {
        for( u1_LoopCnt = Dcm_Dsp_SID2F_u1LoopCnt; u1_LoopCnt < Dcm_Dsp_SID2F_u1NumOfData; u1_LoopCnt++ )
        {
            b_BreakFlag = (boolean)FALSE;

            u1_RetReadFnc = Dcm_Dsp_DidMng_CallReadFnc( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, u1_OpStatusTmp, &(Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_STATE]), &u1_ErrorCode );

            if( u1_RetReadFnc == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            }
            else if( u1_RetReadFnc == (Std_ReturnType)E_NOT_OK )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                b_BreakFlag = (boolean)TRUE;

                if( u1_ErrorCode != (Dcm_NegativeResponseCodeType)0x00U )
                {
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
                }
            }
            else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                b_BreakFlag = (boolean)TRUE;

                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2F_READ_DATA ); /* no return check required */

                u1_RetVal = DCM_E_PENDING;
            }
            else
            {
                /* No process */
            }

            if( b_BreakFlag == (boolean)TRUE )
            {
                Dcm_Dsp_SID2F_u1LoopCnt = u1_LoopCnt;
                break;
            }
            else
            {
                u1_OpStatusTmp = DCM_INITIAL;
            }
        }
    }

    if( b_BreakFlag == (boolean)FALSE )
    {
        /* Positive response */
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }

    return  u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_Read_LoopBool                              */
/* Description   | Read loop processing by Bool Data                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_Read_LoopBool
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetReadFnc;
    Std_ReturnType                  u1_RetGetAnySigPos;
    uint8                           u1_LoopCnt;
    uint8                           u1_BoolResData;
    uint8                           u1_ResControlState;
    uint16                          u2_Pos;
    boolean                         b_BreakFlag;
    boolean                         b_ReportControlStateOnlyIOCP03;
    boolean                         b_ReportControlState;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    Dcm_OpStatusType                u1_OpStatusTmp;

    u1_RetVal           = E_OK;
    u1_OpStatusTmp      = u1OpStatus;
    u1_ErrorCode        = (Dcm_NegativeResponseCodeType)0x00U;
    b_BreakFlag         = (boolean)FALSE;
    b_ReportControlStateOnlyIOCP03 = Dcm_Dsp_Sid2F_bReportControlStateOnlyIOCP03;
    b_ReportControlState = (boolean)FALSE;

    if( b_ReportControlStateOnlyIOCP03 == (boolean)TRUE )
    {
        if( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_SHTTERMADJ )
        {
            b_ReportControlState = (boolean)TRUE;
        }
    }
    else
    {
        b_ReportControlState = (boolean)TRUE;
    }

    if( b_ReportControlState == (boolean)TRUE )
    {
        for( u1_LoopCnt = Dcm_Dsp_SID2F_u1LoopCnt; u1_LoopCnt < Dcm_Dsp_SID2F_u1NumOfData; u1_LoopCnt++ )
        {
            b_BreakFlag = (boolean)FALSE;

            u1_RetReadFnc = Dcm_Dsp_DidMng_CallReadFnc( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, u1_OpStatusTmp, &u1_BoolResData, &u1_ErrorCode );

            if( u1_RetReadFnc == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

                u1_RetGetAnySigPos = Dcm_Dsp_DidMng_GetAnySigPos( Dcm_Dsp_SID2F_u2DidIndex, u1_LoopCnt, &u2_Pos );

                if( u1_RetGetAnySigPos == (Std_ReturnType)E_OK )
                {
                    u1_ResControlState = (uint8)( u1_BoolResData << ( ( DCM_DSP_SID2F_MASK_BIT8 - ( u2_Pos & DCM_DSP_SID2F_MASK_BITMASK_BOOL ) ) - (uint8)1U ) );
                    Dcm_Dsp_Main_stMsgContext.resData[(u2_Pos >> DCM_DSP_SID2F_MASK_BYTESHIFT) + DCM_DSP_SID2F_RESDATA_STATE ] |= u1_ResControlState;
                }
                else
                {
                    b_BreakFlag = (boolean)TRUE;
                }
            }
            else if( u1_RetReadFnc == (Std_ReturnType)E_NOT_OK )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                b_BreakFlag = (boolean)TRUE;

                if( u1_ErrorCode != (Dcm_NegativeResponseCodeType)0x00U )
                {
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
                }
            }
            else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                b_BreakFlag = (boolean)TRUE;

                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2F_READ_DATA ); /* no return check required */

                u1_RetVal = DCM_E_PENDING;
            }
            else
            {
                /* No process */
            }

            if( b_BreakFlag == (boolean)TRUE )
            {
                Dcm_Dsp_SID2F_u1LoopCnt = u1_LoopCnt;
                break;
            }
            else
            {
                u1_OpStatusTmp = DCM_INITIAL;
            }
        }
    }

    if( b_BreakFlag == (boolean)FALSE )
    {
        /* Positive response */
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */

#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_Read_External                              */
/* Description   | Read loop processing                                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2F_Read_External
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetReadFnc;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    uint8                           u1_SignalIndex;
    boolean                         b_ReportControlStateOnlyIOCP03;
    boolean                         b_ReportControlState;

    u1_RetVal           = E_OK;
    u1_ErrorCode        = DCM_E_GENERALREJECT;
    b_ReportControlStateOnlyIOCP03 = Dcm_Dsp_Sid2F_bReportControlStateOnlyIOCP03;
    b_ReportControlState = (boolean)FALSE;
    /* External has only one signal */
    u1_SignalIndex      = (uint8)0U;

    if( b_ReportControlStateOnlyIOCP03 == (boolean)TRUE )
    {
        if( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_SHTTERMADJ )
        {
            b_ReportControlState = (boolean)TRUE;
        }
    }
    else
    {
        b_ReportControlState = (boolean)TRUE;
    }

    if( b_ReportControlState == (boolean)TRUE )
    {
        u1_RetReadFnc = Dcm_Dsp_DidMng_CallReadFnc( Dcm_Dsp_SID2F_u2DidIndex, 
                                                    u1_SignalIndex, 
                                                    u1OpStatus, 
                                                    &(Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2F_RESDATA_STATE]), 
                                                    &u1_ErrorCode );
        if( u1_RetReadFnc == (Std_ReturnType)E_OK )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            /* Positive response */
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
        else if( u1_RetReadFnc == (Std_ReturnType)E_NOT_OK )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
        }
        else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2F_READ_DATA ); /* no return check required */
            u1_RetVal = DCM_E_PENDING;
        }
        else
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
        }
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        /* Positive response */
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }

    return  u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2F_GetCtrlStateLenforResData                  */
/* Description   | Get ControlState length for Response Data                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2CtrlStateLen : ControlState Length                */
/* Return Value  | uint16 CtrlStateLenforResData                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint16, DCM_CODE ) Dcm_Dsp_SID2F_GetCtrlStateLenforResData
(
    const uint16 u2CtrlStateLen
)
{
    uint16          u2_CtrlStateLenforResData;
    boolean         b_ReportControlStateOnlyIOCP03;
    
    b_ReportControlStateOnlyIOCP03 = Dcm_Dsp_Sid2F_bReportControlStateOnlyIOCP03;

    if( b_ReportControlStateOnlyIOCP03 == (boolean)TRUE )
    {
        if( Dcm_Dsp_SID2F_u1IOCP == DCM_DSP_SID2F_IOCP_SHTTERMADJ )
        {
            u2_CtrlStateLenforResData = u2CtrlStateLen;
        }
        else
        {
            u2_CtrlStateLenforResData = (uint16)0U;
        }
    }
    else
    {
         u2_CtrlStateLenforResData = u2CtrlStateLen;
    }

    return u2_CtrlStateLenforResData;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID2F == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-0-1         :2019-01-11                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
