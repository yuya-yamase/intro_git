/* Dcm_Dsp_SID19_Sub42_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub42/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub42.h>
#if ( DCM_SUPPORT_SID19_SUB42 == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID19_Sub42_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID19_SUB42_REQOFST_FGID    ((uint32)0U)
#define DCM_DSP_SID19_SUB42_REQOFST_DTCSM   ((uint32)1U)
#define DCM_DSP_SID19_SUB42_REQOFST_DTCSVM  ((uint32)2U)
#define DCM_DSP_SID19_SUB42_RESOFST_FGID    ((uint32)0U)
#define DCM_DSP_SID19_SUB42_RESOFST_DTCSAM  ((uint32)1U)
#define DCM_DSP_SID19_SUB42_RESOFST_DTCSVAM ((uint32)2U)
#define DCM_DSP_SID19_SUB42_RESOFST_DTCFID  ((uint32)3U)
#define DCM_DSP_SID19_SUB42_SHFT_DTCHB      ((uint8)16U)
#define DCM_DSP_SID19_SUB42_SHFT_DTCMB      ((uint8)8U)
#define DCM_DSP_SID19_SUB42_LEN_FGID        ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB42_LEN_DTCSM       ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB42_LEN_DTCSVM      ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB42_LEN_DTCSAM      ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB42_LEN_DTCSVAM     ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB42_LEN_DTCFID      ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB42_LEN_DTCS        ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB42_LEN_DTC         ((Dcm_MsgLenType)3U)
#define DCM_DSP_SID19_SUB42_LEN_SODTC       ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB42_LEN_REQ         ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB42_LEN_FGID + DCM_DSP_SID19_SUB42_LEN_DTCSM + DCM_DSP_SID19_SUB42_LEN_DTCSVM))
#define DCM_DSP_SID19_SUB42_LEN_RES_MIN     ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB42_LEN_FGID + DCM_DSP_SID19_SUB42_LEN_DTCSAM + DCM_DSP_SID19_SUB42_LEN_DTCSVAM + DCM_DSP_SID19_SUB42_LEN_DTCFID))
#define DCM_DSP_SID19_SUB42_LEN_RES_DASR    ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB42_LEN_DTCS + DCM_DSP_SID19_SUB42_LEN_DTC + DCM_DSP_SID19_SUB42_LEN_SODTC))
#define DCM_DSP_SID19_SUB42_FGID_VAL_33     ((uint8)0x33U)
#define DCM_DSP_SID19_SUB42_FGID_VAL_FF     ((uint8)0xFFU)
#define DCM_DSP_SID19_SUB42_DTCSM_00        ((uint8)0x00U)
#define DCM_DSP_SID19_SUB42_DTCSVM_00       ((uint8)0x00U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub42_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_CancelProc
( void );
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub42_GetDTC
( void );
#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub42_GetSizeOfDTC
( void );
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_AdjustDataLenForPage
( void );
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_StartPage
( void );
#endif /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID19_Sub42_ChkEnableFGID
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

#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON )
static VAR(uint32, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub42_u4ResDataLenforPB;
static VAR(uint16, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub42_u2RemainingResDataNumforPB;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub42_bUpdatePageFlag;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub42_bGetDTCEnded;
#endif /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON */

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
/* Function Name | Dcm_SID19_Sub42                                          */
/* Description   | Report DTC By Severity Mask                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Status of the current operation    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                : Result OK                          */
/*               | DCM_E_PENDING       : Result Pending                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID19_Sub42
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub42_InitialProc( pMsgContext );
        /* This Return Value is check-free */
    }
    else
    {
        Dcm_Dsp_SID19_Sub42_CancelProc();
    }

    return u1_RetVal;
}

