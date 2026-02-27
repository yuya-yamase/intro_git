/* Dcm_Dsp_SID19_Sub1A(v5-8-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
#define     DCM_DSP_SID19_SUB1A_DTCEDRN_NUM01               ((uint8)0x01U)
#define     DCM_DSP_SID19_SUB1A_DTCEDRN_NUM90               ((uint8)0x90U)
#define     DCM_DSP_SID19_SUB1A_DTCEDRN_NUM9F               ((uint8)0x9FU)
#define     DCM_DSP_SID19_SUB1A_DTCEDRN_NUMFD               ((uint8)0xFDU)
#define     DCM_DSP_SID19_SUB1A_DTCSAM_00                   ((uint8)0x00U)
#define     DCM_DSP_SID19_SUB1A_DTCSAM_LEN                  ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB1A_DTCEDRN_LEN                 ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB1A_DTC_LEN                     ((Dcm_MsgLenType)3U)
#define     DCM_DSP_SID19_SUB1A_SODTC_LEN                   ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB1A_DTCASR_LEN                  ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB1A_DTC_LEN + DCM_DSP_SID19_SUB1A_SODTC_LEN))
#define     DCM_DSP_SID19_SUB1A_REQ_OFS_DTCEDRN             ((uint32)0U)
#define     DCM_DSP_SID19_SUB1A_REQ_DATA_LEN                (DCM_DSP_SID19_SUB1A_DTCEDRN_LEN)
#define     DCM_DSP_SID19_SUB1A_RES_OFS_DTCSAM              ((uint32)0U)
#define     DCM_DSP_SID19_SUB1A_RES_DATA_MIN_LEN            (DCM_DSP_SID19_SUB1A_DTCSAM_LEN)


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
#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_ChkAndSetEDRN
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_GetSizeOfDTC
(
    void
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_AdjustDataLenForPage
(
    void
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_StartPage
(
    void
);
#endif /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON )
static VAR(uint32, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub1A_u4ResDataLenforPB;
static VAR(uint16, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub1A_u2RemainingResDataNumforPB;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub1A_bUpdatePageFlag;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub1A_bGetDTCEnded;
#endif /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON */

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

#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_GetSizeOfDTCCbk                      */
/* Description   | Call Back Function to Continue SID19_Sub1A Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event Id                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_GetSizeOfDTCCbk
(
    const uint8 u1EventId
)
{
    Std_ReturnType  u1_RetGetSizeOfDTC;
    Std_ReturnType  u1_RetChkEDRN;

    u1_RetGetSizeOfDTC = Dcm_Dsp_SID19_Sub1A_GetSizeOfDTC();
    if( u1_RetGetSizeOfDTC == (Std_ReturnType)E_OK )
    {
        u1_RetChkEDRN = Dcm_Dsp_SID19_Sub1A_ChkAndSetEDRN();
        if( u1_RetChkEDRN == (Std_ReturnType)E_OK )
        {
            (void)Dcm_Dsp_SID19_Sub1A_GetDTC();         /* no return check required */
        }
    }

    return ;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_GetDTCCbk                            */
/* Description   | Call Back Function to Continue SID19_Sub1A Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_GetDTCCbk
(
    const uint8 u1EventId
)
{
    (void)Dcm_Dsp_SID19_Sub1A_GetDTC();     /* no return check required */

    return;
}

