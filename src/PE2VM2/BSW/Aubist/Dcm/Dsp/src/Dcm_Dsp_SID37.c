/* Dcm_Dsp_SID37_c(v5-9-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID37/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if( DCM_SUPPORT_SID37 == STD_ON )

#include <Dcm/Dcm_Dsp_SID37.h>
#include <Dcm/Dcm_Dsp_SID37_Callout.h>
#include "../../Dsp/cfg/Dcm_Dsp_SID37_Cfg.h"
#include <Dcm/Dcm_Dsp_DataTfrMng.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID37_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID37_ChkProgProcFinished
(
    const Dcm_OpStatusType u1OpStatus
);

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID37_ReqTfrExitProc
(
    const Dcm_OpStatusType u1OpStatus
);

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID37_CancelProc
( void );

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID37_u4ReqParamRecordLen;

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
/* Function Name | Dcm_Dsp_SID37_Init                                       */
/* Description   | SID36 initialization                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID37_Init
( void )
{
    Dcm_Dsp_SID37_u4ReqParamRecordLen = (uint32)0x00000000U;
    
    return;
}

/****************************************************************************/
/* Function Name | Dcm_SID37                                                */
/* Description   | Request processing of SID37                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Processing normal                      */
/*               |   DCM_E_PENDING : Pending                                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID37
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID37_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID37_CancelProc();
    }
    else
    {
        /* no process */
    }

    if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID37_ChkProgProcFinishedCbk                     */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_CheckProgProcessFinished                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID37_ChkProgProcFinishedCbk
