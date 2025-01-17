/* Dem_DTC_DTCStatus_Update_c(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/DTC_DTCStatus_Update/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../cfg/Dem_Data_Cfg.h"

#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"

#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_Pm_DTC_PFC.h"

#include "../../../../inc/Dem_Pm_DataCtl.h"
#include "../../../../inc/Dem_Pm_Misfire.h"
#include "../../../../inc/Dem_Pm_MonSts.h"

#include "../../../../inc/Dem_Pm_Ind_MI.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckDTCStatusChange
(
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) EventQualification,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
);

static FUNC( void, DEM_CODE ) Dem_DTC_UpdateDTCStatusByPassedEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
);
static FUNC( void, DEM_CODE ) Dem_DTC_UpdateDTCStatusByFailedEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
);

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DTC_UpdateDTCStatusByShortMIToContinuousMI
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
);
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DTC_ChangeDTCStatus                                  */
/* Description   | DTC processing for the event which Dem received (update  */
/*               |  handling of DTC status, update information registratio- */
/*               | n to Dem_Data).                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event Index                                       */
/*               | [in] EventQualification :                                */
/*               |        Qualification state of the event (passed, failed- */
/*               |        , not qualified).                                 */
/*               | [out] OldDTCStatusStPtr :                                */
/*               |        DTC status before the event reception.            */
/*               | [out] NewDTCStatusStPtr :                                */
/*               |        DTC status after the event reception.             */
/*               | [out] OccurFlagPtr :                                     */
/*               |        Show that bit3 or bit7 on occurred this time.     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : change of DTCStatus was successful   */
/*               |        DEM_IRT_NG : the call was not successful          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_ChangeDTCStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) EventQualification,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr,
    P2VAR( Dem_OrderListOccurredFlagType, AUTOMATIC, AUTOMATIC ) OccurFlagPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckDTC;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indicatorStatus;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    retVal = DEM_IRT_NG;
    OccurFlagPtr->ConfirmedOccurFlag = (boolean)FALSE;
    OccurFlagPtr->MILOccurFlag = (boolean)FALSE;

    /*  set extendDTCstatus.                        */
    NewDTCStatusStPtr->DTCStatus         =   OldDTCStatusStPtr->DTCStatus;
    NewDTCStatusStPtr->ExtendDTCStatus   =   OldDTCStatusStPtr->ExtendDTCStatus;
    NewDTCStatusStPtr->ExtendDTCStatus2  =   OldDTCStatusStPtr->ExtendDTCStatus2;

    /* The update of each bit is judged by Qualification and the DTC status retrieved. */
    retCheckDTC = Dem_DTC_CheckDTCStatusChange( EventQualification, EventStrgIndex, OldDTCStatusStPtr, NewDTCStatusStPtr ); /* [GUDCHK:CALLER]EventStrgIndex */

    if( retCheckDTC == DEM_IRT_OK )
    {
        if( EventQualification == DEM_EVENT_QUALIFICATION_FAILED )
        {
            /* OldDTCStatus : bit3 = OFF */
            if( ( OldDTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_CDTC ) != DEM_UDS_STATUS_CDTC )
            {
                /* NewDTCStatus : bit3 = ON */
                if( ( NewDTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )
                {
                    /* bit3 change ON */
                    OccurFlagPtr->ConfirmedOccurFlag = (boolean)TRUE;
                }
            }
            if( ( OldDTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_WIR ) != DEM_UDS_STATUS_WIR )
            {
                /* NewDTCStatus : bit7 = ON */
                if( ( NewDTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_WIR ) == DEM_UDS_STATUS_WIR )
                {
                    isMILIndicator  =   Dem_CfgInfoPm_ChkDTCCls_MILONAtConfirmed( EventStrgIndex );     /* [GUDCHK:CALLER]EventStrgIndex */
                    if( isMILIndicator == (boolean)TRUE )
                    {
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
                        (void)Dem_IndMI_GetMILStatusByEventStrgIndex( EventStrgIndex, &indicatorStatus ); /* no return check required */    /* [GUDCHK:CALLER]EventStrgIndex */
                        if ( indicatorStatus != DEM_INDICATOR_SHORT )
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
                        {
                            /* bit7 change ON */
                            OccurFlagPtr->MILOccurFlag = (boolean)TRUE;
                        }
                    }
                }
            }
        }
        retVal = DEM_IRT_OK;
    }

    if( retVal != DEM_IRT_OK )
    {
        /* Output a fixation value */
        NewDTCStatusStPtr->DTCStatus        = DEM_DTCSTATUS_BYTE_DEFAULT;
        NewDTCStatusStPtr->ExtendDTCStatus  = DEM_DTCSTATUSEX_BYTE_DEFAULT;
        NewDTCStatusStPtr->ExtendDTCStatus2 = DEM_DTCSTATUSEX2_BYTE_DEFAULT;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DTC_UpdateDTCStatusByRetentionResult                 */
/* Description   | Update DTCStatus by the event retention result           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        EventStrgIndex                                    */
/*               | [in] EventRetentionResult :                              */
/*               |        Flag indicating the event retention result        */
/*               | [in] ConfirmedOccurFlag :                                */
/*               |        Flag indicating the Confirmed event outbreak      */
/*               | [in] MisfireCylinder :                                   */
/*               |        Misfire cylinder                                  */
/*               | [in] OldDTCStatusStPtr :                                 */
/*               |        DTCStatus before the processing                   */
/*               | [in/out] NewDTCStatusStPtr :                             */
/*               |        DTCStatus after the update.                       */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_UpdateDTCStatusByRetentionResult
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,          /* MISRA DEVIATION */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) EventRetentionResult,
    VAR( boolean, AUTOMATIC ) ConfirmedOccurFlag,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder,    /* MISRA DEVIATION */
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,  /* MISRA DEVIATION */
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
)
{
    if( EventRetentionResult == DEM_IRT_NG )
    {
        /*----------------------------------------------*/
        /*  Update statusOfDTC at Overflow occurred.    */
        /*----------------------------------------------*/
        NewDTCStatusStPtr->DTCStatus = Dem_DTC_ResetAllConfirmedDTCStatus_OnOverflow( NewDTCStatusStPtr->DTCStatus );

        /* Reset Indicator Status bit.              */
        NewDTCStatusStPtr->ExtendDTCStatus = Dem_DTC_ExDTC_ResetIndicatorBit_OnOverflow( NewDTCStatusStPtr->ExtendDTCStatus );

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
        /* When the executed asynchronous processing function is the notification target of MonitorStatus. */
        Dem_MonSts_SetAsyncUpdateMode( DEM_MONSTS_ASYNCUPD_OVERFLOW );
#endif  /*  ( DEM_TRIGGER_FIM_REPORTS == STD_ON )           */

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
        NewDTCStatusStPtr->ExtendDTCStatus = Dem_DTC_ExDTC_ResetPredictiveFaultBit_OnOverflow( NewDTCStatusStPtr->ExtendDTCStatus );
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    */
        Dem_Misfire_RestoreCylinderToTmp_OnOverflow( EventStrgIndex );
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )               */

        /*  Reset ActiveFaultAtCycleStart bit.          */
        /*  Reset ContinuousExp bit                     */
        NewDTCStatusStPtr->ExtendDTCStatus2 = Dem_DTC_ExDTC2_ResetContMIHistAndIndAtCycleStartBit_OnOverflow( NewDTCStatusStPtr->ExtendDTCStatus2 );

    }
    /* Set NewDTCStatus to temporary area */
    Dem_Data_SetDTCStatusStructToTmp( NewDTCStatusStPtr );

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /* Set NewPFC to temporary area */
    Dem_DTC_UpdatePFC( EventStrgIndex, OldDTCStatusStPtr, NewDTCStatusStPtr, MisfireCylinder );
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */

    /* Initialize FailureCounter when ConfirmedOccurFlag is TRUE and        */
    /* NewDTCStatusStPtr->DTCStatus include DEM_UDS_STATUS_CDTC.              */
    if( ConfirmedOccurFlag == (boolean)TRUE )
    {
        if( ( NewDTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )
        {
            /* Initialize FailureCounter                                    */
            Dem_Data_InitFailureCounterOfTmp();
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DTC_CheckDTCStatusChange                             */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventQualification :                                */
/*               |                                                          */
/* Parameters    | [in]  OldDTCStatusStPtr : DTC status before the change.  */
/* Parameters    | [out] NewDTCStatusStPtr : DTC status after the change.   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckDTCStatusChange
(
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) EventQualification,        /* [PRMCHK:CALLER] */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    if( EventQualification == DEM_EVENT_QUALIFICATION_PASSED )
    {
        /* Each bit transition of DTCStatus when accepted PassedEvent. */
        Dem_DTC_UpdateDTCStatusByPassedEvent( EventStrgIndex, OldDTCStatusStPtr, NewDTCStatusStPtr );   /* [GUDCHK:CALLER]EventStrgIndex */
    }
    else if( EventQualification == DEM_EVENT_QUALIFICATION_FAILED )
    {
        /* Each bit transition of DTCStatus when accepted FailedEvent. */
        Dem_DTC_UpdateDTCStatusByFailedEvent( EventStrgIndex, OldDTCStatusStPtr, NewDTCStatusStPtr );   /* [GUDCHK:CALLER]EventStrgIndex */
    }
    else
    {
        /* EventQualification out of the rule. */
        NewDTCStatusStPtr->DTCStatus        =   OldDTCStatusStPtr->DTCStatus;
        NewDTCStatusStPtr->ExtendDTCStatus  =   OldDTCStatusStPtr->ExtendDTCStatus;
        NewDTCStatusStPtr->ExtendDTCStatus2 =   OldDTCStatusStPtr->ExtendDTCStatus2;
    }

    if( OldDTCStatusStPtr->DTCStatus == NewDTCStatusStPtr->DTCStatus )
    {
        /* There is no update of DTCStatus. */
        if( OldDTCStatusStPtr->ExtendDTCStatus != NewDTCStatusStPtr->ExtendDTCStatus )
        {
            /* There is a change in ExtendDTCStatus in the old and the new. */
            retVal = DEM_IRT_OK;
        }
        else
        {
            if( OldDTCStatusStPtr->ExtendDTCStatus2 != NewDTCStatusStPtr->ExtendDTCStatus2 )
            {
                /* There is a change in ExtendDTCStatus in the old and the new. */
                retVal = DEM_IRT_OK;
            }
        }
    }
    else
    {
        /* There is a change in DTCStatus in the old and the new. */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}



/****************************************************************************/
/* Function Name | Dem_DTC_UpdateDTCStatusByPassedEvent                     */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  OldDTCStatusStPtr : DTC status before the change.  */
/* Parameters    | [out] NewDTCStatusStPtr : DTC status after the change.   */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTC_UpdateDTCStatusByPassedEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex, /* MISRA DEVIATION *//* [PRMCHK:CALLER] */
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
)
{
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    VAR( Dem_IndicatorStatusType, AUTOMATIC )       indicatorStatus;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC )       extendStatusOfDTC;
    VAR( Dem_u08_DemBooleanType, AUTOMATIC )        milAtShortMIFlg;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    /* Each bit transition of DTCStatus when accepted PassedEvent. */
    NewDTCStatusStPtr->DTCStatus        =   Dem_DTC_SetPassedDTCStatus( OldDTCStatusStPtr->DTCStatus );

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    (void)Dem_IndMI_GetMILStatusByEventStrgIndex( EventStrgIndex, &indicatorStatus ); /* no return check required */    /* [GUDCHK:CALLER]EventStrgIndex */
    if ( indicatorStatus == DEM_INDICATOR_CONTINUOUS )
    {
        (void)Dem_DataMngC_GetER_ExtendDTCStatus( EventStrgIndex, &extendStatusOfDTC ); /* no return check required */  /* [GUDCHK:CALLER]EventStrgIndex */
        if ( ( extendStatusOfDTC & DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE )
        {
            milAtShortMIFlg = Dem_IndMI_GetMILAtShortMIFlg();
            if ( milAtShortMIFlg != DEM_BOOLEAN_TRUE )
            {
                NewDTCStatusStPtr->DTCStatus = Dem_DTC_ResetWIRStatusBit( NewDTCStatusStPtr->DTCStatus );
            }
        }
    }
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    /*  Extend DTC status : PassedBit history        */
    NewDTCStatusStPtr->ExtendDTCStatus  =   Dem_DTC_ExDTC_SetPassedExDTCStatus( OldDTCStatusStPtr->ExtendDTCStatus );
    NewDTCStatusStPtr->ExtendDTCStatus2 =   Dem_DTC_ExDTC2_SetPassedExDTCStatus( OldDTCStatusStPtr->ExtendDTCStatus2 );

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DTC_UpdateDTCStatusByFailedEvent                     */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  OldDTCStatusStPtr : DTC status before the change.  */
/* Parameters    | [out] NewDTCStatusStPtr : DTC status after the change.   */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTC_UpdateDTCStatusByFailedEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,        /* [PRMCHK:CALLER] */
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
)
{
    VAR( Dem_u08_FailureCounterType, AUTOMATIC )                 failureCounter;
    VAR( Dem_u08_FailureCounterType, AUTOMATIC )                 failureCounterThreshold;
    VAR( boolean, AUTOMATIC )               changeDTCStatus;
    VAR( boolean, AUTOMATIC ) isActiveFault;
    VAR( boolean, AUTOMATIC ) isWIRIndicator;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                 retCheckConfirmedFaultOfCAT;
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )             */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )             */

    changeDTCStatus = (boolean)FALSE;

    /* Each bit transition of DTCStatus when accepted FailedEvent. */
    NewDTCStatusStPtr->DTCStatus        =   Dem_DTC_SetFailedDTCStatus( OldDTCStatusStPtr->DTCStatus );
    NewDTCStatusStPtr->ExtendDTCStatus  =   Dem_DTC_ExDTC_SetFailedExDTCStatus( OldDTCStatusStPtr->ExtendDTCStatus );
    NewDTCStatusStPtr->ExtendDTCStatus2 =   Dem_DTC_ExDTC2_SetFailedExDTCStatus( OldDTCStatusStPtr->ExtendDTCStatus2 );

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    for [1]13 CCR section1968.2 */
    retCheckConfirmedFaultOfCAT = Dem_Misfire_CheckConfirmedFaultOfCAT( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */
    if( retCheckConfirmedFaultOfCAT == DEM_IRT_OK )
    {
        changeDTCStatus = (boolean)TRUE;
    }

    if( changeDTCStatus != (boolean)TRUE )
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )     */
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
    {
        Dem_Data_GetFailureCounterFromTmp( &failureCounter, &failureCounterThreshold );
        if( failureCounter >= failureCounterThreshold )
        {
            changeDTCStatus = (boolean)TRUE;
        }
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
        else
        {
            if ( ( ( OldDTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC ) &&
                 ( ( OldDTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_PDTC ) != DEM_UDS_STATUS_PDTC ) )
            {
                changeDTCStatus = (boolean)TRUE;
            }
        }
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
    }

    if( changeDTCStatus == (boolean)TRUE )
    {
        NewDTCStatusStPtr->DTCStatus   =   Dem_DTC_SetConfirmedDTCBit( NewDTCStatusStPtr->DTCStatus );

        /* INFO: Only the indicator of MIL and UserDefinedIndicator is considered. */

        /*  If Indicator use, set IndicatorFlag of extend DTC status.   */
        isActiveFault    =   Dem_CfgInfoPm_GetIsActiveFault( EventStrgIndex );      /* [GUDCHK:CALLER]EventStrgIndex */
        if( isActiveFault == (boolean)TRUE )
        {
            /*  Extend DTC status : ConfirmedBit history, Indicator information   */
            NewDTCStatusStPtr->ExtendDTCStatus =   Dem_DTC_ExDTC_SetIndicatorAndConfirmedHistoryBit( NewDTCStatusStPtr->ExtendDTCStatus );

            /*  If MIL or UserDefinedIndicator use, set bit7 to ON.     */
            isWIRIndicator  =   Dem_CfgInfoPm_ChkDTCCls_WIRbitONAtConfirmed( EventStrgIndex );  /* [GUDCHK:CALLER]EventStrgIndex */
            if( isWIRIndicator == (boolean)TRUE )
            {
                NewDTCStatusStPtr->DTCStatus = Dem_DTC_SetWIRStatusBit( NewDTCStatusStPtr->DTCStatus );

                /* Extend DTC status2 : Continuous Experience Bit */
                isMILIndicator = Dem_CfgInfoPm_ChkDTCCls_MILONAtConfirmed( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex */
                if ( isMILIndicator == (boolean)TRUE )
                {
                    NewDTCStatusStPtr->ExtendDTCStatus2 =   Dem_DTC_ExDTC2_SetContinuousMIHistoryBit( NewDTCStatusStPtr->ExtendDTCStatus2 );
                }
            }
        }
        else
        {
            /*  Set Only ConfirmedHistory bit.      */
            /*  Extend DTC status : ConfirmedBit history        */
            NewDTCStatusStPtr->ExtendDTCStatus =   Dem_DTC_ExDTC_SetConfirmedHistoryBit( NewDTCStatusStPtr->ExtendDTCStatus );
        }
    }
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    if ( ( NewDTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_WIR ) != DEM_UDS_STATUS_WIR )
    {
        /* When Short-MI -> Continuous-MI, Bit7 turns on. */
        Dem_DTC_UpdateDTCStatusByShortMIToContinuousMI( EventStrgIndex, NewDTCStatusStPtr );    /* [GUDCHK:CALLER]EventStrgIndex */
    }
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
    return ;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_UpdateDTCStatusByShortMIToContinuousMI           */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex : EventStrgIndex                    */
/* Parameters    | [in/out] NewDTCStatusStPtr : DTC status after the change.*/
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTC_UpdateDTCStatusByShortMIToContinuousMI
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
)
{
    VAR( boolean, AUTOMATIC ) hasContinuousMI;
    VAR( boolean, AUTOMATIC ) isClassA;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indicatorStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) b1counterExist;
    VAR( boolean, AUTOMATIC ) b1CounterThresholdReached;

    hasContinuousMI = Dem_CfgInfoPm_ChkDTCCls_HasContinuousMI( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex */
    if ( hasContinuousMI == (boolean)TRUE )
    {
        (void)Dem_IndMI_GetMILStatusByEventStrgIndex( EventStrgIndex, &indicatorStatus ); /* no return check required */    /* [GUDCHK:CALLER]EventStrgIndex */

        if ( indicatorStatus == DEM_INDICATOR_SHORT )
        {
            isClassA = Dem_CfgInfoPm_ChkDTCCls_MILONAtConfirmed( EventStrgIndex );          /* [GUDCHK:CALLER]EventStrgIndex */
            if ( isClassA == (boolean)TRUE )
            {
                /* Class A */
                NewDTCStatusStPtr->DTCStatus = Dem_DTC_SetWIRStatusBit( NewDTCStatusStPtr->DTCStatus );
            }
            else
            {
                /* Class B1 */
                b1counterExist = Dem_IndMI_CheckB1CounterThresholdReached( EventStrgIndex, &b1CounterThresholdReached );    /* [GUDCHK:CALLER]EventStrgIndex */
                if ( b1counterExist == DEM_IRT_OK )
                {
                    if ( b1CounterThresholdReached == (boolean)TRUE )
                    {
                        NewDTCStatusStPtr->DTCStatus = Dem_DTC_SetWIRStatusBit( NewDTCStatusStPtr->DTCStatus );
                    }
                }
            }
        }
    }

    return;
}
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