#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_UpdatePage                           */
/* Description   | UpdatePage of SID 19 SF 1A                               */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptResData       : Response Data                    */
/*               | [IN]  u4ResMaxDataLen : Buffer Size of Response Data     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_UpdatePage
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
        Dcm_Dsp_SID19_Sub1A_bUpdatePageFlag = (boolean)TRUE;
        Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
    }
    else
    {
        Dcm_Dsp_Main_stMsgContext.resData          = ptResData;
        Dcm_Dsp_Main_stMsgContext.resMaxDataLen    = u4ResMaxDataLen;
        Dcm_Dsp_Main_stMsgContext.resDataLen       = (uint32)0U;

        u1_RetGetDTC = Dcm_Dsp_SID19_Sub1A_GetDTC();
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
/* Function Name | Dcm_Dsp_SID19_Sub1A_CancelPage                           */
/* Description   | CancelPage of SID 19 SF 1A                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_CancelPage
(void)
{
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB1A_GETDTC, (boolean)FALSE );
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON */

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
#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Dcm_MsgItemType                 u1_ReqEDRN;
    Std_ReturnType                  u1_RetChkEnableRecNum;
    Dem_ReturnSetFilterType         u1_RetDemFilter;
    Std_ReturnType                  u1_RetStatusAvailabilityMask;
    Std_ReturnType                  u1_RetVal;
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
            u1_ReqEDRN = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB1A_REQ_OFS_DTCEDRN];

            u1_RetChkEnableRecNum = Dcm_Dsp_SID19_Sub1A_ChkEnableRecNum( u1_ReqEDRN );

            if( u1_RetChkEnableRecNum == (Std_ReturnType)E_OK )
            {
                u1_DTCStatusMask = DCM_DSP_SID19_SUB1A_DTCSAM_00;
                u1_RetStatusAvailabilityMask = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask,
                                                                                    DEM_DTC_ORIGIN_PRIMARY_MEMORY );
                if( u1_RetStatusAvailabilityMask == (Std_ReturnType)E_OK )
                {
                    u1_RetDemFilter = Dem_DcmSetEDRNumberFilter( u1_ReqEDRN );
                    if( u1_RetDemFilter == DEM_FILTER_ACCEPTED )
                    {
                        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB1A_RES_OFS_DTCSAM] = u1_DTCStatusMask;
                        Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB1A_DTCSAM_LEN;

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
#endif  /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Dcm_MsgItemType                 u1_ReqEDRN;
    Std_ReturnType                  u1_RetChkEDRN;
    Std_ReturnType                  u1_RetChkEnableRecNum;
    Dem_ReturnSetFilterType         u1_RetDemFilter;
    Std_ReturnType                  u1_RetGetSizeOfDTC;
    Std_ReturnType                  u1_RetStatusAvailabilityMask;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_SendNegResFlag;

    b_SendNegResFlag = (boolean)FALSE;
    u1_NegResCode    = DCM_E_GENERALREJECT;
    u1_RetVal        = E_OK;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID19_Sub1A_bGetDTCEnded = (boolean)FALSE;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID19_SUB1A_REQ_DATA_LEN )
    {
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= DCM_DSP_SID19_SUB1A_RES_DATA_MIN_LEN )
        {
            u1_ReqEDRN = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB1A_REQ_OFS_DTCEDRN];

            u1_RetChkEnableRecNum = Dcm_Dsp_SID19_Sub1A_ChkEnableRecNum( u1_ReqEDRN );

            if( u1_RetChkEnableRecNum == (Std_ReturnType)E_OK )
            {
                u1_DTCStatusMask = DCM_DSP_SID19_SUB1A_DTCSAM_00;
                u1_RetStatusAvailabilityMask = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask,
                                                                                    DEM_DTC_ORIGIN_PRIMARY_MEMORY );
                if( u1_RetStatusAvailabilityMask == (Std_ReturnType)E_OK )
                {
                    u1_RetDemFilter = Dem_DcmSetEDRNumberFilter( u1_ReqEDRN );
                    if( u1_RetDemFilter == DEM_FILTER_ACCEPTED )
                    {
                        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID19_SUB1A_RES_OFS_DTCSAM] = u1_DTCStatusMask;
                        Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB1A_DTCSAM_LEN;

                        u1_RetGetSizeOfDTC = Dcm_Dsp_SID19_Sub1A_GetSizeOfDTC();
                        switch( u1_RetGetSizeOfDTC )
                        {
                            case E_OK:
                                u1_RetChkEDRN = Dcm_Dsp_SID19_Sub1A_ChkAndSetEDRN();
                                if( u1_RetChkEDRN == (Std_ReturnType)E_OK )
                                {
                                    u1_RetVal = Dcm_Dsp_SID19_Sub1A_GetDTC();
                                    /* This Return Value is check-free */
                                }
                                break;
                            case DCM_E_PENDING:
                                u1_RetVal = DCM_E_PENDING;
                                break;
                            default:
                                /* no process */
                                break;
                        }
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
#endif  /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_CancelProc                           */
/* Description   | Cancel process of SID19_Sub1A request                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_OFF )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_CancelProc
( void )
{
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB1A_GETDTC,    /* no return check required */
                                         (boolean)FALSE );

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_CancelProc
( void )
{
    Dcm_Main_EvtDistr_RetType   u1_RetDelGetSizeofDTC;

    u1_RetDelGetSizeofDTC = Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB1A_GETSIZE, (boolean)FALSE );
    if( u1_RetDelGetSizeofDTC != DCM_MAIN_EVTDISTR_E_OK )
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB1A_GETDTC, (boolean)FALSE ); /* no return check required */
    }
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_GetSizeOfDTC                         */
/* Description   | Get Number of DTCs and calculate response data length    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |    E_OK             : Processing normal                  */
/*               |    DCM_E_PENDING    : Result Pending                     */
/*               |    E_NOT_OK         : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_GetSizeOfDTC
(
    void
)
{
    uint16                                  u2_NumOfDTC;
    Dem_ReturnGetNumberOfFilteredDTCType    u1_RetNumOfFilDTC;
    Std_ReturnType                          u1_RetVal;

    u1_RetVal   = E_OK;
    u2_NumOfDTC = (uint16)0U;

    u1_RetNumOfFilDTC = Dem_DcmGetNumberOfEDRNumFilteredDTC( &u2_NumOfDTC );
    switch( u1_RetNumOfFilDTC )
    {
        case DEM_NUMBER_OK:
            Dcm_Dsp_SID19_Sub1A_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen +
                                                        ( (uint32)u2_NumOfDTC * (uint32)DCM_DSP_SID19_SUB1A_DTCASR_LEN ) +  /* no wrap around */
                                                        (uint32)DCM_DSP_SID19_SUB1A_DTCEDRN_LEN;
            Dcm_Dsp_SID19_Sub1A_u2RemainingResDataNumforPB  = u2_NumOfDTC;
            Dcm_Dsp_SID19_Sub1A_bUpdatePageFlag             = (boolean)FALSE;
            break;
        case DEM_NUMBER_PENDING:
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB1A_GETSIZE );   /* no return check required */
            u1_RetVal = DCM_E_PENDING;
            break;
        default:
            /*   General Reject    -> 0x10                              */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            u1_RetVal = E_NOT_OK;
            break;
        }

    return u1_RetVal;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON */

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
#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_OFF )
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
        u1_RetNextDTC = Dem_DcmGetNextEDRNumFilteredDTC( &u4_DTC, &u1_DTCStatus );
        switch( u1_RetNextDTC )
        {
            case DEM_FILTERED_OK:

                b_LenChkResult = (boolean)FALSE;
                if( Dcm_Dsp_Main_stMsgContext.resDataLen == (Dcm_MsgLenType)DCM_DSP_SID19_SUB1A_DTCSAM_LEN )
                {
                    /* In case for the first time */
                    if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= (DCM_DSP_SID19_SUB1A_DTCEDRN_LEN + DCM_DSP_SID19_SUB1A_DTCASR_LEN) )   /* no wrap around */
                    {
                        /* Set Extended Data Record Number */
                        Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB1A_REQ_OFS_DTCEDRN];
                        Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB1A_DTCSAM_LEN + DCM_DSP_SID19_SUB1A_DTCEDRN_LEN;

                        b_LenChkResult = (boolean)TRUE;
                    }
                }
                else
                {
                    /* In case for the second time or more */
                    if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= DCM_DSP_SID19_SUB1A_DTCASR_LEN )    /* no wrap around */
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

                    Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID19_SUB1A_DTCASR_LEN;   /* no wrap around */
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
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
        }
    }

    return u1_RetVal;
}

