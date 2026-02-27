/* Dcm_Dsp_SID04_c(v5-8-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID04/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if ( DCM_OBDTYPE_TYPE_OBD == STD_ON )
#if ( DCM_SUPPORT_SID04 == STD_ON )

#include <Dcm/Dcm_Dsp_SID04.h>
#include "../../Dsp/cfg/Dcm_Dsp_SID04_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include "Dcm/Dcm_Main_EvtDistr.h"
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID04_REQ_DATA_LENGTH ( (Dcm_MsgLenType)0U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID04_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID04_CancelProc
(
    void
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID04_ClearDTC
(
    void
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
/* Function Name | Dcm_SID04                                                */
/* Description   | <Module>_<DiagnosticService>                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   const Dcm_OpStatusType       : OpStatus           */
/*               | [IN]   const Dcm_MsgContextType*    : ptMsgContext       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/*               | DCM_E_PENDING 0x0A                                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID04 /* MISRA DEVIATION */
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;
    /* Opstatus check */
    if( OpStatus == DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID04_InitialProc( pMsgContext );
        /* Return value is a check-free */
    }
    else if( OpStatus == DCM_CANCEL )
    {
        Dcm_Dsp_SID04_CancelProc();
    }
    else
    {
        /* No process */
    }
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID04_Cbk                                        */
/* Description   | Call Back Function to Continue SID04 Processing          */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   const uint8                  : u1EventId          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID04_Cbk  /* MISRA DEVIATION */
(
    const uint8 u1EventId                 /* MISRA DEVIATION */
)
{
    /* Return value ignoring */
    (void)Dcm_Dsp_SID04_ClearDTC();

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID04_ClearCheckCbk                              */
/* Description   | Call Back Function to Continue SID04 Condition Check     */
/*               | Processing                                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID04_ClearCheckCbk         /* MISRA DEVIATION */
(
    const uint8 u1EventId                                /* MISRA DEVIATION */
)
{
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Std_ReturnType                  u1_RetSwc;

    u1_NegResCode = DCM_E_GENERALREJECT;
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    u1_RetSwc = Dcm_Dsp_SID04_CheckSWC( DCM_PENDING, &u1_NegResCode );
    if( u1_RetSwc == (Std_ReturnType)E_OK )
    {
        /* Return value ignoring */
        (void)Dcm_Dsp_SID04_ClearDTC();
    }
    else if( u1_RetSwc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        /* Return value ignoring */
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID04_CLEARCHK );
    }
    else
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }

    return ;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID04_InitialProc                                */
/* Description   | SID04 Processing                                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   const Dcm_MsgContextType*    : ptMsgContext     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/*               | DCM_E_PENDING 0x0A                                       */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID04_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Std_ReturnType               u1_RetVal;
    Std_ReturnType               u1_RetChkStatus;
    Dcm_NegativeResponseCodeType u1_NegResCode;

    u1_RetVal        = E_OK;
    u1_NegResCode    = (Dcm_NegativeResponseCodeType)0x00U;

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    /* Data Length Check*/
    if( ptMsgContext->reqDataLen == DCM_DSP_SID04_REQ_DATA_LENGTH )
    {
        u1_RetChkStatus = Dcm_Dsp_SID04_CheckSWC( DCM_INITIAL, &u1_NegResCode );
        if( u1_RetChkStatus == (Std_ReturnType)E_OK )
        {
            u1_NegResCode = (Dcm_NegativeResponseCodeType)0x00U;
            u1_RetVal = Dcm_Dsp_SID04_ClearDTC();
            /* Return value is a check-free */
        }
        else if( u1_RetChkStatus == (Std_ReturnType)DCM_E_PENDING )
        {
            u1_NegResCode = (Dcm_NegativeResponseCodeType)0x00U;
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
            /* Return value ignoring */
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID04_CLEARCHK );
            u1_RetVal = DCM_E_PENDING;
        }
        else
        {
            /* No process (u1_NegResCode have been already set by Dcm_Dsp_SID04_CheckSWC function) */
        }
    }
    else
    {
        /* Send Negative Response NRC:0x13 */
        u1_NegResCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( u1_NegResCode != (Dcm_NegativeResponseCodeType)0x00U )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID04_CancelProc                                 */
/* Description   | Receive Cancel request and Set Cancel Flag               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID04_CancelProc
(
    void
)
{
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Dcm_Main_EvtDistr_RetType       u1_RetDel;
    boolean                         b_UserNotifyFlag;

    u1_NegResCode = DCM_E_GENERALREJECT;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        /* Delete CheckSWC Callback Event */
        u1_RetDel = Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID04_CLEARCHK, (boolean)FALSE );

        if ( u1_RetDel == DCM_MAIN_EVTDISTR_E_OK )
        {
            /* Cancel CheckSWC */
            /* Return value ignoring */
            (void)Dcm_Dsp_SID04_CheckSWC( DCM_CANCEL, &u1_NegResCode );
        }
        else
        {
            /* Cancel Clear DTC */
            /* Return value ignoring */
            (void)Dem_DcmClearDTC( DEM_DTC_CANCEL_CLEAR_DTC, DEM_DTC_FORMAT_OBD, DEM_DTC_ORIGIN_PRIMARY_MEMORY );
            /* Return value ignoring */
            (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID04_ALLCLEARDTC , (boolean)FALSE );
        }

        /* Return value ignoring */
        (void)Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    }
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID04_ClearDTC                                   */
/* Description   | Clear DTC Request to DEM                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/*               | DCM_E_PENDING 0x0A                                       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID04_ClearDTC
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
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            break;
        case DEM_CLEAR_PENDING:
            /* Return value ignoring */
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID04_ALLCLEARDTC );
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

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID04 == STD_ON */
#endif /* DCM_OBDTYPE_TYPE_OBD */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2018-12-25                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
