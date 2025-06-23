/* Dcm_Dsp_SID14_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID14/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID14.h>
#if ( DCM_SUPPORT_SID14 == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID14_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID14_ReqDataLength             ((uint8)3U)
#define     DCM_DSP_SID14_ShiftDTCHigh              (16U)
#define     DCM_DSP_SID14_ShiftDTCMiddle            (8U)
#define     DCM_DSP_SID14_DTCHigh                   (0U)
#define     DCM_DSP_SID14_DTCMiddle                 (1U)
#define     DCM_DSP_SID14_DTCLow                    (2U)
#define     DCM_DSP_SID14_MEMSEL_INIT_VALUE         ((uint8)0x00U)

#if ( DCM_SID14_MEMORYSELECTION_USE == STD_ON )
#define     DCM_DSP_SID14_REQ_OFF_MEMSEL            ((uint8)3U)
#define     DCM_DSP_SID14_REQ_MEMSEL_LEN            ((uint8)1U)
#define     DCM_DSP_SID14_REQ_DATA_AND_MEMSEL_LEN   ((uint32)(DCM_DSP_SID14_ReqDataLength + DCM_DSP_SID14_REQ_MEMSEL_LEN))
#define     DCM_DSP_SID14_MEMSEL_BASE_VAL           ((uint16)0x0100U)
#endif /* DCM_SID14_MEMORYSELECTION_USE == STD_ON */

