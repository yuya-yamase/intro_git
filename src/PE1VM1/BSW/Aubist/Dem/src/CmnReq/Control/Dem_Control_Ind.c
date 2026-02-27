/* Dem_Control_Ind_c(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_Ind/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_CmnIf_Ind.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Ind.h"

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


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Control_SetWIRStatus                                 */
/* Description   | Set WIRStatus by Event index.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Event index.                                      */
/*               | [in] WIRStatus  :                                        */
/*               |        set WIRStatus.                                    */
/*               |              TRUE  : WIRStatus TRUE                      */
/*               |              FALSE : WIRStatus FALSE                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetWIRStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( boolean, AUTOMATIC ) WIRStatus
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_DTCSettingStatusType, AUTOMATIC ) settingStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) execClearDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retEventIdRange;
    VAR( boolean, AUTOMATIC ) availableStatus;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterInit();
    if( checkStatus == DEM_IRT_OK )
    {
        settingStatus = Dem_Control_GetDTCSettingStatus();
        if( settingStatus == DEM_CTL_STS_DTC_SETTING_ENABLE )
        {
            execClearDTC = Dem_Control_CheckExecClearDTCProcess();
            if( execClearDTC == (boolean)FALSE )
            {
                eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
                retEventIdRange = Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );

                if( retEventIdRange == DEM_IRT_OK )
                {
                    availableStatus = Dem_DataAvl_GetEvtAvlCommon( eventCtrlIndex );
                    if( availableStatus == (boolean)TRUE )
                    {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
                        memKind = Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );
                        if( memKind == DEM_MEMKIND_PRIMARY )
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */
                        {
                            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );            /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
                            retVal = Dem_Ind_SetWIRStatus( eventStrgIndex, WIRStatus );
                        }
                    }
                }
            }
        }
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetIndicatorStatus                           */
/* Description   | Get Indicator Status by Indicator Id.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] IndicatorId :                                       */
/*               |        Indicator Id.                                     */
/*               | [out] IndicatorStatusPtr                                 */
/*               |        Pointer to data for set Indicator Status.         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/*               |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIndicatorStatus
(
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) IndicatorId,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retVal = Dem_Ind_GetIndicatorStatus( IndicatorId, IndicatorStatusPtr );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetIndStatusByEventId                        */
/* Description   | Gets the indicator status derived from the event status. */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [in] IndicatorId :                                       */
/*               |        Number of indicator                               */
/*               | [out] IndicatorStatusPtr                                 */
/*               |        Status of the indicator, like off, on, or blinki- */
/*               |        ng.                                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIndStatusByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) IndicatorId,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retEventIdRange;
    VAR( boolean, AUTOMATIC ) availableStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
        retEventIdRange = Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );

        if( retEventIdRange == DEM_IRT_OK )
        {
            availableStatus = Dem_DataAvl_GetEvtAvlCommon( eventCtrlIndex );
            if( availableStatus == (boolean)TRUE )
            {
                retVal = Dem_Ind_GetIndicatorStatusByEventCtrlIndex( eventCtrlIndex, IndicatorId, IndicatorStatusPtr );
            }
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
