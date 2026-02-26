/* Dcm_Dsp_SID19_Sub55(v5-4-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub55/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub55.h>
#if ( DCM_SUPPORT_SID19_SUB55 == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID19_Sub55_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID19_SUB55_SHFT_DTC_HI                 ((uint8)16U)
#define     DCM_DSP_SID19_SUB55_SHFT_DTC_MI                 ((uint8)8U)
#define     DCM_DSP_SID19_SUB55_FGID_VAL_33                 ((uint8)0x33U)
#define     DCM_DSP_SID19_SUB55_FGID_VAL_FF                 ((uint8)0xFFU)
#define     DCM_DSP_SID19_SUB55_DTC_ST_MSK_00               ((uint8)0x00U)
#define     DCM_DSP_SID19_SUB55_FGID_LEN                    ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB55_DTC_ST_AVAIL_MSK_LEN        ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB55_DTC_FORMAT_ID_LEN           ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB55_DTC_LEN                     ((Dcm_MsgLenType)3U)
#define     DCM_DSP_SID19_SUB55_DTC_ST_LEN                  ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB55_DTC_DASR_LEN                ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB55_DTC_LEN + DCM_DSP_SID19_SUB55_DTC_ST_LEN))
#define     DCM_DSP_SID19_SUB55_REQ_OFFSET_FGID             ((uint32)0U)
#define     DCM_DSP_SID19_SUB55_REQ_DATA_LEN                (DCM_DSP_SID19_SUB55_FGID_LEN)
#define     DCM_DSP_SID19_SUB55_RES_OFFSET_FGID             ((uint32)0U)
#define     DCM_DSP_SID19_SUB55_RES_OFFSET_DTC_ST_AVAIL_MSK ((uint32)1U)
#define     DCM_DSP_SID19_SUB55_RES_OFFSET_DTC_FORMAT_ID    ((uint32)2U)
#define     DCM_DSP_SID19_SUB55_RES_DATA_MIN_LEN            ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB55_FGID_LEN + DCM_DSP_SID19_SUB55_DTC_ST_AVAIL_MSK_LEN + DCM_DSP_SID19_SUB55_DTC_FORMAT_ID_LEN))


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub55_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub55_CancelProc
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub55_GetDTC
(
    void
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID19_Sub55_ChkEnableFGID
(
    const uint8 u1FGID,
    P2VAR( Dem_DTCKindType, AUTOMATIC, DCM_APPL_DATA ) ptReqDTCKind
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
/* Function Name | Dcm_SID19_Sub55                                          */
/* Description   | Request processing of SID19_Sub55                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/*               |   DCM_E_PENDING  : Pending                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID19_Sub55
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub55_InitialProc( pMsgContext );
    }
    else
    {
        Dcm_Dsp_SID19_Sub55_CancelProc();
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub55_Cbk                                  */
/* Description   | Call Back Function to Continue SID19_Sub55 Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub55_Cbk
(
    const uint8 u1EventId
)
{
    (void)Dcm_Dsp_SID19_Sub55_GetDTC();     /* no return check required */

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub55_InitialProc                          */
/* Description   | Initial process of SID19_Sub55 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK            : Processing normal                    */
/*               |   DCM_E_PENDING   : Pending                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub55_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dem_ReturnSetFilterType         u1_RetSetFilter;
    Dem_DTCKindType                 u1_ReqDTCKind;
    Dem_DTCTranslationFormatType    u1_DTCFormamtType;
    Std_ReturnType                  u1_RetChkFGID;
    Std_ReturnType                  u1_RetStatusAvailabilityMask;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_SendNegResFlag;

    u1_NegResCode    = DCM_E_GENERALREJECT;
    u1_RetVal        = E_OK;
    u1_ReqDTCKind = DEM_DTC_KIND_EMISSION_REL_DTCS;
    b_SendNegResFlag = (boolean)FALSE;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID19_SUB55_REQ_DATA_LEN )
    {
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= DCM_DSP_SID19_SUB55_RES_DATA_MIN_LEN )
        {
            u1_RetChkFGID = Dcm_Dsp_SID19_Sub55_ChkEnableFGID( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB55_REQ_OFFSET_FGID], &u1_ReqDTCKind );
            if( u1_RetChkFGID == (Std_ReturnType)E_OK )
            {
                u1_DTCStatusMask = DCM_DSP_SID19_SUB55_DTC_ST_MSK_00;
                u1_RetStatusAvailabilityMask = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask,
                                                                                    DEM_DTC_ORIGIN_PRIMARY_MEMORY );
                if( u1_RetStatusAvailabilityMask == (Std_ReturnType)E_OK )
                {
                    u1_DTCFormamtType = Dem_DcmGetTranslationType();
                    if( ( u1_DTCFormamtType == DEM_DTC_TRANSLATION_SAEJ1939_73 ) ||
                        ( u1_DTCFormamtType == DEM_DTC_TRANSLATION_J2012DA_FORMAT_04 ) )
                    {
                        u1_RetSetFilter = Dem_DcmSetDTCFilter( DCM_DSP_SID19_SUB55_DTC_ST_MSK_00,
                                                               u1_ReqDTCKind,
                                                               DEM_DTC_FORMAT_UDS,
                                                               DEM_DTC_ORIGIN_PERMANENT_MEMORY,
                                                               (boolean)FALSE,
                                                               DEM_SEVERITY_NO_SEVERITY,
                                                               (boolean)FALSE );

                        if( u1_RetSetFilter == (Dem_ReturnSetFilterType)DEM_FILTER_ACCEPTED )
                        {
                            /* Set FunctionalGroupIdentifier */
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB55_RES_OFFSET_FGID] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB55_REQ_OFFSET_FGID];
                            /* Set DTCStatusAvailableMask */
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB55_RES_OFFSET_DTC_ST_AVAIL_MSK] = u1_DTCStatusMask;
                            /* Set DTCFormatIdentifier */
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB55_RES_OFFSET_DTC_FORMAT_ID] = u1_DTCFormamtType;

                            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB55_FGID_LEN + 
                                                                   DCM_DSP_SID19_SUB55_DTC_ST_AVAIL_MSK_LEN + 
                                                                   DCM_DSP_SID19_SUB55_DTC_FORMAT_ID_LEN;

                            u1_RetVal = Dcm_Dsp_SID19_Sub55_GetDTC();
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
                else
                {
                    /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                    b_SendNegResFlag = (boolean)TRUE;
                }
            }
            else
            {
                u1_NegResCode = DCM_E_REQUESTOUTOFRANGE;
                b_SendNegResFlag = (boolean)TRUE;
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
/* Function Name | Dcm_Dsp_SID19_Sub55_CancelProc                           */
/* Description   | Cancel process of SID19_Sub55 request                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub55_CancelProc
( void )
{
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB55_GETDTC,    /* no return check required */
                                         (boolean)FALSE );

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub55_GetDTC                               */
/* Description   | Get DTC and Edit Response or Register Event              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          : Result OK                                */
/*               | DCM_E_PENDING : Result Pending                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub55_GetDTC
( void )
{
    uint32                                  u4_DTC;
    Dcm_MsgLenType                          u4_ResDataPos;
    Dem_UdsStatusByteType                   u1_DTCStatus;
    Dem_ReturnGetNextFilteredElementType    u1_RetNextDTC;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    Std_ReturnType                          u1_RetVal;
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
        u1_RetNextDTC = Dem_DcmGetNextFilteredDTC( &u4_DTC,
                                                   &u1_DTCStatus );
        switch( u1_RetNextDTC )
        {
            case DEM_FILTERED_OK:

                if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= DCM_DSP_SID19_SUB55_DTC_DASR_LEN )    /* no wrap around */
                {
                    /* DTC Data Set */
                    u4_ResDataPos = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    /* Set DTCHighByte */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB55_SHFT_DTC_HI);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set DTCMiddleByte */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB55_SHFT_DTC_MI);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set DTCLowByte */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set statusOfDTC */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = u1_DTCStatus;

                    Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID19_SUB55_DTC_DASR_LEN;   /* no wrap around */
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
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB55_GETDTC );    /* no return check required */
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
/* Function Name | Dcm_Dsp_SID19_Sub55_ChkEnableFGID                        */
/* Description   | Check if FGID is enable and set DTCKind.                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1FGID       : FGID                                */
/*               | [OUT] ptReqDTCKind : DTCKind                             */
/* Return Value  | E_OK               : FGID is enabled.                    */
/*               | E_NOT_OK           : FGID is disabled.                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub55_ChkEnableFGID
(
    const uint8 u1FGID,
    P2VAR( Dem_DTCKindType, AUTOMATIC, DCM_APPL_DATA ) ptReqDTCKind
)
{
    Std_ReturnType                          u1_AcceptFF;
    Std_ReturnType                          u1_RetVal;

    u1_RetVal = E_NOT_OK;

    switch( u1FGID )
    {
        case DCM_DSP_SID19_SUB55_FGID_VAL_33:
            *ptReqDTCKind = DEM_DTC_KIND_EMISSION_REL_DTCS;
            u1_RetVal = E_OK;
            break;
        case DCM_DSP_SID19_SUB55_FGID_VAL_FF:
            u1_AcceptFF = Dcm_Dsp_SID19_Sub55_CheckFGIDFFRequestIsAcceptable();
            if( u1_AcceptFF == (Std_ReturnType)E_OK )
            {
                *ptReqDTCKind = DEM_DTC_KIND_ALL_DTCS;
                u1_RetVal = E_OK;
            }
            break;
        default:
                /* u1_RetVal equal E_NOT_OK; */
                /* No process */
            break;
    }

    return u1_RetVal;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID19_SUB55 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-2-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
