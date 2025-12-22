/* Dcm_Dsp_SID19_Sub56(v5-8-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub56/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub56.h>
#if ( DCM_SUPPORT_SID19_SUB56 == STD_ON )
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID19_SUB56_SHFT_DTC_HI                 ((uint8)16U)
#define     DCM_DSP_SID19_SUB56_SHFT_DTC_MI                 ((uint8)8U)
#define     DCM_DSP_SID19_SUB56_FGID_VALID_VAL              ((uint8)0x33U)
#define     DCM_DSP_SID19_SUB56_RGI_INVALID_VAL             ((uint8)0xFFU)
#define     DCM_DSP_SID19_SUB56_DTCSAM_00                   ((uint8)0x00U)
#define     DCM_DSP_SID19_SUB56_FGID_LEN                    ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB56_RGI_LEN                     ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB56_DTCSAM_LEN                  ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB56_DTCFID_LEN                  ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB56_DTC_LEN                     ((Dcm_MsgLenType)3U)
#define     DCM_DSP_SID19_SUB56_SODTC_LEN                   ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB56_DTCASR_LEN                  ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB56_DTC_LEN + DCM_DSP_SID19_SUB56_SODTC_LEN))
#define     DCM_DSP_SID19_SUB56_REQ_OFS_FGID                ((uint32)0U)
#define     DCM_DSP_SID19_SUB56_REQ_OFS_RGI                 ((uint32)1U)
#define     DCM_DSP_SID19_SUB56_REQ_DATA_LEN                (DCM_DSP_SID19_SUB56_FGID_LEN + DCM_DSP_SID19_SUB56_RGI_LEN)
#define     DCM_DSP_SID19_SUB56_RES_OFS_FGID                ((uint32)0U)
#define     DCM_DSP_SID19_SUB56_RES_OFS_DTCSAM              ((uint32)1U)
#define     DCM_DSP_SID19_SUB56_RES_OFS_DTCFID              ((uint32)2U)
#define     DCM_DSP_SID19_SUB56_RES_OFS_RGI                 ((uint32)3U)
#define     DCM_DSP_SID19_SUB56_RES_DATA_MIN_LEN            ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB56_FGID_LEN + DCM_DSP_SID19_SUB56_DTCSAM_LEN + DCM_DSP_SID19_SUB56_DTCFID_LEN + DCM_DSP_SID19_SUB56_RGI_LEN))


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_CancelProc
( void );
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_ChkReqParams
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_GetDTC
( void );
#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_GetSizeOfDTC
( void );
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_AdjustDataLenForPage
( void );
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_StartPage
( void );
#endif /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON )
static VAR(uint32, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub56_u4ResDataLenforPB;
static VAR(uint16, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub56_u2RemainingResDataNumforPB;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub56_bUpdatePageFlag;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub56_bGetDTCEnded;
#endif /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON */

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
/* Function Name | Dcm_SID19_Sub56                                          */
/* Description   | Request processing of SID19_Sub56                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/*               |   DCM_E_PENDING  : Result Pending                        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID19_Sub56
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub56_InitialProc( pMsgContext );
    }
    else
    {
        Dcm_Dsp_SID19_Sub56_CancelProc();
    }

    return u1_RetVal;
}

#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub56_GetSizeOfDTCCbk                      */
/* Description   | Call Back Function to Continue SID19_Sub56 Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event Id                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_GetSizeOfDTCCbk
(
    const uint8 u1EventId
)
{
    Std_ReturnType  u1_RetGetSizeOfDTC;

    u1_RetGetSizeOfDTC = Dcm_Dsp_SID19_Sub56_GetSizeOfDTC();
    if( u1_RetGetSizeOfDTC == (Std_ReturnType)E_OK )
    {
        (void)Dcm_Dsp_SID19_Sub56_GetDTC();         /* no return check required */
    }

    return;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub56_GetDTCCbk                            */
