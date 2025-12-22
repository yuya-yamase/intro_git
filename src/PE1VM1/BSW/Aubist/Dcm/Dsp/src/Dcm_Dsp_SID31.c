/* Dcm_Dsp_SID31_c(v5-5-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID31/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID31.h>
#if ( DCM_SUPPORT_SID31 == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID31_Cfg.h"
#include <Dcm/Dcm_Dsp_SID31_OBD.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_EvtDistr.h>

#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID31_SUBFUNC_START         ((uint8)0x01U)
#define DCM_DSP_SID31_SUBFUNC_STOP          ((uint8)0x02U)
#define DCM_DSP_SID31_SUBFUNC_REQRSLT       ((uint8)0x03U)
#define DCM_DSP_SID31_SUBFUNC_MASK          ((uint8)0x7FU)
#define DCM_DSP_SID31_SUBFUNC_SUPBIT        ((uint8)7U)
#define DCM_DSP_SID31_SUBFUNC_LEN           ((uint8)1U)
#define DCM_DSP_SID31_SUBFUNC_BYTE          ((uint8)0U)

#define DCM_DSP_SID31_RID_SHIFT             ((uint8)8U)
#define DCM_DSP_SID31_RID_LEN               ((uint8)2U)
#define DCM_DSP_SID31_RID_BYTE_MSB          ((uint8)1U)
#define DCM_DSP_SID31_RID_BYTE_LSB          ((uint8)2U)

#define DCM_DSP_SID31_SIG_SHIFT_H           ((uint8)24U)
#define DCM_DSP_SID31_SIG_SHIFT_M           ((uint8)16U)
#define DCM_DSP_SID31_SIG_SHIFT_L           ((uint8)8U)
#define DCM_DSP_SID31_SIG_SHIFT_BYTE        ((uint8)3U)
#define DCM_DSP_SID31_SIG_BYTE              ((uint8)3U)
#define DCM_DSP_SID31_SIG_BYTEPOS_H         ((uint8)3U)
#define DCM_DSP_SID31_SIG_BYTEPOS_M         ((uint8)2U)
#define DCM_DSP_SID31_SIG_BYTEPOS_L         ((uint8)1U)
#define DCM_DSP_SID31_SIG_BITMASK           ((uint16)0x0007U)
#define DCM_DSP_SID31_SIG_BIT0_ON           ((uint8)0x01U)

#define DCM_DSP_SID31_SIG_BIT1              ((uint8)1U)
#define DCM_DSP_SID31_SIG_BIT8              ((uint8)8U)
#define DCM_DSP_SID31_SIG_BIT16             ((uint8)16U)
#define DCM_DSP_SID31_SIG_BIT32             ((uint8)32U)
#define DCM_DSP_SID31_SIG_BITVARI           ((uint8)0U)
#define DCM_DSP_SID31_SIG_BITDYN            ((uint8)0U)
#define DCM_DSP_SID31_TYPETBLNUM            ((uint8)(DCM_DSP_DYNAMIC_LENGTH + (uint8)1U))

#define DCM_DSP_SID31_MSGLEN_MIN            ((uint8)(DCM_DSP_SID31_SUBFUNC_LEN + DCM_DSP_SID31_RID_LEN))

#define DCM_DSP_SID31_ROUTINEINFO_LEN       ((uint8)1U)
#define DCM_DSP_SID31_ROUTINEINFO_POS       ((uint8)3U)

#define DCM_DSP_SID31_VALUE_MAX_U4          ((uint32)0xFFFFFFFFU)

#if( DCM_OBD_RANGE_RID_USE == STD_ON )
#define DCM_DSP_SID31_RID_E0                ((uint8)0xE0U)
#endif /* DCM_OBD_RANGE_RID_USE == STD_ON */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_InitialProcSub
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptNrcFlag
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_CancelProc
(
    void
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_RcrrpProc
(
    void
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_ExecuteRoutine
(
    const Dcm_OpStatusType u1OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction
);
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_ExecRoutineProc
(
    const Dcm_OpStatusType u1OpStatus,
    const uint16 u2RoutineIndex,
    const uint8  u1SubFunction,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptExecProcessPage,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptProcessEnded
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_HandleProcResultPreStartPage
(
    const uint16 u2RoutineIndex,
    const uint8  u1SubFunction,
    const uint32 u4PageLen,
    const uint8  u1RetCout,
    P2CONST( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptExecProcessPage,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptProcessEnded,
    const Dcm_NegativeResponseCodeType u1ErrorCode
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_HandleProcResultPostStartPage
(
    const uint16 u2RoutineIndex,
    const uint8  u1SubFunction,
    const uint32 u4PageLen,
    const uint8  u1RetCout,
    P2CONST( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptExecProcessPage,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptProcessEnded
);
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */
static FUNC ( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkRoutineId
(
    const uint16 u2RoutineId,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptRoutineIndex
);
static FUNC ( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkSesCtrl
(
    const uint16 u2RoutineIndex
);
static FUNC ( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkSecLevel
(
    const uint16 u2RoutineIndex
);
static FUNC ( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkSubFunction
(
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction
);
static FUNC (Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkReqLen
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction
);
static FUNC (Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkResMax
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_ChkResLenOVFL
(
    const uint32 u4ResLen
);
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF )
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_SetReqData
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData
);
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_SetReqData
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData
);
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF )
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_SetResData
(
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction,
    P2CONST( uint32, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    const uint32 u4VarDataLen
);
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_SetResData
(
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction,
    P2CONST( uint32, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    const uint32 u4PageDataLen
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_SetResDataLen
(
    P2CONST( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) ptOutSigInfo,
    const uint8  u1OutSigNum,
    const uint32 u4PageDataLen,
    const boolean bRoutineInfoUsed
);
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF )
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_SetResInfo
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const boolean bRoutineInfoUsed,
    const uint8 u1OutSigNum,
    P2CONST( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) ptOutSigInfo,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData
);
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_SetResInfo
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const boolean bRoutineInfoUsed,
    const uint8 u1OutSigNum,
    P2CONST( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) ptOutSigInfo,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData
);
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID31_StartPage
(
    void
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID31_AdjustDataLenForPage
(
    void
);
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID31_u2ExpectedSettingLen;
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID31_u2RoutineIndex;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID31_u1SubFunction;

#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID31_u4ResDataLenforPB;
static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID31_u4RemainingResDataLenforPB;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_SID31_bUpdatePageFlag;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_SID31_bProcessEnded;
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>

static CONST ( AB_83_ConstV uint8, DCM_CONST ) Dcm_Dsp_SID31_TypeTbl[ DCM_DSP_SID31_TYPETBLNUM ] =
{
    DCM_DSP_SID31_SIG_BIT1,         /* DCM_DSP_BOOLEAN          */
    DCM_DSP_SID31_SIG_BIT16,        /* DCM_DSP_SINT16           */
    DCM_DSP_SID31_SIG_BIT32,        /* DCM_DSP_SINT32           */
    DCM_DSP_SID31_SIG_BIT8,         /* DCM_DSP_SINT8            */
    DCM_DSP_SID31_SIG_BIT16,        /* DCM_DSP_UINT16           */
    DCM_DSP_SID31_SIG_BIT32,        /* DCM_DSP_UINT32           */
    DCM_DSP_SID31_SIG_BIT8,         /* DCM_DSP_UINT8            */
    DCM_DSP_SID31_SIG_BITVARI,      /* DCM_DSP_VARIABLE_LENGTH  */
    DCM_DSP_SID31_SIG_BITDYN        /* DCM_DSP_DYNAMIC_LENGTH   */
};

#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_SID31                                                */
/* Description   | Request processing of SID 31                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   DCM_E_FORCE_RCRRP : RCRRP response                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID31    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID31_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID31_CancelProc();
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_FORCE_RCRRP_OK )
    {
        u1_RetVal = Dcm_Dsp_SID31_RcrrpProc();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_Cbk                                        */
/* Description   | Routine execute request upon pending                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID31_Cbk    /* MISRA DEVIATION */
(
    const uint8 u1EventId                   /* MISRA DEVIATION */
)
{
    (void)Dcm_Dsp_SID31_ExecuteRoutine( DCM_PENDING, &Dcm_Dsp_Main_stMsgContext, Dcm_Dsp_SID31_u2RoutineIndex, Dcm_Dsp_SID31_u1SubFunction ); /* no return check required */

    return;
}

#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_UpdatePageCbk                              */
/* Description   | Call Back Function to Continue SID31 UpdatePage          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event Id                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID31_UpdatePageCbk         /* MISRA DEVIATION */
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    uint8                           u1_OpStatus;

    if( u1EventId == DCM_M_EVTID_SID31_UPDATERCRRP )
    {
        u1_OpStatus   = DCM_FORCE_RCRRP_OK;
    }
    else
    {
        /* if( u1EventId == DCM_M_EVTID_SID31_UPDATEPAGE ) */
        u1_OpStatus   = DCM_PENDING;
    }

    (void)Dcm_Dsp_SID31_ExecuteRoutine( u1_OpStatus, &Dcm_Dsp_Main_stMsgContext, Dcm_Dsp_SID31_u2RoutineIndex, Dcm_Dsp_SID31_u1SubFunction );  /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_UpdatePage                                 */
/* Description   | UpdatePage of SID 31                                     */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptResData       : Response Data                    */
/*               | [IN]  u4ResMaxDataLen : Buffer Size of Response Data     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_UpdatePage  /* MISRA DEVIATION */
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
)
{
    Std_ReturnType    u1_RetVal;

    u1_RetVal = E_OK;

    if( u4ResMaxDataLen == (Dcm_MsgLenType)DCM_DSD_UPDATEPAGE_INITIAL_ACT )
    {
        Dcm_Dsp_SID31_bUpdatePageFlag = (boolean)TRUE;
        Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
    }
    else
    {
        Dcm_Dsp_Main_stMsgContext.resData          = ptResData;
        Dcm_Dsp_Main_stMsgContext.resMaxDataLen    = u4ResMaxDataLen;
        Dcm_Dsp_Main_stMsgContext.resDataLen       = (uint32)0U;

        u1_RetVal = Dcm_Dsp_SID31_ExecuteRoutine( DCM_UPDATE_PAGE_OK, &Dcm_Dsp_Main_stMsgContext, Dcm_Dsp_SID31_u2RoutineIndex, Dcm_Dsp_SID31_u1SubFunction );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_CancelPage                                 */
/* Description   | CancelPage of SID31                                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID31_CancelPage
(void)
{
    boolean                         b_UserNotify;

    b_UserNotify    = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SID31_ExecuteRoutine( DCM_CANCEL, &Dcm_Dsp_Main_stMsgContext, Dcm_Dsp_SID31_u2RoutineIndex, Dcm_Dsp_SID31_u1SubFunction ); /* no return check required */

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID31_EXECUTE, (boolean)FALSE );
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID31_UPDATEPAGE, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_InitialProc                                */
/* Description   | Initial process of SID 31 request                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   DCM_E_FORCE_RCRRP : RCRRP response                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if( DCM_OBD_RANGE_RID_USE == STD_OFF )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint8 u1_NrcFlag;
    Std_ReturnType  u1_RetVal;
    Dcm_Main_ReturnCheckType u1_CheckRet;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    uint8   u1_SubFunction;
    uint16  u2_RoutineId;
    uint16  u2_RoutineIndex;

    u1_RetVal = E_OK;
    u1_NrcFlag = (uint8)STD_OFF;
    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;
    u2_RoutineIndex = (uint16)0U;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE                                  */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    /* Save message context */
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    /* Check minimum message length */
    if( ptMsgContext->reqDataLen >= DCM_DSP_SID31_MSGLEN_MIN )
    {
        /* Set suppress bit */
        Dcm_Dsp_Main_stMsgContext.msgAddInfo.suppressPosResponse = ptMsgContext->reqData[DCM_DSP_SID31_SUBFUNC_BYTE] >> DCM_DSP_SID31_SUBFUNC_SUPBIT ;

        /* Get routine ID */
        u2_RoutineId = (uint16)( (uint16)ptMsgContext->reqData[DCM_DSP_SID31_RID_BYTE_MSB] << DCM_DSP_SID31_RID_SHIFT );
        u2_RoutineId = (uint16)ptMsgContext->reqData[DCM_DSP_SID31_RID_BYTE_LSB] | u2_RoutineId;

        /* Check routine ID */
        u1_CheckRet = Dcm_Dsp_SID31_ChkRoutineId( u2_RoutineId, &u2_RoutineIndex );
        if( u1_CheckRet == DCM_MAIN_E_CHECK_OK )
        {
            /* Check active session */
            u1_CheckRet = Dcm_Dsp_SID31_ChkSesCtrl( u2_RoutineIndex );
            if( u1_CheckRet == DCM_MAIN_E_CHECK_OK )
            {
                /* Check active security level */
                u1_CheckRet = Dcm_Dsp_SID31_ChkSecLevel( u2_RoutineIndex );
                if( u1_CheckRet == DCM_MAIN_E_CHECK_OK )
                {
                    /* Get SubFunction */
                    u1_SubFunction = ptMsgContext->reqData[DCM_DSP_SID31_SUBFUNC_BYTE] & DCM_DSP_SID31_SUBFUNC_MASK;

                    /* Check subfunction */
                    u1_CheckRet = Dcm_Dsp_SID31_ChkSubFunction( u2_RoutineIndex, u1_SubFunction );
                    if( u1_CheckRet == DCM_MAIN_E_CHECK_OK )
                    {
                        /* Save routine index and subfunction */
                        Dcm_Dsp_SID31_u2RoutineIndex = u2_RoutineIndex;
                        Dcm_Dsp_SID31_u1SubFunction  = u1_SubFunction;

                        u1_RetVal = Dcm_Dsp_SID31_InitialProcSub( ptMsgContext, &u1_ErrorCode, &u1_NrcFlag );
                    }
                    else
                    {
                        /* NRC0x12 */
                        u1_NrcFlag = (uint8)STD_ON;
                        u1_ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                    }
                }
                else
                {
                    /* NRC0x33 */
                    u1_NrcFlag = (uint8)STD_ON;
                    u1_ErrorCode = DCM_E_SECURITYACCESSDENIED;
                }
            }
            else
            {
                /* NRC0x31 */
                u1_NrcFlag = (uint8)STD_ON;
                u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
            }
        }
        else
        {
            /* NRC0x31 */
            u1_NrcFlag = (uint8)STD_ON;
            u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
        }
    }
    else
    {
        /* NRC0x13 */
        u1_NrcFlag = (uint8)STD_ON;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( u1_NrcFlag != (uint8)STD_OFF )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_RID_USE == STD_OFF */
#if( DCM_OBD_RANGE_RID_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint16                       u2_RoutineId;
    uint16                       u2_RoutineIndex;
    uint8                        u1_NrcFlag;
    uint8                        u1_SubFunction;
    uint8                        u1_RidHi;
    uint8                        u1_RidLo;
    Std_ReturnType               u1_RetVal;
    Std_ReturnType               u1_RetObdIfProc;
    Std_ReturnType               u1_RetChkRidSupProc;
    Dcm_Main_ReturnCheckType     u1_CheckRet;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    boolean                      b_ChkUseObd;

    u1_RetVal = E_OK;
    u1_NrcFlag = (uint8)STD_OFF;
    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;
    u2_RoutineIndex = (uint16)0U;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE                                  */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    /* Save message context */
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    /* Check minimum message length */
    if( ptMsgContext->reqDataLen >= DCM_DSP_SID31_MSGLEN_MIN )
    {
        /* Set suppress bit */
        Dcm_Dsp_Main_stMsgContext.msgAddInfo.suppressPosResponse = ptMsgContext->reqData[DCM_DSP_SID31_SUBFUNC_BYTE] >> DCM_DSP_SID31_SUBFUNC_SUPBIT ;

        /* Get routine ID */
        u1_RidHi = ptMsgContext->reqData[DCM_DSP_SID31_RID_BYTE_MSB];
        u1_RidLo = ptMsgContext->reqData[DCM_DSP_SID31_RID_BYTE_LSB];
        u2_RoutineId = (uint16)( (uint16)u1_RidHi << DCM_DSP_SID31_RID_SHIFT );
        u2_RoutineId = (uint16)u1_RidLo | u2_RoutineId;

        b_ChkUseObd = (boolean)FALSE;
        /* Get SubFunction */
        u1_SubFunction = ptMsgContext->reqData[DCM_DSP_SID31_SUBFUNC_BYTE] & DCM_DSP_SID31_SUBFUNC_MASK;

        if( u1_SubFunction == DCM_DSP_SID31_SUBFUNC_START )
        {
            if( u1_RidHi == DCM_DSP_SID31_RID_E0 )
            {
                /* Use OBD-IF to RID:0xE000-E0FF */
                b_ChkUseObd = (boolean)TRUE;
            }
        }

        if( b_ChkUseObd == (boolean)TRUE )
        {
            /* Use OBD-IF */
            u1_RetObdIfProc = Dcm_Dsp_SID31_OBD_StartRoutineProc( &Dcm_Dsp_Main_stMsgContext, &u1_ErrorCode );
            if( u1_RetObdIfProc == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            }
            else
            {
                u1_NrcFlag = (uint8)STD_ON;
                if( u1_ErrorCode == DCM_E_REQUESTOUTOFRANGE )
                {
                    /* Check routine ID */
                    u1_CheckRet = Dcm_Dsp_SID31_ChkRoutineId( u2_RoutineId, &u2_RoutineIndex );
                    if( u1_CheckRet == DCM_MAIN_E_CHECK_OK )
                    {
                        u1_ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                    }
                }
            }
        }
        else
        {
            /* Check routine ID */
            u1_CheckRet = Dcm_Dsp_SID31_ChkRoutineId( u2_RoutineId, &u2_RoutineIndex );
            if( u1_CheckRet == DCM_MAIN_E_CHECK_OK )
            {
                /* Check active session */
                u1_CheckRet = Dcm_Dsp_SID31_ChkSesCtrl( u2_RoutineIndex );
                if( u1_CheckRet == DCM_MAIN_E_CHECK_OK )
                {
                    /* Check active security level */
                    u1_CheckRet = Dcm_Dsp_SID31_ChkSecLevel( u2_RoutineIndex );
                    if( u1_CheckRet == DCM_MAIN_E_CHECK_OK )
                    {
                        /* Check subfunction */
                        u1_CheckRet = Dcm_Dsp_SID31_ChkSubFunction( u2_RoutineIndex, u1_SubFunction );
                        if( u1_CheckRet == DCM_MAIN_E_CHECK_OK )
                        {
                            /* Save routine index and subfunction */
                            Dcm_Dsp_SID31_u2RoutineIndex = u2_RoutineIndex;
                            Dcm_Dsp_SID31_u1SubFunction  = u1_SubFunction;

                            u1_RetVal = Dcm_Dsp_SID31_InitialProcSub( ptMsgContext, &u1_ErrorCode, &u1_NrcFlag );
                        }
                        else
                        {
                            /* NRC0x12 */
                            u1_NrcFlag = (uint8)STD_ON;
                            u1_ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                        }
                    }
                    else
                    {
                        /* NRC0x33 */
                        u1_NrcFlag = (uint8)STD_ON;
                        u1_ErrorCode = DCM_E_SECURITYACCESSDENIED;
                    }
                }
                else
                {
                    /* NRC0x31 */
                    u1_NrcFlag = (uint8)STD_ON;
                    u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
                }
            }
            else
            {
                u1_RetChkRidSupProc = E_NOT_OK;
                if( ( u1_SubFunction == DCM_DSP_SID31_SUBFUNC_STOP ) || ( u1_SubFunction == DCM_DSP_SID31_SUBFUNC_REQRSLT ) )
                {
                    if( u1_RidHi == DCM_DSP_SID31_RID_E0 )
                    {
                        u1_RetChkRidSupProc = Dcm_Dsp_SID31_OBD_CheckRidSupportProc( &Dcm_Dsp_Main_stMsgContext );
                    }
                }
                if( u1_RetChkRidSupProc == (Std_ReturnType)E_OK )
                {
                    /* NRC 0x12 */
                    u1_NrcFlag = (uint8)STD_ON;
                    u1_ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                }
                else
                {
                    /* NRC 0x31 */
                    u1_NrcFlag = (uint8)STD_ON;
                    u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
                }
            }
        }
    }
    else
    {
        /* NRC0x13 */
        u1_NrcFlag = (uint8)STD_ON;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( u1_NrcFlag != (uint8)STD_OFF )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
    }

    return u1_RetVal;
}
#endif /* DCM_OBD_RANGE_RID_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_InitialProcSub                             */
/* Description   | Initial process of SID 31 request                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  ptMsgContext : Message Context                     */
/*               | [OUT] ptErrorCode  : Error code                          */
/*               | [OUT] ptNrcFlag    : Nrc flag                            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   DCM_E_FORCE_RCRRP : RCRRP response                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_InitialProcSub
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptNrcFlag
)
{
    Std_ReturnType  u1_RetVal;
    Dcm_Main_ReturnCheckType u1_CheckRet;
    uint16 u2_RIndex;
    uint16 u2_RIDNum;

    u1_RetVal = E_OK;
    *ptNrcFlag = (uint8)STD_OFF;
    *ptErrorCode = (Dcm_NegativeResponseCodeType)0x00U;

    u2_RIndex = Dcm_Dsp_SID31_u2RoutineIndex;
    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    if( u2_RIndex < u2_RIDNum )
    {
        /* Check request message length  */
        u1_CheckRet = Dcm_Dsp_SID31_ChkReqLen( ptMsgContext, u2_RIndex, Dcm_Dsp_SID31_u1SubFunction );
        if( u1_CheckRet == DCM_MAIN_E_CHECK_OK )
        {
            /* Check response message length  */
            u1_CheckRet = Dcm_Dsp_SID31_ChkResMax( ptMsgContext, u2_RIndex, Dcm_Dsp_SID31_u1SubFunction );
            if( u1_CheckRet == DCM_MAIN_E_CHECK_OK )
            {
                /* Set Subfunction and RID in response data */
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID31_SUBFUNC_BYTE] = Dcm_Dsp_SID31_u1SubFunction;
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID31_RID_BYTE_MSB] = (uint8)( Dcm_P_SID31_Routine_Tbl[u2_RIndex].u2ID >> DCM_DSP_SID31_RID_SHIFT );
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID31_RID_BYTE_LSB] = (uint8)( Dcm_P_SID31_Routine_Tbl[u2_RIndex].u2ID );

                /* Set Subfunction and RID length in response length */
                Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID31_SUBFUNC_LEN + DCM_DSP_SID31_RID_LEN;

                Dcm_Dsp_SID31_u2ExpectedSettingLen = (uint16)0U;

                u1_RetVal = Dcm_Dsp_SID31_ExecuteRoutine( DCM_INITIAL, ptMsgContext, u2_RIndex, Dcm_Dsp_SID31_u1SubFunction );
            }
            else
            {
                /* NRC0x10 */
                *ptNrcFlag = (uint8)STD_ON;
                *ptErrorCode = DCM_E_GENERALREJECT;
            }
        }
        else
        {
            /* NRC0x13 */
            *ptNrcFlag = (uint8)STD_ON;
            *ptErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_CancelProc                                 */
/* Description   | Cancel process of SID 31 request                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_CancelProc
(
    void
)
{
    boolean b_UserNotifyFlag;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SID31_ExecuteRoutine( DCM_CANCEL, &Dcm_Dsp_Main_stMsgContext, Dcm_Dsp_SID31_u2RoutineIndex, Dcm_Dsp_SID31_u1SubFunction ); /* no return check required */

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID31_EXECUTE, (boolean)FALSE ); /* no return check required */
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE                                   */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_RcrrpProc                                  */
/* Description   | RCRRP process of SID 31 request                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   DCM_E_FORCE_RCRRP : RCRRP response                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_RcrrpProc
(
    void
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = Dcm_Dsp_SID31_ExecuteRoutine( DCM_FORCE_RCRRP_OK, &Dcm_Dsp_Main_stMsgContext, Dcm_Dsp_SID31_u2RoutineIndex, Dcm_Dsp_SID31_u1SubFunction );

    return u1_RetVal;
}

#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_ExecuteRoutine                             */
/* Description   | Routine execute processing                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus      : Operation state                   */
/*               | [IN] ptMsgContext    : Message Context                   */
/*               | [IN] u2RoutineIndex  : Routine Index                     */
/*               | [IN] u1SubFunction   : Sub function                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   DCM_E_FORCE_RCRRP : RCRRP response                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_ExecuteRoutine
(
    const Dcm_OpStatusType u1OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction
)
{
    Dcm_Dsp_SID31_SigDataType st_SigData;
    uint32          u4_AvailableLen;
    uint32          u4_ResDataLen;
    uint16          u2_SigCnt;
    uint16          u2_RIDNum;
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetCout;
    Dcm_NegativeResponseCodeType u1_ErrorCode;

    u1_RetVal = E_OK;

    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    if( u2RoutineIndex < u2_RIDNum )
    {
        u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;

        /* Signal data init */
        for( u2_SigCnt = (uint16)0U; u2_SigCnt < DCM_DSP_SID31_SIGMAX; u2_SigCnt++ )
        {
            st_SigData.u4SigData[u2_SigCnt] = (uint32)0U;
        }
        st_SigData.u1SigInDataNum = (uint8)0U;
        st_SigData.u1SigOutDataNum = (uint8)0U;
        st_SigData.ptVarInData  = NULL_PTR;
        st_SigData.ptVarOutData = NULL_PTR;
        st_SigData.u4VarDataLen = (uint32)0U;

        if( u1OpStatus != (Dcm_OpStatusType)DCM_CANCEL )
        {
            /* Request data setting */
            Dcm_Dsp_SID31_SetReqData( ptMsgContext, u2RoutineIndex, u1SubFunction, &st_SigData );
        }

        if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_START )
        {
            u1_RetCout = Dcm_Dsp_SID31_StartCout( u2RoutineIndex, &st_SigData, u1OpStatus, &u1_ErrorCode );
        }
        else if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_STOP )
        {
            u1_RetCout = Dcm_Dsp_SID31_StopCout( u2RoutineIndex, &st_SigData, u1OpStatus, &u1_ErrorCode );
        }
        else
        {
            u1_RetCout = Dcm_Dsp_SID31_ReqResultsCout( u2RoutineIndex, &st_SigData, u1OpStatus, &u1_ErrorCode );
        }

        if( u1OpStatus != (Dcm_OpStatusType)DCM_CANCEL )
        {
            if( u1_RetCout == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

                u4_AvailableLen =  (uint32)( DCM_DSP_SID31_VALUE_MAX_U4 - (uint32)( Dcm_Dsp_Main_stMsgContext.resDataLen + Dcm_Dsp_SID31_u2ExpectedSettingLen )); /* no wrap around */
                if( u4_AvailableLen >= st_SigData.u4VarDataLen )
                {
                    u4_ResDataLen = (uint32)( Dcm_Dsp_Main_stMsgContext.resDataLen + Dcm_Dsp_SID31_u2ExpectedSettingLen + st_SigData.u4VarDataLen ); /* no wrap around */
                    if(Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= u4_ResDataLen)
                    {
                        /* Response data setting */
                        Dcm_Dsp_SID31_SetResData( u2RoutineIndex, u1SubFunction, &st_SigData.u4SigData[st_SigData.u1SigInDataNum], st_SigData.u4VarDataLen );

                        /* Positive response */
                        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext);
                    }
                    else
                    {
                        /* NRC0x14 Send */
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG );
                    }
                }
                else
                {
                    /* NRC0x14 Send */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG );
                }
            }
            else if( u1_RetCout == (Std_ReturnType)E_NOT_OK )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

                /* Negative response */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
            }
            else if( u1_RetCout == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );

                /* Pending */
                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID31_EXECUTE ); /* no return check required */
                u1_RetVal = DCM_E_PENDING;
            }
            else if( u1_RetCout == (Std_ReturnType)DCM_E_FORCE_RCRRP )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );

                /* NRC0x78 Send */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING );
                u1_RetVal = DCM_E_FORCE_RCRRP;
            }
            else
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                /* NRC0x10 Send */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_ExecuteRoutine                             */
/* Description   | Routine execute processing                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus      : Operation state                   */
/*               | [IN] ptMsgContext    : Message Context                   */
/*               | [IN] u2RoutineIndex  : Routine Index                     */
/*               | [IN] u1SubFunction   : Sub function                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   DCM_E_FORCE_RCRRP : RCRRP response                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_ExecuteRoutine
(
    const Dcm_OpStatusType u1OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction
)
{
    Dcm_Dsp_SID31_SigDataType st_SigData;
    uint16          u2_SigCnt;
    uint16          u2_RIDNum;
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetSetReqData;
    boolean         b_ExecProcessPage;
    boolean         b_ProcessEnded;

    u1_RetVal = E_OK;
    u1_RetSetReqData = E_OK;
    b_ExecProcessPage = (boolean)FALSE;
    b_ProcessEnded = (boolean)FALSE;

    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    if( Dcm_Dsp_SID31_bProcessEnded == (boolean)FALSE )
    {
        if( u2RoutineIndex < u2_RIDNum )
        {
            /* Signal data init */
            for( u2_SigCnt = (uint16)0U; u2_SigCnt < DCM_DSP_SID31_SIGMAX; u2_SigCnt++ )
            {
                st_SigData.u4SigData[u2_SigCnt] = (uint32)0U;
            }
            st_SigData.u1SigInDataNum = (uint8)0U;
            st_SigData.u1SigOutDataNum = (uint8)0U;
            st_SigData.ptVarInData  = NULL_PTR;
            st_SigData.ptVarOutData = NULL_PTR;
            st_SigData.u4VarDataLen = (uint32)0U;
            st_SigData.u4PageDataLen = (uint32)0U;

            if( u1OpStatus != (Dcm_OpStatusType)DCM_CANCEL )
            {
                /* Request data setting */
                u1_RetSetReqData = Dcm_Dsp_SID31_SetReqData( ptMsgContext, u2RoutineIndex, u1SubFunction, &st_SigData );
            }

            if( u1_RetSetReqData == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID31_ExecRoutineProc( u1OpStatus, u2RoutineIndex, u1SubFunction, &st_SigData, &b_ExecProcessPage, &b_ProcessEnded );

                if( b_ExecProcessPage == (boolean)TRUE )
                {
                    if( Dcm_Dsp_SID31_bUpdatePageFlag == (boolean)FALSE )
                    {
                        Dcm_Dsp_SID31_u4RemainingResDataLenforPB -= (uint32)Dcm_Dsp_Main_stMsgContext.resDataLen; /* no wrap around */
                        if( b_ProcessEnded == (boolean)TRUE )
                        {
                            Dcm_Dsp_SID31_AdjustDataLenForPage();
                        }
                        Dcm_Dsp_SID31_StartPage();
                    }
                    else
                    {
                        if( Dcm_Dsp_SID31_u4RemainingResDataLenforPB < Dcm_Dsp_Main_stMsgContext.resDataLen )
                        {
                            Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_SID31_u4RemainingResDataLenforPB;
                            Dcm_Dsp_SID31_u4RemainingResDataLenforPB = (uint32)0U;
                        }
                        else
                        {
                            Dcm_Dsp_SID31_u4RemainingResDataLenforPB -= Dcm_Dsp_Main_stMsgContext.resDataLen; /* no wrap around */
                        }
                        if( b_ProcessEnded == (boolean)TRUE )
                        {
                            Dcm_Dsp_SID31_AdjustDataLenForPage();
                        }
                        if( Dcm_Dsp_Main_stMsgContext.resDataLen != (uint32)0U )
                        {
                            Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
                        }
                        else
                        {
                            u1_RetVal = E_NOT_OK;
                        }
                    }
                }
                Dcm_Dsp_SID31_bProcessEnded = b_ProcessEnded;
            }
            else
            {
                /* NRC0x10 Send */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            }
        }
    }
    else
    {
        Dcm_Dsp_SID31_AdjustDataLenForPage();
        if( Dcm_Dsp_Main_stMsgContext.resDataLen != (uint32)0U )
        {
            Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_ExecRoutineProc                            */
/* Description   | Routine execute processing                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/*               | [IN] u2RoutineIndex : Routine Index                      */
/*               | [IN] u1SubFunction  : Sub function                       */
/*               | [IN] ptSigData      : Signal data                        */
/*               | [OUT] ptExecProcessPage : Execute Process Page Flag      */
/*               | [OUT] ptProcessEnded    : Process Ended Flag             */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   DCM_E_FORCE_RCRRP : RCRRP response                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_ExecRoutineProc
(
    const Dcm_OpStatusType u1OpStatus,
    const uint16 u2RoutineIndex,
    const uint8  u1SubFunction,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptExecProcessPage,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptProcessEnded
)
{
    uint32          u4_PageLen;
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetCout;
    Dcm_NegativeResponseCodeType u1_ErrorCode;

    u1_RetVal = E_OK;
    u1_ErrorCode = DCM_E_GENERALREJECT;
    u4_PageLen = ptSigData->u4PageDataLen;

    if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_START )
    {
        u1_RetCout = Dcm_Dsp_SID31_StartCout( u2RoutineIndex, ptSigData, u1OpStatus, &u1_ErrorCode );
    }
    else if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_STOP )
    {
        u1_RetCout = Dcm_Dsp_SID31_StopCout( u2RoutineIndex, ptSigData, u1OpStatus, &u1_ErrorCode );
    }
    else
    {
        u1_RetCout = Dcm_Dsp_SID31_ReqResultsCout( u2RoutineIndex, ptSigData, u1OpStatus, &u1_ErrorCode );
    }
    if( u1OpStatus != (Dcm_OpStatusType)DCM_CANCEL )
    {
        if( Dcm_Dsp_SID31_bUpdatePageFlag == (boolean)FALSE )
        {
            u1_RetVal = Dcm_Dsp_SID31_HandleProcResultPreStartPage( u2RoutineIndex, u1SubFunction, u4_PageLen, u1_RetCout, ptSigData, ptExecProcessPage, ptProcessEnded, u1_ErrorCode );
        }
        else
        {
            u1_RetVal = Dcm_Dsp_SID31_HandleProcResultPostStartPage( u2RoutineIndex, u1SubFunction, u4_PageLen, u1_RetCout, ptSigData, ptExecProcessPage, ptProcessEnded );
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_HandleProcResultPreStartPage               */
/* Description   | Handle process result Before StartPage                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2RoutineIndex : Routine Index                      */
/*               | [IN] u1SubFunction  : Sub function                       */
/*               | [IN] u4PageLen      : Page Length                        */
/*               | [IN] u1RetCout      : Return Cout                        */
/*               | [IN] ptSigData      : Signal data                        */
/*               | [OUT] ptExecProcessPage : Execute Process Page Flag      */
/*               | [OUT] ptProcessEnded    : Process Ended Flag             */
/*               | [IN] u1ErrorCode    : NRC                                */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   DCM_E_FORCE_RCRRP : RCRRP response                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_HandleProcResultPreStartPage
(
    const uint16 u2RoutineIndex,
    const uint8  u1SubFunction,
    const uint32 u4PageLen,
    const uint8  u1RetCout,
    P2CONST( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptExecProcessPage,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptProcessEnded,
    const Dcm_NegativeResponseCodeType u1ErrorCode
)
{
    uint32          u4_AvailableLen;
    Std_ReturnType  u1_RetVal;

    *ptProcessEnded = (boolean)FALSE;
    u1_RetVal = E_OK;

    if( u1RetCout == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        *ptProcessEnded = (boolean)TRUE;
        if( ptSigData->u4VarDataLen >= ptSigData->u4PageDataLen )
        {
            u4_AvailableLen =  (uint32)( DCM_DSP_SID31_VALUE_MAX_U4 - (uint32)( (uint32)DCM_DSP_SID31_MSGLEN_MIN + (uint32)Dcm_Dsp_SID31_u2ExpectedSettingLen )); /* no wrap around */
            if( u4_AvailableLen >= ptSigData->u4VarDataLen )
            {
                if( u4PageLen >= ptSigData->u4PageDataLen )
                {
                    /* Total length of response data(SubFunction + RID + RoutineInfo + Out Signal Length) */
                    Dcm_Dsp_SID31_u4ResDataLenforPB = (uint32)( (uint32)DCM_DSP_SID31_MSGLEN_MIN + (uint32)Dcm_Dsp_SID31_u2ExpectedSettingLen + ptSigData->u4VarDataLen ); /* no wrap around */
                    /* Remaining data length for total length of response data */
                    Dcm_Dsp_SID31_u4RemainingResDataLenforPB = Dcm_Dsp_SID31_u4ResDataLenforPB;

                    /* Response data setting */
                    Dcm_Dsp_SID31_SetResData( u2RoutineIndex, u1SubFunction, &ptSigData->u4SigData[ptSigData->u1SigInDataNum], ptSigData->u4PageDataLen );
                    *ptExecProcessPage = (boolean)TRUE;
                }
                else
                {
                    /* NRC0x14 Send */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG );
                }
            }
            else
            {
                /* NRC0x14 Send */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG );
            }
        }
        else
        {
            /* NRC0x10 Send */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
        }
    }
    else if( u1RetCout == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );

        /* Pending */
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID31_EXECUTE ); /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else if( u1RetCout == (Std_ReturnType)DCM_E_FORCE_RCRRP )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        
        /* NRC0x78 Send */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING );
        u1_RetVal = DCM_E_FORCE_RCRRP;
    }
    else if( u1RetCout == (Std_ReturnType)DCM_E_UPDATE_PAGE )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        if( ptSigData->u4VarDataLen >= ptSigData->u4PageDataLen )
        {
            u4_AvailableLen =  (uint32)( DCM_DSP_SID31_VALUE_MAX_U4 - (uint32)( (uint32)DCM_DSP_SID31_MSGLEN_MIN + (uint32)Dcm_Dsp_SID31_u2ExpectedSettingLen )); /* no wrap around */
            if( u4_AvailableLen >= ptSigData->u4VarDataLen )
            {
                if( u4PageLen >= ptSigData->u4PageDataLen )
                {
                    /* Total length of response data(SubFunction + RID + RoutineInfo + Out Signal Length) */
                    Dcm_Dsp_SID31_u4ResDataLenforPB = (uint32)( (uint32)DCM_DSP_SID31_MSGLEN_MIN + (uint32)Dcm_Dsp_SID31_u2ExpectedSettingLen + ptSigData->u4VarDataLen ); /* no wrap around */
                    /* Remaining data length for total length of response data */
                    Dcm_Dsp_SID31_u4RemainingResDataLenforPB = Dcm_Dsp_SID31_u4ResDataLenforPB;

                    /* Response data setting */
                    Dcm_Dsp_SID31_SetResData( u2RoutineIndex, u1SubFunction, &ptSigData->u4SigData[ptSigData->u1SigInDataNum], ptSigData->u4PageDataLen );
                    *ptExecProcessPage = (boolean)TRUE;
                }
                else
                {
                    /* NRC0x14 Send */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG );
                }
            }
            else
            {
                /* NRC0x14 Send */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG );
            }
        }
        else
        {
            /* NRC0x10 Send */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
        }
    }
    else
    {
        /* When return of Callout is E_NOT_OK or abnormal */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        /* User defined Code(0xXX) or NRC0x10 Send */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1ErrorCode );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_HandleProcResultPostStartPage              */
