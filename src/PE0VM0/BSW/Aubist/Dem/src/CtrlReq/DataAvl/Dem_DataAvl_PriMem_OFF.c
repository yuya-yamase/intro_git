/* Dem_DataAvl_PriMem_OFF_c(v5-3-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataAvl_PriMem_OFF/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_DataAvl.h"

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_OFF )
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataAvl_GetEvtAvl                                    */
/* Description   | Get the available status of a specific Event.            */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        Identification of an event.                       */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Event is available.                        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataAvl_GetEvtAvl
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex      /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    retVal = (boolean)TRUE;

    /*  This is empty function for function switching.  */

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataAvl_GetEvtAvl_InEvtStrgGrp                       */
/* Description   | Get the available status of a specific Event.            */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Identification of an event.                       */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Event is available.                        */
/*               |        FALSE : Event is not available.                   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataAvl_GetEvtAvl_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex      /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) retVal;

    retVal = (boolean)TRUE;

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_OFF */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
