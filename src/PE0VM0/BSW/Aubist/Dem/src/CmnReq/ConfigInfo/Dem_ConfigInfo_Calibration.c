/* Dem_ConfigInfo_Calibration_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#include "../../../cfg/Dem_Calibration_Cfg.h"
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
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId              */
/* Description   | Get EventId by event index.                              */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event ID for retrieving.                      */
/* Return Value  | Dem_EventIdType                                          */
/*               |        EventId.                                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_EventIdType, DEM_CODE_TRUST ) Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /* The specified event index is out of the range ? */
    eventId = Dem_EventCtrlIndexToEventIdTable[ EventCtrlIndex ];                   /* [GUDCHK:CALLER]EventCtrlIndex */

    /* Return with the result. */
    return eventId;
}


#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoCalib_CnvUdmEventIndexToEventId               */
/* Description   | Get EventId by event index.                              */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event ID for retrieving.                      */
/* Return Value  | Dem_EventIdType                                          */
/*               |        EventId.                                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_EventIdType, DEM_CODE_TRUST ) Dem_CfgInfoCalib_CnvUdmEventIndexToEventId
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex           /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /* The specified event index is out of the range ? */
    eventId = Dem_UdmEventIndexToEventIdTable[ UdmEventIndex ];                     /* [GUDCHK:CALLER]UdmEventIndex */

    /* Return with the result. */
    return eventId;
}
#endif  /*  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
/****************************************************************************/
/* Function Name | Dem_CfgInfoCalib_CnvEventConfigIdToEventCtrlIndex        */
/* Description   | Get event index by EventConfigID.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] EventConfigureId   :   EventConfigID.               */
/*               | [out] EventCtrlIndexPtr :                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK / DEM_IRT_NG.                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoCalib_CnvEventConfigIdToEventCtrlIndex
(
    VAR( Dem_EventParameterConfigIdType, AUTOMATIC )    EventConfigureId,
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) EventCtrlIndexPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )        eventCtrlIndex;
    VAR( Dem_EventParameterConfigIdType, AUTOMATIC )    numOfAllEventConfigured;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Get the total number of configurations */
    numOfAllEventConfigured =   (Dem_EventParameterConfigIdType)Dem_CfgInfoCmn_GetMaxNumberOfAllMemoryEvent();
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
    retVal = DEM_IRT_NG;

    if ( EventConfigureId < numOfAllEventConfigured )                               /* [GUD:if]EventConfigureId */
    {
        eventCtrlIndex = Dem_EventParameterIndexOrderTable[ EventConfigureId ];     /* [GUD]EventConfigureId */
        retVal = DEM_IRT_OK;
    }
    *EventCtrlIndexPtr  =   eventCtrlIndex;

    return retVal;
}
#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