/* Description   | Call Back Function to Continue SID19_Sub56 Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event Id                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_GetDTCCbk
(
    const uint8 u1EventId
)
{
    (void)Dcm_Dsp_SID19_Sub56_GetDTC();     /* no return check required */

    return;
}

#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub56_UpdatePage                           */
/* Description   | UpdatePage of SID19_Sub56                                */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptResData       : Response Data                    */
/*               | [IN]  u4ResMaxDataLen : Buffer Size of Response Data     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_UpdatePage
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
        Dcm_Dsp_SID19_Sub56_bUpdatePageFlag = (boolean)TRUE;
        Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
    }
    else
    {
        Dcm_Dsp_Main_stMsgContext.resData          = ptResData;
        Dcm_Dsp_Main_stMsgContext.resMaxDataLen    = u4ResMaxDataLen;
        Dcm_Dsp_Main_stMsgContext.resDataLen       = (uint32)0U;

        u1_RetGetDTC = Dcm_Dsp_SID19_Sub56_GetDTC();
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
/* Function Name | Dcm_Dsp_SID19_Sub56_CancelPage                           */
/* Description   | CancelPage of SID19_Sub56                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_CancelPage
( void )
{
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB56_GETDTC, (boolean)FALSE );
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub56_InitialProc                          */
/* Description   | Initial process of SID19_Sub56                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                : Result OK                          */
/*               | DCM_E_PENDING       : Result Pending                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dem_DTCTranslationFormatType    u1_DTCFormamt;
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Std_ReturnType                  u1_RetChkReqParams;
    Dem_ReturnSetFilterType         u1_RetSetFilter;
    Std_ReturnType                  u1_RetStatusAvailabilityMask;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_SendNegResFlag;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext   = *ptMsgContext;
    b_SendNegResFlag            = (boolean)FALSE;
    u1_NegResCode               = DCM_E_GENERALREJECT;
    u1_RetVal                   = E_OK;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID19_SUB56_REQ_DATA_LEN )
    {
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= DCM_DSP_SID19_SUB56_RES_DATA_MIN_LEN )
        {
            u1_RetChkReqParams = Dcm_Dsp_SID19_Sub56_ChkReqParams( &Dcm_Dsp_Main_stMsgContext );
            if( u1_RetChkReqParams == (Std_ReturnType)E_OK )
            {
                u1_DTCStatusMask = DCM_DSP_SID19_SUB56_DTCSAM_00;
                u1_RetStatusAvailabilityMask = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask, DEM_DTC_ORIGIN_PRIMARY_MEMORY );
                if( u1_RetStatusAvailabilityMask == (Std_ReturnType)E_OK )
                {
                    u1_DTCFormamt = Dem_DcmGetTranslationType();
                    if( ( u1_DTCFormamt == DEM_DTC_TRANSLATION_SAEJ1939_73 ) || ( u1_DTCFormamt == DEM_DTC_TRANSLATION_J2012DA_FORMAT_04 ) )
                    {
                        u1_RetSetFilter = Dem_DcmSetDTCFilterForReadiness( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB56_REQ_OFS_RGI] );

                        if( u1_RetSetFilter == DEM_FILTER_ACCEPTED )
                        {
                            /* Set FunctionalGroupIdentifier */
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB56_RES_OFS_FGID] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB56_REQ_OFS_FGID];
                            /* Set DTCStatusAvailableMask */
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB56_RES_OFS_DTCSAM] = (Dcm_MsgItemType)u1_DTCStatusMask;
                            /* Set DTCFormatIdentifier */
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB56_RES_OFS_DTCFID] = (Dcm_MsgItemType)u1_DTCFormamt;
                            /* Set DTCReadinessGroupIdentifier */
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB56_RES_OFS_RGI] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB56_REQ_OFS_RGI];

                            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB56_FGID_LEN + 
                                                                   DCM_DSP_SID19_SUB56_DTCSAM_LEN + 
                                                                   DCM_DSP_SID19_SUB56_DTCFID_LEN + 
                                                                   DCM_DSP_SID19_SUB56_RGI_LEN;

                            u1_RetVal = Dcm_Dsp_SID19_Sub56_GetDTC();
                        }
                        else if( u1_RetSetFilter == DEM_WRONG_FILTER )
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
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }

    return u1_RetVal;

}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dem_DTCTranslationFormatType    u1_DTCFormamt;
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Std_ReturnType                  u1_RetChkReqParams;
    Std_ReturnType                  u1_RetGetSizeOfDTC;
    Dem_ReturnSetFilterType         u1_RetSetFilter;
    Std_ReturnType                  u1_RetStatusAvailabilityMask;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_SendNegResFlag;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext           = *ptMsgContext;
    Dcm_Dsp_SID19_Sub56_bGetDTCEnded    = (boolean)FALSE;
    b_SendNegResFlag                    = (boolean)FALSE;
    u1_NegResCode                       = DCM_E_GENERALREJECT;
    u1_RetVal                           = E_OK;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID19_SUB56_REQ_DATA_LEN )
    {
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= DCM_DSP_SID19_SUB56_RES_DATA_MIN_LEN )
        {
            u1_RetChkReqParams = Dcm_Dsp_SID19_Sub56_ChkReqParams( &Dcm_Dsp_Main_stMsgContext );
            if( u1_RetChkReqParams == (Std_ReturnType)E_OK )
            {
                u1_DTCStatusMask = DCM_DSP_SID19_SUB56_DTCSAM_00;
                u1_RetStatusAvailabilityMask = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask, DEM_DTC_ORIGIN_PRIMARY_MEMORY );
                if( u1_RetStatusAvailabilityMask == (Std_ReturnType)E_OK )
                {
                    u1_DTCFormamt = Dem_DcmGetTranslationType();
                    if( ( u1_DTCFormamt == DEM_DTC_TRANSLATION_SAEJ1939_73 ) || ( u1_DTCFormamt == DEM_DTC_TRANSLATION_J2012DA_FORMAT_04 ) )
                    {
                        u1_RetSetFilter = Dem_DcmSetDTCFilterForReadiness( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB56_REQ_OFS_RGI] );

                        if( u1_RetSetFilter == DEM_FILTER_ACCEPTED )
                        {
                            /* Set FunctionalGroupIdentifier */
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB56_RES_OFS_FGID] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB56_REQ_OFS_FGID];
                            /* Set DTCStatusAvailableMask */
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB56_RES_OFS_DTCSAM] = (Dcm_MsgItemType)u1_DTCStatusMask;
                            /* Set DTCFormatIdentifier */
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB56_RES_OFS_DTCFID] = (Dcm_MsgItemType)u1_DTCFormamt;
                            /* Set DTCReadinessGroupIdentifier */
                            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB56_RES_OFS_RGI] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB56_REQ_OFS_RGI];

                            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB56_FGID_LEN + 
                                                                   DCM_DSP_SID19_SUB56_DTCSAM_LEN + 
                                                                   DCM_DSP_SID19_SUB56_DTCFID_LEN + 
                                                                   DCM_DSP_SID19_SUB56_RGI_LEN;
 
                            u1_RetGetSizeOfDTC = Dcm_Dsp_SID19_Sub56_GetSizeOfDTC();
                            if( u1_RetGetSizeOfDTC == (Std_ReturnType)E_OK )
                            {
                                u1_RetVal = Dcm_Dsp_SID19_Sub56_GetDTC();
                            }
                            else if( u1_RetGetSizeOfDTC == (Std_ReturnType)DCM_E_PENDING )
                            {
                                u1_RetVal = DCM_E_PENDING;
                            }
                            else
                            {
                                /* no process */
                                /* General Reject    -> 0x10                            */
                                /* NRC is sent in Dcm_Dsp_SID19_Sub56_GetSizeOfDTC()    */
                            }
                        }
                        else if( u1_RetSetFilter == DEM_WRONG_FILTER )
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
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }

    return u1_RetVal;

}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub56_ChkReqParams                         */
/* Description   | Check Parameters of SID19_Sub56 request                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK            : Parameters Check OK                  */
/*               |   E_NOT_OK        : Parameters Check NG                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_ChkReqParams
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    if( ptMsgContext->reqData[DCM_DSP_SID19_SUB56_REQ_OFS_FGID] == DCM_DSP_SID19_SUB56_FGID_VALID_VAL )
    {
        if( ptMsgContext->reqData[DCM_DSP_SID19_SUB56_REQ_OFS_RGI] != DCM_DSP_SID19_SUB56_RGI_INVALID_VAL )
        {
            u1_RetVal = E_OK;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub56_CancelProc                           */