#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub42_GetSizeOfDTCCbk                      */
/* Description   | Call Back Function to Continue SID19_Sub42 Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event Id                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_GetSizeOfDTCCbk
(
    const uint8 u1EventId
)
{
    Std_ReturnType  u1_RetGetSizeOfDTC;

    u1_RetGetSizeOfDTC = Dcm_Dsp_SID19_Sub42_GetSizeOfDTC();
    if( u1_RetGetSizeOfDTC == (Std_ReturnType)E_OK )
    {
        (void)Dcm_Dsp_SID19_Sub42_GetDTC();         /* no return check required */
    }

    return;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub42_GetDTCCbk                            */
/* Description   | Call Back Function to Continue SID19_Sub42 Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event Id                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_GetDTCCbk      /* MISRA DEVIATION */
(
    const uint8 u1EventId                                /* MISRA DEVIATION */
)
{
    (void)Dcm_Dsp_SID19_Sub42_GetDTC();     /* no return check required */

    return;
}

#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub42_UpdatePage                           */
/* Description   | UpdatePage of SID19_Sub42                                */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptResData       : Response Data                    */
/*               | [IN]  u4ResMaxDataLen : Buffer Size of Response Data     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub42_UpdatePage
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
)
{
    Std_ReturnType      u1_RetGetDTC;
    Std_ReturnType      u1_RetVal;
    
    u1_RetVal = E_OK;

    if( u4ResMaxDataLen == (Dcm_MsgLenType)DCM_DSD_UPDATEPAGE_INITIAL_ACT )
    {
        Dcm_Dsp_SID19_Sub42_bUpdatePageFlag = (boolean)TRUE;
        Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
    }
    else
    {
        Dcm_Dsp_Main_stMsgContext.resData          = ptResData;
        Dcm_Dsp_Main_stMsgContext.resMaxDataLen    = u4ResMaxDataLen;
        Dcm_Dsp_Main_stMsgContext.resDataLen       = (uint32)0U;

        u1_RetGetDTC = Dcm_Dsp_SID19_Sub42_GetDTC();
        if( u1_RetGetDTC == (Std_ReturnType)DCM_E_PENDING )
        {
            u1_RetVal = DCM_E_PENDING;
        }
        else
        {
            if( Dcm_Dsp_Main_stMsgContext.resDataLen == (uint32)0U )
            {
                u1_RetVal = E_NOT_OK;
            }
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub42_CancelPage                           */
/* Description   | CancelPage of SID19_Sub42                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_CancelPage
(void)
{
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB42_GETDTC, (boolean)FALSE );
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub42_InitialProc                          */
/* Description   | Initial process of SID19_Sub42                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                : Result OK                          */
/*               | DCM_E_PENDING       : Result Pending                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub42_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkFGID;
    Std_ReturnType                  u1_RetDDGDSAM;
    Std_ReturnType                  u1_RetDDGDSVAM;
    Dem_DTCTranslationFormatType    u1_DTCFormatType;
    Dem_ReturnSetFilterType         u1_RetSetFilter;
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dem_DTCKindType                 u1_ReqDTCKind;
    Dem_DTCSeverityType             u1_DTCSeverityMask;
    uint8                           u1_InDTCStatusMask;
    uint8                           u1_InDTCSeverityMask;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    boolean                         b_SendNegResFlag;
    boolean                         b_SendPosResFlag;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    u1_RetVal = E_OK;
    u1_DTCStatusMask = DCM_DSP_SID19_SUB42_DTCSM_00;
    u1_ReqDTCKind = DEM_DTC_KIND_EMISSION_REL_DTCS;
    u1_DTCSeverityMask = DCM_DSP_SID19_SUB42_DTCSVM_00;
    u1_NegResCode = DCM_E_GENERALREJECT;
    b_SendNegResFlag = (boolean)FALSE;
    b_SendPosResFlag = (boolean)FALSE;

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID19_SUB42_LEN_REQ )
    {
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= DCM_DSP_SID19_SUB42_LEN_RES_MIN )
        {
            u1_RetChkFGID = Dcm_Dsp_SID19_Sub42_ChkEnableFGID( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB42_REQOFST_FGID], &u1_ReqDTCKind);
            if( u1_RetChkFGID == (Std_ReturnType)E_OK )
            {
                u1_RetDDGDSAM = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask,
                                                                     DEM_DTC_ORIGIN_PRIMARY_MEMORY );
                if( u1_RetDDGDSAM == (Std_ReturnType)E_OK )
                {
                    u1_RetDDGDSVAM = Dem_DcmGetDTCSeverityAvailabilityMask( &u1_DTCSeverityMask );
                    if( u1_RetDDGDSVAM == (Std_ReturnType)E_OK )
                    {
                        u1_DTCFormatType = Dem_DcmGetTranslationType();
                        if( ( u1_DTCFormatType == DEM_DTC_TRANSLATION_SAEJ1939_73 ) ||
                            ( u1_DTCFormatType == DEM_DTC_TRANSLATION_J2012DA_FORMAT_04 ) )
                        {
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB42_RESOFST_FGID] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB42_REQOFST_FGID];
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB42_RESOFST_DTCSAM] = u1_DTCStatusMask;
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB42_RESOFST_DTCSVAM] = u1_DTCSeverityMask;
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB42_RESOFST_DTCFID] = u1_DTCFormatType;
                            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB42_LEN_RES_MIN;

                            u1_InDTCStatusMask = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB42_REQOFST_DTCSM];
                            if( u1_InDTCStatusMask != DCM_DSP_SID19_SUB42_DTCSM_00 )
                            {
                                u1_InDTCSeverityMask = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB42_REQOFST_DTCSVM];
                                if( u1_InDTCSeverityMask != DCM_DSP_SID19_SUB42_DTCSVM_00 )
                                {
                                    u1_RetSetFilter = Dem_DcmSetDTCFilter( u1_InDTCStatusMask,
                                                                           u1_ReqDTCKind,
                                                                           DEM_DTC_FORMAT_UDS,
                                                                           DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                                           (boolean)TRUE,
                                                                           u1_InDTCSeverityMask,
                                                                           (boolean)FALSE );

                                    if( u1_RetSetFilter == (Dem_ReturnSetFilterType)DEM_FILTER_ACCEPTED )
                                    {
                                        u1_RetVal = Dcm_Dsp_SID19_Sub42_GetDTC();
                                    }
                                    else if( u1_RetSetFilter == (Dem_ReturnSetFilterType)DEM_WRONG_FILTER )
                                    {
                                        b_SendPosResFlag = (boolean)TRUE;
                                    }
                                    else
                                    {
                                        /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                                        b_SendNegResFlag = (boolean)TRUE;
                                    }
                                }
                                else
                                {
                                    b_SendPosResFlag = (boolean)TRUE;
                                }
                            }
                            else
                            {
                                b_SendPosResFlag = (boolean)TRUE;
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

    if( b_SendPosResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_NegResCode );
    }

    return u1_RetVal;

}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub42_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkFGID;
    Std_ReturnType                  u1_RetGetSizeOfDTC;
    Std_ReturnType                  u1_RetDDGDSAM;
    Std_ReturnType                  u1_RetDDGDSVAM;
    Dem_DTCTranslationFormatType    u1_DTCFormatType;
    Dem_ReturnSetFilterType         u1_RetSetFilter;
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dem_DTCKindType                 u1_ReqDTCKind;
    Dem_DTCSeverityType             u1_DTCSeverityMask;
    uint8                           u1_InDTCStatusMask;
    uint8                           u1_InDTCSeverityMask;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    boolean                         b_SendNegResFlag;
    boolean                         b_SendPosResFlag;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_SID19_Sub42_bGetDTCEnded =  (boolean)FALSE;

    u1_RetVal = E_OK;
    u1_DTCStatusMask = DCM_DSP_SID19_SUB42_DTCSM_00;
    u1_ReqDTCKind = DEM_DTC_KIND_EMISSION_REL_DTCS;
    u1_DTCSeverityMask = DCM_DSP_SID19_SUB42_DTCSVM_00;
    u1_NegResCode = DCM_E_GENERALREJECT;
    b_SendNegResFlag = (boolean)FALSE;
    b_SendPosResFlag = (boolean)FALSE;

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID19_SUB42_LEN_REQ )
    {
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= DCM_DSP_SID19_SUB42_LEN_RES_MIN )
        {
            u1_RetChkFGID = Dcm_Dsp_SID19_Sub42_ChkEnableFGID( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB42_REQOFST_FGID], &u1_ReqDTCKind);
            if( u1_RetChkFGID == (Std_ReturnType)E_OK )
            {
                u1_RetDDGDSAM = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask,
                                                                     DEM_DTC_ORIGIN_PRIMARY_MEMORY );
                if( u1_RetDDGDSAM == (Std_ReturnType)E_OK )
                {
                    u1_RetDDGDSVAM = Dem_DcmGetDTCSeverityAvailabilityMask( &u1_DTCSeverityMask );
                    if( u1_RetDDGDSVAM == (Std_ReturnType)E_OK )
                    {
                        u1_DTCFormatType = Dem_DcmGetTranslationType();
                        if( ( u1_DTCFormatType == DEM_DTC_TRANSLATION_SAEJ1939_73 ) ||
                            ( u1_DTCFormatType == DEM_DTC_TRANSLATION_J2012DA_FORMAT_04 ) )
                        {
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB42_RESOFST_FGID] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB42_REQOFST_FGID];
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB42_RESOFST_DTCSAM] = u1_DTCStatusMask;
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB42_RESOFST_DTCSVAM] = u1_DTCSeverityMask;
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB42_RESOFST_DTCFID] = u1_DTCFormatType;
                            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB42_LEN_RES_MIN;

                            u1_InDTCStatusMask = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB42_REQOFST_DTCSM];
                            if( u1_InDTCStatusMask != DCM_DSP_SID19_SUB42_DTCSM_00 )
                            {
                                u1_InDTCSeverityMask = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB42_REQOFST_DTCSVM];
                                if( u1_InDTCSeverityMask != DCM_DSP_SID19_SUB42_DTCSVM_00 )
                                {
                                    u1_RetSetFilter = Dem_DcmSetDTCFilter( u1_InDTCStatusMask,
                                                                           u1_ReqDTCKind,
                                                                           DEM_DTC_FORMAT_UDS,
                                                                           DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                                           (boolean)TRUE,
                                                                           u1_InDTCSeverityMask,
                                                                           (boolean)FALSE );

                                    if( u1_RetSetFilter == (Dem_ReturnSetFilterType)DEM_FILTER_ACCEPTED )
                                    {
                                        u1_RetGetSizeOfDTC = Dcm_Dsp_SID19_Sub42_GetSizeOfDTC();
                                        switch( u1_RetGetSizeOfDTC )
                                        {
                                            case E_OK:
                                                u1_RetVal = Dcm_Dsp_SID19_Sub42_GetDTC();
                                                /* This Return Value is check-free */
                                                break;
                                            case DCM_E_PENDING:
                                                u1_RetVal = DCM_E_PENDING;
                                                break;
                                            default:
                                                /* no process */
                                                break;
                                        }
                                    }
                                    else if( u1_RetSetFilter == (Dem_ReturnSetFilterType)DEM_WRONG_FILTER )
                                    {
                                        b_SendPosResFlag = (boolean)TRUE;
                                    }
                                    else
                                    {
                                        /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                                        b_SendNegResFlag = (boolean)TRUE;
                                    }
                                }
                                else
                                {
                                    b_SendPosResFlag = (boolean)TRUE;
                                }
                            }
                            else
                            {
                                b_SendPosResFlag = (boolean)TRUE;
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

    if( b_SendPosResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_NegResCode );
    }

    return u1_RetVal;

}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub42_CancelProc                           */
/* Description   | Receive Cancel request and Set Cancel Flag               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_OFF )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_CancelProc
( void )
{

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB42_GETDTC, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_CancelProc
( void )
{
    Dcm_Main_EvtDistr_RetType   u1_RetDelGetSizeofDTC;

    u1_RetDelGetSizeofDTC = Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB42_GETSIZE, (boolean)FALSE );
    if( u1_RetDelGetSizeofDTC != DCM_MAIN_EVTDISTR_E_OK )
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB42_GETDTC, (boolean)FALSE ); /* no return check required */
    }
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub42_GetSizeOfDTC                         */
/* Description   | Get Number of DTCs and Severity and calculate response   */
/*               | data length                                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |    E_OK             : Processing normal                  */
/*               |    DCM_E_PENDING    : Result Pending                     */
/*               |    E_NOT_OK         : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub42_GetSizeOfDTC
(
    void
)
{
    uint16                                  u2_NumOfDTC;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    Dem_ReturnGetNumberOfFilteredDTCType    u1_RetNumOfFilDTC;
    Std_ReturnType                          u1_RetVal;

    u1_RetVal   = E_OK;
    u1_NegResCode = DCM_E_GENERALREJECT;

    u1_RetNumOfFilDTC = Dem_DcmGetNumberOfFilteredDTCAndSeverity( &u2_NumOfDTC );
    switch( u1_RetNumOfFilDTC )
    {
        case DEM_NUMBER_OK:
            Dcm_Dsp_SID19_Sub42_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen + (uint32)((uint32)u2_NumOfDTC * (uint32)DCM_DSP_SID19_SUB42_LEN_RES_DASR); /* no wrap around */
            Dcm_Dsp_SID19_Sub42_u2RemainingResDataNumforPB  = u2_NumOfDTC;
            Dcm_Dsp_SID19_Sub42_bUpdatePageFlag             = (boolean)FALSE;
            break;
        case DEM_NUMBER_PENDING:
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB42_GETSIZE );   /* no return check required */
            u1_RetVal = DCM_E_PENDING;
            break;
        default:
            /*   General Reject    -> 0x10                              */
            /* default value of u1_NegResCode is DCM_E_GENERALREJECT    */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
            u1_RetVal = E_NOT_OK;
            break;
        }

    return u1_RetVal;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub42_GetDTC                               */
