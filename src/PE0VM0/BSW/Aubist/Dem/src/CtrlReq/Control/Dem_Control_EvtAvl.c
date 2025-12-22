/* Dem_Control_EvtAvl_c(v5-9-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_EvtAvl/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_PreFFD.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../usr/Dem_SavedZone_Callout.h"

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEvtAvlValue
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( boolean, AUTOMATIC ) AvailableStatus
);

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

#if ( DEM_EVENT_AVAILABILITY_FIM_REPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Control_SetEvtAvl                                    */
/* Description   | Set the available status of a specific Event.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] AvailableStatus :                                   */
/*               |        This parameter specifies whether the respective   */
/*               |        Event shall be available (TRUE) or not (FALSE).   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Change of available status not       */
/*               |                     accepted.                            */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEvtAvl
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( boolean, AUTOMATIC ) AvailableStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retTempVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );  /* [GUD:RET:DEM_IRT_OK]eventCtrlIndex */

    if( retTempVal == DEM_IRT_OK )
    {
        retVal = Dem_Control_SetEvtAvlValue( eventCtrlIndex, AvailableStatus );         /* [GUD]eventCtrlIndex */
    }

    return retVal;
}
#endif /* ( DEM_EVENT_AVAILABILITY_FIM_REPORT == STD_OFF ) */

#if ( DEM_EVENT_AVAILABILITY_FIM_REPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_SetEvtAvl                                    */
/* Description   | Set the available status of a specific Event.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] AvailableStatus :                                   */
/*               |        This parameter specifies whether the respective   */
/*               |        Event shall be available (TRUE) or not (FALSE).   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Change of available status not       */
/*               |                     accepted.                            */
/*               |        DEM_IRT_FAILED_ENQUEUE : Operation was successful,*/
/*               |                     but failed Enqueue.                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEvtAvl
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( boolean, AUTOMATIC ) AvailableStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retTempVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );  /* [GUD:RET:DEM_IRT_OK]eventCtrlIndex */
    if( retTempVal == DEM_IRT_OK )
    {
        retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_NOTIFY_EVENT_AVAILABLE, (Dem_u16_AsyncReqItemAType)eventCtrlIndex, (Dem_u08_AsyncReqItemBType)AvailableStatus );/* [GUD]eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            (void)Dem_Control_SetEvtAvlValue( eventCtrlIndex, AvailableStatus );      /* no return check required *//* [GUD]eventCtrlIndex */

            retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_NOTIFY_EVENT_AVAILABLE, (Dem_u16_AsyncReqItemAType)eventCtrlIndex, (Dem_u08_AsyncReqItemBType)AvailableStatus );
            if( retTempVal == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
            else
            {
                retVal = DEM_IRT_FAILED_ENQUEUE;
            }
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* When event index can not be obtained */
        /* Discard it as an incorrect event reception */
        /* No process */
    }

    return retVal;
}

#endif /* ( DEM_EVENT_AVAILABILITY_FIM_REPORT == STD_ON ) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_Control_SetEvtAvlValue                               */
/* Description   | Set the available status of a specific Event.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        EventIndex.                                       */
/*               | [in] AvailableStatus :                                   */
/*               |        This parameter specifies whether the respective   */
/*               |        Event shall be available (TRUE) or not (FALSE).   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Change of available status not       */
/*               |                     accepted.                            */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEvtAvlValue
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( boolean, AUTOMATIC ) AvailableStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
#endif  /* ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )              */

    /* Gets event available status */
    retVal = Dem_DataAvl_SetEvtAvl( EventCtrlIndex, AvailableStatus );      /* [GUD:RET:DEM_IRT_OK]EventCtrlIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )   /*  [FuncSw]    */
    if( retVal == DEM_IRT_OK )
    {
        /*  update FCThreshold.         */
        Dem_Event_UpdateFCThresholdValue_InEvtStrgGrp( EventCtrlIndex );    /* [GUD]EventCtrlIndex */
    }
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )            */

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
    if( retVal == DEM_IRT_OK  )
    {
        if( AvailableStatus == (boolean)FALSE )
        {
            checkStatus = Dem_Control_ChkAfterCompleteInit();
            if( checkStatus == DEM_IRT_OK )
            {
                /*--------------------------------------*/
                /*  notify SAVED_ZONE update - start.   */
                Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
                /*--------------------------------------*/

                /* Removes pre-stored freeze frame corresponding to the specified event index. */
                /* PrestoreFreezeFrame exclusive section is controlled in this function. */
                (void)Dem_PreFFD_ClearPrestoredFreezeFrame( EventCtrlIndex );/* no return check required */

                /*--------------------------------------*/
                /*  notify SAVED_ZONE update - end.     */
                Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
                /*--------------------------------------*/

            }
        }
    }
#endif  /* ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )              */

    /* Returns with the result. */
    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