/* Description   | Handle process result After StartPage                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2RoutineIndex : Routine Index                      */
/*               | [IN] u1SubFunction  : Sub function                       */
/*               | [IN] u4PageLen      : Page Length                        */
/*               | [IN] u1RetCout      : Return Cout                        */
/*               | [IN] ptSigData      : Signal data                        */
/*               | [OUT] ptExecProcessPage : Execute Process Page Flag      */
/*               | [OUT] ptProcessEnded    : Process Ended Flag             */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_HandleProcResultPostStartPage
(
    const uint16 u2RoutineIndex,
    const uint8  u1SubFunction,
    const uint32 u4PageLen,
    const uint8  u1RetCout,
    P2CONST( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptExecProcessPage,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptProcessEnded
)
{
    Std_ReturnType  u1_RetVal;

    *ptProcessEnded = (boolean)FALSE;
    u1_RetVal = E_OK;

    if( u1RetCout == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        *ptProcessEnded = (boolean)TRUE;
        *ptExecProcessPage = (boolean)TRUE;
        if( u4PageLen >= ptSigData->u4PageDataLen )
        {
            /* Response data setting */
            Dcm_Dsp_SID31_SetResData( u2RoutineIndex, u1SubFunction, &ptSigData->u4SigData[ptSigData->u1SigInDataNum], ptSigData->u4PageDataLen );
        }
        /* If the buffer size is exceeded, continue processing without updating resDataLen */
    }
    else if( u1RetCout == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );

        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID31_UPDATEPAGE ); /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else if( u1RetCout == (Std_ReturnType)DCM_E_FORCE_RCRRP )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );

        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID31_UPDATERCRRP ); /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else if( u1RetCout == (Std_ReturnType)DCM_E_UPDATE_PAGE )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        *ptExecProcessPage = (boolean)TRUE;
        if( u4PageLen >= ptSigData->u4PageDataLen )
        {
            /* Response data setting */
            Dcm_Dsp_SID31_SetResData( u2RoutineIndex, u1SubFunction, &ptSigData->u4SigData[ptSigData->u1SigInDataNum], ptSigData->u4PageDataLen );
        }
        else
        {
            /* If the buffer size is exceeded, continue processing without updating resDataLen */
            *ptProcessEnded = (boolean)TRUE;
        }
    }
    else
    {
        /* When return of Callout is E_NOT_OK or abnormal */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_ChkRoutineId                               */
/* Description   | Routine ID check                                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u2RoutineId    : Routine ID                        */
/*               | [OUT] ptRoutineIndex : Routine Index                     */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               |   DCM_MAIN_E_CHECK_OK           : Check OK               */
/*               |   DCM_MAIN_E_CHECK_NOT_OK       : Check NG               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkRoutineId
(
    const uint16 u2RoutineId,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptRoutineIndex
)
{
    boolean b_CheckFlag;
    Std_ReturnType           u1_RetSupported;
    Dcm_Main_ReturnCheckType u1_RetVal;
    uint16  u2_TopIndex;
    uint16  u2_MidIndex;
    uint16  u2_EndIndex;
    uint16  u2_RIDNum;

    u1_RetVal = DCM_MAIN_E_CHECK_NOT_OK;
    b_CheckFlag = (boolean)FALSE;

    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    if( u2_RIDNum != (uint16)0U )
    {
        /* Binary Search */
        u2_TopIndex = (uint16)0U;
        u2_EndIndex = (uint16)( u2_RIDNum - (uint16)1U );

        if( Dcm_P_SID31_Routine_Tbl[u2_TopIndex].u2ID > u2RoutineId )
        {   /* It is smaller than the beginning */
            /* No process */
        }
        else if( Dcm_P_SID31_Routine_Tbl[u2_EndIndex].u2ID < u2RoutineId )
        {   /* It is larger than the end */
            /* No process */
        }
        else if( Dcm_P_SID31_Routine_Tbl[u2_TopIndex].u2ID == u2RoutineId )
        {  /* Equal to the beginning */
            *ptRoutineIndex = u2_TopIndex;
            b_CheckFlag = (boolean)TRUE;
        }
        else
        {
            while( u2_TopIndex < u2_EndIndex )
            {
                u2_MidIndex =  (uint16)( ( (uint32)u2_TopIndex + (uint32)u2_EndIndex ) >> 1U ); /* no wrap around */
                if( Dcm_P_SID31_Routine_Tbl[u2_MidIndex].u2ID < u2RoutineId )
                {
                    u2_TopIndex = u2_MidIndex + (uint16)1U;
                }
                else
                {
                    u2_EndIndex = u2_MidIndex;
                }

                if( Dcm_P_SID31_Routine_Tbl[u2_TopIndex].u2ID == u2RoutineId )
                {
                    /* Successful search */
                    *ptRoutineIndex = u2_TopIndex;
                    b_CheckFlag = (boolean)TRUE;
                    break;
                }
            }
        }
    }

    if( b_CheckFlag == (boolean)TRUE )
    {
        if( Dcm_P_SID31_Routine_Tbl[*ptRoutineIndex].bUsed == (boolean)TRUE )
        {
            u1_RetSupported = Dcm_Dsp_SID31_CheckSupportedRid( u2RoutineId , Dcm_Dsp_Main_stMsgContext.dcmRxPduId);
            if( u1_RetSupported == (Std_ReturnType)E_OK )
            {
                u1_RetVal = DCM_MAIN_E_CHECK_OK;
            }
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_ChkSesCtrl                                 */
/* Description   | Active session check                                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2RoutineIndex : Routine Index                      */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               |   DCM_MAIN_E_CHECK_OK           : Check OK               */
/*               |   DCM_MAIN_E_CHECK_NOT_OK       : Check NG               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkSesCtrl
(
    const uint16 u2RoutineIndex
)
{
    Dcm_Main_ReturnCheckType u1_RetVal;
    Dcm_SesCtrlType u1_SesCtrlType;
    uint16          u2_ComAuthIndex;
    uint16          u2_ComAuthCnt;
    uint16          u2_RIDNum;
    sint32          s4_ComAuthNum;

    u1_RetVal = DCM_MAIN_E_CHECK_NOT_OK;

    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    s4_ComAuthNum = (sint32)Dcm_P_SID31_u2Comauth_N;
    
    if( u2RoutineIndex < u2_RIDNum )
    {
        if( Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1ComAuthNum != (uint8)0U )
        {
            u2_ComAuthIndex = Dcm_P_SID31_ComAuth_INDEX_Tbl[u2RoutineIndex];
            if( (sint32)u2_ComAuthIndex < s4_ComAuthNum ) /* MISRA DEVIATION */
            {
                if( Dcm_P_SID31_ComAuthN_Tbl[u2_ComAuthIndex].u1SessionRefNum != (uint8)0U ) /* MISRA DEVIATION */
                {
                    /* Get active session */
                    u1_SesCtrlType = (uint8)0U;
                    (void)Dcm_GetSesCtrlType( &u1_SesCtrlType ); /* no return check required */

                    /* Support session check */
                    for( u2_ComAuthCnt = (uint16)0U; u2_ComAuthCnt < Dcm_P_SID31_ComAuthN_Tbl[u2_ComAuthIndex].u1SessionRefNum; u2_ComAuthCnt++ )
                    {
                        if( Dcm_P_SID31_Routine_Tbl[u2RoutineIndex].ptCommonAuthorizationRef->ptRIDNSessionRef[u2_ComAuthCnt].ptSessionRef->u1Level == u1_SesCtrlType )
                        {
                            u1_RetVal = DCM_MAIN_E_CHECK_OK;
                            break;
                        }
                    }
                }
                else
                {
                    u1_RetVal = DCM_MAIN_E_CHECK_OK;
                }
            }
        }
        else
        {
            u1_RetVal = DCM_MAIN_E_CHECK_OK;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_ChkSecLevel                                */
/* Description   | Active security level check                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2RoutineIndex : Routine Index                      */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               |   DCM_MAIN_E_CHECK_OK           : Check OK               */
/*               |   DCM_MAIN_E_CHECK_NOT_OK       : Check NG               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkSecLevel
(
    const uint16 u2RoutineIndex
)
{
    Dcm_Main_ReturnCheckType u1_RetVal;
    Dcm_SecLevelType    u1_SecurityLevel;
    uint16              u2_ComAuthIndex;
    uint16              u2_ComAuthCnt;
    uint16              u2_RIDNum;
    sint32              s4_ComAuthNum;

    u1_RetVal = DCM_MAIN_E_CHECK_NOT_OK;

    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    s4_ComAuthNum = (sint32)Dcm_P_SID31_u2Comauth_N;

    if( u2RoutineIndex < u2_RIDNum )
    {
        if( Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1ComAuthNum != (uint8)0U )
        {
            u2_ComAuthIndex = Dcm_P_SID31_ComAuth_INDEX_Tbl[u2RoutineIndex];
            if( (sint32)u2_ComAuthIndex < s4_ComAuthNum ) /* MISRA DEVIATION */
            {
                if( Dcm_P_SID31_ComAuthN_Tbl[u2_ComAuthIndex].u1SecurityLevelRefNum != (uint8)0U ) /* MISRA DEVIATION */
                {
                    /* Get active security level */
                    u1_SecurityLevel = (uint8)0U;
                    (void)Dcm_GetSecurityLevel( &u1_SecurityLevel ); /* no return check required */

                    /* Support security level check */
                    for( u2_ComAuthCnt = (uint16)0U; u2_ComAuthCnt < Dcm_P_SID31_ComAuthN_Tbl[u2_ComAuthIndex].u1SecurityLevelRefNum; u2_ComAuthCnt++ )
                    {
                        if( Dcm_P_SID31_Routine_Tbl[u2RoutineIndex].ptCommonAuthorizationRef->ptRIDNSecurityLevelRef[u2_ComAuthCnt].ptSecurityLevelRef->u1Level == u1_SecurityLevel )
                        {
                            u1_RetVal = DCM_MAIN_E_CHECK_OK;
                            break;
                        }
                    }
                }
                else
                {
                    u1_RetVal = DCM_MAIN_E_CHECK_OK;
                }
            }
        }
        else
        {
            u1_RetVal = DCM_MAIN_E_CHECK_OK;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_ChkSubFunction                             */
/* Description   | SubFunction Check                                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2RoutineIndex : Routine Index                      */
/*               | [IN] u1SubFunction  : Sub function                       */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               |   DCM_MAIN_E_CHECK_OK           : Check OK               */
/*               |   DCM_MAIN_E_CHECK_NOT_OK       : Check NG               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkSubFunction
(
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction
)
{
    Std_ReturnType           u1_RetSupported;
    Dcm_Main_ReturnCheckType u1_RetVal;
    boolean b_RidSubfuncEnabled;
    uint16 u2_RIDNum;
    uint16 u2_RID;

    u1_RetVal = DCM_MAIN_E_CHECK_NOT_OK;
    b_RidSubfuncEnabled = (boolean)FALSE;

    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    if( u2RoutineIndex < u2_RIDNum )
    {
        if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_START )
        {
            if( Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StaNum != (uint8)0U )
            {
                b_RidSubfuncEnabled = (boolean)TRUE;
            }
        }
        else if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_STOP )
        {
            if( Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StoNum != (uint8)0U )
            {
                b_RidSubfuncEnabled = (boolean)TRUE;
            }
        }
        else if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_REQRSLT )
        {
            if( Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1ReqRsltNum != (uint8)0U )
            {
                b_RidSubfuncEnabled = (boolean)TRUE;
            }
        }
        else
        {
            /* No process */
        }
        if( b_RidSubfuncEnabled == (boolean)TRUE )
        {
            u2_RID = Dcm_P_SID31_Routine_Tbl[u2RoutineIndex].u2ID;
            u1_RetSupported = Dcm_Dsp_SID31_CheckSupportedSubFuncForRid(u2_RID , u1SubFunction, Dcm_Dsp_Main_stMsgContext.dcmRxPduId);
            if( u1_RetSupported == (Std_ReturnType)E_OK )
            {
                u1_RetVal = DCM_MAIN_E_CHECK_OK;
            }
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_ChkReqLen                                  */
/* Description   | Request message length check                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message context                    */
/*               | [IN] u2RoutineIndex : Routine Index                      */
/*               | [IN] u1SubFunction  : Sub function                       */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               |   DCM_MAIN_E_CHECK_OK           : Check OK               */
/*               |   DCM_MAIN_E_CHECK_NOT_OK       : Check NG               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkReqLen
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction
)
{
    uint32  u4_BitLen;
    uint32  u4_BytePos;
    uint32  u4_ReqLen;
    uint16  u2_RIDNum;
    uint8   u1_SigNum;
    Dcm_Main_ReturnCheckType u1_RetVal;

    u1_RetVal = DCM_MAIN_E_CHECK_NOT_OK;

    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    if( u2RoutineIndex < u2_RIDNum )
    {
        u4_ReqLen = (uint32)0U;

        if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_START )
        {
            u1_SigNum = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StaInSigNum;
            if( u1_SigNum != (uint8)0U )
            {
                if( Dcm_P_SID31_StaIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type == DCM_DSP_DYNAMIC_LENGTH )
                {
                    u1_RetVal = DCM_MAIN_E_CHECK_OK;
                }
                else if( Dcm_P_SID31_StaIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type != DCM_DSP_VARIABLE_LENGTH )
                {
                    /* Get bit length */
                    u4_BitLen = (uint32)Dcm_P_SID31_StaIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos +   /* no wrap around */
                                            Dcm_Dsp_SID31_TypeTbl[ Dcm_P_SID31_StaIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type];
                    /* Get byte length */
                    u4_ReqLen = (uint32)( ( u4_BitLen + ( DCM_DSP_SID31_SIG_BIT8 - (uint8)1U ) ) >> DCM_DSP_SID31_SIG_SHIFT_BYTE ); /* no wrap around */
                }
                else
                {
                    /* Change bit(pos) to byte */
                    /* At VARIABLE_LENGTH, Pos can only be set to 0 or multiples of 8, so there is no digit loss */
                    u4_BytePos =  (uint32)( (uint32)Dcm_P_SID31_StaIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE );
                    /* Get byte length */
                    u4_ReqLen = u4_BytePos + Dcm_P_SID31_StaIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u4Length ; /* no wrap around */
                }
            }
        }
        else if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_STOP )
        {
            u1_SigNum = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StoInSigNum;
            if( u1_SigNum != (uint8)0U )
            {
                /* Get bit length */
                if( Dcm_P_SID31_StoIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type != DCM_DSP_VARIABLE_LENGTH )
                {
                    /* Get bit length */
                    u4_BitLen = (uint32)Dcm_P_SID31_StoIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos +   /* no wrap around */
                                            Dcm_Dsp_SID31_TypeTbl[ Dcm_P_SID31_StoIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type];
                    /* Get byte length */
                    u4_ReqLen = (uint32)( ( u4_BitLen + ( DCM_DSP_SID31_SIG_BIT8 - (uint8)1U ) ) >> DCM_DSP_SID31_SIG_SHIFT_BYTE ); /* no wrap around */
                }
                else
                {
                    /* Change bit(pos) to byte */
                    /* At VARIABLE_LENGTH, Pos can only be set to 0 or multiples of 8, so there is no digit loss */
                    u4_BytePos =  (uint32)( (uint32)Dcm_P_SID31_StoIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE );
                    /* Get byte length */
                    u4_ReqLen = u4_BytePos + Dcm_P_SID31_StoIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u4Length ; /* no wrap around */
                }
            }
        }
        else
        {
            u1_SigNum = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1ReqRsltInSigNum;
            if( u1_SigNum != (uint8)0U )
            {
                /* Get bit length */
                if( Dcm_P_SID31_ReqRsltIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type != DCM_DSP_VARIABLE_LENGTH )
                {
                    /* Get bit length */
                    u4_BitLen = (uint32)Dcm_P_SID31_ReqRsltIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos +   /* no wrap around */
                                            Dcm_Dsp_SID31_TypeTbl[ Dcm_P_SID31_ReqRsltIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type];
                    /* Get byte length */
                    u4_ReqLen = (uint32)( ( u4_BitLen + ( DCM_DSP_SID31_SIG_BIT8 - (uint8)1U ) ) >> DCM_DSP_SID31_SIG_SHIFT_BYTE ); /* no wrap around */
                }
                else
                {
                    /* Change bit(pos) to byte */
                    /* At VARIABLE_LENGTH, Pos can only be set to 0 or multiples of 8, so there is no digit loss */
                    u4_BytePos =  (uint32)( (uint32)Dcm_P_SID31_ReqRsltIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE );
                    /* Get byte length */
                    u4_ReqLen = u4_BytePos + Dcm_P_SID31_ReqRsltIn_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u4Length ; /* no wrap around */
                }
            }
        }

        if( u1_RetVal != DCM_MAIN_E_CHECK_OK )
        {
            u4_ReqLen += DCM_DSP_SID31_SUBFUNC_LEN + DCM_DSP_SID31_RID_LEN; /* no wrap around */
            if( u4_ReqLen == ptMsgContext->reqDataLen )
            {
                u1_RetVal = DCM_MAIN_E_CHECK_OK;
            }
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_ChkResMax                                  */
/* Description   | Response message maximum length check                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message context                    */
/*               | [IN] u2RoutineIndex : Routine Index                      */
/*               | [IN] u1SubFunction  : Sub function                       */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               |   DCM_MAIN_E_CHECK_OK           : Check OK               */
/*               |   DCM_MAIN_E_CHECK_NOT_OK       : Check NG               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_SID31_ChkResMax
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction
)
{
    uint32  u4_BitLen;
    uint32  u4_BytePos;
    uint32  u4_ResLen;
    uint16  u2_RIDNum;
    uint8   u1_SigNum;
    Dcm_Main_ReturnCheckType u1_RetVal;

    u1_RetVal = DCM_MAIN_E_CHECK_NOT_OK;

    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    if( u2RoutineIndex < u2_RIDNum )
    {
        u4_ResLen = (uint32)0U;

        if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_START )
        {
            u1_SigNum = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StaOutSigNum;
            if( u1_SigNum != (uint8)0U )
            {
                /* Get bit length */
                if( Dcm_P_SID31_StaOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type != DCM_DSP_VARIABLE_LENGTH )
                {
                    /* Get bit length */
                    u4_BitLen = (uint32)Dcm_P_SID31_StaOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos +  /* no wrap around */
                                            Dcm_Dsp_SID31_TypeTbl[ Dcm_P_SID31_StaOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type];
                    /* Get byte length */
                    u4_ResLen = (uint32)( ( u4_BitLen + ( DCM_DSP_SID31_SIG_BIT8 - (uint8)1U ) ) >> DCM_DSP_SID31_SIG_SHIFT_BYTE ); /* no wrap around */
                }
                else
                {
                    /* Change bit(pos) to byte */
                    u4_BytePos =  (uint32)( (uint32)Dcm_P_SID31_StaOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE );
                    /* Get byte length */
                    u4_ResLen = u4_BytePos + Dcm_P_SID31_StaOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u4Length ; /* no wrap around */
                }
            }
            if( Dcm_P_SID31_Routine_Tbl[u2RoutineIndex].bRoutineInfoUsed == (boolean)TRUE )
            {
                /* Add 1byte(routineInfo) */
                u4_ResLen += (uint32)DCM_DSP_SID31_ROUTINEINFO_LEN; /* no wrap around */
            }
        }
        else if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_STOP )
        {
            u1_SigNum = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StoOutSigNum;
            if( u1_SigNum != (uint8)0U )
            {
                /* Get bit length */
                if( Dcm_P_SID31_StoOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type != DCM_DSP_VARIABLE_LENGTH )
                {
                    /* Get bit length */
                    u4_BitLen = (uint32)Dcm_P_SID31_StoOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos +  /* no wrap around */
                                            Dcm_Dsp_SID31_TypeTbl[ Dcm_P_SID31_StoOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type];
                    /* Get byte length */
                    u4_ResLen = (uint32)( ( u4_BitLen + ( DCM_DSP_SID31_SIG_BIT8 - (uint8)1U ) ) >> DCM_DSP_SID31_SIG_SHIFT_BYTE ); /* no wrap around */
                }
                else
                {
                    /* Change bit(pos) to byte */
                    u4_BytePos =  (uint32)( (uint32)Dcm_P_SID31_StoOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE );
                    /* Get byte length */
                    u4_ResLen = u4_BytePos + Dcm_P_SID31_StoOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u4Length ; /* no wrap around */
                }
            }
        }
        else if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_REQRSLT )
        {
            u1_SigNum = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1ReqRsltOutSigNum;
            if( u1_SigNum != (uint8)0U )
            {
                /* Get bit length */
                if( Dcm_P_SID31_ReqRsltOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type != DCM_DSP_VARIABLE_LENGTH )
                {
                    /* Get bit length */
                    u4_BitLen = (uint32)Dcm_P_SID31_ReqRsltOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos +  /* no wrap around */
                                            Dcm_Dsp_SID31_TypeTbl[Dcm_P_SID31_ReqRsltOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u1Type];
                    /* Get byte length */
                    u4_ResLen = (uint16)( ( u4_BitLen + ( DCM_DSP_SID31_SIG_BIT8 - (uint8)1U ) ) >> DCM_DSP_SID31_SIG_SHIFT_BYTE ); /* no wrap around */
                }
                else
                {
                    /* Change bit(pos) to byte */
                    u4_BytePos =  (uint32)( (uint32)Dcm_P_SID31_ReqRsltOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE );
                    /* Get byte length */
                    u4_ResLen = u4_BytePos + Dcm_P_SID31_ReqRsltOut_Tbl[u2RoutineIndex].ptSignal[u1_SigNum - (uint8)1U].u4Length ; /* no wrap around */
                }
            }
        }
        else
        {
            /* No process */
        }

        u4_ResLen += DCM_DSP_SID31_SUBFUNC_LEN + DCM_DSP_SID31_RID_LEN; /* no wrap around */
        u1_RetVal = Dcm_Dsp_SID31_ChkResLenOVFL( u4_ResLen );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_ChkResLenOVFL                              */
