/* Dcm_Dsp_SID19_Sub1A(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub1A/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub1A.h>
#if ( DCM_SUPPORT_SID19_SUB1A == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID19_Sub1A_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID19_SUB1A_SHFT_DTC_HI                 ((uint8)16U)
#define     DCM_DSP_SID19_SUB1A_SHFT_DTC_MI                 ((uint8)8U)
#define     DCM_DSP_SID19_SUB1A_DTC_EDRN_NUM01              ((uint8)0x01U)
#define     DCM_DSP_SID19_SUB1A_DTC_EDRN_NUM90              ((uint8)0x90U)
#define     DCM_DSP_SID19_SUB1A_DTC_EDRN_NUM9F              ((uint8)0x9FU)
#define     DCM_DSP_SID19_SUB1A_DTC_EDRN_NUMFD              ((uint8)0xFDU)
#define     DCM_DSP_SID19_SUB1A_DTC_ST_MSK_00               ((uint8)0x00U)
#define     DCM_DSP_SID19_SUB1A_DTC_ST_AVAIL_MSK_LEN        ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB1A_DTC_EDRN_LEN                ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB1A_DTC_LEN                     ((Dcm_MsgLenType)3U)
#define     DCM_DSP_SID19_SUB1A_DTC_ST_LEN                  ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB1A_DTC_DASR_LEN                ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB1A_DTC_LEN + DCM_DSP_SID19_SUB1A_DTC_ST_LEN))
#define     DCM_DSP_SID19_SUB1A_REQ_OFFSET_DTC_EDRN         ((uint32)0U)
#define     DCM_DSP_SID19_SUB1A_REQ_DATA_LEN                (DCM_DSP_SID19_SUB1A_DTC_EDRN_LEN)
#define     DCM_DSP_SID19_SUB1A_RES_OFFSET_DTC_ST_AVAIL_MSK ((uint32)0U)
#define     DCM_DSP_SID19_SUB1A_RES_DATA_MIN_LEN            (DCM_DSP_SID19_SUB1A_DTC_ST_AVAIL_MSK_LEN)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_CancelProc
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_GetDTC
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_ChkEnableRecNum
(
    const uint8 u1DTCRecNum
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
/* Function Name | Dcm_SID19_Sub1A                                          */
/* Description   | Request processing of SID19_Sub1A                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/*               |   DCM_E_PENDING  : Pending                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID19_Sub1A
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub1A_InitialProc( pMsgContext );
    }
    else
    {
        Dcm_Dsp_SID19_Sub1A_CancelProc();
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_Cbk                                  */
/* Description   | Call Back Function to Continue SID19_Sub1A Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_Cbk
(
    const uint8 u1EventId
)
{
    (void)Dcm_Dsp_SID19_Sub1A_GetDTC();     /* no return check required */

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_InitialProc                          */
/* Description   | Initial process of SID19_Sub1A request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK            : Processing normal                    */
/*               |   DCM_E_PENDING   : Pending                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dcm_MsgItemType                 u1_ReqEDRN;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dem_ReturnSetFilterType         u1_RetDemFilter;
    Std_ReturnType                  u1_RetStatusAvailabilityMask;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkEnableRecNum;
    boolean                         b_SendNegResFlag;

    b_SendNegResFlag = (boolean)FALSE;
    u1_NegResCode    = DCM_E_GENERALREJECT;
    u1_RetVal        = E_OK;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID19_SUB1A_REQ_DATA_LEN )
    {
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= DCM_DSP_SID19_SUB1A_RES_DATA_MIN_LEN )
        {
            u1_ReqEDRN = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB1A_REQ_OFFSET_DTC_EDRN];
            
            u1_RetChkEnableRecNum = Dcm_Dsp_SID19_Sub1A_ChkEnableRecNum( u1_ReqEDRN );
            
            if( u1_RetChkEnableRecNum == (Std_ReturnType)E_NOT_OK )
            {
                u1_NegResCode = DCM_E_REQUESTOUTOFRANGE;
                b_SendNegResFlag = (boolean)TRUE;
            }
            else
            {
                u1_DTCStatusMask = DCM_DSP_SID19_SUB1A_DTC_ST_MSK_00;
                u1_RetStatusAvailabilityMask = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask,
                                                                                    DEM_DTC_ORIGIN_PRIMARY_MEMORY );
                if( u1_RetStatusAvailabilityMask == (Std_ReturnType)E_OK )
                {
                    u1_RetDemFilter = Dem_DcmSetEDRNumberFilter( u1_ReqEDRN );
                    if( u1_RetDemFilter == DEM_FILTER_ACCEPTED )
                    {
                        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB1A_RES_OFFSET_DTC_ST_AVAIL_MSK] = u1_DTCStatusMask;
                        Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB1A_DTC_ST_AVAIL_MSK_LEN;

                        u1_RetVal = Dcm_Dsp_SID19_Sub1A_GetDTC();
                    }
                    else if( u1_RetDemFilter == DEM_WRONG_FILTER )
                    {
                        u1_NegResCode = DCM_E_REQUESTOUTOFRANGE;
                        b_SendNegResFlag = (boolean)TRUE;
                    }
                    else
                    {
                        /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                        b_SendNegResFlag = (boolean)TRUE;
                    }
                }
                else
                {
                    /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                    b_SendNegResFlag = (boolean)TRUE;
                }
            }
        }
        else
        {
            u1_NegResCode = DCM_E_RESPONSETOOLONG;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        u1_NegResCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_NegResCode );
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_CancelProc                           */
/* Description   | Cancel process of SID19_Sub1A request                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_CancelProc
( void )
{
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB1A_GETDTC,    /* no return check required */
                                         (boolean)FALSE );

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_GetDTC                               */
/* Description   | Get DTC and Edit Response or Register Event              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          : Result OK                                */
/*               | DCM_E_PENDING : Result Pending                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_GetDTC
( void )
{
    uint32                                  u4_DTC;
    Dcm_MsgLenType                          u4_ResDataPos;
    Dem_UdsStatusByteType                   u1_DTCStatus;
    Dem_ReturnGetNextFilteredElementType    u1_RetNextDTC;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    Std_ReturnType                          u1_RetVal;
    boolean                                 b_LenChkResult;
    boolean                                 b_LoopEnd;
    boolean                                 b_SendPosRes;

    b_LoopEnd     = (boolean)FALSE;
    b_SendPosRes  = (boolean)FALSE;
    u1_DTCStatus  = (Dem_UdsStatusByteType)0U;
    u1_NegResCode = DCM_E_GENERALREJECT;
    u1_RetVal     = E_OK;
    u4_DTC        = (uint32)0U;

    while( b_LoopEnd == (boolean)FALSE )
    {
        u1_RetNextDTC = Dem_DcmGetNextEDRNumFilteredDTC( &u4_DTC,
                                                         &u1_DTCStatus );
        switch( u1_RetNextDTC )
        {
            case DEM_FILTERED_OK:

                b_LenChkResult = (boolean)FALSE;
                if( Dcm_Dsp_Main_stMsgContext.resDataLen == (Dcm_MsgLenType)DCM_DSP_SID19_SUB1A_DTC_ST_AVAIL_MSK_LEN )
                {
                    /* In case for the first time */
                    if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= (DCM_DSP_SID19_SUB1A_DTC_EDRN_LEN + DCM_DSP_SID19_SUB1A_DTC_DASR_LEN) )   /* no wrap around */
                    {
                        /* Set Extended Data Record Number */
                        Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB1A_REQ_OFFSET_DTC_EDRN];
                        Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB1A_DTC_ST_AVAIL_MSK_LEN + DCM_DSP_SID19_SUB1A_DTC_EDRN_LEN;

                        b_LenChkResult = (boolean)TRUE;
                    }
                }
                else
                {
                    /* In case for the second time or more */
                    if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= DCM_DSP_SID19_SUB1A_DTC_DASR_LEN )    /* no wrap around */
                    {
                        b_LenChkResult = (boolean)TRUE;
                    }
                }

                if( b_LenChkResult == (boolean)TRUE )
                {
                    /* DTC Data Set */
                    u4_ResDataPos = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    /* Set DTCHighByte */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB1A_SHFT_DTC_HI);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set DTCMiddleByte */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB1A_SHFT_DTC_MI);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set DTCLowByte */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set statusOfDTC */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = u1_DTCStatus;

                    Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID19_SUB1A_DTC_DASR_LEN;   /* no wrap around */
                }
                else
                {
                    b_LoopEnd = (boolean)TRUE;
                    u1_NegResCode = DCM_E_RESPONSETOOLONG;
                }
                break;
            case DEM_FILTERED_NO_MATCHING_ELEMENT:
                b_LoopEnd = (boolean)TRUE;
                b_SendPosRes = (boolean)TRUE;
                break;
            case DEM_FILTERED_PENDING:
                b_LoopEnd = (boolean)TRUE;
                u1_RetVal = DCM_E_PENDING;
                break;
            default:
                b_LoopEnd = (boolean)TRUE;
                /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                break;
        }
    }/* while End */

    if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB1A_GETDTC );    /* no return check required */
    }
    else
    {
        if( b_SendPosRes == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         u1_NegResCode );
        }
    }

    return u1_RetVal;
}
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_ChkEnableRecNum                      */
/* Description   | Check if DTCExtDataRecordNumber is enabled               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1DTCRecNum : RecordNumber                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/*               |   E_NOT_OK       : Processing not normal                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID19_Sub1A_ChkEnableRecNum
(
    const uint8 u1DTCRecNum
)
{
    uint16          u2_ConnectionId;
    Std_ReturnType  u1_RetVal;
    uint8           u1_ProtocolGroup;
    boolean         b_OutputOnlyOBDRecNum;

    u1_RetVal = E_NOT_OK;

    u2_ConnectionId = ( uint16 )0x0000U;
    (void)Dcm_GetActiveProtocol( NULL_PTR,
                                 &u2_ConnectionId,
                                 NULL_PTR );
    u1_ProtocolGroup = Dcm_Dsl_GetActiveProtocolGroup( u2_ConnectionId );

    if( u1_ProtocolGroup == DCM_DSL_UDS_PROTOCOL )
    {
        if( ( u1DTCRecNum >= DCM_DSP_SID19_SUB1A_DTC_EDRN_NUM01 ) && ( u1DTCRecNum <= DCM_DSP_SID19_SUB1A_DTC_EDRN_NUMFD ) )
        {
            u1_RetVal = E_OK;
        }
    }
    else /* u1_ProtocolGroup eqal DCM_DSL_OBD_PROTOCOL */
    {
        b_OutputOnlyOBDRecNum = Dcm_Dsp_SID19_Sub1A_bOutputOnlyEmiOBDRecNumToOBDClient;
        if( b_OutputOnlyOBDRecNum == (boolean)TRUE )
        {
            if( ( u1DTCRecNum >= DCM_DSP_SID19_SUB1A_DTC_EDRN_NUM90 ) && ( u1DTCRecNum <= DCM_DSP_SID19_SUB1A_DTC_EDRN_NUM9F ) )
            {
                u1_RetVal = E_OK;
            }
        }
        else
        {
            if( ( u1DTCRecNum >= DCM_DSP_SID19_SUB1A_DTC_EDRN_NUM01 ) && ( u1DTCRecNum <= DCM_DSP_SID19_SUB1A_DTC_EDRN_NUMFD ) )
            {
                u1_RetVal = E_OK;
            }
        }
    }
    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID19_SUB1A == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-2-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
