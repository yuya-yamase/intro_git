/* Dem_ConfigInfo_PriMem_ClearAllowed_c(v5-9-0)                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_PriMem/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../usr/Dem_Clear_Callout.h"

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
/* Functions                                                                */
/****************************************************************************/

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_ClearAllowed_ByEvtCtrlIdx                  */
/* Description   | Gets Clear Allowed.                                      */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventIndex : Event index.                           */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Clear allowed                             */
/*               |        FALSE : Clear not allowed                         */
/* Notes         | The caller of this function must guarantee the range     */
/*               | of EventIndex values                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ClearAllowed_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( boolean, AUTOMATIC ) clearAllowed;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

    clearAllowed  =   (boolean)FALSE;
    if( EventCtrlIndex < eventConfigureNum )                                                                /* [GUD:if]EventCtrlIndex */
    {
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                /* [GUD]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
        clearAllowed    =   Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp( eventStrgIndex );                      /* [GUD]eventStrgIndex */
    }

    return clearAllowed;
}

#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp                  */
/* Description   | Gets Clear Allowed.                                      */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventStorageNum           */
/* Parameters    | [in] EventIndex : Event index.                           */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Clear allowed                             */
/*               |        FALSE : Clear not allowed                         */
/* Notes         | The caller of this function must guarantee the range     */
/*               | of EventIndex values                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) clearAllowed;
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
#if ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON )    /* [FuncSw] */
    VAR( boolean, AUTOMATIC ) clearAllowedByCallout;
#endif  /* ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON )         */

    clearAllowed  =   (boolean)FALSE;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        eventAttr       =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventAttribute;             /* [GUD]EventStrgIndex */
        if (( eventAttr & DEM_EVTATTR_CLEARALLOWED ) == DEM_EVTATTR_CLEARALLOWED )
        {
            clearAllowed  =   (boolean)TRUE;

#if ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON )    /* [FuncSw] */
            clearAllowedByCallout   =   Dem_CfgInfoPm_JudgeClearAllowedByCallout( EventStrgIndex );
            if ( clearAllowedByCallout != (boolean)TRUE )
            {
                clearAllowed  =   (boolean)FALSE;
            }
#endif  /* ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON )         */
        }
    }
    return clearAllowed;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_ClearAllowedByConfig_InEvtStrgGrp          */
/* Description   | Gets Clear Allowed.                                      */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventIndex : Event index.                           */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Clear allowed                             */
/*               |        FALSE : Clear not allowed                         */
/* Notes         | The caller of this function must guarantee the range     */
/*               | of EventIndex values                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created. based on Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp(). */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ClearAllowedByConfig_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) clearAllowed;
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    clearAllowed  =   (boolean)FALSE;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        eventAttr       =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventAttribute;             /* [GUD]EventStrgIndex */
        if (( eventAttr & DEM_EVTATTR_CLEARALLOWED ) == DEM_EVTATTR_CLEARALLOWED )
        {
            clearAllowed  =   (boolean)TRUE;
        }
    }
    return clearAllowed;
}

#if ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_JudgeClearAllowedByCallout                 */
/* Description   | Gets Clear Allowed.                                      */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventStorageNum           */
/* Parameters    | [in] EventStrgIndex : Event index.                       */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Clear allowed                             */
/*               |        FALSE : Clear not allowed                         */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_JudgeClearAllowedByCallout
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) clearAllowed;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    VAR( Dem_UdsStatusByteType, AUTOMATIC ) baseDTCStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) cnvDTCStatus;

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;

    /*  check whether EventStrgIndex is OBD event or not.   */
    isSpecificEvent    =   Dem_CfgInfoPm_CheckEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );

    if ( isSpecificEvent == (boolean)TRUE )
    {
        /*----------------------------------------------------------*/
        /*  it's Misfire/Similar event.                             */
        /*  always clear allowed.                                   */
        /*----------------------------------------------------------*/
        clearAllowed    =   (boolean)TRUE;
    }
    else
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */
    {
        /*----------------------------------------------------------*/
        /*  it's nonOBD event.                                      */
        /*  check clear allowed condition by callout function.      */
        /*----------------------------------------------------------*/

        /*----------------------------------------------------------*/
        /*  get statusOfDTC.                                        */
        /*----------------------------------------------------------*/
        (void)Dem_DataMngC_GetER_StatusOfDTC( EventStrgIndex, &baseDTCStatus );         /* no return check required *//* [GUDCHK:CALLER]EventStrgIndex */

        /*----------------------------------------------------------*/
        /*  translate to output statusOfDTC by callout function.    */
        /*----------------------------------------------------------*/
        (void)Dem_DTC_TranslateDTCStatusForOutput( EventStrgIndex, &baseDTCStatus );    /* no return check required *//* [GUDCHK:CALLER]EventStrgIndex */

        /*----------------------------------------------------------*/
        /*  convert to output statusOfDTC.                          */
        /*----------------------------------------------------------*/
        cnvDTCStatus = Dem_DTC_CnvDTCStatus_ForOutput( baseDTCStatus );

        /*----------------------------------------------------------*/
        /*  convert EventStrgIndex to eventId.                      */
        /*----------------------------------------------------------*/
        eventId =   DEM_EVENTID_INVALID;
        (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId ); /* no return check required *//* [GUDCHK:CALLER]EventStrgIndex */

        /*----------------------------------------------------------*/
        /*  call callout function.                                  */
        /*----------------------------------------------------------*/
        clearAllowed    =   Dem_JudgeClearAllowed( eventId, cnvDTCStatus );
    }
    return clearAllowed;
}
#endif  /* ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON )             */
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_ON ) */

#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp                  */
/* Description   | Gets Clear Allowed.                                      */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventIndex : Event index.                           */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Clear allowed                             */
/*               |        FALSE : Clear not allowed                         */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* MISRA DEVIATION */
)
{
    /*  This is empty function for function switching.  */
    return (boolean)TRUE;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_ClearAllowedByConfig_InEvtStrgGrp          */
/* Description   | Gets Clear Allowed.                                      */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventIndex : Event index.                           */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Clear allowed                             */
/*               |        FALSE : Clear not allowed                         */
/* Notes         | The caller of this function must guarantee the range     */
/*               | of EventIndex values                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created. based on Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp(). */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ClearAllowedByConfig_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* MISRA DEVIATION */
)
{
    /*  This is empty function for function switching.  */
    return (boolean)TRUE;
}
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