/* Description   | Response message overflow check                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u4ResLen : Response message length                  */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               |   DCM_MAIN_E_CHECK_OK           : Check OK               */
/*               |   DCM_MAIN_E_CHECK_NOT_OK       : Check NG               */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_ChkResLenOVFL
(
    const uint32 u4ResLen
)
{
    Dcm_Main_ReturnCheckType        u1_RetVal;

    u1_RetVal = DCM_MAIN_E_CHECK_NOT_OK;

    if( u4ResLen <= Dcm_Dsp_Main_stMsgContext.resMaxDataLen )
    {
        u1_RetVal = DCM_MAIN_E_CHECK_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_ChkResLenOVFL
(
    const uint32 u4ResLen
)
{
    Dcm_Main_ReturnCheckType        u1_RetVal;

    u1_RetVal = DCM_MAIN_E_CHECK_OK;

    Dcm_Dsp_SID31_u4ResDataLenforPB = (uint32)0U;
    Dcm_Dsp_SID31_u4RemainingResDataLenforPB = (uint32)0U;
    Dcm_Dsp_SID31_bUpdatePageFlag   = (boolean)FALSE;
    Dcm_Dsp_SID31_bProcessEnded     = (boolean)FALSE;

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_SetReqData                                 */
/* Description   | Request data setting                                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message context                    */
/*               | [IN] u2RoutineIndex : Routine Index                      */
/*               | [IN] u1SubFunction  : Sub function                       */
/*               | [OUT]ptSigData      : Signal data                        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_SetReqData
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData
)
{
    P2CONST ( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) pt_InSigInfo;
    P2CONST ( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) pt_OutSigInfo;
    P2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) pt_SigNumInfo;
    uint32  u4_SigData;
    uint16  u2_SigData;
    uint16  u2_BytePos;
    uint16  u2_RIDNum;
    uint8   u1_Endianness;
    uint8   u1_InSigNum;
    uint8   u1_OutSigNum;
    uint8   u1_ReqDataMaskResult;
    uint8   u1_SigCnt;
    uint8   u1_SigPosMask;
    boolean b_RoutineInfoUsed;

    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    if( u2RoutineIndex < u2_RIDNum )
    {
        b_RoutineInfoUsed = (boolean)FALSE;
        if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_START )
        {
            u1_InSigNum   = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StaInSigNum;
            pt_InSigInfo  = Dcm_P_SID31_StaIn_Tbl[u2RoutineIndex].ptSignal;
            u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StaOutSigNum;
            pt_OutSigInfo = Dcm_P_SID31_StaOut_Tbl[u2RoutineIndex].ptSignal;
            pt_SigNumInfo = Dcm_P_SID31_RID_StaInNTbl[u2RoutineIndex];
            b_RoutineInfoUsed = Dcm_P_SID31_Routine_Tbl[u2RoutineIndex].bRoutineInfoUsed;
        }
        else if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_STOP )
        {
            u1_InSigNum   = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StoInSigNum;
            pt_InSigInfo  = Dcm_P_SID31_StoIn_Tbl[u2RoutineIndex].ptSignal;
            u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StoOutSigNum;
            pt_OutSigInfo = Dcm_P_SID31_StoOut_Tbl[u2RoutineIndex].ptSignal;
            pt_SigNumInfo = Dcm_P_SID31_RID_StoInNTbl[u2RoutineIndex];
        }
        else
        {
            u1_InSigNum   = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1ReqRsltInSigNum;
            pt_InSigInfo  = Dcm_P_SID31_ReqRsltIn_Tbl[u2RoutineIndex].ptSignal;
            u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1ReqRsltOutSigNum;
            pt_OutSigInfo = Dcm_P_SID31_ReqRsltOut_Tbl[u2RoutineIndex].ptSignal;
            pt_SigNumInfo = Dcm_P_SID31_RID_ReqRsltInNTbl[u2RoutineIndex];
        }

        /* Set request infomation  */
        for( u1_SigCnt = (uint8)0U; u1_SigCnt < u1_InSigNum; u1_SigCnt++ )
        {
            u2_BytePos = (uint16)( ( pt_InSigInfo[u1_SigCnt].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE ) + DCM_DSP_SID31_SIG_BYTE );

            if( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_VARIABLE_LENGTH )
            {
                ptSigData->ptVarInData = &ptMsgContext->reqData[u2_BytePos];
                ptSigData->u4VarDataLen = pt_InSigInfo[u1_SigCnt].u4Length ;
            }
            else if( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_DYNAMIC_LENGTH )
            {
                ptSigData->ptVarInData = &ptMsgContext->reqData[u2_BytePos];
                ptSigData->u4VarDataLen = (uint32)( ptMsgContext->reqDataLen - DCM_DSP_SID31_SIG_BYTE );    /* no wrap around */
            }
            else if( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_BOOLEAN )
            {
                u1_SigPosMask = DCM_DSP_SID31_SIG_BIT0_ON << ( pt_InSigInfo[u1_SigCnt].u2Pos & DCM_DSP_SID31_SIG_BITMASK );
                u1_ReqDataMaskResult = ptMsgContext->reqData[u2_BytePos] & u1_SigPosMask;
                if( u1_ReqDataMaskResult != (uint8)0U )
                {
                    ptSigData->u4SigData[ptSigData->u1SigInDataNum] = (uint32)TRUE;
                }
                else
                {
                    ptSigData->u4SigData[ptSigData->u1SigInDataNum] = (uint32)FALSE;
                }
                ptSigData->u1SigInDataNum = (uint8)(ptSigData->u1SigInDataNum + (uint8)1U);
            }
            else if( ( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_UINT8 ) || ( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_SINT8 ) )
            {
                ptSigData->u4SigData[ptSigData->u1SigInDataNum] = ptMsgContext->reqData[u2_BytePos];
                ptSigData->u1SigInDataNum = (uint8)(ptSigData->u1SigInDataNum + (uint8)1U);
            }
            else
            {
                if( pt_SigNumInfo[u1_SigCnt].u1SigEndNum != (uint8)0U )
                {
                    if( pt_InSigInfo[u1_SigCnt].u1Endianness != DCM_DSP_OPAQUE )
                    {
                        u1_Endianness = pt_InSigInfo[u1_SigCnt].u1Endianness;
                    }
                    else
                    {
                        u1_Endianness = Dcm_Dsp_u1Data_Default_Endianness;
                    }
                }
                else
                {
                    u1_Endianness = Dcm_Dsp_u1Data_Default_Endianness;
                }

                if( ( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_UINT16 ) || ( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_SINT16 ) )
                {
                    if( u1_Endianness != DCM_DSP_LITTLE_ENDIAN )
                    {
                        /* Byte swapping */
                        u2_SigData = (uint16)ptMsgContext->reqData[u2_BytePos] << DCM_DSP_SID31_SIG_SHIFT_L;
                        u2_SigData = u2_SigData | ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L];
                    }
                    else
                    {
                        u2_SigData = (uint16)ptMsgContext->reqData[u2_BytePos];
                        u2_SigData = u2_SigData | (uint16)( (uint16)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] << DCM_DSP_SID31_SIG_SHIFT_L );
                    }
                    ptSigData->u4SigData[ptSigData->u1SigInDataNum] = (uint32)u2_SigData;
                }
                else
                {
                    if( u1_Endianness != DCM_DSP_LITTLE_ENDIAN )
                    {
                        /* Byte swapping */
                        u4_SigData = (uint32)ptMsgContext->reqData[u2_BytePos] << DCM_DSP_SID31_SIG_SHIFT_H;
                        u4_SigData = u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] << DCM_DSP_SID31_SIG_SHIFT_M );
                        u4_SigData = u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_M] << DCM_DSP_SID31_SIG_SHIFT_L );
                        u4_SigData = u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_H] );
                    }
                    else
                    {
                        u4_SigData = (uint32)ptMsgContext->reqData[u2_BytePos];
                        u4_SigData =  u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] << DCM_DSP_SID31_SIG_SHIFT_L );
                        u4_SigData =  u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_M] << DCM_DSP_SID31_SIG_SHIFT_M );
                        u4_SigData =  u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_H] << DCM_DSP_SID31_SIG_SHIFT_H );
                    }
                    ptSigData->u4SigData[ptSigData->u1SigInDataNum] = u4_SigData;
                }
                ptSigData->u1SigInDataNum = (uint8)(ptSigData->u1SigInDataNum + (uint8)1U);
            }
        }

        /* Set response infomation  */
        Dcm_Dsp_SID31_SetResInfo( ptMsgContext, b_RoutineInfoUsed, u1_OutSigNum, pt_OutSigInfo, ptSigData );
    }

    return;
}
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_SetReqData                                 */
/* Description   | Request data setting                                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message context                    */
/*               | [IN] u2RoutineIndex : Routine Index                      */
/*               | [IN] u1SubFunction  : Sub function                       */
/*               | [OUT]ptSigData      : Signal data                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_SetReqData
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData
)
{
    P2CONST ( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) pt_InSigInfo;
    P2CONST ( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) pt_OutSigInfo;
    P2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) pt_SigNumInfo;
    uint32  u4_SigData;
    uint16  u2_SigData;
    uint16  u2_BytePos;
    uint16  u2_RIDNum;
    uint8   u1_Endianness;
    uint8   u1_InSigNum;
    uint8   u1_OutSigNum;
    uint8   u1_ReqDataMaskResult;
    uint8   u1_SigCnt;
    uint8   u1_SigPosMask;
    Std_ReturnType    u1_RetVal;
    boolean b_RoutineInfoUsed;

    u1_RetVal = E_OK;
    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    if( u2RoutineIndex < u2_RIDNum )
    {
        b_RoutineInfoUsed = (boolean)FALSE;
        if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_START )
        {
            u1_InSigNum   = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StaInSigNum;
            pt_InSigInfo  = Dcm_P_SID31_StaIn_Tbl[u2RoutineIndex].ptSignal;
            u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StaOutSigNum;
            pt_OutSigInfo = Dcm_P_SID31_StaOut_Tbl[u2RoutineIndex].ptSignal;
            pt_SigNumInfo = Dcm_P_SID31_RID_StaInNTbl[u2RoutineIndex];
            b_RoutineInfoUsed = Dcm_P_SID31_Routine_Tbl[u2RoutineIndex].bRoutineInfoUsed;
        }
        else if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_STOP )
        {
            u1_InSigNum   = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StoInSigNum;
            pt_InSigInfo  = Dcm_P_SID31_StoIn_Tbl[u2RoutineIndex].ptSignal;
            u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StoOutSigNum;
            pt_OutSigInfo = Dcm_P_SID31_StoOut_Tbl[u2RoutineIndex].ptSignal;
            pt_SigNumInfo = Dcm_P_SID31_RID_StoInNTbl[u2RoutineIndex];
        }
        else
        {
            u1_InSigNum   = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1ReqRsltInSigNum;
            pt_InSigInfo  = Dcm_P_SID31_ReqRsltIn_Tbl[u2RoutineIndex].ptSignal;
            u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1ReqRsltOutSigNum;
            pt_OutSigInfo = Dcm_P_SID31_ReqRsltOut_Tbl[u2RoutineIndex].ptSignal;
            pt_SigNumInfo = Dcm_P_SID31_RID_ReqRsltInNTbl[u2RoutineIndex];
        }

        /* Set request infomation  */
        for( u1_SigCnt = (uint8)0U; u1_SigCnt < u1_InSigNum; u1_SigCnt++ )
        {
            u2_BytePos = (uint16)( ( pt_InSigInfo[u1_SigCnt].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE ) + DCM_DSP_SID31_SIG_BYTE );

            if( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_VARIABLE_LENGTH )
            {
                ptSigData->ptVarInData = &ptMsgContext->reqData[u2_BytePos];
                ptSigData->u4VarDataLen = pt_InSigInfo[u1_SigCnt].u4Length ;
            }
            else if( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_DYNAMIC_LENGTH )
            {
                ptSigData->ptVarInData = &ptMsgContext->reqData[u2_BytePos];
                ptSigData->u4VarDataLen = (uint32)( ptMsgContext->reqDataLen - DCM_DSP_SID31_SIG_BYTE );    /* no wrap around */
            }
            else if( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_BOOLEAN )
            {
                u1_SigPosMask = DCM_DSP_SID31_SIG_BIT0_ON << ( pt_InSigInfo[u1_SigCnt].u2Pos & DCM_DSP_SID31_SIG_BITMASK );
                u1_ReqDataMaskResult = ptMsgContext->reqData[u2_BytePos] & u1_SigPosMask;
                if( u1_ReqDataMaskResult != (uint8)0U )
                {
                    ptSigData->u4SigData[ptSigData->u1SigInDataNum] = (uint32)TRUE;
                }
                else
                {
                    ptSigData->u4SigData[ptSigData->u1SigInDataNum] = (uint32)FALSE;
                }
                ptSigData->u1SigInDataNum = (uint8)(ptSigData->u1SigInDataNum + (uint8)1U);
            }
            else if( ( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_UINT8 ) || ( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_SINT8 ) )
            {
                ptSigData->u4SigData[ptSigData->u1SigInDataNum] = ptMsgContext->reqData[u2_BytePos];
                ptSigData->u1SigInDataNum = (uint8)(ptSigData->u1SigInDataNum + (uint8)1U);
            }
            else
            {
                if( pt_SigNumInfo[u1_SigCnt].u1SigEndNum != (uint8)0U )
                {
                    if( pt_InSigInfo[u1_SigCnt].u1Endianness != DCM_DSP_OPAQUE )
                    {
                        u1_Endianness = pt_InSigInfo[u1_SigCnt].u1Endianness;
                    }
                    else
                    {
                        u1_Endianness = Dcm_Dsp_u1Data_Default_Endianness;
                    }
                }
                else
                {
                    u1_Endianness = Dcm_Dsp_u1Data_Default_Endianness;
                }

                if( ( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_UINT16 ) || ( pt_InSigInfo[u1_SigCnt].u1Type == DCM_DSP_SINT16 ) )
                {
                    if( u1_Endianness != DCM_DSP_LITTLE_ENDIAN )
                    {
                        /* Byte swapping */
                        u2_SigData = (uint16)ptMsgContext->reqData[u2_BytePos] << DCM_DSP_SID31_SIG_SHIFT_L;
                        u2_SigData = u2_SigData | ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L];
                    }
                    else
                    {
                        u2_SigData = (uint16)ptMsgContext->reqData[u2_BytePos];
                        u2_SigData = u2_SigData | (uint16)( (uint16)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] << DCM_DSP_SID31_SIG_SHIFT_L );
                    }
                    ptSigData->u4SigData[ptSigData->u1SigInDataNum] = (uint32)u2_SigData;
                }
                else
                {
                    if( u1_Endianness != DCM_DSP_LITTLE_ENDIAN )
                    {
                        /* Byte swapping */
                        u4_SigData = (uint32)ptMsgContext->reqData[u2_BytePos] << DCM_DSP_SID31_SIG_SHIFT_H;
                        u4_SigData = u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] << DCM_DSP_SID31_SIG_SHIFT_M );
                        u4_SigData = u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_M] << DCM_DSP_SID31_SIG_SHIFT_L );
                        u4_SigData = u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_H] );
                    }
                    else
                    {
                        u4_SigData = (uint32)ptMsgContext->reqData[u2_BytePos];
                        u4_SigData =  u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] << DCM_DSP_SID31_SIG_SHIFT_L );
                        u4_SigData =  u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_M] << DCM_DSP_SID31_SIG_SHIFT_M );
                        u4_SigData =  u4_SigData | (uint32)( (uint32)ptMsgContext->reqData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_H] << DCM_DSP_SID31_SIG_SHIFT_H );
                    }
                    ptSigData->u4SigData[ptSigData->u1SigInDataNum] = u4_SigData;
                }
                ptSigData->u1SigInDataNum = (uint8)(ptSigData->u1SigInDataNum + (uint8)1U);
            }
        }

        /* Set response infomation  */
        u1_RetVal = Dcm_Dsp_SID31_SetResInfo( ptMsgContext, b_RoutineInfoUsed, u1_OutSigNum, pt_OutSigInfo, ptSigData );
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_SetResData                                 */
/* Description   | Response data setting                                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2RoutineIndex : Routine Index                      */
/*               | [IN] u1SubFunction  : Sub function                       */
/*               | [IN] ptSigData      : Signal data                        */
/*               | [IN] u4VarDataLen   : Variable data length               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_SetResData
(
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction,
    P2CONST( uint32, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    const uint32 u4VarDataLen
)
{
    P2CONST ( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) pt_OutSigInfo;
    P2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) pt_SigNumInfo;
    uint32  u4_BitLen;
    uint32  u4_SigData;
    uint32  u4_BytePos;
    uint32  u4_ResLen;
    uint16  u2_RIDNum;
    uint16  u2_BytePos;
    uint16  u2_SigData;
    uint8   u1_Endianness;
    uint8   u1_OutSigNum;
    uint8   u1_SigCnt;
    uint8   u1_SigType;
    boolean b_RoutineInfoUsed;

    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    if( u2RoutineIndex < u2_RIDNum )
    {
        b_RoutineInfoUsed = (boolean)FALSE;
        if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_START )
        {
            u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StaOutSigNum;
            pt_OutSigInfo = Dcm_P_SID31_StaOut_Tbl[u2RoutineIndex].ptSignal;
            pt_SigNumInfo = Dcm_P_SID31_RID_StaOutNTbl[u2RoutineIndex];

            b_RoutineInfoUsed = Dcm_P_SID31_Routine_Tbl[u2RoutineIndex].bRoutineInfoUsed;
            if( b_RoutineInfoUsed == (boolean)TRUE )
            {
                /* set routineInfo */
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID31_ROUTINEINFO_POS] = Dcm_P_SID31_Routine_Tbl[u2RoutineIndex].u1RoutineInfo;
            }
        }
        else if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_STOP )
        {
            u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StoOutSigNum;
            pt_OutSigInfo = Dcm_P_SID31_StoOut_Tbl[u2RoutineIndex].ptSignal;
            pt_SigNumInfo = Dcm_P_SID31_RID_StoOutNTbl[u2RoutineIndex];
        }
        else
        {
            u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1ReqRsltOutSigNum;
            pt_OutSigInfo = Dcm_P_SID31_ReqRsltOut_Tbl[u2RoutineIndex].ptSignal;
            pt_SigNumInfo = Dcm_P_SID31_RID_ReqRsltOutNTbl[u2RoutineIndex];
        }

        for( u1_SigCnt = (uint8)0U; u1_SigCnt < u1_OutSigNum; u1_SigCnt++ )
        {
            u2_BytePos = (uint16)( ( pt_OutSigInfo[u1_SigCnt].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE ) + DCM_DSP_SID31_SIG_BYTE );
            if( b_RoutineInfoUsed == (boolean)TRUE )
            {
                u2_BytePos += (uint16)DCM_DSP_SID31_ROUTINEINFO_LEN; /* no wrap around */
            }

            if( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_VARIABLE_LENGTH )
            {
                /* resData is already set in the callout function */
            }
            else if( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_BOOLEAN )
            {
                Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos] |= (uint8)( ( (uint8)(ptSigData[u1_SigCnt]) & DCM_DSP_SID31_SIG_BIT0_ON ) << ( pt_OutSigInfo[u1_SigCnt].u2Pos & DCM_DSP_SID31_SIG_BITMASK ) );
            }
            else if( ( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_UINT8 ) || ( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_SINT8 ) )
            {
                Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos] = (uint8)ptSigData[u1_SigCnt];
            }
            else
            {
                if( pt_SigNumInfo[u1_SigCnt].u1SigEndNum != (uint8)0U )
                {
                    if( pt_OutSigInfo[u1_SigCnt].u1Endianness != DCM_DSP_OPAQUE )
                    {
                        u1_Endianness = pt_OutSigInfo[u1_SigCnt].u1Endianness;
                    }
                    else
                    {
                        u1_Endianness = Dcm_Dsp_u1Data_Default_Endianness;
                    }
                }
                else
                {
                    u1_Endianness = Dcm_Dsp_u1Data_Default_Endianness;
                }

                if( ( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_UINT16 ) || ( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_SINT16 ) )
                {
                    u2_SigData = (uint16)ptSigData[u1_SigCnt];
                    if( u1_Endianness != DCM_DSP_LITTLE_ENDIAN )
                    {
                        /* Byte swapping */
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos]                               = (uint8)(u2_SigData >> DCM_DSP_SID31_SIG_SHIFT_L);
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] = (uint8)(u2_SigData);
                    }
                    else
                    {
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos]                               = (uint8)(u2_SigData);
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] = (uint8)(u2_SigData >> DCM_DSP_SID31_SIG_SHIFT_L);
                    }
                }
                else
                {
                    u4_SigData = ptSigData[u1_SigCnt];
                    if( u1_Endianness != DCM_DSP_LITTLE_ENDIAN )
                    {
                        /* Byte swapping */
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos]                               = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_H);
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_M);
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_M] = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_L);
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_H] = (uint8)(u4_SigData);
                    }
                    else
                    {
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos]                               = (uint8)(u4_SigData);
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_L);
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_M] = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_M);
                        Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_H] = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_H);
                    }
                }
            }
        }

        if( u1_OutSigNum != (uint8)0U )
        {
            u1_SigType = pt_OutSigInfo[u1_OutSigNum - (uint8)1U].u1Type;
            /* Get bit length */
            if( u1_SigType != DCM_DSP_VARIABLE_LENGTH )
            {
                u4_BitLen = (uint32)pt_OutSigInfo[u1_OutSigNum - (uint8)1U].u2Pos + Dcm_Dsp_SID31_TypeTbl[u1_SigType];  /* no wrap around */
                /* Get byte length */
                u4_ResLen = (uint32)( ( u4_BitLen + ( DCM_DSP_SID31_SIG_BIT8 - (uint8)1U ) ) >> DCM_DSP_SID31_SIG_SHIFT_BYTE ); /* no wrap around */
            }
            else
            {
                /* Change bit(pos) to byte */
                u4_BytePos =  (uint32)( (uint32)pt_OutSigInfo[u1_OutSigNum - (uint8)1U].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE );
                /* Get byte length */
                u4_ResLen = u4_BytePos + u4VarDataLen;   /* no wrap around */
            }
            /* Get byte length */
            Dcm_Dsp_Main_stMsgContext.resDataLen += (Dcm_MsgLenType)u4_ResLen; /* no wrap around */
        }
        if( b_RoutineInfoUsed == (boolean)TRUE )
        {
            Dcm_Dsp_Main_stMsgContext.resDataLen += (Dcm_MsgLenType)DCM_DSP_SID31_ROUTINEINFO_LEN; /* no wrap around */
        }
    }

    return;
}

