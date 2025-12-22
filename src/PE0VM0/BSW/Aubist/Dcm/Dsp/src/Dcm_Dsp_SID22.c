/* Dcm_Dsp_SID22_c(v5-4-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID22/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID22.h>
#if ( DCM_SUPPORT_SID22 == STD_ON )
#include <Dcm/Dcm_Dsp_DidMng.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID22_DIDLEN        ((uint8)0x02U)
#define DCM_DSP_SID22_DIDSHIFT      ((uint8)8U)
#define DCM_DSP_SID22_ODD_NUM           ((uint32)0x00000001UL)
#define DCM_DSP_SID22_CALC_SHIFT_VAL    ((uint8)0x01U)

#define DCM_DSP_SID22_SUPPORT_CHK       ((uint8)0x00U)
#define DCM_DSP_SID22_DIDAVAILABLE      ((uint8)0x01U)
#define DCM_DSP_SID22_READ_DATA_LEN     ((uint8)0x02U)

#define DCM_DSP_SID22_DYN_DID_NOT_DEF   ((uint8)0x00U)

#define DCM_DSP_SID22_LOOP_CNT_NUM_ZERO ((uint16)0x0000U)
#define DCM_DSP_SID22_INVALID_NRC_ZERO  ((uint8)0x00U)

#define DCM_DSP_SID22_PB_MIN_BLANK      ((uint8)0x03U)

#define DCM_DSP_SID22_VALUE_MAX_U4      ((uint32)0xFFFFFFFFU)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct{
    uint16      u2DidIndex;
    uint8       u1KindOfTable;
}Dcm_Dsp_SID22_DidIndexInfoType;

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_CancelProc
(
    void
);
static FUNC (Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_ReadDataProc
(
    const uint8 u1ProcessId
);
static FUNC (Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_CheckSupportProc
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_IsDidAvailableProc
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_ReadDidDataProc
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_ReadDataLenProc
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_CheckConditionProc
(
    void
);
static FUNC(Dcm_Main_ReturnCheckType, DCM_CODE) Dcm_Dsp_SID22_CheckValidDidProc
(
    boolean b_SupportEnabledDid
);

#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_ReadDidDataUpdate
(
    const Dcm_OpStatusType u1OpStatus
);
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID22_StartPage
(
    void
);
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_ExecReadDidData
(
    const uint8                                 u1NotifyOpStatus,
    const uint16                                u2DidNumOfReqMsg,
    const uint16                                u2DidToReadCnt,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA )   pRemainReadDidNum,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) pErrorCode
);
static FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID22_IsResDataSettingPossible
(
    const uint32 u4DataBufferLength
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_JudgeProceedToNextProcByDidSupported
(
    void
);
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_OBD_RANGE_DID_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_CallReadObdDid
(
    const uint16 u2Did,
    const Dcm_OpStatusType u1NotifyOpStatus,
    const uint32 u4DataBufferLen,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptResData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptResDataLen,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptNextOpInit
);
#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* data                                                                       */
/*----------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID22_u2DidInfo;
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID22_u2DidToReadCnt;
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID22_u2DidNumOfReqMsg;
static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID22_u4ResDataLen;
static VAR( Dcm_Dsp_SID22_DidIndexInfoType, DCM_VAR_NO_INIT ) Dcm_Dsp_SID22_stDidIndexInfo;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_SID22_bDidReadSupInfo[DCM_P_MAX_DID_TO_READ];
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID22_u2DidSupIndexInfo;

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_SID22                                                */
/* Description   | SID22 request processing                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN]OpStatus         :Operation Status                   */
/*               | [IN]pMsgContext      :Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID22    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID22_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID22_CancelProc( );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_FORCE_RCRRP_OK )
    {
        u1_RetVal = Dcm_Dsp_SID22_ReadDidDataProc( DCM_FORCE_RCRRP_OK );
    }
    else
    {
        /* None */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_IsDidAvailableCbk                          */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_IsDidAvailable                                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID22_IsDidAvailableCbk   /* MISRA DEVIATION */
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{

    (void)Dcm_Dsp_SID22_ReadDataProc( DCM_DSP_SID22_DIDAVAILABLE );                         /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_ReadDidDataCbk                             */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_ReadDidData                                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID22_ReadDidDataCbk      /* MISRA DEVIATION */
(
    const uint8 u1EventId
)
{
    uint8                           u1_NotifyOpStatus;

    if( u1EventId == DCM_M_EVTID_SID22_READ_CYCLE )
    {
        u1_NotifyOpStatus   = DCM_INITIAL;
    }
    else
    {
        u1_NotifyOpStatus   = DCM_PENDING;
    }

    (void)Dcm_Dsp_SID22_ReadDidDataProc( u1_NotifyOpStatus );                               /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_DidRangeDataLenCbk                         */
/* Description   | Callback function for  event delivery registration of    */
/*               | Xxx_ ReadDidRangeDataLength                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID22_DidRangeDataLenCbk    /* MISRA DEVIATION */
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{

    (void)Dcm_Dsp_SID22_ReadDataProc( DCM_DSP_SID22_READ_DATA_LEN );                        /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_CheckSupportCbk                            */
/* Description   | Callback function for  event delivery registration of    */
/*               | Dcm_Dsp_SID22_CheckSupportProc                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID22_CheckSupportCbk
(
    const uint8 u1EventId
)
{

    (void)Dcm_Dsp_SID22_ReadDataProc( DCM_DSP_SID22_SUPPORT_CHK );                        /* no return check required */

    return;
}

#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_UpdatePageCbk                              */
/* Description   | Call Back Function to Continue SID22 UpdatePage          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event Id                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID22_UpdatePageCbk         /* MISRA DEVIATION */
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    uint8                           u1_NotifyOpStatus;
    boolean                         b_UserNotifyFlag;

    if( u1EventId == DCM_M_EVTID_SID22_UPDATERCRRP )
    {
        u1_NotifyOpStatus   = DCM_FORCE_RCRRP_OK;
    }
    else
    {
        /* if( u1EventId == DCM_M_EVTID_SID22_UPDATEPAGE ) */
        b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
        if( b_UserNotifyFlag != (boolean)TRUE )
        {
            u1_NotifyOpStatus   = DCM_INITIAL;
        }
        else
        {
            u1_NotifyOpStatus   = DCM_PENDING;
        }
    }

    (void)Dcm_Dsp_SID22_ReadDidDataUpdate( u1_NotifyOpStatus );               /* no return check required */

    return;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */


#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_UpdatePage                                 */
/* Description   | UpdatePage of SID 22                                     */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptResData       : Response Data                    */
/*               | [IN]  u4ResMaxDataLen : Buffer Size of Response Data     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_UpdatePage  /* MISRA DEVIATION */
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
)
{
    Std_ReturnType                  u1_RetVal;
    Dcm_OpStatusType                u1_NotifyOpStatus;
    boolean                         b_UserNotifyFlag;

    u1_RetVal          = E_OK;

    if( u4ResMaxDataLen == (Dcm_MsgLenType)DCM_DSD_UPDATEPAGE_INITIAL_ACT )
    {
        Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
        Dcm_Dsp_SID22_u4ResDataLen -= Dcm_Dsp_Main_stMsgContext.resDataLen; /* no wrap around */
    }
    else
    {
        Dcm_Dsp_Main_stMsgContext.resData          = ptResData;
        Dcm_Dsp_Main_stMsgContext.resMaxDataLen    = u4ResMaxDataLen;
        Dcm_Dsp_Main_stMsgContext.resDataLen       = (uint32)0U;

        b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
        if( b_UserNotifyFlag != (boolean)TRUE )
        {
            u1_NotifyOpStatus   = DCM_INITIAL;
        }
        else
        {
            u1_NotifyOpStatus   = DCM_UPDATE_PAGE_OK;
        }

        u1_RetVal = Dcm_Dsp_SID22_ReadDidDataUpdate( u1_NotifyOpStatus );
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */


#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_CancelPage                                 */
/* Description   | CancelPage of SID 22                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_OBD_RANGE_DID_USE == STD_OFF )
FUNC(void, DCM_CODE) Dcm_Dsp_SID22_CancelPage            /* MISRA DEVIATION */
(void)
{
    boolean                         b_UserNotifyFlag;
    uint16                          u2_DidInfo;
    uint32                          u4_DataBufferLength;
    uint32                          u4_DataLength;
    Dcm_Dsp_SID22_DidIndexInfoType  st_DidIndexInfo;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    uint16                          u2_LoopCnt;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ResData;

    u2_DidInfo              = Dcm_Dsp_SID22_u2DidInfo;
    u4_DataBufferLength     = 0x00000000U;
    u4_DataLength           = 0x00000000U;
    u1_ErrorCode            = 0x00U;
    u2_LoopCnt              = 0U;
    pt_ResData              = &(Dcm_Dsp_Main_stMsgContext.resData[0]);

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        st_DidIndexInfo = Dcm_Dsp_SID22_stDidIndexInfo;

        if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
        {
            ( void )Dcm_Dsp_DidMng_CallReadDidFnc( st_DidIndexInfo.u2DidIndex,
                                                   u2_DidInfo,
                                                   pt_ResData,
                                                   DCM_CANCEL,
                                                   u4_DataBufferLength,
                                                   &u4_DataLength,
                                                   &u1_ErrorCode
                                                   );                                       /* no return check required */
        }
        else
        {
            ( void )Dcm_Dsp_DidMng_CallReadDynDidFnc( st_DidIndexInfo.u2DidIndex,
                                                      pt_ResData,
                                                      DCM_CANCEL,
                                                      u4_DataBufferLength,
                                                      &u4_DataLength,
                                                      &u1_ErrorCode,
                                                      &u2_LoopCnt
                                                      );                                    /* no return check required */
        }

        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_READ_DID_DATA,     (boolean)FALSE );     /* no return check required */

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_UPDATEPAGE, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_OFF */
#if ( DCM_OBD_RANGE_DID_USE == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsp_SID22_CancelPage            /* MISRA DEVIATION */
(void)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ResData;
    uint32                          u4_DataBufferLength;
    uint32                          u4_DataLength;
    Dcm_Dsp_SID22_DidIndexInfoType  st_DidIndexInfo;
    uint16                          u2_DidInfo;
    uint16                          u2_LoopCnt;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_UserNotifyFlag;

    u2_DidInfo              = Dcm_Dsp_SID22_u2DidInfo;
    u4_DataBufferLength     = 0x00000000U;
    u4_DataLength           = 0x00000000U;
    u1_ErrorCode            = 0x00U;
    u2_LoopCnt              = 0U;
    pt_ResData              = &(Dcm_Dsp_Main_stMsgContext.resData[0]);

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        st_DidIndexInfo = Dcm_Dsp_SID22_stDidIndexInfo;

        if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
        {
            ( void )Dcm_Dsp_DidMng_CallReadDidFnc( st_DidIndexInfo.u2DidIndex,
                                                   u2_DidInfo,
                                                   pt_ResData,
                                                   DCM_CANCEL,
                                                   u4_DataBufferLength,
                                                   &u4_DataLength,
                                                   &u1_ErrorCode
                                                   );                                       /* no return check required */
        }
        else if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_DYNAMIC )
        {
            ( void )Dcm_Dsp_DidMng_CallReadDynDidFnc( st_DidIndexInfo.u2DidIndex,
                                                      pt_ResData,
                                                      DCM_CANCEL,
                                                      u4_DataBufferLength,
                                                      &u4_DataLength,
                                                      &u1_ErrorCode,
                                                      &u2_LoopCnt
                                                      );                                    /* no return check required */
        }
        else
        {
            ( void )Dcm_Dsp_DidMng_OBD_CallReadObdDidFnc( u2_DidInfo,
                                                          DCM_CANCEL,
                                                          u4_DataBufferLength,
                                                          pt_ResData,
                                                          &u4_DataLength,
                                                          &u1_ErrorCode
                                                          );                                /* no return check required */
        }

        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_READ_DID_DATA,     (boolean)FALSE );     /* no return check required */

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_UPDATEPAGE, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_InitialProc                                */
/* Description   | Execute SID 22 request processing                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN]ptMsgContext     :Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType                  u1_RetVal;
    Dcm_MsgLenType                  u4_ReqDataLen;
    uint32                          u4_ReqMsgLenChk;
    uint32                          u4_ReadDidNum;
    uint32                          u4_DidReadSumCnt;
    uint32                          u4_MaxDidToRead;

    u1_RetVal               = E_OK;
    u4_MaxDidToRead         = (uint32)Dcm_P_u2Max_Did_To_Read;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID22_u2DidToReadCnt = 0U;
    Dcm_Dsp_SID22_u4ResDataLen   = 0U;

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    u4_ReqDataLen = Dcm_Dsp_Main_stMsgContext.reqDataLen;
    if( u4_ReqDataLen >= DCM_DSP_SID22_DIDLEN )
    {
        u4_ReqMsgLenChk = u4_ReqDataLen & DCM_DSP_SID22_ODD_NUM;

        if( u4_ReqMsgLenChk != DCM_DSP_SID22_ODD_NUM )
        {

            u4_ReadDidNum = u4_ReqDataLen >> DCM_DSP_SID22_CALC_SHIFT_VAL;

            if( u4_ReadDidNum <= u4_MaxDidToRead )
            {
                for( u4_DidReadSumCnt = (uint32)0U; u4_DidReadSumCnt < u4_ReadDidNum; u4_DidReadSumCnt++ )
                {
                    Dcm_Dsp_SID22_bDidReadSupInfo[u4_DidReadSumCnt] = (boolean)TRUE;
                }
                Dcm_Dsp_SID22_u2DidNumOfReqMsg = (uint16)u4_ReadDidNum;
#if ( DCM_OBD_RANGE_DID_USE == STD_ON )
                Dcm_Dsp_DidMng_OBD_ClrForEachReq();
#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */
                u1_RetVal = Dcm_Dsp_SID22_ReadDataProc( DCM_DSP_SID22_SUPPORT_CHK );
            }
            else
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
            }
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
        }
    }
    else
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    }

    return u1_RetVal;

}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_CancelProc                                 */
/* Description   | SID22 request cancel processing                          */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_OBD_RANGE_DID_USE == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_CancelProc
(
    void
)
{
    boolean                         b_UserNotifyFlag;
    uint16                          u2_DidInfo;
    Dcm_DidSupportedType            u1_Supported;
    uint32                          u4_DataBufferLength;
    uint32                          u4_DataLength;
    Dcm_Dsp_SID22_DidIndexInfoType  st_DidIndexInfo;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    uint16                          u2_LoopCnt;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ResData;

    u2_DidInfo      = Dcm_Dsp_SID22_u2DidInfo;
    u1_Supported    = DCM_DID_NOT_SUPPORTED;
    u4_DataBufferLength   = 0x00000000U;
    u4_DataLength   = 0x00000000U;
    u1_ErrorCode    = 0x00U;
    u2_LoopCnt      = 0U;
    pt_ResData      = &(Dcm_Dsp_Main_stMsgContext.resData[0]);

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        st_DidIndexInfo = Dcm_Dsp_SID22_stDidIndexInfo;

        if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
        {
            ( void )Dcm_Dsp_DidMng_CallAvailableFnc( st_DidIndexInfo.u2DidIndex,
                                                     u2_DidInfo,
                                                     DCM_CANCEL,
                                                     &u1_Supported
                                                     );                                     /* no return check required */

            ( void )Dcm_Dsp_DidMng_CallDataLengthFnc( st_DidIndexInfo.u2DidIndex,
                                                      u2_DidInfo,
                                                      DCM_CANCEL,
                                                      &u4_DataLength
                                                      );                                    /* no return check required */

            ( void )Dcm_Dsp_DidMng_CallReadDidFnc( st_DidIndexInfo.u2DidIndex,
                                                   u2_DidInfo,
                                                   pt_ResData,
                                                   DCM_CANCEL,
                                                   u4_DataBufferLength,
                                                   &u4_DataLength,
                                                   &u1_ErrorCode
                                                   );                                       /* no return check required */

            (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_DIDAVAILABLE,      (boolean)FALSE );     /* no return check required */
            (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_RANGE_DATA_LEN,    (boolean)FALSE );     /* no return check required */
        }
        else
        {
            ( void )Dcm_Dsp_DidMng_CallReadDynDidFnc( st_DidIndexInfo.u2DidIndex,
                                                      pt_ResData,
                                                      DCM_CANCEL,
                                                      u4_DataBufferLength,
                                                      &u4_DataLength,
                                                      &u1_ErrorCode,
                                                      &u2_LoopCnt
                                                      );                                    /* no return check required */
        }

        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_READ_DID_DATA,     (boolean)FALSE );     /* no return check required */

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    }
    else
    {
        /* None */
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_CHKSUP_CYCLE,      (boolean)FALSE );         /* no return check required */
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_READ_CYCLE,        (boolean)FALSE );         /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_OFF */
#if ( DCM_OBD_RANGE_DID_USE == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_CancelProc
(
    void
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ResData;
    uint32                          u4_DataBufferLength;
    uint32                          u4_DataLength;
    Dcm_Dsp_SID22_DidIndexInfoType  st_DidIndexInfo;
    uint16                          u2_DidInfo;
    uint16                          u2_LoopCnt;
    Dcm_DidSupportedType            u1_Supported;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_UserNotifyFlag;

    u2_DidInfo      = Dcm_Dsp_SID22_u2DidInfo;
    u1_Supported    = DCM_DID_NOT_SUPPORTED;
    u4_DataBufferLength   = 0x00000000U;
    u4_DataLength   = 0x00000000U;
    u1_ErrorCode    = 0x00U;
    u2_LoopCnt      = 0U;
    pt_ResData      = &(Dcm_Dsp_Main_stMsgContext.resData[0]);

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        st_DidIndexInfo = Dcm_Dsp_SID22_stDidIndexInfo;

        if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
        {
            ( void )Dcm_Dsp_DidMng_CallAvailableFnc( st_DidIndexInfo.u2DidIndex,
                                                     u2_DidInfo,
                                                     DCM_CANCEL,
                                                     &u1_Supported
                                                     );                                     /* no return check required */

            ( void )Dcm_Dsp_DidMng_CallDataLengthFnc( st_DidIndexInfo.u2DidIndex,
                                                      u2_DidInfo,
                                                      DCM_CANCEL,
                                                      &u4_DataLength
                                                      );                                    /* no return check required */

            ( void )Dcm_Dsp_DidMng_CallReadDidFnc( st_DidIndexInfo.u2DidIndex,
                                                   u2_DidInfo,
                                                   pt_ResData,
                                                   DCM_CANCEL,
                                                   u4_DataBufferLength,
                                                   &u4_DataLength,
                                                   &u1_ErrorCode
                                                   );                                       /* no return check required */

            (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_DIDAVAILABLE,      (boolean)FALSE );     /* no return check required */
            (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_RANGE_DATA_LEN,    (boolean)FALSE );     /* no return check required */
        }
        else if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_DYNAMIC )
        {
            ( void )Dcm_Dsp_DidMng_CallReadDynDidFnc( st_DidIndexInfo.u2DidIndex,
                                                      pt_ResData,
                                                      DCM_CANCEL,
                                                      u4_DataBufferLength,
                                                      &u4_DataLength,
                                                      &u1_ErrorCode,
                                                      &u2_LoopCnt
                                                      );                                    /* no return check required */
        }
        else
        {
            ( void )Dcm_Dsp_DidMng_OBD_CallReadObdDidFnc( u2_DidInfo,
                                                          DCM_CANCEL,
                                                          u4_DataBufferLength,
                                                          pt_ResData,
                                                          &u4_DataLength,
                                                          &u1_ErrorCode
                                                          );                                /* no return check required */
        }

        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_READ_DID_DATA,     (boolean)FALSE );     /* no return check required */

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    }
    else
    {
        /* None */
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_CHKSUP_CYCLE,      (boolean)FALSE );         /* no return check required */
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID22_READ_CYCLE,        (boolean)FALSE );         /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */

#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_ReadDataProc                               */
/* Description   | ReadData execution processing                            */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1ProcessId      :Process ID                         */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC (Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_ReadDataProc
(
    const uint8 u1ProcessId
)
{
    uint32                          u4_ResDataLenMax;
    Dcm_MsgLenType                  u4_ResMaxDataLen;
    Dcm_MsgLenType                  u4_MaxDataLen;

    uint16                          u2_DidHightByte;
    uint16                          u2_DidLowByte;
    uint16                          u2_DidInfo;
    uint16                          u2_DidNumOfReqMsg;
    uint16                          u2_ReadDidCnt;
    uint16                          u2_DidToReadCnt;
    uint16                          u2_RemainCheckSupNum;
    uint8                           u1_ChkId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_ChkReturnFnc;
    Std_ReturnType                  u1_RetJudgeNextProc;
    boolean                         b_BreakFlag;
    boolean                         b_DataSetPossible;

    u1_RetVal               = E_OK;
    u1_ChkId                = u1ProcessId;
    b_BreakFlag             = (boolean)FALSE;

    Dcm_Dsp_SID22_u2DidSupIndexInfo = Dcm_Dsp_SID22_u2DidToReadCnt;
    u2_DidToReadCnt                 = Dcm_Dsp_SID22_u2DidToReadCnt;
    u2_DidNumOfReqMsg               = Dcm_Dsp_SID22_u2DidNumOfReqMsg;
    u4_ResDataLenMax                = Dcm_P_Sid22_u4Resdatalen_Max;
    u2_RemainCheckSupNum            = Dcm_P_u2Did_Check_Num_Per_Cycle;

    for( u2_ReadDidCnt = u2_DidToReadCnt; u2_ReadDidCnt < u2_DidNumOfReqMsg; u2_ReadDidCnt++ )
    {
        if( u2_RemainCheckSupNum == DCM_DSP_SID22_LOOP_CNT_NUM_ZERO )
        {
            Dcm_Dsp_SID22_u2DidToReadCnt = u2_DidToReadCnt;
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID22_CHKSUP_CYCLE ); /* no return check required */
            u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
            b_BreakFlag = (boolean)TRUE;
        }
        else
        {
            u2_DidHightByte = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN );
            u2_DidLowByte   = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN ) + (uint16)1U;

            u2_DidInfo =  (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[u2_DidHightByte]) << DCM_DSP_SID22_DIDSHIFT )
                                 | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[u2_DidLowByte]);

            Dcm_Dsp_SID22_u2DidInfo = u2_DidInfo;

            if( u1_ChkId == DCM_DSP_SID22_DIDAVAILABLE )
            {
                u1_ChkReturnFnc = Dcm_Dsp_SID22_IsDidAvailableProc( DCM_PENDING );
            }
            else if( u1_ChkId == DCM_DSP_SID22_READ_DATA_LEN )
            {
                u1_ChkReturnFnc = Dcm_Dsp_SID22_ReadDataLenProc( DCM_PENDING );
            }
            else
            {
                u1_ChkReturnFnc = Dcm_Dsp_SID22_CheckSupportProc( );
            }

            if( u1_ChkReturnFnc == (Std_ReturnType)E_OK )
            {
                u2_RemainCheckSupNum = (uint16)(u2_RemainCheckSupNum - (uint16)1U);
                u2_DidToReadCnt = (uint16)(u2_DidToReadCnt + (uint16)1U);
                Dcm_Dsp_SID22_u2DidSupIndexInfo = u2_DidToReadCnt;
                u1_ChkId  = DCM_DSP_SID22_SUPPORT_CHK;
            }
            else if( u1_ChkReturnFnc == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsp_SID22_u2DidToReadCnt = u2_DidToReadCnt;
                u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
                b_BreakFlag = (boolean)TRUE;
            }
            else
            {
                b_BreakFlag = (boolean)TRUE;
            }
        }

        if( b_BreakFlag == (boolean)FALSE )
        {
            /* None */
        }
        else
        {
            break;
        }
    }

    if( u2_DidToReadCnt == u2_DidNumOfReqMsg )
    {
        u4_ResMaxDataLen    = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;

        if( u4_ResMaxDataLen < u4_ResDataLenMax )    /* MISRA DEVIATION */
        {
            u4_MaxDataLen = u4_ResMaxDataLen;    /* MISRA DEVIATION */
        }
        else
        {
            u4_MaxDataLen = u4_ResDataLenMax;
        }
        
        u1_RetJudgeNextProc = Dcm_Dsp_SID22_JudgeProceedToNextProcByDidSupported();
        if( u1_RetJudgeNextProc == (Std_ReturnType)E_OK )
        {
            b_DataSetPossible = Dcm_Dsp_SID22_IsResDataSettingPossible( u4_MaxDataLen );
            if( b_DataSetPossible == (boolean)TRUE )            /* MISRA DEVIATION */
            {
                Dcm_Dsp_SID22_u2DidToReadCnt = 0U;
                u1_RetVal = Dcm_Dsp_SID22_ReadDidDataProc( DCM_INITIAL );
            }
            else
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG ); /* MISRA DEVIATION */
            }
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    else
    {
        /* None */
    }

    return u1_RetVal;

}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */

#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_ReadDataProc                               */
/* Description   | ReadData execution processing                            */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1ProcessId      :Process ID                         */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC (Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_ReadDataProc
(
    const uint8 u1ProcessId
)
{
    Dcm_MsgLenType                  u4_MaxDataLen;
    uint16                          u2_DidHightByte;
    uint16                          u2_DidLowByte;
    uint16                          u2_DidInfo;
    uint16                          u2_DidNumOfReqMsg;
    uint16                          u2_ReadDidCnt;
    uint16                          u2_DidToReadCnt;
    uint16                          u2_RemainCheckSupNum;
    uint8                           u1_ChkId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_ChkReturnFnc;
    Std_ReturnType                  u1_RetJudgeNextProc;
    boolean                         b_BreakFlag;
    boolean                         b_DataSetPossible;

    u1_RetVal               = E_OK;
    u1_ChkId                = u1ProcessId;
    b_BreakFlag             = (boolean)FALSE;

    Dcm_Dsp_SID22_u2DidSupIndexInfo = Dcm_Dsp_SID22_u2DidToReadCnt;
    u2_DidToReadCnt                 = Dcm_Dsp_SID22_u2DidToReadCnt;
    u2_DidNumOfReqMsg               = Dcm_Dsp_SID22_u2DidNumOfReqMsg;
    u2_RemainCheckSupNum            = Dcm_P_u2Did_Check_Num_Per_Cycle;

    for( u2_ReadDidCnt = u2_DidToReadCnt; u2_ReadDidCnt < u2_DidNumOfReqMsg; u2_ReadDidCnt++ )
    {
        if( u2_RemainCheckSupNum == DCM_DSP_SID22_LOOP_CNT_NUM_ZERO )
        {
            Dcm_Dsp_SID22_u2DidToReadCnt = u2_DidToReadCnt;
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID22_CHKSUP_CYCLE ); /* no return check required */
            u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
            b_BreakFlag = (boolean)TRUE;
        }
        else
        {
            u2_DidHightByte = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN );
            u2_DidLowByte   = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN ) + (uint16)1U;

            u2_DidInfo =  (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[u2_DidHightByte]) << DCM_DSP_SID22_DIDSHIFT )
                                 | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[u2_DidLowByte]);

            Dcm_Dsp_SID22_u2DidInfo = u2_DidInfo;

            if( u1_ChkId == DCM_DSP_SID22_DIDAVAILABLE )
            {
                u1_ChkReturnFnc = Dcm_Dsp_SID22_IsDidAvailableProc( DCM_PENDING );
            }
            else if( u1_ChkId == DCM_DSP_SID22_READ_DATA_LEN )
            {
                u1_ChkReturnFnc = Dcm_Dsp_SID22_ReadDataLenProc( DCM_PENDING );
            }
            else
            {
                u1_ChkReturnFnc = Dcm_Dsp_SID22_CheckSupportProc( );
            }

            if( u1_ChkReturnFnc == (Std_ReturnType)E_OK )
            {
                u2_RemainCheckSupNum = (uint16)(u2_RemainCheckSupNum - (uint16)1U);
                u2_DidToReadCnt = (uint16)(u2_DidToReadCnt + (uint16)1U);
                Dcm_Dsp_SID22_u2DidSupIndexInfo = u2_DidToReadCnt;
                u1_ChkId  = DCM_DSP_SID22_SUPPORT_CHK;
            }
            else if( u1_ChkReturnFnc == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsp_SID22_u2DidToReadCnt = u2_DidToReadCnt;
                u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
                b_BreakFlag = (boolean)TRUE;
            }
            else
            {
                b_BreakFlag = (boolean)TRUE;
            }
        }

        if( b_BreakFlag == (boolean)FALSE )
        {
            /* None */
        }
        else
        {
            break;
        }
    }

    if( u2_DidToReadCnt == u2_DidNumOfReqMsg )
    {
        
        u1_RetJudgeNextProc = Dcm_Dsp_SID22_JudgeProceedToNextProcByDidSupported();
        if( u1_RetJudgeNextProc == (Std_ReturnType)E_OK )
        {
            u4_MaxDataLen = Dcm_P_Sid22_u4Resdatalen_Max;
            b_DataSetPossible = Dcm_Dsp_SID22_IsResDataSettingPossible( u4_MaxDataLen );
            if( b_DataSetPossible == (boolean)TRUE )            /* MISRA DEVIATION */
            {
                Dcm_Dsp_SID22_u2DidToReadCnt = 0U;
                u1_RetVal = Dcm_Dsp_SID22_ReadDidDataProc( DCM_INITIAL );
            }
            else
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG ); /* MISRA DEVIATION */
            }
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    else
    {
        /* None */
    }

    return u1_RetVal;

}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_CheckSupportProc                           */
/* Description   | Confirm whether request DID is supported                 */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_OBD_RANGE_DID_USE == STD_OFF )
static FUNC (Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_CheckSupportProc
(
    void
)
{
    Std_ReturnType                  u1_RetVal;
    Dcm_Main_ReturnCheckType        u1_RetValidDid;

    u1_RetVal       = E_NOT_OK;

    u1_RetValidDid = Dcm_Dsp_SID22_CheckValidDidProc( (boolean)TRUE );

    if( u1_RetValidDid == DCM_MAIN_E_CHECK_OK )
    {
        if( Dcm_Dsp_SID22_stDidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_DYNAMIC )
        {
            u1_RetVal = Dcm_Dsp_SID22_CheckConditionProc();
        }
        else
        {
            u1_RetVal = Dcm_Dsp_SID22_IsDidAvailableProc( DCM_INITIAL );
        }
    }
    else if( u1_RetValidDid == DCM_MAIN_E_CHECK_NOT_OK )
    {
        Dcm_Dsp_SID22_bDidReadSupInfo[Dcm_Dsp_SID22_u2DidSupIndexInfo] = (boolean)FALSE;
        u1_RetVal = (Std_ReturnType)E_OK;
    }
    else
    {
        /* None */
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_OFF */
#if ( DCM_OBD_RANGE_DID_USE == STD_ON )
static FUNC (Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_CheckSupportProc
(
    void
)
{
    Std_ReturnType                  u1_RetVal;
    Dcm_Main_ReturnCheckType        u1_RetValidDid;

    u1_RetVal       = E_NOT_OK;

    u1_RetValidDid = Dcm_Dsp_SID22_CheckValidDidProc( (boolean)TRUE );

    if( u1_RetValidDid == DCM_MAIN_E_CHECK_OK )
    {
        if( Dcm_Dsp_SID22_stDidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_DYNAMIC )
        {
            u1_RetVal = Dcm_Dsp_SID22_CheckConditionProc();
        }
        else if( Dcm_Dsp_SID22_stDidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_OBDDID )
        {
            u1_RetVal = Dcm_Dsp_SID22_ReadDataLenProc( DCM_INITIAL );
        }
        else
        {
            u1_RetVal = Dcm_Dsp_SID22_IsDidAvailableProc( DCM_INITIAL );
        }
    }
    else if( u1_RetValidDid == DCM_MAIN_E_CHECK_NOT_OK )
    {
        Dcm_Dsp_SID22_bDidReadSupInfo[Dcm_Dsp_SID22_u2DidSupIndexInfo] = (boolean)FALSE;
        u1_RetVal = (Std_ReturnType)E_OK;
    }
    else
    {
        /* None */
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_IsDidAvailableProc                         */
/* Description   | Confirm whether the requested DID is located in the      */
/*               | valid range within DidRange                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1OpStatus       :Operation Status                   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_IsDidAvailableProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType          u1_RetVal;
    Std_ReturnType          u1_RetAvailableFnc;
    Std_ReturnType          u1_RetSupportedDid;
    Dcm_DidSupportedType    u1_Supported;
    uint16                  u2_DidInfo;
    Dcm_Dsp_SID22_DidIndexInfoType  st_DidIndexInfo;

    u1_RetVal               = E_NOT_OK;
    u1_Supported            = DCM_DID_NOT_SUPPORTED;
    u2_DidInfo              = Dcm_Dsp_SID22_u2DidInfo;
    st_DidIndexInfo         = Dcm_Dsp_SID22_stDidIndexInfo;

    /* Call Xxx_IsDidAvailable function */
    u1_RetAvailableFnc = Dcm_Dsp_DidMng_CallAvailableFnc( st_DidIndexInfo.u2DidIndex,
                                                          u2_DidInfo,
                                                          u1OpStatus,
                                                          &u1_Supported
                                                          );

    if( u1_RetAvailableFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        if( u1_Supported == (Dcm_DidSupportedType)DCM_DID_SUPPORTED )
        {
            u1_RetSupportedDid = Dcm_Dsp_DidMng_CheckSupportedDid( u2_DidInfo, DCM_DID_REQTYPE_READ, Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
            if( u1_RetSupportedDid == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID22_CheckConditionProc();
            }
            else
            {
                Dcm_Dsp_SID22_bDidReadSupInfo[Dcm_Dsp_SID22_u2DidSupIndexInfo] = (boolean)FALSE;
                u1_RetVal = (Std_ReturnType)E_OK;
            }
        }
        else
        {
            Dcm_Dsp_SID22_bDidReadSupInfo[Dcm_Dsp_SID22_u2DidSupIndexInfo] = (boolean)FALSE;
            u1_RetVal = (Std_ReturnType)E_OK;
        }
    }
    else if( u1_RetAvailableFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        ( void )Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID22_DIDAVAILABLE );              /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    return u1_RetVal;

}


#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_ReadDidDataProc                            */
/* Description   | Data is read from the request DID                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1OpStatus       :Operation Status                   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_ReadDidDataProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    uint32                                   u4_WriteBytePos;
    uint16                                   u2_RemainReadDidNum;
    uint16                                   u2_ReadDidCnt;
    uint16                                   u2_DidHightByte;
    uint16                                   u2_DidLowByte;
    uint16                                   u2_DidInfo;
    uint16                                   u2_ReqDidBytePos;
    uint16                                   u2_DidNumOfReqMsg;
    uint16                                   u2_DidToReadCnt;
    uint8                                    u1_NotifyOpStatus;
    Dcm_Main_ReturnCheckType                 u1_RetCheckValidDid;
    Std_ReturnType                           u1_RetVal;
    Std_ReturnType                           u1_RetReadDidDataFnc;
    Dcm_NegativeResponseCodeType             u1_ErrorCode;
    boolean                                  b_BreakFlag;
    boolean                                  b_RetChkReadDid;
    boolean                                  b_UserNotifyFlag;

    u1_RetVal               = E_OK;
    u1_NotifyOpStatus       = u1OpStatus;
    u2_RemainReadDidNum     = Dcm_P_u2Did_Read_Num_Per_Cycle;
    b_BreakFlag             = (boolean)FALSE;
    u1_ErrorCode            = DCM_DSP_SID22_INVALID_NRC_ZERO;
    u2_DidToReadCnt         = Dcm_Dsp_SID22_u2DidToReadCnt;
    u2_DidNumOfReqMsg       = Dcm_Dsp_SID22_u2DidNumOfReqMsg;

    for( u2_ReadDidCnt = u2_DidToReadCnt; u2_ReadDidCnt < u2_DidNumOfReqMsg; u2_ReadDidCnt++ )
    {
        u2_DidHightByte = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN );
        u2_DidLowByte   = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN ) + (uint16)1U;
        u2_DidInfo =  (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[u2_DidHightByte]) << DCM_DSP_SID22_DIDSHIFT )
                             | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[u2_DidLowByte]);
        Dcm_Dsp_SID22_u2DidInfo = u2_DidInfo;
        b_RetChkReadDid = Dcm_Dsp_SID22_bDidReadSupInfo[u2_DidToReadCnt];
        if( b_RetChkReadDid == (boolean)TRUE )
        {
            u1_RetCheckValidDid = Dcm_Dsp_SID22_CheckValidDidProc( (boolean)FALSE );
            if( u1_RetCheckValidDid == DCM_MAIN_E_CHECK_OK )
            {
                if( u1_NotifyOpStatus == (Dcm_OpStatusType)DCM_INITIAL )
                {
                    /* Write DID to response buffer */
                    u4_WriteBytePos = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    u2_ReqDidBytePos = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN );
                    Dcm_Dsp_Main_stMsgContext.resData[u4_WriteBytePos] = Dcm_Dsp_Main_stMsgContext.reqData[u2_ReqDidBytePos];
                    Dcm_Dsp_Main_stMsgContext.resData[u4_WriteBytePos + (uint8)1U] = Dcm_Dsp_Main_stMsgContext.reqData[u2_ReqDidBytePos + (uint8)1U];   /* no wrap around */
                    Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID22_DIDLEN;   /* no wrap around */
                }
                else
                {
                    /* None */
                }
                u1_RetReadDidDataFnc = Dcm_Dsp_SID22_ExecReadDidData( u1_NotifyOpStatus, u2_DidNumOfReqMsg, u2_DidToReadCnt, &u2_RemainReadDidNum, &u1_ErrorCode );
                if( u1_RetReadDidDataFnc == (Std_ReturnType)E_OK )
                {
                    u2_DidToReadCnt = (uint16)(u2_DidToReadCnt + (uint16)1U);
                    u1_NotifyOpStatus   = (Dcm_OpStatusType)DCM_INITIAL;
                }
                else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_PENDING )
                {
                    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
                    if( b_UserNotifyFlag != (boolean)TRUE )
                    {
                        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID22_READ_CYCLE ); /* no return check required */
                    }
                    else
                    {
                        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID22_READ_DID_DATA ); /* no return check required */
                    }
                    u1_RetVal = u1_RetReadDidDataFnc;
                    b_BreakFlag = (boolean)TRUE;
                }
                else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_FORCE_RCRRP )
                {
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING );
                    u1_RetVal   = u1_RetReadDidDataFnc;
                    b_BreakFlag = (boolean)TRUE;
                }
                else
                {
                    if( u1_ErrorCode != DCM_DSP_SID22_INVALID_NRC_ZERO )
                    {
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
                    }
                    b_BreakFlag = (boolean)TRUE;
                }
            }
            else
            {
                u2_DidToReadCnt = (uint16)(u2_DidToReadCnt + (uint16)1U);
                u1_NotifyOpStatus = (Dcm_OpStatusType)DCM_INITIAL;
            }
        }
        else
        {
            u2_DidToReadCnt = (uint16)(u2_DidToReadCnt + (uint16)1U);
            u1_NotifyOpStatus = (Dcm_OpStatusType)DCM_INITIAL;
        }
        if( b_BreakFlag == (boolean)FALSE )
        {
            /* None */
        }
        else
        {
            break;
        }
    }
    if( u2_DidToReadCnt == u2_DidNumOfReqMsg )
    {
        if( Dcm_Dsp_Main_stMsgContext.resDataLen > (uint32)0U )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    else
    {
        /* None */
    }
    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */


#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_ReadDidDataProc                            */
/* Description   | Data is read from the request DID                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1OpStatus       :Operation Status                   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_ReadDidDataProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetReadDidDataFnc;
    Dcm_Main_ReturnCheckType        u1_RetCheckValidDid;
    boolean                         b_RetChkReadDid;
    uint8                           u1_NotifyOpStatus;
    uint16                          u2_RemainReadDidNum;
    boolean                         b_BreakFlag;
    uint16                          u2_ReadDidCnt;
    uint16                          u2_DidHightByte;
    uint16                          u2_DidLowByte;
    uint16                          u2_DidInfo;
    uint16                          u2_ReqDidBytePos;
    uint32                          u4_WriteBytePos;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    uint16                          u2_DidNumOfReqMsg;
    uint16                          u2_DidToReadCnt;
    boolean                         b_StartPageFlag;
    boolean                         b_UserNotifyFlag;

    u1_RetVal               = E_OK;
    u1_NotifyOpStatus       = u1OpStatus;
    u2_RemainReadDidNum     = Dcm_P_u2Did_Read_Num_Per_Cycle;
    b_BreakFlag             = (boolean)FALSE;
    u1_ErrorCode            = DCM_DSP_SID22_INVALID_NRC_ZERO;
    b_StartPageFlag         = (boolean)FALSE;
    u2_DidToReadCnt         = Dcm_Dsp_SID22_u2DidToReadCnt;
    u2_DidNumOfReqMsg       = Dcm_Dsp_SID22_u2DidNumOfReqMsg;

    for( u2_ReadDidCnt = u2_DidToReadCnt; u2_ReadDidCnt < u2_DidNumOfReqMsg; u2_ReadDidCnt++ )
    {
        u2_DidHightByte = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN );
        u2_DidLowByte   = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN ) + (uint16)1U;
        u2_DidInfo =  (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[u2_DidHightByte]) << DCM_DSP_SID22_DIDSHIFT )
                             | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[u2_DidLowByte]);
        Dcm_Dsp_SID22_u2DidInfo = u2_DidInfo;
        b_RetChkReadDid = Dcm_Dsp_SID22_bDidReadSupInfo[u2_DidToReadCnt];
        if( b_RetChkReadDid == (boolean)TRUE )
        {
            u1_RetCheckValidDid = Dcm_Dsp_SID22_CheckValidDidProc( (boolean)FALSE );
            if( u1_RetCheckValidDid == DCM_MAIN_E_CHECK_OK )
            {
                if( u1_NotifyOpStatus == (Dcm_OpStatusType)DCM_INITIAL )
                {
                    /* Write DID to response buffer */
                    u4_WriteBytePos = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    u2_ReqDidBytePos = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN );
                    Dcm_Dsp_Main_stMsgContext.resData[u4_WriteBytePos] = Dcm_Dsp_Main_stMsgContext.reqData[u2_ReqDidBytePos];
                    Dcm_Dsp_Main_stMsgContext.resData[u4_WriteBytePos + (uint8)1U] = Dcm_Dsp_Main_stMsgContext.reqData[u2_ReqDidBytePos + (uint8)1U];   /* no wrap around */
                    Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID22_DIDLEN;   /* no wrap around */
                }
                else
                {
                    /* None */
                }

                u1_RetReadDidDataFnc = Dcm_Dsp_SID22_ExecReadDidData( u1_NotifyOpStatus, u2_DidNumOfReqMsg, u2_DidToReadCnt, &u2_RemainReadDidNum, &u1_ErrorCode );
                if( u1_RetReadDidDataFnc == (Std_ReturnType)E_OK )
                {
                    u2_DidToReadCnt = (uint16)(u2_DidToReadCnt + (uint16)1U);
                    u1_NotifyOpStatus   = (Dcm_OpStatusType)DCM_INITIAL;
                    /* Return Value E_OK has been already set in u1_RetVal */
                }
                else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_PENDING )
                {
                    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
                    if( b_UserNotifyFlag != (boolean)TRUE )
                    {
                        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID22_READ_CYCLE ); /* no return check required */
                    }
                    else
                    {
                        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID22_READ_DID_DATA ); /* no return check required */
                    }
                    u1_RetVal           = u1_RetReadDidDataFnc;
                    b_BreakFlag         = (boolean)TRUE;
                }
                else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_UPDATE_PAGE )
                {
                    b_StartPageFlag     = (boolean)TRUE;
                    /* Return Value E_OK has been already set in u1_RetVal */
                    b_BreakFlag         = (boolean)TRUE;
                }
                else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_FORCE_RCRRP )
                {
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING );
                    u1_RetVal           = u1_RetReadDidDataFnc;
                    b_BreakFlag         = (boolean)TRUE;
                }
                else
                {
                    /* u1_RetReadDidDataFnc == (Std_ReturnType)E_NOT_OK */
                    /* When return of Xxx_ReadDidData is abnormal , u1_ErrorCode will be DCM_DSP_SID22_INVALID_NRC_ZERO */
                    if( u1_ErrorCode != DCM_DSP_SID22_INVALID_NRC_ZERO )
                    {
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
                    }
                    b_BreakFlag         = (boolean)TRUE;
                }
            }
            else
            {
                u2_DidToReadCnt = (uint16)(u2_DidToReadCnt + (uint16)1U);
                u1_NotifyOpStatus = (Dcm_OpStatusType)DCM_INITIAL;
            }
        }
        else
        {
            u2_DidToReadCnt = (uint16)(u2_DidToReadCnt + (uint16)1U);
            u1_NotifyOpStatus = (Dcm_OpStatusType)DCM_INITIAL;
        }
        if( b_BreakFlag == (boolean)FALSE )
        {
            /* None */
        }
        else
        {
            break;
        }
    }
    if( u2_DidToReadCnt == u2_DidNumOfReqMsg )
    {
        if( Dcm_Dsp_Main_stMsgContext.resDataLen > (uint32)0U )
        {
            Dcm_Dsp_SID22_u2DidToReadCnt    = u2_DidNumOfReqMsg;
            Dcm_Dsp_SID22_u4ResDataLen      = Dcm_Dsp_Main_stMsgContext.resDataLen;
            b_StartPageFlag                 = (boolean)TRUE;
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    if( b_StartPageFlag == (boolean)TRUE )
    {
        Dcm_Dsp_SID22_StartPage();
    }
    else
    {
        /* None */
    }
    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */


#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_ReadDidDataUpdate                          */
/* Description   | Data is read from the request DID                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1OpStatus       :Operation Status                   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_ReadDidDataUpdate
(
    const Dcm_OpStatusType u1OpStatus
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ResData;
    uint32                          u4_RemainDataLen;
    uint32                          u4_RemainBuffLen;
    uint32                          u4_AdjustDataLen;
    uint32                          u4_Index;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetReadDidDataFnc;
    Dcm_Main_ReturnCheckType        u1_RetCheckValidDid;
    boolean                         b_RetChkReadDid;
    uint8                           u1_NotifyOpStatus;
    uint16                          u2_RemainReadDidNum;
    boolean                         b_BreakFlag;
    uint16                          u2_ReadDidCnt;
    uint16                          u2_DidHightByte;
    uint16                          u2_DidLowByte;
    uint16                          u2_DidInfo;
    uint16                          u2_ReqDidBytePos;
    uint32                          u4_WriteBytePos;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    uint16                          u2_DidNumOfReqMsg;
    uint16                          u2_DidToReadCnt;
    uint32                          u4_SendDataLen;
    boolean                         b_ProcessPageFlag;

    u1_RetVal               = E_OK;
    u1_NotifyOpStatus       = u1OpStatus;
    u2_RemainReadDidNum     = Dcm_P_u2Did_Read_Num_Per_Cycle;
    b_BreakFlag             = (boolean)FALSE;
    u1_ErrorCode            = DCM_DSP_SID22_INVALID_NRC_ZERO;
    b_ProcessPageFlag       = (boolean)FALSE;
    u2_DidToReadCnt         = Dcm_Dsp_SID22_u2DidToReadCnt;
    u2_DidNumOfReqMsg       = Dcm_Dsp_SID22_u2DidNumOfReqMsg;

    for( u2_ReadDidCnt = u2_DidToReadCnt; u2_ReadDidCnt < u2_DidNumOfReqMsg; u2_ReadDidCnt++ )
    {
        u2_DidHightByte = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN );
        u2_DidLowByte   = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN ) + (uint16)1U;
        u2_DidInfo =  (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[u2_DidHightByte]) << DCM_DSP_SID22_DIDSHIFT )
                             | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[u2_DidLowByte]);
        Dcm_Dsp_SID22_u2DidInfo = u2_DidInfo;
        b_RetChkReadDid = Dcm_Dsp_SID22_bDidReadSupInfo[u2_DidToReadCnt];
        if( b_RetChkReadDid == (boolean)TRUE )
        {
            u1_RetCheckValidDid = Dcm_Dsp_SID22_CheckValidDidProc( (boolean)FALSE );
            if( u1_RetCheckValidDid == DCM_MAIN_E_CHECK_OK )
            {
                if( u1_NotifyOpStatus == (Dcm_OpStatusType)DCM_INITIAL )
                {
                    /* Write DID to response buffer */
                    u4_WriteBytePos = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    u2_ReqDidBytePos = ( u2_DidToReadCnt * DCM_DSP_SID22_DIDLEN );
                    Dcm_Dsp_Main_stMsgContext.resData[u4_WriteBytePos] = Dcm_Dsp_Main_stMsgContext.reqData[u2_ReqDidBytePos];
                    Dcm_Dsp_Main_stMsgContext.resData[u4_WriteBytePos + (uint8)1U] = Dcm_Dsp_Main_stMsgContext.reqData[u2_ReqDidBytePos + (uint8)1U];   /* no wrap around */
                    Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID22_DIDLEN;   /* no wrap around */
                }
                else
                {
                    /* None */
                }

                u1_RetReadDidDataFnc = Dcm_Dsp_SID22_ExecReadDidData( u1_NotifyOpStatus, u2_DidNumOfReqMsg, u2_DidToReadCnt, &u2_RemainReadDidNum, &u1_ErrorCode );
                if( u1_RetReadDidDataFnc == (Std_ReturnType)E_OK )
                {
                    u2_DidToReadCnt = (uint16)(u2_DidToReadCnt + (uint16)1U);
                    u1_NotifyOpStatus   = (Dcm_OpStatusType)DCM_INITIAL;
                    /* Return Value E_OK has been already set in u1_RetVal */
                }
                else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_PENDING )
                {
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID22_UPDATEPAGE ); /* no return check required */
                    u1_RetVal           = u1_RetReadDidDataFnc;
                    b_BreakFlag         = (boolean)TRUE;
                }
                else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_UPDATE_PAGE )
                {
                    b_ProcessPageFlag   = (boolean)TRUE;
                    /* Return Value E_OK has been already set in u1_RetVal */
                    b_BreakFlag         = (boolean)TRUE;
                }
                else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_FORCE_RCRRP )
                {
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID22_UPDATERCRRP); /* no return check required */
                    u1_RetVal           = DCM_E_PENDING;
                    b_BreakFlag         = (boolean)TRUE;
                }
                else
                {
                    /*  u1_RetReadDidDataFnc == (Std_ReturnType)E_NOT_OK */
                    u1_RetVal           = (Std_ReturnType)E_NOT_OK;
                    b_BreakFlag         = (boolean)TRUE;
                    Dcm_Dsp_SID22_u2DidToReadCnt    = u2_DidNumOfReqMsg;
                }
            }
            else
            {
                u2_DidToReadCnt = (uint16)(u2_DidToReadCnt + (uint16)1U);
                u1_NotifyOpStatus = (Dcm_OpStatusType)DCM_INITIAL;
            }
        }
        else
        {
            u2_DidToReadCnt = (uint16)(u2_DidToReadCnt + (uint16)1U);
            u1_NotifyOpStatus = (Dcm_OpStatusType)DCM_INITIAL;
        }
        if( b_BreakFlag == (boolean)FALSE )
        {
            /* None */
        }
        else
        {
            break;
        }
    }
    if( u2_DidToReadCnt == u2_DidNumOfReqMsg )
    {
        /* Update the finished data number at reading completion. */
        Dcm_Dsp_SID22_u2DidToReadCnt    = u2_DidNumOfReqMsg;
        if( Dcm_Dsp_SID22_u4ResDataLen > Dcm_Dsp_Main_stMsgContext.resDataLen )
        {
            u4_RemainDataLen    = Dcm_Dsp_SID22_u4ResDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen; /* no wrap around */
            u4_RemainBuffLen    = Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen; /* no wrap around */
            u4_AdjustDataLen    = u4_RemainBuffLen;
            if( u4_RemainBuffLen > u4_RemainDataLen )
            {
                u4_AdjustDataLen = u4_RemainDataLen;
            }
            pt_ResData  = &(Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen]);
            for( u4_Index = (uint32)0U; u4_Index < u4_AdjustDataLen; u4_Index++ )
            {
                pt_ResData[u4_Index] = (uint8)0x00U;
            }
            Dcm_Dsp_Main_stMsgContext.resDataLen += u4_AdjustDataLen; /* no wrap around */
        }
        else
        {
            Dcm_Dsp_Main_stMsgContext.resDataLen    = Dcm_Dsp_SID22_u4ResDataLen;
        }
        b_ProcessPageFlag = (boolean)TRUE;
    }
    if( b_ProcessPageFlag == (boolean)TRUE )
    {
        u4_SendDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen;
        if( u4_SendDataLen != (uint32)0U )
        {
            Dcm_Dsp_MsgMaker_ProcessPage( u4_SendDataLen );
            Dcm_Dsp_SID22_u4ResDataLen -= u4_SendDataLen; /* no wrap around */
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_ExecReadDidData                            */
/* Description   | Execute Xxx_ReadDidData Callout Functions                */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1NotifyOpStatus      :Operation Status              */
/* Parameters    | [IN]u2DidNumOfReqMsg      :Number Of Dids in the Request */
/* Parameters    | [IN]u2DidToReadCnt        :Number Of Dids Already Read   */
/* Parameters    | [IN/OUT]pRemainReadDidNum :Remain ReadDidData Number     */
/* Parameters    | [OUT]pErrorCode           :Error Code for NRC            */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/*               | DCM_E_UPDATE_PAGE                                        */
/*               | E_NOT_OK                                                 */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
#if ( DCM_OBD_RANGE_DID_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_ExecReadDidData
(
    const uint8                                 u1NotifyOpStatus,
    const uint16                                u2DidNumOfReqMsg,
    const uint16                                u2DidToReadCnt,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA )   pRemainReadDidNum,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) pErrorCode
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ResData;
    Dcm_Dsp_SID22_DidIndexInfoType              st_DidIndexInfo;
    uint32                                      u4_ResMaxDataLen;
    uint32                                      u4_ResDataLenMax;
    uint32                                      u4_MaxDataLen;
    uint32                                      u4_ResDataLen;
    uint32                                      u4_PrevResDataLen;
    uint32                                      u4_DataBufferLen;
    uint16                                      u2_DidInfo;
    uint16                                      u2_DidCompReadCnt;
    Dcm_NegativeResponseCodeType                u1_LocalErrorCode;
    Std_ReturnType                              u1_RetReadDidDataFnc;
    Std_ReturnType                              u1_RetVal;

    u1_RetVal               = E_NOT_OK;
    u2_DidInfo              = Dcm_Dsp_SID22_u2DidInfo;
    pt_ResData              = &(Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen]);
    st_DidIndexInfo         = Dcm_Dsp_SID22_stDidIndexInfo;
    u4_ResDataLen           = 0U;
    u4_PrevResDataLen       = Dcm_Dsp_Main_stMsgContext.resDataLen;
    u4_DataBufferLen        = Dcm_Dsp_Main_stMsgContext.resMaxDataLen - u4_PrevResDataLen; /* no wrap around */
    u4_ResDataLenMax        = Dcm_P_Sid22_u4Resdatalen_Max;
    u2_DidCompReadCnt       = u2DidToReadCnt;
    u1_LocalErrorCode       = DCM_DSP_SID22_INVALID_NRC_ZERO;
    *pErrorCode             = DCM_DSP_SID22_INVALID_NRC_ZERO;

    if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
    {
        /* Call Xxx_ReadDidData function */
        u1_RetReadDidDataFnc = Dcm_Dsp_DidMng_CallReadDidFnc( st_DidIndexInfo.u2DidIndex, u2_DidInfo, pt_ResData, u1NotifyOpStatus, u4_DataBufferLen, &u4_ResDataLen, &u1_LocalErrorCode );
    }
    else
    {
        /* Call Xxx_ReadDidData function */
        u1_RetReadDidDataFnc = Dcm_Dsp_DidMng_CallReadDynDidFnc( st_DidIndexInfo.u2DidIndex, pt_ResData, u1NotifyOpStatus, u4_DataBufferLen, &u4_ResDataLen, &u1_LocalErrorCode, pRemainReadDidNum );
    }
    if( u1_RetReadDidDataFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
        {
            (*pRemainReadDidNum) = (uint16)((*pRemainReadDidNum) - (uint16)1U);
        }
        Dcm_Dsp_Main_stMsgContext.resDataLen += u4_ResDataLen; /* no wrap around */
        u4_ResMaxDataLen    = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
        if( u4_ResMaxDataLen < u4_ResDataLenMax )    /* MISRA DEVIATION */
        {
            u4_MaxDataLen = u4_ResMaxDataLen;    /* MISRA DEVIATION */
        }
        else
        {
            u4_MaxDataLen = u4_ResDataLenMax;
        }
        if( Dcm_Dsp_Main_stMsgContext.resDataLen <= u4_MaxDataLen )
        {
            u2_DidCompReadCnt = (uint16)(u2_DidCompReadCnt + (uint16)1U);
            if( u2_DidCompReadCnt < u2DidNumOfReqMsg )
            {
                if( *pRemainReadDidNum == DCM_DSP_SID22_LOOP_CNT_NUM_ZERO )
                {
                    u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
                }
                else
                {
                    u1_RetVal = (Std_ReturnType)E_OK;
                }
            }
            else
            {
                u1_RetVal = (Std_ReturnType)E_OK;
            }
        }
        else
        {
            /* None */
        }
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)E_NOT_OK )
    {
        *pErrorCode = u1_LocalErrorCode;
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        Dcm_Dsp_Main_stMsgContext.resDataLen += u4_ResDataLen; /* no wrap around */
        u4_ResMaxDataLen    = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
        if( u4_ResMaxDataLen < u4_ResDataLenMax )    /* MISRA DEVIATION */
        {
            u4_MaxDataLen = u4_ResMaxDataLen;    /* MISRA DEVIATION */
        }
        else
        {
            u4_MaxDataLen = u4_ResDataLenMax;
        }
        if( Dcm_Dsp_Main_stMsgContext.resDataLen <= u4_MaxDataLen )
        {
            u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
        }
        else
        {
            /* None */
        }
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_FORCE_RCRRP )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        Dcm_Dsp_Main_stMsgContext.resDataLen += u4_ResDataLen; /* no wrap around */
        u4_ResMaxDataLen    = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
        if( u4_ResMaxDataLen < u4_ResDataLenMax )    /* MISRA DEVIATION */
        {
            u4_MaxDataLen = u4_ResMaxDataLen;    /* MISRA DEVIATION */
        }
        else
        {
            u4_MaxDataLen = u4_ResDataLenMax;
        }
        if( Dcm_Dsp_Main_stMsgContext.resDataLen <= u4_MaxDataLen )
        {
            u1_RetVal = (Std_ReturnType)DCM_E_FORCE_RCRRP;
        }
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    switch( u1_RetVal )
    {
        case DCM_E_PENDING:
        case DCM_E_FORCE_RCRRP:
            /* DidToReadCnt set for next cycle */
            Dcm_Dsp_SID22_u2DidToReadCnt    = u2_DidCompReadCnt;
            break;
        default:
            /* no process */
            break;
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_OFF */
#if ( DCM_OBD_RANGE_DID_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_ExecReadDidData
(
    const uint8                                 u1NotifyOpStatus,
    const uint16                                u2DidNumOfReqMsg,
    const uint16                                u2DidToReadCnt,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA )   pRemainReadDidNum,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) pErrorCode
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ResData;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ObdResData;
    Dcm_Dsp_SID22_DidIndexInfoType              st_DidIndexInfo;
    uint32                                      u4_ResMaxDataLen;
    uint32                                      u4_ResDataLenMax;
    uint32                                      u4_MaxDataLen;
    uint32                                      u4_ResDataLen;
    uint32                                      u4_ObdResDataLen;
    uint32                                      u4_PrevResDataLen;
    uint32                                      u4_DataBufferLen;
    uint32                                      u4_ObdDataBufferLen;
    uint16                                      u2_DidInfo;
    uint16                                      u2_DidCompReadCnt;
    Dcm_NegativeResponseCodeType                u1_LocalErrorCode;
    Std_ReturnType                              u1_RetReadDidDataFnc;
    Std_ReturnType                              u1_RetVal;

    u1_RetVal               = E_NOT_OK;
    u2_DidInfo              = Dcm_Dsp_SID22_u2DidInfo;
    pt_ResData              = &(Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen]);
    st_DidIndexInfo         = Dcm_Dsp_SID22_stDidIndexInfo;
    u4_ResDataLen           = (uint32)0U;
    u4_PrevResDataLen       = Dcm_Dsp_Main_stMsgContext.resDataLen;
    u4_DataBufferLen        = Dcm_Dsp_Main_stMsgContext.resMaxDataLen - u4_PrevResDataLen; /* no wrap around */
    u4_ResDataLenMax        = Dcm_P_Sid22_u4Resdatalen_Max;
    u2_DidCompReadCnt       = u2DidToReadCnt;
    u1_LocalErrorCode       = DCM_DSP_SID22_INVALID_NRC_ZERO;
    *pErrorCode             = DCM_DSP_SID22_INVALID_NRC_ZERO;

    if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
    {
        /* Call Xxx_ReadDidData function */
        u1_RetReadDidDataFnc = Dcm_Dsp_DidMng_CallReadDidFnc( st_DidIndexInfo.u2DidIndex, u2_DidInfo, pt_ResData, u1NotifyOpStatus, u4_DataBufferLen, &u4_ResDataLen, &u1_LocalErrorCode );
    }
    else if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_OBDDID )
    {
        u4_ObdDataBufferLen = (uint32)(u4_DataBufferLen + (uint32)DCM_DSP_SID22_DIDLEN); /* no wrap around */
        u4_ObdResDataLen    = (uint32)0U;
        pt_ObdResData       = &(Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen - (uint32)DCM_DSP_SID22_DIDLEN]); /* no wrap around */
        /* Call Xxx_ReadData, Dem_DcmGetNumTIDsOfOBDMID, Dem_DcmGetDTRData, Dem_DcmGetInfoTypeValuexx, Xxx_GetInfotypeValueDat function */
        u1_RetReadDidDataFnc = Dcm_Dsp_DidMng_OBD_CallReadObdDidFnc( u2_DidInfo, u1NotifyOpStatus, u4_ObdDataBufferLen, pt_ObdResData, &u4_ObdResDataLen, &u1_LocalErrorCode );
        if( u1_RetReadDidDataFnc == (Std_ReturnType)E_OK )
        {
            if( u4_ObdResDataLen <= (uint32)DCM_DSP_SID22_DIDLEN )
            {
                /* delete DID */
                Dcm_Dsp_Main_stMsgContext.resDataLen -= (uint32)DCM_DSP_SID22_DIDLEN; /* no wrap around */
            }
            else
            {
                u4_ResDataLen = (uint32)(u4_ObdResDataLen - (uint32)DCM_DSP_SID22_DIDLEN); /* no wrap around */
            }
        }
    }
    else
    {
        /* Call Xxx_ReadDidData function */
        u1_RetReadDidDataFnc = Dcm_Dsp_DidMng_CallReadDynDidFnc( st_DidIndexInfo.u2DidIndex, pt_ResData, u1NotifyOpStatus, u4_DataBufferLen, &u4_ResDataLen, &u1_LocalErrorCode, pRemainReadDidNum );
    }
    if( u1_RetReadDidDataFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        if( st_DidIndexInfo.u1KindOfTable != DCM_DSP_DIDMNG_DID_DYNAMIC )
        {
            (*pRemainReadDidNum) = (uint16)((*pRemainReadDidNum) - (uint16)1U);
        }
        Dcm_Dsp_Main_stMsgContext.resDataLen += u4_ResDataLen; /* no wrap around */
        u4_ResMaxDataLen    = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
        if( u4_ResMaxDataLen < u4_ResDataLenMax )    /* MISRA DEVIATION */
        {
            u4_MaxDataLen = u4_ResMaxDataLen;    /* MISRA DEVIATION */
        }
        else
        {
            u4_MaxDataLen = u4_ResDataLenMax;
        }
        if( Dcm_Dsp_Main_stMsgContext.resDataLen <= u4_MaxDataLen )
        {
            u2_DidCompReadCnt = (uint16)(u2_DidCompReadCnt + (uint16)1U);
            if( u2_DidCompReadCnt < u2DidNumOfReqMsg )
            {
                if( *pRemainReadDidNum == DCM_DSP_SID22_LOOP_CNT_NUM_ZERO )
                {
                    u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
                }
                else
                {
                    u1_RetVal = (Std_ReturnType)E_OK;
                }
            }
            else
            {
                u1_RetVal = (Std_ReturnType)E_OK;
            }
        }
        else
        {
            /* None */
        }
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)E_NOT_OK )
    {
        *pErrorCode = u1_LocalErrorCode;
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        Dcm_Dsp_Main_stMsgContext.resDataLen += u4_ResDataLen; /* no wrap around */
        u4_ResMaxDataLen    = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
        if( u4_ResMaxDataLen < u4_ResDataLenMax )    /* MISRA DEVIATION */
        {
            u4_MaxDataLen = u4_ResMaxDataLen;    /* MISRA DEVIATION */
        }
        else
        {
            u4_MaxDataLen = u4_ResDataLenMax;
        }
        if( Dcm_Dsp_Main_stMsgContext.resDataLen <= u4_MaxDataLen )
        {
            u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
        }
        else
        {
            /* None */
        }
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_FORCE_RCRRP )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        Dcm_Dsp_Main_stMsgContext.resDataLen += u4_ResDataLen; /* no wrap around */
        u4_ResMaxDataLen    = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
        if( u4_ResMaxDataLen < u4_ResDataLenMax )    /* MISRA DEVIATION */
        {
            u4_MaxDataLen = u4_ResMaxDataLen;    /* MISRA DEVIATION */
        }
        else
        {
            u4_MaxDataLen = u4_ResDataLenMax;
        }
        if( Dcm_Dsp_Main_stMsgContext.resDataLen <= u4_MaxDataLen )
        {
            u1_RetVal = (Std_ReturnType)DCM_E_FORCE_RCRRP;
        }
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    switch( u1_RetVal )
    {
        case DCM_E_PENDING:
        case DCM_E_FORCE_RCRRP:
            /* DidToReadCnt set for next cycle */
            Dcm_Dsp_SID22_u2DidToReadCnt    = u2_DidCompReadCnt;
            break;
        default:
            /* no process */
            break;
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_OBD_RANGE_DID_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_ExecReadDidData
(
    const uint8                                 u1NotifyOpStatus,
    const uint16                                u2DidNumOfReqMsg,
    const uint16                                u2DidToReadCnt,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA )   pRemainReadDidNum,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) pErrorCode
)
{
    Std_ReturnType                              u1_RetVal;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ResData;
    Dcm_Dsp_SID22_DidIndexInfoType              st_DidIndexInfo;
    uint32                                      u4_ResDataLen;
    uint32                                      u4_PrevResDataLen;
    uint32                                      u4_DataBufferLen;
    Std_ReturnType                              u1_RetReadDidDataFnc;
    uint16                                      u2_DidInfo;
    uint16                                      u2_DidCompReadCnt;
    Dcm_NegativeResponseCodeType                u1_LocalErrorCode;

    u1_RetVal               = E_NOT_OK;
    u2_DidInfo              = Dcm_Dsp_SID22_u2DidInfo;
    pt_ResData              = &(Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen]);
    st_DidIndexInfo         = Dcm_Dsp_SID22_stDidIndexInfo;
    u4_ResDataLen           = (uint32)0U;
    u4_PrevResDataLen       = Dcm_Dsp_Main_stMsgContext.resDataLen;
    u4_DataBufferLen        = Dcm_Dsp_Main_stMsgContext.resMaxDataLen - u4_PrevResDataLen;  /* no wrap around */
    u2_DidCompReadCnt       = u2DidToReadCnt;
    u1_LocalErrorCode       = DCM_DSP_SID22_INVALID_NRC_ZERO;
    *pErrorCode             = DCM_DSP_SID22_INVALID_NRC_ZERO;

    if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
    {
        /* Call Xxx_ReadDidData function */
        u1_RetReadDidDataFnc = Dcm_Dsp_DidMng_CallReadDidFnc( st_DidIndexInfo.u2DidIndex, u2_DidInfo, pt_ResData, u1NotifyOpStatus, u4_DataBufferLen, &u4_ResDataLen, &u1_LocalErrorCode );
    }
    else
    {
        /* Call Xxx_ReadDidData function */
        u1_RetReadDidDataFnc = Dcm_Dsp_DidMng_CallReadDynDidFnc( st_DidIndexInfo.u2DidIndex, pt_ResData, u1NotifyOpStatus, u4_DataBufferLen, &u4_ResDataLen, &u1_LocalErrorCode, pRemainReadDidNum );
    }
    if( u1_RetReadDidDataFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
        {
            (*pRemainReadDidNum) = (uint16)((*pRemainReadDidNum) - (uint16)1U);
        }
        if( u4_DataBufferLen >= u4_ResDataLen )
        {
            Dcm_Dsp_Main_stMsgContext.resDataLen   += u4_ResDataLen;    /* no wrap around */
            u2_DidCompReadCnt = (uint16)(u2_DidCompReadCnt + (uint16)1U);
            if( ( u4_DataBufferLen - u4_ResDataLen ) >= DCM_DSP_SID22_PB_MIN_BLANK )
            {
                if( u2_DidCompReadCnt < u2DidNumOfReqMsg )
                {
                    if( *pRemainReadDidNum == DCM_DSP_SID22_LOOP_CNT_NUM_ZERO )
                    {
                        u1_RetVal       = DCM_E_PENDING;
                    }
                    else
                    {
                        u1_RetVal       = E_OK;
                    }
                }
                else
                {
                    u1_RetVal           = E_OK;
                }
            }
            else
            {
                /* Finish the reading processing of current cycle. */
                u1_RetVal               = DCM_E_UPDATE_PAGE;
            }
        }
        else
        {
            /* The processing end by the abnormal detection. */
            /* None */
        }
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        *pErrorCode = u1_LocalErrorCode;
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
        {
            u1_RetVal                   = DCM_E_PENDING;
        }
        else
        {
            if( u4_DataBufferLen >= u4_ResDataLen )
            {
                Dcm_Dsp_Main_stMsgContext.resDataLen   += u4_ResDataLen;    /* no wrap around */
                if( u4_DataBufferLen > u4_ResDataLen )
                {
                    u1_RetVal           = DCM_E_PENDING;
                }
                else
                {
                    /* Call ProcessPage */
                    u1_RetVal           = DCM_E_UPDATE_PAGE;
                }
            }
            else
            {
                /* None */
            }
        }
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_UPDATE_PAGE )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        if( u4_DataBufferLen >= u4_ResDataLen )
        {
            Dcm_Dsp_Main_stMsgContext.resDataLen   += u4_ResDataLen;    /* no wrap around */
            /* Call ProcessPage */
            u1_RetVal                   = DCM_E_UPDATE_PAGE;
        }
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_FORCE_RCRRP )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
        {
            u1_RetVal                   = DCM_E_FORCE_RCRRP;
        }
        else
        {
            if( u4_DataBufferLen >= u4_ResDataLen )
            {
                Dcm_Dsp_Main_stMsgContext.resDataLen   += u4_ResDataLen;    /* no wrap around */
                u1_RetVal           = DCM_E_FORCE_RCRRP;
            }
            else
            {
                /* None */
            }
        }
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    switch( u1_RetVal )
    {
        case DCM_E_PENDING:
        case DCM_E_UPDATE_PAGE:
        case DCM_E_FORCE_RCRRP:
            /* DidToReadCnt set for next cycle */
            Dcm_Dsp_SID22_u2DidToReadCnt    = u2_DidCompReadCnt;
            break;
        default:
            /* no process */
            break;
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_OFF */
#if ( DCM_OBD_RANGE_DID_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_ExecReadDidData
(
    const uint8                                 u1NotifyOpStatus,
    const uint16                                u2DidNumOfReqMsg,
    const uint16                                u2DidToReadCnt,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA )   pRemainReadDidNum,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) pErrorCode
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ResData;
    Dcm_Dsp_SID22_DidIndexInfoType              st_DidIndexInfo;
    uint32                                      u4_ResDataLen;
    uint32                                      u4_PrevResDataLen;
    uint32                                      u4_DataBufferLen;
    uint16                                      u2_DidInfo;
    uint16                                      u2_DidCompReadCnt;
    Dcm_NegativeResponseCodeType                u1_LocalErrorCode;
    Std_ReturnType                              u1_RetReadDidDataFnc;
    Std_ReturnType                              u1_RetVal;
    boolean                                     b_NextOpInit;

    u1_RetVal               = E_NOT_OK;
    b_NextOpInit            = (boolean)FALSE;
    u2_DidInfo              = Dcm_Dsp_SID22_u2DidInfo;
    pt_ResData              = &(Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen]);
    st_DidIndexInfo         = Dcm_Dsp_SID22_stDidIndexInfo;
    u4_ResDataLen           = (uint32)0U;
    u4_PrevResDataLen       = Dcm_Dsp_Main_stMsgContext.resDataLen;
    u4_DataBufferLen        = Dcm_Dsp_Main_stMsgContext.resMaxDataLen - u4_PrevResDataLen;  /* no wrap around */
    u2_DidCompReadCnt       = u2DidToReadCnt;
    u1_LocalErrorCode       = DCM_DSP_SID22_INVALID_NRC_ZERO;
    *pErrorCode             = DCM_DSP_SID22_INVALID_NRC_ZERO;

    if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
    {
        /* Call Xxx_ReadDidData function */
        u1_RetReadDidDataFnc = Dcm_Dsp_DidMng_CallReadDidFnc( st_DidIndexInfo.u2DidIndex, u2_DidInfo, pt_ResData, u1NotifyOpStatus, u4_DataBufferLen, &u4_ResDataLen, &u1_LocalErrorCode );
    }
    else if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_OBDDID )
    {
        u1_RetReadDidDataFnc = Dcm_Dsp_SID22_CallReadObdDid( u2_DidInfo, u1NotifyOpStatus, u4_DataBufferLen, pt_ResData, &u4_ResDataLen, &u1_LocalErrorCode, &b_NextOpInit );
    }
    else
    {
        /* Call Xxx_ReadDidData function */
        u1_RetReadDidDataFnc = Dcm_Dsp_DidMng_CallReadDynDidFnc( st_DidIndexInfo.u2DidIndex, pt_ResData, u1NotifyOpStatus, u4_DataBufferLen, &u4_ResDataLen, &u1_LocalErrorCode, pRemainReadDidNum );
    }
    if( u1_RetReadDidDataFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        if( st_DidIndexInfo.u1KindOfTable != DCM_DSP_DIDMNG_DID_DYNAMIC )
        {
            (*pRemainReadDidNum) = (uint16)((*pRemainReadDidNum) - (uint16)1U);
        }
        if( u4_DataBufferLen >= u4_ResDataLen )
        {
            Dcm_Dsp_Main_stMsgContext.resDataLen   += u4_ResDataLen;    /* no wrap around */
            u2_DidCompReadCnt = (uint16)(u2_DidCompReadCnt + (uint16)1U);
            if( ( u4_DataBufferLen - u4_ResDataLen ) >= DCM_DSP_SID22_PB_MIN_BLANK )
            {
                if( u2_DidCompReadCnt < u2DidNumOfReqMsg )
                {
                    if( *pRemainReadDidNum == DCM_DSP_SID22_LOOP_CNT_NUM_ZERO )
                    {
                        u1_RetVal   = DCM_E_PENDING;
                    }
                    else
                    {
                        u1_RetVal   = E_OK;
                    }
                }
                else
                {
                    u1_RetVal       = E_OK;
                }
            }
            else
            {
                u1_RetVal           = DCM_E_UPDATE_PAGE;
            }
        }
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        *pErrorCode = u1_LocalErrorCode;
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
        {
            u1_RetVal               = DCM_E_PENDING;
        }
        else
        {
            if( u4_DataBufferLen >= u4_ResDataLen )
            {
                Dcm_Dsp_Main_stMsgContext.resDataLen    += u4_ResDataLen;    /* no wrap around */
                if( u4_DataBufferLen > u4_ResDataLen )
                {
                    u1_RetVal       = DCM_E_PENDING;
                }
                else
                {
                    u1_RetVal       = DCM_E_UPDATE_PAGE;
                }
            }
        }
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_UPDATE_PAGE )
    {
        if( b_NextOpInit == (boolean)TRUE )
        {
            /* The next process starts from writing the DID. */
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
        else
        {
            /* The next process is executed from the continuation of the data writing. */
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        }
        if( u4_DataBufferLen >= u4_ResDataLen )
        {
            Dcm_Dsp_Main_stMsgContext.resDataLen    += u4_ResDataLen;    /* no wrap around */
            u1_RetVal               = DCM_E_UPDATE_PAGE;
        }
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_FORCE_RCRRP )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
        {
            u1_RetVal               = DCM_E_FORCE_RCRRP;
        }
        else
        {
            if( u4_DataBufferLen >= u4_ResDataLen )
            {
                Dcm_Dsp_Main_stMsgContext.resDataLen    += u4_ResDataLen;    /* no wrap around */
                u1_RetVal           = DCM_E_FORCE_RCRRP;
            }
        }
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    switch( u1_RetVal )
    {
        case DCM_E_PENDING:
        case DCM_E_UPDATE_PAGE:
        case DCM_E_FORCE_RCRRP:
            /* DidToReadCnt set for next cycle */
            Dcm_Dsp_SID22_u2DidToReadCnt    = u2_DidCompReadCnt;
            break;
        default:
            /* no process */
            break;
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_ReadDataLenProc                            */
/* Description   | DID data length acquisition processing                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1OpStatus       :Operation Status                   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_OBD_RANGE_DID_USE == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_ReadDataLenProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType          u1_RetVal;
    uint16                  u2_DidInfo;
    uint32                  u4_DidDataLen;
    uint32                  u4_ResDataLen;
    Dcm_Dsp_SID22_DidIndexInfoType      st_DidIndexInfo;
    boolean                 b_ReadSuccessFlag;

    u2_DidInfo              = Dcm_Dsp_SID22_u2DidInfo;
    st_DidIndexInfo         = Dcm_Dsp_SID22_stDidIndexInfo;
    b_ReadSuccessFlag       = (boolean)FALSE;

    if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
    {
        u1_RetVal = Dcm_Dsp_DidMng_CallDataLengthFnc( st_DidIndexInfo.u2DidIndex,
                                                      u2_DidInfo,
                                                      u1OpStatus,
                                                      &u4_DidDataLen
                                                      );
    }
    else
    {
        u1_RetVal = Dcm_Dsp_DidMng_GetDynDidDataLen( st_DidIndexInfo.u2DidIndex,
                                                     &u4_DidDataLen
                                                     );
    }

    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        if( u4_DidDataLen <= ( DCM_DSP_SID22_VALUE_MAX_U4 - DCM_DSP_SID22_DIDLEN ) )
        {
            u4_ResDataLen = DCM_DSP_SID22_DIDLEN + u4_DidDataLen;
            if( u4_ResDataLen <= ( DCM_DSP_SID22_VALUE_MAX_U4 - Dcm_Dsp_SID22_u4ResDataLen ) )
            {
                Dcm_Dsp_SID22_u4ResDataLen += u4_ResDataLen;
                b_ReadSuccessFlag = (boolean)TRUE;
            }
        }

        if( b_ReadSuccessFlag == (boolean)FALSE )
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG );
            u1_RetVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    else if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        ( void )Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID22_RANGE_DATA_LEN );            /* no return check required */
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_OFF */
#if ( DCM_OBD_RANGE_DID_USE == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_ReadDataLenProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType          u1_RetVal;
    uint16                  u2_DidInfo;
    uint32                  u4_DidDataLen;
    uint32                  u4_ResDataLen;
    Dcm_Dsp_SID22_DidIndexInfoType      st_DidIndexInfo;
    boolean                 b_ReadSuccessFlag;

    u2_DidInfo              = Dcm_Dsp_SID22_u2DidInfo;
    st_DidIndexInfo         = Dcm_Dsp_SID22_stDidIndexInfo;
    b_ReadSuccessFlag       = (boolean)FALSE;

    if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
    {
        u1_RetVal = Dcm_Dsp_DidMng_CallDataLengthFnc( st_DidIndexInfo.u2DidIndex,
                                                      u2_DidInfo,
                                                      u1OpStatus,
                                                      &u4_DidDataLen
                                                      );
    }
    else if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_OBDDID )
    {
        u1_RetVal = Dcm_Dsp_DidMng_OBD_GetObdDidDataLen( u2_DidInfo,
                                                     &u4_DidDataLen
                                                     );
    }
    else
    {
        u1_RetVal = Dcm_Dsp_DidMng_GetDynDidDataLen( st_DidIndexInfo.u2DidIndex,
                                                     &u4_DidDataLen
                                                     );
    }

    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        if( u4_DidDataLen <= ( DCM_DSP_SID22_VALUE_MAX_U4 - DCM_DSP_SID22_DIDLEN ) )
        {
            u4_ResDataLen = DCM_DSP_SID22_DIDLEN + u4_DidDataLen;
            if( u4_ResDataLen <= ( DCM_DSP_SID22_VALUE_MAX_U4 - Dcm_Dsp_SID22_u4ResDataLen ) )
            {
                Dcm_Dsp_SID22_u4ResDataLen += u4_ResDataLen;
                b_ReadSuccessFlag = (boolean)TRUE;
            }
        }

        if( b_ReadSuccessFlag == (boolean)FALSE )
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG );
            u1_RetVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    else if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_OBDDID )
        {
            Dcm_Dsp_SID22_bDidReadSupInfo[Dcm_Dsp_SID22_u2DidSupIndexInfo] = (boolean)FALSE;
            u1_RetVal = (Std_ReturnType)E_OK;
        }
    }
    else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        ( void )Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID22_RANGE_DATA_LEN );            /* no return check required */
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_CheckConditionProc                         */
/* Description   | Check whether the prerequisite is satisfied for          */
/*               | the requested DID                                        */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_CheckConditionProc
(
    void
)
{

    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkSes;
    Std_ReturnType                  u1_RetChkSec;
    Std_ReturnType                  u1_RetChkModeRule;
    Dcm_SesCtrlType                 u1_SesCtrlType;
    Dcm_SecLevelType                u1_SecLevel;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    Dcm_Dsp_SID22_DidIndexInfoType  st_DidIndexInfo;

    u1_SesCtrlType          = DCM_DEFAULT_SESSION;
    u1_SecLevel             = DCM_SEC_LEV_LOCKED;
    u1_ErrorCode            = DCM_DSP_SID22_INVALID_NRC_ZERO;

    u1_RetVal       = E_NOT_OK;
    st_DidIndexInfo = Dcm_Dsp_SID22_stDidIndexInfo;

    ( void )Dcm_GetSesCtrlType( &u1_SesCtrlType );      /* no return check required */

    u1_RetChkSes = Dcm_Dsp_DidMng_ChkDidInfo( st_DidIndexInfo.u2DidIndex, st_DidIndexInfo.u1KindOfTable, DCM_DSP_DIDMNG_CHECK_READ_SES, u1_SesCtrlType );

    if( u1_RetChkSes == (Std_ReturnType)E_OK )
    {
        ( void )Dcm_GetSecurityLevel( &u1_SecLevel );   /* no return check required */
        u1_RetChkSec = Dcm_Dsp_DidMng_ChkDidInfo( st_DidIndexInfo.u2DidIndex, st_DidIndexInfo.u1KindOfTable, DCM_DSP_DIDMNG_CHECK_READ_SEC, u1_SecLevel );

        if( u1_RetChkSec == (Std_ReturnType)E_OK )
        {
            if( st_DidIndexInfo.u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
            {
                u1_RetChkModeRule = Dcm_Dsp_DidMng_CallModeRuleFnc( st_DidIndexInfo.u2DidIndex, DCM_DSP_DIDMNG_CHECK_READ_MR, Dcm_Dsp_SID22_u2DidInfo, &u1_ErrorCode );
            }
            else
            {
                u1_RetChkModeRule = Dcm_Dsp_DidMng_DynDidModeRuleFnc( st_DidIndexInfo.u2DidIndex, DCM_DSP_DIDMNG_CHECK_READ_MR, &u1_ErrorCode );

            }
            if( u1_RetChkModeRule == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID22_ReadDataLenProc( DCM_INITIAL );
            }
            else if( u1_RetChkModeRule == (Std_ReturnType)E_NOT_OK )
            {
                if( u1_ErrorCode != DCM_DSP_SID22_INVALID_NRC_ZERO )
                {
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
                }
                else
                {
                    /* None */
                }
            }
            else
            {
                /* None */
            }

        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_SECURITYACCESSDENIED );
        }
    }
    else
    {
        Dcm_Dsp_SID22_bDidReadSupInfo[Dcm_Dsp_SID22_u2DidSupIndexInfo] = (boolean)FALSE;
        u1_RetVal = (Std_ReturnType)E_OK;
    }

    return u1_RetVal;
}
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_CheckValidDidProc                          */
/* Description   | Check if the DIDRange table has a valid DID              */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               | DCM_MAIN_E_CHECK_OK                                      */
/*               | DCM_MAIN_E_CHECK_NOT_OK                                  */
/*               | DCM_MAIN_E_INVALID_CONFIG                                */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_OBD_RANGE_DID_USE == STD_OFF )
static FUNC(Dcm_Main_ReturnCheckType,DCM_CODE) Dcm_Dsp_SID22_CheckValidDidProc
(
    boolean b_SupportEnabledDid
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkDynamicDid;
    Std_ReturnType                  u1_RetSupportedDid;
    Dcm_Main_ReturnCheckType        u1_RetIndividualDid;
    Dcm_Main_ReturnCheckType        u1_RetDidRange;
    boolean                         b_IndividualDid;
    boolean                         b_ChkDynamicExe;
    uint16                          u2_IndividualDidIndex;
    uint16                          u2_RangeIndex;
    uint8                           u1_IndividualDidCRWSupport;
    uint8                           u1_CRWSupport;
    uint8                           u1_ChkReadSupport;
    uint8                           u1_NumOfSourceDid;
    uint16                          u2_DidInfo;
    uint16                          u2_DynamicIndex;

    u1_RetVal       = DCM_MAIN_E_CHECK_NOT_OK;
    b_IndividualDid = (boolean)FALSE;
    u2_DidInfo      = Dcm_Dsp_SID22_u2DidInfo;
    u2_IndividualDidIndex       = 0U;
    u1_IndividualDidCRWSupport  = 0U;
    u2_RangeIndex   = 0U;
    u1_CRWSupport   = 0U;
    u1_NumOfSourceDid   = 0U;
    u2_DynamicIndex     = 0U;

    /* Check DID Support IndividualDID */
    u1_RetIndividualDid = Dcm_Dsp_DidMng_ChkDid( u2_DidInfo,
                                                 DCM_DSP_DIDMNG_DID,
                                                 &u2_IndividualDidIndex,
                                                 &u1_IndividualDidCRWSupport
                                                 );

    if( u1_RetIndividualDid == DCM_MAIN_E_CHECK_OK )
    {
        u1_ChkReadSupport = u1_IndividualDidCRWSupport & DCM_DSP_DIDMNG_READ_ONLY_DYN;

        if( u1_ChkReadSupport == DCM_DSP_DIDMNG_READ_ONLY_DYN )
        {
            if( b_SupportEnabledDid == (boolean)TRUE )
            {
                u1_RetSupportedDid = Dcm_Dsp_DidMng_CheckSupportedDid( u2_DidInfo, DCM_DID_REQTYPE_READ, Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
                if( u1_RetSupportedDid == (Std_ReturnType)E_OK )
                {
                    b_ChkDynamicExe = (boolean)TRUE;
                }
                else
                {
                    b_ChkDynamicExe = (boolean)FALSE;
                    b_IndividualDid = (boolean)TRUE;
                }
            }
            else
            {
                b_ChkDynamicExe = (boolean)TRUE;
            }

            if( b_ChkDynamicExe == (boolean)TRUE )
            {
                u1_RetChkDynamicDid = Dcm_Dsp_DidMng_ChkDynamic( u2_DidInfo, &u1_NumOfSourceDid, &u2_DynamicIndex );

                if( u1_RetChkDynamicDid == (Std_ReturnType)E_OK )
                {
                    if( u1_NumOfSourceDid > DCM_DSP_SID22_DYN_DID_NOT_DEF )
                    {
                        Dcm_Dsp_SID22_stDidIndexInfo.u1KindOfTable = DCM_DSP_DIDMNG_DID_DYNAMIC;
                        Dcm_Dsp_SID22_stDidIndexInfo.u2DidIndex    = u2_DynamicIndex;

                        b_IndividualDid = (boolean)TRUE;
                        u1_RetVal = DCM_MAIN_E_CHECK_OK;

                    }
                    else
                    {
                        /* None */
                    }
                }
            }
            else
            {
                /* None */
            }
        }
        else
        {
            /* None */
        }
    }
    else
    {
        /* None */
    }

    if( b_IndividualDid == (boolean)FALSE)
    {
        /* Check DID Support Range */
        u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( u2_DidInfo,
                                                DCM_DSP_DIDMNG_DID_RANGE,
                                                &u2_RangeIndex,
                                                &u1_CRWSupport
                                                );

        if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
        {
            u1_ChkReadSupport = u1_CRWSupport & DCM_DSP_DIDMNG_READ_ONLY;

            if( u1_ChkReadSupport == DCM_DSP_DIDMNG_READ_ONLY )
            {

                Dcm_Dsp_SID22_stDidIndexInfo.u1KindOfTable = DCM_DSP_DIDMNG_DID_RANGE;
                Dcm_Dsp_SID22_stDidIndexInfo.u2DidIndex    = u2_RangeIndex;

                u1_RetVal = DCM_MAIN_E_CHECK_OK;
            }
            else
            {
                /* None */
            }
        }
        else if( u1_RetDidRange == DCM_MAIN_E_CHECK_NOT_OK )
        {
            /* None */
        }
        else
        {
            u1_RetVal = DCM_MAIN_E_INVALID_CONFIG;
        }
    }
    else
    {
        /* None */
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_OFF */
#if ( DCM_OBD_RANGE_DID_USE == STD_ON )
static FUNC(Dcm_Main_ReturnCheckType,DCM_CODE) Dcm_Dsp_SID22_CheckValidDidProc
(
    boolean b_SupportEnabledDid
)
{
    uint16                          u2_IndividualDidIndex;
    uint16                          u2_RangeIndex;
    uint16                          u2_DidInfo;
    uint16                          u2_DynamicIndex;
    uint8                           u1_IndividualDidCRWSupport;
    uint8                           u1_CRWSupport;
    uint8                           u1_ChkReadSupport;
    uint8                           u1_NumOfSourceDid;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkDynamicDid;
    Std_ReturnType                  u1_RetSupportedDid;
    Std_ReturnType                  u1_RetChkOBDDid;
    Dcm_Main_ReturnCheckType        u1_RetIndividualDid;
    Dcm_Main_ReturnCheckType        u1_RetDidRange;
    boolean                         b_IndividualDid;
    boolean                         b_ChkDynamicExe;

    u1_RetVal       = DCM_MAIN_E_CHECK_NOT_OK;
    b_IndividualDid = (boolean)FALSE;
    u2_DidInfo      = Dcm_Dsp_SID22_u2DidInfo;
    u2_IndividualDidIndex       = (uint16)0U;
    u1_IndividualDidCRWSupport  = (uint8)0U;
    u2_RangeIndex   = (uint16)0U;
    u1_CRWSupport   = (uint8)0U;
    u1_NumOfSourceDid   = (uint8)0U;
    u2_DynamicIndex     = (uint16)0U;

    /* Check DID Support IndividualDID */
    u1_RetIndividualDid = Dcm_Dsp_DidMng_ChkDid( u2_DidInfo,
                                                 DCM_DSP_DIDMNG_DID,
                                                 &u2_IndividualDidIndex,
                                                 &u1_IndividualDidCRWSupport
                                                 );

    if( u1_RetIndividualDid == DCM_MAIN_E_CHECK_OK )
    {
        u1_ChkReadSupport = u1_IndividualDidCRWSupport & DCM_DSP_DIDMNG_READ_ONLY_DYN;

        if( u1_ChkReadSupport == DCM_DSP_DIDMNG_READ_ONLY_DYN )
        {
            if( b_SupportEnabledDid == (boolean)TRUE )
            {
                u1_RetSupportedDid = Dcm_Dsp_DidMng_CheckSupportedDid( u2_DidInfo, DCM_DID_REQTYPE_READ, Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
                if( u1_RetSupportedDid == (Std_ReturnType)E_OK )
                {
                    b_ChkDynamicExe = (boolean)TRUE;
                }
                else
                {
                    b_ChkDynamicExe = (boolean)FALSE;
                    b_IndividualDid = (boolean)TRUE;
                }
            }
            else
            {
                b_ChkDynamicExe = (boolean)TRUE;
            }

            if( b_ChkDynamicExe == (boolean)TRUE )
            {
                u1_RetChkDynamicDid = Dcm_Dsp_DidMng_ChkDynamic( u2_DidInfo, &u1_NumOfSourceDid, &u2_DynamicIndex );

                if( u1_RetChkDynamicDid == (Std_ReturnType)E_OK )
                {
                    if( u1_NumOfSourceDid > DCM_DSP_SID22_DYN_DID_NOT_DEF )
                    {
                        Dcm_Dsp_SID22_stDidIndexInfo.u1KindOfTable = DCM_DSP_DIDMNG_DID_DYNAMIC;
                        Dcm_Dsp_SID22_stDidIndexInfo.u2DidIndex    = u2_DynamicIndex;

                        b_IndividualDid = (boolean)TRUE;
                        u1_RetVal = DCM_MAIN_E_CHECK_OK;

                    }
                    else
                    {
                        /* None */
                    }
                }
            }
            else
            {
                /* None */
            }
        }
        else
        {
            /* None */
        }
    }
    else
    {
        /* None */
    }

    if( b_IndividualDid == (boolean)FALSE)
    {
        /* Check DID Support Range */
        u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( u2_DidInfo,
                                                DCM_DSP_DIDMNG_DID_RANGE,
                                                &u2_RangeIndex,
                                                &u1_CRWSupport
                                                );

        if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
        {
            u1_ChkReadSupport = u1_CRWSupport & DCM_DSP_DIDMNG_READ_ONLY;

            if( u1_ChkReadSupport == DCM_DSP_DIDMNG_READ_ONLY )
            {

                Dcm_Dsp_SID22_stDidIndexInfo.u1KindOfTable = DCM_DSP_DIDMNG_DID_RANGE;
                Dcm_Dsp_SID22_stDidIndexInfo.u2DidIndex    = u2_RangeIndex;

                u1_RetVal = DCM_MAIN_E_CHECK_OK;
            }
            else
            {
                /* None */
            }
        }
        else if( u1_RetDidRange == DCM_MAIN_E_CHECK_NOT_OK )
        {
            if( b_SupportEnabledDid == (boolean)TRUE )
            {
                /* Check DID Support OBDDID */
                u1_RetChkOBDDid = Dcm_Dsp_DidMng_OBD_ChkObdDid( u2_DidInfo );
                if( u1_RetChkOBDDid == (Std_ReturnType)E_OK )
                {
                    Dcm_Dsp_SID22_stDidIndexInfo.u1KindOfTable = DCM_DSP_DIDMNG_DID_OBDDID;
                    Dcm_Dsp_SID22_stDidIndexInfo.u2DidIndex    = (uint16)0U;
                    u1_RetVal = DCM_MAIN_E_CHECK_OK;
                }
            }
            else
            {
                Dcm_Dsp_SID22_stDidIndexInfo.u1KindOfTable = DCM_DSP_DIDMNG_DID_OBDDID;
                Dcm_Dsp_SID22_stDidIndexInfo.u2DidIndex    = (uint16)0U;
                u1_RetVal = DCM_MAIN_E_CHECK_OK;
            }
        }
        else
        {
            u1_RetVal = DCM_MAIN_E_INVALID_CONFIG;
        }
    }
    else
    {
        /* None */
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */


#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_StartPage                                  */
/* Description   | StartPagedProcessing                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID22_StartPage
(
    void
)
{
    uint16              u2_PbidSid22;
    Dcm_MsgContextType  st_MsgContext;

    u2_PbidSid22 = Dcm_P_u2Pbid_Sid22;

    st_MsgContext.reqData                           = NULL_PTR;
    st_MsgContext.reqDataLen                        = (Dcm_MsgLenType)0U;
    st_MsgContext.resData                           = NULL_PTR;
    st_MsgContext.msgAddInfo.reqType                = (uint8)0U;
    st_MsgContext.msgAddInfo.suppressPosResponse    = STD_OFF;
    st_MsgContext.resMaxDataLen                     = (Dcm_MsgLenType)0U;
    st_MsgContext.idContext                         = (Dcm_IdContextType)0U;
    st_MsgContext.dcmRxPduId                        = (PduIdType)0U;
    st_MsgContext.resDataLen                        = Dcm_Dsp_SID22_u4ResDataLen;

    Dcm_Dsp_MsgMaker_StartPagedProcessing( &st_MsgContext, u2_PbidSid22 );

    return ;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_IsResDataSettingPossible                   */
/* Description   | Compare the Response data size with the input data       */
/* Preconditions | Response data size having been calculated                */
/* Parameters    | [IN] u4DataBufferLength : Length of Data-Buffer          */
/* Return Value  | boolean                                                  */
/*               |   TRUE   : Response data setting is possible.            */
/*               |   FALSE  : Response data setting is impossible.          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID22_IsResDataSettingPossible
(
    const uint32 u4DataBufferLength
)
{
    boolean         b_SettingPossible;

    b_SettingPossible = (boolean)FALSE;
    if( u4DataBufferLength >= Dcm_Dsp_SID22_u4ResDataLen )
    {
        b_SettingPossible = (boolean)TRUE;
    }

    return b_SettingPossible;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_JudgeProceedToNextProcByDidSupported       */
/* Description   | Proccess of Did Non Support                              */
/* Preconditions | -                                                        */
/* Parameters    | void        :                                            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK      : -                                          */
/*               |   E_NOT_OK  : -                                          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_JudgeProceedToNextProcByDidSupported
(
    void
)
{
    uint16                              u2_DidSupChkCnt;
    uint16                              u2_DidNumOfReqMsg;
    Std_ReturnType                      u1_RetVal;
    boolean                             b_RoorIfAnyOneUnsupportedDidExist;

    u2_DidNumOfReqMsg                   = Dcm_Dsp_SID22_u2DidNumOfReqMsg;
    b_RoorIfAnyOneUnsupportedDidExist   = Dcm_P_Sid22_bRoorIfAnyOneUnsupportedDidExist;

    if( b_RoorIfAnyOneUnsupportedDidExist == (boolean)TRUE )
    {
        u1_RetVal = (Std_ReturnType)E_OK;
        /* If unsupported DID is included , proceed to negative-response Proccessing. */
        for( u2_DidSupChkCnt = 0U; u2_DidSupChkCnt < u2_DidNumOfReqMsg; u2_DidSupChkCnt++ )
        {
            /* Dcm_Dsp_SID22_bDidReadSupInfo array elements corresponding to unsupported DIDs are set to FALSE */
            if( Dcm_Dsp_SID22_bDidReadSupInfo[u2_DidSupChkCnt] == (boolean)FALSE )
            {
                u1_RetVal = (Std_ReturnType)E_NOT_OK;
                break;
            }
        }
    }
    else /* FALSE */
    {
        u1_RetVal = (Std_ReturnType)E_NOT_OK;
        /* If at least one DID is supported , proceed to Next Proccessing. */
        for( u2_DidSupChkCnt = 0U; u2_DidSupChkCnt < u2_DidNumOfReqMsg; u2_DidSupChkCnt++ )
        {
            /* Dcm_Dsp_SID22_bDidReadSupInfo array elements corresponding to supported DIDs are set to TRUE */
            if( Dcm_Dsp_SID22_bDidReadSupInfo[u2_DidSupChkCnt] == (boolean)TRUE )
            {
                u1_RetVal = (Std_ReturnType)E_OK;
                break;
            }
        }
    }

    return u1_RetVal;
}


#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_OBD_RANGE_DID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID22_CallReadObdDid                             */
/* Description   | Read OBDDID Data                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2Did      : DID                                    */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData : Start pointer of read data                */
/*               | [out] ptDataLength : Read Data Length                    */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               | [out] ptNextOpInit : Next OpStatus is DCM_INITIAL        */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/*               |        DCM_E_UPDATE_PAGE : Update Page                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID22_CallReadObdDid
(
    const uint16 u2Did,
    const Dcm_OpStatusType u1NotifyOpStatus,
    const uint32 u4DataBufferLen,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptResData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptResDataLen,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptNextOpInit
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ObdResData;
    uint32                                      u4_ObdResDataLen;
    uint32                                      u4_ObdDataBufferLen;
    Dcm_NegativeResponseCodeType                u1_LocalErrorCode;
    Std_ReturnType                              u1_RetReadDidDataFnc;

    u1_LocalErrorCode       = DCM_DSP_SID22_INVALID_NRC_ZERO;
    *ptErrorCode            = DCM_DSP_SID22_INVALID_NRC_ZERO;
    *ptNextOpInit           = (boolean)FALSE;

    if( ( u1NotifyOpStatus == (Dcm_OpStatusType)DCM_INITIAL ) || ( u1NotifyOpStatus == (Dcm_OpStatusType)DCM_PENDING ) )
    {
        u4_ObdDataBufferLen = (uint32)(u4DataBufferLen + (uint32)DCM_DSP_SID22_DIDLEN); /* no wrap around */
        u4_ObdResDataLen    = (uint32)0U;
        pt_ObdResData       = &(Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen - (uint32)DCM_DSP_SID22_DIDLEN]); /* no wrap around */
    }
    else
    {
        u4_ObdDataBufferLen = u4DataBufferLen;
        u4_ObdResDataLen    = (uint32)0U;
        pt_ObdResData       = ptResData;
    }
    *ptResDataLen           = (uint32)0U;

    /* Call Xxx_ReadData, Dem_DcmGetNumTIDsOfOBDMID, Dem_DcmGetDTRData, Dem_DcmGetInfoTypeValuexx, Xxx_GetInfotypeValueDat function */
    u1_RetReadDidDataFnc = Dcm_Dsp_DidMng_OBD_CallReadObdDidFnc( u2Did, u1NotifyOpStatus, u4_ObdDataBufferLen, pt_ObdResData, &u4_ObdResDataLen, &u1_LocalErrorCode );
    if( u1_RetReadDidDataFnc == (Std_ReturnType)E_OK )
    {
        if( u1NotifyOpStatus == (Dcm_OpStatusType)DCM_INITIAL )
        {
            if( u4_ObdResDataLen <= (uint32)DCM_DSP_SID22_DIDLEN )
            {
                /* delete DID */
                Dcm_Dsp_Main_stMsgContext.resDataLen -= (uint32)DCM_DSP_SID22_DIDLEN; /* no wrap around */
            }
            else
            {
                *ptResDataLen = (uint32)(u4_ObdResDataLen - (uint32)DCM_DSP_SID22_DIDLEN); /* no wrap around */
            }
        }
        else if( u1NotifyOpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            if( u4_ObdResDataLen <= (uint32)DCM_DSP_SID22_DIDLEN )
            {
                /* delete DID */
                Dcm_Dsp_Main_stMsgContext.resDataLen -= (uint32)DCM_DSP_SID22_DIDLEN; /* no wrap around */
            }
            else
            {
                *ptResDataLen = (uint32)(u4_ObdResDataLen - (uint32)DCM_DSP_SID22_DIDLEN); /* no wrap around */
            }
        }
        else
        {
            *ptResDataLen = u4_ObdResDataLen;
        }
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        /* No Process */
    }
    else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_UPDATE_PAGE )
    {
        if( u1NotifyOpStatus == (Dcm_OpStatusType)DCM_INITIAL )
        {
            if( u4_ObdResDataLen <= (uint32)DCM_DSP_SID22_DIDLEN )
            {
                /* delete DID */
                Dcm_Dsp_Main_stMsgContext.resDataLen -= (uint32)DCM_DSP_SID22_DIDLEN; /* no wrap around */
                *ptNextOpInit = (boolean)TRUE;
            }
            else
            {
                *ptResDataLen = (uint32)(u4_ObdResDataLen - (uint32)DCM_DSP_SID22_DIDLEN); /* no wrap around */
            }
        }
        else
        {
            *ptResDataLen = u4_ObdResDataLen;
        }
    }
    else
    {
        *ptErrorCode = u1_LocalErrorCode;
    }

    return u1_RetReadDidDataFnc;
}
#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID22 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-08-20                                              */
/*  v1-2-0         :2018-11-28                                              */
/*  v3-0-0         :2019-09-26                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

