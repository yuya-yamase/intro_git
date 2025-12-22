/* Dcm_Dsp_SID19_Sub0A_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub0A/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub0A.h>
#if ( DCM_SUPPORT_SID19_SUB0A == STD_ON )
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID19_SUB0A_SHFT_DTC_HI                 (16U)
#define DCM_DSP_SID19_SUB0A_SHFT_DTC_MI                 (8U)
#define DCM_DSP_SID19_SUB0A_RES_OFS_DTC_HI              (0U)
#define DCM_DSP_SID19_SUB0A_RES_OFS_DTC_MI              (1U)
#define DCM_DSP_SID19_SUB0A_RES_OFS_DTC_LO              (2U)
#define DCM_DSP_SID19_SUB0A_RES_OFS_SODTC               (3U)
#define DCM_DSP_SID19_SUB0A_DTCSM_00                    ((uint8)0x00U)
#define DCM_DSP_SID19_SUB0A_REQ_DATA_LEN                (0U)
#define DCM_DSP_SID19_SUB0A_DTC_LEN                     (3U)
#define DCM_DSP_SID19_SUB0A_SODTC_LEN                   (1U)
#define DCM_DSP_SID19_SUB0A_DTCSM_LEN                   (1U)
#define DCM_DSP_SID19_SUB0A_DTCASR_LEN                  (DCM_DSP_SID19_SUB0A_DTC_LEN+DCM_DSP_SID19_SUB0A_SODTC_LEN)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub0A_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub0A_CancelProc
( void );
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub0A_GetDTC
( void );
#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub0A_GetSizeOfDTC
( void );
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub0A_AdjustDataLenForPage
( void );
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub0A_StartPage
( void );
#endif /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON )
static VAR(uint32, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub0A_u4ResDataLenforPB;
static VAR(uint16, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub0A_u2RemainingResDataNumforPB;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub0A_bUpdatePageFlag;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub0A_bGetDTCEnded;
#endif /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON */

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
/* Function Name | Dcm_SID19_Sub0A                                          */
/* Description   | Report DTC By Status Mask                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Status of the current operation    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                : Result OK                          */
/*               | DCM_E_PENDING       : Result Pending                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID19_Sub0A /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType          u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub0A_InitialProc( pMsgContext );
        /* This Return Value is check-free */
    }
    else
    {
        Dcm_Dsp_SID19_Sub0A_CancelProc();
    }

    return u1_RetVal;
}

#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub0A_GetSizeOfDTCCbk                      */
/* Description   | Call Back Function to Continue SID19_Sub0A Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event Id                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub0A_GetSizeOfDTCCbk
(
    const uint8 u1EventId
)
{
    Std_ReturnType  u1_RetGetSizeOfDTC;

    u1_RetGetSizeOfDTC = Dcm_Dsp_SID19_Sub0A_GetSizeOfDTC();
    if( u1_RetGetSizeOfDTC == (Std_ReturnType)E_OK )
    {
        (void)Dcm_Dsp_SID19_Sub0A_GetDTC();         /* no return check required */
    }

    return;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub0A_GetDTCCbk                            */
/* Description   | Call Back Function to Continue SID19_Sub0A Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event Id                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub0A_GetDTCCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId                                /* MISRA DEVIATION */
)
{
    (void)Dcm_Dsp_SID19_Sub0A_GetDTC();                  /* no return check required */

    return ;
}