#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_SetResData                                 */
/* Description   | Response data setting                                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2RoutineIndex : Routine Index                      */
/*               | [IN] u1SubFunction  : Sub function                       */
/*               | [IN] ptSigData      : Signal data                        */
/*               | [IN] u4PageDataLen  : Page data length                   */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_SetResData
(
    const uint16 u2RoutineIndex,
    const uint8 u1SubFunction,
    P2CONST( uint32, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    const uint32 u4PageDataLen
)
{
    P2CONST ( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) pt_OutSigInfo;
    P2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) pt_SigNumInfo;
    uint32  u4_SigData;
    uint16  u2_RIDNum;
    uint16  u2_BytePos;
    uint16  u2_SigData;
    uint8   u1_Endianness;
    uint8   u1_OutSigNum;
    uint8   u1_SigCnt;
    boolean b_RoutineInfoUsed;

    u2_RIDNum = Dcm_P_SID31_u2RIDNumber;
    if( Dcm_Dsp_SID31_bUpdatePageFlag == (boolean)FALSE )
    {
        if( u2RoutineIndex < u2_RIDNum )
        {
            b_RoutineInfoUsed = (boolean)FALSE;
            if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_START )
            {
                u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StaOutSigNum;
                pt_OutSigInfo = Dcm_P_SID31_StaOut_Tbl[u2RoutineIndex].ptSignal;
                pt_SigNumInfo = Dcm_P_SID31_RID_StaOutNTbl[u2RoutineIndex];

                b_RoutineInfoUsed = Dcm_P_SID31_Routine_Tbl[u2RoutineIndex].bRoutineInfoUsed;
                if( b_RoutineInfoUsed == (boolean)TRUE )
                {
                    /* set routineInfo */
                    Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID31_ROUTINEINFO_POS] = Dcm_P_SID31_Routine_Tbl[u2RoutineIndex].u1RoutineInfo;
                }
            }
            else if( u1SubFunction == DCM_DSP_SID31_SUBFUNC_STOP )
            {
                u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1StoOutSigNum;
                pt_OutSigInfo = Dcm_P_SID31_StoOut_Tbl[u2RoutineIndex].ptSignal;
                pt_SigNumInfo = Dcm_P_SID31_RID_StoOutNTbl[u2RoutineIndex];
            }
            else
            {
                u1_OutSigNum  = Dcm_P_SID31_RIDN_Tbl[u2RoutineIndex].u1ReqRsltOutSigNum;
                pt_OutSigInfo = Dcm_P_SID31_ReqRsltOut_Tbl[u2RoutineIndex].ptSignal;
                pt_SigNumInfo = Dcm_P_SID31_RID_ReqRsltOutNTbl[u2RoutineIndex];
            }
            for( u1_SigCnt = (uint8)0U; u1_SigCnt < u1_OutSigNum; u1_SigCnt++ )
            {
                u2_BytePos = (uint16)( ( pt_OutSigInfo[u1_SigCnt].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE ) + DCM_DSP_SID31_SIG_BYTE );
                if( b_RoutineInfoUsed == (boolean)TRUE )
                {
                    u2_BytePos += (uint16)DCM_DSP_SID31_ROUTINEINFO_LEN; /* no wrap around */
                }

                if( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_VARIABLE_LENGTH )
                {
                    /* resData is already set in the callout function */
                }
                else if( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_BOOLEAN )
                {
                    Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos] |= (uint8)( ( (uint8)(ptSigData[u1_SigCnt]) & DCM_DSP_SID31_SIG_BIT0_ON ) << ( pt_OutSigInfo[u1_SigCnt].u2Pos & DCM_DSP_SID31_SIG_BITMASK ) );
                }
                else if( ( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_UINT8 ) || ( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_SINT8 ) )
                {
                    Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos] = (uint8)ptSigData[u1_SigCnt];
                }
                else
                {
                    if( pt_SigNumInfo[u1_SigCnt].u1SigEndNum != (uint8)0U )
                    {
                        if( pt_OutSigInfo[u1_SigCnt].u1Endianness != DCM_DSP_OPAQUE )
                        {
                            u1_Endianness = pt_OutSigInfo[u1_SigCnt].u1Endianness;
                        }
                        else
                        {
                            u1_Endianness = Dcm_Dsp_u1Data_Default_Endianness;
                        }
                    }
                    else
                    {
                        u1_Endianness = Dcm_Dsp_u1Data_Default_Endianness;
                    }

                    if( ( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_UINT16 ) || ( pt_OutSigInfo[u1_SigCnt].u1Type == DCM_DSP_SINT16 ) )
                    {
                        u2_SigData = (uint16)ptSigData[u1_SigCnt];
                        if( u1_Endianness != DCM_DSP_LITTLE_ENDIAN )
                        {
                            /* Byte swapping */
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos]                               = (uint8)(u2_SigData >> DCM_DSP_SID31_SIG_SHIFT_L);
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] = (uint8)(u2_SigData);
                        }
                        else
                        {
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos]                               = (uint8)(u2_SigData);
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] = (uint8)(u2_SigData >> DCM_DSP_SID31_SIG_SHIFT_L);
                        }
                    }
                    else
                    {
                        u4_SigData = ptSigData[u1_SigCnt];
                        if( u1_Endianness != DCM_DSP_LITTLE_ENDIAN )
                        {
                            /* Byte swapping */
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos]                               = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_H);
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_M);
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_M] = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_L);
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_H] = (uint8)(u4_SigData);
                        }
                        else
                        {
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos]                               = (uint8)(u4_SigData);
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_L] = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_L);
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_M] = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_M);
                            Dcm_Dsp_Main_stMsgContext.resData[u2_BytePos + DCM_DSP_SID31_SIG_BYTEPOS_H] = (uint8)(u4_SigData >> DCM_DSP_SID31_SIG_SHIFT_H);
                        }
                    }
                }
            }
            /* Set response data Length */
            Dcm_Dsp_SID31_SetResDataLen( pt_OutSigInfo, u1_OutSigNum, u4PageDataLen, b_RoutineInfoUsed );
        }
    }
    else
    {
        Dcm_Dsp_Main_stMsgContext.resDataLen = u4PageDataLen;
    }
    
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_SetResDataLen                              */
/* Description   | Response data length setting                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptOutSigInfo      : Out Signal Info                 */
/*               | [IN] u1OutSigNum       : Out Signal Num                  */
/*               | [IN] u4PageDataLen     : Page data length                */
/*               | [IN] bRoutineInfoUsed  : Routine Info Used               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_SetResDataLen
(
    P2CONST( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) ptOutSigInfo,
    const uint8  u1OutSigNum,
    const uint32 u4PageDataLen,
    const boolean bRoutineInfoUsed
)
{
    uint32  u4_BitLen;
    uint32  u4_BytePos;
    uint32  u4_ResLen;
    uint8   u1_SigType;

    if( u1OutSigNum != (uint8)0U )
    {
        u1_SigType = ptOutSigInfo[u1OutSigNum - (uint8)1U].u1Type;
        if( u1_SigType != DCM_DSP_VARIABLE_LENGTH )
        {
            /* Get bit length */
            u4_BitLen = (uint32)ptOutSigInfo[u1OutSigNum - (uint8)1U].u2Pos + Dcm_Dsp_SID31_TypeTbl[u1_SigType];  /* no wrap around */
            /* Get byte length */
            u4_ResLen = (uint32)( ( u4_BitLen + ( DCM_DSP_SID31_SIG_BIT8 - (uint8)1U ) ) >> DCM_DSP_SID31_SIG_SHIFT_BYTE ); /* no wrap around */
        }
        else
        {
            /* Change bit(pos) to byte */
            u4_BytePos =  (uint32)( (uint32)ptOutSigInfo[u1OutSigNum - (uint8)1U].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE );
            /* Get byte length */
            u4_ResLen = u4_BytePos + u4PageDataLen;   /* no wrap around */
        }
        /* Get byte length */
        Dcm_Dsp_Main_stMsgContext.resDataLen += (Dcm_MsgLenType)u4_ResLen; /* no wrap around */
    }
    if( bRoutineInfoUsed == (boolean)TRUE )
    {
        Dcm_Dsp_Main_stMsgContext.resDataLen += (Dcm_MsgLenType)DCM_DSP_SID31_ROUTINEINFO_LEN; /* no wrap around */
    }

    return;
}

