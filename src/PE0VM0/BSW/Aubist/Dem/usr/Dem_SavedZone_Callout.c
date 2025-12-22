/* Dem_SavedZone_Callout_c(v5-10-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/SavedZone_Callout/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_SavedZone_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_GetSavedZoneInitializeType                           */
/* Description   | Get initialize type of saved zone.                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_SavedZoneInitializeType                              */
/*               |        DEM_SZINITTYPE_NO_INITIALIZE                      */
/*               |        DEM_SZINITTYPE_INITIALIZE_SAMEAS_CLEARDTC         */
/*               |        DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC_AND_IUMPR   */
/*               |        DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC             */
/*               |        DEM_SZINITTYPE_INITIALIZE_ALL                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_SavedZoneInitializeType, DEM_CODE_CALLOUT ) Dem_GetSavedZoneInitializeType
( void )
{
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitializeType;

    InitializeType = DEM_SZINITTYPE_NO_INITIALIZE;

    return InitializeType;
}


/****************************************************************************/
/* Function Name | Dem_NotifySavedZoneUpdate_Enter                          */
/* Description   | Notify SAVED_ZONE area data update : update start.       */
/* Preconditions | none                                                     */
/* Parameters    | none.                                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZoneUpdate_Enter
( void )
{
    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return ;
}

/****************************************************************************/
/* Function Name | Dem_NotifySavedZoneUpdate_Exit                           */
/* Description   | Notify SAVED_ZONE area data update : update end.         */
/* Preconditions | none                                                     */
/* Parameters    | none.                                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZoneUpdate_Exit
( void )
{
    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return ;
}

#if ( DEM_PFC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_NotifySavedZonePermanentUpdate_Enter                 */
/* Description   | Notify SAVED_ZONE_PERMANENT area data update :           */
/*               |                           update start.                  */
/* Preconditions | none                                                     */
/* Parameters    | none.                                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZonePermanentUpdate_Enter
( void )
{
    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return ;
}

/****************************************************************************/
/* Function Name | Dem_NotifySavedZonePermanentUpdate_Exit                  */
/* Description   | Notify SAVED_ZONE_PERMANENT area data update :           */
/*               |                           update end.                    */
/* Preconditions | none                                                     */
/* Parameters    | none.                                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZonePermanentUpdate_Exit
( void )
{
    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return ;
}
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )        */

#if ( DEM_IUMPR_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_NotifySavedZoneIUMPRUpdate_Enter                     */
/* Description   | Notify SAVED_ZONE_IUMPR area data update :               */
/*               |                           update start.                  */
/* Preconditions | none                                                     */
/* Parameters    | none.                                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZoneIUMPRUpdate_Enter
( void )
{
    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return ;
}

/****************************************************************************/
/* Function Name | Dem_NotifySavedZoneIUMPRUpdate_Exit                      */
/* Description   | Notify SAVED_ZONE_IUMPR area data update :               */
/*               |                           update end.                    */
/* Preconditions | none                                                     */
/* Parameters    | none.                                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZoneIUMPRUpdate_Exit
( void )
{
    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return ;
}
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )        */

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
