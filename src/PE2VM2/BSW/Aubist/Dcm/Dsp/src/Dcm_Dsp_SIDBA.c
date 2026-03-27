/* Dcm_Dsp_SIDBA_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SIDBA/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if( DCM_SUPPORT_SIDBA == STD_ON )

#include <Dcm/Dcm_Dsp_SIDBA.h>
#include "../../Dsp/cfg/Dcm_Dsp_SIDBA_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SIDBA_SUB02                  ((uint8)0x02U)
#define DCM_DSP_SIDBA_SUB03                  ((uint8)0x03U)
#define DCM_DSP_SIDBA_SUB04                  ((uint8)0x04U)
#define DCM_DSP_SIDBA_REQ_DATA_LEN           ((Dcm_MsgLenType)0U) /* Requested data size for subfunction02 and subfunction03 */
#define DCM_DSP_SIDBA_RES_DATA_MIN_LEN       ((Dcm_MsgLenType)0U) /* Minimum size of response data for subfunction02 and subfunction03 */
#define DCM_DSP_SIDBA_REQ_DATA_SUB04_LEN     ((Dcm_MsgLenType)4U) /* Requested data size for subfunction04 */
#define DCM_DSP_SIDBA_RES_DATA_SUB04_MIN_LEN ((Dcm_MsgLenType)2U) /* Minimum size of response data for subfunction04 */
#define DCM_DSP_SIDBA_REQ_DATA_SHFT_H        ((uint8)8U)
#define DCM_DSP_SIDBA_REQ_DATA_CODE_H        ((uint8)0U)
#define DCM_DSP_SIDBA_REQ_DATA_CODE_L        ((uint8)1U)
#define DCM_DSP_SIDBA_REQ_DATA_FRAME_H       ((uint8)2U)
#define DCM_DSP_SIDBA_REQ_DATA_FRAME_L       ((uint8)3U)
#define DCM_DSP_SIDBA_RES_DATA_CODE_H        ((uint8)0U)
#define DCM_DSP_SIDBA_RES_DATA_CODE_L        ((uint8)1U)
#define DCM_DSP_SIDBA_BEHAVIORMEMORY_INVALID ((uint16)0xFFFFU)
#define DCM_DSP_SIDBA_FRAMENUM_INVALID       ((uint16)0xFFFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDBA_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1SubFunction
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SIDBA_CancelProc
(
    const uint8 u1SubFunction
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDBA_GetBehaviorMemoryInfo
(
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) u1ErrorCode
);

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
/* Function Name | Dcm_SIDBA_Sub02                                          */
/* Description   | Request processing of SID BA subfunction 02              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK             : Processing normal                   */
/*               |   DCM_E_PENDING    : Pending                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SIDBA_Sub02
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SIDBA_InitialProc( pMsgContext, DCM_DSP_SIDBA_SUB02 );
    }
    else
    {
        Dcm_Dsp_SIDBA_CancelProc( DCM_DSP_SIDBA_SUB02 );
    }
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_SIDBA_Sub03                                          */
/* Description   | Request processing of SID BA subfunction 03              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK             : Processing normal                   */
/*               |   DCM_E_PENDING    : Pending                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SIDBA_Sub03
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SIDBA_InitialProc( pMsgContext, DCM_DSP_SIDBA_SUB03 );
    }
    else
    {
        Dcm_Dsp_SIDBA_CancelProc( DCM_DSP_SIDBA_SUB03 );
    }
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_SIDBA_Sub04                                          */
/* Description   | Request processing of SID BA subfunction 04              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK             : Processing normal                   */
/*               |   DCM_E_PENDING    : Pending                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SIDBA_Sub04
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;
    
    u1_RetVal = E_OK;
    
    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SIDBA_InitialProc( pMsgContext, DCM_DSP_SIDBA_SUB04 );
    }
    else
    {
        Dcm_Dsp_SIDBA_CancelProc( DCM_DSP_SIDBA_SUB04 );
    }
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDBA_Cbk                                        */
/* Description   | Call Back Function to Continue SIDBA Processing          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event Id                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SIDBA_Cbk
(
    const uint8 u1EventId
)
{
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrCode;

    u1_ErrCode = DCM_E_GENERALREJECT;

    u1_RetVal = Dcm_Dsp_SIDBA_GetBehaviorMemoryInfo( &u1_ErrCode );
    if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrCode );
    }

    return ;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDBA_InitialProc                                */