#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_SetResInfo                                 */
/* Description   | Set response infomation                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext     : Message context                  */
/*               | [IN] bRoutineInfoUsed : RoutineInfoUsed                  */
/*               | [IN] u1OutSigNum      : Out Signal Num                   */
/*               | [IN] ptOutSigInfo     : Out Signal Info                  */
/*               | [OUT] ptSigData       : Signal data                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID31_SetResInfo
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const boolean bRoutineInfoUsed,
    const uint8 u1OutSigNum,
    P2CONST( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) ptOutSigInfo,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData
)
{
    uint32  u4_BitLen;
    uint16  u2_BufCnt;
    uint16  u2_BytePos;
    uint8   u1_SigCnt;
    uint8   u1_SigType;

    for( u1_SigCnt = (uint8)0U; u1_SigCnt < u1OutSigNum; u1_SigCnt++ )
    {
        if( ptOutSigInfo[u1_SigCnt].u1Type == DCM_DSP_VARIABLE_LENGTH )
        {
            u2_BytePos = (uint16)( ( ptOutSigInfo[u1_SigCnt].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE ) + DCM_DSP_SID31_SIG_BYTE );
            if( bRoutineInfoUsed == (boolean)TRUE )
            {
                u2_BytePos += (uint16)DCM_DSP_SID31_ROUTINEINFO_LEN;   /* no wrap around */
            }
            ptSigData->ptVarOutData = &ptMsgContext->resData[u2_BytePos];
        }
        else
        {
            ptSigData->u1SigOutDataNum = (uint8)(ptSigData->u1SigOutDataNum + (uint8)1U);
        }
    }

    if( u1OutSigNum != (uint8)0U )
    {
        u1_SigType = ptOutSigInfo[u1OutSigNum - (uint8)1U].u1Type;
       /* Get bit length */
        if( u1_SigType != DCM_DSP_VARIABLE_LENGTH )
        {
            u4_BitLen = (uint32)ptOutSigInfo[u1OutSigNum - (uint8)1U].u2Pos + Dcm_Dsp_SID31_TypeTbl[u1_SigType];  /* no wrap around */
            u2_BytePos = (uint16)( ( u4_BitLen + ( DCM_DSP_SID31_SIG_BIT8 - (uint8)1U ) ) >> DCM_DSP_SID31_SIG_SHIFT_BYTE ); /* no wrap around */
        }
        else
        {
            u2_BytePos = (uint16)ptOutSigInfo[u1OutSigNum - (uint8)1U].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE;
        }
        if( bRoutineInfoUsed == (boolean)TRUE )
        {
            u2_BytePos += (uint16)DCM_DSP_SID31_ROUTINEINFO_LEN;   /* no wrap around */
        }

        /* Response data clear */
        for( u2_BufCnt = (uint16)0U; u2_BufCnt < u2_BytePos; u2_BufCnt++ )
        {
            ptMsgContext->resData[DCM_DSP_SID31_SIG_BYTE + u2_BufCnt] = (uint8)0x00U;
        }
        Dcm_Dsp_SID31_u2ExpectedSettingLen = u2_BytePos;
    }

    return;
}

