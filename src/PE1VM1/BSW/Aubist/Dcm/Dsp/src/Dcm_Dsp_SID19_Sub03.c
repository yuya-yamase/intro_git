/* Dcm_Dsp_SID19_Sub03_c(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub03/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub03.h>
#if ( DCM_SUPPORT_SID19_SUB03 == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID19_Sub03_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID19_SUB03_ShftDTCHi                   ((uint8)16U)
#define     DCM_DSP_SID19_SUB03_ShftDTCMi                   ((uint8)8U)
#define     DCM_DSP_SID19_SUB03_ReqLen                      ((uint8)0U)
#define     DCM_DSP_SID19_SUB03_ResOffDTCMi                 ((uint8)1U)
#define     DCM_DSP_SID19_SUB03_ResOffDTCLo                 ((uint8)2U)
#define     DCM_DSP_SID19_SUB03_ResOffDTCSRN                ((uint8)3U)
#define     DCM_DSP_SID19_SUB03_DTCLen                      ((uint8)3U)
#define     DCM_DSP_SID19_SUB03_DTCSRNLen                   ((uint8)1U)
#define     DCM_DSP_SID19_SUB03_DASRNLen                    (DCM_DSP_SID19_SUB03_DTCLen + DCM_DSP_SID19_SUB03_DTCSRNLen)
#define     DCM_DSP_SID19_SUB03_NUM00                       ((uint8)0x00U)
#define     DCM_DSP_SID19_SUB03_NUMF0                       ((uint8)0xF0U)
#define     DCM_DSP_SID19_SUB03_REPORT_ALL                  ((uint8)0x00U)
#define     DCM_DSP_SID19_SUB03_REPORT_WITHOUT_SPECIFIC_RN  ((uint8)0x01U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID19_Sub03_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID19_Sub03_CancelProc
(
    void
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID19_Sub03_GetRecord
(
    void
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID19_Sub03_SetReportType
(
    void
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID19_Sub03_JudgeReportType
(
    const uint8 u1RecordNumber
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID19_Sub03_u1SetReportType;

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
/* Function Name | Dcm_SID19_Sub03                                          */
/* Description   | Request processing of SID 19_Sub03                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID19_Sub03 /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType    u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub03_InitialProc( pMsgContext );
        /* This Return Value is check-free */
    }
    else
    {
        Dcm_Dsp_SID19_Sub03_CancelProc();
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub03_Cbk                                  */
/* Description   | Call Back Function to Continue SID19_Sub03 Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID19_Sub03_Cbk /* MISRA DEVIATION */
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    (void)Dcm_Dsp_SID19_Sub03_GetRecord(); /* no return check required */

    return ;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub03_InitialProc                          */
/* Description   | Initial process of SID19_Sub03                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID19_Sub03_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    boolean                         b_SendNegResFlag;
    Dem_ReturnSetFilterType         u1_RetSetFilter;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    uint16                          u2_NumOfFilteredRecords;
    boolean                         b_CheckChkOrgImp;

    b_SendNegResFlag        = (boolean)FALSE;
    u1_RetVal               = E_OK;
    u2_NumOfFilteredRecords = (uint16)0U;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID19_SUB03_ReqLen )
    {
        u1_RetSetFilter = Dem_DcmSetFreezeFrameRecordFilter( DEM_DTC_FORMAT_UDS, &u2_NumOfFilteredRecords );
        if( u1_RetSetFilter == (Dem_ReturnSetFilterType)DEM_FILTER_ACCEPTED )
        {
            Dcm_Dsp_SID19_Sub03_SetReportType();
            u1_RetVal = Dcm_Dsp_SID19_Sub03_GetRecord();
            /* This Return Value is check-free */
        }
        else
        {
            b_CheckChkOrgImp = Dcm_Dsp_SID19_Sub03_bChkOrgImp;
            /* Check Config Implement Error Check */
            if( b_CheckChkOrgImp != (boolean)TRUE )
            {
                u1_NegResCode = DCM_E_BUSYREPEATREQUEST;
                b_SendNegResFlag = (boolean)TRUE;
            }
            else
            {
                /* No process */
            }
        }
    }
    else
    {
        /* This Route                                                       */
        /*   Request Length Check NG    -> 0x13                             */
        u1_NegResCode    = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;

}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub03_CancelProc                           */
/* Description   | Cancel process of SID19_Sub03 request                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID19_Sub03_CancelProc
(
    void
)
{

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB03_GETRECORD, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub03_SetReportType                        */
/* Description   | Set ReportType                                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID19_Sub03_SetReportType
(
    void
)
{
    uint16  u2_ConnectionId;
    uint8           u1_ProtocolGroup;
    boolean b_OutputLegislatedOBDData;


    u2_ConnectionId = (uint16)0x0000U;
    (void)Dcm_GetActiveProtocol( NULL_PTR,
                                 &u2_ConnectionId,
                                 NULL_PTR );

    u1_ProtocolGroup = Dcm_Dsl_GetActiveProtocolGroup( u2_ConnectionId );

    Dcm_Dsp_SID19_Sub03_u1SetReportType = DCM_DSP_SID19_SUB03_REPORT_ALL;

    if( u1_ProtocolGroup == DCM_DSL_UDS_PROTOCOL )
    {
        b_OutputLegislatedOBDData = Dcm_Dsp_SID19_Sub03_bOutputLegislatedOBDData;

        if( b_OutputLegislatedOBDData == (boolean)FALSE )
        {
            Dcm_Dsp_SID19_Sub03_u1SetReportType = DCM_DSP_SID19_SUB03_REPORT_WITHOUT_SPECIFIC_RN;
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub03_GetRecord                            */
/* Description   | Get DTCRecord and Edit Response or Register Event        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID19_Sub03_GetRecord
(
    void
)
{
    Std_ReturnType                          u1_RetVal;
    Std_ReturnType                          u1_RetJdg;
    boolean                                 b_SendNegResFlag;
    boolean                                 b_SendPosResFlag;
    boolean                                 b_LoopEndFlag;
    uint32                                  u4_DTC;
    uint8                                   u1_RecordNumber;
    Dem_ReturnGetNextFilteredElementType    u1_RetNextFR;
    Dcm_NegativeResponseCodeType            u1_NegResCode;

    u1_RetVal        = E_OK;
    b_SendNegResFlag = (boolean)FALSE;
    b_SendPosResFlag = (boolean)FALSE;
    b_LoopEndFlag    = (boolean)FALSE;
    u4_DTC           = (uint32)0U;
    u1_RecordNumber  = (uint8)0U;
    u1_NegResCode    = (Dcm_NegativeResponseCodeType)0U;

    while( b_LoopEndFlag == (boolean)FALSE )
    {
        u1_RetNextFR = Dem_DcmGetNextFilteredRecord( &u4_DTC, &u1_RecordNumber );
        switch( u1_RetNextFR )
        {
            case DEM_FILTERED_OK :
                u1_RetJdg = Dcm_Dsp_SID19_Sub03_JudgeReportType( u1_RecordNumber );
                if( u1_RetJdg == (Std_ReturnType)E_OK )
                {
                    if( ( Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen ) >= DCM_DSP_SID19_SUB03_DASRNLen )    /* no wrap around */
                    {
                        /* DTC Data And RecordNumber Set */
                        Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ]  = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB03_ShftDTCHi);
                        Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB03_ResOffDTCMi ] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB03_ShftDTCMi); /* no wrap around */
                        Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB03_ResOffDTCLo ] = (uint8)(u4_DTC);  /* no wrap around */
                        Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB03_ResOffDTCSRN ] = u1_RecordNumber; /* no wrap around */
                        /* DTC Data Length And RecordNumber Length Plus */
                        Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + DCM_DSP_SID19_SUB03_DASRNLen; /* no wrap around */
                    }
                    else
                    {
                        /* Write Buffer Error Loop End */
                        b_LoopEndFlag = (boolean)TRUE;
                        u1_NegResCode    = DCM_E_RESPONSETOOLONG;
                        b_SendNegResFlag = Dcm_Dsp_SID19_Sub03_bNegativeResponseSendResponseTooLong;
                    }
                }
                break;
            case DEM_FILTERED_NO_MATCHING_ELEMENT:
                b_LoopEndFlag = (boolean)TRUE;
                b_SendPosResFlag = (boolean)TRUE;
                break;
            case DEM_FILTERED_PENDING:
                b_LoopEndFlag = (boolean)TRUE;
                u1_RetVal = DCM_E_PENDING;
                break;
            default:
                b_LoopEndFlag = (boolean)TRUE;
                break;
        }
    }/* while End */

    if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB03_GETRECORD ); /* no return check required */
    }
    else
    {
        if( b_SendPosResFlag == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
        else if( b_SendNegResFlag == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
        }
        else
        {
            /* No process */
        }
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub03_JudgeReportType                      */
/* Description   | Judge Output ReportNumber                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RecordNumber : RecordNumber                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID19_Sub03_JudgeReportType
(
    const uint8 u1RecordNumber
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( ( u1RecordNumber == DCM_DSP_SID19_SUB03_NUM00 ) ||
        ( u1RecordNumber == DCM_DSP_SID19_SUB03_NUMF0 ) )
    {
        if( Dcm_Dsp_SID19_Sub03_u1SetReportType == DCM_DSP_SID19_SUB03_REPORT_WITHOUT_SPECIFIC_RN )
        {
            u1_RetVal = E_NOT_OK;
        }
    }

    return u1_RetVal;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID19_SUB03 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File************************************************************/