/* Description   | Receive Cancel request and Set Cancel Flag               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_OFF )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_CancelProc
( void )
{
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB56_GETDTC, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_CancelProc
( void )
{
    Dcm_Main_EvtDistr_RetType   u1_RetDelGetSizeofDTC;

    u1_RetDelGetSizeofDTC = Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB56_GETSIZE, (boolean)FALSE );
    if( u1_RetDelGetSizeofDTC != DCM_MAIN_EVTDISTR_E_OK )
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB56_GETDTC, (boolean)FALSE ); /* no return check required */
    }
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub56_GetSizeOfDTC                         */
/* Description   | Get Number of DTCs and calculate response data length    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |    E_OK             : Processing normal                  */
/*               |    DCM_E_PENDING    : Result Pending                     */
/*               |    E_NOT_OK         : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_GetSizeOfDTC
( void )
{
    uint16                                  u2_NumOfDTC;
    Dem_ReturnGetNumberOfFilteredDTCType    u1_RetNumOfFilDTCForRd;
    Std_ReturnType                          u1_RetVal;

    u1_RetVal   = E_OK;
    u2_NumOfDTC = (uint16)0U;

    u1_RetNumOfFilDTCForRd = Dem_DcmGetNumberOfFilteredDTCForReadiness( &u2_NumOfDTC );
    switch( u1_RetNumOfFilDTCForRd )
    {
        case DEM_NUMBER_OK:
            Dcm_Dsp_SID19_Sub56_u4ResDataLenforPB           = Dcm_Dsp_Main_stMsgContext.resDataLen + ((uint32)u2_NumOfDTC * (uint32)DCM_DSP_SID19_SUB56_DTCASR_LEN); /* no wrap around */
            Dcm_Dsp_SID19_Sub56_u2RemainingResDataNumforPB  = u2_NumOfDTC;
            Dcm_Dsp_SID19_Sub56_bUpdatePageFlag             = (boolean)FALSE;
            break;
        case DEM_NUMBER_PENDING:
            u1_RetVal = DCM_E_PENDING;
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB56_GETSIZE );   /* no return check required */
            break;
        default:
            /* General Reject -> 0x10 */
            u1_RetVal = E_NOT_OK;
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            break;
    }

    return u1_RetVal;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub56_GetDTC                               */