#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_SetResInfo                                 */
/* Description   | Set response infomation                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext     : Message context                  */
/*               | [IN] bRoutineInfoUsed : RoutineInfoUsed                  */
/*               | [IN] u1OutSigNum      : Out Signal Num                   */
/*               | [IN] ptOutSigInfo     : Out Signal Info                  */
/*               | [OUT] ptSigData       : Signal data                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_SetResInfo
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const boolean bRoutineInfoUsed,
    const uint8 u1OutSigNum,
    P2CONST( AB_83_ConstV Dcm_Dsp_SigType, AUTOMATIC, DCM_APPL_CONST ) ptOutSigInfo,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData
)
{
    uint32  u4_FixedDataLen;
    uint32  u4_PageLen;
    uint32  u4_BitLen;
    uint16  u2_BufCnt;
    uint16  u2_BytePos;
    uint8   u1_SigCnt;
    uint8   u1_SigType;
    Std_ReturnType  u1_RetVal;
    boolean b_CalcPageDataLen;

    u1_RetVal = E_OK;

    if( Dcm_Dsp_SID31_bUpdatePageFlag == (boolean)FALSE )
    {
        for( u1_SigCnt = (uint8)0U; u1_SigCnt < u1OutSigNum; u1_SigCnt++ )
        {
            if( ptOutSigInfo[u1_SigCnt].u1Type == DCM_DSP_VARIABLE_LENGTH )
            {
                u2_BytePos = (uint16)( ( ptOutSigInfo[u1_SigCnt].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE ) + DCM_DSP_SID31_SIG_BYTE );
                if( bRoutineInfoUsed == (boolean)TRUE )
                {
                    u2_BytePos += (uint16)DCM_DSP_SID31_ROUTINEINFO_LEN;   /* no wrap around */
                }
                ptSigData->ptVarOutData = &ptMsgContext->resData[u2_BytePos];
            }
            else
            {
                ptSigData->u1SigOutDataNum = (uint8)(ptSigData->u1SigOutDataNum + (uint8)1U);
            }
        }

        b_CalcPageDataLen = (boolean)FALSE;
        if( u1OutSigNum != (uint8)0U )
        {
            u1_SigType = ptOutSigInfo[u1OutSigNum - (uint8)1U].u1Type;
            /* Get bit length */
            if( u1_SigType != DCM_DSP_VARIABLE_LENGTH )
            {
                u4_BitLen = (uint32)ptOutSigInfo[u1OutSigNum - (uint8)1U].u2Pos + Dcm_Dsp_SID31_TypeTbl[u1_SigType];  /* no wrap around */
                u2_BytePos = (uint16)( ( u4_BitLen + ( DCM_DSP_SID31_SIG_BIT8 - (uint8)1U ) ) >> DCM_DSP_SID31_SIG_SHIFT_BYTE ); /* no wrap around */
            }
            else
            {
                u2_BytePos = (uint16)ptOutSigInfo[u1OutSigNum - (uint8)1U].u2Pos >> DCM_DSP_SID31_SIG_SHIFT_BYTE;
                b_CalcPageDataLen = (boolean)TRUE;
            }
            if( bRoutineInfoUsed == (boolean)TRUE )
            {
                u2_BytePos += (uint16)DCM_DSP_SID31_ROUTINEINFO_LEN;   /* no wrap around */
            }

            /* Response data clear */
            for( u2_BufCnt = (uint16)0U; u2_BufCnt < u2_BytePos; u2_BufCnt++ )
            {
                ptMsgContext->resData[DCM_DSP_SID31_SIG_BYTE + u2_BufCnt] = (uint8)0x00U;
            }
            Dcm_Dsp_SID31_u2ExpectedSettingLen = u2_BytePos;
        }
        /* Check length of response message up to fixed length  */
        u4_FixedDataLen = (uint32)( Dcm_Dsp_Main_stMsgContext.resDataLen + (uint32)Dcm_Dsp_SID31_u2ExpectedSettingLen );
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= u4_FixedDataLen )
        {
            if( b_CalcPageDataLen == (boolean)TRUE )
            {
                /* Calculate free buffer size for response */
                u4_PageLen = (uint32)( Dcm_Dsp_Main_stMsgContext.resMaxDataLen - u4_FixedDataLen ); /* no wrap around */
                ptSigData->u4PageDataLen = u4_PageLen;
            }
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        for( u1_SigCnt = (uint8)0U; u1_SigCnt < u1OutSigNum; u1_SigCnt++ )
        {
            if( ptOutSigInfo[u1_SigCnt].u1Type == DCM_DSP_VARIABLE_LENGTH )
            {
                ptSigData->ptVarOutData = &ptMsgContext->resData[0];
            }
        }
        Dcm_Dsp_SID31_u2ExpectedSettingLen = (uint16)0U;
        
        ptSigData->u4PageDataLen = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
    }



    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_StartPage                                  */