#if ( DCM_OBD_DTC_ALL_CLEAR_BY_FFFF33 == STD_ON )
#define     DCM_DSP_SID14_DTC_VAL_FFFF33            ((uint32)0x00FFFF33U)
#define     DCM_DSP_SID14_DTC_VAL_FFFFFF            ((uint32)0x00FFFFFFU)
#endif /* DCM_OBD_DTC_ALL_CLEAR_BY_FFFF33 == STD_ON */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID14_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID14_CancelProc
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID14_ClearDTC
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID14_CheckClearDTC
(
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA )                      ptRespFlag,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID14_SetGroupOfDTC
(
    const uint32 u4GroupOfDTC
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


static VAR(uint32, DCM_VAR_NO_INIT)             Dcm_Dsp_SID14_u4GroupOfDTC;
static VAR(uint16, DCM_VAR_NO_INIT)             Dcm_Dsp_SID14_u2DTCOrigin;

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
/* Function Name | Dcm_SID14                                                */
/* Description   | Request processing of SID 14                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID14                 /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType      u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID14_InitialProc( pMsgContext );
        /* Return value is a check-free */
    }
    else
    {
        Dcm_Dsp_SID14_CancelProc();
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID14_Cbk                                        */
/* Description   | Call Back Function to Continue SID14 Processing          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID14_Cbk                   /* MISRA DEVIATION */
(
    const uint8 u1EventId                                /* MISRA DEVIATION */
)
{
    Std_ReturnType      u1_RetVal;

    u1_RetVal = Dcm_Dsp_SID14_ClearDTC();
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        /* Final Response Has Been Transmitted. and Proc End */
        /* No process */
    }
    else
    {
        /* u1_RetVal == DCM_E_PENDING                                   */
        /* Proc End and Retry in the next period                        */
        /* No process */
    }

    return ;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID14_InitialProc                                */
/* Description   | Initial process of SID 14 request                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_SID14_MEMORYSELECTION_USE == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID14_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    uint32                          u4_GroupOfDTC;
    uint16                          u2_PduId;
    uint8                           u1_MemorySelectionValue;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkClear;
    Std_ReturnType                  u1_RetChkAccpt;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    boolean                         b_SendNegResFlag;
    boolean                         b_MemorySelectionUse;

    u1_RetVal           = E_OK;
    b_SendNegResFlag    = (boolean)FALSE;
    u1_NegResCode       = DCM_E_GENERALREJECT;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE                                  */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID14_u4GroupOfDTC = (uint32)0U;
    Dcm_Dsp_SID14_u2DTCOrigin = (uint16)DEM_DTC_ORIGIN_PRIMARY_MEMORY;

    if(( ptMsgContext->reqDataLen == (Dcm_MsgLenType)DCM_DSP_SID14_ReqDataLength ) ||
       ( ptMsgContext->reqDataLen == (Dcm_MsgLenType)DCM_DSP_SID14_REQ_DATA_AND_MEMSEL_LEN ))
    {
        u4_GroupOfDTC = (((uint32)ptMsgContext->reqData[DCM_DSP_SID14_DTCHigh])   << DCM_DSP_SID14_ShiftDTCHigh   ) |
                        (((uint32)ptMsgContext->reqData[DCM_DSP_SID14_DTCMiddle]) << DCM_DSP_SID14_ShiftDTCMiddle ) |
                        ( (uint32)ptMsgContext->reqData[DCM_DSP_SID14_DTCLow]);
        Dcm_Dsp_SID14_SetGroupOfDTC( u4_GroupOfDTC );

        u2_PduId = ptMsgContext->dcmRxPduId;
        b_MemorySelectionUse = (boolean)FALSE;
        u1_MemorySelectionValue = DCM_DSP_SID14_MEMSEL_INIT_VALUE;

        if( ptMsgContext->reqDataLen == (Dcm_MsgLenType)DCM_DSP_SID14_REQ_DATA_AND_MEMSEL_LEN )
        {
            b_MemorySelectionUse = (boolean)TRUE;
            u1_MemorySelectionValue = ptMsgContext->reqData[DCM_DSP_SID14_REQ_OFF_MEMSEL];
            Dcm_Dsp_SID14_u2DTCOrigin = (uint16)DCM_DSP_SID14_MEMSEL_BASE_VAL + (uint16)u1_MemorySelectionValue;
        }

        u1_RetChkAccpt = Dcm_Dsp_SID14_CheckTheClearDTCRequestIsAcceptable( u2_PduId, u4_GroupOfDTC, b_MemorySelectionUse, u1_MemorySelectionValue, &u1_NegResCode );
        if( u1_RetChkAccpt == (Std_ReturnType)E_OK )
        {
            u1_RetChkClear = Dcm_Dsp_SID14_CheckClearDTC( &b_SendNegResFlag, &u1_NegResCode );

            if( u1_RetChkClear == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID14_ClearDTC();
                /* Return value is a check-free */
            }
        }
        else if( u1_RetChkAccpt == (Std_ReturnType)E_NOT_OK )
        {
            b_SendNegResFlag    = (boolean)TRUE;
        }
        else
        {
            u1_NegResCode       = DCM_E_GENERALREJECT;
            b_SendNegResFlag    = (boolean)TRUE;
        }
    }
    else
    {
        /* Send Negative Response NRC:0x13                                  */
        u1_NegResCode       = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag    = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }

    return u1_RetVal;
}
#endif /* DCM_SID14_MEMORYSELECTION_USE == STD_ON */
#if ( DCM_SID14_MEMORYSELECTION_USE == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID14_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    uint32                          u4_GroupOfDTC;
    uint16                          u2_PduId;
    uint8                           u1_MemorySelectionValue;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkClear;
    Std_ReturnType                  u1_RetChkAccpt;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    boolean                         b_SendNegResFlag;
    boolean                         b_MemorySelectionUse;

    u1_RetVal           = E_OK;
    b_SendNegResFlag    = (boolean)FALSE;
    u1_NegResCode       = DCM_E_GENERALREJECT;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE                                  */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID14_u4GroupOfDTC = (uint32)0U;
    Dcm_Dsp_SID14_u2DTCOrigin = (uint16)DEM_DTC_ORIGIN_PRIMARY_MEMORY;

    if( ptMsgContext->reqDataLen == (Dcm_MsgLenType)DCM_DSP_SID14_ReqDataLength )
    {
        u4_GroupOfDTC = (((uint32)ptMsgContext->reqData[DCM_DSP_SID14_DTCHigh])   << DCM_DSP_SID14_ShiftDTCHigh   ) |
                        (((uint32)ptMsgContext->reqData[DCM_DSP_SID14_DTCMiddle]) << DCM_DSP_SID14_ShiftDTCMiddle ) |
                        ( (uint32)ptMsgContext->reqData[DCM_DSP_SID14_DTCLow]);
        Dcm_Dsp_SID14_SetGroupOfDTC( u4_GroupOfDTC );

        u2_PduId = ptMsgContext->dcmRxPduId;
        b_MemorySelectionUse = (boolean)FALSE;
        u1_MemorySelectionValue = DCM_DSP_SID14_MEMSEL_INIT_VALUE;

        u1_RetChkAccpt = Dcm_Dsp_SID14_CheckTheClearDTCRequestIsAcceptable( u2_PduId, u4_GroupOfDTC, b_MemorySelectionUse, u1_MemorySelectionValue, &u1_NegResCode );
        if( u1_RetChkAccpt == (Std_ReturnType)E_OK )
        {
            u1_RetChkClear = Dcm_Dsp_SID14_CheckClearDTC( &b_SendNegResFlag, &u1_NegResCode );

            if( u1_RetChkClear == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID14_ClearDTC();
                /* Return value is a check-free */
            }
        }
        else if( u1_RetChkAccpt == (Std_ReturnType)E_NOT_OK )
        {
            b_SendNegResFlag    = (boolean)TRUE;
        }
        else
        {
            u1_NegResCode       = DCM_E_GENERALREJECT;
            b_SendNegResFlag    = (boolean)TRUE;
        }
    }
    else
    {
        /* Send Negative Response NRC:0x13                                  */
        u1_NegResCode       = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag    = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }

    return u1_RetVal;
}
#endif /* DCM_SID14_MEMORYSELECTION_USE == STD_OFF */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID14_CancelProc                                 */
/* Description   | Cancel process of SID 14 request                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID14_CancelProc
(
    void
)
{

    /* Cancel Clear DTC */
    (void)Dem_DcmClearDTC( DEM_DTC_CANCEL_CLEAR_DTC, DEM_DTC_FORMAT_UDS, (Dem_DTCOriginType)Dcm_Dsp_SID14_u2DTCOrigin );    /* no return check required */
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID14_CLEARDTC, (boolean)FALSE );                                      /* no return check required */

    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE                                   */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID14_ClearDTC                                   */