/* Description   | Get DTC and Edit Response or Register Event              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                : Result OK                          */
/*               | DCM_E_PENDING       : Result Pending                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_GetDTC
( void )
{
    uint32                                  u4_DTC;
    Dcm_MsgLenType                          u4_ResDataPos;
    Dem_UdsStatusByteType                   u1_DTCStatus;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    Dem_ReturnGetNextFilteredElementType    u1_RetNextDTC;
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
        u1_RetNextDTC = Dem_DcmGetNextFilteredDTCForReadiness( &u4_DTC, &u1_DTCStatus );
        switch( u1_RetNextDTC )
        {
            case DEM_FILTERED_OK:
                if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= DCM_DSP_SID19_SUB56_DTCASR_LEN )    /* no wrap around */
                {
                    /* DTC Data Set */
                    u4_ResDataPos = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    /* Set DTCHighByte */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB56_SHFT_DTC_HI);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set DTCMiddleByte */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB56_SHFT_DTC_MI);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set DTCLowByte */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set statusOfDTC */
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = u1_DTCStatus;

                    Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID19_SUB56_DTCASR_LEN;   /* no wrap around */
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
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB56_GETDTC );    /* no return check required */
    }
    else
    {
        if( b_SendPosRes == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
        }
    }

    return u1_RetVal;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_GetDTC