/* Description   | Get DTC and Severity and Edit Response or Register Event */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                : Result OK                          */
/*               | DCM_E_PENDING       : Result Pending                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub42_GetDTC
( void )
{
    uint32                                  u4_DTC;
    Dcm_MsgLenType                          u4_ResDataLen;
    Std_ReturnType                          u1_RetVal;
    Dem_UdsStatusByteType                   u1_DtcStatus;
    Dem_DTCSeverityType                     u1_DTCSeverity;
    uint8                                   u1_DTCFuncUnit;
    Dem_ReturnGetNextFilteredElementType    u1_RetNextDtc;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    boolean                                 b_SendPosResFlag;
    boolean                                 b_LoopEnd;

    u4_DTC = (uint32)0x00000000U;
    u1_RetVal = E_OK;
    u1_DtcStatus = (Dem_UdsStatusByteType)0x00U;
    u1_DTCSeverity = (Dem_DTCSeverityType)0x00U;
    u1_DTCFuncUnit = (uint8)0x00U;
    u1_NegResCode = DCM_E_GENERALREJECT;
    b_SendPosResFlag = (boolean)FALSE;
    b_LoopEnd = (boolean)FALSE;

    while( b_LoopEnd == (boolean)FALSE )
    {
        u1_RetNextDtc = Dem_DcmGetNextFilteredDTCAndSeverity( &u4_DTC,
                                                              &u1_DtcStatus,
                                                              &u1_DTCSeverity,
                                                              &u1_DTCFuncUnit );
        switch( u1_RetNextDtc )
        {
            case DEM_FILTERED_OK :

                if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= DCM_DSP_SID19_SUB42_LEN_RES_DASR )    /* no wrap around */
                {
                    u4_ResDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen;

                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] = u1_DTCSeverity;
                    u4_ResDataLen++;    /* no wrap around */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB42_SHFT_DTCHB);
                    u4_ResDataLen++;    /* no wrap around */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB42_SHFT_DTCMB);
                    u4_ResDataLen++;    /* no wrap around */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] = (uint8)(u4_DTC);
                    u4_ResDataLen++;    /* no wrap around */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] = u1_DtcStatus;
                    u4_ResDataLen++;    /* no wrap around */

                    Dcm_Dsp_Main_stMsgContext.resDataLen = u4_ResDataLen;
                    /* while continue */
                }
                else
                {
                    /* Write Buffer Error Loop End (u1_RetVal != E_OK)      */
                    b_LoopEnd = (boolean)TRUE;
                    u1_NegResCode = DCM_E_RESPONSETOOLONG;
                }
                break;
            case DEM_FILTERED_NO_MATCHING_ELEMENT:
                /* Loop End , Processing completion                         */
                b_LoopEnd = (boolean)TRUE;
                b_SendPosResFlag = (boolean)TRUE;
                break;
            case DEM_FILTERED_PENDING:
                /* Loop End , Wait a processing                             */
                b_LoopEnd = (boolean)TRUE;
                u1_RetVal = DCM_E_PENDING;
                break;
            default:
                /* Loop End , Illegal Return Value                          */
                b_LoopEnd = (boolean)TRUE;
                /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                break;
        }
    }/* while End */

    if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB42_GETDTC );    /* no return check required */
    }
    else
    {
        if( b_SendPosResFlag == (boolean)TRUE )
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
#endif  /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub42_GetDTC
( void )
{
    uint32                                  u4_DTC;
    Dcm_MsgLenType                          u4_ResDataLen;
    Std_ReturnType                          u1_RetVal;
    Dem_UdsStatusByteType                   u1_DtcStatus;
    Dem_DTCSeverityType                     u1_DTCSeverity;
    uint8                                   u1_DTCFuncUnit;
    Dem_ReturnGetNextFilteredElementType    u1_RetNextDtc;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    boolean                                 b_SendPosResFlag;
    boolean                                 b_LoopEnd;


    u4_DTC = (uint32)0x00000000U;
    u1_RetVal = E_OK;
    u1_DtcStatus = (Dem_UdsStatusByteType)0x00U;
    u1_DTCSeverity = (Dem_DTCSeverityType)0x00U;
    u1_DTCFuncUnit = (uint8)0x00U;
    u1_NegResCode = DCM_E_GENERALREJECT;
    b_SendPosResFlag = (boolean)FALSE;
    b_LoopEnd = (boolean)FALSE;

    if( Dcm_Dsp_SID19_Sub42_bGetDTCEnded == (boolean)TRUE)
    {
        b_SendPosResFlag = (boolean)TRUE;
        b_LoopEnd        = (boolean)TRUE;
    }

    while( b_LoopEnd == (boolean)FALSE )
    {
        if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= DCM_DSP_SID19_SUB42_LEN_RES_DASR )    /* no wrap around */
        {
            if( Dcm_Dsp_SID19_Sub42_u2RemainingResDataNumforPB != (uint16)0U )
            {
                u1_RetNextDtc = Dem_DcmGetNextFilteredDTCAndSeverity( &u4_DTC,
                                                                      &u1_DtcStatus,
                                                                      &u1_DTCSeverity,
                                                                      &u1_DTCFuncUnit );
                switch( u1_RetNextDtc )
                {
                    case DEM_FILTERED_OK :
                        u4_ResDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen;

                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] = u1_DTCSeverity;
                        u4_ResDataLen++;    /* no wrap around */
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB42_SHFT_DTCHB);
                        u4_ResDataLen++;    /* no wrap around */
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB42_SHFT_DTCMB);
                        u4_ResDataLen++;    /* no wrap around */
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] = (uint8)(u4_DTC);
                        u4_ResDataLen++;    /* no wrap around */
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] = u1_DtcStatus;
                        u4_ResDataLen++;    /* no wrap around */

                        Dcm_Dsp_Main_stMsgContext.resDataLen = u4_ResDataLen;
                        Dcm_Dsp_SID19_Sub42_u2RemainingResDataNumforPB = Dcm_Dsp_SID19_Sub42_u2RemainingResDataNumforPB - (uint16)1U;  /* no wrap around */
                        break;
                    case DEM_FILTERED_NO_MATCHING_ELEMENT:
                        /* Loop End , Processing completion                         */
                        b_LoopEnd = (boolean)TRUE;
                        b_SendPosResFlag = (boolean)TRUE;
                        Dcm_Dsp_SID19_Sub42_bGetDTCEnded = (boolean)TRUE;
                        break;
                    case DEM_FILTERED_PENDING:
                        /* Loop End , Wait a processing                             */
                        b_LoopEnd = (boolean)TRUE;
                        u1_RetVal = DCM_E_PENDING;
                        break;
                    default:
                        /* Loop End , Illegal Return Value                          */
                        b_LoopEnd = (boolean)TRUE;
                        Dcm_Dsp_SID19_Sub42_bGetDTCEnded = (boolean)TRUE;
                        break;
                }
            }
            else
            {
                Dcm_Dsp_SID19_Sub42_bGetDTCEnded = (boolean)TRUE;
                b_LoopEnd           = (boolean)TRUE;
                b_SendPosResFlag    = (boolean)TRUE;
            }
        }
        else
        {
            b_LoopEnd           = (boolean)TRUE;
            b_SendPosResFlag    = (boolean)TRUE;
        }
    }/* while End */

    if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB42_GETDTC ); /* no return check required */
    }
    else
    {
        if( Dcm_Dsp_SID19_Sub42_bUpdatePageFlag == (boolean)FALSE )
        {
            if( b_SendPosResFlag == (boolean)TRUE )
            {
                if( Dcm_Dsp_SID19_Sub42_bGetDTCEnded == (boolean)TRUE )
                {
                    /* If reading of all RecordNumbers is completed before updatePage, correct the total length of data to the current data length and send it all at once */
                    Dcm_Dsp_SID19_Sub42_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    Dcm_Dsp_SID19_Sub42_u2RemainingResDataNumforPB = (uint16)0U;
                }
                Dcm_Dsp_SID19_Sub42_StartPage();
            }
            else
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
            }
        }
        else
        {
            Dcm_Dsp_SID19_Sub42_AdjustDataLenForPage();
            if( Dcm_Dsp_Main_stMsgContext.resDataLen != (Dcm_MsgLenType)0U )
            {
                Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
            }
        }
    }

    return u1_RetVal;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub42_AdjustDataLenForPage                 */
