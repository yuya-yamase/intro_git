/* Dem_DTC_FilDTC_ReadinessGrp_c(v5-5-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_FilDTC_ReadinessGrp/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
#include "../../../../cfg/Dem_Readiness_Cfg.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_Pm_Misfire.h"
#include "../../../../usr/Dem_Readiness_Callout.h"

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


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u08_ReadinessGroupIndexType, DEM_VAR_NO_INIT )  Dem_ReadinessGroupIdForFilter;
static VAR( Dem_u16_EventCtrlIndexType, DEM_VAR_NO_INIT )  Dem_ReadinessGroupEvtListIdx;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_DTC_SetDTCFilterForReadiness                         */
/* Description   | Set filter of ReadinessGroup.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] ReadinessGroupId :                                  */
/*               |        Defines the Readiness group for DTC filter        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Filter was accepted                  */
/*               |        DEM_IRT_NG : Wrong filter selected                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SetDTCFilterForReadiness
(
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) ReadinessGroupId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) readinessGroupNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventNum;
#if ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) supported;
#endif  /* ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )            */

    retVal= DEM_IRT_NG;
    readinessGroupNum = Dem_ReadinessGroupNum;

#if ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )   /*  [FuncSw]    */
    supported   =   Dem_JudgeReadinessGroupIdSupported( ReadinessGroupId );
    if ( supported == (boolean)FALSE )
    {
        /*  not support. retVal : DEM_IRT_NG.       */
    }
    else
