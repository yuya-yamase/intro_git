/* Dcm_Dsp_SIDA4_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SIDA4/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if( DCM_SUPPORT_SIDA4 == STD_ON )
#include <Dcm/Dcm_Dsp_SIDA4.h>
#include "../../Dsp/cfg/Dcm_Dsp_SIDA4_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include "Dcm/Dcm_Main_EvtDistr.h"
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SIDA4_REQ_DATA_LENGTH  ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SIDA4_REQ_CLEAROPT_POS ( (Dcm_MsgLenType)0U )
#define DCM_DSP_SIDA4_RES_DATA_LENGTH  ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SIDA4_RES_CLEAROPT_POS ( (Dcm_MsgLenType)0U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDA4_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SIDA4_CancelProc
(
    void
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDA4_ClearDTC
(
    void
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDA4_ClearMarketabilityOBS
(
    const Dcm_OpStatusType OpStatus
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
/* Function Name | Dcm_SIDA4                                                */
/* Description   | Request processing of SID A4                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   const Dcm_OpStatusType       : OpStatus           */
/*               | [IN]   const Dcm_MsgContextType*    : ptMsgContext       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/*               | DCM_E_PENDING 0x0A                                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SIDA4 /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;
    /* Opstatus check */
    if( OpStatus == DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SIDA4_InitialProc( pMsgContext );
        /* Return value is a check-free */
    }
    else if( OpStatus == DCM_CANCEL )
    {
        Dcm_Dsp_SIDA4_CancelProc();
    }
    else
    {
        /* No process */
    }
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDA4_Cbk                                        */
/* Description   | Call Back Function to Continue SIDA4 Processing          */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   const uint8                  : u1EventId          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SIDA4_Cbk  /* MISRA DEVIATION */
(
    const uint8 u1EventId                 /* MISRA DEVIATION */
)
{
    if( u1EventId == DCM_M_EVTID_SIDA4_CLEARDTC )
    {
        /* Return value ignoring */
        (void)Dcm_Dsp_SIDA4_ClearDTC();
    }
    else if( u1EventId == DCM_M_EVTID_SIDA4_CLEAROBS )
    {
        /* Return value ignoring */
        (void)Dcm_Dsp_SIDA4_ClearMarketabilityOBS( DCM_PENDING );
    }
    else
    {
        /* No process */
    }

    return ;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDA4_InitialProc                                */
/* Description   | Initial process of SID A4 request                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   const Dcm_MsgContextType*    : ptMsgContext       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/*               | DCM_E_PENDING 0x0A                                       */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDA4_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Std_ReturnType               u1_RetVal;
    Std_ReturnType               u1_RetChkStatus;
    Dcm_NegativeResponseCodeType u1_NegResCode;
    uint8                        u1_ClearOpt;
    boolean                      b_supportedFlag;
    boolean                      b_clearFlag;

    u1_RetVal        = E_OK;
    u1_NegResCode    = DCM_E_GENERALREJECT;
    b_supportedFlag  = (boolean)FALSE;
    b_clearFlag      = (boolean)FALSE;

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    /* Data Length Check */
    if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SIDA4_REQ_DATA_LENGTH )
    {
        u1_ClearOpt = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SIDA4_REQ_CLEAROPT_POS];
        /* clearOption Check */
        if( u1_ClearOpt == DCM_DSP_SIDA4_CLEAROPT10 )
        {
            b_supportedFlag  = (boolean)Dcm_Dsp_SIDA4_bClearOption10Used;
        }
        else if( u1_ClearOpt == DCM_DSP_SIDA4_CLEAROPT20 )
        {
            b_supportedFlag  = (boolean)Dcm_Dsp_SIDA4_bClearOption20Used;
        }
        else if( u1_ClearOpt == DCM_DSP_SIDA4_CLEAROPT30 )
        {
            b_supportedFlag  = (boolean)Dcm_Dsp_SIDA4_bClearOption30Used;
        }
        else
        {
            /* No process */
        }

        if( b_supportedFlag  == (boolean)TRUE )
        {
            /* Data Length Check */
            if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SIDA4_REQ_DATA_LENGTH )
            {
                /* Clear DTC/OBS Condition Check */
                u1_RetChkStatus = Dcm_Dsp_SIDA4_CheckSWC( u1_ClearOpt, &u1_NegResCode );
                if( u1_RetChkStatus == (Std_ReturnType)E_OK )
                {
                    b_clearFlag = (boolean)TRUE;
                }
            }
            else
            {
                /* Send Negative Response NRC:0x13 */
                u1_NegResCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
        }
        else
        {
            /* Send Negative Response NRC:0x31 */
            u1_NegResCode = DCM_E_REQUESTOUTOFRANGE;
        }
    }
    else
    {
        /* Send Negative Response NRC:0x13 */
        u1_NegResCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_clearFlag == (boolean)TRUE )
    {
        if( ( u1_ClearOpt == DCM_DSP_SIDA4_CLEAROPT10 )||
            ( u1_ClearOpt == DCM_DSP_SIDA4_CLEAROPT20 ) )
        {
            u1_RetVal = Dcm_Dsp_SIDA4_ClearDTC();
            /* Return value is a check-free */
        }
        else
        {
            u1_RetVal = Dcm_Dsp_SIDA4_ClearMarketabilityOBS( DCM_INITIAL );
            /* Return value is a check-free */
        }
    }
    else
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }


    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDA4_CancelProc                                 */