(
    const uint8 u1EventId
)
{
    Dcm_MsgLenType  u4_RecordLen;
    Std_ReturnType  u1_RetVal;

    u1_RetVal = Dcm_Dsp_SID37_ChkProgProcFinished( DCM_PENDING );
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        u4_RecordLen = Dcm_Dsp_SID37_u4ReqParamRecordLen;
        if( Dcm_Dsp_Main_stMsgContext.reqDataLen == u4_RecordLen )
        {
            (void)Dcm_Dsp_SID37_ReqTfrExitProc( DCM_INITIAL );             /* no return check required */
        }
        else
        {
            /* NRC0x13 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID37_ProcReqTfrExitCbk                          */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_ProcessRequestTransferExit                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID37_ProcReqTfrExitCbk
(
    const uint8 u1EventId
)
{
    (void)Dcm_Dsp_SID37_ReqTfrExitProc( DCM_PENDING );             /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID37_Confirmation                               */
/* Description   | Complete transmission of SID37 response message          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1IdContext    : ID Context                         */
/*               | [IN] u2ConnectionId : Connection ID                      */
/*               | [IN] u1Status       : Status                             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_NO_TRANSIT_TO_NONE == STD_OFF )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID37_Confirmation
(
    const Dcm_IdContextType u1IdContext,
    const uint16 u2ConnectionId,
    const Dcm_ConfirmationStatusType u1Status
)
{
    if( u1Status == (Dcm_ConfirmationStatusType)DCM_RES_POS_OK )
    {
        Dcm_Dsp_DataTfrMng_InitTfrStatus();
        Dcm_Dsp_DataTfrMng_InitTfrInfo();
    }

    return;
}
#endif  /* DCM_NO_TRANSIT_TO_NONE == STD_OFF */
#if ( DCM_NO_TRANSIT_TO_NONE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID37_Confirmation
(
    const Dcm_IdContextType u1IdContext,
    const uint16 u2ConnectionId,
    const Dcm_ConfirmationStatusType u1Status
)
{
    /* no process */

    return;
}
#endif  /* DCM_NO_TRANSIT_TO_NONE == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID37_InitialProc                                */
/* Description   | Initial process of SID37                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/*               |   E_NOT_OK       : Failure                               */
/*               |   DCM_E_PENDING  : Pending                               */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_UL_PROCESS_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID37_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint8           u1_TfrStatus;
    Std_ReturnType  u1_RetVal;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    u1_RetVal = E_OK;

    u1_TfrStatus = Dcm_Dsp_DataTfrMng_GetTfrStatus();
    if( ( u1_TfrStatus == DCM_TFR_DL_START ) ||
        ( u1_TfrStatus == DCM_TFR_DL_PROCEED ) ||
        ( u1_TfrStatus == DCM_TFR_DL_FIN ) )
    {
        Dcm_Dsp_SID37_u4ReqParamRecordLen = Dcm_Dsp_SID37_u4ReqParamRecordLenForDL;
        u1_RetVal = Dcm_Dsp_SID37_ChkProgProcFinished( DCM_INITIAL );
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            if( Dcm_Dsp_Main_stMsgContext.reqDataLen == Dcm_Dsp_SID37_u4ReqParamRecordLen )
            {
                u1_RetVal = Dcm_Dsp_SID37_ReqTfrExitProc( DCM_INITIAL );
            }
            else
            {
                /* NRC0x13 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                             DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
            }
        }
    }
    else
    {
        /* NRC0x24 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_REQUESTSEQUENCEERROR );
    }

    return u1_RetVal;
}
#endif /* DCM_UL_PROCESS_USE == STD_OFF */
#if ( DCM_UL_PROCESS_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID37_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint8           u1_TfrStatus;
    Std_ReturnType  u1_RetVal;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    u1_RetVal = E_OK;

    u1_TfrStatus = Dcm_Dsp_DataTfrMng_GetTfrStatus();
    if( ( u1_TfrStatus == DCM_TFR_DL_START ) ||
        ( u1_TfrStatus == DCM_TFR_DL_PROCEED ) ||
        ( u1_TfrStatus == DCM_TFR_DL_FIN ) )
    {
        Dcm_Dsp_SID37_u4ReqParamRecordLen = Dcm_Dsp_SID37_u4ReqParamRecordLenForDL;
        u1_RetVal = Dcm_Dsp_SID37_ChkProgProcFinished( DCM_INITIAL );
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            if( Dcm_Dsp_Main_stMsgContext.reqDataLen == Dcm_Dsp_SID37_u4ReqParamRecordLen )
            {
                u1_RetVal = Dcm_Dsp_SID37_ReqTfrExitProc( DCM_INITIAL );
            }
            else
            {
                /* NRC0x13 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                             DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
            }
        }
    }
    else if( ( u1_TfrStatus == DCM_TFR_UL_START ) ||
             ( u1_TfrStatus == DCM_TFR_UL_PROCEED ) ||
             ( u1_TfrStatus == DCM_TFR_UL_FIN ) )
    {
        Dcm_Dsp_SID37_u4ReqParamRecordLen = Dcm_Dsp_SID37_u4ReqParamRecordLenForUL;
        u1_RetVal = Dcm_Dsp_SID37_ChkProgProcFinished( DCM_INITIAL );
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            if( Dcm_Dsp_Main_stMsgContext.reqDataLen == Dcm_Dsp_SID37_u4ReqParamRecordLen )
            {
                u1_RetVal = Dcm_Dsp_SID37_ReqTfrExitProc( DCM_INITIAL );
            }
            else
            {
                /* NRC0x13 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                             DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
            }
        }
    }
    else
    {
        /* NRC0x24 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_REQUESTSEQUENCEERROR );
    }

    return u1_RetVal;
}
#endif /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID37_ChkProgProcFinished                        */
/* Description   | Check whether program process is finished                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus   : Operation state                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Program process is finished            */
/*               |   E_NOT_OK      : Program process is not finished        */
/*               |   DCM_E_PENDING : Check is not yet finished              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID37_ChkProgProcFinished
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Dcm_Dsp_DataTfrMng_TfrInfoType  st_TfrInfo;
    Std_ReturnType                  u1_RetVal;

    Dcm_Dsp_DataTfrMng_GetTfrInfo( &st_TfrInfo );
    u1_RetVal = Dcm_Dsp_SID37_CallCheckProgProcessFinishedFnc( u1OpStatus,
                                                               st_TfrInfo.u1Dfid,
                                                               st_TfrInfo.u1MemoryId,
                                                               st_TfrInfo.u4MemoryAddress,
                                                               st_TfrInfo.u4MemorySize );
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
    }
    else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID37_CHKPROGPROCFIN );             /* no return check required */
    }
    else if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        /* NRC0x24 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_REQUESTSEQUENCEERROR );
    }
    else
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        /* NRC0x10 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_GENERALREJECT );

        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID37_ReqTfrExitProc                             */
/* Description   | Process of request transfer exit                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus   : Operation state                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Request was successful                 */
/*               |   E_NOT_OK      : Request was not successful             */
/*               |   DCM_E_PENDING : Request is not yet finished            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID37_ReqTfrExitProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    uint32                                    u4_ResDataLen;
    Std_ReturnType                            u1_RetProcReqTfrExit;
    Std_ReturnType                            u1_RetVal;
    Dcm_NegativeResponseCodeType              u1_ErrorCode;
    uint8                                     u1_DummyTfrReqParamRecord;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )  pt_ReqData;

    u4_ResDataLen = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
    u1_RetVal = E_NOT_OK;
    u1_ErrorCode = DCM_E_GENERALREJECT;
    u1_DummyTfrReqParamRecord = (uint8)0U;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == (Dcm_MsgLenType)0x00000000U )
    {
        pt_ReqData = &u1_DummyTfrReqParamRecord;
    }
    else
    {
        pt_ReqData = Dcm_Dsp_Main_stMsgContext.reqData;
    }
    
    u1_RetProcReqTfrExit = Dcm_Dsp_DataTfrMng_ProcReqTfrExit( u1OpStatus,
                                                              pt_ReqData,
                                                              Dcm_Dsp_Main_stMsgContext.reqDataLen,
                                                              &Dcm_Dsp_Main_stMsgContext.resData[0],
                                                              &u4_ResDataLen,
                                                              &u1_ErrorCode );

    if( u1_RetProcReqTfrExit == (Std_ReturnType)E_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        Dcm_Dsp_Main_stMsgContext.resDataLen = u4_ResDataLen;
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );

        u1_RetVal = E_OK;
    }
    else if( u1_RetProcReqTfrExit == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID37_PROCREQTFREXIT );               /* no return check required */

        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID37_CancelProc                                 */
/* Description   | Cancel process of SID37                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK : Processing normal                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID37_CancelProc
( void )
{
    uint32                                 u4_DummyTfrResParamRecordSize;
    Std_ReturnType                         u1_RetVal;
    uint8                                  u1_DummyTfrReqParamRecord;
    uint8                                  u1_DummyTfrResParamRecord;
    Dcm_NegativeResponseCodeType           u1_DummyErrorCode;
    boolean                                b_UserNotifyFlag;

    u1_RetVal = E_OK;
    u4_DummyTfrResParamRecordSize = (uint32)0U;
    u1_DummyTfrReqParamRecord = (uint8)0U;
    u1_DummyTfrResParamRecord = (uint8)0U;
    u1_DummyErrorCode = (uint8)0U;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SID37_CallCheckProgProcessFinishedFnc( DCM_CANCEL,               /* no return check required */
                                                             0x00U,
                                                             0x00U,
                                                             0x00000000U,
                                                             0x00000000U );

        (void)Dcm_Dsp_DataTfrMng_ProcReqTfrExit( DCM_CANCEL,                           /* no return check required */
                                                 &u1_DummyTfrReqParamRecord,
                                                 0x00000000U,
                                                 &u1_DummyTfrResParamRecord,
                                                 &u4_DummyTfrResParamRecordSize,
                                                 &u1_DummyErrorCode );

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID37_CHKPROGPROCFIN,             /* no return check required */
                                         (boolean)FALSE );

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID37_PROCREQTFREXIT,             /* no return check required */
                                         (boolean)FALSE );

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID37 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