#endif  /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_GetDTC
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

    if( Dcm_Dsp_SID19_Sub1A_bGetDTCEnded == (boolean)TRUE )
    {
        b_SendPosRes        = (boolean)TRUE;
        b_LoopEnd           = (boolean)TRUE;
    }

    while( b_LoopEnd == (boolean)FALSE )
    {
        if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= DCM_DSP_SID19_SUB1A_DTCASR_LEN )    /* no wrap around */
        {
            if( Dcm_Dsp_SID19_Sub1A_u2RemainingResDataNumforPB != (uint16)0U )
            {
                u1_RetNextDTC = Dem_DcmGetNextEDRNumFilteredDTC( &u4_DTC, &u1_DTCStatus );
                switch( u1_RetNextDTC )
                {
                    case DEM_FILTERED_OK:
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

                        Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + DCM_DSP_SID19_SUB1A_DTCASR_LEN;   /* no wrap around */
                        Dcm_Dsp_SID19_Sub1A_u2RemainingResDataNumforPB = Dcm_Dsp_SID19_Sub1A_u2RemainingResDataNumforPB - (uint16)1U;   /* no wrap around */
                        break;
                    case DEM_FILTERED_NO_MATCHING_ELEMENT:
                        /* Loop End , Processing completion */
                        Dcm_Dsp_SID19_Sub1A_bGetDTCEnded = (boolean)TRUE;
                        b_LoopEnd = (boolean)TRUE;
                        b_SendPosRes = (boolean)TRUE;
                        break;
                    case DEM_FILTERED_PENDING:
                        /* Loop End , Wait a processing */
                        b_LoopEnd = (boolean)TRUE;
                        u1_RetVal = DCM_E_PENDING;
                        break;
                    default:
                        /* Loop End , Illegal Return Value */
                        Dcm_Dsp_SID19_Sub1A_bGetDTCEnded = (boolean)TRUE;
                        b_LoopEnd = (boolean)TRUE;
                        break;
                }
            }
            else
            {
                Dcm_Dsp_SID19_Sub1A_bGetDTCEnded = (boolean)TRUE;
                b_LoopEnd                        = (boolean)TRUE;
                b_SendPosRes                     = (boolean)TRUE;
            }
        }
        else
        {
            b_LoopEnd           = (boolean)TRUE;
            b_SendPosRes        = (boolean)TRUE;
        }
    }/* while End */

    if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB1A_GETDTC );    /* no return check required */
    }
    else
    {
        if( Dcm_Dsp_SID19_Sub1A_bUpdatePageFlag == (boolean)FALSE )
        {
            if( b_SendPosRes == (boolean)TRUE )
            {
                if( Dcm_Dsp_SID19_Sub1A_bGetDTCEnded == (boolean)TRUE )
                {
                    if( Dcm_Dsp_Main_stMsgContext.resDataLen <= ( DCM_DSP_SID19_SUB1A_DTCSAM_LEN + DCM_DSP_SID19_SUB1A_DTCEDRN_LEN ) )
                    {
                        Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB1A_RES_DATA_MIN_LEN;
                    }
                    /* If reading of all RecordNumbers is completed before updatePage, correct the total length of data to the current data length and send it all at once */
                    Dcm_Dsp_SID19_Sub1A_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    Dcm_Dsp_SID19_Sub1A_u2RemainingResDataNumforPB = (uint16)0U;
                }
                Dcm_Dsp_SID19_Sub1A_StartPage();
            }
            else
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            }
        }
        else
        {
            Dcm_Dsp_SID19_Sub1A_AdjustDataLenForPage();
            if( Dcm_Dsp_Main_stMsgContext.resDataLen != (Dcm_MsgLenType)0U )
            {
                Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
            }
        }
    }

    return u1_RetVal;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON */

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
    uint8           u1_ProtocolGroup;
    Std_ReturnType  u1_RetVal;
    boolean         b_OutputOnlyOBDRecNum;

    u1_RetVal = E_NOT_OK;

    u2_ConnectionId = ( uint16 )0x0000U;
    (void)Dcm_GetActiveProtocol( NULL_PTR, &u2_ConnectionId, NULL_PTR );
    u1_ProtocolGroup = Dcm_Dsl_GetActiveProtocolGroup( u2_ConnectionId );

    if( u1_ProtocolGroup == DCM_DSL_UDS_PROTOCOL )
    {
        if( ( u1DTCRecNum >= DCM_DSP_SID19_SUB1A_DTCEDRN_NUM01 ) && ( u1DTCRecNum <= DCM_DSP_SID19_SUB1A_DTCEDRN_NUMFD ) )
        {
            u1_RetVal = E_OK;
        }
    }
    else /* u1_ProtocolGroup eqal DCM_DSL_OBD_PROTOCOL */
    {
        b_OutputOnlyOBDRecNum = Dcm_Dsp_SID19_Sub1A_bOutputOnlyEmiOBDRecNumToOBDClient;
        if( b_OutputOnlyOBDRecNum == (boolean)TRUE )
        {
            if( ( u1DTCRecNum >= DCM_DSP_SID19_SUB1A_DTCEDRN_NUM90 ) && ( u1DTCRecNum <= DCM_DSP_SID19_SUB1A_DTCEDRN_NUM9F ) )
            {
                u1_RetVal = E_OK;
            }
        }
        else
        {
            if( ( u1DTCRecNum >= DCM_DSP_SID19_SUB1A_DTCEDRN_NUM01 ) && ( u1DTCRecNum <= DCM_DSP_SID19_SUB1A_DTCEDRN_NUMFD ) )
            {
                u1_RetVal = E_OK;
            }
        }
    }
    return u1_RetVal;
}