/* Description   | Receive Cancel request and Set Cancel Flag               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SIDA4_CancelProc
(
    void
)
{
    boolean  b_UserNotifyFlag;
    uint8    u1_ClearOpt;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        u1_ClearOpt = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SIDA4_REQ_CLEAROPT_POS];
        if( ( u1_ClearOpt == DCM_DSP_SIDA4_CLEAROPT10 )||
            ( u1_ClearOpt == DCM_DSP_SIDA4_CLEAROPT20 ) )
        {
            /* Cancel Clear DTC */
            /* Return value ignoring */
            (void)Dem_DcmClearDTC( DEM_DTC_CANCEL_CLEAR_DTC, DEM_DTC_FORMAT_OBD, DEM_DTC_ORIGIN_PRIMARY_MEMORY );
            /* Return value ignoring */
            (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SIDA4_CLEARDTC , (boolean)FALSE );
        }
        else if( u1_ClearOpt == DCM_DSP_SIDA4_CLEAROPT30 )
        {
            /* Cancel Clear OBS */
            /* Return value ignoring */
            (void)Dcm_Dsp_SIDA4_ClearOBS( DCM_CANCEL );
            /* Return value ignoring */
            (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SIDA4_CLEAROBS , (boolean)FALSE );
        }
        else
        {
            /* No process */
        }
        /* Return value ignoring */
        (void)Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    }
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDA4_ClearDTC                                   */
/* Description   | Clear DTC Request to DEM                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/*               | DCM_E_PENDING 0x0A                                       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDA4_ClearDTC
(
    void
)
{
    Dem_ReturnClearDTCType  u1_RetClearDTC;
    Std_ReturnType          u1_RetVal;

    u1_RetVal = E_OK;

    /* DTC Clear */
    u1_RetClearDTC = Dem_DcmClearDTC( DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_FORMAT_OBD, DEM_DTC_ORIGIN_PRIMARY_MEMORY );
    switch( u1_RetClearDTC )
    {
        case DEM_CLEAR_OK:
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SIDA4_RES_CLEAROPT_POS] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SIDA4_REQ_CLEAROPT_POS];
            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SIDA4_RES_DATA_LENGTH;
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            break;
        case DEM_CLEAR_PENDING:
            /* Return value ignoring */
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SIDA4_CLEARDTC );
            /* Return value ignoring */
            (void)Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
            u1_RetVal = DCM_E_PENDING;
            break;
        case DEM_CLEAR_FAILED:
            /* NRC:0x22 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
            break;
        case DEM_CLEAR_BUSY:
            /* NRC:0x22 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
            break;
        case DEM_CLEAR_MEMORY_ERROR:
            /* NRC:0x22 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
            break;
        default:
            /* No process */
            break;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDA4_ClearMarketabilityOBS                      */
/* Description   | Clear OBS Request to SWC                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus : Status of the current operation          */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/*               | DCM_E_PENDING 0x0A                                       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDA4_ClearMarketabilityOBS
(
    const Dcm_OpStatusType OpStatus
)
{
    Std_ReturnType  u1_RetClearOBS;
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    /* OBS Clear */
    u1_RetClearOBS = Dcm_Dsp_SIDA4_ClearOBS( OpStatus );
    switch( u1_RetClearOBS )
    {
        case E_OK:
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SIDA4_RES_CLEAROPT_POS] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SIDA4_REQ_CLEAROPT_POS];
            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SIDA4_RES_DATA_LENGTH;
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            break;
        case DCM_E_PENDING:
            /* Return value ignoring */
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SIDA4_CLEAROBS );
            /* Return value ignoring */
            (void)Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
            u1_RetVal = DCM_E_PENDING;
            break;
        default:
            /* NRC:0x10 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            break;
    }

    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SIDA4 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-09-26                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
