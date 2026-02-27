/* Dem_ConfigInfo_UserDefMem_Calib_c(v5-8-0)                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_UserDefMem_Calib/CODE                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_OFF )
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_PBcfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "Dem_ConfigInfo_Calibration.h"

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
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetEventAvailable                         */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventIndex < Dem_UdmMemEventConfigureNum                 */
/* Parameters    | [in] EventIndex :  EventIndex                            */
/* Return Value  | boolean                                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE_TRUST ) Dem_CfgInfoUdm_GetEventAvailable
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex           /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_PB_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( boolean, AUTOMATIC ) eventAvailableDef;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_EventParameterConfigIdType, AUTOMATIC ) eventConfigId;

    /*  convert eventIndex to eventConfigId.        */
    eventId             =   Dem_CfgInfoCalib_CnvUdmEventIndexToEventId( UdmEventIndex );                    /* [GUDCHK:CALLER]UdmEventIndex */
    eventConfigId       =   (Dem_EventParameterConfigIdType)eventId - (Dem_EventParameterConfigIdType)1U;

    /*  get data.        */
    eventAttr   = Dem_PB_EventParameterAttribute[ eventConfigId ];                                          /* [GUDCHK:CALLER]UdmEventIndex */
    eventAvailableDef    =   (boolean)FALSE;

    if (( eventAttr & DEM_PB_EVTATTR_AVAILABLE_ENABLE ) == DEM_PB_EVTATTR_AVAILABLE_ENABLE )
    {
        eventAvailableDef    =   (boolean)TRUE;  /*  EventAvailable     */
    }

    return eventAvailableDef;
}
#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON */

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetUdsDTCValue                            */
/* Description   | GetData by EventIndex : DTC value                        */
/* Preconditions | EventIndex < Dem_UdmMemEventConfigureNum                 */
/* Parameters    | [in] UdmEventIndex :  EventIndex                         */
/* Return Value  | Dem_u32_DTCValueType                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u32_DTCValueType, DEM_CODE ) Dem_CfgInfoUdm_GetUdsDTCValue
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex           /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValue;

    /*  get UDS DTC value.                   */
    udsDTCValue    =   Dem_UdmEventParameterTable[ UdmEventIndex ].DemDtcValue;                 /* [GUDCHK:CALLER]UdmEventIndex */

    return udsDTCValue;
}



/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetIsWIRIndicator                         */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventIndex < Dem_UdmMemEventConfigureNum                 */
/* Parameters    | [in] UdmEventIndex :  EventIndex                         */
/* Return Value  | boolean                                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoUdm_GetIsWIRIndicator
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex           /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( boolean, AUTOMATIC ) isWIRIndicator;
    /*  get data.        */
    eventAttr = Dem_UdmEventParameterTable[ UdmEventIndex ].DemEventAttribute;                  /* [GUDCHK:CALLER]UdmEventIndex */

    isWIRIndicator    =   (boolean)FALSE;
    if(( eventAttr & DEM_EVTATTR_INDICATOR_USE ) == DEM_EVTATTR_INDICATOR_USE )
    {
        isWIRIndicator    =   (boolean)TRUE;
    }
    return isWIRIndicator;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetEventPriority                          */
/* Description   | GetData by EventStrgIndex                                */
/* Preconditions | EventIndex < Dem_UdmMemEventConfigureNum                 */
/* Parameters    | [in] UdmEventIndex :  EventIndex                         */
/* Return Value  | Dem_u08_EventPriorityType                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_EventPriorityType, DEM_CODE ) Dem_CfgInfoUdm_GetEventPriority
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex           /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) eventPriority;

    /*  get data.        */
    eventPriority = Dem_UdmEventParameterTable[ UdmEventIndex ].DemEventPriority;                   /* [GUDCHK:CALLER]UdmEventIndex */

    return eventPriority;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_OFF )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