#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub0A_UpdatePage                           */
/* Description   | UpdatePage of SID 19 SF 0A                               */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptResData       : Response Data                    */
/*               | [IN]  u4ResMaxDataLen : Buffer Size of Response Data     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub0A_UpdatePage
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
        Dcm_Dsp_SID19_Sub0A_bUpdatePageFlag = (boolean)TRUE;
        Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
    }
    else
    {
        Dcm_Dsp_Main_stMsgContext.resData          = ptResData;
        Dcm_Dsp_Main_stMsgContext.resMaxDataLen    = u4ResMaxDataLen;
        Dcm_Dsp_Main_stMsgContext.resDataLen       = (uint32)0U;

        u1_RetGetDTC = Dcm_Dsp_SID19_Sub0A_GetDTC();
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
/* Function Name | Dcm_Dsp_SID19_Sub0A_CancelPage                           */
/* Description   | CancelPage of SID 19 SF 0A                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub0A_CancelPage
(void)
{
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB0A_GETDTC, (boolean)FALSE );
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub0A_InitialProc                          */
/* Description   | Initial process of SID19_Sub0A                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                : Result OK                          */
/*               | DCM_E_PENDING       : Result Pending                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub0A_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Dem_ReturnSetFilterType         u1_RetSetFilter;
    Std_ReturnType                  u1_RetDDGDSAM;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_SendNegResFlag;
    boolean                         b_SendPosResFlag;


    u1_RetVal           = E_OK;
    b_SendPosResFlag    = (boolean)FALSE;
    b_SendNegResFlag    = (boolean)FALSE;
    u1_DTCStatusMask    = DCM_DSP_SID19_SUB0A_DTCSM_00;
    u1_NegResCode       = DCM_E_GENERALREJECT;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_REQ_DATA_LEN )
    {
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_DTCSM_LEN )
        {
            u1_RetDDGDSAM = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask, DEM_DTC_ORIGIN_PRIMARY_MEMORY );
            if( u1_RetDDGDSAM == (Std_ReturnType)E_OK )
            {
                /* Write DTC Status Availability Mask to Response Buffer    */
                Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ] = u1_DTCStatusMask;
                Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_DTCSM_LEN;  /* no wrap around */

                if( u1_DTCStatusMask != DCM_DSP_SID19_SUB0A_DTCSM_00)
                {
                    u1_RetSetFilter = Dem_DcmSetDTCFilter( DCM_DSP_SID19_SUB0A_DTCSM_00,
                                                           DEM_DTC_KIND_ALL_DTCS,
                                                           DEM_DTC_FORMAT_UDS,
                                                           DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                           (boolean)FALSE,
                                                           DEM_SEVERITY_NO_SEVERITY,
                                                           (boolean)FALSE
                                                           );
                    switch( u1_RetSetFilter )
                    {
                        case DEM_FILTER_ACCEPTED:
                            u1_RetVal = Dcm_Dsp_SID19_Sub0A_GetDTC();
                            /* This Return Value is check-free */
                            break;
                        case DEM_WRONG_CONDITION :
                            /*   Status Busy NG    -> 0x21                              */
                            u1_NegResCode    = DCM_E_BUSYREPEATREQUEST;
                            b_SendNegResFlag = (boolean)TRUE;
                            break;
                        case DEM_WRONG_FILTER :
                            /* No break; fall through to the default case */
                        default:
                            /*   General Reject    -> 0x10                              */
                            /* default value of u1_NegResCode is DCM_E_GENERALREJECT    */
                            b_SendNegResFlag = (boolean)TRUE;
                            break;
                    }
                }
                else
                {
                    /* DTCStatusAvailabilityMask Is Equal To Zero           */
                    b_SendPosResFlag = (boolean)TRUE;
                }
            }
            else
            {
                /*   General Reject    -> 0x10                              */
                /* default value of u1_NegResCode is DCM_E_GENERALREJECT    */
                b_SendNegResFlag = (boolean)TRUE;
            }
        }
        else
        {
            /*   Response Length Too Long    -> 0x14                            */
            u1_NegResCode = DCM_E_RESPONSETOOLONG;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        /*   Request Length Check NG    -> 0x13                             */
        u1_NegResCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }
    else
    {
        if( b_SendPosResFlag == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
    }

    return u1_RetVal;

}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub0A_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Dem_ReturnSetFilterType         u1_RetSetFilter;
    Std_ReturnType                  u1_RetDDGDSAM;
    Std_ReturnType                  u1_RetGetSizeOfDTC;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_SendNegResFlag;
    boolean                         b_SendPosResFlag;

    u1_RetVal           = E_OK;
    b_SendPosResFlag    = (boolean)FALSE;
    b_SendNegResFlag    = (boolean)FALSE;
    u1_DTCStatusMask    = DCM_DSP_SID19_SUB0A_DTCSM_00;
    u1_NegResCode       = DCM_E_GENERALREJECT;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID19_Sub0A_bGetDTCEnded =  (boolean)FALSE;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_REQ_DATA_LEN )
    {
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_DTCSM_LEN )
        {
            u1_RetDDGDSAM = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask, DEM_DTC_ORIGIN_PRIMARY_MEMORY );
            if( u1_RetDDGDSAM == (Std_ReturnType)E_OK )
            {
                /* Write DTC Status Availability Mask to Response Buffer    */
                Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ] = u1_DTCStatusMask;
                Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_DTCSM_LEN;  /* no wrap around */

                if( u1_DTCStatusMask != DCM_DSP_SID19_SUB0A_DTCSM_00)
                {
                    u1_RetSetFilter = Dem_DcmSetDTCFilter( DCM_DSP_SID19_SUB0A_DTCSM_00,
                                                           DEM_DTC_KIND_ALL_DTCS,
                                                           DEM_DTC_FORMAT_UDS,
                                                           DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                           (boolean)FALSE,
                                                           DEM_SEVERITY_NO_SEVERITY,
                                                           (boolean)FALSE
                                                           );
                    switch( u1_RetSetFilter )
                    {
                        case DEM_FILTER_ACCEPTED:
                            u1_RetGetSizeOfDTC = Dcm_Dsp_SID19_Sub0A_GetSizeOfDTC();
                            switch( u1_RetGetSizeOfDTC )
                            {
                                case E_OK:
                                    u1_RetVal = Dcm_Dsp_SID19_Sub0A_GetDTC();
                                    /* This Return Value is check-free */
                                    break;
                                case DCM_E_PENDING:
                                    u1_RetVal = DCM_E_PENDING;
                                    break;
                                default:
                                    /* no process */
                                    break;
                            }
                            break;
                        case DEM_WRONG_CONDITION :
                            /*   Status Busy NG    -> 0x21                              */
                            u1_NegResCode    = DCM_E_BUSYREPEATREQUEST;
                            b_SendNegResFlag = (boolean)TRUE;
                            break;
                        case DEM_WRONG_FILTER :
                            /* No break; fall through to the default case */
                        default:
                            /*   General Reject    -> 0x10                              */
                            /* default value of u1_NegResCode is DCM_E_GENERALREJECT    */
                            b_SendNegResFlag = (boolean)TRUE;
                            break;
                    }
                }
                else
                {
                    /* DTCStatusAvailabilityMask Is Equal To Zero           */
                    b_SendPosResFlag = (boolean)TRUE;
                }
            }
            else
            {
                /*   General Reject    -> 0x10                              */
                /* default value of u1_NegResCode is DCM_E_GENERALREJECT    */
                b_SendNegResFlag = (boolean)TRUE;
            }
        }
        else
        {
            /*   Response Length Too Long    -> 0x14                    */
            u1_NegResCode    = DCM_E_RESPONSETOOLONG;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        /*   Request Length Check NG    -> 0x13                     */
        u1_NegResCode    = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }
    else
    {
        if( b_SendPosResFlag == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
    }

    return u1_RetVal;

}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub0A_CancelProc                           */
/* Description   | Receive Cancel request and Set Cancel Flag               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_OFF )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub0A_CancelProc
( void )
{

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB0A_GETDTC, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub0A_CancelProc
( void )
{
    Dcm_Main_EvtDistr_RetType   u1_RetDelGetSizeofDTC;

    u1_RetDelGetSizeofDTC = Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB0A_GETSIZE, (boolean)FALSE );
    if( u1_RetDelGetSizeofDTC != DCM_MAIN_EVTDISTR_E_OK )
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB0A_GETDTC, (boolean)FALSE ); /* no return check required */
    }
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub0A_GetSizeOfDTC                         */
/* Description   | Get Number of DTCs and calculate response data length    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |    E_OK             : Processing normal                  */
/*               |    DCM_E_PENDING    : Result Pending                     */
/*               |    E_NOT_OK         : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub0A_GetSizeOfDTC
(
    void
)
{
    uint16                                  u2_NumOfDTC;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    Dem_ReturnGetNumberOfFilteredDTCType    u1_RetNumOfFilDTC;
    Std_ReturnType                          u1_RetVal;

    u1_RetVal     = E_OK;
    u1_NegResCode = DCM_E_GENERALREJECT;

    u1_RetNumOfFilDTC = Dem_DcmGetNumberOfFilteredDTC( &u2_NumOfDTC );
    switch( u1_RetNumOfFilDTC )
    {
        case DEM_NUMBER_OK:
            Dcm_Dsp_SID19_Sub0A_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen + (uint32)((uint32)u2_NumOfDTC * (uint32)DCM_DSP_SID19_SUB0A_DTCASR_LEN); /* no wrap around */
            Dcm_Dsp_SID19_Sub0A_u2RemainingResDataNumforPB  = u2_NumOfDTC;
            Dcm_Dsp_SID19_Sub0A_bUpdatePageFlag             = (boolean)FALSE;
            break;
        case DEM_NUMBER_PENDING:
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB0A_GETSIZE );   /* no return check required */
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
#endif  /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub0A_GetDTC                               */
/* Description   | Get DTC and Edit Response or Register Event              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                : Result OK                          */
/*               | DCM_E_PENDING       : Result Pending                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub0A_GetDTC
( void )
{
    uint32                                  u4_DTC;
    Dem_UdsStatusByteType                   u1_DtcStatus;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    Dem_ReturnGetNextFilteredElementType    u1_RetNextDtc;
    Std_ReturnType                          u1_RetVal;
    boolean                                 b_LoopEnd;
    boolean                                 b_SendPosResFlag;

    u1_RetVal        = E_OK;
    b_SendPosResFlag = (boolean)FALSE;
    u4_DTC           = (uint32)0U;
    u1_DtcStatus     = (Dem_UdsStatusByteType)0U;
    b_LoopEnd        = (boolean)FALSE;
    u1_NegResCode    = DCM_E_GENERALREJECT;

    while( b_LoopEnd == (boolean)FALSE )
    {
        u1_RetNextDtc = Dem_DcmGetNextFilteredDTC( &u4_DTC, &u1_DtcStatus );
        switch( u1_RetNextDtc )
        {
            case DEM_FILTERED_OK :
                if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= DCM_DSP_SID19_SUB0A_DTCASR_LEN )    /* no wrap around */
                {
                    /* DTC Data Set */
                    /* Set u4_DTC(bit16-bit23) to u1_DTCInfo[0]                 */
                    Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB0A_SHFT_DTC_HI);
                    /* Set u4_DTC(bit08-bit15) to u1_DTCInfo[1]                 */
                    Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_RES_OFS_DTC_MI ] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB0A_SHFT_DTC_MI); /* no wrap around */
                    /* Set u4_DTC(bit00-bit07) to u1_DTCInfo[2]                 */
                    Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_RES_OFS_DTC_LO ] = (uint8)(u4_DTC);  /* no wrap around */
                    /* Set u1_DtcStatus        to u1_DTCInfo[3]                 */
                    Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_RES_OFS_SODTC ] = u1_DtcStatus; /* no wrap around */
                    /* DTC Data Length Plus */
                    Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_DTCASR_LEN;  /* no wrap around */
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
                /*   General Reject    -> 0x10                              */
                /* default value of u1_NegResCode is DCM_E_GENERALREJECT    */
                break;
        }
    }/* while End */

    if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB0A_GETDTC ); /* no return check required */
    }
    else
    {
        if( b_SendPosResFlag == (boolean)TRUE )
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
#endif  /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub0A_GetDTC
( void )
{
    uint32                                  u4_DTC;
    Dem_UdsStatusByteType                   u1_DtcStatus;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    Dem_ReturnGetNextFilteredElementType    u1_RetNextDtc;
    Std_ReturnType                          u1_RetVal;
    boolean                                 b_LoopEnd;
    boolean                                 b_SendPosResFlag;

    u1_RetVal        = E_OK;
    b_SendPosResFlag = (boolean)FALSE;
    u4_DTC           = (uint32)0U;
    u1_DtcStatus     = (Dem_UdsStatusByteType)0U;
    b_LoopEnd        = (boolean)FALSE;
    u1_NegResCode    = DCM_E_GENERALREJECT;

    if( Dcm_Dsp_SID19_Sub0A_bGetDTCEnded == (boolean)TRUE )
    {
        b_SendPosResFlag    = (boolean)TRUE;
        b_LoopEnd           = (boolean)TRUE;
    }

    while( b_LoopEnd == (boolean)FALSE )
    {
        if( (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen) >= DCM_DSP_SID19_SUB0A_DTCASR_LEN )    /* no wrap around */
        {
            if( Dcm_Dsp_SID19_Sub0A_u2RemainingResDataNumforPB != (uint16)0U )
            {
                u1_RetNextDtc = Dem_DcmGetNextFilteredDTC( &u4_DTC, &u1_DtcStatus );
                switch( u1_RetNextDtc )
                {
                    case DEM_FILTERED_OK :
                        /* DTC Data Set */
                        /* Set u4_DTC(bit16-bit23) to u1_DTCInfo[0]                 */
                        Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB0A_SHFT_DTC_HI);
                        /* Set u4_DTC(bit08-bit15) to u1_DTCInfo[1]                 */
                        Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_RES_OFS_DTC_MI ] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB0A_SHFT_DTC_MI); /* no wrap around */
                        /* Set u4_DTC(bit00-bit07) to u1_DTCInfo[2]                 */
                        Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_RES_OFS_DTC_LO ] = (uint8)(u4_DTC);  /* no wrap around */
                        /* Set u1_DtcStatus        to u1_DTCInfo[3]                 */
                        Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_RES_OFS_SODTC ] = u1_DtcStatus; /* no wrap around */
                        /* DTC Data Length Plus */
                        Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB0A_DTCASR_LEN;  /* no wrap around */
                        Dcm_Dsp_SID19_Sub0A_u2RemainingResDataNumforPB = Dcm_Dsp_SID19_Sub0A_u2RemainingResDataNumforPB - (uint16)1U;

                        break;
                    case DEM_FILTERED_NO_MATCHING_ELEMENT:
                        /* Loop End , Processing completion                         */
                        Dcm_Dsp_SID19_Sub0A_bGetDTCEnded = (boolean)TRUE;
                        b_LoopEnd           = (boolean)TRUE;
                        b_SendPosResFlag    = (boolean)TRUE;
                        break;
                    case DEM_FILTERED_PENDING:
                        /* Loop End , Wait a processing                             */
                        b_LoopEnd = (boolean)TRUE;
                        u1_RetVal = DCM_E_PENDING;
                        break;
                    default:
                        /* Loop End , Illegal Return Value                          */
                        Dcm_Dsp_SID19_Sub0A_bGetDTCEnded = (boolean)TRUE;
                        b_LoopEnd = (boolean)TRUE;
                        break;
                }
            }
            else
            {
                Dcm_Dsp_SID19_Sub0A_bGetDTCEnded = (boolean)TRUE;
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
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB0A_GETDTC ); /* no return check required */
    }
    else
    {
        if( Dcm_Dsp_SID19_Sub0A_bUpdatePageFlag == (boolean)FALSE )
        {
            if( b_SendPosResFlag == (boolean)TRUE )
            {
                if( Dcm_Dsp_SID19_Sub0A_bGetDTCEnded == (boolean)TRUE )
                {
                    /* If reading of all RecordNumbers is completed before updatePage, correct the total length of data to the current data length and send it all at once */
                    Dcm_Dsp_SID19_Sub0A_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    Dcm_Dsp_SID19_Sub0A_u2RemainingResDataNumforPB = (uint16)0U;
                }
                Dcm_Dsp_SID19_Sub0A_StartPage();
            }
            else
            {
                /*   General Reject    -> 0x10                              */
                /* default value of u1_NegResCode is DCM_E_GENERALREJECT    */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
            }
        }
        else
        {
            Dcm_Dsp_SID19_Sub0A_AdjustDataLenForPage();
            if( Dcm_Dsp_Main_stMsgContext.resDataLen != (Dcm_MsgLenType)0U )
            {
                Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
            }
        }
    }

    return u1_RetVal;
}
#endif  /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub0A_AdjustDataLenForPage                 */
/* Description   | Adjust data length for page                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub0A_AdjustDataLenForPage
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

    if( Dcm_Dsp_SID19_Sub0A_bGetDTCEnded == (boolean)TRUE )
    {
        if( Dcm_Dsp_SID19_Sub0A_u2RemainingResDataNumforPB != (uint16)0U )
        {
            u4_RemainingResDataLenforPB = (uint32)((uint32)Dcm_Dsp_SID19_Sub0A_u2RemainingResDataNumforPB * (uint32)DCM_DSP_SID19_SUB0A_DTCASR_LEN);    /* no wrap around */
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
                if( u4_RemainingPaddingLen >= (uint32)DCM_DSP_SID19_SUB0A_DTCASR_LEN )
                {
                    for( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)DCM_DSP_SID19_SUB0A_DTCASR_LEN; u1_Cnt++ )
                    {
                        Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)0;
                        u4_ResDataPos = u4_ResDataPos + (uint32)1U;  /* no wrap around */
                    }
                    u4_RemainingPaddingLen = u4_RemainingPaddingLen - (uint32)DCM_DSP_SID19_SUB0A_DTCASR_LEN;   /* no wrap around */
                    Dcm_Dsp_SID19_Sub0A_u2RemainingResDataNumforPB = Dcm_Dsp_SID19_Sub0A_u2RemainingResDataNumforPB - (uint16)1U;    /* no wrap around */
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
/* Function Name | Dcm_Dsp_SID19_Sub0A_StartPage                            */
/* Description   | Start paged processing of SID 19 SF 0A                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub0A_StartPage
(
    void
)
{
    Dcm_MsgContextType  st_MsgContext;
    uint16              u2_PbidSid;

    u2_PbidSid = Dcm_P_u2Pbid_Sid19_Sub0A;

    st_MsgContext.reqData                           = NULL_PTR;
    st_MsgContext.reqDataLen                        = (Dcm_MsgLenType)0U;
    st_MsgContext.resData                           = NULL_PTR;
    st_MsgContext.msgAddInfo.reqType                = (uint8)0U;
    st_MsgContext.msgAddInfo.suppressPosResponse    = STD_OFF;
    st_MsgContext.resMaxDataLen                     = (Dcm_MsgLenType)0U;
    st_MsgContext.idContext                         = (Dcm_IdContextType)0U;
    st_MsgContext.dcmRxPduId                        = (PduIdType)0U;
    st_MsgContext.resDataLen                        = Dcm_Dsp_SID19_Sub0A_u4ResDataLenforPB;

    Dcm_Dsp_MsgMaker_StartPagedProcessing( &st_MsgContext, u2_PbidSid );

    return ;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID19_SUB0A == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File************************************************************/
