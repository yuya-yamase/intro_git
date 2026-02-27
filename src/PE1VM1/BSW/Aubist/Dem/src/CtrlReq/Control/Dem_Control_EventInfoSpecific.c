/* Dem_Control_EventInfoSpecific_c(v5-9-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_EventInfoSpecific/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Misfire_Cfg.h"
#include "../../../cfg/Dem_Similar_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_Specific.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../inc/Dem_Rc_SimilarMng.h"
#include "Dem_Control_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_SetExceedanceUsedForMisfireEmission          */
/* Description   | Set exceedanceUsed status.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExceedanceUsedStatus : ExceedanceUsed status.       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_SetExceedanceUsedForMisfireEmission
(
    VAR( boolean, AUTOMATIC ) ExceedanceUsedStatus
)
{
    Dem_Misfire_SetExceedanceUsedForMisfireEmission( ExceedanceUsedStatus );
    return ;
}
#endif /* DEM_MISFIRE_EVENT_CONFIGURED -STD_ON- */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetPendingClearCounter                       */
/* Description   | Gets the current PendingClear counter of an event.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] PendingClearCounterPtr :                           */
/*               |        Pointer to the area to get counter.               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of counter was successful        */
/*               |        DEM_IRT_NG : get of counter failed                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_GetAgingCounter.       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetPendingClearCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u08_HealingCounterType, AUTOMATIC, AUTOMATIC ) PendingClearCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC ) threshold;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*  convert eventid to eventCtrlIndex with check eventAvailable.    */
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventID, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );    /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ] eventStrgIndex */

            /*  check and get similarStrgIndex.     */
            retCnvId        =   Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( eventStrgIndex, &similarStrgIndex );     /* [GUD:RET:DEM_IRT_OK] similarStrgIndex */

            if ( retCnvId == DEM_IRT_OK )
            {
                /*--------------------------------------------------------------------------*/
                /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
                /* These are the reasons why this function needs to get exclusive.          */
                /*  - This function call [DataMng] function directory.                      */
                /*  - This function called from SW-C/Dcm context.                           */
                /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
                SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
                SchM_Exit_Dem_EventMemory();
                /*--------------------------------------------------------------------------*/

                (void)Dem_SimilarMng_GetPendingClearCounter( similarStrgIndex, PendingClearCounterPtr );    /* no return check required */  /* [GUD]similarStrgIndex */

                threshold   =   Dem_CfgInfoPm_GetPendingClearCntThreshold( similarStrgIndex );
                if ( *PendingClearCounterPtr > threshold )
                {
                    *PendingClearCounterPtr =   threshold;
                }

                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetSimilarCondition                          */
/* Description   | Gets the similar condition of an event.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] SimilarConditionArrayPtr :                         */
/*               |        Pointer to the area to get SimilarConditions.     */
/*               | [out] SimilarConditionStatusPtr :                        */
/*               |        Pointer to the area to get SimilarConditions sta- */
/*               |        tus.                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : success                             */
/*               |        DEM_IRT_NG  : failed                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created. based on Dem_Control_GetPendingClearCounter.*/
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetSimilarCondition
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, DEM_APPL_DATA ) SimilarConditionArrayPtr,
    P2VAR( Dem_SimilarConditionStatusType, AUTOMATIC, AUTOMATIC ) SimilarConditionStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( boolean, AUTOMATIC ) similarConditionStoredflg;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_SimilarConditionStatusType, AUTOMATIC ) similarConditionStatus;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*  convert eventid to eventCtrlIndex with check eventAvailable.    */
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventID, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );    /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ] eventStrgIndex */

            /*  check and get similarStrgIndex.     */
            retCnvId        =   Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( eventStrgIndex, &similarStrgIndex );     /* [GUD:RET:DEM_IRT_OK] similarStrgIndex */

            if ( retCnvId == DEM_IRT_OK )
            {
                /*--------------------------------------------------------------------------*/
                /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
                /* These are the reasons why this function needs to get exclusive.          */
                /*  - This function call [DataMng] function directory.                      */
                /*  - This function called from SW-C/Dcm context.                           */
                /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
                SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
                SchM_Exit_Dem_EventMemory();
                /*--------------------------------------------------------------------------*/

                similarConditionStatus = DEM_SIMILARCONDITION_STATUS_NO_DATA;

                faultIndex = DEM_FAULTINDEX_INITIAL;
                failRecordNum = Dem_FailRecordNum;

                /*  check whether SimilarEvent is registered in fault record.       */
                (void)Dem_DataMngC_GetER_FaultIndex( eventStrgIndex, &faultIndex );                                         /* no return check required *//* [GUD]eventStrgIndex */
                if( faultIndex < failRecordNum )
                {
                    similarConditionStoredflg = (boolean)FALSE;

                    /*  check current SimilarConditions stored flag.    */
                    Dem_SimilarMng_GetSimilarConditionStoredflg( similarStrgIndex, &similarConditionStoredflg );            /* [GUD]similarStrgIndex */
                    if( similarConditionStoredflg == (boolean)TRUE )
                    {
                        /*  SimilarConditions is stored.    */

                        Dem_SimilarMng_GetSimilarConditionStoredList( similarStrgIndex, SimilarConditionArrayPtr );         /* [GUD]similarStrgIndex */
                        similarConditionStatus = DEM_SIMILARCONDITION_STATUS_STORED;
                    }
                    else
                    {
                        /*  SimilarConditions not stored.   */

                        statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;

                        /*  check current statusOfDTC.      */
                        (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &statusOfDTC );                               /* no return check required *//* [GUD]eventStrgIndex */
                        if( ( statusOfDTC & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC )      /*  statusOfDTC : bit2  */
                        {
                            /*  SimilarConditions is latched.   */

                            Dem_SimilarMng_GetSimilarConditionLatchedList( similarStrgIndex, SimilarConditionArrayPtr );    /* [GUD]similarStrgIndex */
                            similarConditionStatus = DEM_SIMILARCONDITION_STATUS_LATCHED;
                        }
                    }
                }

                *SimilarConditionStatusPtr = similarConditionStatus;
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetExceedanceCounter                         */
/* Description   | Gets the current ExceedanceCounter counter of an event.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] ExceedanceCounterPtr :                             */
/*               |        Pointer to the area to get counter.               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of counter was successful        */
/*               |        DEM_IRT_NG : get of counter failed                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_GetAgingCounter.       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetExceedanceCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u08_ExceedanceCounterType, AUTOMATIC, AUTOMATIC ) ExceedanceCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( boolean, AUTOMATIC ) exceedanceUsedFlag;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC ) simExceedanceCounter;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )           */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )      /* [FuncSw] */
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC ) misfExceedanceCounter;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*  convert eventid to eventCtrlIndex with check eventAvailable.    */
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventID, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [DataMng] function directory.                      */
            /*  - This function called from SW-C/Dcm context.                           */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();
            /*--------------------------------------------------------------------------*/

            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );    /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ] eventStrgIndex */

            /*  check event attribute.      */
            eventKind   =   Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( eventStrgIndex );    /* [GUD]eventStrgIndex */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )      /* [FuncSw] */
            if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
            {
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /* [FuncSw] */
                if(( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
                {
                    /*--------------------------*/
                    /*  misfire(CAT)            */
                    /*--------------------------*/
                    exceedanceUsedFlag  =   Dem_MisfireExceedanceUsedCat;
                    if( exceedanceUsedFlag == (boolean)TRUE )
                    {
                        misfireIndex    =   Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireCAT();
                        (void)Dem_MisfireMng_GetExceedanceCounter( misfireIndex, &misfExceedanceCounter );  /* no return check required */
                        *ExceedanceCounterPtr   =   (Dem_u08_ExceedanceCounterType)misfExceedanceCounter;
                        if ( misfExceedanceCounter > DEM_MISFIRE_CAT_EXCESSCONTERTHRESHOLD )
                        {
                            *ExceedanceCounterPtr   =   DEM_MISFIRE_CAT_EXCESSCONTERTHRESHOLD;
                        }
                        retVal = DEM_IRT_OK;
                    }
                }
                else
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */
                {
                    /*--------------------------*/
                    /*  misfire(emission)       */
                    /*--------------------------*/
                    exceedanceUsedFlag  =   Dem_Misfire_GetExceedanceUsedForMisfireEmission();
                    if( exceedanceUsedFlag == (boolean)TRUE )
                    {
                        misfireIndex    =   Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireEmission();
                        (void)Dem_MisfireMng_GetExceedanceCounter( misfireIndex, &misfExceedanceCounter );  /* no return check required */
                        *ExceedanceCounterPtr   =   (Dem_u08_ExceedanceCounterType)misfExceedanceCounter;
                        if ( misfExceedanceCounter > DEM_MISFIRE_EMISSION_EXCESSCONTERTHRESHOLD )
                        {
                            *ExceedanceCounterPtr   =   DEM_MISFIRE_EMISSION_EXCESSCONTERTHRESHOLD;
                        }
                        retVal = DEM_IRT_OK;
                    }
                }
            }
            else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            if(( eventKind & ( DEM_EVTKIND_TYPE_SIMILAR_EVENT ) ) == DEM_EVTKIND_TYPE_SIMILAR_EVENT )
            {
                /*--------------------------*/
                /*  similar                 */
                /*--------------------------*/
                /*  check and get similarStrgIndex.     */
                retCnvId        =   Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( eventStrgIndex, &similarStrgIndex );     /* [GUD:RET:DEM_IRT_OK] similarStrgIndex */

                if ( retCnvId == DEM_IRT_OK )
                {
                    exceedanceUsedFlag  =   Dem_SimilarClassRefTable[ similarStrgIndex ].DemExceedanceUsed;     /* [GUD] similarStrgIndex */
                    if( exceedanceUsedFlag == (boolean)TRUE )
                    {
                        (void)Dem_SimilarMng_GetExceedanceCounter( similarStrgIndex, &simExceedanceCounter );   /* no return check required */  /* [GUD]similarStrgIndex */
                        *ExceedanceCounterPtr   =   (Dem_u08_ExceedanceCounterType)simExceedanceCounter;
                        if ( simExceedanceCounter > DEM_SIMILAR_EXCESSCONTERTHRESHOLD )
                        {
                            *ExceedanceCounterPtr   =   DEM_SIMILAR_EXCESSCONTERTHRESHOLD;
                        }
                        retVal = DEM_IRT_OK;
                    }
                }
            }
            else
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )           */
            {
                /*--------------------------------------*/
                /*  normal event    :   DEM_IRT_NG      */
                /*--------------------------------------*/
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON ) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