/* Description   | Clear DTC Request to DEM                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID14_ClearDTC
(
    void
)
{
    Dem_ReturnClearDTCType  u1_RetClearDTC;
    Std_ReturnType          u1_RetVal;

    u1_RetVal      = E_OK;

    u1_RetClearDTC = Dem_DcmClearDTC( Dcm_Dsp_SID14_u4GroupOfDTC, DEM_DTC_FORMAT_UDS, (Dem_DTCOriginType)Dcm_Dsp_SID14_u2DTCOrigin );
    switch( u1_RetClearDTC )
    {
        case DEM_CLEAR_OK:
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            break;
        case DEM_CLEAR_WRONG_DTC:
            /* NRC:0x31                                                     */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            break;
        case DEM_CLEAR_FAILED:
            /* NRC:0x22                                                     */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
            break;
        case DEM_CLEAR_PENDING:
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID14_CLEARDTC );                                /* no return check required */
            u1_RetVal = DCM_E_PENDING;
            break;
        case DEM_CLEAR_BUSY:
            /* NRC:0x22                                                     */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
            break;
        case DEM_CLEAR_MEMORY_ERROR:
            /* NRC:0x72                                                     */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE );
            break;
        default:
            /* No process                                                   */
            break;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID14_CheckClearDTC                              */
/* Description   | Check Before Clear DTC Request to DEM                    */
/* Preconditions | None                                                     */
/* Parameters    | [OUT]  ptRespFlag*   : Response Request Flag             */
/*               | [OUT]  ptErrorCode   : Negative Response Code            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Check OK                           */
/*               |   E_NOT_OK          : Check NG                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID14_CheckClearDTC
(
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA )                      ptRespFlag,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Dem_ReturnClearDTCType  u1_RetChkClear;
    Std_ReturnType          u1_RetSwc;
    Std_ReturnType          u1_RetVal;

    u1_RetVal       = E_NOT_OK;
    *ptRespFlag     = (boolean)FALSE;

    u1_RetChkClear = Dem_DcmCheckClearParameter( Dcm_Dsp_SID14_u4GroupOfDTC, DEM_DTC_FORMAT_UDS, (Dem_DTCOriginType)Dcm_Dsp_SID14_u2DTCOrigin );
    switch( u1_RetChkClear )
    {
        case DEM_CLEAR_OK:
            u1_RetSwc = Dcm_Dsp_SID14_CheckSWC( Dcm_Dsp_SID14_u4GroupOfDTC, ptErrorCode );
            if( u1_RetSwc == (Std_ReturnType)E_OK )
            {
                u1_RetVal = E_OK;
            }
            else
            {
                *ptRespFlag = (boolean)TRUE;
                /* ptErrorCode have been already set by Dcm_Dsp_SID14_CheckSWC function. */
            }
            break;
        case DEM_CLEAR_WRONG_DTCORIGIN:
            /* No break; fall through to the DEM_CLEAR_WRONG_DTC case */
        case DEM_CLEAR_WRONG_DTC:
            /* NRC:0x31                                                     */
            *ptRespFlag     = (boolean)TRUE;
            *ptErrorCode    = (Dcm_NegativeResponseCodeType)DCM_E_REQUESTOUTOFRANGE;
            break;
        case DEM_CLEAR_FAILED:
            /* NRC:0x22                                                     */
            *ptRespFlag     = (boolean)TRUE;
            *ptErrorCode    = (Dcm_NegativeResponseCodeType)DCM_E_CONDITIONSNOTCORRECT;
            break;
        default:
            /* No process                                                   */
            break;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID14_SetGroupOfDTC                              */
/* Description   | Set GroupOfDTC Data                                      */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u4GroupOfDTC : GroupOfDTC                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if( DCM_OBD_DTC_ALL_CLEAR_BY_FFFF33 == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID14_SetGroupOfDTC
(
    const uint32 u4GroupOfDTC
)
{
    uint32      u4_GroupOfDTC;

    u4_GroupOfDTC = u4GroupOfDTC;

    /* Replace FFFF33 to FFFFFF */
    if( u4GroupOfDTC == DCM_DSP_SID14_DTC_VAL_FFFF33 )
    {
        u4_GroupOfDTC = DCM_DSP_SID14_DTC_VAL_FFFFFF;
    }

    Dcm_Dsp_SID14_u4GroupOfDTC = u4_GroupOfDTC;

    return;
}
#endif /* DCM_OBD_DTC_ALL_CLEAR_BY_FFFF33 == STD_ON */
#if( DCM_OBD_DTC_ALL_CLEAR_BY_FFFF33 == STD_OFF )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID14_SetGroupOfDTC
(
    const uint32 u4GroupOfDTC
)
{
    Dcm_Dsp_SID14_u4GroupOfDTC = u4GroupOfDTC;

    return;
}
#endif /* DCM_OBD_DTC_ALL_CLEAR_BY_FFFF33 == STD_OFF */


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID14 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