( void )
{
    uint32                                  u4_DTC;
    Dcm_MsgLenType                          u4_ResDataPos;
    Dem_UdsStatusByteType                   u1_DTCStatus;
    Dem_ReturnGetNextFilteredElementType    u1_RetNextDTC;
    Std_ReturnType                          u1_RetVal;
    boolean                                 b_LoopEnd;
    boolean                                 b_SendPosRes;

    b_LoopEnd     = (boolean)FALSE;
    b_SendPosRes  = (boolean)FALSE;
    u1_DTCStatus  = (Dem_UdsStatusByteType)0U;
    u1_RetVal     = E_OK;
    u4_DTC        = (uint32)0U;

    if( Dcm_Dsp_SID19_Sub56_bGetDTCEnded == (boolean)TRUE)
    {
        b_SendPosRes     = (boolean)TRUE;
        b_LoopEnd        = (boolean)TRUE;
    }

    while( b_LoopEnd == (boolean)FALSE )
    {
        if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= DCM_DSP_SID19_SUB56_DTCASR_LEN )    /* no wrap around */
        {
            if( Dcm_Dsp_SID19_Sub56_u2RemainingResDataNumforPB != (uint16)0U )
            {
                u1_RetNextDTC = Dem_DcmGetNextFilteredDTCForReadiness( &u4_DTC, &u1_DTCStatus );
                switch( u1_RetNextDTC )
                {
                    case DEM_FILTERED_OK:
                        /* DTC Data Set */
                        u4_ResDataPos = Dcm_Dsp_Main_stMsgContext.resDataLen;
                        /* Set DTCHighByte */
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB56_SHFT_DTC_HI);
                        u4_ResDataPos++;    /* no wrap around */
                        /* Set DTCMiddleByte */
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB56_SHFT_DTC_MI);
                        u4_ResDataPos++;    /* no wrap around */
                        /* Set DTCLowByte */
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)(u4_DTC);
                        u4_ResDataPos++;    /* no wrap around */
                        /* Set statusOfDTC */
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = u1_DTCStatus;

                        Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID19_SUB56_DTCASR_LEN;   /* no wrap around */

                        Dcm_Dsp_SID19_Sub56_u2RemainingResDataNumforPB = Dcm_Dsp_SID19_Sub56_u2RemainingResDataNumforPB - (uint16)1U;  /* no wrap around */
                        break;
                    case DEM_FILTERED_NO_MATCHING_ELEMENT:
                        Dcm_Dsp_SID19_Sub56_bGetDTCEnded = (boolean)TRUE;
                        b_LoopEnd = (boolean)TRUE;
                        b_SendPosRes = (boolean)TRUE;
                        break;
                    case DEM_FILTERED_PENDING:
                        b_LoopEnd = (boolean)TRUE;
                        u1_RetVal = DCM_E_PENDING;
                        break;
                    default:
                        /* General Reject -> 0x10 */
                        Dcm_Dsp_SID19_Sub56_bGetDTCEnded = (boolean)TRUE;
                        b_LoopEnd = (boolean)TRUE;
                        break;
                }
            }
            else
            {
                Dcm_Dsp_SID19_Sub56_bGetDTCEnded = (boolean)TRUE;
                b_LoopEnd = (boolean)TRUE;
                b_SendPosRes = (boolean)TRUE;
            }
        }
        else
        {
            b_LoopEnd = (boolean)TRUE;
            b_SendPosRes = (boolean)TRUE;
        }
    }/* while End */

    if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB56_GETDTC );    /* no return check required */
    }
    else
    {
        if( Dcm_Dsp_SID19_Sub56_bUpdatePageFlag == (boolean)FALSE )
        {
            if( b_SendPosRes == (boolean)TRUE )
            {
                if( Dcm_Dsp_SID19_Sub56_bGetDTCEnded == (boolean)TRUE )
                {
                    /* If reading of all RecordNumbers is completed before updatePage, correct the total length of data to the current data length and send it all at once */
                    Dcm_Dsp_SID19_Sub56_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    Dcm_Dsp_SID19_Sub56_u2RemainingResDataNumforPB = (uint16)0U;
                }
                Dcm_Dsp_SID19_Sub56_StartPage();
            }
            else
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            }
        }
        else
        {
            Dcm_Dsp_SID19_Sub56_AdjustDataLenForPage();
            if( Dcm_Dsp_Main_stMsgContext.resDataLen != (Dcm_MsgLenType)0U )
            {
                Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
            }
        }
    }

    return u1_RetVal;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub56_AdjustDataLenForPage                 */