/* Description   | Initial process of SIDBA Subfunction 0xXX                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/*               | [IN] u1SubFunction  : Sub-Function Code                  */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                : Result OK                          */
/*               | DCM_E_PENDING       : Result Pending                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SIDBA_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    const uint8 u1SubFunction
)
{
    Dcm_MsgLenType                  u4_ReqDataLen;
    Dcm_MsgLenType                  u4_ResMinDataLen;
    uint16                          u2_BehaviorMemoryCode;
    uint16                          u2_FrameNumber;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetGetBehaviorMemory;
    boolean                         b_SendNegRes;

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    u1_NegResCode       = DCM_E_GENERALREJECT;
    b_SendNegRes        = (boolean)FALSE;
    u1_RetVal           = E_OK;
    
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    /* Set Common Data */
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    
    /* Check Sub Function Type */
    if( u1SubFunction == DCM_DSP_SIDBA_SUB04 )
    {
        u4_ReqDataLen = DCM_DSP_SIDBA_REQ_DATA_SUB04_LEN;
        u4_ResMinDataLen = DCM_DSP_SIDBA_RES_DATA_SUB04_MIN_LEN;
        u2_BehaviorMemoryCode = (uint16)( (uint16)(Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SIDBA_REQ_DATA_CODE_H ]) << DCM_DSP_SIDBA_REQ_DATA_SHFT_H ) |
                                (uint16)( Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SIDBA_REQ_DATA_CODE_L ] );
        u2_FrameNumber = (uint16)( (uint16)(Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SIDBA_REQ_DATA_FRAME_H ]) << DCM_DSP_SIDBA_REQ_DATA_SHFT_H ) |
                         (uint16)( Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SIDBA_REQ_DATA_FRAME_L ] );
    }
    else
    {
        u4_ReqDataLen = DCM_DSP_SIDBA_REQ_DATA_LEN;
        u4_ResMinDataLen = DCM_DSP_SIDBA_RES_DATA_MIN_LEN;
        u2_BehaviorMemoryCode = DCM_DSP_SIDBA_BEHAVIORMEMORY_INVALID;
        u2_FrameNumber = DCM_DSP_SIDBA_FRAMENUM_INVALID;
    }
    
    /* Check Request Data Length */
    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == u4_ReqDataLen )
    {
        /* Check Response Data Area Length */
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= u4_ResMinDataLen )
        {
            if( u1SubFunction == DCM_DSP_SIDBA_SUB04 )
            {
                Dcm_Dsp_Main_stMsgContext.resData[ DCM_DSP_SIDBA_RES_DATA_CODE_H ] = Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SIDBA_REQ_DATA_CODE_H ];
                Dcm_Dsp_Main_stMsgContext.resData[ DCM_DSP_SIDBA_RES_DATA_CODE_L ] = Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SIDBA_REQ_DATA_CODE_L ];
            }
            Dcm_Dsp_Main_stMsgContext.resDataLen = u4_ResMinDataLen;
            
            (void)Dcm_Dsp_SIDBA_BehaviorMemory_ReportRequest( DCM_INITIAL, u1SubFunction, u2_BehaviorMemoryCode, u2_FrameNumber ); /* no return check required */
            u1_RetGetBehaviorMemory = Dcm_Dsp_SIDBA_GetBehaviorMemoryInfo( &u1_NegResCode );
            
            if( u1_RetGetBehaviorMemory == (Std_ReturnType)E_OK )
            {
                u1_RetVal = E_OK;
            }
            else if( u1_RetGetBehaviorMemory == (Std_ReturnType)DCM_E_PENDING )
            {
                u1_RetVal = DCM_E_PENDING;
            }
            else
            {
                /* NRC 0x31, 0x14, 0x22 */
                b_SendNegRes    = (boolean)TRUE;
            }
        }
        else
        {
            /* NRC 0x14 */
            u1_NegResCode   = DCM_E_RESPONSETOOLONG;
            b_SendNegRes    = (boolean)TRUE;
        }
    }
    else
    {
        /* NRC 0x13 */
        u1_NegResCode   = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegRes    = (boolean)TRUE;
    }
    
    if( b_SendNegRes == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDBA_CancelProc                                 */
/* Description   | SIDBA request cancel processing                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SubFunction  : Sub-Function Code                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SIDBA_CancelProc
(
    const uint8 u1SubFunction
)
{
    boolean                         b_UserNotifyFlag;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SIDBA_BehaviorMemory_ReportRequest( DCM_CANCEL, u1SubFunction, DCM_DSP_SIDBA_BEHAVIORMEMORY_INVALID, DCM_DSP_SIDBA_FRAMENUM_INVALID ); /* no return check required */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SIDBA_GETBEHAVIORMEMORY, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDBA_GetBehaviorMemoryInfo                      */
/* Description   | Get BehaviorMemory Information                           */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] u1ErrorCode   : NRC Error Code                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                : Result OK                          */
/*               | E_NOT_OK            : Result Not OK                      */
/*               | DCM_E_PENDING       : Result Pending                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SIDBA_GetBehaviorMemoryInfo
(
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) u1ErrorCode

)
{
    uint32                          u4_DataBufferLength;
    uint32                          u4_DataLength;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetGetInfo;
    Dcm_NegativeResponseCodeType    u1_ErrCode;

    u4_DataLength = Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen; /* no wrap around */
    u1_ErrCode = DCM_E_GENERALREJECT;
    u1_RetVal = E_NOT_OK;
    
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    
    u1_RetGetInfo = Dcm_Dsp_SIDBA_BehaviorMemory_GetInfo( &Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ],
                                                          &u4_DataLength,
                                                          &u1_ErrCode );
    
    if( u1_RetGetInfo == (Std_ReturnType)E_OK )
    {
        u4_DataBufferLength = Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen; /* no wrap around */
        if( u4_DataLength <= u4_DataBufferLength )
        {
            Dcm_Dsp_Main_stMsgContext.resDataLen += u4_DataLength; /* no wrap around */
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            u1_RetVal = E_OK;
        }
        else
        {
            *u1ErrorCode = DCM_E_RESPONSETOOLONG;
        }
    }
    else if( u1_RetGetInfo == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SIDBA_GETBEHAVIORMEMORY ); /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        *u1ErrorCode = u1_ErrCode;
    }
    
    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SIDBA == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