#endif  /* ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )            */
    {
        Dem_ReadinessGroupIdForFilter = ReadinessGroupId;
        Dem_ReadinessGroupEvtListIdx = ( Dem_u16_EventCtrlIndexType )0U;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        /* misfire filtering for SID19-56 */
        Dem_Misfire_SetFilteredDTCForCylinder();
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

        if( ReadinessGroupId < readinessGroupNum )
        {
            eventNum = Dem_CfgInfoPm_GetEventNumberOfReadinessGroup( DEM_READINESSGROUPINDEX_INVALID, ReadinessGroupId );
            if( eventNum > ( Dem_u16_EventCtrlIndexType )0U )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }
    return retVal;
}

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_GetNextFilteredDTCForReadiness                   */
/* Description   | Gets the next filtered DTC and its DTC status.           */
/* Preconditions | Dem_DTC_SetDTCFilterForReadiness being executed.         */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function               */
/*               | [out] DTCStatusPtr :                                     */
/*               |        receives the status information of the requested  */
/*               |        DTC                                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetNextFilteredDTCForReadiness
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) readinessGroupId;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) readinessGroupNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventListIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) nextEventListIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) retChkEventAvailable;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkCylDtc;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkDtc;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) eventOBDKind;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    readinessGroupId = Dem_ReadinessGroupIdForFilter;
    readinessGroupNum = Dem_ReadinessGroupNum;
    nextEventListIndex = Dem_ReadinessGroupEvtListIdx;

    if( readinessGroupId < readinessGroupNum )
    {
        eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

        eventNum = Dem_CfgInfoPm_GetEventNumberOfReadinessGroup( DEM_READINESSGROUPINDEX_INVALID, readinessGroupId );

        for( eventListIndex = nextEventListIndex; eventListIndex < eventNum; eventListIndex++  )
        {
            eventCtrlIndex = Dem_CfgInfoPm_GetEventCtrlIndexOfReadinessGroup( DEM_READINESSGROUPINDEX_INVALID, readinessGroupId, eventListIndex );
            if ( eventCtrlIndex < eventConfigureNum )                               /* [GUD:if]eventCtrlIndex */
            {
                retChkEventAvailable = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );     /* [GUD]eventCtrlIndex */
                if( retChkEventAvailable == (boolean)TRUE )
                {
                    eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex );   /* [GUD]eventCtrlIndex */
                    if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                    {
                        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );        /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED:eventCtrlIndex]eventStrgIndex */
                        misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );    /* [GUD]eventStrgIndex */

                        if( misfireEventKind == (boolean)FALSE )
                        {
                            retChkDtc = Dem_DTC_GetDTCStatusAndUdsDTC( eventStrgIndex, DTCValuePtr, DTCStatusPtr ); /* [GUD]eventStrgIndex */
                            if( retChkDtc == DEM_IRT_OK )
                            {
                                Dem_ReadinessGroupEvtListIdx = eventListIndex + ( Dem_u16_EventCtrlIndexType )1U;
                                retVal = DEM_IRT_OK;
                            }
                        }
                        else
                        {
                            retChkCylDtc = Dem_Misfire_GetNextFilterdDTCForCylinder( DTCValuePtr, DTCStatusPtr );
                            if( retChkCylDtc == DEM_IRT_OK )
                            {
                                retVal = DEM_IRT_OK;
                            }
                        }

                        if( retVal == DEM_IRT_OK )
                        {
                            break;
                        }
                    }
                }
            }
        }

        if( retVal == DEM_IRT_NO_MATCHING_ELEMENT )
        {
            Dem_ReadinessGroupEvtListIdx = eventNum;
        }
    }

    if( retVal == DEM_IRT_OK )
    {
        /*------------------------------------------*/
        /*  convert to output statusOfDTC.          */
        /*------------------------------------------*/
        (*DTCStatusPtr) =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( (*DTCStatusPtr) );
    }

    return retVal;
}
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DTC_GetNextFilteredDTCForReadiness                   */
/* Description   | Gets the next filtered DTC and its DTC status.           */
/* Preconditions | Dem_DTC_SetDTCFilterForReadiness being executed.         */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function               */
/*               | [out] DTCStatusPtr :                                     */
/*               |        receives the status information of the requested  */
/*               |        DTC                                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetNextFilteredDTCForReadiness
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) readinessGroupId;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) readinessGroupNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventListIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) nextEventListIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) retChkEventAvailable;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkDtc;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) eventOBDKind;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    readinessGroupId = Dem_ReadinessGroupIdForFilter;
    readinessGroupNum = Dem_ReadinessGroupNum;
    nextEventListIndex = Dem_ReadinessGroupEvtListIdx;

    if( readinessGroupId < readinessGroupNum )
    {
        eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

        eventNum = Dem_CfgInfoPm_GetEventNumberOfReadinessGroup( DEM_READINESSGROUPINDEX_INVALID, readinessGroupId );

        for( eventListIndex = nextEventListIndex; eventListIndex < eventNum; eventListIndex++  )
        {
            eventCtrlIndex = Dem_CfgInfoPm_GetEventCtrlIndexOfReadinessGroup( DEM_READINESSGROUPINDEX_INVALID, readinessGroupId, eventListIndex );
            if ( eventCtrlIndex < eventConfigureNum )                               /* [GUD:if]eventCtrlIndex */
            {
                retChkEventAvailable = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );     /* [GUD]eventCtrlIndex */
                if( retChkEventAvailable == (boolean)TRUE )
                {
                    eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex );       /* [GUD]eventCtrlIndex */
                    if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                    {
                        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );        /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
                        retChkDtc = Dem_DTC_GetDTCStatusAndUdsDTC( eventStrgIndex, DTCValuePtr, DTCStatusPtr );     /* [GUD]eventStrgIndex */
                        if( retChkDtc == DEM_IRT_OK )
                        {
                            Dem_ReadinessGroupEvtListIdx = eventListIndex + ( Dem_u16_EventCtrlIndexType )1U;
                            retVal = DEM_IRT_OK;
                            break;
                        }
                    }
                }
            }
        }

        if( retVal == DEM_IRT_NO_MATCHING_ELEMENT )
        {
            Dem_ReadinessGroupEvtListIdx = eventNum;
        }
    }

    if( retVal == DEM_IRT_OK )
    {
        /*------------------------------------------*/
        /*  convert to output statusOfDTC.          */
        /*------------------------------------------*/
        (*DTCStatusPtr) =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( (*DTCStatusPtr) );
    }

    return retVal;
}
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_OFF )         */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