/* Description   | Adjust data length for page                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_AdjustDataLenForPage
( void )
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

    if( Dcm_Dsp_SID19_Sub56_bGetDTCEnded == (boolean)TRUE )
    {
        if( Dcm_Dsp_SID19_Sub56_u2RemainingResDataNumforPB != (uint16)0U )
        {
            u4_RemainingResDataLenforPB = (uint32)Dcm_Dsp_SID19_Sub56_u2RemainingResDataNumforPB * (uint32)DCM_DSP_SID19_SUB56_DTCASR_LEN;    /* no wrap around */
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
                if( u4_RemainingPaddingLen >= (uint32)DCM_DSP_SID19_SUB56_DTCASR_LEN )
                {
                    for( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)DCM_DSP_SID19_SUB56_DTCASR_LEN; u1_Cnt++ )
                    {
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)0U;
                        u4_ResDataPos = u4_ResDataPos + (uint32)1U;  /* no wrap around */
                    }
                    u4_RemainingPaddingLen = u4_RemainingPaddingLen - (uint32)DCM_DSP_SID19_SUB56_DTCASR_LEN;   /* no wrap around */
                    Dcm_Dsp_SID19_Sub56_u2RemainingResDataNumforPB = Dcm_Dsp_SID19_Sub56_u2RemainingResDataNumforPB - (uint16)1U;    /* no wrap around */
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
/* Function Name | Dcm_Dsp_SID19_Sub56_StartPage                            */
/* Description   | Start paged processing of SID19_Sub56                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_StartPage
( void )
{
    Dcm_MsgContextType  st_MsgContext;
    uint16              u2_PbidSid;

    u2_PbidSid = Dcm_P_u2Pbid_Sid19_Sub56;

    st_MsgContext.reqData                           = NULL_PTR;
    st_MsgContext.reqDataLen                        = (Dcm_MsgLenType)0U;
    st_MsgContext.resData                           = NULL_PTR;
    st_MsgContext.msgAddInfo.reqType                = (uint8)0U;
    st_MsgContext.msgAddInfo.suppressPosResponse    = STD_OFF;
    st_MsgContext.resMaxDataLen                     = (Dcm_MsgLenType)0U;
    st_MsgContext.idContext                         = (Dcm_IdContextType)0U;
    st_MsgContext.dcmRxPduId                        = (PduIdType)0U;
    st_MsgContext.resDataLen                        = Dcm_Dsp_SID19_Sub56_u4ResDataLenforPB;

    Dcm_Dsp_MsgMaker_StartPagedProcessing( &st_MsgContext, u2_PbidSid );

    return ;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB56_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID19_SUB56 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-2-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
