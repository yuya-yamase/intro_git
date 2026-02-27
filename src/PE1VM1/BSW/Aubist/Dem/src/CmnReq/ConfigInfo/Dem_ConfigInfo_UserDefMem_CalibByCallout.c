/* Dem_ConfigInfo_UserDefMem_CalibByCallout_c(v5-8-0)                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_UserDefMem_CalibByCallout/CODE             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_PBcfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "Dem_ConfigInfo_Calibration.h"
#include "../../../usr/Dem_Calibration_Callout.h"

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
/* Preconditions | EventCtrlIndex < Dem_UdmMemEventConfigureNum             */
/* Parameters    | [in] EventCtrlIndex :  EventIndex                        */
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
    VAR( boolean, AUTOMATIC ) eventAvailableDef;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /*  convert UdmEventIndex to eventId.        */
    eventId     =   Dem_CfgInfoCalib_CnvUdmEventIndexToEventId( UdmEventIndex );    /* [GUDCHK:CALLER]UdmEventIndex */

    /*  get data.        */
    eventAvailableDef   = Dem_Calib_GetEventAvailable( eventId );

    /*  check output value.     */
    if ( eventAvailableDef != (boolean)FALSE )
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
/* Preconditions | UdmEventIndex < Dem_UdmMemEventConfigureNum              */
/* Parameters    | [in] EventCtrlIndex :  EventIndex                        */
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
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /*  convert UdmEventIndex to eventId.        */
    eventId     =   Dem_CfgInfoCalib_CnvUdmEventIndexToEventId( UdmEventIndex );    /* [GUDCHK:CALLER]UdmEventIndex */

    /*  get UDS DTC value.                   */
    udsDTCValue     =   Dem_Calib_GetUdsDTCValue( eventId );

    /*  mask output value.      */
    udsDTCValue     =   udsDTCValue & DEM_CALIB_UDSDTCVALUE_MASK;


    return udsDTCValue;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetIsWIRIndicator                          */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
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
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( boolean, AUTOMATIC ) isWIRIndicator;

    /*  convert UdmEventIndex to eventId.        */
    eventId     =   Dem_CfgInfoCalib_CnvUdmEventIndexToEventId( UdmEventIndex );    /* [GUDCHK:CALLER]UdmEventIndex */

    {
        /*  get data.        */
        isWIRIndicator  =   Dem_Calib_GetIsWIRIndicator( eventId );

        /*  check output value.     */
        if ( isWIRIndicator != (boolean)TRUE )
        {
            isWIRIndicator    =   (boolean)FALSE;
        }
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
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /*  convert EventStrgIndex to eventId.        */
    eventId     =   Dem_CfgInfoCalib_CnvUdmEventIndexToEventId( UdmEventIndex );    /* [GUDCHK:CALLER]UdmEventIndex */

    /*  get data.        */
    eventPriority   =   Dem_Calib_GetEventPriority( eventId );

    /*------------------------------------------*/
    /*    0:    correct priority(highest)       */
    /*      DEM_PRIORITY_RESERVED_HI_MIN        */
    /*          invalid priority(reserve)       */
    /*      DEM_PRIORITY_RESERVED_HI_MAX        */
    /*          DEM_PRIORITY_OBD_DEFAULT        */
    /*                                          */
    /*              correct priority            */
    /*                                          */
    /*          DEM_PRIORITY_NONOBD_DEFAULT     */
    /*      DEM_PRIORITY_RESERVED_LO_MIN        */
    /*          invalid priority(reserve)       */
    /*  255:DEM_PRIORITY_RESERVED_LO_MAX(255)   */
    /*------------------------------------------*/
    /*  check output value.     */
    if ( eventPriority >= DEM_PRIORITY_RESERVED_LO_MIN )  /*    reserved area check :   low reserve : DEM_PRIORITY_RESERVED_LO_MIN <= value <= DEM_PRIORITY_RESERVED_LO_MAX(255)    */
    {
        eventPriority   =   DEM_PRIORITY_NONOBD_DEFAULT;
    }
    else if ( eventPriority <= DEM_PRIORITY_RESERVED_HI_MAX )  /*    reserved area check :   high reserve : DEM_PRIORITY_RESERVED_HI_MIN <= value <= DEM_PRIORITY_RESERVED_HI_MAX    */
    {
        if ( eventPriority >= DEM_PRIORITY_RESERVED_HI_MIN )  /*    reserved area check :   high value  */
        {
            eventPriority   =   DEM_PRIORITY_NONOBD_DEFAULT;
        }
    }
    else
    {
        /*  no process.         */
    }
    return eventPriority;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