/* Description   | StartPagedProcessing                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID31_StartPage
(
    void
)
{
    uint16              u2_PbidSid31;
    Dcm_MsgContextType  st_MsgContext;

    u2_PbidSid31 = Dcm_P_u2Pbid_Sid31;

    st_MsgContext.reqData                           = NULL_PTR;
    st_MsgContext.reqDataLen                        = (Dcm_MsgLenType)0U;
    st_MsgContext.resData                           = NULL_PTR;
    st_MsgContext.msgAddInfo.reqType                = (uint8)0U;
    st_MsgContext.msgAddInfo.suppressPosResponse    = STD_OFF;
    st_MsgContext.resMaxDataLen                     = (Dcm_MsgLenType)0U;
    st_MsgContext.idContext                         = (Dcm_IdContextType)0U;
    st_MsgContext.dcmRxPduId                        = (PduIdType)0U;
    st_MsgContext.resDataLen                        = Dcm_Dsp_SID31_u4ResDataLenforPB;

    Dcm_Dsp_MsgMaker_StartPagedProcessing( &st_MsgContext, u2_PbidSid31 );

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_AdjustDataLenForPage                       */
/* Description   | Adjust data length for page                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID31_AdjustDataLenForPage
(
    void
)
{
    uint32              u4_RemainingResDataLenforPB;
    uint32              u4_ResMaxPageLen;
    uint32              u4_ResRemainingPageLen;
    uint32              u4_ResDataLen;
    uint32              u4_ResDataPos;
    uint32              u4_PaddingMaxDataLen;
    uint32              u4_PaddingCnt;

    u4_RemainingResDataLenforPB = Dcm_Dsp_SID31_u4RemainingResDataLenforPB;
    if( u4_RemainingResDataLenforPB > (uint32)0 )
    {
        u4_ResMaxPageLen       = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
        u4_ResDataLen          = Dcm_Dsp_Main_stMsgContext.resDataLen;
        u4_ResRemainingPageLen = u4_ResMaxPageLen - u4_ResDataLen; /* no wrap around */
        if( u4_RemainingResDataLenforPB > u4_ResRemainingPageLen )
        {
            u4_PaddingMaxDataLen = u4_ResMaxPageLen;
        }
        else
        {
            u4_PaddingMaxDataLen = u4_RemainingResDataLenforPB + u4_ResDataLen; /* no wrap around */
        }
        u4_PaddingCnt = u4_PaddingMaxDataLen - u4_ResDataLen; /* no wrap around */
        for( u4_ResDataPos = u4_ResDataLen; u4_ResDataPos < u4_PaddingMaxDataLen; u4_ResDataPos++ )
        {
            Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)0;
        }
        Dcm_Dsp_Main_stMsgContext.resDataLen = u4_PaddingMaxDataLen;
        Dcm_Dsp_SID31_u4RemainingResDataLenforPB = Dcm_Dsp_SID31_u4RemainingResDataLenforPB - u4_PaddingCnt; /* no wrap around */
    }
    return ;
}
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID31 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-08-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
