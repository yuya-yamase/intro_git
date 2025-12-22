/* Dem_DataAvl_PriMem_Misfire_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataAvl_PriMem_Misfire/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )

#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"

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
/* Function Name | Dem_DataAvl_GetMisfireCylDTCAvailable                    */
/* Description   | Get the available status of a specific Event.            */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_MisfireKindBitType                               */
/*               |      DEM_MISFIRE_KINDBIT_CAT      : CAT enable.          */
/*               |      DEM_MISFIRE_KINDBIT_EMISSION : Emission enable.     */
/*               |      DEM_MISFIRE_KINDBIT_NONE     : both disable.        */
/*               |      DEM_MISFIRE_KINDBIT_BOTH     : both enable.         */
/* Notes         |                                                          */
/*               |  Emission        :   TRUE    TRUE    FALSE   FALSE       */
/*               |  CAT             :   TRUE    FALSE   TRUE    FALSE       */
/*               |----------------------------------------------------------*/
/*               |  eventstrgindex  :   Emi     Emi     CAT     INVALID     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_MisfireKindBitType, DEM_CODE ) Dem_DataAvl_GetMisfireCylDTCAvailable
( void )
{
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailableAndEventStrgIndex( &eventStrgIndex );

    return availableMisfireKind;
}


#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataAvl_GetMisfireCylDTCAvailableAndEventStrgIndex   */
/* Description   | Get the available status of a specific Event.            */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_MisfireKindBitType                               */
/*               |      DEM_MISFIRE_KINDBIT_CAT      : CAT enable.          */
/*               |      DEM_MISFIRE_KINDBIT_EMISSION : Emission enable.     */
/*               |      DEM_MISFIRE_KINDBIT_NONE     : both disable.        */
/*               |      DEM_MISFIRE_KINDBIT_BOTH     : both enable.         */
/* Notes         |                                                          */
/*               |  Emission        :   TRUE    TRUE    FALSE   FALSE       */
/*               |  CAT             :   TRUE    FALSE   TRUE    FALSE       */
/*               |----------------------------------------------------------*/
/*               |  eventstrgindex  :   Emi     Emi     CAT     INVALID     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:Not DEM_MISFIRE_KINDBIT_NONE] EventStrgIndexPtr */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_MisfireKindBitType, DEM_CODE ) Dem_DataAvl_GetMisfireCylDTCAvailableAndEventStrgIndex
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexEmi;
    VAR( boolean, AUTOMATIC ) avlMisfireEmi;
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCAT;
    VAR( boolean, AUTOMATIC ) avlMisfireCAT;
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */

    eventStrgIndex          =   DEM_EVENTSTRGINDEX_INVALID;
    availableMisfireKind    =   DEM_MISFIRE_KINDBIT_NONE;

    /*--------------------------------------*/
    /*  check Misfire Emission value.       */
    /*--------------------------------------*/
    eventStrgIndexEmi   =   Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireEmission();
    avlMisfireEmi       =   Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndexEmi );
    if ( avlMisfireEmi == (boolean)TRUE )
    {
        eventStrgIndex  =   eventStrgIndexEmi;
        availableMisfireKind =  DEM_MISFIRE_KINDBIT_EMISSION;
    }

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    /*--------------------------------------*/
    /*  check Misfire CAT value.            */
    /*--------------------------------------*/
    eventStrgIndexCAT   =   Dem_CfgInfoPm_GetEventStrgIndex_MisfireCAT();
    avlMisfireCAT       =   Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndexCAT );
    if ( avlMisfireCAT == (boolean)TRUE )
    {
        if ( eventStrgIndex == DEM_EVENTSTRGINDEX_INVALID )
        {
            eventStrgIndex  =   eventStrgIndexCAT;
        }
        availableMisfireKind =  ( availableMisfireKind | DEM_MISFIRE_KINDBIT_CAT );
    }
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */

    *EventStrgIndexPtr  =   eventStrgIndex;

    return availableMisfireKind;
}

#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON */

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DataAvl_GetMisfireCylDTCAvailableAndEventStrgIndex   */
/* Description   | Get the available status of a specific Event.            */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_MisfireKindBitType                               */
/*               |      DEM_MISFIRE_KINDBIT_CAT      : CAT enable.          */
/*               |      DEM_MISFIRE_KINDBIT_EMISSION : Emission enable.     */
/*               |      DEM_MISFIRE_KINDBIT_NONE     : both disable.        */
/*               |      DEM_MISFIRE_KINDBIT_BOTH     : both enable.         */
/* Notes         |                                                          */
/*               |  Emission        :   TRUE    TRUE    FALSE   FALSE       */
/*               |  CAT             :   TRUE    FALSE   TRUE    FALSE       */
/*               |----------------------------------------------------------*/
/*               |  eventstrgindex  :   Emi     Emi     CAT     INVALID     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_MisfireKindBitType, DEM_CODE ) Dem_DataAvl_GetMisfireCylDTCAvailableAndEventStrgIndex
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr /* MISRA DEVIATION */
)
{
    *EventStrgIndexPtr  =   Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireEmission();

    return DEM_MISFIRE_KINDBIT_BOTH;
}
#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_OFF */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