#if ( DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_ChkAndSetEDRN                        */
/* Description   | Check the response buffer free space and set EDRN to the */
/*               | response buffer                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          : Check OK                                 */
/*               | E_NOT_OK      : Check NG                                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub1A_ChkAndSetEDRN
(
    void
)
{
    Std_ReturnType      u1_RetVal;

    u1_RetVal = E_OK;

    if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= (DCM_DSP_SID19_SUB1A_DTCEDRN_LEN + DCM_DSP_SID19_SUB1A_DTCASR_LEN) )   /* no wrap around */
    {
        if( Dcm_Dsp_SID19_Sub1A_u2RemainingResDataNumforPB != (uint16)0U )
        {
            /* Set Extended Data Record Number */
            Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB1A_REQ_OFS_DTCEDRN];
            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB1A_DTCSAM_LEN + DCM_DSP_SID19_SUB1A_DTCEDRN_LEN;
        }
    }
    else
    {
        u1_RetVal = E_NOT_OK;
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub1A_AdjustDataLenForPage                 */
/* Description   | Adjust data length for page                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_AdjustDataLenForPage
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

    if( Dcm_Dsp_SID19_Sub1A_bGetDTCEnded == (boolean)TRUE )
    {
        if( Dcm_Dsp_SID19_Sub1A_u2RemainingResDataNumforPB != (uint16)0U )
        {
            u4_RemainingResDataLenforPB = (uint32)((uint32)Dcm_Dsp_SID19_Sub1A_u2RemainingResDataNumforPB * (uint32)DCM_DSP_SID19_SUB1A_DTCASR_LEN);    /* no wrap around */
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
                if( u4_RemainingPaddingLen >= (uint32)DCM_DSP_SID19_SUB1A_DTCASR_LEN )
                {
                    for( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)DCM_DSP_SID19_SUB1A_DTCASR_LEN; u1_Cnt++ )
                    {
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)0;
                        u4_ResDataPos = u4_ResDataPos + (uint32)1U;  /* no wrap around */
                    }
                    u4_RemainingPaddingLen = u4_RemainingPaddingLen - (uint32)DCM_DSP_SID19_SUB1A_DTCASR_LEN;   /* no wrap around */
                    Dcm_Dsp_SID19_Sub1A_u2RemainingResDataNumforPB = Dcm_Dsp_SID19_Sub1A_u2RemainingResDataNumforPB - (uint16)1U;    /* no wrap around */
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
/* Function Name | Dcm_Dsp_SID19_Sub1A_StartPage                            */
/* Description   | Start paged processing of SID 19 SF 1A                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub1A_StartPage
(
    void
)
{
    Dcm_MsgContextType  st_MsgContext;
    uint16              u2_PbidSid;

    u2_PbidSid = Dcm_P_u2Pbid_Sid19_Sub1A;

    st_MsgContext.reqData                           = NULL_PTR;
    st_MsgContext.reqDataLen                        = (Dcm_MsgLenType)0U;
    st_MsgContext.resData                           = NULL_PTR;
    st_MsgContext.msgAddInfo.reqType                = (uint8)0U;
    st_MsgContext.msgAddInfo.suppressPosResponse    = STD_OFF;
    st_MsgContext.resMaxDataLen                     = (Dcm_MsgLenType)0U;
    st_MsgContext.idContext                         = (Dcm_IdContextType)0U;
    st_MsgContext.dcmRxPduId                        = (PduIdType)0U;
    st_MsgContext.resDataLen                        = Dcm_Dsp_SID19_Sub1A_u4ResDataLenforPB;

    Dcm_Dsp_MsgMaker_StartPagedProcessing( &st_MsgContext, u2_PbidSid );

    return ;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB1A_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID19_SUB1A == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-2-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