/* Description   | Adjust data length for page                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_AdjustDataLenForPage
(
    void
)
{
    uint32              u4_PaddingMaxDataLen;
    uint32              u4_RemainingPaddingLen;
    uint32              u4_RemainingResDataLenforPB;
    uint32              u4_ResDataLen;
    uint32              u4_ResDataPos;
    uint32              u4_ResMaxPageLen;
    uint32              u4_ResRemainingPageLen;
    uint8               u1_Cnt;
    boolean             b_LoopEnd;

    b_LoopEnd   = (boolean)FALSE;

    if( Dcm_Dsp_SID19_Sub42_bGetDTCEnded == (boolean)TRUE )
    {
        if( Dcm_Dsp_SID19_Sub42_u2RemainingResDataNumforPB != (uint16)0U )
        {
            u4_RemainingResDataLenforPB = (uint32)((uint32)Dcm_Dsp_SID19_Sub42_u2RemainingResDataNumforPB * (uint32)DCM_DSP_SID19_SUB42_LEN_RES_DASR);    /* no wrap around */
            u4_ResMaxPageLen            = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
            u4_ResDataLen               = Dcm_Dsp_Main_stMsgContext.resDataLen;
            u4_ResRemainingPageLen      = u4_ResMaxPageLen - u4_ResDataLen; /* no wrap around */
            if( u4_RemainingResDataLenforPB > u4_ResRemainingPageLen )
            {
                u4_PaddingMaxDataLen = u4_ResMaxPageLen;
            }
            else
            {
                u4_PaddingMaxDataLen = u4_RemainingResDataLenforPB + u4_ResDataLen; /* no wrap around */
            }

            u4_ResDataPos           = u4_ResDataLen;
            u4_RemainingPaddingLen  = u4_PaddingMaxDataLen - u4_ResDataLen; /* no wrap around */
            
            while( b_LoopEnd == (boolean)FALSE )
            {
                if( u4_RemainingPaddingLen >= (uint32)DCM_DSP_SID19_SUB42_LEN_RES_DASR )
                {
                    for( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)DCM_DSP_SID19_SUB42_LEN_RES_DASR; u1_Cnt++ )
                    {
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)0;
                        u4_ResDataPos = u4_ResDataPos + (uint32)1U;  /* no wrap around */
                    }
                    u4_RemainingPaddingLen = u4_RemainingPaddingLen - (uint32)DCM_DSP_SID19_SUB42_LEN_RES_DASR;   /* no wrap around */
                    Dcm_Dsp_SID19_Sub42_u2RemainingResDataNumforPB = Dcm_Dsp_SID19_Sub42_u2RemainingResDataNumforPB - (uint16)1U;    /* no wrap around */
                }
                else
                {
                    b_LoopEnd   = (boolean)TRUE;
                }
            }/* while End */
            Dcm_Dsp_Main_stMsgContext.resDataLen    = u4_ResDataPos;
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub42_StartPage                            */
/* Description   | Start paged processing of SID19_Sub42                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_StartPage
(
    void
)
{
    Dcm_MsgContextType  st_MsgContext;
    uint16              u2_PbidSid;

    u2_PbidSid = Dcm_P_u2Pbid_Sid19_Sub42;

    st_MsgContext.reqData                           = NULL_PTR;
    st_MsgContext.reqDataLen                        = (Dcm_MsgLenType)0U;
    st_MsgContext.resData                           = NULL_PTR;
    st_MsgContext.msgAddInfo.reqType                = (uint8)0U;
    st_MsgContext.msgAddInfo.suppressPosResponse    = STD_OFF;
    st_MsgContext.resMaxDataLen                     = (Dcm_MsgLenType)0U;
    st_MsgContext.idContext                         = (Dcm_IdContextType)0U;
    st_MsgContext.dcmRxPduId                        = (PduIdType)0U;
    st_MsgContext.resDataLen                        = Dcm_Dsp_SID19_Sub42_u4ResDataLenforPB;

    Dcm_Dsp_MsgMaker_StartPagedProcessing( &st_MsgContext, u2_PbidSid );

    return ;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub42_ChkEnableFGID                        */
/* Description   | Check if FGID is enable and set DTCKind.                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1FGID       : FGID                                */
/*               | [OUT] ptReqDTCKind : DTCKind                             */
/* Return Value  | E_OK               : FGID is enabled.                    */
/*               | E_NOT_OK           : FGID is disabled.                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub42_ChkEnableFGID
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
        case DCM_DSP_SID19_SUB42_FGID_VAL_33:
            *ptReqDTCKind = DEM_DTC_KIND_EMISSION_REL_DTCS;
            u1_RetVal = E_OK;
            break;
        case DCM_DSP_SID19_SUB42_FGID_VAL_FF:
            u1_AcceptFF = Dcm_Dsp_SID19_Sub42_CheckFGIDFFRequestIsAcceptable();
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
#endif /* DCM_SUPPORT_SID19_SUB42 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-2-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File************************************************************/
